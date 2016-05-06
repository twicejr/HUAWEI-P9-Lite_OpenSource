/*lint --e{718,746}*/
#include <bsp_memmap.h>   
#include <osl_types.h>
#include <bsp_sysctrl.h>
#include <osl_bio.h>  
#include "mdrv_sysctrl.h" 

int mdrv_sysctrl_set_regval(unsigned int regAddr, unsigned int setData)
{
	writel(setData, HI_SYSSC_AO_BASE_ADDR + regAddr);
	return 0;
} 

int mdrv_sysctrl_get_regval(unsigned int regAddr, unsigned int * getData)
{
	if (NULL == getData)
	{
		/*lint -save -e18*/
		sc_pr_err("DRV_SYSCTRL_REG_GET:getData buffer is NULL!\n");
		/*lint -restore +e18*/
		return -1;
	}
	* getData = readl(HI_SYSSC_AO_BASE_ADDR + regAddr);

	return 0;
} 

