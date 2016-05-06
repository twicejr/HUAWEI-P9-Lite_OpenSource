#include <of.h>
#include <osl_irq.h>
#include "securec.h"
#include <c_sys_pmu.h>


struct sys_pmu g_sys_pmu;

/* idx和counter之间的关系
*idx = counter +1  0x1F五位
*counter是配置到寄存器的值
*/

u32 sys_pmu_pmnc_counter_valid(u32 idx)
{
	return idx >= SYS_PMU_IDX_CYCLE_COUNTER &&
		idx <= SYS_PMU_IDX_COUNTER_LAST;
}

u32 sys_pmu_pmnc_counter_has_overflowed(u32 pmnc, int idx)
{
	return pmnc & BIT(SYS_PMU_IDX_TO_COUNTER(idx));
}

u32 sys_pmu_read_cp15(enum E_SYS_PMU_REG reg)
{
    u32 val = 0;

    switch(reg)
    {
        case ARMv7_PMCR:
            asm volatile("mrc p15, 0, %0, c9, c12, 0" : "=r"(val));
            break;
        case ARMv7_PMCNTENSET:
            asm volatile("mrc p15, 0, %0, c9, c12, 1" : "=r"(val));
            break;
        case ARMv7_PMCNTENCLR:
            asm volatile("mrc p15, 0, %0, c9, c12, 2" : "=r"(val));
            break;
        case ARMv7_PMOVSR:
            asm volatile("mrc p15, 0, %0, c9, c12, 3" : "=r"(val));
            break;
        case ARMv7_PMSELR:
            asm volatile("mrc p15, 0, %0, c9, c12, 5" : "=r"(val));
            break;
        case ARMv7_PMCCNTR:
            asm volatile("mrc p15, 0, %0, c9, c13, 0" : "=r"(val));
            break;
        case ARMv7_PMXEVTYPER:
            asm volatile("mrc p15, 0, %0, c9, c13, 1" : "=r"(val));
            break;
        case ARMv7_PMXEVCNTR:
            asm volatile("mrc p15, 0, %0, c9, c13, 2" : "=r"(val));
            break;
        case ARMv7_PMINTENSET:
            asm volatile("mrc p15, 0, %0, c9, c14, 1" : "=r"(val));
            break;
        default:
            sys_bus_trace("not support reg = %d\n", reg);
            break;
    }

    return val;
}

void sys_pmu_write_cp15(enum E_SYS_PMU_REG reg, u32 val)
{
    switch(reg)
    {
        case ARMv7_PMCR:
            val &= SYS_PMU_PMNC_MASK;
	        isb();
            asm volatile("mcr p15, 0, %0, c9, c12, 0" : : "r"(val));
            break;
        case ARMv7_PMCNTENSET:
            asm volatile("mcr p15, 0, %0, c9, c12, 1" : : "r"(val));
            break;
        case ARMv7_PMCNTENCLR:
            asm volatile("mcr p15, 0, %0, c9, c12, 2" : : "r"(val));
            break;
        case ARMv7_PMOVSR:
            asm volatile("mcr p15, 0, %0, c9, c12, 3" : : "r"(val));
            break;
        case ARMv7_PMSELR:
            asm volatile("mcr p15, 0, %0, c9, c12, 5" : : "r"(val));
            break;
        case ARMv7_PMXEVTYPER:
            asm volatile("mcr p15, 0, %0, c9, c13, 1" : : "r"(val));
            break;
        case ARMv7_PMINTENSET:
            asm volatile("mcr p15, 0, %0, c9, c14, 1" : : "r"(val));
            break;
        case ARMv7_PMINTENCLR:
            asm volatile("mcr p15, 0, %0, c9, c14, 2" : : "r"(val));
            break;
        default:
            sys_bus_trace("not support reg = %d\n", reg);
            break;
    }

    isb();
}

void sys_pmu_pmnc_select_counter(int idx)
{
    u32 counter;

    counter = SYS_PMU_IDX_TO_COUNTER(idx);
    sys_pmu_write_cp15(ARMv7_PMSELR, counter);
}

void sys_pmu_pmnc_write_evtsel(u32 idx, u32 val)
{
    u32 counter;

    sys_pmu_pmnc_select_counter(idx);
    val &= SYS_PMU_EVTYPE_MASK;
    sys_pmu_write_cp15(ARMv7_PMXEVTYPER, val);
    counter = SYS_PMU_IDX_TO_COUNTER(idx);
    g_sys_pmu.event[counter].type = val;
}

u32 sys_pmu_read_counter(u32 idx)
{
	u32 val = 0;

	if (!sys_pmu_pmnc_counter_valid(idx))
	{
		sys_bus_trace("reading wrong counter %d\n", idx);
	}
	else if (idx == SYS_PMU_IDX_CYCLE_COUNTER)
	{
        val = sys_pmu_read_cp15(ARMv7_PMCCNTR);
	}
	else
	{
        val = sys_pmu_read_cp15(ARMv7_PMXEVCNTR);
	}

	return val;
}

void sys_pmu_pmnc_enable_counter(u32 idx)
{
	u32 counter = SYS_PMU_IDX_TO_COUNTER(idx);
    sys_pmu_write_cp15(ARMv7_PMCNTENSET, BIT(counter));
    g_sys_pmu.event[counter].flag = 1;
}

void sys_pmu_pmnc_disable_counter(u32 idx)
{
    u32 counter;

    counter = SYS_PMU_IDX_TO_COUNTER(idx);
    sys_pmu_write_cp15(ARMv7_PMCNTENCLR, BIT(counter));
    g_sys_pmu.event[counter].flag = 0;
}

u32 sys_pmu_num_of_event_counters(void)
{
    u32 cnt = 0;

    cnt = sys_pmu_read_cp15(ARMv7_PMCR);
    cnt = (cnt >> SYS_PMU_PMNC_N_SHIFT) & SYS_PMU_PMNC_N_MASK;

    return cnt+1;
}

void sys_pmu_pmnc_enable_intens(u32 idx)
{
	u32 counter = SYS_PMU_IDX_TO_COUNTER(idx);
    sys_pmu_write_cp15(ARMv7_PMINTENSET, BIT(counter));
}

void sys_pmu_pmnc_disable_intens(u32 idx)
{
	u32 counter = SYS_PMU_IDX_TO_COUNTER(idx);
    sys_pmu_write_cp15(ARMv7_PMINTENCLR, BIT(counter));
    sys_pmu_write_cp15(ARMv7_PMOVSR, BIT(counter));
}

void sys_pmu_enable_event(u32 val, u32 idx)
{
    unsigned long flags;

    if (!sys_pmu_pmnc_counter_valid(idx))
    {
		sys_bus_trace("wrong idx %d\n", idx);
		return;
	}

	spin_lock_irqsave(&g_sys_pmu.pmu_lock, flags);

	sys_pmu_pmnc_disable_counter(idx);

	if (idx != SYS_PMU_IDX_CYCLE_COUNTER)
		sys_pmu_pmnc_write_evtsel(idx, val);

	sys_pmu_pmnc_enable_intens(idx);

	sys_pmu_pmnc_enable_counter(idx);

	spin_unlock_irqrestore(&g_sys_pmu.pmu_lock, flags);
}

void sys_pmu_disable_event(u32 idx)
{
	unsigned long flags;

	if (!sys_pmu_pmnc_counter_valid(idx))
    {
		sys_bus_trace("wrong idx %d\n", idx);
		return;
	}

	spin_lock_irqsave(&g_sys_pmu.pmu_lock, flags);

	sys_pmu_pmnc_disable_counter(idx);

	sys_pmu_pmnc_disable_intens(idx);

	spin_unlock_irqrestore(&g_sys_pmu.pmu_lock, flags);
}

void sys_pmu_start(void)
{
	unsigned long flags;
    u32 pmnc = 0;
    u32 counter = SYS_PMU_IDX_TO_COUNTER(0);

	spin_lock_irqsave(&g_sys_pmu.pmu_lock, flags);


    g_sys_pmu.event[counter].flag = 1;
    g_sys_pmu.event[counter].type = 0x1f;

    pmnc = sys_pmu_read_cp15(ARMv7_PMCR);
	pmnc |= SYS_PMU_PMNC_E;
	sys_pmu_write_cp15(ARMv7_PMCR, pmnc);

	spin_unlock_irqrestore(&g_sys_pmu.pmu_lock, flags);
}

void sys_pmu_stop(void)
{
	unsigned long flags;
    u32 pmnc = 0;

	spin_lock_irqsave(&g_sys_pmu.pmu_lock, flags);

    pmnc = sys_pmu_read_cp15(ARMv7_PMCR);
	pmnc &= ~SYS_PMU_PMNC_E;
	sys_pmu_write_cp15(ARMv7_PMCR, pmnc);

	spin_unlock_irqrestore(&g_sys_pmu.pmu_lock, flags);
}

void sys_pmu_pmnc_dump_regs(void)
{
	u32 idx = 0;
    u32 counter = 0;

	sys_bus_trace("PMNC registers dump:\n");
	sys_bus_trace("PMNC  =0x%08x\n", sys_pmu_read_cp15(ARMv7_PMCR));
	sys_bus_trace("CNTENS=0x%08x\n", sys_pmu_read_cp15(ARMv7_PMCNTENSET));
	sys_bus_trace("INTENS=0x%08x\n", sys_pmu_read_cp15(ARMv7_PMINTENSET));
	sys_bus_trace("PMOVSR=0x%08x\n", sys_pmu_read_cp15(ARMv7_PMOVSR));
	sys_bus_trace("SELECT=0x%08x\n", sys_pmu_read_cp15(ARMv7_PMSELR));
	sys_bus_trace("CCNT  =0x%08x\n", sys_pmu_read_cp15(ARMv7_PMCCNTR));
    sys_bus_trace("CCNT over_val=0x%08x%08x\n", \
        *((u32*)&g_sys_pmu.event[0x1f].counter+1), *((u32*)&g_sys_pmu.event[0x1f].counter));
	for (idx=SYS_PMU_IDX_COUNTER0; idx<SYS_PMU_IDX_COUNTER_LAST; idx++)
    {
        counter = SYS_PMU_IDX_TO_COUNTER(idx);
		sys_pmu_pmnc_select_counter(idx);
		sys_bus_trace("CNT[%d] count =0x%08x\n",
            counter, sys_pmu_read_cp15(ARMv7_PMXEVCNTR));
		sys_bus_trace("CNT[%d] evtsel=0x%08x\n",
			counter, sys_pmu_read_cp15(ARMv7_PMXEVTYPER));
        sys_bus_trace("over val = 0x%08x%08x\n", \
            *((u32*)&g_sys_pmu.event[counter].counter+1), *((u32*)&g_sys_pmu.event[counter].counter));
	}
}

u32 sys_pmu_pmnc_getreset_flags(void)
{
	u32 val;

    val = sys_pmu_read_cp15(ARMv7_PMOVSR);
    sys_pmu_write_cp15(ARMv7_PMOVSR, val);

	return val;
}

int sys_pmu_pmnc_has_overflowed(u32 pmnc)
{
	return pmnc & SYS_PMU_OVERFLOWED_MASK;
}

void sys_pmu_reset(void)
{
	u32 idx = 0;
    u32 counter = 0;

	for (idx=SYS_PMU_IDX_CYCLE_COUNTER; idx<SYS_PMU_IDX_COUNTER_LAST; idx++)
    {
		sys_pmu_pmnc_disable_counter(idx);
		sys_pmu_pmnc_disable_intens(idx);
        counter = SYS_PMU_IDX_TO_COUNTER(idx);
        g_sys_pmu.event[counter].counter = 0;
	}

    sys_pmu_write_cp15(ARMv7_PMCR, SYS_PMU_PMNC_P | SYS_PMU_PMNC_C);
}

void sys_pmu_handler(void)
{
	u32 pmnc = 0;
    u32 idx = 0;
    u32 counter = 0;
    u64 cnt = 0xFFFFFFFF;

	pmnc = sys_pmu_pmnc_getreset_flags();
    //sys_bus_trace("sys_pmu_handler pmnc = 0x%x\n", pmnc);

	if (!sys_pmu_pmnc_has_overflowed(pmnc))
		return;

	for (idx=SYS_PMU_IDX_CYCLE_COUNTER; idx<SYS_PMU_IDX_COUNTER_LAST; idx++)
	{
		if (!sys_pmu_pmnc_counter_has_overflowed(pmnc, idx))
			continue;
        counter = SYS_PMU_IDX_TO_COUNTER(idx);
        g_sys_pmu.event[counter].counter += cnt;
        /*sys_bus_trace("counter = 0x%02x , type = 0x%x, val = 0x%08x%08x\n",  counter, \
                 g_sys_pmu.event[counter].type,*((u32*)&g_sys_pmu.event[counter].counter+1), *((u32*)&g_sys_pmu.event[counter].counter));*/
	}
}

void sys_pmu_init(void)
{
    int ret = 0;
    u32 irq = 0;
    struct device_node *np = NULL;

    (void)memset_s((void*)&g_sys_pmu, sizeof(struct sys_pmu), 0, sizeof(struct sys_pmu));

    np = of_find_compatible_node(NULL, NULL, "sys_bus, sys_pmu");
    if (!np)
    {
        sys_bus_trace("find sys_pmu node error\n");
        return;
    }
    g_sys_pmu.of_node = np;

    irq = irq_of_parse_and_map(np, 0);
    if(!irq)
    {
        sys_bus_trace("get irq num error\n");
        return;
    }
    g_sys_pmu.irq = irq;

    g_sys_pmu.total_counter = sys_pmu_num_of_event_counters() + 1;
    spin_lock_init(&g_sys_pmu.pmu_lock);

	ret = request_irq(g_sys_pmu.irq, (irq_handler_t)sys_pmu_handler, 0, "sys_pmu", NULL);
	if(ret != 0)
	{
        sys_bus_trace("request_irq failed! \n");
	}
}

