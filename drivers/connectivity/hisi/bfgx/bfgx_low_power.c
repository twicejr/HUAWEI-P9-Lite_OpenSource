

/*****************************************************************************
  1 Include Head file
*****************************************************************************/
#include <linux/delay.h>
#include "hw_bfg_ps.h"
#include "plat_debug.h"
#include "plat_pm.h"
#include "bfgx_exception_rst.h"

/*****************************************************************************
  2 Define global variable
*****************************************************************************/
/*****************************************************************************
  3 Function implement

*****************************************************************************/


void host_allow_bfg_sleep(struct ps_core_s *ps_core_d)
{
    struct pm_drv_data *pm_data = pm_get_drvdata();
    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return;
    }

    PS_PRINT_INFO("%s\n", __func__);

    if (false == ps_core_d->tty_have_open)
    {
        PS_PRINT_INFO("tty has closed, not send msg to dev\n");
        return;
    }

    spin_lock(&pm_data->node_timer_spinlock);

    /* if someone is visiting the dev_node */
    if (atomic_read(&ps_core_d->node_visit_flag) > 0 )
    {
        PS_PRINT_INFO("someone visit node, not send allow sleep msg\n");
        spin_unlock(&pm_data->node_timer_spinlock);
        /* gnss write do NOT mod timer */
        mod_timer(&pm_data->bfg_timer, jiffies + BT_SLEEP_TIME * HZ);
        return;
    }

    /* 设置device状态为睡眠态，在host唤醒dev完成之前(或dev唤醒host前)uart不可用 */
    ps_core_d->ps_pm->bfgx_uart_state_set(UART_NOT_READY);
    ps_core_d->ps_pm->bfgx_dev_state_set(BFGX_SLEEP);

    spin_unlock(&pm_data->node_timer_spinlock);

    mod_timer(&pm_data->dev_ack_timer, jiffies + (WAIT_DEVACK_MSEC * HZ / 1000));

    /* we need reinit completion cnt as 0, to prevent such case:
     * 1)host allow dev sleep, dev ack with OK, cnt=1,
     * 2)device wkup host,
     * 3)host allow dev sleep,
     * 4)host wkup dev, it will wait dev_ack succ immediately since cnt==1,
     * 5)dev ack with ok, cnt=2,
     * this case will cause host wait dev_ack invalid.
     */
    INIT_COMPLETION(pm_data->dev_ack_comp);
    ps_tx_sys_cmd(ps_core_d, SYS_MSG, SYS_CFG_ALLOWDEV_SLP);
}

/**
 * Prototype    : bfgx_wakeup_device
 * Description  : check bfg device state for transfer data
 * input        : ps_core_d
 * output       : no
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2013/05/09
 *     Author       : wx145522
 *     Modification : Created function
 *
 */


/**
 * Prototype    : bfg_timer_expire
 * Description  : bfg timer expired function
 * input        : uint64
 * output       : no
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2013/05/09
 *     Author       : wx145522
 *     Modification : Created function
 *
 */
void bfg_timer_expire(uint64 data)
{
    struct ps_core_s *ps_core_d = NULL;
    struct pm_drv_data  *pm_data = (struct pm_drv_data*)data;
    if (unlikely(NULL == pm_data))
    {
        PS_PRINT_ERR("pm_data is null\n");
        return;
    }

    ps_core_d = pm_data->ps_pm_interface->ps_core_data;

    PS_PRINT_INFO("%s\n", __func__);

    if (BFGX_PM_DISABLE == pm_data->bfgx_lowpower_enable)
    {
        PS_PRINT_DBG("lowpower function disabled\n");
        return;
    }
    if (BFGX_SLEEP == pm_data->ps_pm_interface->bfgx_dev_state_get())
    {
        PS_PRINT_DBG("dev has been sleep\n");
        return;
    }

    if (GNSS_AGREE_SLEEP == atomic_read(&pm_data->gnss_sleep_flag))
    {
        host_allow_bfg_sleep(ps_core_d);
    }
    else
    {
        mod_timer(&pm_data->bfg_timer, jiffies + BT_SLEEP_TIME * HZ);
    }

}
