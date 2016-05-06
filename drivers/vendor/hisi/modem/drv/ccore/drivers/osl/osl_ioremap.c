#if defined(__OS_RTOSCK__)

#include <sre_mmu.h>

#include <osl_types.h>
#include <osl_bio.h>

/* device: strongly-ordered 寄存器都要使用该接口 */
void *ioremap(MMU_VA_T phy_addr, unsigned int len)
{
	MMU_VA_T virt_addr = phy_addr;
	u32 state          = OS_MMU_STATE_READ | OS_MMU_STATE_WRITE  | OS_MMU_STATE_STRONGLY_ORDERED;
	if(SRE_OK != SRE_MmuAssign(virt_addr, phy_addr, len, state))
	{
		return NULL;
	}
	else
	{
		return (void *)virt_addr;
	}
}

/* device: non-cacheable normal */
void *ioremap_wc(MMU_VA_T phy_addr, unsigned int len)
{
	MMU_VA_T virt_addr = phy_addr;
	u32 state          = OS_MMU_STATE_READ | OS_MMU_STATE_WRITE  | OS_MMU_STATE_EXE  | OS_MMU_STATE_CACHE_OFF;
	if(SRE_OK != SRE_MmuAssign(virt_addr, phy_addr, len, state))
	{
		return NULL;
	}
	else
	{
		return (void *)virt_addr;
	}
}

/* memory: normal */
void *ioremap_memory(MMU_VA_T phy_addr, unsigned int len)
{
	MMU_VA_T virt_addr = phy_addr;
	u32 state          = OS_MMU_STATE_READ | OS_MMU_STATE_WRITE  | OS_MMU_STATE_CACHE_WBNWA;
	if(SRE_OK != SRE_MmuAssign(virt_addr, phy_addr, len, state))
	{
		return NULL;
	}
	else
	{
		return (void *)virt_addr;
	}
}
#endif

