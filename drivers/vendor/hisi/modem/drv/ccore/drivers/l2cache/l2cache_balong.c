
#include <sre_cache.h>
#include <of.h>
#include <osl_bio.h>
#include <bsp_l2cache.h>

#define l2cache_trace(level, fmt, ...)      (bsp_trace(level, BSP_MODU_L2CACHE, "[l2cache]:<%s> <%d> "fmt, __FUNCTION__,__LINE__, ##__VA_ARGS__))

u32 l2cache_addr = 0;

/* for mmu mapping on l2cache*/
extern VIRT_PHYS_MEM_S sysPhysMemDesc [];

void l2cache_HardBootInit(void)
{

	u64 start = 0;
    u64 size = 0;
    u32 ret = 0;
	struct device_node *l2cache_node = NULL;
    const char *l2cache_name = {"arm,pl310-cache"};
    
	l2cache_node = of_find_compatible_node(NULL, NULL, l2cache_name);
	if (!l2cache_node)
	{
        l2cache_trace(BSP_LOG_LEVEL_ERROR, "of_find_compatible_node l2cache not found.\r\n");
        return;
	}

    ret = of_reg_info_get(l2cache_node, 0, &start, &size);
    if(0 != ret)
    {
        l2cache_trace(BSP_LOG_LEVEL_ERROR, "l2cache of_reg_info_get failed.\r\n");
        return;
    }
    
    l2cache_addr = (u32)start;

	sysPhysMemDesc[MMU_MAP_L2CACHE].uwVirtualAddr      = l2cache_addr;
	sysPhysMemDesc[MMU_MAP_L2CACHE].uwPhysicalAddr     = l2cache_addr;
	sysPhysMemDesc[MMU_MAP_L2CACHE].uwLen              = (u32)size;
	sysPhysMemDesc[MMU_MAP_L2CACHE].uwInitialStateMask = MMU_STATEMASK_ALL;
	sysPhysMemDesc[MMU_MAP_L2CACHE].uwInitialState     = MMU_STATE_RW | OS_MMU_STATE_STRONGLY_ORDERED;

    ret = SRE_CacheInit(l2cache_addr);
    if(SRE_OK != ret)
    {
        l2cache_trace(BSP_LOG_LEVEL_ERROR, "SRE_CacheInit failed,errNo:0x%x\r\n",ret);
        return;
    }
    return;
}




