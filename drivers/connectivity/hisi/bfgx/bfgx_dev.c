

/*****************************************************************************
  1 Include Head file
*****************************************************************************/
#include <linux/platform_device.h>
#include <linux/jiffies.h>
#include <linux/kernel.h>
#include <linux/ktime.h>
#include <linux/delay.h>
#include <linux/gpio.h>
#include <linux/tty.h>
#include <linux/poll.h>
#include <linux/module.h>
#include <linux/miscdevice.h>

#include "board.h"
#include "hw_bfg_ps.h"
#include "plat_type.h"
#include "plat_debug.h"
#include "plat_uart.h"
#include "plat_pm.h"
#include "bfgx_user_ctrl.h"
#include "bfgx_exception_rst.h"

/*****************************************************************************
  Define global variable
*****************************************************************************/
/**
 * This references is the per-PS platform device in the arch/arm/
 * board-xx.c file.
 */
struct platform_device *hw_ps_device = NULL;
STATIC int g_debug_cnt = 0;

uint32 g_bfgx_open_cmd[BFGX_BUTT] =
{
    SYS_CFG_OPEN_BT,
    SYS_CFG_OPEN_FM,
    SYS_CFG_OPEN_GNSS,
    SYS_CFG_OPEN_IR,
    SYS_CFG_OPEN_NFC,
};

uint32 g_bfgx_close_cmd[BFGX_BUTT] =
{
    SYS_CFG_CLOSE_BT,
    SYS_CFG_CLOSE_FM,
    SYS_CFG_CLOSE_GNSS,
    SYS_CFG_CLOSE_IR,
    SYS_CFG_CLOSE_NFC,
};

uint32 g_bfgx_open_cmd_timeout[BFGX_BUTT] =
{
    WAIT_BT_OPEN_TIME,
    WAIT_FM_OPEN_TIME,
    WAIT_GNSS_OPEN_TIME,
    WAIT_IR_OPEN_TIME,
    WAIT_NFC_OPEN_TIME,
};

uint32 g_bfgx_close_cmd_timeout[BFGX_BUTT] =
{
    WAIT_BT_CLOSE_TIME,
    WAIT_FM_CLOSE_TIME,
    WAIT_GNSS_CLOSE_TIME,
    WAIT_IR_CLOSE_TIME,
    WAIT_NFC_CLOSE_TIME,
};

const uint8 *g_bfgx_subsys_name[BFGX_BUTT] =
{
    "BT",
    "FM",
    "GNSS",
    "IR",
    "NFC",
};

extern int isAsic(void);

/*****************************************************************************
  Function implement
*****************************************************************************/

/**********************************************************************/
/* internal functions */
/**
 * Prototype    : ps_get_plat_reference
 * Description  : reference the plat's dat,This references the per-PS
 *                  platform device in the arch/arm/board-xx.c file.
 * input        : use *hw_ps_device
 * output       : the have registered platform device struct
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2012/11/05
 *     Author       : wx144390
 *     Modification : Created function
 *
 */
int32 ps_get_plat_reference(struct ps_plat_s **plat_data)
{
    struct platform_device   *pdev = NULL;
    struct ps_plat_s    *ps_plat_d = NULL;

    pdev = hw_ps_device;
    if (!pdev)
    {
        *plat_data = NULL;
        PS_PRINT_ERR("%s pdev is NULL\n", __func__);
        return FAILURE;
    }

    ps_plat_d  = dev_get_drvdata(&pdev->dev);
    *plat_data = ps_plat_d;

    return SUCCESS;
}

/**
 * Prototype    : ps_get_core_reference
 * Description  : reference the core's data,This references the per-PS
 *                  platform device in the arch/xx/board-xx.c file..
 * input        : use *hw_ps_device
 * output       : the have registered ps_core_d struct
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2012/11/05
 *     Author       : wx144390
 *     Modification : Created function
 *
 */
int32 ps_get_core_reference(struct ps_core_s **core_data)
{
    struct platform_device *pdev = NULL;
    struct ps_plat_s  *ps_plat_d = NULL;

    pdev = hw_ps_device;
    if (!pdev)
    {
        *core_data = NULL;
        PS_PRINT_ERR("%s pdev is NULL\n", __func__);
        return FAILURE;
    }

    ps_plat_d  = dev_get_drvdata(&pdev->dev);
    if (NULL == ps_plat_d)
    {
        PS_PRINT_ERR("ps_plat_d is NULL\n");
        return FAILURE;
    }

    *core_data = ps_plat_d->core_data;

    return SUCCESS;
}

/**
 * Prototype    : ps_chk_bfg_active
 * Description  : to chk wether or not bfg active
 *
 * input        : ps_plat_d
 * output       : no
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2012/11/05
 *     Author       : wx144390
 *     Modification : Created function
 *
 */
bool ps_chk_bfg_active(struct ps_core_s *ps_core_d)
{
    int32 i = 0;
    for (i = 0; i < BFGX_BUTT; i++)
    {
        if (POWER_STATE_SHUTDOWN != atomic_read(&ps_core_d->bfgx_info[i].subsys_state))
        {
            return true;
        }
    }

    return false;
}

/* only gnss is open and it agree to sleep */
bool ps_chk_only_gnss_and_cldslp(struct ps_core_s *ps_core_d)
{
    struct pm_drv_data  *pm_data = pm_get_drvdata();
    if ((POWER_STATE_SHUTDOWN == atomic_read(&ps_core_d->bfgx_info[BFGX_BT].subsys_state)) &&
        (POWER_STATE_SHUTDOWN == atomic_read(&ps_core_d->bfgx_info[BFGX_FM].subsys_state)) &&
        (POWER_STATE_SHUTDOWN == atomic_read(&ps_core_d->bfgx_info[BFGX_IR].subsys_state)) &&
        (POWER_STATE_SHUTDOWN == atomic_read(&ps_core_d->bfgx_info[BFGX_NFC].subsys_state)) &&
        (POWER_STATE_OPEN == atomic_read(&ps_core_d->bfgx_info[BFGX_GNSS].subsys_state))   &&
        (GNSS_AGREE_SLEEP == atomic_read(&pm_data->gnss_sleep_flag)) &&
        (BFGX_ACTIVE == pm_data->bfgx_dev_state))
    {
        return true;
    }
    return false;
}

/**
 * Prototype    : ps_alloc_skb
 * Description  : allocate mem for new skb
 *
 * input        : ps_plat_d
 * output       : no
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2012/11/05
 *     Author       : wx144390
 *     Modification : Created function
 *
 */
struct sk_buff *ps_alloc_skb(uint16 len)
{
    struct sk_buff *skb = NULL;

    PS_PRINT_FUNCTION_NAME;

    skb = alloc_skb(len, GFP_KERNEL);
    if (NULL == skb)
	{
        PS_PRINT_WARNING("can't allocate mem for new skb, len=%d\n", len);
        return NULL;
    }

    skb_put(skb, len);

    return skb;
}

/**
 * Prototype    : ps_kfree_skb
 * Description  : when close a function, kfree skb
 * input        : ps_core_d, skb type
 * output       : no
 *
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2012/12/26
 *     Author       : wx144390
 *     Modification : Created function
 *
 */
void ps_kfree_skb(struct ps_core_s *ps_core_d, uint8 type)
{
    struct sk_buff *skb = NULL;

    PS_PRINT_FUNCTION_NAME;
    if (NULL == ps_core_d)
    {
        PS_PRINT_ERR("ps_core_d is NULL");
        return;
    }

    while ((skb = ps_skb_dequeue(ps_core_d, type)))
    {
        kfree_skb(skb);
    }

    switch (type)
    {
    case TX_HIGH_QUEUE:
        skb_queue_purge(&ps_core_d->tx_high_seq);
        break;
    case TX_LOW_QUEUE:
        skb_queue_purge(&ps_core_d->tx_low_seq);
        break;
    case RX_GNSS_QUEUE:
        skb_queue_purge(&ps_core_d->bfgx_info[BFGX_GNSS].rx_queue);
        break;
    case RX_FM_QUEUE:
        skb_queue_purge(&ps_core_d->bfgx_info[BFGX_FM].rx_queue);
        break;
    case RX_BT_QUEUE:
        skb_queue_purge(&ps_core_d->bfgx_info[BFGX_BT].rx_queue);
        break;
    case RX_DBG_QUEUE:
        skb_queue_purge(&ps_core_d->rx_dbg_seq);
        break;
    case RX_NFC_QUEUE:
        skb_queue_purge(&ps_core_d->bfgx_info[BFGX_NFC].rx_queue);
        break;
    case RX_IR_QUEUE:
        skb_queue_purge(&ps_core_d->bfgx_info[BFGX_IR].rx_queue);
        break;
    default:
        PS_PRINT_ERR("queue type is error, type=%d\n", type);
        break;
    }
    return;
}

/**
 * Prototype    : ps_restore_skbqueue
 * Description  : when err and restore skb to seq function.
 * input        : ps_core_d, skb
 * output       : not
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2012/11/05
 *     Author       : wx144390
 *     Modification : Created function
 *
 */
int32 ps_restore_skbqueue(struct ps_core_s *ps_core_d, struct sk_buff *skb, uint8 type)
{
    PS_PRINT_FUNCTION_NAME;

    if (unlikely((NULL == skb) || (NULL == ps_core_d)))
    {
        PS_PRINT_ERR(" skb or ps_core_d is NULL\n");
        return -EINVAL;
    }

    switch (type)
    {
    case RX_GNSS_QUEUE:
        skb_queue_head(&ps_core_d->bfgx_info[BFGX_GNSS].rx_queue, skb);
        break;
    case RX_FM_QUEUE:
        skb_queue_head(&ps_core_d->bfgx_info[BFGX_FM].rx_queue, skb);
        break;
    case RX_BT_QUEUE:
        skb_queue_head(&ps_core_d->bfgx_info[BFGX_BT].rx_queue, skb);
        break;
    case RX_IR_QUEUE:
        skb_queue_head(&ps_core_d->bfgx_info[BFGX_IR].rx_queue, skb);
        break;
    case RX_NFC_QUEUE:
        skb_queue_head(&ps_core_d->bfgx_info[BFGX_NFC].rx_queue, skb);
        break;
    case RX_DBG_QUEUE:
        skb_queue_head(&ps_core_d->rx_dbg_seq, skb);
        break;

    default:
        PS_PRINT_ERR("queue type is error, type=%d\n", type);
        break;
    }

    return 0;
}

/* prepare to visit dev_node
*/
int32 prepare_to_visit_node(struct ps_core_s *ps_core_d)
{
    struct pm_drv_data *pm_data = NULL;
    uint8 uart_ready = UART_NOT_READY;
    int32  ret = 0;

    pm_data = pm_get_drvdata();
    if (unlikely(NULL == pm_data))
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return -EFAULT;
    }

    /* lock wake_lock */
    ps_core_d->ps_pm->bfg_wake_lock();

    /* open tty if tty has not been opened */
    ret = open_tty_drv(ps_core_d->pm_data);
    if (ret != 0)
    {
        PS_PRINT_ERR("open tty is err! ret = %d\n",ret);
        return -EIO;
    }

    /* try to wake up device */
    spin_lock_bh(&pm_data->node_timer_spinlock);
    atomic_inc(&ps_core_d->node_visit_flag);    /* mark someone is visiting dev node */
    uart_ready = ps_core_d->ps_pm->bfgx_uart_state_get();
    spin_unlock_bh(&pm_data->node_timer_spinlock);
    if (UART_NOT_READY == uart_ready)
    {
        if (0 != host_wkup_dev())
        {
            PS_PRINT_ERR("wkup device FAILED!\n");
            atomic_dec(&ps_core_d->node_visit_flag);
            return -EIO;
        }
    }

    return 0;
}

/* we should do something before exit from visiting dev_node */
int32 post_to_visit_node(struct ps_core_s *ps_core_d)
{
    atomic_dec(&ps_core_d->node_visit_flag);

    return 0;
}

int32 alloc_seperted_rx_buf(uint8 subsys, uint32 len,uint8 alloctype)
{
    struct ps_core_s *ps_core_d = NULL;
    struct bfgx_sepreted_rx_st *pst_sepreted_data = NULL;
    uint8 *p_rx_buf = NULL;

    if (subsys >= BFGX_BUTT)
    {
        PS_PRINT_ERR("subsys out of range! subsys=%d\n", subsys);
        return -EINVAL;
    }
    if (alloctype >= ALLOC_BUFF)
    {
        PS_PRINT_ERR("alloc type out of range! subsys=%d,alloctype=%d\n", subsys,alloctype);
        return -EINVAL;
    }

    ps_get_core_reference(&ps_core_d);
    if (unlikely(NULL == ps_core_d))
    {
        PS_PRINT_ERR("ps_core_d is err\n");
        return -EINVAL;
    }
    pst_sepreted_data = &ps_core_d->bfgx_info[subsys].sepreted_rx;

    if (KZALLOC == alloctype)
    {
        p_rx_buf = kzalloc(len, GFP_KERNEL);
    }
    else if (VMALLOC == alloctype)
    {
        p_rx_buf = vmalloc(len);
    }

    if (NULL == p_rx_buf)
    {
        PS_PRINT_ERR("alloc failed! subsys=%d, len=%d\n", subsys, len);
        return -ENOMEM;
    }

    spin_lock(&pst_sepreted_data->sepreted_rx_lock);
    pst_sepreted_data->rx_prev_seq = RX_SEQ_NULL;
    pst_sepreted_data->rx_buf_all_len = 0;
    pst_sepreted_data->rx_buf_ptr = p_rx_buf;
    pst_sepreted_data->rx_buf_org_ptr = p_rx_buf;
    spin_unlock(&pst_sepreted_data->sepreted_rx_lock);

    return 0;
}

int32 free_seperted_rx_buf(uint8 subsys,uint8 alloctype)
{
    struct ps_core_s *ps_core_d = NULL;
    struct bfgx_sepreted_rx_st *pst_sepreted_data = NULL;

    if (subsys >= BFGX_BUTT)
    {
        PS_PRINT_ERR("subsys out of range! subsys=%d\n", subsys);
        return -EINVAL;
    }
    if (alloctype >= ALLOC_BUFF)
    {
        PS_PRINT_ERR("alloc type out of range! subsys=%d,alloctype=%d\n", subsys,alloctype);
        return -EINVAL;
    }

    ps_get_core_reference(&ps_core_d);
    if (unlikely(NULL == ps_core_d))
    {
        PS_PRINT_ERR("ps_core_d is NULL\n");
        return -EINVAL;
    }
    pst_sepreted_data = &ps_core_d->bfgx_info[subsys].sepreted_rx;

    spin_lock(&pst_sepreted_data->sepreted_rx_lock);
    if (NULL != pst_sepreted_data->rx_buf_org_ptr)
    {
        if (KZALLOC == alloctype)
        {
            kfree(pst_sepreted_data->rx_buf_org_ptr);
        }
        else if (VMALLOC == alloctype)
        {
            vfree(pst_sepreted_data->rx_buf_org_ptr);
        }
    }
    pst_sepreted_data->rx_prev_seq = RX_SEQ_NULL;
    pst_sepreted_data->rx_buf_all_len = 0;
    pst_sepreted_data->rx_buf_ptr = NULL;
    pst_sepreted_data->rx_buf_org_ptr = NULL;
    spin_unlock(&pst_sepreted_data->sepreted_rx_lock);

    return 0;
}

int32 bfgx_open_fail_process(uint8 subsys, int32 error)
{
    struct ps_core_s *ps_core_d = NULL;

    if (subsys >= BFGX_BUTT)
    {
         PS_PRINT_ERR("subsys is error, subsys=[%d]\n", subsys);
         return BFGX_POWER_FAILED;
    }

    if (error >= BFGX_POWER_ENUM_BUTT)
    {
         PS_PRINT_ERR("error is error, error=[%d]\n", error);
         return BFGX_POWER_FAILED;
    }

    ps_get_core_reference(&ps_core_d);
    if (unlikely(NULL == ps_core_d))
    {
        PS_PRINT_ERR("ps_core_d is NULL\n");
        return BFGX_POWER_FAILED;
    }

    PS_PRINT_INFO("bfgx open fail, type=[%d]\n", error);

    switch (error)
    {
    case BFGX_POWER_PULL_POWER_GPIO_FAIL:
    case BFGX_POWER_TTY_OPEN_FAIL:
    case BFGX_POWER_TTY_FLOW_ENABLE_FAIL:
        break;

    case BFGX_POWER_WIFI_DERESET_BCPU_FAIL:
    case BFGX_POWER_WIFI_ON_BOOT_UP_FAIL:
        if (BFGX_POWER_SUCCESS == plat_power_fail_exception_info_set(SUBSYS_BFGX, subsys, BFGX_POWER_ON_FAIL))
        {
            bfgx_system_reset();
            plat_power_fail_process_done();
        }
        else
        {
            PS_PRINT_ERR("bfgx power fail, set exception info fail\n");
        }

        ps_core_d->ps_pm->bfg_power_set(subsys, BFG_POWER_GPIO_DOWN);
        break;

    case BFGX_POWER_WIFI_OFF_BOOT_UP_FAIL:
    case BFGX_POWER_DOWNLOAD_FIRMWARE_FAIL:
        ps_core_d->ps_pm->bfg_power_set(subsys, BFG_POWER_GPIO_DOWN);
        break;

    case BFGX_POWER_WAKEUP_FAIL:
    case BFGX_POWER_OPEN_CMD_FAIL:
        if (BFGX_POWER_SUCCESS == plat_power_fail_exception_info_set(SUBSYS_BFGX, subsys, BFGX_POWER_ON_FAIL))
        {
            if (EXCEPTION_SUCCESS != bfgx_subsystem_reset())
            {
                PS_PRINT_ERR("bfgx_subsystem_reset failed \n");
            }
            plat_power_fail_process_done();
        }
        else
        {
            PS_PRINT_ERR("bfgx power fail, set exception info fail\n");
        }

        ps_core_d->ps_pm->bfg_power_set(subsys, BFG_POWER_GPIO_DOWN);
        break;

    default:
        PS_PRINT_ERR("error is undefined, error=[%d]\n", error);
        break;
    }

    return BFGX_POWER_SUCCESS;
}

/**********************************************************************/

int32 uart_wifi_open(void)
{
    struct ps_core_s *ps_core_d = NULL;
    uint64 timeleft;
    int32 ret;

    PS_PRINT_INFO("%s\n", __func__);

    ps_get_core_reference(&ps_core_d);
    if (unlikely(NULL == ps_core_d))
    {
        PS_PRINT_ERR("ps_core_d is err\n");
        return -EINVAL;
    }

    /*如果BFGIN睡眠，则唤醒之*/
    ret = prepare_to_visit_node(ps_core_d);
    if (ret < 0)
    {
        PS_PRINT_ERR("prepare work FAIL\n");
        return ret;
    }

    PS_PRINT_INFO("uart open WCPU\n");
    INIT_COMPLETION(ps_core_d->wait_wifi_opened);
    /* tx sys bt open info */
    ps_uart_state_pre(ps_core_d->tty);
    ps_tx_sys_cmd(ps_core_d, SYS_MSG, SYS_CFG_OPEN_WIFI);

    timeleft = wait_for_completion_timeout(&ps_core_d->wait_wifi_opened, msecs_to_jiffies(WAIT_WIFI_OPEN_TIME));
    if (!timeleft)
    {
        ps_uart_state_dump(ps_core_d->tty);
        PS_PRINT_ERR("wait wifi open ack timeout\n");
        post_to_visit_node(ps_core_d);
        return -ETIMEDOUT;
    }

    post_to_visit_node(ps_core_d);

    msleep(20);

    return SUCCESS;
}

/**********************************************************************/

int32 uart_wifi_close(void)
{
    struct ps_core_s *ps_core_d = NULL;
    uint64 timeleft;
    int32  ret;

    PS_PRINT_INFO("%s\n", __func__);

    ps_get_core_reference(&ps_core_d);
    if (unlikely(NULL == ps_core_d))
    {
        PS_PRINT_ERR("ps_core_d is err\n");
        return -EINVAL;
    }

    /*如果BFGIN睡眠，则唤醒之*/
    ret = prepare_to_visit_node(ps_core_d);
    if (ret < 0)
    {
        PS_PRINT_ERR("prepare work FAIL\n");
        return ret;
    }

    PS_PRINT_INFO("uart close WCPU\n");

    INIT_COMPLETION(ps_core_d->wait_wifi_closed);
    ps_uart_state_pre(ps_core_d->tty);
    ps_tx_sys_cmd(ps_core_d, SYS_MSG, SYS_CFG_CLOSE_WIFI);

    timeleft = wait_for_completion_timeout(&ps_core_d->wait_wifi_closed, msecs_to_jiffies(WAIT_WIFI_CLOSE_TIME));
    if (!timeleft)
    {
        ps_uart_state_dump(ps_core_d->tty);
        PS_PRINT_ERR("wait wifi close ack timeout\n");
        post_to_visit_node(ps_core_d);
        return -ETIMEDOUT;
    }

    PS_PRINT_WARNING("uart close WCPU done,gpio level[%d]\n",board_get_wlan_wkup_gpio_val());

    post_to_visit_node(ps_core_d);

    return SUCCESS;
}

/**********************************************************************/

int32 uart_bfgx_close_cmd(void)
{
#define wait_close_times  (100)
    struct ps_core_s *ps_core_d = NULL;
    int bwkup_gpio_val = 1;
    int32 ret;
    int i;

    PS_PRINT_INFO("%s\n", __func__);

    ps_get_core_reference(&ps_core_d);
    if (unlikely(NULL == ps_core_d))
    {
        PS_PRINT_ERR("ps_core_d is err\n");
        return -EINVAL;
    }

    /*如果BFGIN睡眠，则唤醒之*/
    ret = prepare_to_visit_node(ps_core_d);
    if (ret < 0)
    {
        PS_PRINT_ERR("prepare work FAIL\n");
        return ret;
    }

    /*下发BFGIN shutdown命令*/
    PS_PRINT_INFO("uart shutdown BCPU\n");

    ps_uart_state_pre(ps_core_d->tty);
    ps_tx_sys_cmd(ps_core_d, SYS_MSG, SYS_CFG_SHUTDOWN_SLP);

    ret = FAILURE;
    for(i=0;i<wait_close_times;i++)
    {
        bwkup_gpio_val = board_get_bwkup_gpio_val();
        if(0 == bwkup_gpio_val)
        {
            ret = SUCCESS;
            break;
        }
        msleep(10);
    }
    PS_PRINT_INFO("bfg gpio level:%d, i=%d\n", bwkup_gpio_val, i);

    if (FAILURE == ret)
    {
        ps_uart_state_dump(ps_core_d->tty);
    }

    post_to_visit_node(ps_core_d);

    return ret;
}

int32 bfgx_open_cmd_send(uint32 subsys)
{
    uint64 timeleft;
    struct ps_core_s *ps_core_d = NULL;
    struct st_bfgx_data *pst_bfgx_data = NULL;

    ps_get_core_reference(&ps_core_d);
    if (unlikely(NULL == ps_core_d))
    {
        PS_PRINT_ERR("ps_core_d is null\n");
        return -EINVAL;
    }

    if (subsys >= BFGX_BUTT)
    {
        PS_PRINT_ERR("subsys is err, subsys is [%d]\n", subsys);
        return -EINVAL;
    }

    if (BFGX_IR == subsys)
    {
        ps_tx_sys_cmd(ps_core_d, SYS_MSG, g_bfgx_open_cmd[subsys]);
        msleep(100);
        return 0;
    }

    pst_bfgx_data = &ps_core_d->bfgx_info[subsys];

    INIT_COMPLETION(pst_bfgx_data->wait_opened);
    ps_uart_state_pre(ps_core_d->tty);
    ps_tx_sys_cmd(ps_core_d, SYS_MSG, g_bfgx_open_cmd[subsys]);
    timeleft = wait_for_completion_timeout(&pst_bfgx_data->wait_opened, msecs_to_jiffies(g_bfgx_open_cmd_timeout[subsys]));
    if (!timeleft)
    {
        ps_uart_state_dump(ps_core_d->tty);
        PS_PRINT_ERR("wait %s open ack timeout\n", g_bfgx_subsys_name[subsys]);
        if (BFGX_GNSS == subsys)
        {
            CHR_EXCEPTION(CHR_GNSS_DRV(CHR_GNSS_DRV_EVENT_PLAT, CHR_PLAT_DRV_ERROR_OPEN_THREAD));
        }
        return -ETIMEDOUT;
    }

    return 0;
}

int32 bfgx_close_cmd_send(uint32 subsys)
{
    uint64 timeleft;
    struct ps_core_s *ps_core_d = NULL;
    struct st_bfgx_data *pst_bfgx_data = NULL;

    ps_get_core_reference(&ps_core_d);
    if (unlikely(NULL == ps_core_d))
    {
        PS_PRINT_ERR("ps_core_d is null\n");
        return -EINVAL;
    }

    if (subsys >= BFGX_BUTT)
    {
        PS_PRINT_ERR("subsys is err, subsys is [%d]\n", subsys);
        return -EINVAL;
    }

    if (BFGX_IR == subsys)
    {
        ps_tx_sys_cmd(ps_core_d, SYS_MSG, g_bfgx_close_cmd[subsys]);
        msleep(100);
        return 0;
    }

    pst_bfgx_data = &ps_core_d->bfgx_info[subsys];

    INIT_COMPLETION(pst_bfgx_data->wait_closed);
    ps_uart_state_pre(ps_core_d->tty);
    ps_tx_sys_cmd(ps_core_d, SYS_MSG, g_bfgx_close_cmd[subsys]);
    timeleft = wait_for_completion_timeout(&pst_bfgx_data->wait_closed, msecs_to_jiffies(g_bfgx_close_cmd_timeout[subsys]));
    if (!timeleft)
    {
        ps_uart_state_dump(ps_core_d->tty);
        PS_PRINT_ERR("wait %s close ack timeout\n", g_bfgx_subsys_name[subsys]);
        if (BFGX_GNSS == subsys)
        {
            CHR_EXCEPTION(CHR_GNSS_DRV(CHR_GNSS_DRV_EVENT_PLAT, CHR_PLAT_DRV_ERROR_CLOSE_THREAD));
        }
        return -ETIMEDOUT;
    }

    return 0;
}

/**********************************************************************/
/**
 * Prototype    : hw_bt_open
 * Description  : functions called from above bt hal,when open bt file
 *                  input : "/dev/hwbt"
 * input        : return 0 --> open is ok
 * output       : return !0--> open is false
 *
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2012/12/26
 *     Author       : wx144390
 *     Modification : Created function
 *
 */
STATIC int32 hw_bt_open(struct inode *inode, struct file *filp)
{
    struct ps_core_s *ps_core_d = NULL;
    struct st_bfgx_data *pst_bt_data = NULL;
    int32  error = BFGX_POWER_SUCCESS;
    struct pm_drv_data *pm_data = pm_get_drvdata();

    if (NULL == pm_data)
    {
       PS_PRINT_ERR("pm_data is NULL!\n");
        return OAL_FAIL;
    }

    PS_PRINT_INFO("%s\n", __func__);

    ps_get_core_reference(&ps_core_d);
    if (unlikely((NULL == ps_core_d)||(NULL == inode)||(NULL == filp)||
        (NULL == ps_core_d->ps_pm)||(NULL == ps_core_d->ps_pm->bfg_power_set)))
    {
        PS_PRINT_ERR("ps_core_d is err\n");
        return -EINVAL;
    }

    mutex_lock(&pm_data->host_mutex);
    pst_bt_data = &ps_core_d->bfgx_info[BFGX_BT];

    if (POWER_STATE_OPEN == atomic_read(&pst_bt_data->subsys_state))
    {
        PS_PRINT_WARNING("[BFGX]""BT has opened! It's Not necessary to send msg to device\n");
        mutex_unlock(&pm_data->host_mutex);
        return BFGX_POWER_SUCCESS;
    }

    if (isAsic())
    {
        error = ps_core_d->ps_pm->bfg_power_set(BFGX_BT, BFG_POWER_GPIO_UP);
        if (BFGX_POWER_SUCCESS != error)
        {
            PS_PRINT_ERR("set bt power on err! error = %d\n", error);
            goto bfgx_power_on_fail;
        }
    }

    if (BFGX_POWER_SUCCESS != prepare_to_visit_node(ps_core_d))
    {
        PS_PRINT_ERR("prepare work FAIL\n");
        error = BFGX_POWER_WAKEUP_FAIL;
        goto bfgx_wakeup_fail;
    }

    if (BFGX_POWER_SUCCESS != bfgx_open_cmd_send(BFGX_BT))
    {
        PS_PRINT_ERR("bfgx open cmd fail\n");
        error = BFGX_POWER_OPEN_CMD_FAIL;
        goto bfgx_open_cmd_fail;
    }

    mod_timer(&pm_data->bfg_timer, jiffies + BT_SLEEP_TIME * HZ);

    atomic_set(&pst_bt_data->subsys_state, POWER_STATE_OPEN);
    post_to_visit_node(ps_core_d);

    mutex_unlock(&pm_data->host_mutex);

    return BFGX_POWER_SUCCESS;

bfgx_open_cmd_fail:
    post_to_visit_node(ps_core_d);
bfgx_wakeup_fail:
bfgx_power_on_fail:
    bfgx_open_fail_process(BFGX_BT, error);
    mutex_unlock(&pm_data->host_mutex);
    return BFGX_POWER_FAILED;
}

/**
 * Prototype    : hw_bt_read
 * Description  : functions called from above bt hal,read count data to buf
 * input        : file handle, buf, count
 * output       : return size --> actual read byte size
 *
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2012/12/26
 *     Author       : wx144390
 *     Modification : Created function
 *
 */
STATIC ssize_t hw_bt_read(struct file *filp, int8 __user *buf,
                                size_t count,loff_t *f_pos)
{
    struct ps_core_s *ps_core_d = NULL;
    struct sk_buff *skb = NULL;
    uint16 count1;

    PS_PRINT_FUNCTION_NAME;

    ps_get_core_reference(&ps_core_d);
    if (unlikely((NULL == ps_core_d)||(NULL == buf)||(NULL == filp)))
    {
        PS_PRINT_ERR("ps_core_d is NULL\n");
        return -EINVAL;
    }

    if (NULL == (skb = ps_skb_dequeue(ps_core_d, RX_BT_QUEUE)))
    {
        PS_PRINT_WARNING("bt read skb queue is null!\n");
        return 0;
    }

    /* read min value from skb->len or count */
    count1 = min_t(size_t, skb->len, count);
    if (copy_to_user(buf, skb->data, count1))
    {
        PS_PRINT_ERR("copy_to_user is err!\n");
        ps_restore_skbqueue(ps_core_d, skb, RX_BT_QUEUE);
        return -EFAULT;
    }

    /* have read count1 byte */
    skb_pull(skb, count1);

    /* if skb->len = 0: read is over */
    if (0 == skb->len)
    {   /* curr skb data have read to user */
        kfree_skb(skb);
    }
    else
    {   /* if don,t read over; restore to skb queue */
        ps_restore_skbqueue(ps_core_d, skb, RX_BT_QUEUE);
    }

    return count1;
}

/**
 * Prototype    : hw_bt_write
 * Description  : functions called from above bt hal,write count data to buf
 * input        : file handle, buf, count
 * output       : return size --> actual write byte size
 *
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2012/12/26
 *     Author       : wx144390
 *     Modification : Created function
 *
 */
STATIC ssize_t hw_bt_write(struct file *filp, const int8 __user *buf,
                                size_t count,loff_t *f_pos)
{
    struct ps_core_s *ps_core_d = NULL;
    struct sk_buff *skb;
    uint16 total_len;
    int32  ret = 0;

    PS_PRINT_FUNCTION_NAME;

    ps_get_core_reference(&ps_core_d);
    if (unlikely((NULL == ps_core_d)||(NULL == buf)||(NULL == filp)||(NULL == ps_core_d->ps_pm)))
    {
        PS_PRINT_ERR("ps_core_d is NULL\n");
        return -EINVAL;
    }

    if (count > BT_TX_MAX_FRAME)
    {
        PS_PRINT_ERR("bt skb len is too large!\n");
        return -EINVAL;
    }

    /* if high queue num > MAX_NUM and don't write */
    if (ps_core_d->tx_high_seq.qlen > TX_HIGH_QUE_MAX_NUM)
    {
        PS_PRINT_ERR("bt tx high seqlen large than MAXNUM\n");
        return 0;
    }

    ret = prepare_to_visit_node(ps_core_d);
    if (ret < 0)
    {
        PS_PRINT_ERR("prepare work fail, bring to reset work\n");
        plat_exception_handler(SUBSYS_BFGX, THREAD_BT, BFGX_WAKEUP_FAIL);
        return ret;
    }

    /* modify expire time of uart idle timer */
    mod_timer(&ps_core_d->ps_pm->pm_priv_data->bfg_timer, jiffies + BT_SLEEP_TIME * HZ);

    total_len = count + sizeof(struct ps_packet_head) + sizeof(struct ps_packet_end);

    skb  = ps_alloc_skb(total_len);
    if (NULL == skb)
    {
        PS_PRINT_ERR("ps alloc skb mem fail\n");
        post_to_visit_node(ps_core_d);
        return -EFAULT;
    }

    if (copy_from_user(&skb->data[sizeof(struct ps_packet_head)], buf, count))
    {
        PS_PRINT_ERR("copy_from_user from bt is err\n");
        kfree_skb(skb);
        post_to_visit_node(ps_core_d);
        return -EFAULT;
    }

    ps_add_packet_head(skb->data, BT_MSG, total_len);
    ps_skb_enqueue(ps_core_d, skb, TX_HIGH_QUEUE);
    queue_work(ps_core_d->ps_tx_workqueue, &ps_core_d->tx_skb_work);

    post_to_visit_node(ps_core_d);

    return count;
}

/**
 * Prototype    : hw_bt_poll
 * Description  : called by bt func from hal;
 *                  check whether or not allow read and write
 * input        : file handle
 * output       : no
 *
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2012/12/26
 *     Author       : wx144390
 *     Modification : Created function
 *
 */
STATIC uint32 hw_bt_poll(struct file *filp, poll_table *wait)
{
    struct ps_core_s *ps_core_d = NULL;
    uint32 mask = 0;

    PS_PRINT_FUNCTION_NAME;

    ps_get_core_reference(&ps_core_d);
    if (unlikely((NULL == ps_core_d)||(NULL == filp)))
    {
        PS_PRINT_ERR("ps_core_d is NULL\n");
        return -EINVAL;
    }

    /* push curr wait event to wait queue */
    poll_wait(filp, &ps_core_d->bfgx_info[BFGX_BT].rx_wait, wait);

    if (ps_core_d->bfgx_info[BFGX_BT].rx_queue.qlen)
    {   /* have data to read */
        mask |= POLLIN | POLLRDNORM;
    }

    return mask;
}

/**
 * Prototype    : hw_bt_ioctl
 * Description  : called by bt func from hal; default not use
 * input        : file handle, cmd, arg
 * output       : no
 *
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2012/12/26
 *     Author       : wx144390
 *     Modification : Created function
 *
 */
STATIC int64 hw_bt_ioctl(struct file *file, uint32 cmd, uint64 arg)
{
    PS_PRINT_FUNCTION_NAME;

    return 0;
}

/**
 * Prototype    : hw_bt_release
 * Description  : called by bt func from hal when close bt inode
 * input        : have opened file handle
 * output       : return 0 --> close is ok
 *                return !0--> close is false
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2012/12/26
 *     Author       : wx144390
 *     Modification : Created function
 *
 */
STATIC int32 hw_bt_release(struct inode *inode, struct file *filp)
{
    struct ps_core_s *ps_core_d = NULL;
    struct st_bfgx_data *pst_bt_data = NULL;
    int32 ret = 0;
    struct pm_drv_data *pm_data = pm_get_drvdata();

    if (NULL == pm_data)
    {
       PS_PRINT_ERR("pm_data is NULL!\n");
        return OAL_FAIL;
    }

    PS_PRINT_INFO("%s\n", __func__);

    ps_get_core_reference(&ps_core_d);
    if (unlikely((NULL == ps_core_d)||(NULL == inode)||(NULL == filp)||(NULL == ps_core_d->ps_pm)))
    {
        PS_PRINT_ERR("ps_core_d is NULL\n");
        return -EINVAL;
    }

    mutex_lock(&pm_data->host_mutex);
    pst_bt_data = &ps_core_d->bfgx_info[BFGX_BT];

    wake_up_interruptible(&pst_bt_data->rx_wait);

    ret = prepare_to_visit_node(ps_core_d);
    if (ret < 0)
    {
        /*唤醒失败，bfgx close时的唤醒失败不进行DFR恢复*/
        PS_PRINT_ERR("prepare work FAIL\n");
    }

    ret = bfgx_close_cmd_send(BFGX_BT);
    if (ret < 0)
    {
        /*发送close命令失败，不进行DFR，继续进行下电流程，DFR恢复延迟到下次open时或者其他业务运行时进行*/
        PS_PRINT_ERR("bfgx close cmd fail\n");
    }

    atomic_set(&pst_bt_data->subsys_state, POWER_STATE_SHUTDOWN);
    ps_kfree_skb(ps_core_d, RX_BT_QUEUE);

    if (isAsic())
    {
        ret = ps_core_d->ps_pm->bfg_power_set(BFGX_BT, BFG_POWER_GPIO_DOWN);
        if (ret)
        {
            /*下电失败，不进行DFR，DFR恢复延迟到下次open时或者其他业务运行时进行*/
            PS_PRINT_ERR("set bt power off err!ret = %d\n", ret);
        }
    }

    post_to_visit_node(ps_core_d);

    mutex_unlock(&pm_data->host_mutex);

    return 0;
}

STATIC int32 hw_nfc_open(struct inode *inode, struct file *filp)
{
    struct ps_core_s *ps_core_d = NULL;
    struct st_bfgx_data *pst_nfc_data = NULL;
    int32 error = BFGX_POWER_SUCCESS;
    struct pm_drv_data *pm_data = pm_get_drvdata();

    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return -FAILURE;
    }

    PS_PRINT_INFO("%s", __func__);

    ps_get_core_reference(&ps_core_d);

    if (unlikely((NULL == ps_core_d)||(NULL == inode)||(NULL == filp)||
        (NULL == ps_core_d->ps_pm)||(NULL == ps_core_d->ps_pm->bfg_power_set)))
    {
        PS_PRINT_ERR("ps_core_d is err\n");
        return -EINVAL;
    }

    mutex_lock(&pm_data->host_mutex);
    pst_nfc_data = &ps_core_d->bfgx_info[BFGX_NFC];

    if (POWER_STATE_OPEN == atomic_read(&pst_nfc_data->subsys_state))
    {
        PS_PRINT_WARNING("NFC has opened! It's Not necessary to send msg to device\n");
        mutex_unlock(&pm_data->host_mutex);
        return BFGX_POWER_SUCCESS;
    }

    if (BFGX_POWER_SUCCESS != alloc_seperted_rx_buf(BFGX_NFC, NFC_RX_MAX_FRAME,KZALLOC))
    {
        PS_PRINT_ERR("no mem to allocate to read nfc!\n");
        mutex_unlock(&pm_data->host_mutex);
        return -ENOMEM;
    }

    if (isAsic())
    {
        error = ps_core_d->ps_pm->bfg_power_set(BFGX_NFC, BFG_POWER_GPIO_UP);
        if (BFGX_POWER_SUCCESS != error)
        {
            PS_PRINT_ERR("set nfc power on err! error = %d\n", error);
            goto bfgx_power_on_fail;
        }
    }

    if (BFGX_POWER_SUCCESS != prepare_to_visit_node(ps_core_d))
    {
        PS_PRINT_ERR("prepare work FAIL\n");
        error = BFGX_POWER_WAKEUP_FAIL;
        goto bfgx_wakeup_fail;
    }

    if (BFGX_POWER_SUCCESS != bfgx_open_cmd_send(BFGX_NFC))
    {
        PS_PRINT_ERR("bfgx open cmd fail\n");
        error = BFGX_POWER_OPEN_CMD_FAIL;
        goto bfgx_open_cmd_fail;
    }

    mod_timer(&pm_data->bfg_timer, jiffies + BT_SLEEP_TIME * HZ);

    atomic_set(&pst_nfc_data->subsys_state, POWER_STATE_OPEN);

    post_to_visit_node(ps_core_d);

    mutex_unlock(&pm_data->host_mutex);

    return BFGX_POWER_SUCCESS;

bfgx_open_cmd_fail:
    post_to_visit_node(ps_core_d);
bfgx_wakeup_fail:
bfgx_power_on_fail:
    free_seperted_rx_buf(BFGX_NFC,KZALLOC);
    bfgx_open_fail_process(BFGX_NFC, error);
    mutex_unlock(&pm_data->host_mutex);
    return BFGX_POWER_FAILED;
}

STATIC ssize_t hw_nfc_read(struct file *filp, int8 __user *buf,
                                size_t count,loff_t *f_pos)
{
    struct ps_core_s *ps_core_d = NULL;
    struct sk_buff *skb = NULL;
    uint16 count1;

    PS_PRINT_FUNCTION_NAME;

    ps_get_core_reference(&ps_core_d);
    if (unlikely((NULL == ps_core_d)||(NULL == buf)||(NULL == filp)))
    {
        PS_PRINT_ERR("ps_core_d is NULL\n");
        return -EINVAL;
    }

    if (NULL == (skb = ps_skb_dequeue(ps_core_d, RX_NFC_QUEUE)))
    {
        PS_PRINT_WARNING("nfc read skb queue is null!");
        return 0;
    }

    count1 = min_t(size_t, skb->len, count);
    if (copy_to_user(buf, skb->data, count1))
    {
        PS_PRINT_ERR("copy_to_user is err!\n");
        ps_restore_skbqueue(ps_core_d, skb, RX_NFC_QUEUE);
        return -EFAULT;
    }

    skb_pull(skb, count1);
    if (0 == skb->len)
    {
        kfree_skb(skb);
    }
    else
    {
        ps_restore_skbqueue(ps_core_d, skb, RX_NFC_QUEUE);
    }

    return count1;
}

STATIC ssize_t hw_nfc_write(struct file *filp, const int8 __user *buf,
                                size_t count, loff_t *f_pos)
{
    struct ps_core_s *ps_core_d = NULL;
    int32 ret = 0;

    PS_PRINT_FUNCTION_NAME;

    ps_get_core_reference(&ps_core_d);

    if (unlikely((NULL == ps_core_d)||(NULL == buf)||(NULL == filp)||(NULL == ps_core_d->ps_pm)))
    {
        PS_PRINT_ERR("ps_core_d is NULL\n");
        return -EINVAL;
    }

    if (count > NFC_TX_MAX_FRAME)
    {
        PS_PRINT_ERR("bt skb len is too large!\n");
        return -EINVAL;
    }

    if (ps_core_d->tx_low_seq.qlen > TX_LOW_QUE_MAX_NUM)
    {
        return 0;
    }

    ret = prepare_to_visit_node(ps_core_d);
    if (ret < 0)
    {
        PS_PRINT_ERR("prepare work fail, bring to reset work\n");
        plat_exception_handler(SUBSYS_BFGX, THREAD_NFC, BFGX_WAKEUP_FAIL);
        return ret;
    }
    /* modify expire time of uart idle timer */
    mod_timer(&ps_core_d->ps_pm->pm_priv_data->bfg_timer, jiffies + BT_SLEEP_TIME * HZ);

    /* to divide up packet function and tx to tty work */
    if (ps_tx_nfcbuf(ps_core_d, buf, count) < 0)
    {
        PS_PRINT_ERR("hw_nfc_write is err\n");
        post_to_visit_node(ps_core_d);
        return -EFAULT;
    }

    post_to_visit_node(ps_core_d);

    PS_PRINT_DBG("NFC data write end\n");

    return count;
}


STATIC uint32 hw_nfc_poll(struct file *filp, poll_table *wait)
{
    struct ps_core_s *ps_core_d = NULL;
    uint32 mask = 0;

    PS_PRINT_FUNCTION_NAME;

    ps_get_core_reference(&ps_core_d);
    if (unlikely((NULL == ps_core_d)||(NULL == filp)))
    {
        PS_PRINT_ERR("ps_core_d is NULL\n");
        return -EINVAL;
    }

    /* push curr wait event to wait queue */
    poll_wait(filp, &ps_core_d->bfgx_info[BFGX_NFC].rx_wait, wait);

    if (ps_core_d->bfgx_info[BFGX_NFC].rx_queue.qlen)
    {   /* have data to read */
        mask |= POLLIN | POLLRDNORM;
    }

    return mask;
}

STATIC int32 hw_nfc_release(struct inode *inode, struct file *filp)
{
    struct ps_core_s *ps_core_d = NULL;
    struct st_bfgx_data *pst_nfc_data = NULL;
    int32 ret = 0;
    struct pm_drv_data *pm_data = pm_get_drvdata();

    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return -FAILURE;
    }

    PS_PRINT_INFO("%s\n", __func__);

    ps_get_core_reference(&ps_core_d);
    if (unlikely((NULL == ps_core_d)||(NULL == inode)||(NULL == filp)||(NULL == ps_core_d->ps_pm)))
    {
        PS_PRINT_ERR("ps_core_d is NULL\n");
        return -EINVAL;
    }

    mutex_lock(&pm_data->host_mutex);

    pst_nfc_data = &ps_core_d->bfgx_info[BFGX_NFC];

    wake_up_interruptible(&pst_nfc_data->rx_wait);

    ret = prepare_to_visit_node(ps_core_d);
    if (ret < 0)
    {
        PS_PRINT_ERR("prepare work FAIL\n");
    }

    ret = bfgx_close_cmd_send(BFGX_NFC);
    if (ret < 0)
    {
        PS_PRINT_ERR("bfgx close cmd fail\n");
    }

    atomic_set(&pst_nfc_data->subsys_state, POWER_STATE_SHUTDOWN);
    free_seperted_rx_buf(BFGX_NFC,KZALLOC);
    ps_kfree_skb(ps_core_d, RX_NFC_QUEUE);

    if (isAsic())
    {
        ret = ps_core_d->ps_pm->bfg_power_set(BFGX_NFC, BFG_POWER_GPIO_DOWN);
        if (ret)
        {
            PS_PRINT_ERR("set nfc power off err!ret = %d\n", ret);
        }
    }

    post_to_visit_node(ps_core_d);

    mutex_unlock(&pm_data->host_mutex);

    return 0;
}

/**
 * Prototype    : hw_ir_open
 * Description  : open ir device
 * input        : struct inode *inode, struct file *filp
 * output       : return 0
 *
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2015/2/11
 *     Author       : wx222439
 *     Modification : Created function
 *
 */
STATIC int32 hw_ir_open(struct inode *inode, struct file *filp)
{
    struct ps_core_s *ps_core_d = NULL;
    struct st_bfgx_data *pst_ir_data = NULL;
    int32 error = BFGX_POWER_SUCCESS;
    struct pm_drv_data *pm_data = pm_get_drvdata();

    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return -FAILURE;
    }

    PS_PRINT_INFO("%s", __func__);

    ps_get_core_reference(&ps_core_d);
    if (unlikely((NULL == ps_core_d)||(NULL == inode)||(NULL == filp)||
        (NULL == ps_core_d->ps_pm)||(NULL == ps_core_d->ps_pm->bfg_power_set)))
    {
        PS_PRINT_ERR("ps_core_d is err\n");
        return -EINVAL;
    }

    mutex_lock(&pm_data->host_mutex);
    pst_ir_data = &ps_core_d->bfgx_info[BFGX_IR];

    if (POWER_STATE_OPEN == atomic_read(&pst_ir_data->subsys_state))
    {
        PS_PRINT_WARNING("IR has opened! It's Not necessary to send msg to device\n");
        mutex_unlock(&pm_data->host_mutex);
        return BFGX_POWER_SUCCESS;
    }

    if (BFGX_POWER_SUCCESS != alloc_seperted_rx_buf(BFGX_IR, IR_RX_MAX_FRAME,KZALLOC))
    {
        PS_PRINT_ERR("no mem to allocate to read ir!\n");
        mutex_unlock(&pm_data->host_mutex);
        return -ENOMEM;
    }

    if (isAsic())
    {
        error = ps_core_d->ps_pm->bfg_power_set(BFGX_IR, BFG_POWER_GPIO_UP);
        if (BFGX_POWER_SUCCESS != error)
        {
            PS_PRINT_ERR("set ir power on err! error = %d\n", error);
            goto bfgx_power_on_fail;
        }
    }

    if (BFGX_POWER_SUCCESS != prepare_to_visit_node(ps_core_d))
    {
        PS_PRINT_ERR("prepare work FAIL\n");
        error = BFGX_POWER_WAKEUP_FAIL;
        goto bfgx_wakeup_fail;
    }

    if (BFGX_POWER_SUCCESS != bfgx_open_cmd_send(BFGX_IR))
    {
        PS_PRINT_ERR("bfgx open cmd fail\n");
        error = BFGX_POWER_OPEN_CMD_FAIL;
        goto bfgx_open_cmd_fail;
    }

    mod_timer(&pm_data->bfg_timer, jiffies + BT_SLEEP_TIME * HZ);

    atomic_set(&pst_ir_data->subsys_state, POWER_STATE_OPEN);
    post_to_visit_node(ps_core_d);

    mutex_unlock(&pm_data->host_mutex);

    return BFGX_POWER_SUCCESS;

bfgx_open_cmd_fail:
    post_to_visit_node(ps_core_d);
bfgx_wakeup_fail:
bfgx_power_on_fail:
    free_seperted_rx_buf(BFGX_IR,KZALLOC);
    bfgx_open_fail_process(BFGX_IR, error);
    mutex_unlock(&pm_data->host_mutex);
    return BFGX_POWER_FAILED;
}

/**
 * Prototype    : hw_ir_read
 * Description  : read ir node data
 * input        : struct file *filp, int8 __user *buf, size_t count,loff_t *f_pos
 * output       : return read len
 *
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2015/2/11
 *     Author       : wx222439
 *     Modification : Created function
 *
 */
STATIC ssize_t hw_ir_read(struct file *filp, int8 __user *buf,
                                size_t count, loff_t *f_pos)
{
    uint16 ret_count;
    struct sk_buff *skb = NULL;
    struct ps_core_s *ps_core_d = NULL;

    PS_PRINT_FUNCTION_NAME;

    ps_get_core_reference(&ps_core_d);
    if (unlikely((NULL == ps_core_d)||(NULL == buf)||(NULL == filp)))
    {
        PS_PRINT_ERR("ps_core_d is NULL\n");
        return -EINVAL;
    }

    if (NULL == (skb = ps_skb_dequeue(ps_core_d, RX_IR_QUEUE)))
    {
        PS_PRINT_DBG("ir read skb queue is null!\n");
        return 0;
    }

    ret_count = min_t(size_t, skb->len, count);
    if (copy_to_user(buf, skb->data, ret_count))
    {
        PS_PRINT_ERR("copy_to_user is err!\n");
        ps_restore_skbqueue(ps_core_d, skb, RX_IR_QUEUE);
        return -EFAULT;
    }

    skb_pull(skb, ret_count);

    if (0 == skb->len)
    {
        kfree_skb(skb);
    }
    else
    {
        ps_restore_skbqueue(ps_core_d, skb, RX_IR_QUEUE);
    }

    return ret_count;
}

/**
 * Prototype    : hw_ir_write
 * Description  : write data to ir node
 * input        : struct file *filp, const int8 __user *buf, size_t count, loff_t *f_pos
 * output       : return write len
 *
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2015/2/11
 *     Author       : wx222439
 *     Modification : Created function
 *
 */
STATIC ssize_t hw_ir_write(struct file *filp, const int8 __user *buf,
                                size_t count, loff_t *f_pos)
{
    struct ps_core_s *ps_core_d = NULL;
    int32 ret = 0;

    PS_PRINT_FUNCTION_NAME;

    ps_get_core_reference(&ps_core_d);

    if (unlikely((NULL == ps_core_d)||(NULL == buf)||(NULL == filp)||(NULL == ps_core_d->ps_pm)))
    {
        PS_PRINT_ERR("ps_core_d is NULL\n");
        return -EINVAL;
    }

    if (count > IR_TX_MAX_FRAME)
    {
        PS_PRINT_ERR("IR skb len is too large!\n");
        return -EINVAL;
    }

    if (ps_core_d->tx_low_seq.qlen > TX_LOW_QUE_MAX_NUM)
    {
        return 0;
    }

    ret = prepare_to_visit_node(ps_core_d);
    if (ret < 0)
    {
        PS_PRINT_ERR("prepare work fail, bring to reset work\n");
        plat_exception_handler(SUBSYS_BFGX, THREAD_IR, BFGX_WAKEUP_FAIL);
        return ret;
    }
    /* modify expire time of uart idle timer */
    mod_timer(&ps_core_d->ps_pm->pm_priv_data->bfg_timer, jiffies + BT_SLEEP_TIME * HZ);

    /* to divide up packet function and tx to tty work */
    if (ps_tx_irbuf(ps_core_d, buf, count) < 0)
    {
        PS_PRINT_ERR("hw_ir_write is err\n");
        post_to_visit_node(ps_core_d);
        return -EFAULT;
    }

    post_to_visit_node(ps_core_d);
    PS_PRINT_DBG("IR data write end\n");

    return count;
}

/**
 * Prototype    : hw_ir_release
 * Description  : release
 * input        : struct inode *inode, struct file *filp
 * output       : return 0
 *
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2015/2/11
 *     Author       : wx222439
 *     Modification : Created function
 *
 */
STATIC int32 hw_ir_release(struct inode *inode, struct file *filp)
{
    int32 ret = 0;
    struct ps_core_s *ps_core_d = NULL;
    struct st_bfgx_data *pst_ir_data = NULL;
    struct pm_drv_data *pm_data = pm_get_drvdata();

    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return -FAILURE;
    }

    PS_PRINT_INFO("%s\n", __func__);

    ps_get_core_reference(&ps_core_d);
    if (unlikely((NULL == ps_core_d)||(NULL == inode)||(NULL == filp)||(NULL == ps_core_d->ps_pm)))
    {
        PS_PRINT_ERR("ps_core_d is NULL\n");
        return -EINVAL;
    }

    mutex_lock(&pm_data->host_mutex);

    pst_ir_data = &ps_core_d->bfgx_info[BFGX_IR];

    wake_up_interruptible(&pst_ir_data->rx_wait);

    ret = prepare_to_visit_node(ps_core_d);
    if (ret < 0)
    {
        PS_PRINT_ERR("prepare work FAIL\n");
    }

    ret = bfgx_close_cmd_send(BFGX_IR);
    if (ret < 0)
    {
        PS_PRINT_ERR("bfgx close cmd fail\n");
    }

    atomic_set(&pst_ir_data->subsys_state, POWER_STATE_SHUTDOWN);
    free_seperted_rx_buf(BFGX_IR,KZALLOC);
    ps_kfree_skb(ps_core_d, RX_IR_QUEUE);

    if (isAsic())
    {
        ret = ps_core_d->ps_pm->bfg_power_set(BFGX_IR, BFG_POWER_GPIO_DOWN);
        if (ret)
        {
            PS_PRINT_ERR("set ir power off err!ret = %d", ret);
        }
    }

    post_to_visit_node(ps_core_d);

    mutex_unlock(&pm_data->host_mutex);

    return 0;
}

/**********************************************************************/
/**
 * Prototype    : hw_fm_open
 * Description  : functions called from above fm hal,when open fm file
 *                  input : "/dev/hwfm"
 * input        : return 0 --> open is ok
 * output       : return !0--> open is false
 *
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2012/11/05
 *     Author       : wx144390
 *     Modification : Created function
 *
 */
STATIC int32 hw_fm_open(struct inode *inode, struct file *filp)
{
    struct ps_core_s *ps_core_d = NULL;
    struct st_bfgx_data *pst_fm_data = NULL;
    int32 error = BFGX_POWER_SUCCESS;
    struct pm_drv_data *pm_data = pm_get_drvdata();

    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return -FAILURE;
    }

    PS_PRINT_INFO("%s", __func__);

    ps_get_core_reference(&ps_core_d);
    if (unlikely((NULL == ps_core_d)||(NULL == inode)||(NULL == filp)||
        (NULL == ps_core_d->ps_pm)||(NULL == ps_core_d->ps_pm->bfg_power_set)))
    {
        PS_PRINT_ERR("ps_core_d is NULL\n");
        return -EINVAL;
    }

    mutex_lock(&pm_data->host_mutex);
    pst_fm_data = &ps_core_d->bfgx_info[BFGX_FM];

    if (POWER_STATE_OPEN == atomic_read(&pst_fm_data->subsys_state))
    {
        PS_PRINT_WARNING("FM has opened! It's Not necessary to send msg to device\n");
        mutex_unlock(&pm_data->host_mutex);
        return BFGX_POWER_SUCCESS;
    }

    if (BFGX_POWER_SUCCESS != alloc_seperted_rx_buf(BFGX_FM, FM_RX_MAX_FRAME,KZALLOC))
    {
        PS_PRINT_ERR("no mem to allocate to read fm!\n");
        mutex_unlock(&pm_data->host_mutex);
        return -ENOMEM;
    }

    if (isAsic())
    {
        error = ps_core_d->ps_pm->bfg_power_set(BFGX_FM, BFG_POWER_GPIO_UP);
        if (BFGX_POWER_SUCCESS != error)
        {
            PS_PRINT_ERR("set fm power on err! error = %d\n", error);
            goto bfgx_power_on_fail;
        }
    }

    if (BFGX_POWER_SUCCESS != prepare_to_visit_node(ps_core_d))
    {
        PS_PRINT_ERR("prepare work FAIL\n");
        error = BFGX_POWER_WAKEUP_FAIL;
        goto bfgx_wakeup_fail;
    }

    if (BFGX_POWER_SUCCESS != bfgx_open_cmd_send(BFGX_FM))
    {
        PS_PRINT_ERR("bfgx open cmd fail\n");
        error = BFGX_POWER_OPEN_CMD_FAIL;
        goto bfgx_open_cmd_fail;
    }

    mod_timer(&pm_data->bfg_timer, jiffies + BT_SLEEP_TIME * HZ);

    ps_core_d->fm_read_delay = FM_READ_DEFAULT_TIME;

    atomic_set(&pst_fm_data->subsys_state, POWER_STATE_OPEN);
    post_to_visit_node(ps_core_d);
    mutex_unlock(&pm_data->host_mutex);

    return BFGX_POWER_SUCCESS;

bfgx_open_cmd_fail:
    post_to_visit_node(ps_core_d);
bfgx_wakeup_fail:
bfgx_power_on_fail:
    free_seperted_rx_buf(BFGX_FM,KZALLOC);
    bfgx_open_fail_process(BFGX_FM, error);
    mutex_unlock(&pm_data->host_mutex);
    return BFGX_POWER_FAILED;
}

/**
 * Prototype    : hw_fm_read
 * Description  : functions called from above fm hal,read count data to buf
 * input        : file handle, buf, count
 * output       : return size --> actual read byte size
 *
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2012/11/05
 *     Author       : wx144390
 *     Modification : Created function
 *
 */
STATIC ssize_t hw_fm_read(struct file *filp, int8 __user *buf,
                                size_t count,loff_t *f_pos)
{
    struct ps_core_s *ps_core_d = NULL;
    struct sk_buff *skb = NULL;
    uint16 count1;
    int64 timeout;

    PS_PRINT_FUNCTION_NAME;

    ps_get_core_reference(&ps_core_d);
    if (unlikely((NULL == ps_core_d)||(NULL == buf)||(NULL == filp)))
    {
        PS_PRINT_ERR("ps_core_d is NULL\n");
        return -EINVAL;
    }

    if (0 == ps_core_d->bfgx_info[BFGX_FM].rx_queue.qlen)
    {   /* if don,t data, and wait timeout function */
        if (filp->f_flags & O_NONBLOCK)
        {   /* if O_NONBLOCK read and return */
            return -EAGAIN;
        }
        /* timeout function;when have data,can interrupt */
        timeout = wait_event_interruptible_timeout(ps_core_d->bfgx_info[BFGX_FM].rx_wait,
            (ps_core_d->bfgx_info[BFGX_FM].rx_queue.qlen > 0), msecs_to_jiffies(ps_core_d->fm_read_delay));
        if (!timeout)
        {
            PS_PRINT_DBG("fm read time out!\n");
            return -ETIMEDOUT;
        }
    }

    if (NULL == (skb = ps_skb_dequeue(ps_core_d, RX_FM_QUEUE)))
    {
        PS_PRINT_WARNING("fm read no data!\n");
        return -ETIMEDOUT;
    }

    count1 = min_t(size_t, skb->len, count);
    if (copy_to_user(buf, skb->data, count1))
    {
        PS_PRINT_ERR("copy_to_user is err!\n");
        ps_restore_skbqueue(ps_core_d, skb, RX_FM_QUEUE);
        return -EFAULT;
    }

    skb_pull(skb, count1);

    /* if skb->len == 0: curr skb read is over */
    if (0 == skb->len)
    {   /* curr skb data have read to user */
        kfree_skb(skb);
    }
    else
    {   /* if don,t read over; restore to skb queue */
        ps_restore_skbqueue(ps_core_d, skb, RX_FM_QUEUE);
    }

    return count1;
}

/**
 * Prototype    : hw_fm_write
 * Description  : functions called from above fm hal,write count data to buf
 * input        : file handle, buf, count
 * output       : return size --> actual write byte size
 *
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2012/11/05
 *     Author       : wx144390
 *     Modification : Created function
 *
 */
STATIC ssize_t hw_fm_write(struct file *filp, const int8 __user *buf,
                                size_t count,loff_t *f_pos)
{
    struct ps_core_s *ps_core_d = NULL;
    int32 ret = 0;

    PS_PRINT_FUNCTION_NAME;

    ps_get_core_reference(&ps_core_d);
    if (unlikely((NULL == ps_core_d)||(NULL == buf)||(NULL == filp)||(NULL == ps_core_d->ps_pm)))
    {
        PS_PRINT_ERR("ps_core_d is NULL\n");
        return -EINVAL;
    }

    /* if count is too large;and don,t tx */
    if (count > (FM_TX_MAX_FRAME - sizeof(struct ps_packet_head) - sizeof(struct ps_packet_end)))
    {
        PS_PRINT_ERR("err:fm packet is too large!\n");
        return -EINVAL;
    }

    /* if low queue num > MAX_NUM and don't write */
    if (ps_core_d->tx_low_seq.qlen > TX_LOW_QUE_MAX_NUM)
    {
        return 0;
    }

    ret = prepare_to_visit_node(ps_core_d);
    if (ret < 0)
    {
        PS_PRINT_ERR("prepare work fail, bring to reset work\n");
        plat_exception_handler(SUBSYS_BFGX, THREAD_FM, BFGX_WAKEUP_FAIL);
        return ret;
    }

    /* modify expire time of uart idle timer */
    mod_timer(&ps_core_d->ps_pm->pm_priv_data->bfg_timer, jiffies + BT_SLEEP_TIME * HZ);

    /* to divide up packet function and tx to tty work */
    if (ps_tx_fmbuf(ps_core_d, buf, count) < 0)
    {
        PS_PRINT_ERR("hw_fm_write is err\n");
        post_to_visit_node(ps_core_d);
        return -EFAULT;
    }

    post_to_visit_node(ps_core_d);

    PS_PRINT_DBG("FM data write end\n");

    return count;
}

/**
 * Prototype    : hw_fm_ioctl
 * Description  : called by hw func from hal when open power gpio or close power gpio
 * input        : file handle, cmd, arg
 * output       : no
 *
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2012/11/05
 *     Author       : wx144390
 *     Modification : Created function
 *
 */
STATIC int64 hw_fm_ioctl(struct file *file, uint32 cmd, uint64 arg)
{
    struct ps_core_s *ps_core_d = NULL;

    PS_PRINT_FUNCTION_NAME;

    ps_get_core_reference(&ps_core_d);
    if (unlikely((NULL == ps_core_d)||(NULL == file)))
    {
        PS_PRINT_ERR("ps_core_d is NULL\n");
        return -EINVAL;
    }

    if (FM_SET_READ_TIME == cmd)
    {
        if (arg < FM_MAX_READ_TIME)
        {   /* set timeout for fm read function */
            ps_core_d->fm_read_delay = arg;
        }
        else
        {
            PS_PRINT_ERR("arg is too large!\n");
            return -EINVAL;
        }
    }

    return 0;
}

/**
 * Prototype    : hw_fm_release
 * Description  : called by fm func from hal when close fm inode
 * input        : have opened file handle
 * output       : return 0 --> close is ok
 *                return !0--> close is false
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2012/11/05
 *     Author       : wx144390
 *     Modification : Created function
 *
 */
STATIC int32 hw_fm_release(struct inode *inode, struct file *filp)
{
    struct ps_core_s *ps_core_d = NULL;
    struct st_bfgx_data *pst_fm_data = NULL;
    int32 ret = 0;
    struct pm_drv_data *pm_data = pm_get_drvdata();

    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return -FAILURE;
    }

    PS_PRINT_INFO("%s", __func__);

    ps_get_core_reference(&ps_core_d);
    if (unlikely((NULL == ps_core_d)||(NULL == inode)||(NULL == filp)||(NULL == ps_core_d->ps_pm)))
    {
        PS_PRINT_ERR("ps_core_d is NULL\n");
        return -EINVAL;
    }

    mutex_lock(&pm_data->host_mutex);
    pst_fm_data = &ps_core_d->bfgx_info[BFGX_FM];

    wake_up_interruptible(&pst_fm_data->rx_wait);

    ret = prepare_to_visit_node(ps_core_d);
    if (ret < 0)
    {
        PS_PRINT_ERR("prepare work FAIL\n");
    }

    ret = bfgx_close_cmd_send(BFGX_FM);
    if (ret < 0)
    {
        PS_PRINT_ERR("bfgx close cmd fail\n");
    }

    atomic_set(&pst_fm_data->subsys_state, POWER_STATE_SHUTDOWN);
    free_seperted_rx_buf(BFGX_FM,KZALLOC);
    ps_kfree_skb(ps_core_d, RX_FM_QUEUE);

    if (isAsic())
    {
        ret = ps_core_d->ps_pm->bfg_power_set(BFGX_FM, BFG_POWER_GPIO_DOWN);
        if (ret != 0)
        {
            PS_PRINT_ERR("set fm power off err!ret = %d", ret);
        }
    }

    post_to_visit_node(ps_core_d);

    mutex_unlock(&pm_data->host_mutex);

    return 0;
}

/**
 * Prototype    : hw_gnss_open
 * Description  : functions called from above gnss hal,when open gnss file
 * input        : "/dev/hwgnss"
 * output       : return 0 --> open is ok
 *                return !0--> open is false
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2012/11/05
 *     Author       : wx144390
 *     Modification : Created function
 *
 */
STATIC int32 hw_gnss_open(struct inode *inode, struct file *filp)
{
    struct ps_core_s *ps_core_d = NULL;
    struct st_bfgx_data *pst_gnss_data = NULL;
    int32  error = BFGX_POWER_SUCCESS;
    struct pm_drv_data *pm_data = pm_get_drvdata();

    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return -FAILURE;
    }

    PS_PRINT_INFO("%s", __func__);

    ps_get_core_reference(&ps_core_d);

    if (unlikely((NULL == ps_core_d)||(NULL == inode)||(NULL == filp)||
        (NULL == ps_core_d->ps_pm)||(NULL == ps_core_d->ps_pm->bfg_power_set)))
    {
        PS_PRINT_ERR("ps_core_d is NULL\n");
        return -EINVAL;
    }

    mutex_lock(&pm_data->host_mutex);
    pst_gnss_data = &ps_core_d->bfgx_info[BFGX_GNSS];

    if (POWER_STATE_OPEN == atomic_read(&pst_gnss_data->subsys_state))
    {
        PS_PRINT_WARNING("GNSS has opened! It's Not necessary to send msg to device\n");
        mutex_unlock(&pm_data->host_mutex);
        return BFGX_POWER_SUCCESS;
    }

    if (BFGX_POWER_SUCCESS != alloc_seperted_rx_buf(BFGX_GNSS,GNSS_RX_MAX_FRAME,VMALLOC))
    {
        PS_PRINT_ERR("no mem to allocate to read gnss!\n");
        mutex_unlock(&pm_data->host_mutex);
        return -ENOMEM;
    }
    atomic_set(&pm_data->gnss_sleep_flag, GNSS_NOT_AGREE_SLEEP);
    if (isAsic())
    {
        error = ps_core_d->ps_pm->bfg_power_set(BFGX_GNSS, BFG_POWER_GPIO_UP);
        if (BFGX_POWER_SUCCESS != error)
        {
            PS_PRINT_ERR("set gnss power on err! error = %d\n", error);
            goto bfgx_power_on_fail;
        }
    }

    if (BFGX_POWER_SUCCESS != prepare_to_visit_node(ps_core_d))
    {
        PS_PRINT_ERR("prepare work FAIL\n");
        error = BFGX_POWER_WAKEUP_FAIL;
        goto bfgx_wakeup_fail;
    }

    if (BFGX_POWER_SUCCESS != bfgx_open_cmd_send(BFGX_GNSS))
    {
        PS_PRINT_ERR("bfgx open cmd fail\n");
        error = BFGX_POWER_OPEN_CMD_FAIL;
        goto bfgx_open_cmd_fail;
    }

    ps_core_d->gnss_read_delay = GNSS_READ_DEFAULT_TIME;

    atomic_set(&pst_gnss_data->subsys_state, POWER_STATE_OPEN);
    post_to_visit_node(ps_core_d);
    mutex_unlock(&pm_data->host_mutex);

    return BFGX_POWER_SUCCESS;

bfgx_open_cmd_fail:
    post_to_visit_node(ps_core_d);
bfgx_wakeup_fail:
bfgx_power_on_fail:
    free_seperted_rx_buf(BFGX_GNSS,VMALLOC);
    bfgx_open_fail_process(BFGX_GNSS, error);
    mutex_unlock(&pm_data->host_mutex);
    atomic_set(&pm_data->gnss_sleep_flag, GNSS_AGREE_SLEEP);
    return BFGX_POWER_FAILED;
}

/**
 * Prototype    : hw_gnss_read
 * Description  : functions called from above gnss hal,read count data to buf
 * input        : file handle, buf, count
 * output       : return size --> actual read byte size
 *
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2012/11/05
 *     Author       : wx144390
 *     Modification : Created function
 *
 */
STATIC ssize_t hw_gnss_read(struct file *filp, int8 __user *buf,
                                    size_t count,loff_t *f_pos)
{
    struct ps_core_s *ps_core_d = NULL;
    struct sk_buff *skb = NULL;
    int32 count1;
    int64 timeout;
    uint8 seperate_tag = 0;
    int32   copy_cnt = 0;

    PS_PRINT_FUNCTION_NAME;

    ps_get_core_reference(&ps_core_d);
    if (unlikely((NULL == ps_core_d)||(NULL == buf)||(NULL == filp)))
    {
        PS_PRINT_ERR("ps_core_d is NULL\n");
        return -EINVAL;
    }

    if (0 == ps_core_d->bfgx_info[BFGX_GNSS].rx_queue.qlen)
    {   /* if no data, and wait timeout function */
        if (filp->f_flags & O_NONBLOCK)
        {   /* if O_NONBLOCK read and return */
            return -EAGAIN;
        }
        /* timeout function;when have data,can interrupt */
        timeout = wait_event_interruptible_timeout(ps_core_d->bfgx_info[BFGX_GNSS].rx_wait,
            (ps_core_d->bfgx_info[BFGX_GNSS].rx_queue.qlen > 0), msecs_to_jiffies(ps_core_d->gnss_read_delay));
        if (!timeout)
        {
            PS_PRINT_DBG("gnss read time out!\n");
            return -ETIMEDOUT;
        }
    }
    spin_lock(&ps_core_d->gnss_rx_lock);
    do
    {
    /* pull skb data from skb queue */
        if (NULL == (skb = ps_skb_dequeue(ps_core_d, RX_GNSS_QUEUE)))
        {
            spin_unlock(&ps_core_d->gnss_rx_lock);
            PS_PRINT_WARNING("gnss read no data!\n");
            return copy_cnt;
        }
        if (1 >= skb->len)
        {
             PS_PRINT_ERR("Panic, tag:%x,  skb->len=%x, copy_cnt=%x, count=%x\n", seperate_tag, skb->len, copy_cnt, (uint32)count);
             goto ERR_SKB_LEN_1;
        }
        /* read min value from skb->len or count */
        seperate_tag = skb->data[skb->len -1];
        switch (seperate_tag)
        {
            case GNSS_SEPER_TAG_INIT:
            case GNSS_SEPER_TAG_LAST:
                count1 = skb->len -1;
                if (copy_cnt + count1 > count)
                {
                      goto ERR_NO_SPACE;
                }
                break;
            default:
                PS_PRINT_ERR("seperate_tag=%x not support\n", seperate_tag);
                if (0 >= count - copy_cnt)
                {
                      goto ERR_NO_SPACE;
                }
                count1 = min_t(size_t, skb->len -1, count - copy_cnt);
                seperate_tag = GNSS_SEPER_TAG_LAST;
                break;
        }

        if (copy_to_user(buf + copy_cnt, skb->data, count1))
        {
            PS_PRINT_WARNING("copy_to_user err, dest=%p, src=%p, tag:%x, count1=%x, skb->len=%x, copy_cnt=%x, read_cnt=%x\n", \
                                  buf + copy_cnt, skb->data, seperate_tag, count1,  skb->len, copy_cnt, (uint32)count);
            ps_restore_skbqueue(ps_core_d, skb, RX_GNSS_QUEUE);
            spin_unlock(&ps_core_d->gnss_rx_lock);
            return -EFAULT;
        }
        /* have read count1 byte */
        skb_pull(skb, count1);
        copy_cnt += count1;
        PS_PRINT_DBG("<=====tag:%x, count1=%x,  skb->len=%x, copy_cnt=%x, read_cnt=%x\n", seperate_tag, count1,  skb->len, copy_cnt, (uint32)count);
        if (1 >= skb->len)
        {   /* drop tag data */
            skb_pull(skb, skb->len);
            kfree_skb(skb);
        }
        else
        {   /* if don,t read over; restore to skb queue */
            ps_restore_skbqueue(ps_core_d, skb, RX_GNSS_QUEUE);
        }
    }while(GNSS_SEPER_TAG_INIT == seperate_tag);
    spin_unlock(&ps_core_d->gnss_rx_lock);

    return copy_cnt;
    ERR_SKB_LEN_1:
        skb_pull(skb, skb->len);
        kfree_skb(skb);
        spin_unlock(&ps_core_d->gnss_rx_lock);
        return copy_cnt;
   ERR_NO_SPACE:
        PS_PRINT_ERR("space is not enough, tag:%x,  skb->len=%x, copy_cnt=%x, count=%x\n", seperate_tag, skb->len, copy_cnt, (uint32)count);
        ps_restore_skbqueue(ps_core_d, skb, RX_GNSS_QUEUE);
        spin_unlock(&ps_core_d->gnss_rx_lock);
        return copy_cnt;
}

/**
 * Prototype    : hw_gnss_write
 * Description  : functions called from above gnss hal,write count data to buf
 * input        : file handle, buf, count
 * output       : return size --> actual write byte size
 *
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2012/11/05
 *     Author       : wx144390
 *     Modification : Created function
 *
 */
STATIC ssize_t hw_gnss_write(struct file *filp, const int8 __user *buf,
                                    size_t count, loff_t *f_pos)
{
    struct ps_core_s *ps_core_d = NULL;
    int32 ret = 0;
    struct pm_drv_data *pm_data = pm_get_drvdata();
    PS_PRINT_FUNCTION_NAME;

    ps_get_core_reference(&ps_core_d);
    if (unlikely((NULL == ps_core_d)||(NULL == buf)||(NULL == filp)||(NULL == ps_core_d->ps_pm) ||(NULL ==  pm_data)))
    {
        PS_PRINT_ERR("ps_core_d is NULL\n");
        return -EINVAL;
    }

    if (count > GNSS_TX_MAX_FRAME)
    {
        PS_PRINT_ERR("err:gnss packet is too large!\n");
        return -EINVAL;
    }

    /* if low queue num > MAX_NUM and don't write */
    if (ps_core_d->tx_low_seq.qlen > TX_LOW_QUE_MAX_NUM)
    {
        return 0;
    }

    atomic_set(&pm_data->gnss_sleep_flag, GNSS_NOT_AGREE_SLEEP);
    ret = prepare_to_visit_node(ps_core_d);
    if (ret < 0)
    {
        atomic_set(&pm_data->gnss_sleep_flag, GNSS_AGREE_SLEEP);
        PS_PRINT_ERR("prepare work fail, bring to reset work\n");
        plat_exception_handler(SUBSYS_BFGX, THREAD_GNSS, BFGX_WAKEUP_FAIL);
        return ret;
    }

    /* to divide up packet function and tx to tty work */
    if (ps_tx_gnssbuf(ps_core_d, buf, count) < 0)
    {
        PS_PRINT_ERR("hw_gnss_write is err\n");
        atomic_set(&pm_data->gnss_sleep_flag, GNSS_AGREE_SLEEP);
        count = -EFAULT;
    }

    post_to_visit_node(ps_core_d);

    return count;
}

/**
 * Prototype    : hw_gnss_ioctl
 * Description  : called by gnss func from hal when open power gpio or close power gpio
 * input        : file handle, cmd, arg
 * output       : no
 *
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2012/11/05
 *     Author       : wx144390
 *     Modification : Created function
 *
 */
STATIC int64 hw_gnss_ioctl(struct file *file, uint32 cmd, uint64 arg)
{
    struct ps_core_s *ps_core_d = NULL;

    PS_PRINT_FUNCTION_NAME;

    ps_get_core_reference(&ps_core_d);
    if (unlikely((NULL == ps_core_d)||(NULL == file)))
    {
        PS_PRINT_ERR("ps_core_d is NULL\n");
        return -EINVAL;
    }

    if (GNSS_SET_READ_TIME == cmd)
    {
        if (arg < GNSS_MAX_READ_TIME)
        {   /* set timeout for gnss read function */
            ps_core_d->gnss_read_delay = arg;
        }
        else
        {
            PS_PRINT_ERR("arg is too large!\n");
            return -EINVAL;
        }
    }

    return 0;
}



STATIC int64 hw_debug_ioctl(struct file *file, uint32 cmd, uint64 arg)
{
    switch (cmd)
    {
        case PLAT_DFR_CFG_CMD:
            plat_dfr_cfg_set(arg);
            break;
        case PLAT_BEATTIMER_TIMEOUT_RESET_CFG_CMD:
            plat_beatTimer_timeOut_reset_cfg_set(arg);
            break;
        default:
            PS_PRINT_WARNING("hw_debug_ioctl cmd = %d not find\n", cmd);
            return -EINVAL;
    }
    return 0;
}


/**
 * Prototype    : hw_gnss_release
 * Description  : called by gnss func from hal when close gnss inode
 * input        : have opened file handle
 * output       : return 0 --> close is ok
 *                return !0--> close is false
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2012/11/05
 *     Author       : wx144390
 *     Modification : Created function
 *
 */
STATIC int32 hw_gnss_release(struct inode *inode, struct file *filp)
{
    struct ps_core_s *ps_core_d = NULL;
    struct st_bfgx_data *pst_gnss_data = NULL;
    int32  ret = 0;
    struct pm_drv_data *pm_data = pm_get_drvdata();

    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return -FAILURE;
    }

    PS_PRINT_INFO("%s", __func__);

    ps_get_core_reference(&ps_core_d);
    if (unlikely((NULL == ps_core_d)||(NULL == inode)||(NULL == filp)||(NULL == ps_core_d->ps_pm)))
    {
        PS_PRINT_ERR("ps_core_d is NULL\n");
        return -EINVAL;
    }

    mutex_lock(&pm_data->host_mutex);

    pst_gnss_data = &ps_core_d->bfgx_info[BFGX_GNSS];

    wake_up_interruptible(&pst_gnss_data->rx_wait);

    ret = prepare_to_visit_node(ps_core_d);
    if (ret < 0)
    {
        PS_PRINT_ERR("prepare work FAIL\n");
    }

    ret = bfgx_close_cmd_send(BFGX_GNSS);
    if (ret < 0)
    {
        PS_PRINT_ERR("bfgx close cmd fail\n");
    }

    atomic_set(&pst_gnss_data->subsys_state, POWER_STATE_SHUTDOWN);
    atomic_set(&pm_data->gnss_sleep_flag, GNSS_AGREE_SLEEP);
    free_seperted_rx_buf(BFGX_GNSS,VMALLOC);
    ps_kfree_skb(ps_core_d, RX_GNSS_QUEUE);

    if (isAsic())
    {
        ret = ps_core_d->ps_pm->bfg_power_set(BFGX_GNSS, BFG_POWER_GPIO_DOWN);
        if (ret)
        {
            PS_PRINT_ERR("set gnss power off err!ret = %d", ret);
        }
    }

    post_to_visit_node(ps_core_d);

    mutex_unlock(&pm_data->host_mutex);

    return 0;
}

/**********************************************************************/
/**
 * Prototype    : hw_debug_open
 * Description  : functions called from above oam hal,when open debug file
 *                  input : "/dev/hwbfgdbg"
 * input        : return 0 --> open is ok
 * output       : return !0--> open is false
 *
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2012/11/05
 *     Author       : wx144390
 *     Modification : Created function
 *
 */
STATIC int32 hw_debug_open(struct inode *inode, struct file *filp)
{
    struct ps_core_s *ps_core_d = NULL;

    PS_PRINT_INFO("%s", __func__);

    ps_get_core_reference(&ps_core_d);
    if (unlikely((NULL == ps_core_d)||(NULL == inode)||(NULL == filp)))
    {
        PS_PRINT_ERR("ps_core_d is NULL\n");
        return -EINVAL;
    }

	g_debug_cnt++;
    PS_PRINT_INFO("%s g_debug_cnt=%d", __func__, g_debug_cnt);
    atomic_set(&ps_core_d->dbg_func_has_open, 1);

    ps_core_d->dbg_read_delay = DBG_READ_DEFAULT_TIME;

    return 0;
}

/**
 * Prototype    : hw_debug_read
 * Description  : functions called from above oam hal,read count data to buf
 * input        : file handle, buf, count
 * output       : return size --> actual read byte size
 *
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2012/11/05
 *     Author       : wx144390
 *     Modification : Created function
 *
 */
STATIC ssize_t hw_debug_read(struct file *filp, int8 __user *buf,
                                size_t count,loff_t *f_pos)
{
    struct ps_core_s *ps_core_d = NULL;
    struct sk_buff *skb = NULL;
    uint16 count1 = 0;
    int64 timeout;

    PS_PRINT_FUNCTION_NAME;

    ps_get_core_reference(&ps_core_d);
    if (unlikely((NULL == ps_core_d)||(NULL == buf)||(NULL == filp)))
    {
        PS_PRINT_ERR("ps_core_d is NULL\n");
        return -EINVAL;
    }

    if (0 == ps_core_d->rx_dbg_seq.qlen)
    {   /* if no data, and wait timeout function */
        if (filp->f_flags & O_NONBLOCK)
        {   /* if O_NONBLOCK read and return */
            return -EAGAIN;
        }

        /* timeout function;when have data,can interrupt */
        timeout = wait_event_interruptible_timeout(ps_core_d->rx_dbg_wait,
            (ps_core_d->rx_dbg_seq.qlen > 0), msecs_to_jiffies(ps_core_d->dbg_read_delay));
        if (!timeout)
        {
            PS_PRINT_DBG("debug read time out!\n");
            return -ETIMEDOUT;
        }
    }

    /* pull skb data from skb queue */
    if (NULL == (skb = ps_skb_dequeue(ps_core_d, RX_DBG_QUEUE)))
    {
        PS_PRINT_DBG("dbg read no data!\n");
        return -ETIMEDOUT;
    }
    /* read min value from skb->len or count */
    count1 = min_t(size_t, skb->len, count);
    if (copy_to_user(buf, skb->data, count1))
    {
        PS_PRINT_ERR("debug copy_to_user is err!\n");
        ps_restore_skbqueue(ps_core_d, skb, RX_DBG_QUEUE);
        return -EFAULT;
    }

    skb_pull(skb, count1);

    /* if skb->len == 0: curr skb read is over */
    if (0 == skb->len)
    {   /* curr skb data have read to user */
        kfree_skb(skb);
    }
    else
    {   /* if don,t read over; restore to skb queue */
        ps_restore_skbqueue(ps_core_d, skb, RX_DBG_QUEUE);
    }

    return count1;
}

/**
 * Prototype    : hw_debug_write
 * Description  : functions called from above oam hal,write count data to buf
 * input        : file handle, buf, count
 * output       : return size --> actual write byte size
 *
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2012/11/05
 *     Author       : wx144390
 *     Modification : Created function
 *
 */
#ifdef PLATFORM_DEBUG_ENABLE
STATIC ssize_t hw_debug_write(struct file *filp, const int8 __user *buf,
                                size_t count,loff_t *f_pos)
{
    struct ps_core_s *ps_core_d = NULL;
    struct sk_buff *skb;
    uint16 total_len;
    int32 ret = 0;

    PS_PRINT_FUNCTION_NAME;

    ps_get_core_reference(&ps_core_d);
    if (unlikely((NULL == ps_core_d)||(NULL == buf)||(NULL == filp)))
    {
        PS_PRINT_ERR("ps_core_d is NULL\n");
        return -EINVAL;
    }

    if (false == ps_core_d->tty_have_open)
    {
        PS_PRINT_ERR("err: uart not opened!\n");
        return -EFAULT;
    }

    if (count > (DBG_TX_MAX_FRAME - sizeof(struct ps_packet_head) - sizeof(struct ps_packet_end)))
    {
        PS_PRINT_ERR("err: dbg packet is too large!\n");
        return -EINVAL;
    }

    /* if low queue num > MAX_NUM and don't write */
    if (ps_core_d->tx_low_seq.qlen > TX_LOW_QUE_MAX_NUM)
    {
        return 0;
    }

    if (false == ps_chk_bfg_active(ps_core_d))
    {
        PS_PRINT_ERR("bfg is closed, /dev/hwdebug cant't write!!!\n");
        return -EINVAL;
    }

    ret = prepare_to_visit_node(ps_core_d);
    if (ret < 0)
    {
        PS_PRINT_ERR("prepare work FAIL\n");
        return ret;
    }
    /* modify expire time of uart idle timer */
    mod_timer(&ps_core_d->ps_pm->pm_priv_data->bfg_timer, jiffies + BT_SLEEP_TIME * HZ);

    total_len = count + sizeof(struct ps_packet_head) + sizeof(struct ps_packet_end);

    skb  = ps_alloc_skb(total_len);
    if (NULL == skb)
    {
        PS_PRINT_ERR("ps alloc skb mem fail\n");
        post_to_visit_node(ps_core_d);
        return -EFAULT;
    }

    if (copy_from_user(&skb->data[sizeof(struct ps_packet_head)], buf, count))
    {
        PS_PRINT_ERR("copy_from_user from dbg is err\n");
        kfree_skb(skb);
        post_to_visit_node(ps_core_d);
        return -EFAULT;
    }

    ps_add_packet_head(skb->data, OML_MSG, total_len);
    ps_skb_enqueue(ps_core_d, skb, TX_LOW_QUEUE);
    queue_work(ps_core_d->ps_tx_workqueue, &ps_core_d->tx_skb_work);

    post_to_visit_node(ps_core_d);

    return count;
}
#endif
/**
 * Prototype    : hw_debug_release
 * Description  : called by oam func from hal when close debug inode
 * input        : have opened file handle
 * output       : return 0 --> close is ok
 *                return !0--> close is false
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2012/11/05
 *     Author       : wx144390
 *     Modification : Created function
 *
 */
STATIC int32 hw_debug_release(struct inode *inode, struct file *filp)
{
    struct ps_core_s *ps_core_d = NULL;

    PS_PRINT_INFO("%s", __func__);

    ps_get_core_reference(&ps_core_d);
    if (unlikely((NULL == ps_core_d)||(NULL == inode)||(NULL == filp)))
    {
        PS_PRINT_ERR("ps_core_d is NULL\n");
        return -EINVAL;
    }

	g_debug_cnt--;
    PS_PRINT_INFO("%s g_debug_cnt=%d", __func__, g_debug_cnt);
	if (0 == g_debug_cnt)
	{
		/* wake up bt dbg wait queue */
		wake_up_interruptible(&ps_core_d->rx_dbg_wait);
		atomic_set(&ps_core_d->dbg_func_has_open, 0);

		/* kfree have rx dbg skb */
		ps_kfree_skb(ps_core_d, RX_DBG_QUEUE);
	}

    return 0;
}

uart_loop_cfg g_st_uart_loop_test_cfg = {1000, 1024, 0, 0};
uart_loop_test_struct *g_pst_uart_loop_test_info = NULL;

int32 uart_loop_set_pkt_count(uint32 count)
{
    PS_PRINT_INFO("uart loop test, set pkt count to [%d]\n", count);
    g_st_uart_loop_test_cfg.loop_count = count;

    return 0;
}

int32 uart_loop_set_pkt_len(uint32 pkt_len)
{
    PS_PRINT_INFO("uart loop test, set pkt len to [%d]\n", pkt_len);
    g_st_uart_loop_test_cfg.pkt_len = pkt_len;

    return 0;
}

int32 alloc_uart_loop_test(void)
{
    uint8 *uart_loop_tx_buf = NULL;
    uint8 *uart_loop_rx_buf = NULL;
    uint16 pkt_len = 0;

    if (NULL == g_pst_uart_loop_test_info)
    {
        g_pst_uart_loop_test_info = (uart_loop_test_struct *)kzalloc(sizeof(uart_loop_test_struct), GFP_KERNEL);
        if (NULL == g_pst_uart_loop_test_info)
        {
            PS_PRINT_ERR("malloc g_pst_uart_loop_test_info fail\n");
            goto malloc_test_info_fail;
        }

        pkt_len = g_st_uart_loop_test_cfg.pkt_len;
        if (0 == pkt_len || pkt_len > UART_LOOP_MAX_PKT_LEN)
        {
            pkt_len = UART_LOOP_MAX_PKT_LEN;
            g_st_uart_loop_test_cfg.pkt_len = UART_LOOP_MAX_PKT_LEN;
        }

        uart_loop_tx_buf = (uint8 *)kzalloc(pkt_len, GFP_KERNEL);
        if (NULL == uart_loop_tx_buf)
        {
            PS_PRINT_ERR("malloc uart_loop_tx_buf fail\n");
            goto malloc_tx_buf_fail;
        }

        uart_loop_rx_buf = (uint8 *)kzalloc(pkt_len, GFP_KERNEL);
        if (NULL == uart_loop_rx_buf)
        {
            PS_PRINT_ERR("malloc uart_loop_rx_buf fail\n");
            goto malloc_rx_buf_fail;
        }

        g_st_uart_loop_test_cfg.uart_loop_enable = 1;

        init_completion(&g_pst_uart_loop_test_info->set_done);
        init_completion(&g_pst_uart_loop_test_info->loop_test_done);

        g_pst_uart_loop_test_info->test_cfg   = &g_st_uart_loop_test_cfg;
        g_pst_uart_loop_test_info->tx_buf     = uart_loop_tx_buf;
        g_pst_uart_loop_test_info->rx_buf     = uart_loop_rx_buf;
        g_pst_uart_loop_test_info->rx_pkt_len = 0;

        PS_PRINT_INFO("uart loop test, pkt len is [%d]\n", pkt_len);
        PS_PRINT_INFO("uart loop test, loop count is [%d]\n", g_st_uart_loop_test_cfg.loop_count);
    }

    return 0;

malloc_rx_buf_fail:
    kfree(uart_loop_tx_buf);
malloc_tx_buf_fail:
    kfree(g_pst_uart_loop_test_info);
    g_pst_uart_loop_test_info = NULL;
malloc_test_info_fail:
    return -ENOMEM;
}

void free_uart_loop_test(void)
{
    if (NULL == g_pst_uart_loop_test_info)
    {
        return;
    }
    PS_PRINT_ERR("free uart loop test buf\n");
    g_st_uart_loop_test_cfg.uart_loop_enable = 0;
    kfree(g_pst_uart_loop_test_info->rx_buf);
    kfree(g_pst_uart_loop_test_info->tx_buf);
    kfree(g_pst_uart_loop_test_info);
    g_pst_uart_loop_test_info = NULL;

    return;
}

int32 uart_loop_test_open(void)
{
    struct ps_core_s *ps_core_d = NULL;
    int32  error = BFGX_POWER_SUCCESS;

    PS_PRINT_INFO("%s\n", __func__);

    ps_get_core_reference(&ps_core_d);
    if (unlikely((NULL == ps_core_d)||(NULL == ps_core_d->ps_pm)||(NULL == ps_core_d->ps_pm->bfg_power_set)))
    {
        PS_PRINT_ERR("ps_core_d is err\n");
        return -EINVAL;
    }

    if (ps_chk_bfg_active(ps_core_d))
    {
        PS_PRINT_ERR("bfgx subsys must all close\n");
        return -EINVAL;
    }

    if (BFGX_POWER_SUCCESS != alloc_uart_loop_test())
    {
        PS_PRINT_ERR("alloc mem for uart loop test fail!\n");
        goto alloc_mem_fail;
    }

    if (isAsic())
    {
        error = ps_core_d->ps_pm->bfg_power_set(BFGX_GNSS, BFG_POWER_GPIO_UP);
        if (BFGX_POWER_SUCCESS != error)
        {
            PS_PRINT_ERR("uart loop test, power on err! error = %d\n", error);
            goto power_on_fail;
        }
    }

    if (BFGX_POWER_SUCCESS != prepare_to_visit_node(ps_core_d))
    {
        PS_PRINT_ERR("uart loop test, prepare work fail\n");
        error = BFGX_POWER_WAKEUP_FAIL;
        goto wakeup_fail;
    }

    post_to_visit_node(ps_core_d);

    return BFGX_POWER_SUCCESS;

wakeup_fail:
    ps_core_d->ps_pm->bfg_power_set(BFGX_GNSS, BFG_POWER_GPIO_DOWN);
power_on_fail:
    free_uart_loop_test();
alloc_mem_fail:
    return BFGX_POWER_FAILED;
}

int32 uart_loop_test_close(void)
{
    struct ps_core_s *ps_core_d = NULL;

    PS_PRINT_INFO("%s", __func__);

    ps_get_core_reference(&ps_core_d);
    if (unlikely((NULL == ps_core_d)||(NULL == ps_core_d->ps_pm)))
    {
        PS_PRINT_ERR("ps_core_d is NULL\n");
        return -EINVAL;
    }

    if (0 != prepare_to_visit_node(ps_core_d))
    {
        PS_PRINT_ERR("uart loop test, prepare work fail\n");
    }

    if (isAsic())
    {
        if (0 != ps_core_d->ps_pm->bfg_power_set(BFGX_GNSS, BFG_POWER_GPIO_DOWN))
        {
            PS_PRINT_ERR("uart loop test, power off err!");
        }
    }

    free_uart_loop_test();

    post_to_visit_node(ps_core_d);

    return 0;
}

int32 uart_loop_test_set(uint8 flag)
{
    uint64 timeleft;
    struct ps_core_s *ps_core_d = NULL;
    uint8 cmd;

    ps_get_core_reference(&ps_core_d);
    if (unlikely(NULL == ps_core_d))
    {
        PS_PRINT_ERR("ps_core_d is null\n");
        return -EINVAL;
    }

    if (UART_LOOP_SET_DEVICE_DATA_HANDLER == flag)
    {
        cmd = SYS_CFG_SET_UART_LOOP_HANDLER;
    }
    else
    {
        cmd = SYS_CFG_SET_UART_LOOP_FINISH;
    }

    INIT_COMPLETION(g_pst_uart_loop_test_info->set_done);
    ps_uart_state_pre(ps_core_d->tty);
    ps_tx_sys_cmd(ps_core_d, SYS_MSG, cmd);
    timeleft = wait_for_completion_timeout(&g_pst_uart_loop_test_info->set_done, msecs_to_jiffies(5000));
    if (!timeleft)
    {
        ps_uart_state_dump(ps_core_d->tty);
        PS_PRINT_ERR("wait set uart loop ack timeout\n");
        return -ETIMEDOUT;
    }

    return 0;
}

int32 uart_loop_test_send_data(struct ps_core_s *ps_core_d, uint8 *buf, size_t count)
{
    struct sk_buff *skb;
    uint16 tx_skb_len;
    uint16 tx_gnss_len;
    uint8  start = 0;

    PS_PRINT_FUNCTION_NAME;

    if (unlikely(NULL == ps_core_d))
    {
        PS_PRINT_ERR("ps_core_d is NULL\n");
        return -EINVAL;
    }

    while(count > 0)
    {
        if (count > GNSS_TX_PACKET_LIMIT)
        {
            tx_gnss_len = GNSS_TX_PACKET_LIMIT;
        }
        else
        {
            tx_gnss_len = count;
        }
        /* curr tx skb total lenth */
        tx_skb_len = tx_gnss_len + sizeof(struct ps_packet_head);
        tx_skb_len = tx_skb_len + sizeof(struct ps_packet_end);

        skb  = ps_alloc_skb(tx_skb_len);
        if (NULL == skb)
        {
            PS_PRINT_ERR("ps alloc skb mem fail\n");
            return -EFAULT;
        }

        if (count > GNSS_TX_PACKET_LIMIT)
        {
            if (false == start)
            {   /* this is a start gnss packet */
                ps_add_packet_head(skb->data, GNSS_First_MSG, tx_skb_len);
                start = true;
            }
            else
            {   /* this is a int gnss packet */
                ps_add_packet_head(skb->data, GNSS_Common_MSG, tx_skb_len);
            }
        }
        else
        {   /* this is the last gnss packet */
            ps_add_packet_head(skb->data, GNSS_Last_MSG, tx_skb_len);
        }

        memcpy(&skb->data[sizeof(struct ps_packet_head)], buf, tx_gnss_len);

        /* push the skb to skb queue */
        ps_skb_enqueue(ps_core_d, skb, TX_LOW_QUEUE);
        queue_work(ps_core_d->ps_tx_workqueue, &ps_core_d->tx_skb_work);

        buf   = buf + tx_gnss_len;
        count = count - tx_gnss_len;
    }

    return 0;
}


int32 uart_loop_test_send_pkt(void)
{
    uint64 timeleft;
    struct ps_core_s *ps_core_d = NULL;

    ps_get_core_reference(&ps_core_d);
    if (unlikely((NULL == ps_core_d)||(NULL == g_pst_uart_loop_test_info)||(NULL == g_pst_uart_loop_test_info->tx_buf)))
    {
        PS_PRINT_ERR("para is invalided\n");
        return -EFAULT;
    }

    /* if low queue num > MAX_NUM and don't write */
    if (ps_core_d->tx_low_seq.qlen > TX_LOW_QUE_MAX_NUM)
    {
        PS_PRINT_ERR("uart loop test, tx low seq is too large [%d]\n", ps_core_d->tx_low_seq.qlen);
        return 0;
    }

    if (prepare_to_visit_node(ps_core_d) < 0)
    {
        PS_PRINT_ERR("prepare work fail\n");
        return -EFAULT;
    }

    INIT_COMPLETION(g_pst_uart_loop_test_info->loop_test_done);

    /* to divide up packet function and tx to tty work */
    if (uart_loop_test_send_data(ps_core_d, g_pst_uart_loop_test_info->tx_buf, g_st_uart_loop_test_cfg.pkt_len) < 0)
    {
        PS_PRINT_ERR("uart loop test pkt send is err\n");
        post_to_visit_node(ps_core_d);
        return -EFAULT;
    }

    timeleft = wait_for_completion_timeout(&g_pst_uart_loop_test_info->loop_test_done, msecs_to_jiffies(5000));
    if (!timeleft)
    {
        ps_uart_state_dump(ps_core_d->tty);
        PS_PRINT_ERR("wait uart loop done timeout\n");
        post_to_visit_node(ps_core_d);
        return -ETIMEDOUT;
    }

    post_to_visit_node(ps_core_d);

    return 0;
}

int32 uart_loop_test_recv_pkt(struct ps_core_s *ps_core_d, const uint8 *buf_ptr, uint16 pkt_len)
{
    uint16  expect_pkt_len;
    uint8 * rx_buf;
    uint16  recvd_len;

    if (unlikely((NULL == ps_core_d)||(NULL == g_pst_uart_loop_test_info)))
    {
        PS_PRINT_ERR("ps_core_d is NULL\n");
        return -EINVAL;
    }

    expect_pkt_len = g_pst_uart_loop_test_info->test_cfg->pkt_len;
    rx_buf         = g_pst_uart_loop_test_info->rx_buf;
    recvd_len      = g_pst_uart_loop_test_info->rx_pkt_len;

    if (recvd_len + pkt_len <= expect_pkt_len)
    {
        memcpy(&rx_buf[recvd_len], buf_ptr, pkt_len);
        g_pst_uart_loop_test_info->rx_pkt_len += pkt_len;
    }
    else
    {
        PS_PRINT_ERR("pkt len err! pkt_len=[%d], recvd_len=[%d], max len=[%d]\n", pkt_len, recvd_len, expect_pkt_len);
    }

    if (expect_pkt_len == g_pst_uart_loop_test_info->rx_pkt_len)
    {
        PS_PRINT_DBG("uart loop recv pkt succ\n");
        g_pst_uart_loop_test_info->rx_pkt_len = 0;
        complete(&g_pst_uart_loop_test_info->loop_test_done);
    }

    return 0;
}

int32 uart_loop_test(void)
{
    uint32 i, count;
    uint16 pkt_len;
    unsigned long long tx_total_len = 0, total_time, throughout, effect;
    ktime_t start_time, end_time, trans_time;

    if (uart_loop_test_open() < 0)
    {
        goto open_fail;
    }

    if (uart_loop_test_set(UART_LOOP_SET_DEVICE_DATA_HANDLER) < 0)
    {
        goto test_set_fail;
    }

    count   = g_pst_uart_loop_test_info->test_cfg->loop_count;
    pkt_len = g_pst_uart_loop_test_info->test_cfg->pkt_len;
    tx_total_len = ((unsigned long long)count) * ((unsigned long long)pkt_len);

    start_time = ktime_get();

    for (i = 0; i < count; i++)
    {
        if (SUCCESS != uart_loop_test_send_pkt())
        {
            PS_PRINT_ERR("uart loop test fail, i=[%d]\n", i);
            goto send_pkt_fail;
        }
    }

    end_time = ktime_get();

    if (uart_loop_test_set(UART_LOOP_RESUME_DEVICE_DATA_HANDLER) < 0)
    {
        PS_PRINT_ERR("uart loop test, resume device data handler failer\n");
    }

    uart_loop_test_close();

    trans_time = ktime_sub(end_time, start_time);
    total_time = (unsigned long long)ktime_to_us(trans_time);
    throughout = tx_total_len*1000000*10*2;
    do_div(throughout, total_time);
    effect = throughout;
    do_div(throughout, 8192);
    do_div(effect, (DEFAULT_BAUD_RATE/100));

    PS_PRINT_INFO("[UART Test] pkt count      [%d] pkts sent\n", count);
    PS_PRINT_INFO("[UART Test] pkt len        [%d] is pkt len\n", pkt_len);
    PS_PRINT_INFO("[UART Test] data lenth     [%llu]\n", tx_total_len*2);
    PS_PRINT_INFO("[UART Test] used time      [%llu] us\n", total_time);
    PS_PRINT_INFO("[UART Test] throughout     [%llu] KBps\n", throughout);
    PS_PRINT_INFO("[UART Test] effect         [%llu]%%\n", effect);

    return SUCCESS;

send_pkt_fail:
test_set_fail:
    uart_loop_test_close();
open_fail:
    return -FAILURE;
}

int conn_test_uart_loop(char *param)
{
    return uart_loop_test();
}
EXPORT_SYMBOL(conn_test_uart_loop);

/**********************************************************************/
STATIC const struct file_operations hw_bt_fops = {
        .owner          = THIS_MODULE,
        .open           = hw_bt_open,
        .write          = hw_bt_write,
        .read           = hw_bt_read,
        .poll           = hw_bt_poll,
        .unlocked_ioctl = hw_bt_ioctl,
        .release        = hw_bt_release,
};

STATIC const struct file_operations hw_fm_fops = {
        .owner          = THIS_MODULE,
        .open           = hw_fm_open,
        .write          = hw_fm_write,
        .read           = hw_fm_read,
        .unlocked_ioctl = hw_fm_ioctl,
        .release        = hw_fm_release,
};

STATIC const struct file_operations hw_gnss_fops = {
        .owner          = THIS_MODULE,
        .open           = hw_gnss_open,
        .write          = hw_gnss_write,
        .read           = hw_gnss_read,
        .unlocked_ioctl = hw_gnss_ioctl,
        .release        = hw_gnss_release,
};

static const struct file_operations hw_ir_fops = {
        .owner          = THIS_MODULE,
        .open           = hw_ir_open,
        .write          = hw_ir_write,
        .read           = hw_ir_read,
        .release        = hw_ir_release,
};


static const struct file_operations hw_nfc_fops = {
        .owner          = THIS_MODULE,
        .open           = hw_nfc_open,
        .write          = hw_nfc_write,
        .read           = hw_nfc_read,
        .poll           = hw_nfc_poll,
        .release        = hw_nfc_release,
};

STATIC const struct file_operations hw_debug_fops = {
        .owner          = THIS_MODULE,
        .open           = hw_debug_open,
#ifdef PLATFORM_DEBUG_ENABLE
        .write          = hw_debug_write,
#endif
        .read           = hw_debug_read,
        .unlocked_ioctl = hw_debug_ioctl,
        .release        = hw_debug_release,
};

STATIC struct miscdevice hw_bt_device = {
        .minor  = MISC_DYNAMIC_MINOR,
        .name   = "hwbt",
        .fops   = &hw_bt_fops,
};

STATIC struct miscdevice hw_fm_device = {
        .minor  = MISC_DYNAMIC_MINOR,
        .name   = "hwfm",
        .fops   = &hw_fm_fops,
};

STATIC struct miscdevice hw_gnss_device = {
        .minor  = MISC_DYNAMIC_MINOR,
        .name   = "hwgnss",
        .fops   = &hw_gnss_fops,
};

#ifdef HAVE_HISI_IR
STATIC struct miscdevice hw_ir_device = {
        .minor  = MISC_DYNAMIC_MINOR,
        .name   = "hwir",
        .fops   = &hw_ir_fops,
};
#endif

#ifdef HAVE_HISI_NFC
STATIC struct miscdevice hw_nfc_device = {
        .minor  = MISC_DYNAMIC_MINOR,
        .name   = "hwnfc",
        .fops   = &hw_nfc_fops,
};
#endif

STATIC struct miscdevice hw_debug_device = {
        .minor  = MISC_DYNAMIC_MINOR,
        .name   = "hwbfgdbg",
        .fops   = &hw_debug_fops,
};

static struct  hw_ps_plat_data   hisi_platform_data = {
    .dev_name           = "/dev/ttyAMA3",
    .flow_cntrl         = FLOW_CTRL_ENABLE,
    .baud_rate          = DEFAULT_BAUD_RATE,
    .suspend            = NULL,
    .resume             = NULL,
    .set_bt_power       = NULL,
    .set_fm_power       = NULL,
    .set_gnss_power     = NULL,
    .clear_bt_power     = NULL,
    .clear_fm_power     = NULL,
    .clear_gnss_power   = NULL,
};

STATIC int32 ps_probe(struct platform_device *pdev)
{
    struct hw_ps_plat_data *pdata = NULL;
    struct ps_plat_s *ps_plat_d;
    int32  err;
	struct device_node *np;
	const char * pdev_name;

    PS_PRINT_FUNCTION_NAME;

	np = of_find_compatible_node(NULL, NULL,DTS_COMP_HI1101_PS_NAME);	// should be the same as dts node compatible property
	if (NULL == np)
	{
		PS_PRINT_ERR("Unable to find %s\n",DTS_COMP_HI1101_PS_NAME);
		return -ENOENT;
	}

	if (of_property_read_string(np, "hi1102,uart_port", &pdev_name))
	{
		PS_PRINT_ERR("%s node doesn't have uart-dev property!\n", np->name);
		return -ENOENT;
	}

	strncpy(hisi_platform_data.dev_name, pdev_name, strlen(pdev_name));
	PS_PRINT_INFO("%s node have uart-dev property = %s \n", np->name, hisi_platform_data.dev_name);

	pdev->dev.platform_data = &hisi_platform_data;
	pdata = &hisi_platform_data;

    hw_ps_device = pdev;

    ps_plat_d = kzalloc(sizeof(struct ps_plat_s), GFP_KERNEL);
    if (NULL == ps_plat_d)
    {
        PS_PRINT_ERR("no mem to allocate\n");
        return -ENOMEM;
    }
    dev_set_drvdata(&pdev->dev, ps_plat_d);

    err = ps_core_init(&ps_plat_d->core_data);
    if (0 != err)
    {
        PS_PRINT_ERR(" PS core init failed\n");
        goto err_core_init;
    }

    /* refer to itself */
    ps_plat_d->core_data->pm_data = ps_plat_d;
    /* get reference of pdev */
    ps_plat_d->pm_pdev = pdev;

    init_completion(&ps_plat_d->ldisc_uninstalled);
    init_completion(&ps_plat_d->ldisc_installed);
    init_completion(&ps_plat_d->ldisc_reconfiged);

    err = plat_bfgx_exception_rst_register(ps_plat_d);
    if (0 > err)
    {
        PS_PRINT_ERR("bfgx_exception_rst_register failed\n");
        goto err_exception_rst_reg;
    }

    err = bfgx_user_ctrl_init();
    if (0 > err)
    {
        PS_PRINT_ERR("bfgx_user_ctrl_init failed\n");
        goto err_user_ctrl_init;
    }

    /* copying platform data */
    strncpy(ps_plat_d->dev_name, pdata->dev_name, HISI_UART_DEV_NAME_LEN - 1);
    ps_plat_d->flow_cntrl = pdata->flow_cntrl;
    ps_plat_d->baud_rate  = pdata->baud_rate;
    PS_PRINT_INFO("sysfs entries created\n");

    tty_recv = ps_core_recv;

    err = misc_register(&hw_bt_device);
    if (0 != err)
    {
        PS_PRINT_ERR("Failed to register bt inode\n ");
        goto err_register_bt;
    }

    err = misc_register(&hw_fm_device);
    if (0 != err)
    {
        PS_PRINT_ERR("Failed to register fm inode\n ");
        goto err_register_fm;
    }

    err = misc_register(&hw_gnss_device);
    if (0 != err)
    {
        PS_PRINT_ERR("Failed to register gnss inode\n ");
        goto err_register_gnss;
    }

    err = misc_register(&hw_debug_device);
    if (0 != err)
    {
        PS_PRINT_ERR("Failed to register debug inode\n");
        goto err_register_debug;
    }

#ifdef HAVE_HISI_IR
    err = misc_register(&hw_ir_device);
    if (0 != err)
    {
        PS_PRINT_ERR("Failed to register ir inode\n");
        goto err_register_ir;
    }
#endif

#ifdef HAVE_HISI_NFC
    err = misc_register(&hw_nfc_device);
    if (0 != err)
    {
        PS_PRINT_ERR("Failed to register nfc inode\n ");
        goto err_register_nfc;
    }
#endif

    PS_PRINT_SUC("%s is success!\n", __func__);

    return 0;

#ifdef HAVE_HISI_NFC
    err_register_nfc:
#endif
#ifdef HAVE_HISI_IR
        misc_deregister(&hw_ir_device);
    err_register_ir:
#endif
        misc_deregister(&hw_debug_device);
    err_register_debug:
        misc_deregister(&hw_gnss_device);
    err_register_gnss:
        misc_deregister(&hw_fm_device);
    err_register_fm:
        misc_deregister(&hw_bt_device);
    err_register_bt:
        bfgx_user_ctrl_exit();
    err_user_ctrl_init:
    err_exception_rst_reg:
        ps_core_exit(ps_plat_d->core_data);
    err_core_init:
    	kfree(ps_plat_d);

        return -EFAULT;
}

/**
 * Prototype    : ps_suspend
 * Description  : called by kernel when kernel goto suspend
 * input        : pdev, state
 * output       : return 0 --> ps_suspend is ok
 *                return !0--> ps_suspend is false
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2012/11/05
 *     Author       : wx144390
 *     Modification : Created function
 *
 */
int32 ps_suspend(struct platform_device *pdev, pm_message_t state)
{
#if 0
    struct hw_ps_plat_data  *pdata = pdev->dev.platform_data;
    if (pdata->suspend)
    {
        return pdata->suspend(pdev, state);
    }

    return -EOPNOTSUPP;
#else
    return 0;
#endif
}

/**
 * Prototype    : ps_resume
 * Description  : called by kernel when kernel resume from suspend
 * input        : pdev
 * output       : return 0 --> ps_suspend is ok
 *                return !0--> ps_suspend is false
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2012/11/05
 *     Author       : wx144390
 *     Modification : Created function
 *
 */
int32 ps_resume(struct platform_device *pdev)
{
#if 0
    struct hw_ps_plat_data  *pdata = pdev->dev.platform_data;
    if (pdata->resume)
    {
        return pdata->resume(pdev);
    }

    return -EOPNOTSUPP;
#else
    return 0;
#endif
}
/**
 * Prototype    : ps_remove
 * Description  : called when user applation rmmod driver
 * input        : pdev
 * output       : return 0 --> ps_suspend is ok
 *                return !0--> ps_suspend is false
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2012/11/05
 *     Author       : wx144390
 *     Modification : Created function
 *
 */
STATIC int32 ps_remove(struct platform_device *pdev)
{
    struct ps_plat_s *ps_plat_d;
    struct hw_ps_plat_data *pdata;

    PS_PRINT_FUNCTION_NAME;

    pdata = pdev->dev.platform_data;
    ps_plat_d = dev_get_drvdata(&pdev->dev);
    if (NULL == ps_plat_d)
    {
        PS_PRINT_ERR("ps_plat_d is null\n");
    }

    bfgx_user_ctrl_exit();
    PS_PRINT_INFO("sysfs user ctrl removed\n");

    if (NULL != ps_plat_d)
    {
        ps_plat_d->pm_pdev = NULL;
        ps_core_exit(ps_plat_d->core_data);
    }

    misc_deregister(&hw_bt_device);
    PS_PRINT_INFO("misc bt device have removed\n");
    misc_deregister(&hw_fm_device);
    PS_PRINT_INFO("misc fm device have removed\n");
    misc_deregister(&hw_gnss_device);
    PS_PRINT_INFO("misc gnss device have removed\n");
    misc_deregister(&hw_debug_device);
    PS_PRINT_INFO("misc debug device have removed\n");
#ifdef HAVE_HISI_IR
    misc_deregister(&hw_ir_device);
    PS_PRINT_INFO("misc ir have removed\n");
#endif
#ifdef HAVE_HISI_NFC
    misc_deregister(&hw_nfc_device);
    PS_PRINT_INFO("misc nfc have removed\n");
#endif

    if (NULL != ps_plat_d)
    {
        kfree(ps_plat_d);
        ps_plat_d = NULL;
    }

    return 0;
}
#ifdef _PRE_CONFIG_USE_DTS
static struct of_device_id hi1101_ps_match_table[] = {
	{
		.compatible = DTS_COMP_HI1101_PS_NAME,
		.data = NULL,
    },
	{ },
};
#endif

/**********************************************************/
/*  platform_driver struct for PS module */
STATIC struct platform_driver ps_platform_driver = {
        .probe      = ps_probe,
        .remove     = ps_remove,
        .suspend    = ps_suspend,
        .resume     = ps_resume,
        .driver     = {
            .name   = "hisi_bfgx",
            .owner  = THIS_MODULE,
#ifdef _PRE_CONFIG_USE_DTS
			.of_match_table	= hi1101_ps_match_table,
#endif
        },
};

int32 hw_ps_init(void)
{
    int32 ret;

    PS_PRINT_FUNCTION_NAME;

    ret = platform_driver_register(&ps_platform_driver);
    if (ret)
    {
        PS_PRINT_ERR("Unable to register platform bfgx driver.\n");
    }
    return ret;
}

void hw_ps_exit(void)
{
    platform_driver_unregister(&ps_platform_driver);
}

MODULE_DESCRIPTION("Public serial Driver for huawei BT/FM/GNSS chips");
MODULE_LICENSE("GPL");

