#ifndef __HISILICON_CORE_H
#define __HISILICON_CORE_H

#include <linux/init.h>

extern void __iomem *hs_sctrl_base;
extern void __iomem *hs_secram_va_base;
extern void __iomem *hs_a9per_va_base;
extern void __iomem *hs_pctrl_va_base;
extern void __iomem *hs_pmuspi_va_base;

extern void hs_set_cpu_jump(int cpu, void *jump_addr);
extern int hs_get_cpu_jump(int cpu);
extern void secondary_startup(void);
extern void hs_map_io(void);
extern struct smp_operations hs_smp_ops;
extern void hs_restart(char mode, const char *cmd);

extern void __init hs_hotplug_init(void);
extern void hs_cpu_die(unsigned int cpu);
extern int hs_cpu_kill(unsigned int cpu);
extern void hs_set_cpu(int cpu, bool enable);

#ifdef CONFIG_PM
extern void pmulowpower(int isuspend);
#endif

#endif
