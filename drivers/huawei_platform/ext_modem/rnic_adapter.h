/*
 * rnic_adapter.h
 */

#ifndef RNIC_ADAPTER_H
#define RNIC_ADAPTER_H

#include <linux/list.h>
#include <linux/skbuff.h>

#define TRANSMIT_SHIFT	(10)
#define TRANSMIT_BUFFER_SIZE	(1UL << TRANSMIT_SHIFT)
#define TRANSMIT_MAX_SIZE     ((1UL << TRANSMIT_SHIFT)  - 4)
#define SDIO_SLAVE_ETH_F_BIT            0x20  /* bit[5] of TranHi is for First Segment Indicator */
#define SDIO_SLAVE_ETH_M_BIT            0x10  /* bit[4] of TranHi is for More Segment Indicator */

#define SDIO_HEAD_SIZE          (5)
#define SEND_BLOCK_SIZE        (512  - 4)
#define SDIO_HEAD_MAX_INDEX         (SDIO_HEAD_SIZE - 1)
#define DATA_CHANEL_ID          (15)

struct rnic_buf_in_packet
{
    struct list_head  node;
    unsigned char    id;
    struct sk_buff* buffer;
};

struct sdio_read_func
{
    unsigned char ucPDNId;
    unsigned long (*cbp_read_buff)(unsigned char ucPDNId, struct sk_buff* pstData);
};

typedef unsigned long (*RCV_C_DL_DATA_FUNC)(unsigned char ucPDNId, struct sk_buff* pstData);

/* It is defined in Balong RNIC driver, The struct of the Config, the lenth of this Struct is 8.
typedef struct
{
    RNIC_MODEM_TYPE_ENUM_UINT8          enModemType;
    unsigned char                       ucRmNetId;
    unsigned short                      usModemId;
    unsigned char                       ucPdnId;
    unsigned char                       ucRabId;
    RNIC_RMNET_STATUS_ENUM_UINT8        enRmnetStatus;
    RNIC_IP_TYPE_ENUM_UINT8             enIpType;
}RNIC_RMNET_CONFIG_STRU;
*/

//Copy from balong RNIC
enum RNIC_RESULT_ENUM
{
    RNIC_OK             = 0,                                                    /* 正常返回 */
    RNIC_NOTSTARTED     = 1,                                                    /* 未开始 */
    RNIC_INPROGRESS     = 2,                                                    /* 运行中 */
    RNIC_PERM           = 3,
    RNIC_NOENT          = 4,
    RNIC_IO             = 5,
    RNIC_NXIO           = 6,
    RNIC_NOMEM          = 7,                                                    /* 未申请到内存 */
    RNIC_BUSY           = 8,                                                    /* RNIC网卡设备忙 */
    RNIC_NODEV          = 9,                                                    /* 无设备 */
    RNIC_INVAL          = 10,                                                   /* 非法设备 */
    RNIC_NOTSUPP        = 11,                                                   /* 操作不支持 */
    RNIC_TIMEDOUT       = 12,                                                   /* 超时 */
    RNIC_SUSPENDED      = 13,                                                   /* 挂起 */
    RNIC_UNKNOWN        = 14,                                                   /* 未知错误 */
    RNIC_TEST_FAILED    = 15,                                                   /* 测试失败 */
    RNIC_STATE          = 16,                                                   /* 状态错误 */
    RNIC_STALLED        = 17,                                                   /* 失速 */
    RNIC_PARAM          = 18,                                                   /* 参数错误 */
    RNIC_ABORTED        = 19,                                                   /* 请求取消 */
    RNIC_SHORT          = 20,                                                   /* 资源不足 */
    RNIC_EXPIRED        = 21,                                                   /* 溢出 */

    RNIC_ADDR_INVALID   = 22,                                                   /* 无法分配地址 */
    RNIC_OUT_RANGE      = 23,                                                   /* 不在有效范围内 */
    RNIC_ERROR          = 0xff,                                                 /* RNIC返回失败 */
    RNIC_BUTT
};

typedef struct RnicDataFrame
{
    struct list_head list_head_node;
    unsigned int list_size;
    spinlock_t slock;
    struct mutex m_mutex;
    wait_queue_head_t wait;
} tRnicDataFrame;


void rnic_read_packet(unsigned char* buffer, unsigned int datalen, unsigned char tranHi);
void rnic_txrx_init(void);

#endif
