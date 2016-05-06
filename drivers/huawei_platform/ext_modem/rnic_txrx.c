/*
 * rnic_txrx.c
 *
 */


#include <linux/module.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/device.h>
#include <linux/sysfs.h>

#include <asm/io.h>
#include <linux/wakelock.h>
#include <linux/platform_device.h>
#include <linux/workqueue.h>
#include <asm/atomic.h>

#include <linux/of.h>
#include "modem_packet.h"
#ifndef VOS_ZOS
#define VOS_ZOS                        2
#endif

#ifndef VOS_OS_VER
#define VOS_OS_VER                      VOS_ZOS
#endif

#ifndef VOS_WIN32
#define VOS_WIN32                      1
#endif

#include <linux/kthread.h>
#include <linux/sched.h>
#include <linux/wait.h>
#include <linux/spinlock.h>

#include "viatel.h"
#include "power.h"
#include "ext_modem.h"
#include "rnic_adapter.h"

#undef HWLOG_TAG
#define HWLOG_TAG rnic_adapter
HWLOG_REGIST();

#define DRIVER_VERSION        "1.0.0"

#define DTS_COMP_RNIC_ADAPTER_NAME "rnic_adapter_interface_dev"

#define RNIC_CONFIG_LENTH    (8)

#define SK_BUFFER_RESERVE    (12)
#define MAX_PDN_ID           (10)
#define CDMA_PDNID           (99)

#define RNIC_DATA_DEBUT     (0)
/*This lenth is come from balong, for them, they will preserved the count of packege is 512*/
#define MAX_QUEUE_LENGTH            (512)
#define MODEM_IP_PACKET_MAX_SIZE    (1501)//Ip package max size 1500  + PDN ID 1 = 1501.

#define DOWN_MODEM_SW_FLOW_COTR_RETRY_TIMES    150


unsigned long rnic_send_packet(struct sk_buff* pstData, unsigned char ucPDNId);
static void printf_data(char* buff, int len);

static struct sdio_read_func read_func[MAX_PDN_ID] = {{0}};
static tRnicDataFrame rnic_frame;
static unsigned char* sdio_buff = NULL;
static unsigned int sdio_buff_lenth = 0;
static unsigned char PdnId = 0;

static int check_regist_function(void)
{
    int i = 0;

    mutex_lock(&rnic_frame.m_mutex);
    for (i = 0; i < MAX_PDN_ID; i++)
    {
        if (read_func[i].cbp_read_buff != NULL)
        {
            mutex_unlock(&rnic_frame.m_mutex);
            return i;
        }
    }
    mutex_unlock(&rnic_frame.m_mutex);

    hwlog_err("%s : cannot find regist function.\n", __func__);
    return -1;
}

static int check_regist_function_count(void)
{
    int i = 0;
    int count = 0;

    mutex_lock(&rnic_frame.m_mutex);
    for (i = 0; i < MAX_PDN_ID; i++)
    {
        if (read_func[i].cbp_read_buff != NULL)
        {
            count ++;
        }
    }
    mutex_unlock(&rnic_frame.m_mutex);

    return count;
}

void rnic_read_packet(unsigned char* buffer, unsigned int datalen, unsigned char tranHi)
{
    struct sk_buff* skb;
    unsigned char* data_ptr = NULL;
    unsigned char f_flag = 0;
    unsigned char m_flag = 0;

    unsigned int buff_lenth = 0;

    hwlog_debug("RNIC__ %s  enter datalen=%d\n", __func__, datalen);

    buff_lenth = datalen;

    if (buffer == NULL)
    {
        hwlog_info("RNIC__ %s  buffer == NULL, ip_ptr == NULL\n", __func__);
        return;
    }

    f_flag = tranHi & SDIO_SLAVE_ETH_F_BIT;
    m_flag = tranHi & SDIO_SLAVE_ETH_M_BIT;
    hwlog_debug("RNIC__ %s  f_flag = %x, m_flag=%x\n", __func__, f_flag, m_flag);

    //Payload data length <=508, There is only one CMD53 in READ Block T1 format with M=0, F=1.
    //508< Payload data <= 1020, There is only one CMD53 in READ Block T2 format with M=0, F=1.
    /*Payload data length >= 1020, There are multiple CMD53. The first CMD53 is READ Block T2 format with M=1, F=1. The remaining
        CMD53 format is determined by the data length which could be either T1, T2 with corresponding M and F bit.*/
    if (SDIO_SLAVE_ETH_F_BIT == f_flag)
    {
        unsigned int packge_size = 0;//the data lenth which we will sent to RNIC, it's the IP data.
        //unsigned int buff_len = 0;//the data lenth which come from Modem, the first byte is PDN id.
        PdnId = *buffer;
        hwlog_debug("RNIC__ %s  PdnId = %d\n", __func__, PdnId);

        if (PdnId == CDMA_PDNID)
        {
            int ret = 0;
            ret = check_regist_function();

            if (ret < 0)
            {
                hwlog_info(  "RNIC__ %s don't find the regist function\n", __func__);
                return;
            }
            else
            {
                PdnId = ret;
            }

            if (check_regist_function_count() > 1)
            {
                hwlog_info(  "RNIC__ %s find more than once regist in CDMA Mode\n", __func__);
            }
        }
        else if (PdnId >= MAX_PDN_ID)
        {
            hwlog_info(  "RNIC__ %s find more than once regist in CDMA Mode\n", __func__);
            return;
        }

        packge_size = buff_lenth - 1;

        hwlog_debug("RNIC__ %s Fist data seg packge_size = %d\n", __func__, packge_size);

        if (NULL != sdio_buff)
        {
            kfree(sdio_buff);
        }

        sdio_buff = kzalloc(packge_size, GFP_KERNEL);

        if (NULL == sdio_buff)
        {
            hwlog_info(  "RNIC__ %s %d: kzalloc failed\n", __func__, __LINE__);
            goto err_out;
        }

        if (SDIO_SLAVE_ETH_M_BIT == m_flag)
        {
            if (buff_lenth > TRANSMIT_MAX_SIZE)
            {
                sdio_buff_lenth = TRANSMIT_MAX_SIZE - 1;
            }
            else
            {
                hwlog_info(  "RNIC__ %s %d: the data lenth isn't value\n", __func__, __LINE__);
                goto err_out;
            }
        }
        else
        {
            sdio_buff_lenth = packge_size;
        }

        memcpy(sdio_buff, (buffer + 1), sdio_buff_lenth);
    }
    else
    {
        unsigned int buff_lenth = 0;

        if (NULL == sdio_buff)
        {
            hwlog_info(  "RNIC__ %s %d: sdio_buff == NULL\n", __func__, __LINE__);
            goto err_out;
        }

        buff_lenth = datalen;
        hwlog_debug("RNIC__ %s follow data seg write lenth = %d\n", __func__, buff_lenth);
        memcpy(sdio_buff + sdio_buff_lenth, buffer, buff_lenth);
        sdio_buff_lenth += buff_lenth;
    }

    if (SDIO_SLAVE_ETH_M_BIT != m_flag)
    {
        
        hwlog_debug("RNIC__ %s %d data_length = %d\n", __func__, __LINE__, sdio_buff_lenth);

        //For PDN id will use 1 Byte, so we should get rid off it in the buff.
        if (sdio_buff_lenth <= 1)
        {
            hwlog_info(  "RNIC__ %s %d: the data lenth isn't value\n", __func__, __LINE__);
            goto err_out;
        }

        mutex_lock(&rnic_frame.m_mutex);
        if (read_func[PdnId].cbp_read_buff != NULL)
        {
            skb = dev_alloc_skb(sdio_buff_lenth + SK_BUFFER_RESERVE);

            if (skb == NULL)
            {
                hwlog_info(  "RNIC__ %s %d:skb alloc failed\n", __func__, __LINE__);
                mutex_unlock(&rnic_frame.m_mutex);
                goto err_out;
            }

            skb_reserve(skb, SK_BUFFER_RESERVE);
            data_ptr = (u8*)skb_put(skb, sdio_buff_lenth);
            hwlog_debug("RNIC__ %s %d packge_size = %d\n", __func__, __LINE__, sdio_buff_lenth);

            memcpy(data_ptr, sdio_buff, sdio_buff_lenth);
            //skb will be free in the call back function used by balong.
            read_func[PdnId].cbp_read_buff(PdnId, skb);
        }
        mutex_unlock(&rnic_frame.m_mutex);
        
        PdnId = 0;
        sdio_buff_lenth = 0;

        if (NULL != sdio_buff)
        {
            kfree(sdio_buff);
            sdio_buff = NULL;
        }
    }

    return;

err_out:
    PdnId = 0;
    sdio_buff_lenth = 0;

    if (NULL != sdio_buff)
    {
        kfree(sdio_buff);
        sdio_buff = NULL;
    }

    return;
}
EXPORT_SYMBOL(rnic_read_packet);

unsigned long SDIO_DL_RegDataCallback(unsigned char ucPDNId, RCV_C_DL_DATA_FUNC pFunc)
{

    if (ucPDNId >= MAX_PDN_ID)
    {
        hwlog_err("RNIC__ %s invalid PDN ID pdn id = %d\n", __func__, ucPDNId);
        return RNIC_OUT_RANGE;
    }

    if (pFunc == NULL)
    {
        hwlog_info("RNIC__ %s unregist call back pdn id = %d\n", __func__, ucPDNId);
    }
    else
    {
        hwlog_info("RNIC__ %s  Regist call back pdn id = %d\n", __func__, ucPDNId);
    }

    mutex_lock(&rnic_frame.m_mutex);
    read_func[ucPDNId].cbp_read_buff = pFunc;
    read_func[ucPDNId].ucPDNId = ucPDNId;
    mutex_unlock(&rnic_frame.m_mutex);
    return RNIC_OK;
}
EXPORT_SYMBOL(SDIO_DL_RegDataCallback);

//When show the data, we'll use this function.
static void printf_data(char* buff, int len)
{
    if (RNIC_DATA_DEBUT)
    {
        int i = 0;

        for (i = 4; i < len; i++)
        {
            if (buff[i] > 0xf)
            {
                hwlog_info("%x", buff[i]);
            }
            else
            {
                hwlog_info("0%x", buff[i]);
            }
        }

        hwlog_info("\n");
    }
}

static int check_list_empty(tRnicDataFrame* pTx)
{
    unsigned long flags = 0;
    int ret = 0;

    spin_lock_irqsave(&pTx->slock, flags);
    ret = list_empty(&pTx->list_head_node);
    spin_unlock_irqrestore(&pTx->slock, flags);

    return ret;
}

static void del_all_list_note(tRnicDataFrame* pTx)
{
    unsigned long flags = 0;
    struct rnic_buf_in_packet* packet = NULL;

    while (1)
    {
        spin_lock_irqsave(&pTx->slock, flags);

        if (!list_empty(&pTx->list_head_node))
        {
            packet = list_first_entry(&pTx->list_head_node, struct rnic_buf_in_packet, node);

            if (packet)
            {
                list_del(&packet->node);
                dev_kfree_skb(packet->buffer);
                kfree(packet);
            }
        }
        else
        {
            spin_unlock_irqrestore(&pTx->slock, flags);
            break;
        }

        spin_unlock_irqrestore(&pTx->slock, flags);
    }

    pTx->list_size = 0;
}

static int rnic_send_packet_thread(void* u)
{
    int ret = 0;
    struct task_struct*  thread = current;
    struct rnic_buf_in_packet* packet = NULL;
    unsigned long flags = 0;

    hwlog_info("RNIC__ %s:Enter function SendPacket thread\n", __func__);

    while (1)
    {
        wait_event(rnic_frame.wait, (!check_list_empty(&rnic_frame) || (!thread)));

        /*thread is existed*/
        if (!thread)
        {
            hwlog_err("RNIC__ %s:thread existed\n", __func__);
            del_all_list_note(&rnic_frame);
            break;
        }

        packet = list_first_entry(&rnic_frame.list_head_node, struct rnic_buf_in_packet, node);

        if (packet)
        {

            spin_lock_irqsave(&rnic_frame.slock, flags);
            list_del(&packet->node);

            if (rnic_frame.list_size > 0)
            {
                rnic_frame.list_size --;
            }
            else
            {
                hwlog_info("RNIC__ %s:WARNING:: list_size don't match size = %d\n", __func__,  rnic_frame.list_size);
            }

            spin_unlock_irqrestore(&rnic_frame.slock, flags);
            ret = rnic_send_packet(packet->buffer, packet->id);
            kfree(packet);
        }
        else
        {
            hwlog_err("RNIC__ %s:can get the right packet\n", __func__);
            return -1;
        }
    }

    return ret;
}

static void rnic_rtate_init(tRnicDataFrame* pTx)
{
    hwlog_info("%s %d: Enter.\n", __func__, __LINE__);
    INIT_LIST_HEAD(&pTx->list_head_node);
    init_waitqueue_head(&pTx->wait);
    spin_lock_init(&pTx->slock);
    mutex_init(&pTx->m_mutex);
    pTx->list_size = 0;
    memset(read_func, 0, sizeof(struct sdio_read_func) * MAX_PDN_ID);
    kthread_run(rnic_send_packet_thread, NULL, "SpiSendDataTask");
    hwlog_info("%s %d: Exit.\n", __func__, __LINE__);
}

unsigned long SDIO_UL_SendPacket(struct sk_buff* pstData, unsigned char ucPDNId)
{
    struct rnic_buf_in_packet* packet = NULL;
    unsigned long flags = 0;

    hwlog_debug("RNIC__ %s: enter, SDIO_UL_SendPacket\n", __func__);

    if (NULL == pstData)
    {
        hwlog_err("RNIC__ %s: the pstData is NULL\n", __func__);
        return RNIC_PARAM;
    }

    packet = kzalloc(sizeof(struct rnic_buf_in_packet), GFP_KERNEL);

    if (NULL == packet)
    {
        hwlog_err("RNIC__ %s:can not kzalloc memory\n", __func__);
        return RNIC_NOMEM;
    }

    packet->buffer = pstData;
    packet->id = ucPDNId;

    spin_lock_irqsave(&rnic_frame.slock, flags);

    if (rnic_frame.list_size >= MAX_QUEUE_LENGTH)
    {
        spin_unlock_irqrestore(&rnic_frame.slock, flags);
        kfree(packet);
        hwlog_err("RNIC__ %s:drop the packet\n", __func__);
        return RNIC_EXPIRED;
    }
    else
    {
        list_add_tail(&packet->node, &rnic_frame.list_head_node);
        rnic_frame.list_size ++;
    }

    spin_unlock_irqrestore(&rnic_frame.slock, flags);
    wake_up(&rnic_frame.wait);

    return RNIC_OK;
}

unsigned long rnic_send_packet(struct sk_buff* pstData, unsigned char ucPDNId)
{
    unsigned char* pSource = NULL;
    unsigned int count = 0;
    unsigned char* buff = NULL;
    int ret = -1;

    if (pstData == NULL)
    {
        hwlog_err("RNIC__ %s %d pstData is null\n", __func__, __LINE__);
        return ret;
    }

    pSource = pstData->data;
    count = pstData->len;

    if (pSource == NULL)
    {
        hwlog_err("RNIC__ %s %d pstData->data is null\n", __func__, __LINE__);
        ret =  -1;
        goto down_out;
    }

    if (check_regist_function() == -1)
    {
        hwlog_err("RNIC__ %s %d RNIC read function don't regist\n", __func__, __LINE__);
        ret =  -1;
        goto down_out;
    }

    if (count + 1 > MODEM_IP_PACKET_MAX_SIZE)
    {
        hwlog_err("RNIC__ %s %d IP package size overflow!\n", __func__, __LINE__);
        ret =  -1;
        goto down_out;
    }

    if (count == 0)
    {
        hwlog_err("RNIC__ %s %d count is don't avaluable!\n", __func__, __LINE__);
        ret =  -1;
        goto down_out;
    }

    if ((0 == get_modem_bus_state()) || (0 == is_via_modem_state_ready()))
    {
        hwlog_err("%s %d via modem is not ready!\n", __func__, __LINE__);
        ret = -5;
        goto down_out;
    }

    //The fist addr in the buff is used to write PDN ID.
    buff = kzalloc(pstData->len + 1, GFP_KERNEL);

    if (NULL == buff)
    {
        hwlog_err("RNIC__ %s %d kralloc failed\n", __func__, __LINE__);
        ret = RNIC_NOMEM;
        goto down_out;
    }

    buff[0] = ucPDNId;
    memcpy(buff + 1, pSource, count);

    hwlog_debug("RNIC__ %s: packge size = %d\n", __func__, rnic_frame.list_size);

    /* call rnic write interface from modem channels driver */
    modem_rnic_write(buff, (count + 1));

    kfree(buff);

down_out:
    dev_kfree_skb(pstData);
    return ret;
}
EXPORT_SYMBOL(SDIO_UL_SendPacket);

void rnic_txrx_init(void)
{
    hwlog_info("%s %d: Enter.\n", __func__, __LINE__);
    rnic_rtate_init(&rnic_frame);
    hwlog_info("%s %d: Exit.\n", __func__, __LINE__);
}
EXPORT_SYMBOL(rnic_txrx_init);

