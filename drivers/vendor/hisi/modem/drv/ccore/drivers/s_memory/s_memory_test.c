
#include <osl_types.h>
#include <bsp_om.h>
#include <bsp_s_memory.h>

#define  s_mem_test_info(fmt, ...) \
    (bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_MEM, "[s_mem_test]: <%s> "fmt, __FUNCTION__, ##__VA_ARGS__))

void s_ram_get_test(void* val)
{
	void* tmp;
	tmp = bsp_sram_addr_get(val);
	s_mem_test_info("sram_phy_addr = 0x%x \n",g_mem_ctrl.sram_phy_addr);
	s_mem_test_info("sram_virt_addr = 0x%x \n",g_mem_ctrl.sram_virt_addr);
	s_mem_test_info("sram_mem_size = 0x%x \n",g_mem_ctrl.sram_mem_size);
	s_mem_test_info("set val is 0x%x,return val is 0x%x \n",val,tmp);
}

void s_ddr_get_test(void* val)
{
	void* tmp;
	tmp = bsp_sddr_addr_get(val);
	s_mem_test_info("sddr_phy_addr = 0x%x \n",g_mem_ctrl.sddr_phy_addr);
	s_mem_test_info("sddr_virt_addr = 0x%x \n",g_mem_ctrl.sddr_virt_addr);
	s_mem_test_info("sddr_mem_size = 0x%x \n",g_mem_ctrl.sddr_mem_size);
	s_mem_test_info("set val is 0x%x,return val is 0x%x \n",val,tmp);
}

