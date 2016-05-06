
#ifndef __IRQ_M3_H__
#define __IRQ_M3_H__

#ifdef __cplusplus
extern "C" {
#endif
#include <osl_types.h>
#include "ARMCM3.h"

typedef enum {
	IRQ_NONE,
	IRQ_HANDLED
} irqreturn_t;

typedef irqreturn_t (*irq_handler_t)(int, void *);

struct irq_desc {
		irq_handler_t		handler;
};

#define irq_to_virq(irq)	(irq - 16)
#define irq_to_desc(irq)	(&irq_descs[irq_to_virq(irq)])

#define IRQF_DISABLED		0x00000020

int request_irq(int irq, irq_handler_t handler, unsigned long flags,
	    const char *name, void *dev);

void free_irq(int irq, void *dev_id);

static inline void disable_irq(int irq)
{
	NVIC_DisableIRQ(irq_to_virq(irq));
}

static inline void enable_irq(int irq)
{
	NVIC_EnableIRQ(irq_to_virq(irq));
}

static inline void set_pending(int irq)
{
	NVIC_SetPendingIRQ(irq_to_virq(irq));
}

static inline unsigned int get_pending(int irq)
{
	return NVIC_GetPendingIRQ(irq_to_virq(irq));
}

static inline void clear_pending_irq(int irq)
{
	NVIC_ClearPendingIRQ(irq_to_virq(irq));
}

static inline unsigned int in_interrupt()
{
	return __get_IPSR() & 0xFF;
}
static inline unsigned int get_irq()
{
	return __get_IPSR() & 0xFF;
}


#ifdef __cplusplus
}
#endif

#endif  /* __IRQ_M3_H__ */
