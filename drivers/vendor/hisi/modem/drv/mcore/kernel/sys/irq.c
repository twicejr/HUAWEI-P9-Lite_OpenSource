
#include <printk.h>
#include "irq.h"

typedef int (*funcptr)(int,int);

funcptr g_pIntSwitchHook = NULL;

void int_switch_hook_add(funcptr pHookFunc)
{
    g_pIntSwitchHook = pHookFunc;
}

void int_switch_hook_delete(void)
{
    g_pIntSwitchHook = NULL;
}

irqreturn_t handle_bad_irq(int irq, void *irq_data);

extern unsigned int __isr_vector;
struct irq_desc *irq_descs  = ((struct irq_desc *)&__isr_vector) + 16;

#if 0
void do_nvic()
{
	int irq = __get_IPSR() & 0xFF;
	struct irq_desc *desc = irq_to_desc(irq);
        if(g_pIntSwitchHook)
        {
            (g_pIntSwitchHook)(0,irq);
        }
	if (IRQ_HANDLED != desc->handler(irq, NULL))
	{
		(void)handle_bad_irq(irq,  NULL);
	}
	if(g_pIntSwitchHook)
        {
            (g_pIntSwitchHook)(1,irq);
        }
}
#endif

irqreturn_t handle_bad_irq(int irq, void *irq_data)
{
	UNUSED(irq_data);
	printk("irq: handle_bad_irq %d.\n",irq);
//	NVIC_DisableIRQ(irq_to_virq(irq));
	return IRQ_HANDLED;
}

int request_irq(int irq, irq_handler_t handler, unsigned long flags,
	    const char *name, void *dev)
{
	struct irq_desc *desc = irq_to_desc(irq);
	if(desc->handler == handle_bad_irq)
	{
		desc->handler = handler;
		if (!(flags & IRQF_DISABLED))
			enable_irq(irq);
		return 0;
	}
	else
	{
		printk("irq: request_irq fail irq:%d, name:%s.\n",irq, name);
		return -1;
	}
}

void free_irq(int irq, void *dev_id)
{
	UNUSED(dev_id);
	struct irq_desc *desc = irq_to_desc(irq);
	disable_irq(irq);
	desc->handler = handle_bad_irq;
}

