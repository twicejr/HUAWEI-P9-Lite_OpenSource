#include <osl_types.h>
#include <osl_bio.h>
#include <osl_irq.h>
#include <bsp_gic_pm.h>

unsigned int gic_base_addr = 0;

#define GIC_CPUICR    (0x100 + 0x000)

void gic_cpu_disable(void)
{
    writel(0x0,gic_base_addr+GIC_CPUICR);
}
void gic_cpu_enable(void)
{
    writel(0x1,gic_base_addr+GIC_CPUICR);
}

unsigned int get_peri_base_addr(void)
{
    unsigned int peri_base_addr = 0;
    __asm__ __volatile("mrc p15,4,%0,c15,c0,0"
        :"=r"(peri_base_addr));
    return peri_base_addr;
}
/*用于GIC空间映射*/
extern VIRT_PHYS_MEM_S sysPhysMemDesc [];
void gic_init(void)
{
    /*获取GIC基址*/
	gic_base_addr = get_peri_base_addr();
	sysPhysMemDesc[MMU_MAP_GIC].uwVirtualAddr      = gic_base_addr;
	sysPhysMemDesc[MMU_MAP_GIC].uwPhysicalAddr     = gic_base_addr;
	sysPhysMemDesc[MMU_MAP_GIC].uwLen              = 0x2000;
	sysPhysMemDesc[MMU_MAP_GIC].uwInitialStateMask = MMU_STATEMASK_ALL;
	sysPhysMemDesc[MMU_MAP_GIC].uwInitialState     = MMU_STATE_RWX | OS_MMU_STATE_STRONGLY_ORDERED;    
}
