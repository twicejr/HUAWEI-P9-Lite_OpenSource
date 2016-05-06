

/*****************************************************************************
  1 Header File Including
*****************************************************************************/
#include <linux/module.h>   /* kernel module definitions */
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/ktime.h>
#include <linux/timer.h>
#include <linux/platform_device.h>
#include <linux/kobject.h>
#include <linux/irq.h>
#include <linux/wakelock.h>
#include <linux/mmc/sdio.h>
#include <linux/mmc/host.h>
#include <linux/mmc/card.h>
#include <linux/mmc/sdio_func.h>
#include <linux/mmc/sdio_ids.h>
#include <linux/mmc/sdio_func.h>
#include <linux/mmc/host.h>
#include <linux/gpio.h>
#include <linux/tty.h>
#include <linux/notifier.h>
#include <linux/suspend.h>

#include "board.h"
#include "hw_bfg_ps.h"
#include "plat_type.h"
#include "plat_debug.h"
#include "plat_sdio.h"
#include "plat_uart.h"
#include "plat_firmware.h"
#include "plat_pm.h"
#include "plat_pm_user_ctrl.h"
#include "bfgx_low_power.h"
#include "plat_exception_rst.h"

#include "oal_sdio.h"
#include "oal_sdio_comm.h"
#include "oal_sdio_host_if.h"
#include "oal_hcc_host_if.h"
#include "oal_schedule.h"

/*****************************************************************************
  2 Global Variable Definition
*****************************************************************************/
/*
  * Function: suspend_notify
  * Description: suspend notify call back
  * Ruturn: 0 -- success
 **/
static int pf_suspend_notify(struct notifier_block *notify_block,
                unsigned long mode, void *unused)
{

    struct pm_drv_data *pm_data = pm_get_drvdata();
    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return IRQ_NONE;
    }

    switch (mode) {
        case PM_POST_SUSPEND:
            PS_PRINT_INFO("host resume OK!\n");
            break;
        case PM_SUSPEND_PREPARE:
            PS_PRINT_INFO("host suspend now!\n");
            break;
        default:
            break;
    }
    return 0;
}

static struct notifier_block pf_suspend_notifier = {
        .notifier_call = pf_suspend_notify,
        .priority = INT_MIN,
    };

/*judge whether the wake lock is active or not*/
extern int wake_lock_active(struct wake_lock *lock);

struct pm_drv_data * pm_drv_data_t = NULL;

struct pm_drv_data * pm_get_drvdata(void)
{
	return pm_drv_data_t;
}

static void pm_set_drvdata(struct pm_drv_data * data)
{
	pm_drv_data_t = data;
}


/*****************************************************************************
  3 Function Definition
*****************************************************************************/
int32 sdio_dev_init(struct sdio_func *func)
{
    int32 ret;
    struct pm_drv_data * pm_data = NULL;

    sdio_claim_host(func);

    func->enable_timeout = 1000;

    ret = sdio_enable_func(func);
    if (ret < 0)
    {
        PS_PRINT_ERR("failed to enable sdio function! ret=%d\n", ret);
    }

    ret = sdio_set_block_size(func, HISDIO_BLOCK_SIZE);
    if (ret < 0)
    {
        PS_PRINT_ERR("failed to set sdio blk size! ret=%d\n", ret);
    }

    /* before enable sdio function 1, clear its interrupt flag, no matter it exist or not */
    oal_sdio_writeb(func, HISDIO_FUNC1_INT_MASK, HISDIO_REG_FUNC1_INT_STATUS, &ret);
    if (ret < 0)
    {
        PS_PRINT_ERR("failed to clear sdio interrupt! ret=%d\n", ret);
    }

    /*
     * enable four interrupt sources in function 1:
     *      data ready for host to read
     *      read data error
     *      message from arm is available
     *      device has receive message from host
     * */
    oal_sdio_writeb(func, HISDIO_FUNC1_INT_MASK, HISDIO_REG_FUNC1_INT_ENABLE, &ret);
    if (ret < 0)
    {
        PS_PRINT_ERR("failed to enable sdio interrupt! ret=%d\n", ret);
    }
    pm_data = pm_get_drvdata();
    oal_enable_sdio_state(pm_data->pst_wlan_pm_info->pst_sdio, OAL_SDIO_ALL);
    sdio_release_host(func);

    PS_PRINT_INFO("sdio function %d enabled.\n", func->num);

    return ret;
}

int32 sdio_reinit(void)
{
    int32 ret = 0;
    struct pm_drv_data *pm_data = pm_get_drvdata();
    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return -FAILURE;
    }

    PS_PRINT_INFO("start to power restore sdio\n");
    ret = mmc_power_save_host(pm_data->pst_wlan_pm_info->pst_sdio->func->card->host);
    pm_data->pst_wlan_pm_info->pst_sdio->func->card->host->pm_flags &= ~MMC_PM_KEEP_POWER;
    ret = mmc_power_restore_host(pm_data->pst_wlan_pm_info->pst_sdio->func->card->host);
    pm_data->pst_wlan_pm_info->pst_sdio->func->card->host->pm_flags |= MMC_PM_KEEP_POWER;
    if(ret < 0)
    {
        PS_PRINT_ERR("failed to mmc_power_restore_host\n");
    }

    if (sdio_dev_init(pm_data->pst_wlan_pm_info->pst_sdio->func) != SUCCESS)
    {
        PS_PRINT_ERR("sdio dev reinit failed\n");
        return -FAILURE;
    }

    PS_PRINT_INFO("sdio_dev_init ok\n");

    return SUCCESS;
}


int32 check_bfg_state(void)
{
    struct pm_drv_data *pm_data = pm_get_drvdata();
    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return -FAILURE;
    }

    return pm_data->bfgx_dev_state;
}

STATIC void host_allow_devslp_in_node(struct ps_core_s *ps_core_d)
{
    /* make "host_allow_bfg_sleep()" happy */
    atomic_dec(&ps_core_d->node_visit_flag);
    host_allow_bfg_sleep(ps_core_d);
    /* recovery the original value */
    atomic_inc(&ps_core_d->node_visit_flag);
}

void bfgx_state_set(uint8 on)
{
    struct pm_drv_data *pm_data = pm_get_drvdata();
    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return;
    }

    pm_data->bfgx_dev_state = on;
}

int32 bfgx_state_get(void)
{
    return check_bfg_state();
}

STATIC void bfgx_uart_state_set(uint8 uart_state)
{
    struct pm_drv_data *pm_data = pm_get_drvdata();
    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return;
    }

    pm_data->uart_ready = uart_state;
}

STATIC int8 bfgx_uart_state_get(void)
{
    struct pm_drv_data *pm_data = pm_get_drvdata();
    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return -1;
    }

    return pm_data->uart_ready;
}

int32 bfgx_pm_feature_set(void)
{
    struct ps_core_s *ps_core_d = NULL;
    struct pm_drv_data *pm_data = pm_get_drvdata();
    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return -FAILURE;
    }

    ps_get_core_reference(&ps_core_d);
    if (NULL == ps_core_d)
    {
        PS_PRINT_ERR("ps_core_d is NULL\n");
        return -FAILURE;
    }

    if (BFGX_PM_DISABLE == pm_data->bfgx_pm_ctrl_enable)
    {
        PS_PRINT_INFO("bfgx platform pm ctrl disable\n");
        msleep(50);
        return SUCCESS;
    }

    if (BFGX_PM_ENABLE == pm_data->bfgx_lowpower_enable)
    {
        PS_PRINT_INFO("bfgx platform pm enable\n");
        ps_tx_sys_cmd(ps_core_d, SYS_MSG, SYS_CFG_PL_ENABLE_PM);
    }
    else
    {
        PS_PRINT_INFO("bfgx platform pm disable\n");
        ps_tx_sys_cmd(ps_core_d, SYS_MSG, SYS_CFG_PL_DISABLE_PM);
    }

    if (BFGX_PM_ENABLE == pm_data->bfgx_bt_lowpower_enable)
    {
        PS_PRINT_INFO("bfgx bt pm enable\n");
        ps_tx_sys_cmd(ps_core_d, SYS_MSG, SYS_CFG_BT_ENABLE_PM);
    }
    else
    {
        PS_PRINT_INFO("bfgx bt pm disable\n");
        ps_tx_sys_cmd(ps_core_d, SYS_MSG, SYS_CFG_BT_DISABLE_PM);
    }

    if (BFGX_PM_ENABLE == pm_data->bfgx_gnss_lowpower_enable)
    {
        PS_PRINT_INFO("bfgx gnss pm enable\n");
        ps_tx_sys_cmd(ps_core_d, SYS_MSG, SYS_CFG_GNSS_ENABLE_PM);
    }
    else
    {
        PS_PRINT_INFO("bfgx gnss pm disable\n");
        ps_tx_sys_cmd(ps_core_d, SYS_MSG, SYS_CFG_GNSS_DISABLE_PM);
    }

    if (BFGX_PM_ENABLE == pm_data->bfgx_nfc_lowpower_enable)
    {
        PS_PRINT_INFO("bfgx nfc pm enable\n");
        ps_tx_sys_cmd(ps_core_d, SYS_MSG, SYS_CFG_NFC_ENABLE_PM);
    }
    else
    {
        PS_PRINT_INFO("bfgx nfc pm disable\n");
        ps_tx_sys_cmd(ps_core_d, SYS_MSG, SYS_CFG_NFC_DISABLE_PM);
    }

    msleep(20);

    return SUCCESS;
}


void bfg_wake_lock(void)
{
    struct pm_drv_data *pm_data = pm_get_drvdata();
    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return;
    }

    if (0 == wake_lock_active(&pm_data->bfg_wake_lock))
    {
        wake_lock(&pm_data->bfg_wake_lock);
    }

}

void bfg_wake_unlock(void)
{
    struct pm_drv_data *pm_data = pm_get_drvdata();
    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return;
    }

    /* 这里不判断其是否active也可以，因为unlock函数内部也会判断，为封装统一，还是加着 */
    if (wake_lock_active(&pm_data->bfg_wake_lock))
    {
        wake_unlock(&pm_data->bfg_wake_lock);
    }
}


void host_wkup_dev_work(struct work_struct *work)
{
#define RETRY_TIMES (3)
    int i = 0;
    uint8 zero_num = 0;
    int bwkup_gpio_val = 0;
    uint64 timeleft;
    int ret = 0;
    struct ps_core_s *ps_core_d = NULL;

	struct pm_drv_data *pm_data = pm_get_drvdata();
    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return ;
    }

    PS_PRINT_INFO("%s\n", __func__);

    ps_get_core_reference(&ps_core_d);

    /* if B send work item of wkup_dev before A's work item finished, then
     * B should not do actual wkup operation.
     */
    if (BFGX_ACTIVE == bfgx_state_get())
    {
        if (waitqueue_active(&pm_data->host_wkup_dev_comp.wait))
        {
            PS_PRINT_INFO("it seems like dev ack with NoSleep\n");
            complete_all(&pm_data->host_wkup_dev_comp);
        }
        else /* 目前用了一把host_mutex大锁，这种case不应存在，但低功耗模块不应依赖外部 */
        {
            PS_PRINT_DBG("B do wkup_dev work item after A do it but not finished\n");
        }
        return;
    }

    /* prepare to wake up device */
    ps_uart_state_pre(ps_core_d->tty);
    timeleft = wait_for_completion_timeout(&pm_data->dev_ack_comp, msecs_to_jiffies(WAIT_DEVACK_TIMEOUT_MSEC));
    if (!timeleft)
    {
        ps_uart_state_dump(ps_core_d->tty);
        PS_PRINT_ERR("wait dev allow slp ack timeout\n");
        DECLARE_DFT_TRACE_KEY_INFO("wait dev allow slp ack timeout",OAL_DFT_TRACE_FAIL);
        return;
    }
    /* device doesn't agree to slp */
    if (BFGX_ACTIVE == bfgx_state_get())
    {
        complete_all(&pm_data->host_wkup_dev_comp);
        PS_PRINT_DBG("we know dev ack with NoSleep\n");
        return;
    }

    /* begin to wake up device via uart rxd */
    for (i = 0; i < RETRY_TIMES; i++)
    {
        ret = ps_change_uart_baud_rate(WKUP_DEV_BAUD_RATE, FLOW_CTRL_DISABLE);
        if (0 != ret)
        {
            PS_PRINT_ERR("It is bad!!!, change uart rate fail, try again\n");
            DECLARE_DFT_TRACE_KEY_INFO("change uart rate fail",OAL_DFT_TRACE_FAIL);
            continue;
        }

        do
        {
            ps_write_tty(ps_core_d, &zero_num, sizeof(uint8));
            msleep(100);

            if (BFGX_ACTIVE == ps_core_d->ps_pm->bfgx_dev_state_get())
            {
                bwkup_gpio_val = board_get_bwkup_gpio_val();
                PS_PRINT_INFO("bfg wkup OK, gpio level:%d\n", bwkup_gpio_val);
                ret = ps_change_uart_baud_rate(DEFAULT_BAUD_RATE, FLOW_CTRL_ENABLE);
                if (0 != ret)
                {
                    PS_PRINT_ERR("It is bad!!!, change uart rate fail\n");
                    DECLARE_DFT_TRACE_KEY_INFO("change uart rate fail",OAL_DFT_TRACE_FAIL);
                }
                break;
            }
            else
            {
                if (!IS_ERR_OR_NULL(ps_core_d->tty) && tty_chars_in_buffer(ps_core_d->tty))
                {
                    PS_PRINT_INFO("tty tx buf is not empty\n");
                }

                bwkup_gpio_val = board_get_bwkup_gpio_val();
                PS_PRINT_INFO("bfg still NOT wkup, gpio level:%d\n", bwkup_gpio_val);
                DECLARE_DFT_TRACE_KEY_INFO("bfg wakeup fail",OAL_DFT_TRACE_EXCEP);
                i++;
            }
        }while(i < RETRY_TIMES);
        break;
    }

    if (RETRY_TIMES == i)
    {
        ps_change_uart_baud_rate(DEFAULT_BAUD_RATE, FLOW_CTRL_ENABLE);
        PS_PRINT_INFO("host wkup bfg fail\n");
    }
}

/* sensorbub模块的函数，睡眠唤醒时用来查询sensorhub的状态 */
extern int getSensorMcuMode(void);
extern int get_iomcu_power_state(void);

void host_send_disallow_msg(struct work_struct *work)
{
#define MAX_TTYRESUME_LOOPCNT (300)
#define MAX_SENSORHUB_LOOPCNT (30)
    uint32 loop_tty_resume_cnt = 0;
    uint32 loop_sensorhub_resume_cnt = 0;
    struct ps_core_s *ps_core_d = NULL;
    struct pm_drv_data *pm_data = pm_get_drvdata();

    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return;
    }

    PS_PRINT_INFO("%s\n", __func__);

    ps_get_core_reference(&ps_core_d);
    if (!ps_core_d)
    {
        PS_PRINT_ERR("ps_core has not inited\n");
        return;
    }

    /* 防止host睡眠情况下被dev唤醒进入gpio中断后直接在这里下发消息，
     * 此时uart可能还没有ready,所以这里等待tty resume之后才下发消息 */
    if ((ps_core_d->tty) && (ps_core_d->tty->port))
    {
        PS_PRINT_INFO("tty port flag 0x%x\n", (unsigned int)ps_core_d->tty->port->flags);
        while(test_bit(ASYNCB_SUSPENDED, (volatile unsigned long*)&(ps_core_d->tty->port->flags)))
        {
            if(loop_tty_resume_cnt++ >= MAX_TTYRESUME_LOOPCNT)
            {
                PS_PRINT_ERR("tty is not ready, flag is 0x%x!\n", (unsigned int)ps_core_d->tty->port->flags);
                break;
            }
            msleep(10);
        }

        /*查询sensorhub状态，如果不是wkup状态，uart的时钟可能会不对*/
        if (1 == getSensorMcuMode())
        {
            PS_PRINT_INFO("sensorbub state is %d\n", get_iomcu_power_state());
            while(9 != get_iomcu_power_state() && 0 != get_iomcu_power_state()) //0->ST_POWERON,8->ST_SLEEP,9->ST_WAKEUP
            {
                if (loop_sensorhub_resume_cnt++ >= MAX_SENSORHUB_LOOPCNT)
                {
                    PS_PRINT_ERR("sensorhub not wakeup yet, state is %d\n", get_iomcu_power_state());
                    break;
                }
                msleep(10);
            }
        }
    }
    else
    {
        PS_PRINT_ERR("tty has not inited\n");
        return;
    }

    /* clear pf msg parsing buffer to avoid problem caused by wrong packet */
    reset_uart_rx_buf();

    /* 设置uart可用,下发disallow sleep消息,唤醒完成 */
    bfgx_uart_state_set(UART_READY);
    ps_tx_sys_cmd(ps_core_d, SYS_MSG, SYS_CFG_DISALLOW_SLP);

    /* 这里设置完成量对于dev wkup host没有意义, 只是保证和host wkup dev的操作一致
     * 注意这就要求host wkup dev前需要INIT完成量计数 */
    complete_all(&pm_data->host_wkup_dev_comp);

    /* if any of BFNI is open, we should mod timer. */
    if(!bfgx_other_subsys_all_shutdown(BFGX_GNSS))
    {
        mod_timer(&pm_data->bfg_timer, jiffies + BT_SLEEP_TIME * HZ);
    }

    ps_core_d->ps_pm->operate_beat_timer(BEAT_TIMER_RESET);

    if (NEED_SET_FLAG == atomic_read(&pm_data->bfg_needwait_devboot_flag))
    {
        complete(&pm_data->dev_bootok_ack_comp);
    }
}

int32 host_wkup_dev(void)
{
    uint64 timeleft;
    struct pm_drv_data *pm_data = pm_get_drvdata();
    struct ps_core_s *ps_core_d = NULL;
    if (unlikely(NULL == pm_data))
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return -FAILURE;
    }
    ps_get_core_reference(&ps_core_d);
    if (unlikely(NULL == ps_core_d))
    {
        PS_PRINT_ERR("ps_core_d ot tty is NULL\n");
        return -EINVAL;
    }
    if (BFGX_PM_DISABLE == pm_data->bfgx_lowpower_enable)
    {
        return 0;
    }
    PS_PRINT_DBG("wkup start\n");

    INIT_COMPLETION(pm_data->host_wkup_dev_comp);
    queue_work(pm_data->wkup_dev_workqueue, &pm_data->wkup_dev_work);
    ps_uart_state_pre(ps_core_d->tty);
    timeleft = wait_for_completion_timeout(&pm_data->host_wkup_dev_comp, msecs_to_jiffies(WAIT_WKUPDEV_MSEC));
    if (!timeleft)
    {
        ps_uart_state_dump(ps_core_d->tty);
        PS_PRINT_ERR("wait wake up dev timeout\n");
        return -ETIMEDOUT;
    }
    PS_PRINT_DBG("wkup over\n");

    return 0;
}


int32 bfgx_other_subsys_all_shutdown(uint8 subsys)
{
    int32  i = 0;
    struct ps_core_s *ps_core_d = NULL;

    ps_get_core_reference(&ps_core_d);
    if (NULL == ps_core_d)
    {
        PS_PRINT_ERR("ps_core_d is NULL\n");
        return -EINVAL;
    }

    for (i = 0; i < BFGX_BUTT; i++)
    {
        if (i == subsys)
        {
            continue;
        }

        if (POWER_STATE_OPEN == atomic_read(&ps_core_d->bfgx_info[i].subsys_state))
        {
            return false;
        }
    }

    return true;
}

int32 bfgx_dev_power_on(void)
{
    uint64 timeleft;
    int32 error;
    struct ps_core_s *ps_core_d = NULL;
    struct pm_drv_data *pm_data = pm_get_drvdata();
    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return BFGX_POWER_FAILED;
    }

    ps_get_core_reference(&ps_core_d);
    if (unlikely(NULL == ps_core_d))
    {
        PS_PRINT_ERR("ps_core_d is err\n");
        return BFGX_POWER_FAILED;
    }

    /*防止Host睡眠*/
    wake_lock(&pm_data->bfg_wake_lock);

    INIT_COMPLETION(pm_data->dev_bootok_ack_comp);
    atomic_set(&pm_data->bfg_needwait_devboot_flag, NEED_SET_FLAG);

    if (wlan_is_shutdown())
    {
        PS_PRINT_INFO("bfgx pull up power_on_enable gpio!\n");
        board_power_on();

        if (BFGX_POWER_SUCCESS != open_tty_drv(ps_core_d->pm_data))
        {
            PS_PRINT_ERR("open tty fail!\n");
            error = BFGX_POWER_TTY_OPEN_FAIL;
            goto bfgx_power_on_fail;
        }

        if (BFGX_POWER_SUCCESS != firmware_download_function(BFGX_CFG))
        {
            oal_disable_sdio_state(pm_data->pst_wlan_pm_info->pst_sdio, OAL_SDIO_ALL);
            PS_PRINT_ERR("bfgx download firmware fail!\n");
            error = BFGX_POWER_DOWNLOAD_FIRMWARE_FAIL;
            goto bfgx_power_on_fail;
        }
        oal_disable_sdio_state(pm_data->pst_wlan_pm_info->pst_sdio, OAL_SDIO_ALL);
    }
    else
    {
        if (BFGX_POWER_SUCCESS != open_tty_drv(ps_core_d->pm_data))
        {
            PS_PRINT_ERR("open tty fail!\n");
            error = BFGX_POWER_TTY_OPEN_FAIL;
            goto bfgx_power_on_fail;
        }

        if(BFGX_POWER_SUCCESS != wlan_pm_open_bcpu())
        {
            PS_PRINT_ERR("wifi dereset bcpu fail!\n");
            error = BFGX_POWER_WIFI_DERESET_BCPU_FAIL;
            goto bfgx_power_on_fail;
        }
    }
    ps_uart_state_pre(ps_core_d->tty);
    /*WAIT_BFGX_BOOTOK_TIME:这个时间目前为1s，有1s不够的情况，需要关注*/
    timeleft = wait_for_completion_timeout(&pm_data->dev_bootok_ack_comp, msecs_to_jiffies(WAIT_BFGX_BOOTOK_TIME));
    if (!timeleft)
    {
        ps_uart_state_dump(ps_core_d->tty);
        if (wlan_is_shutdown())
        {
            PS_PRINT_ERR("wifi off, wait bfgx boot up ok timeout\n");
            error = BFGX_POWER_WIFI_OFF_BOOT_UP_FAIL;
            goto bfgx_power_on_fail;
        }
        else
        {
            PS_PRINT_ERR("wifi on, wait bfgx boot up ok timeout\n");
            error = BFGX_POWER_WIFI_ON_BOOT_UP_FAIL;
            goto bfgx_power_on_fail;
        }
    }

    atomic_set(&pm_data->bfg_needwait_devboot_flag, NONEED_SET_FLAG);

    bfgx_pm_feature_set();

    return BFGX_POWER_SUCCESS;

bfgx_power_on_fail:
    wake_unlock(&pm_data->bfg_wake_lock);
    return error;
}


int32 bfgx_dev_power_off(void)
{
    int32  error = SUCCESS;
    struct ps_core_s *ps_core_d = NULL;
    struct pm_drv_data *pm_data = pm_get_drvdata();

    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return -FAILURE;
    }

    ps_get_core_reference(&ps_core_d);
    if (unlikely(NULL == ps_core_d))
    {
        PS_PRINT_ERR("ps_core_d is err\n");
        return -FAILURE;
    }

    pm_data->ps_pm_interface->operate_beat_timer(BEAT_TIMER_DELETE);
    del_timer_sync(&pm_data->bfg_timer);

    /* 下电即将完成，需要在此时设置下次上电要等待device上电成功的flag */
    atomic_set(&pm_data->bfg_needwait_devboot_flag, NEED_SET_FLAG);

    if (wlan_is_shutdown())
    {
        if (SUCCESS != release_tty_drv(ps_core_d->pm_data))
        {
            /*代码执行到此处，说明六合一所有业务都已经关闭，无论tty是否关闭成功，device都要下电*/
            PS_PRINT_ERR("wifi off, close tty is err!");
        }

        pm_data->bfgx_dev_state = BFGX_SLEEP;

        PS_PRINT_INFO("bfgx pull down power_on_enable gpio\n");
        board_power_off();
    }
    else
    {
         if(SUCCESS != uart_bfgx_close_cmd())
         {
            /*bfgx self close fail 了，后面也要通过wifi shutdown bcpu*/
            PS_PRINT_ERR("bfgx self close fail\n");
         }

         if (SUCCESS != release_tty_drv(ps_core_d->pm_data))
         {
            /*代码执行到此处，说明bfgx所有业务都已经关闭，无论tty是否关闭成功，都要关闭bcpu*/
            PS_PRINT_ERR("wifi on, close tty is err!");
         }

         pm_data->bfgx_dev_state = BFGX_SLEEP;

         if(SUCCESS != wlan_pm_shutdown_bcpu_cmd())
         {
            PS_PRINT_ERR("wifi shutdown bcpu fail\n");
            error = -FAILURE;
         }
    }

    /*if wakelock is active, we should wake unlock*/
    if (wake_lock_active(&pm_data->bfg_wake_lock))
    {
        wake_unlock(&pm_data->bfg_wake_lock);
    }

	return error;
}


int32 bfgx_dev_power_control(uint8 subsys, uint8 flag)
{
    int32 ret = 0;

    if (BFG_POWER_GPIO_UP == flag)
    {
        ret = bfgx_power_on(subsys);
        if (ret)
        {
            PS_PRINT_ERR("bfgx power on is error!\n");
        }
    }
    else if (BFG_POWER_GPIO_DOWN == flag)
    {
        ret = bfgx_power_off(subsys);
        if (ret)
        {
            PS_PRINT_ERR("bfgx power off is error!\n");
        }
    }
    else
    {
        PS_PRINT_ERR("invalid input data!\n");
        ret = -FAILURE;
    }

    return ret;
}


int firmware_download_function(uint32 which_cfg)
{
    int32 ret = 0;
    unsigned long long total_time = 0;
    ktime_t start_time, end_time, trans_time;
    static unsigned long long max_time = 0;
    static unsigned long long count = 0;
    struct pm_drv_data *pm_data = pm_get_drvdata();
    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return -FAILURE;
    }

    start_time = ktime_get();

    if (which_cfg >= CFG_FILE_TOTAL)
    {
        PS_PRINT_ERR("cfg file index [%d] outof range\n", which_cfg);
        return -FAILURE;
    }

    PS_PRINT_INFO("enter firmware_download_function\n");

    /*firmware_cfg_init(sdio) function should just be called once*/
    if (!test_bit(FIRMWARE_CFG_INIT_OK, &pm_data->firmware_cfg_init_flag))
    {
        PS_PRINT_INFO("firmware_cfg_init begin\n");
        ret = firmware_cfg_init();
        if (ret)
        {
            PS_PRINT_ERR("firmware_cfg_init failed, ret:%d!\n", ret);
            return ret;
        }

        PS_PRINT_INFO("firmware_cfg_init OK\n");
        set_bit(FIRMWARE_CFG_INIT_OK, &pm_data->firmware_cfg_init_flag);
    }

    oal_sdio_claim_host(pm_data->pst_wlan_pm_info->pst_sdio);

    ret = sdio_reinit();
    if (ret < 0)
    {
        oal_sdio_release_host(pm_data->pst_wlan_pm_info->pst_sdio);
        PS_PRINT_ERR("sdio reinit failed, ret:%d!\n", ret);
        return -FAILURE;
    }

    wlan_pm_init_dev();

    PS_PRINT_INFO("firmware_download begin\n");

    ret = firmware_download(which_cfg);
    if (ret < 0)
    {
        oal_sdio_release_host(pm_data->pst_wlan_pm_info->pst_sdio);
        PS_PRINT_ERR("firmware download fail!\n");
        DECLARE_DFT_TRACE_KEY_INFO("patch_download_fail",OAL_DFT_TRACE_FAIL);
        return -FAILURE;
    }
    DECLARE_DFT_TRACE_KEY_INFO("patch_download_ok",OAL_DFT_TRACE_SUCC);

    oal_sdio_release_host(pm_data->pst_wlan_pm_info->pst_sdio);

    PS_PRINT_INFO("firmware_download success\n");

    end_time = ktime_get();

    trans_time = ktime_sub(end_time, start_time);
    total_time = (unsigned long long)ktime_to_us(trans_time);

    if (total_time > max_time)
    {
        max_time = total_time;
    }

    count++;
    PS_PRINT_WARNING("download firmware, count [%llu], current time [%llu]us, max time [%llu]us\n", count, total_time, max_time);

    return SUCCESS;
}

int32 wlan_is_shutdown(void)
{
    struct pm_drv_data *pm_data = pm_get_drvdata();
    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return -FAILURE;
    }

    return ((POWER_STATE_SHUTDOWN == pm_data->pst_wlan_pm_info->ul_wlan_power_state) ? true : false);
}

int32 bfgx_is_shutdown(void)
{
    struct ps_core_s *ps_core_d = NULL;

    ps_get_core_reference(&ps_core_d);
    if (NULL == ps_core_d)
    {
        PS_PRINT_ERR("ps_core_d is NULL\n");
        return -EINVAL;
    }

    return ps_chk_bfg_active(ps_core_d) ? false : true;
}

int32 wifi_power_fail_process(int32 error)
{
    struct pm_drv_data *pm_data = pm_get_drvdata();
    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return WIFI_POWER_FAIL;
    }

    if (error >= WIFI_POWER_ENUM_BUTT)
    {
         PS_PRINT_ERR("error is undefined, error=[%d]\n", error);
         return WIFI_POWER_FAIL;
    }

    PS_PRINT_INFO("wifi power fail, error=[%d]\n", error);

    switch (error)
    {
    case WIFI_POWER_SUCCESS:
    case WIFI_POWER_PULL_POWER_GPIO_FAIL:
        break;

    /*BFGX off，wifi firmware download fail和wait boot up fail，直接返回失败，上层重试，不走DFR*/
    case WIFI_POWER_BFGX_OFF_BOOT_UP_FAIL:
        PS_PRINT_INFO("bfgx off,set wlan_power_state to shutdown\n");
        oal_wlan_gpio_intr_enable(oal_get_sdio_default_handler(), OAL_FALSE);
        pm_data->pst_wlan_pm_info->ul_wlan_power_state = POWER_STATE_SHUTDOWN;
    case WIFI_POWER_BFGX_OFF_FIRMWARE_DOWNLOAD_FAIL:
        PS_PRINT_INFO("wifi power fail: pull down power on gpio\n");
        board_power_off();
        break;

    /*BFGX on，wifi上电失败，进行全系统复位，wifi本次返回失败，上层重试*/
    case WIFI_POWER_BFGX_ON_BOOT_UP_FAIL:
        PS_PRINT_INFO("bfgx on,set wlan_power_state to shutdown\n");
        oal_wlan_gpio_intr_enable(oal_get_sdio_default_handler(), OAL_FALSE);
        pm_data->pst_wlan_pm_info->ul_wlan_power_state = POWER_STATE_SHUTDOWN;
    case WIFI_POWER_BFGX_DERESET_WCPU_FAIL:
    case WIFI_POWER_BFGX_ON_FIRMWARE_DOWNLOAD_FAIL:
        if (WIFI_POWER_SUCCESS == plat_power_fail_exception_info_set(SUBSYS_WIFI, THREAD_WIFI, WIFI_POWER_ON_FAIL))
        {
            bfgx_system_reset();
            plat_power_fail_process_done();
        }
        else
        {
            PS_PRINT_ERR("wifi power fail, set exception info fail\n");
        }
        break;

    default:
        PS_PRINT_ERR("error is undefined, error=[%d]\n", error);
        break;
    }

    return WIFI_POWER_FAIL;
}

int32 wlan_power_on(void)
{
    int32  error = WIFI_POWER_SUCCESS;
    unsigned long long total_time = 0;
    ktime_t start_time, end_time, trans_time;
    static unsigned long long max_download_time = 0;
    static unsigned long long num = 0;
    struct pm_drv_data *pm_data = pm_get_drvdata();
    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return -FAILURE;
    }

    start_time = ktime_get();

    PS_PRINT_INFO("wlan power on!\n");

    if (bfgx_is_shutdown())
    {
        PS_PRINT_SUC("wifi pull up power_on_enable gpio!\n");
        board_power_on();
        DECLARE_DFT_TRACE_KEY_INFO("wlan_poweron_by_gpio_ok",OAL_DFT_TRACE_SUCC);

        wlan_pm_init_device_ready(pm_data->pst_wlan_pm_info);

        if(WIFI_POWER_SUCCESS == firmware_download_function(BFGX_AND_WIFI_CFG))
        {
            pm_data->pst_wlan_pm_info->ul_wlan_power_state = POWER_STATE_OPEN;
            oal_wlan_gpio_intr_enable(oal_get_sdio_default_handler(), OAL_TRUE);
        }
        else
        {
            PS_PRINT_ERR("firmware download fail\n");
            error = WIFI_POWER_BFGX_OFF_FIRMWARE_DOWNLOAD_FAIL;
            goto wifi_power_fail;
        }

        if(!wlan_pm_wait_device_ready(pm_data->pst_wlan_pm_info))
        {
            DECLARE_DFT_TRACE_KEY_INFO("wlan_poweron_dev_ready_by_gpio_fail", OAL_DFT_TRACE_FAIL);
            PS_PRINT_ERR("wlan_pm_wait_device_ready timeout %d !!!!!!\n", HOST_WAIT_BOTTOM_INIT_TIMEOUT);
            error = WIFI_POWER_BFGX_OFF_BOOT_UP_FAIL;
            goto wifi_power_fail;
        }
    }
    else
    {
        if(WIFI_POWER_SUCCESS != uart_wifi_open())
        {
            DECLARE_DFT_TRACE_KEY_INFO("wlan_poweron_by_uart_fail", OAL_DFT_TRACE_FAIL);
            error = WIFI_POWER_BFGX_DERESET_WCPU_FAIL;
            goto wifi_power_fail;
        }
        else
        {
            wlan_pm_init_device_ready(pm_data->pst_wlan_pm_info);
            if(WIFI_POWER_SUCCESS == firmware_download_function(WIFI_CFG))
            {
                pm_data->pst_wlan_pm_info->ul_wlan_power_state = POWER_STATE_OPEN;
                oal_wlan_gpio_intr_enable(oal_get_sdio_default_handler(), OAL_TRUE);
            }
			else
            {
                PS_PRINT_ERR("firmware download fail\n");
                error = WIFI_POWER_BFGX_ON_FIRMWARE_DOWNLOAD_FAIL;
                goto wifi_power_fail;
            }

            if(!wlan_pm_wait_device_ready(pm_data->pst_wlan_pm_info))
            {
                DECLARE_DFT_TRACE_KEY_INFO("wlan_poweron_dev_ready_by_uart_fail",OAL_DFT_TRACE_FAIL);
                PS_PRINT_ERR("wlan_pm_wait_device_ready timeout %d !!!!!!",HOST_WAIT_BOTTOM_INIT_TIMEOUT);
                error = WIFI_POWER_BFGX_ON_BOOT_UP_FAIL;
                goto wifi_power_fail;
            }
        }
    }

    hcc_enable(hcc_get_default_handler(), OAL_TRUE);

    end_time = ktime_get();

    trans_time = ktime_sub(end_time, start_time);
    total_time = (unsigned long long)ktime_to_us(trans_time);

    if (total_time > max_download_time)
    {
        max_download_time = total_time;
    }

    num++;
    PS_PRINT_WARNING("power on, count [%llu], current time [%llu]us, max time [%llu]us\n", num, total_time, max_download_time);

    return WIFI_POWER_SUCCESS;

wifi_power_fail:
    return wifi_power_fail_process(error);
}

int32 wlan_power_off(void)
{
    struct pm_drv_data *pm_data = pm_get_drvdata();
    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return -FAILURE;
    }

    PS_PRINT_INFO("wlan power off!\n");

    hcc_disable(hcc_get_default_handler(), OAL_TRUE);

    if (bfgx_is_shutdown())
    {
        PS_PRINT_INFO("wifi pull down power_on_enable!\n");
        oal_disable_sdio_state(oal_get_sdio_default_handler(), OAL_SDIO_ALL);
        board_power_off();
        DECLARE_DFT_TRACE_KEY_INFO("wlan_poweroff_by_gpio",OAL_DFT_TRACE_SUCC);
    }
    else
    {
        /*先关闭SDIO TX通道*/       
        oal_disable_sdio_state(oal_get_sdio_default_handler(), OAL_SDIO_TX);

        /*wakeup dev,send poweroff cmd to wifi*/
        if(OAL_SUCC != wlan_pm_poweroff_cmd())
        {
            /*wifi self close 失败了也继续往下执行，uart关闭WCPU，异常恢复推迟到wifi下次open的时候执行*/
            DECLARE_DFT_TRACE_KEY_INFO("wlan_poweroff_by_sdio_fail",OAL_DFT_TRACE_FAIL);
            return -FAILURE;

        }

        oal_disable_sdio_state(oal_get_sdio_default_handler(), OAL_SDIO_ALL);

        /*power off cmd execute succ,send shutdown wifi cmd to BFGN */
        if(OAL_SUCC != uart_wifi_close())
        {
            /*uart关闭WCPU失败也继续执行，DFR推迟到wifi下次open的时候执行*/
            DECLARE_DFT_TRACE_KEY_INFO("wlan_poweroff_uart_cmd_fail",OAL_DFT_TRACE_FAIL);
        }
        DECLARE_DFT_TRACE_KEY_INFO("wlan_poweroff_by_bcpu_ok",OAL_DFT_TRACE_SUCC);
    }

    oal_wlan_gpio_intr_enable(oal_get_sdio_default_handler(), OAL_FALSE);
    
    pm_data->pst_wlan_pm_info->ul_wlan_power_state = POWER_STATE_SHUTDOWN;

    return SUCCESS;
}

int32 bfgx_power_on(uint8 subsys)
{
    int32  ret = BFGX_POWER_SUCCESS;
    unsigned long long total_time = 0;
    ktime_t start_time, end_time, trans_time;
    static unsigned long long max_download_time = 0;
    static unsigned long long num = 0;

    start_time = ktime_get();

    if (bfgx_other_subsys_all_shutdown(subsys))
    {
       ret = bfgx_dev_power_on();
       if(BFGX_POWER_SUCCESS != ret)
       {
            return ret;
       }
    }

    end_time = ktime_get();

    trans_time = ktime_sub(end_time, start_time);
    total_time = (unsigned long long)ktime_to_us(trans_time);

    if (total_time > max_download_time)
    {
        max_download_time = total_time;
    }

    num++;
    PS_PRINT_WARNING("power on, count [%llu], current time [%llu]us, max time [%llu]us\n", num, total_time, max_download_time);

    return BFGX_POWER_SUCCESS;
}

int32 bfgx_power_off(uint8 subsys)
{
    struct ps_core_s *ps_core_d = NULL;

    ps_get_core_reference(&ps_core_d);
    if (unlikely(NULL == ps_core_d))
    {
        PS_PRINT_ERR("ps_core_d is null\n");
        return -FAILURE;
    }

    if (ps_chk_only_gnss_and_cldslp(ps_core_d))
    {
        PS_PRINT_SUC("%s power off request sleep!\n", g_bfgx_subsys_name[subsys]);
        host_allow_devslp_in_node(ps_core_d);

        return SUCCESS;
    }

    PS_PRINT_INFO("%s power off!\n", g_bfgx_subsys_name[subsys]);

    if (bfgx_other_subsys_all_shutdown(subsys))
    {
        return bfgx_dev_power_off();
    }

    return SUCCESS;
}

extern uint32 g_ulJumpCmdResult;
int32 device_mem_check(unsigned long long *time)
{
    int32 ret = -FAILURE;
    unsigned long long total_time = 0;
    ktime_t start_time, end_time, trans_time;
    struct pm_drv_data *pm_data = pm_get_drvdata();
    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return -FAILURE;
    }

    if (NULL == time)
    {
        PS_PRINT_ERR("param time is  NULL!\n");
        return -FAILURE;
    }

    start_time = ktime_get();

    PS_PRINT_INFO("device ram reg test!\n");

    if (bfgx_is_shutdown())
    {
        PS_PRINT_SUC("factory ram reg test pull up power_on_enable gpio!\n");
        board_power_on();
    }
    else
    {
        PS_PRINT_ERR("device mem check:bfgx must be shutdown!\n");
        return ret;
    }

    ret = firmware_download_function(RAM_REG_TEST_CFG);
    if (SUCCESS == ret)
    {
        PS_PRINT_INFO("device ram reg test success!\n");
    }
    else
    {
        PS_PRINT_INFO("device ram reg test failed!\n");
    }

    oal_disable_sdio_state(pm_data->pst_wlan_pm_info->pst_sdio, OAL_SDIO_ALL);

    board_power_off();

    end_time = ktime_get();

    trans_time = ktime_sub(end_time, start_time);
    total_time = (unsigned long long)ktime_to_us(trans_time);

    *time = total_time;

    PS_PRINT_SUC("device mem reg test time [%llu]us\n", total_time);

    ret = g_ulJumpCmdResult;
    g_ulJumpCmdResult = CMD_JUMP_EXEC_RESULT_SUCC;

    return ret;
}

EXPORT_SYMBOL(device_mem_check);


int32 ps_pm_register(struct ps_pm_s *new_pm)
{
    struct pm_drv_data *pm_data = pm_get_drvdata();
    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL\n");
        return -FAILURE;
    }

    if (NULL == new_pm)
    {
        PS_PRINT_ERR("new_pm is null!\n");
        return -FAILURE;
    }

    pm_data->ps_pm_interface                        = new_pm;
    pm_data->ps_pm_interface->pm_priv_data          = pm_data;
    pm_data->ps_pm_interface->bfg_wake_lock         = bfg_wake_lock;
    pm_data->ps_pm_interface->bfg_wake_unlock       = bfg_wake_unlock;
    pm_data->ps_pm_interface->bfgx_dev_state_get    = bfgx_state_get;
    pm_data->ps_pm_interface->bfgx_dev_state_set    = bfgx_state_set;
    pm_data->ps_pm_interface->bfg_power_set         = bfgx_dev_power_control;
    pm_data->ps_pm_interface->bfgx_uart_state_get   = bfgx_uart_state_get;
    pm_data->ps_pm_interface->bfgx_uart_state_set   = bfgx_uart_state_set;

    PS_PRINT_SUC("pm registered over!");

    return SUCCESS;
}
EXPORT_SYMBOL_GPL(ps_pm_register);


int32 ps_pm_unregister(struct ps_pm_s *new_pm)
{
    struct pm_drv_data *pm_data = pm_get_drvdata();
    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL\n");
        return -FAILURE;
    }

    PS_PRINT_DBG("enter\n");

    if (NULL == new_pm)
    {
        PS_PRINT_ERR("new_pm is null!\n");
        return -FAILURE;
    }

    new_pm->bfg_wake_lock           = NULL;
    new_pm->bfg_wake_unlock         = NULL;
    new_pm->bfgx_dev_state_get      = NULL;
    new_pm->bfgx_dev_state_set      = NULL;
    new_pm->bfg_power_set           = NULL;
    new_pm->bfgx_uart_state_set     = NULL;
    new_pm->bfgx_uart_state_get     = NULL;
    pm_data->ps_pm_interface        = NULL;

    PS_PRINT_SUC("pm unregistered over!");

    return SUCCESS;
}
EXPORT_SYMBOL_GPL(ps_pm_unregister);


irqreturn_t bfg_wake_host_isr(int irq, void *dev_id)
{
    struct ps_core_s *ps_core_d = NULL;
    struct pm_drv_data *pm_data = pm_get_drvdata();

    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return IRQ_NONE;
    }

    PS_PRINT_INFO("%s\n", __func__);

    pm_data->bfg_wakeup_host++;

    ps_get_core_reference(&ps_core_d);
    if (ps_core_d == NULL)
    {
        PS_PRINT_ERR("ps_core_d is null\n");
        return IRQ_NONE;
    }

    ps_core_d->ps_pm->bfg_wake_lock();
    bfgx_state_set(BFGX_ACTIVE);

    queue_work(pm_data->wkup_dev_workqueue, &pm_data->send_disallow_msg_work);

    return IRQ_HANDLED;
}

/*return 1 for wifi power on,0 for off.*/
oal_int32 hi110x_get_wifi_power_stat(oal_void)
{
    struct pm_drv_data *pm_data = pm_get_drvdata();
    return (pm_data->pst_wlan_pm_info->ul_wlan_power_state != POWER_STATE_SHUTDOWN);
}
EXPORT_SYMBOL(hi110x_get_wifi_power_stat);

STATIC int low_power_remove(void)
{
    int ret = 0;
    struct pm_drv_data *pm_data = pm_get_drvdata();
    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return -FAILURE;
    }

    wlan_pm_exit();

    /*remove kobject*/
    pm_user_ctrl_exit();

    /*delete timer*/
    del_timer_sync(&pm_data->bfg_timer);
    del_timer_sync(&pm_data->dev_ack_timer);

    /*destory wake lock*/
    wake_lock_destroy(&pm_data->bfg_wake_lock);

    /*free platform driver data struct*/
    kfree(pm_data);

    pm_data = NULL;

    pm_set_drvdata(NULL);

    return ret;
}

STATIC void devack_timer_expire(uint64 data)
{
    struct pm_drv_data  *pm_data = (struct pm_drv_data*)data;
    if (unlikely(NULL == pm_data))
    {
        PS_PRINT_ERR("devack timer para is null\n");
        return;
    }

    PS_PRINT_INFO("%s", __func__);

    if (1 == board_get_bwkup_gpio_val())
    {
        /* device doesn't agree to sleep */
        PS_PRINT_INFO("device does not agree to sleep\n");
        if (unlikely(1 == pm_data->rcvdata_bef_devack_flag))
        {
            PS_PRINT_INFO("device send data to host before dev rcv allow slp msg\n");
            pm_data->rcvdata_bef_devack_flag = 0;
        }
        bfgx_state_set(BFGX_ACTIVE);
        pm_data->ps_pm_interface->bfgx_uart_state_set(UART_READY);
        /* we mod timer at any time, since we could get another chance to sleep
           in exception case like:dev agree to slp after this ack timer expired
         */
        mod_timer(&pm_data->bfg_timer, jiffies + BT_SLEEP_TIME * HZ);

        complete(&pm_data->dev_ack_comp);
    }
    else
    {
        PS_PRINT_INFO("device agree to sleep, but host did not get the ack\n");
        pm_data->ps_pm_interface->operate_beat_timer(BEAT_TIMER_DELETE);
        bfg_wake_unlock();
        complete(&pm_data->dev_ack_comp);
    }

}

STATIC int low_power_probe(void)
{
    int ret = 0;
    struct pm_drv_data  *pm_data = NULL;
    struct workqueue_struct * host_wkup_dev_workq = NULL;

    pm_data = kzalloc(sizeof(struct pm_drv_data), GFP_KERNEL);
    if (NULL == pm_data)
    {
        PS_PRINT_ERR("no mem to allocate pm_data\n");
        goto PMDATA_MALLOC_FAIL;
    }

    pm_data->pst_wlan_pm_info = wlan_pm_init();
    if(0 == pm_data->pst_wlan_pm_info)
    {
        PS_PRINT_ERR("no mem to allocate wlan_pm_info\n");
        goto WLAN_INIT_FAIL;
    }

    pm_data->firmware_cfg_init_flag  = 0;
    pm_data->rcvdata_bef_devack_flag = 0;
    pm_data->bfgx_dev_state         = BFGX_SLEEP;
    pm_data->bfgx_pm_ctrl_enable    = BFGX_PM_DISABLE;
    pm_data->bfgx_lowpower_enable   = BFGX_PM_ENABLE;            /* enable host low_power function defaultly */
    pm_data->bfgx_bt_lowpower_enable   = BFGX_PM_ENABLE;
    pm_data->bfgx_gnss_lowpower_enable = BFGX_PM_ENABLE;
    pm_data->bfgx_nfc_lowpower_enable  = BFGX_PM_DISABLE;

    atomic_set(&pm_data->gnss_sleep_flag, GNSS_AGREE_SLEEP);
    atomic_set(&pm_data->bfg_needwait_devboot_flag, NEED_SET_FLAG);

    /* create an ordered workqueue with @max_active = 1 & WQ_UNBOUND flag to wake up device */
    host_wkup_dev_workq = create_singlethread_workqueue("wkup_dev_workqueue");
    if (!host_wkup_dev_workq)
    {
        PS_PRINT_ERR("create wkup workqueue failed\n");
        goto CREATE_WORKQ_FAIL;
    }
    pm_data->wkup_dev_workqueue = host_wkup_dev_workq;
    INIT_WORK(&pm_data->wkup_dev_work, host_wkup_dev_work);
    INIT_WORK(&pm_data->send_disallow_msg_work, host_send_disallow_msg);

	pm_data->board					= get_board_info();

    pm_data->bfg_irq = pm_data->board->bfgn_irq;

    /*init bfg wake lock */
    wake_lock_init(&pm_data->bfg_wake_lock, WAKE_LOCK_SUSPEND, BFG_LOCK_NAME);

    /*init mutex*/
    mutex_init(&pm_data->host_mutex);
    /*init spinlock*/
    spin_lock_init(&pm_data->node_timer_spinlock);

    /* init timer */
    init_timer(&pm_data->dev_ack_timer);
    pm_data->dev_ack_timer.function = devack_timer_expire;
    pm_data->dev_ack_timer.data     = (unsigned long)pm_data;

    /* init bfg data timer */
    init_timer(&pm_data->bfg_timer);
    pm_data->bfg_timer.function = bfg_timer_expire;
    pm_data->bfg_timer.data     = (unsigned long)pm_data;

    /* init completion */
    init_completion(&pm_data->host_wkup_dev_comp);
    init_completion(&pm_data->dev_ack_comp);
    init_completion(&pm_data->dev_bootok_ack_comp);

    /*set driver data*/
    pm_set_drvdata(pm_data);

    ret = pm_user_ctrl_init();
    if (ret)
    {
        PS_PRINT_ERR("failed to create power properties!\n");
        goto PM_USER_CTL_FAIL;
    }

    /* register host pm */
    ret = register_pm_notifier(&pf_suspend_notifier);
	if (ret < 0)
    {
		PS_PRINT_ERR("%s : register_pm_notifier failed!\n", __func__);
	}

    return OAL_SUCC;

PM_USER_CTL_FAIL:

CREATE_WORKQ_FAIL:

WLAN_INIT_FAIL:
    kfree(pm_data);
PMDATA_MALLOC_FAIL:
    return -ENOMEM;
}

int low_power_init(void)
{
    int ret = -FAILURE;

	ret = low_power_probe();
    if (SUCCESS != ret)
    {
        PS_PRINT_ERR("low_power_init: low_power_probe fail\n");
    }

     PS_PRINT_INFO("low_power_init: success\n");
    return ret;
}

void  low_power_exit(void)
{
	low_power_remove();
    firmware_cfg_clear();
}

