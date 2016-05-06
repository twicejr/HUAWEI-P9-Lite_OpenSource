#ifndef _PWRCTRL_MCA_PROT_H
#define _PWRCTRL_MCA_PROT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <linux/hisi/pm/hi6xxx-power-mca.h>
#include <linux/semaphore.h>

// FIXME: DANGEROUS! IRQ not safe! Check sem/lock.
#define IPC_TARGET_CPU_MCU 0 // FIXME:

/* Platform dependent functions. */
#define mca_sem_t                               struct semaphore
#define mca_sem_init(p_sem, val)                sema_init(p_sem, val)
#define mca_sem_up(p_sem)                       up(p_sem)
#define mca_sem_down(p_sem)                     down(p_sem)
#define mca_sem_down_timeout(p_sem, time_out)   down_timeout(p_sem, msecs_to_jiffies(time_out))
#define	mca_sem_del(p_sem)                             
#define mca_sem_count(p_sem)                    ((p_sem)->count)
#define mca_malloc(size)                        kzalloc(size, GFP_KERNEL)
#define mca_free(p)                             kfree(p)
#define mca_lock_irq()                          local_irq_disable()
#define mca_unlock_irq()                        local_irq_enable()
#define MCA_LOCAL

#define mca_valid_sid(sid)      (sid >= 0 && sid < MCA_MAX_SESSION_NUM)

struct mca_sdata
{
    union mca_udata*   p_rsp;
    mca_post_cb        post_cb;
    void*              private_data;
};

struct mca_sblock
{
    mca_sem_t          sem;
    struct mca_sdata   sdata;
};

#ifdef __cplusplus
}
#endif

#endif
