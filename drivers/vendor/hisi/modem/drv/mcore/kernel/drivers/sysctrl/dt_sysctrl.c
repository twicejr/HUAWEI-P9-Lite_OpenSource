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
#include <product_config.h>
#include <osl_types.h>
#include <osl_common.h>
#include <libfdt.h>
#include <bsp_sysctrl.h>

struct sysctrl_tag{
	void *addr[sysctrl_max];
	unsigned int reg_sum;
};
struct sysctrl_tag sysctrl;

#ifdef CONFIG_OF
void* bsp_sysctrl_addr_get(void* phy_addr){
	return phy_addr;
}

void* bsp_sysctrl_addr_byindex(BSP_SYSCTRL_INDEX index){
	return sysctrl.addr[index];
}

void* bsp_sysctrl_addr_phy_byindex(BSP_SYSCTRL_INDEX index){
	return sysctrl.addr[index];
}

void dt_sysctrl_init(void)
{
	u32 i;
	struct device_node *node = NULL;
	int ret = 0;
	void *reg_data[sysctrl_max*2];

	node = of_find_compatible_node(NULL, NULL, "hisilicon,sysctrl_m3");
	if (!node)
	{
		sc_pr_err("node not found\n");
		return;
	}
	
	ret = of_property_read_u32_array(node, "reg_sum", &sysctrl.reg_sum , 1);
	if(ret)
	{
		sc_pr_err("read reg_sum fail\n");
		return;
	}
	
	ret = of_property_read_u32_array(node, "reg", (void *)reg_data, sysctrl.reg_sum*2);
	if(ret)
	{
		sc_pr_err("read reg faile\n");
		return;
	}

	sysctrl.reg_sum = (sysctrl.reg_sum <= sysctrl_max) ? sysctrl.reg_sum : sysctrl_max;
	for(i = 0; i < sysctrl.reg_sum; i++)
	{
		sysctrl.addr[i] = reg_data[i*2];
		if(sysctrl.addr[i] == 0)
		{
			sc_pr_err("cann't find addr!index=%d\n", i);
			return;
		}
	}
	for(i = sysctrl.reg_sum; i < sysctrl_max; i++)
	{
		sysctrl.addr[i] = sysctrl.addr[sysctrl_ao];
	}

	sc_pr_info("ok\n");

}
#endif

