/*
 * 4wire_wake.c
 *
 */
#include <linux/module.h>
#include <linux/errno.h>
#include <linux/types.h>
#include <linux/time.h>
#include <linux/wakelock.h>
#include <linux/delay.h>
#include <linux/wait.h>

#include "viatel.h"
#include "via_gpios.h"
#include "ext_modem.h"
#include "4wire_wake.h"
#include "apcp_test.h"


#define AP_IDLE_KEEP_WAKE_TIME    2000
#define WAIT_CP_READY_LEVEL_TIME    10
#define MAX_WAIT_CP_READY_RETRY    6


static four_wire_wake_mgmt_t g_four_wire = {0};


void cp_wake_ap_isr(int t_level)
{
    if (t_level == GPIO_LEVEL_LOW)
    {
        /* count cp wake ap times */
        apcp_cpwkap_count();

        /* Cp requset Ap wake, ap keep wake for 2s timeout */
        wake_lock_timeout(&g_four_wire.m_timeout_wk, msecs_to_jiffies(AP_IDLE_KEEP_WAKE_TIME));

        schedule_work(&g_four_wire.m_cpwkap_work);
    }
    else
    {
        /*Cp allow Ap sleep*/
    }
}
EXPORT_SYMBOL(cp_wake_ap_isr);

void ap_busy_wake(void)
{
    unsigned long flags = 0;

    /* first acquire the four wire lock */
    spin_lock_irqsave(&g_four_wire.m_four_wire_splock, flags);
    /* set the bus busy to TRUE */
    atomic_set(&g_four_wire.m_bus_busy_atom, 1);
    /* cancel the 2s timeout timer */
    del_timer(&g_four_wire.m_ap_idle_timer);
    /* wake lock let ap keep wake */
    wake_lock(&g_four_wire.m_bus_busy_wk);
    /* realese the four wire lock */
    spin_unlock_irqrestore(&g_four_wire.m_four_wire_splock, flags);
}
EXPORT_SYMBOL(ap_busy_wake);

static void ap_idle_wake_timer_work(struct work_struct* pt_work)
{
    unsigned long flags = 0;

    /* first acquire the four wire lock */
    spin_lock_irqsave(&g_four_wire.m_four_wire_splock, flags);

    /* judge the bus busy flag */
    if (0 == atomic_read(&g_four_wire.m_bus_busy_atom))   /* the bus is idle */
    {
        /* set the AP_WK_CP gpio to high, that is to notify cp can sleep */
        set_apcp_gpio_output_level(GPIO_4WIRE_AP_WK_CP, GPIO_LEVEL_HIGH);
        /* release wake lock let ap keep wake */
        wake_unlock(&g_four_wire.m_bus_busy_wk);
    }

    /* realese the four wire lock */
    spin_unlock_irqrestore(&g_four_wire.m_four_wire_splock, flags);
}

static void ap_idle_wake_timer_cb(unsigned long data)
{
    schedule_work(&g_four_wire.m_idle_timer_work);
}

int ap_tx_wait_cp_ready(void)
{
    int ret = 0;
    unsigned int no_cp_ready_times = 0;
    int result = 0; /* return value for handle with max retry */
    unsigned int old_apwkcp_value = 0;
    unsigned int old_cp_ready_value = 0;
    /* first let ap keep wake*/
    ap_busy_wake();

    do
    {
        old_apwkcp_value = get_apcp_gpio_level(GPIO_4WIRE_AP_WK_CP);
        old_cp_ready_value = get_apcp_gpio_level(GPIO_4WIRE_CP_READY);

        /* set the AP_WK_CP gpio to low, that is to notify cp wake */
        set_apcp_gpio_output_level(GPIO_4WIRE_AP_WK_CP, GPIO_LEVEL_LOW);

        /* wait CP READY gpio level switch controled by modem */
        ret = wait_apcp_gpio_state(GPIO_4WIRE_CP_READY);

        if (0 == ret)   /* return success */
        {
            if (old_apwkcp_value || old_cp_ready_value)
            {
                hwlog_info("%s %d: old_apwkcp_value=%d old_cp_ready_value=%d\n", \
                           __func__, __LINE__, old_apwkcp_value, old_cp_ready_value);
                mdelay(WAIT_CP_READY_LEVEL_TIME);
            }

            if (0 == get_apcp_gpio_level(GPIO_4WIRE_CP_READY))
            {
                result = 0;
                break;
            }

            /* increase no cp ready times */
            no_cp_ready_times++;
            /* set the AP_WK_CP gpio to high, that is aim to produce a falling edge */
            set_apcp_gpio_output_level(GPIO_4WIRE_AP_WK_CP, GPIO_LEVEL_HIGH);
            mdelay(WAIT_CP_READY_LEVEL_TIME);
        }
        else if (-1 == ret) //timeout
        {
            /* increase no cp ready times */
            no_cp_ready_times++;
            hwlog_err("%s %d: has wait cp ready timeout, ap_wk_cp[%d->%d] cp_ready[%d->%d]\n", \
                      __func__, __LINE__, old_apwkcp_value, get_apcp_gpio_level(GPIO_4WIRE_AP_WK_CP), \
                      old_cp_ready_value, get_apcp_gpio_level(GPIO_4WIRE_CP_READY));
            /* set the AP_WK_CP gpio to high, that is aim to produce a falling edge */
            set_apcp_gpio_output_level(GPIO_4WIRE_AP_WK_CP, GPIO_LEVEL_HIGH);
            mdelay(WAIT_CP_READY_LEVEL_TIME);
        }
        else
        {
            hwlog_err("%s %d: wait cp ready ret=%d\n", __func__, __LINE__, ret);
            result = -1;
            break;
        }

        /* judge if no ack times reach MAX retry times */
        if (no_cp_ready_times >= MAX_WAIT_CP_READY_RETRY)
        {
            hwlog_err("%s %d: had retry wait cp ready reached MAX times\n", __func__, __LINE__);
            result = -2;
            break;
        }
    }
    while (1);

    return result;
}
EXPORT_SYMBOL(ap_tx_wait_cp_ready);

void cp_wake_ap_work(struct work_struct* pt_work)
{
    /* wait AP bus controller to resumed */
    wait_ap_bus_resumed();

    /* set AP_READY gpio to low level,  */
    set_apcp_gpio_output_level(GPIO_4WIRE_AP_READY, GPIO_LEVEL_LOW);
}

void ap_timed_idle_wake(void)
{
    unsigned long flags = 0;

    /* first acquire the four wire lock */
    spin_lock_irqsave(&g_four_wire.m_four_wire_splock, flags);
    /* set the bus busy to FALSE */
    atomic_set(&g_four_wire.m_bus_busy_atom, 0);
    /* start the 2s timeout timer */
    mod_timer(&g_four_wire.m_ap_idle_timer, jiffies + msecs_to_jiffies(AP_IDLE_KEEP_WAKE_TIME));
    /* realese the four wire lock */
    spin_unlock_irqrestore(&g_four_wire.m_four_wire_splock, flags);
}
EXPORT_SYMBOL(ap_timed_idle_wake);

void four_wire_reset(void)
{
    cancel_work_sync(&g_four_wire.m_cpwkap_work);
    cancel_work_sync(&g_four_wire.m_idle_timer_work);
    atomic_set(&g_four_wire.m_bus_busy_atom, 0);
    set_apcp_gpio_output_level(GPIO_4WIRE_AP_WK_CP, GPIO_LEVEL_HIGH);
    set_apcp_gpio_output_level(GPIO_4WIRE_AP_READY, GPIO_LEVEL_HIGH);
}
EXPORT_SYMBOL(four_wire_reset);

int four_wire_wake_init(void)
{
    int ret = 0;

    hwlog_info("%s %d: Enter.\n", __func__, __LINE__);
    wake_lock_init(&g_four_wire.m_bus_busy_wk, WAKE_LOCK_SUSPEND, "apcp bus wk");

    wake_lock_init(&g_four_wire.m_timeout_wk, WAKE_LOCK_SUSPEND, "cp_wk_ap wk");

    /* initialize spinlock used for four wire lock */
    spin_lock_init(&g_four_wire.m_four_wire_splock);

    /* initialize ap hold wake timer when bus idle */
    setup_timer(&g_four_wire.m_ap_idle_timer, ap_idle_wake_timer_cb, (unsigned long)&g_four_wire);

    /* on initialize ap let AP_WK_CP gpio output LOW, notify cp hold wake */
    /* need falling edge when first wake cp after complete download cp.rom */
    set_apcp_gpio_output_level(GPIO_4WIRE_AP_WK_CP, GPIO_LEVEL_HIGH);

    /* on initialize AP_READY gpio output HIGH, means ap need wake before cp tx */
    set_apcp_gpio_output_level(GPIO_4WIRE_AP_READY, GPIO_LEVEL_HIGH);

    INIT_WORK(&g_four_wire.m_cpwkap_work, cp_wake_ap_work);
    INIT_WORK(&g_four_wire.m_idle_timer_work, ap_idle_wake_timer_work);
    hwlog_info("%s %d: Exit.\n", __func__, __LINE__);
    return ret;
}
EXPORT_SYMBOL(four_wire_wake_init);

