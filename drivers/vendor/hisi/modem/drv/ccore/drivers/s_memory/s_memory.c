
#include <securec.h>
#include <soc_memmap.h>
#include <bsp_om.h>
#include <bsp_shared_ddr.h>
#include <bsp_s_memory.h>

#define  s_mem_pr_err(fmt, ...) \
	(bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_MEM, "[s_mem]: <%s> "fmt, __FUNCTION__, ##__VA_ARGS__))
struct mem_ctrl g_mem_ctrl;

void bsp_shared_mem_init(void)
{	
	g_mem_ctrl.sram_phy_addr = (void*)HI_SRAM_MEM_ADDR;
	g_mem_ctrl.sram_mem_size  = HI_SRAM_SIZE;
	g_mem_ctrl.sram_virt_addr = (void*)ioremap_wc((MMU_VA_T)g_mem_ctrl.sram_phy_addr, g_mem_ctrl.sram_mem_size);

	g_mem_ctrl.sddr_phy_addr =  (void*)HI_SHARED_DDR_BASE_ADDR;
	g_mem_ctrl.sddr_mem_size  = HI_SHARED_DDR_SIZE;
	g_mem_ctrl.sddr_virt_addr = (void*)ioremap_wc((MMU_VA_T)g_mem_ctrl.sddr_phy_addr, g_mem_ctrl.sddr_mem_size);

#ifdef DDR_SEC_SHARED_ADDR
    (void)ioremap_wc((MMU_VA_T)DDR_SEC_SHARED_ADDR, DDR_SEC_SHARED_SIZE);
    /* 预留(4K)防止被踩，初始化为全F */
    (void)memset_s((void*)(SHM_SEC_BASE_ADDR + SHM_OFFSET_PROTECT_BARRIER), SHM_SIZE_PROTECT_BARRIER, 0xf, SHM_SIZE_PROTECT_BARRIER);
#endif

	s_mem_pr_err("ok!\n");
}

