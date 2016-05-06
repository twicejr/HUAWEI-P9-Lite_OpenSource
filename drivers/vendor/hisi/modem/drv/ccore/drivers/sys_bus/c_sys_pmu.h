#ifndef __C_SYS_PMU_H__
#define __C_SYS_PMU_H__

#include <osl_spinlock.h>
#include <c_sys_bus_core.h>

#define SYS_PMU_PMNC_E		(1 << 0)
#define	SYS_PMU_PMNC_MASK		0x3f
#define	SYS_PMU_IDX_CYCLE_COUNTER	0
#define	SYS_PMU_IDX_COUNTER0	1
#define	SYS_PMU_EVTYPE_MASK	0xc00000ff
#define	SYS_PMU_EVTYPE_EVENT	0xff
#define	SYS_PMU_MAX_COUNTERS	32
#define	SYS_PMU_COUNTER_MASK	(SYS_PMU_MAX_COUNTERS - 1)
#define	SYS_PMU_PMNC_N_SHIFT	11
#define	SYS_PMU_PMNC_N_MASK	0x1f
#define	SYS_PMU_IDX_COUNTER_LAST	(SYS_PMU_IDX_CYCLE_COUNTER + g_sys_pmu.total_counter - 1)
#define SYS_PMU_PMNC_P		(1 << 1)
#define SYS_PMU_PMNC_C		(1 << 2)
#define	SYS_PMU_IDX_TO_COUNTER(x)	\
	    (((x) - SYS_PMU_IDX_COUNTER0) & SYS_PMU_COUNTER_MASK)
#define	SYS_PMU_FLAG_MASK		0xffffffff
#define	SYS_PMU_OVERFLOWED_MASK	SYS_PMU_FLAG_MASK
#define BIT(nr)			(1UL << (nr))

enum E_SYS_PMU_REG
{
    ARMv7_PMCR = 0,
    ARMv7_PMCNTENSET,
    ARMv7_PMCNTENCLR,
    ARMv7_PMOVSR,
    ARMv7_PMSWINC,
    ARMv7_PMSELR,
    ARMv7_PMCCNTR = 10,
    ARMv7_PMXEVTYPER,
    ARMv7_PMXEVCNTR,
    ARMv7_PMINTENSET = 20,
    ARMv7_PMINTENCLR,
};

struct sys_pmu_event
{
    u32 flag;
    u32 type;
    u64 counter;
};

struct sys_pmu
{
    struct device_node  *of_node;
    u32 total_counter;
    u32 irq;
    spinlock_t	pmu_lock;
    struct sys_pmu_event event[32];
};

u32 sys_pmu_read_cp15(enum E_SYS_PMU_REG reg);
void sys_pmu_init(void);
void sys_pmu_reset(void);
void sys_pmu_enable_event(u32 val, u32 idx);
void sys_pmu_start(void);
void sys_pmu_pmnc_dump_regs(void);
void sys_pmu_stop(void);

#endif /* __C_SYS_PMU_H__ */

