/* hi3xxx_irq_affinity.h */

#ifndef HI3XXX_IRQ_AFFINITY_H
#define HI3XXX_IIRQ_AFFINITY_H

#include <linux/errno.h>

#ifdef CONFIG_HI3XXX_IRQ_AFFINITY
extern void hisi_irqaffinity_status(void);
extern int hisi_irqaffinity_register(unsigned int irq, int cpu);
extern void hisi_irqaffinity_unregister(unsigned int irq);
#else
static inline int hisi_irqaffinity_register(unsigned int irq, int cpu) { return -ENOSYS; }
static inline void hisi_irqaffinity_unregister(unsigned int irq) { return; }
static inline void hisi_irqaffinity_status(void) { return; }
#endif /* CONFIG_HI3XXX_IRQ_AFFINITY */
#endif /* HI3XXX_IRQ_AFFINITY_H */
