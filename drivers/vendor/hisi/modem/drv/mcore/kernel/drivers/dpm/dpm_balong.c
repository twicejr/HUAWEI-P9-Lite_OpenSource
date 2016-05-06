/*lint -save -e537*//*lint -save -e746*/
#include "dpm_balong.h"
#include <amon_balong.h>
#include <printk.h>
#include <bsp_ipc.h>
#include <bsp_ipf.h>
#include <socp_balong.h>
#include <ios_pd.h>
#include <bsp_uart.h>
#include <bsp_hkadc.h>
#include <m3_pm.h>
#include <bsp_hardtimer.h>
#include <temperature.h>
#include <wdt_balong.h>
#include <bsp_pmu.h>

static u32 pm_suspend_flag ;
static u32 pm_resume_flag ;

/*二维数组用来记录可维可测信息:
  *0 suspend失败次数，
  *1 resume失败次数，
  *数组最后一项用于记录分别进入suspend和resume总次数
  */
static u32 dpm_debug[DPM_BUTTON+1][2]={{0,0},{0,0},{0,0},{0,0},{0,0}};


/*各模块填写时，注意suspend顺序与resume顺序相反*/
static s32 enter_suspend_and_resume(u32 pm_msg)
{
	s32 ret = 0;
	pm_suspend_flag = 0;
    pm_resume_flag = 0;
	if(PMSG_SUSPEND==pm_msg){
		/*可维可测，记录进入suspend总次数*/
		dpm_debug[DPM_BUTTON][0]++;
		/*本分支回调各设备的suspend回调函数，顺序往下加*/
		writel(bsp_get_slice_value(), DPM_SRAM_TIMER1);
		ret=tem_protect_suspend();
		if(ret !=0)
		{
			pm_suspend_flag = 1;
			dpm_debug[DPM_TEM][0] +=1;
			goto end;
		}
		writel(bsp_get_slice_value(), DPM_SRAM_TIMER2);
		ret=bsp_socp_suspend();
		writel(bsp_get_slice_value(), DPM_SRAM_TIMER3);
		if(ret !=0)
		{
			pm_suspend_flag = 1;
			dpm_debug[DPM_SOCP][0] +=1;
			goto tem_resume;
		}
		bsp_ipc_suspend();
		bsp_amon_suspend();
		writel(bsp_get_slice_value(), DPM_SRAM_TIMER4);
		(void)uart_suspend_port();
		writel(bsp_get_slice_value(), DPM_SRAM_TIMER5);
		ret = ipf_drx_bak_reg();
		writel(bsp_get_slice_value(), DPM_SRAM_TIMER6);
		if(ret !=0)
		{
			pm_suspend_flag = 1;
			dpm_debug[DPM_IPF][0] +=1;
			goto uart_resume;
		}
        ret = bsp_pmu_suspend();
	    writel(bsp_get_slice_value(), DPM_SRAM_TIMER7);
        if(ret != 0)
        {
            pm_suspend_flag = 1;
            dpm_debug[DPM_PMU][0] +=1;
            goto ipf_resume;
        }
        bsp_wdt_suspend(0);

	}
	else if(PMSG_RESUME==pm_msg){
		dpm_debug[DPM_BUTTON][1]++;/*可维可测，记录进入resume总次数*/
		/*本分支回调各设备的resume回调函数,顺序往上加*/
		writel(bsp_get_slice_value(), DPM_SRAM_TIMER8);
        ret = bsp_pmu_resume();
		writel(bsp_get_slice_value(), DPM_SRAM_TIMER9);
        if(ret != 0)
        {
            pm_resume_flag = 1;
            dpm_debug[DPM_PMU][1] +=1;
            goto resume;
        }
	ipf_resume:
		ipf_drx_restore_reg();
		writel(bsp_get_slice_value(), DPM_SRAM_TIMER10);
    uart_resume:
		(void)uart_resume_port();
		writel(bsp_get_slice_value(), DPM_SRAM_TIMER11);
		bsp_amon_resume();
		bsp_ipc_resume();
		writel(bsp_get_slice_value(), DPM_SRAM_TIMER12);
		bsp_socp_resume();
		writel(bsp_get_slice_value(), DPM_SRAM_TIMER13);
	tem_resume:
		tem_protect_resume();
		writel(bsp_get_slice_value(), DPM_SRAM_TIMER14);
		bsp_hkadc_resume();
		writel(bsp_get_slice_value(), DPM_SRAM_TIMER15);
		bsp_wdt_resume();
	}
	end:
	if(PMSG_SUSPEND==pm_msg)
	{
		if(0==pm_suspend_flag)
			return DPM_OK;
		else
			return DPM_ERROR;
	}
    resume:
	if(PMSG_RESUME==pm_msg)
	{
        if(0==pm_resume_flag)
			return DPM_OK;
		else
			return DPM_ERROR;
	}
	return DPM_OK;
}

s32 dpm_suspend(void)
{
	s32 ret = 0;
	ret = enter_suspend_and_resume(PMSG_SUSPEND);
	return ret;
}
s32 dpm_resume(void)
{
	s32 ret = 0;
	ret = enter_suspend_and_resume(PMSG_RESUME);
	return ret;
}

s32 dpm_suspend_buck3off(void)
{
	return bsp_pmu_sdio_suspend();
}
s32 dpm_resume_buck3off(void)
{
	return bsp_pmu_sdio_resume();
}
#if 0
void bsp_dpm_show(void)
{
	int i = 0;
	printk("id\tsuspend_failed_times\tresume_failed_times\n");
	for(i=0;i<DPM_BUTTON;i++){
		printk("%d\t%d\t\t%d\n",i,dpm_debug[i][0],dpm_debug[i][1]);
	}
	printk("total suspend:%d\n resume:%d\n",dpm_debug[DPM_BUTTON][0],dpm_debug[DPM_BUTTON][1]);
}
#endif
/*lint -restore +e537*//*lint -restore +e746*/