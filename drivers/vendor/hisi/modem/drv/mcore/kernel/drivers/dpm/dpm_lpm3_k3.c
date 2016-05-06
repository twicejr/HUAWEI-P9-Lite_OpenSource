/*lint --e{537,551}*/
#include "dpm_balong.h"
#include <bsp_ipc.h>
#include <bsp_icc.h>
#include <bsp_ipf.h>
#include <bsp_hardtimer.h>
#include <temperature.h>
#include <bsp_pmu_hi6561.h>
static u32 pm_suspend_flag ;
static u32 pm_resume_flag ;

/*二维数组用来记录可维可测信息:
  *0 suspend失败次数，
  *1 resume失败次数，
  *数组最后一项用于记录分别进入suspend和resume总次数
  */
__ao_data static u32 dpm_debug[DPM_BUTTON+1][2]={{0,0},{0,0},{0,0},{0,0},{0,0}};
/*lint --e{732}*/

/*各模块填写时，注意suspend顺序与resume顺序相反*/
static s32 enter_suspend_and_resume(u32 pm_msg)
{
	u32 ret = 0;
	pm_suspend_flag = 0;
	pm_resume_flag = 0;
	if(PMSG_SUSPEND==pm_msg){
		/*可维可测，记录进入suspend总次数*/
		dpm_debug[DPM_BUTTON][0]++;
		/*本分支回调各设备的suspend回调函数，顺序往下加*/

		ret = bsp_icc_suspend();
		if(ret != 0)
		{
			pm_suspend_flag = 1;
		    goto end;
		}
		ret=tem_protect_suspend();
		if(ret !=0)
		{
			pm_suspend_flag = 1;
			dpm_debug[DPM_TEM][0] +=1;
			goto end;
		}
		ret = ipf_drx_bak_reg();
		if(ret !=0)
		{
			pm_suspend_flag = 1;
			dpm_debug[DPM_IPF][0] +=1;
			goto tem_resume;
		}
		bsp_ipc_suspend();
    }
	else if(PMSG_RESUME==pm_msg){
		dpm_debug[DPM_BUTTON][1]++;/*可维可测，记录进入resume总次数*/
		/*本分支回调各设备的resume回调函数,顺序往上加*/
		bsp_ipc_resume();
		ipf_drx_restore_reg();
tem_resume:
		tem_protect_resume();


	}
end:
	if(PMSG_SUSPEND==pm_msg)
	{
		if(0==pm_suspend_flag)
			return DPM_OK;
		else
			return DPM_ERROR;
	}
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
#if 0
void bsp_dpm_show(void)
{
	int i = 0;
	printk("id\tsuspend_failed_times\tresume_failed_times\n");
	for(i=0;i<DPM_BUTTON;i++){
		printk("%d\t%d\t\t%d\n",i,dpm_debug[i][0],dpm_debug[i][1]);
	}
	printk("total suspend:%d\n total resume:%d\n",dpm_debug[DPM_BUTTON][0],dpm_debug[DPM_BUTTON][1]);
}
#endif
