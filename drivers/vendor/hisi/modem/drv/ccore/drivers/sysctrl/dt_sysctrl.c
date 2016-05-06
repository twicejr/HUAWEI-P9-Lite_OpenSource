/*************************************************************************
*   版权所有(C) 2008-2014, 深圳华为技术有限公司.
*
*   文 件 名 :  dt_sysctrl.c
*
*   作    者 :  n00261894
*
*   描    述 :  系统控制器从DTS获取数据模块
*
*   修改记录 :  2014年08月08日  v1.00  n00261894  创建
*************************************************************************/
#include <osl_types.h>
#include <of.h>
#include <bsp_sysctrl.h>

struct sysctrl_tag{
	void* addr_virt[sysctrl_max];
	unsigned long addr_phy[sysctrl_max];
	unsigned int reg_sum;
};
struct sysctrl_tag sysctrl;

#ifdef CONFIG_OF
static unsigned long reg_node_info_get(struct device_node *np, unsigned int sc_index)
{
	const __be32 *spec = NULL;
	const __be32 *prop = NULL;
	unsigned int cells_size = 0, len = 0;
	unsigned int na = 0, ns = 0;

	spec = of_get_property(np, "reg", (int *)&len);
	len /= 4;

	if (NULL == spec)
	{
		sc_pr_err("cannot find reg property\n");
		return 0;
	}

	prop = of_get_property(np, "#address-cells", NULL);
	if(NULL != prop)
	{
		na = be32_to_cpup(prop);
	}

	prop = of_get_property(np, "#size-cells", NULL);
	if(NULL != prop)
	{
		ns = be32_to_cpup(prop);
	}

	cells_size = na + ns;
	if(cells_size == 0)
	{
		na = 1;
		ns = 1;
		cells_size = na + ns;
	}
	if((sc_index * cells_size) > len)
	{
		sc_pr_err("sc_index = %d is out of range\n", sc_index);
		return 0;
	}

	return (unsigned long)of_read_number(spec + sc_index *cells_size , 1);
}

static void* virt_addr_lookup(unsigned long phy_addr)
{
	u32 i = 0;
	u32 addr = phy_addr & ~0xfff;

	for(i = 0; i < sysctrl.reg_sum; i++)
	{
		if(addr == sysctrl.addr_phy[i])
		{
			return (void*)((unsigned long)sysctrl.addr_virt[i] + phy_addr - sysctrl.addr_phy[i]);
		}
	}

	return 0;
}

void* bsp_sysctrl_addr_get(void* phy_addr){
	return (void*)virt_addr_lookup((unsigned long)phy_addr);
}

void* bsp_sysctrl_addr_byindex(BSP_SYSCTRL_INDEX sc_index){
	return (void*)sysctrl.addr_virt[sc_index];
}

void* bsp_sysctrl_addr_phy_byindex(BSP_SYSCTRL_INDEX sc_index){
	return (void*)sysctrl.addr_phy[sc_index];
}

void dt_sysctrl_init(void)
{
	unsigned int i;
	struct device_node *node = NULL;
	int ret = 0;

	node = of_find_compatible_node(NULL, NULL, "hisilicon,sysctrl_mdm");
	if (!node)
	{
		sc_pr_err("dts node not found!\n");
		return;
	}
	
	ret = of_property_read_u32(node, "reg_sum", &sysctrl.reg_sum);
	if(ret)
	{
		sc_pr_err("read reg_sum from dts is failed,ret = %d!\n", ret);
		return;
	}

	sysctrl.reg_sum = (sysctrl.reg_sum <= sysctrl_max) ? sysctrl.reg_sum : sysctrl_max;
	for(i = 0; i < sysctrl.reg_sum; i++)
	{
		sysctrl.addr_virt[i] = of_iomap(node, (int)i);
		if (0 == sysctrl.addr_virt[i])
		{
			sc_pr_err("of iomap fail!, index=%d\n", i);
			return;
		}
		sysctrl.addr_phy[i] = reg_node_info_get(node, i);
		if(sysctrl.addr_phy[i] == 0)
		{
			sc_pr_err("cann't find reg property!, index=%d\n", i);
			return;
		}
	}
	for(i = sysctrl.reg_sum; i < sysctrl_max; i++)
	{
		sysctrl.addr_virt[i] = sysctrl.addr_virt[sysctrl_ao];
		sysctrl.addr_phy[i] = sysctrl.addr_phy[sysctrl_ao];
	}
	
	sc_pr_info("ok\n");

}
#endif

