/*
 * hisi_mntn_test.c - for hisi MNTN test purpose
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 *
 */
#define MERROR_LEVEL    1
#define MWARNING_LEVEL  1
#define MNOTICE_LEVEL   1
#define MINFO_LEVEL     1
#define MDEBUG_LEVEL    0
#define MLOG_TAG        "mntn"

#include <linux/module.h>	/* Needed by all modules */
#include <linux/kernel.h>	/* Needed for KERN_ERR */
#include <linux/init.h>		/* Needed for the macros */
#include <linux/slab.h>
#include <linux/kallsyms.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/spinlock.h>
#include <linux/hrtimer.h>
#include <linux/delay.h>
#include <linux/hisi/util.h>
#include "mntn_log.h"

enum WDT_TST_LOCK_TYPE {
	WDT_TST_LOCK_SPINLOCK,
	WDT_TST_LOCK_MUTEX,
	WDT_TST_LOCK_SEM,
	WDT_TST_LOCK_NONE
};

static bool wdt_tst_enabled; /* default value is false*/
static spinlock_t wdt_tst_a_spinlock;
static spinlock_t wdt_tst_b_spinlock;
static struct workqueue_struct *wdt_tst_wq_a;
static struct work_struct wdt_tst_w_a;
static struct workqueue_struct *wdt_tst_wq_b;
static struct work_struct wdt_tst_w_b;
static struct hrtimer wdt_irq_tst_hrtimer;
static struct mutex wdt_tst_a_mutex;
static struct mutex wdt_tst_b_mutex;
static int wdt_tst_lock_type;

/*
	WDT PROCESS TEST
*/
static void hisi_wdt_tst_proc_body(void *data)
{
	mlog_e("in while\n");
	asm("b .");
}

/*
	WDT LOCK TEST
*/
#define WDT_TST_LOCK_A()	\
do {\
	if (WDT_TST_LOCK_SPINLOCK == wdt_tst_lock_type) {\
		spin_lock_irqsave(&wdt_tst_a_spinlock, flagsa);\
	} else {\
		mutex_lock(&wdt_tst_a_mutex);\
	} \
} while (0)

#define WDT_TST_UNLOCK_A()	\
do {\
	if (WDT_TST_LOCK_SPINLOCK == wdt_tst_lock_type) {\
		spin_unlock_irqrestore(&wdt_tst_a_spinlock, flagsa);\
	} else {\
		mutex_unlock(&wdt_tst_a_mutex);\
	} \
} while (0)

#define WDT_TST_LOCK_B()	\
do {\
	if (WDT_TST_LOCK_SPINLOCK == wdt_tst_lock_type) {\
		spin_lock_irqsave(&wdt_tst_b_spinlock, flagsb);\
	} else {\
		mutex_lock(&wdt_tst_a_mutex);\
	} \
} while (0)

#define WDT_TST_UNLOCK_B()	\
do {\
	if (WDT_TST_LOCK_SPINLOCK == wdt_tst_lock_type) {\
		spin_unlock_irqrestore(&wdt_tst_b_spinlock, flagsb);\
	} else {\
		mutex_unlock(&wdt_tst_a_mutex);\
	} \
} while (0)

static int hisi_wdt_tst_lock_a(void)
{
	unsigned long flagsa = 0, flagsb = 0;

	mlog_e("lock A to in\n");
	WDT_TST_LOCK_A();

	mlog_e("lock A in, flags=0x%x\n", (unsigned int)flagsa);
	mdelay(2000);
	mlog_e("lock B to in\n");
	WDT_TST_LOCK_B();

	mlog_e("during lock AB\n");

	WDT_TST_UNLOCK_A();
	mlog_e("lock A to out\n");
	WDT_TST_UNLOCK_B();
	mlog_e("lock A out\n");

	return 0;
}

static int hisi_wdt_tst_lock_b(void)
{
	unsigned long flagsa = 0, flagsb = 0;

	mlog_e("lock B to in\n");
	WDT_TST_LOCK_B();
	mlog_e("lock B in, flags=0x%x\n", (unsigned int)flagsb);
	mdelay(2000);
	mlog_e("lock A to in\n");
	WDT_TST_LOCK_A();

	mlog_e("during lock BA\n");

	WDT_TST_UNLOCK_A();
	mlog_e("lock B to out\n");
	WDT_TST_UNLOCK_B();
	mlog_e("lock B out\n");

	return 0;
}

static void hisi_wdt_tst_lock_a_work_func(struct work_struct *work)
{
	hisi_wdt_tst_lock_a();
}

static void hisi_wdt_tst_lock_b_work_func(struct work_struct *work)
{
	hisi_wdt_tst_lock_b();
}

/*
	WDT IRQ TEST
*/
static enum hrtimer_restart hisi_wdt_tst_irq_body(struct hrtimer *timer)
{
	mlog_e("in while\n");
	asm("b .");

	return HRTIMER_NORESTART;
}

static void hisi_wdt_tst_irq_hrtimer(void *data)
{
	hrtimer_init(&wdt_irq_tst_hrtimer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	wdt_irq_tst_hrtimer.function = hisi_wdt_tst_irq_body;
	hrtimer_start(&wdt_irq_tst_hrtimer,
		      ktime_set(1 /*second */ , 0 /*msecond */),
		      HRTIMER_MODE_REL | HRTIMER_MODE_PINNED);

}

/*
	test IF
	while in process
*/
int hisi_wdt_tst_proc(int cpu)
{
	if (!wdt_tst_enabled) {
		mlog_i("wdt tst not enabled\n");
		return 1;
	}

	/* cpu should = 0 */
	mlog_i("cpu = %d\n", cpu);
	smp_call_function_single(cpu, hisi_wdt_tst_proc_body, NULL, 0);

	return 0;
}

/*
	test IF
	dead lock
*/
int hisi_wdt_tst_lock(int type)
{
	if (!wdt_tst_enabled) {
		mlog_i("wdt tst not enabled\n");
		return 1;
	}

	switch (type) {
	case 0:/*spinlock */
		wdt_tst_lock_type = WDT_TST_LOCK_SPINLOCK;
		mlog_i("spinlock\n");
		break;
	case 1:/*mutex */
		wdt_tst_lock_type = WDT_TST_LOCK_MUTEX;
		mlog_i("mutex\n");
		break;
	default:
		wdt_tst_lock_type = WDT_TST_LOCK_NONE;
		mlog_i("none\n");
		break;
	}

	if (wdt_tst_lock_type != WDT_TST_LOCK_NONE) {
		queue_work_on(0 /*cpu 0 */ , wdt_tst_wq_a, &wdt_tst_w_a);
		queue_work_on(1 /*cpu 1 */ , wdt_tst_wq_b, &wdt_tst_w_b);
	}

	return 0;
}

/*
	test IF
	while in irq
*/
int hisi_wdt_tst_irq(int cpu)
{
	if (!wdt_tst_enabled) {
		mlog_i("wdt tst not enabled\n");
		return 1;
	}

	/* cpu should = 0 */
	mlog_i("cpu = %d\n", cpu);
	smp_call_function_single(cpu, hisi_wdt_tst_irq_hrtimer, NULL, 0);

	return 0;
}

static int __init hisi_mntn_test_module_init(void)
{
	/*
	   for lock test, spinlock
	 */
	spin_lock_init(&wdt_tst_a_spinlock);
	spin_lock_init(&wdt_tst_b_spinlock);

	wdt_tst_wq_a = create_workqueue("wdt_tst_wq_a");
	if (NULL == wdt_tst_wq_a) {
		mlog_e("wdt_tst_wq_a workqueue create failed\n");
		return -EFAULT;
	}
	INIT_WORK(&wdt_tst_w_a, hisi_wdt_tst_lock_a_work_func);

	wdt_tst_wq_b = create_workqueue("wdt_tst_wq_b");
	if (NULL == wdt_tst_wq_b) {
		mlog_e("wdt_tst_wq_b workqueue create failed\n");
		return -EFAULT;
	}
	INIT_WORK(&wdt_tst_w_b, hisi_wdt_tst_lock_b_work_func);

	/*
	   for lock test, mutex
	 */
	mutex_init(&wdt_tst_a_mutex);
	mutex_init(&wdt_tst_b_mutex);

	/* for lock test, semphore */

	wdt_tst_enabled = true;

	return 0;

}

static void __exit hisi_mntn_test_module_exit(void)
{
	wdt_tst_enabled = false;

	return;
}

module_init(hisi_mntn_test_module_init);
module_exit(hisi_mntn_test_module_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("WangLai.Shi");
MODULE_DESCRIPTION("mntn test");
