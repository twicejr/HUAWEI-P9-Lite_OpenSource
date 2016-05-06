/*
 * 4wire_wake.h
 *
 */
#ifndef FOUR_WIRE_WAKE_H
#define FOUR_WIRE_WAKE_H

#include <linux/types.h>
#include <linux/semaphore.h>
#include <linux/wakelock.h>
#include <linux/workqueue.h>
#include <linux/timer.h>

typedef struct four_wire_wake_mgmt
{
    atomic_t m_bus_busy_atom; /* atomic flag to mark modem bus busy or not */

    spinlock_t m_four_wire_splock; /* use spinlock for four wire */

    struct wake_lock m_bus_busy_wk; /* wakelock for hold wake for bus busy tx or rx */

    struct wake_lock m_timeout_wk; /* 2s timeout wakelock when cp wake ap */

    struct timer_list m_ap_idle_timer; /* when bus idle, ap hold wake for a 2s timeout */

    struct work_struct m_cpwkap_work; /* handle cp wake ap work */

    struct work_struct m_idle_timer_work; /* handler idle time callback as cannot down semaphore in softirq context */
} four_wire_wake_mgmt_t;


void cp_wake_ap_isr(int t_level);
int four_wire_wake_init(void);
void four_wire_reset(void);
int ap_tx_wait_cp_ready(void);
void ap_busy_wake(void);
void ap_timed_idle_wake(void);


#endif
