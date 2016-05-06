/*************************************************************************
*   版权所有(C) 2008-2013, 深圳华为技术有限公司.
*
*   文 件 名 :  dpm_balong.c.c
*
*   作    者 :  lixiaojie l00227190
*
*   描    述 :  本文件主要完成C 核dpm接口实现
*
*   修改记录 :  2013年6月18日  v1.00  l00227190  创建
*************************************************************************/
/*lint --e{530, 801,830,539}*/

#include <securec.h>
#include <bsp_dpm.h>
#include <bsp_hardtimer.h>
#include <bsp_dump_drv.h>
#include <bsp_pm_om.h>
#include "dpm_balong.h"

extern struct dpm_control dpm_ctrl;
/*在串口调试使用*/
s32 bsp_dpm_suspend_single(char *dev_name)
{
	s32 ret = 0;
	struct dpm_device *cur;
	unsigned long flags = 0;
	if(NULL == dev_name)
	{
		dpm_print("null para\n");
		return ERROR;
	}
	else
	{
		spin_lock_irqsave(&(dpm_ctrl.dpm_list_mtx),flags);/*lint !e40*/
		list_for_each_entry(cur,&(dpm_ctrl.dpm_list),entry)
		{
			ret = strcmp(cur->device_name,dev_name);
			if(0==ret)
			{
				dpm_ctrl.device_name = dev_name;
				break;
			}
		}
		/*如果未查到匹配项返回错误*/
		if(&cur->entry == &(dpm_ctrl.dpm_list))
		{
			dpm_print("dev not in list\n");
			goto failed;
		}
		if(cur->prepare)
		{
			dpm_ctrl.current_callback = cur->prepare;
			dpm_ctrl.flag = 1;
			cur->debug_time[PREPARE][0]=bsp_get_slice_value();
			ret = cur->prepare(cur);
			cur->debug_time[PREPARE][1]=bsp_get_slice_value();
			dpm_ctrl.flag = 0;
			if(OK!=ret)
			{
				cur->debug_count[PREPARE]++;
				goto failed;
			}
		}
		/*prepare成功执行后，移入prepared链表*/
		list_move_tail(&cur->entry,&(dpm_ctrl.dpm_prepared_list));
		if(cur->suspend_early)
		{
			dpm_ctrl.current_callback = cur->suspend_early;
			dpm_ctrl.flag = 1;
			cur->debug_time[SUS_EARLY][0]=bsp_get_slice_value();
			ret = cur->suspend_early(cur);
			cur->debug_time[SUS_EARLY][1]=bsp_get_slice_value();
			dpm_ctrl.flag = 0;
			if(OK!=ret)
			{
				cur->debug_count[SUS_EARLY]++;
				if(cur->complete)
				{
					dpm_ctrl.current_callback = cur->suspend;
					dpm_ctrl.flag = 1;
					cur->debug_time[COMPLETE][0]=bsp_get_slice_value();
					ret = cur->complete(cur);
					cur->debug_time[COMPLETE][1]=bsp_get_slice_value();
					dpm_ctrl.flag = 0;
					if(ret != OK)
					{
						cur->debug_count[COMPLETE]++;
					}
				}
				goto failed;
			}
		}
		list_move_tail(&cur->entry,&(dpm_ctrl.dpm_sus_early_list));
		if(cur->suspend)
		{
			dpm_ctrl.current_callback = cur->suspend;
			dpm_ctrl.flag = 1;
			cur->debug_time[SUSPEND][0]=bsp_get_slice_value();
			ret = cur->suspend(cur);
			cur->debug_time[SUSPEND][1]=bsp_get_slice_value();
			dpm_ctrl.flag = 0;
			if(OK!=ret)
			{
				cur->debug_count[SUSPEND]++;
				if(cur->resume_late)
				{
					dpm_ctrl.current_callback = cur->resume_late;
					dpm_ctrl.flag = 1;
					cur->debug_time[RES_LATE][0]=bsp_get_slice_value();
					ret = cur->resume_late(cur);
					cur->debug_time[RES_LATE][1]=bsp_get_slice_value();
					dpm_ctrl.flag = 0;
					if(ret != OK)
					{
						cur->debug_count[RES_LATE]++;
					}
					goto failed;
				}
				if(cur->complete)
				{
					dpm_ctrl.current_callback = cur->suspend;
					dpm_ctrl.flag = 1;
					cur->debug_time[COMPLETE][0]=bsp_get_slice_value();
					/* coverity[copy_paste_error] */
					ret = cur->complete(cur);
					cur->debug_time[COMPLETE][1]=bsp_get_slice_value();
					dpm_ctrl.flag = 0;
					if(ret != OK)
					{
						cur->debug_count[COMPLETE]++;
					}
					goto failed;
				}				
			}
		}
		/*suspend成功执行后，移入suspend链表*/
		list_move_tail(&cur->entry,&(dpm_ctrl.dpm_suspend_list));
		if(cur->suspend_late)
		{
			dpm_ctrl.current_callback = cur->suspend_late;
			dpm_ctrl.flag = 1;
			cur->debug_time[LATE][0]=bsp_get_slice_value();
			ret = cur->suspend_late(cur);
			cur->debug_time[LATE][1]=bsp_get_slice_value();
			dpm_ctrl.flag = 0;
			if(OK!=ret)
			{
				cur->debug_count[LATE]++;
				if(cur->resume)
				{
					dpm_ctrl.current_callback = cur->resume;
					dpm_ctrl.flag = 1;
					cur->debug_time[RESUME][0]=bsp_get_slice_value();
					ret = cur->resume(cur);
					cur->debug_time[RESUME][1]=bsp_get_slice_value();
					dpm_ctrl.flag = 0;
					if(ret != OK)
					{
						cur->debug_count[RESUME]++;
					}
					goto failed;
				}
				if(cur->resume_late)
				{
					dpm_ctrl.current_callback = cur->resume_late;
					dpm_ctrl.flag = 1;
					cur->debug_time[RES_LATE][0]=bsp_get_slice_value();
					ret = cur->resume_late(cur);
					cur->debug_time[RES_LATE][1]=bsp_get_slice_value();
					dpm_ctrl.flag = 0;
					if(ret != OK)
					{
						cur->debug_count[RES_LATE]++;
					}
					goto failed;
				}
				if(cur->complete)
				{
					dpm_ctrl.current_callback = cur->complete;
					dpm_ctrl.flag = 1;
					cur->debug_time[COMPLETE][0]=bsp_get_slice_value();
					/* coverity[original] */
					ret = cur->complete(cur);
					cur->debug_time[COMPLETE][1]=bsp_get_slice_value();
					dpm_ctrl.flag = 0;
					if(ret != OK)
					{
						cur->debug_count[COMPLETE]++;
					}
					goto failed;
				}		
			}
		}
		/*suspend late成功执行后，移入late early链表*/
		list_move_tail(&cur->entry,&(dpm_ctrl.dpm_late_early_list));
		spin_unlock_irqrestore(&(dpm_ctrl.dpm_list_mtx),flags);/*lint !e40*/
		return OK;
	}
	failed:
		spin_unlock_irqrestore(&(dpm_ctrl.dpm_list_mtx),flags);/*lint !e40*/
		return ERROR;
}
/*在串口调试使用*/
s32 bsp_dpm_resume_single(char *dev_name)
{
	s32 ret = 0;
	struct dpm_device *cur;
	unsigned long flags = 0;
	if(NULL == dev_name)
	{
		dpm_print("[%s]:null para\n");
		return ERROR;
	}
	else
	{
		spin_lock_irqsave(&(dpm_ctrl.dpm_list_mtx),flags);/*lint !e40*/
		list_for_each_entry(cur,&(dpm_ctrl.dpm_late_early_list),entry)
		{
			ret = strcmp(cur->device_name,dev_name);
			if(0==ret)
			{
				dpm_ctrl.device_name = dev_name;
				break;
			}
		}
		/*如果未查到匹配项返回错误*/
		if(&cur->entry == &(dpm_ctrl.dpm_late_early_list))
		{
			dpm_print("dev not in list\n");
			goto failed;
		}
		if(cur->resume_early)
		{
			dpm_ctrl.current_callback = cur->resume_early;
			dpm_ctrl.flag = 1;
			cur->debug_time[EARLY][0]=bsp_get_slice_value();
			ret = cur->resume_early(cur);
			cur->debug_time[EARLY][1]=bsp_get_slice_value();
			dpm_ctrl.flag = 0;
			if(OK != ret)
			{
				cur->debug_count[EARLY]++;
				goto failed;
			}
		}
		/*resume early 成功执行后，移入到suspend链表*/
		list_move(&cur->entry,&(dpm_ctrl.dpm_suspend_list));
		if(cur->resume)
		{
			dpm_ctrl.current_callback = cur->resume;
			dpm_ctrl.flag = 1;
			cur->debug_time[RESUME][0]=bsp_get_slice_value();
			ret = cur->resume(cur);
			cur->debug_time[RESUME][1]=bsp_get_slice_value();
			dpm_ctrl.flag = 0;
			if(OK != ret)
			{
				cur->debug_count[RESUME]++;
				goto failed;
			}
		}
		/*resume成功执行后，移入到prepared链表*/
		list_move(&cur->entry,&(dpm_ctrl.dpm_sus_early_list));
		if(cur->resume_late)
		{
			dpm_ctrl.current_callback = cur->resume_late;
			dpm_ctrl.flag = 1;
			cur->debug_time[RES_LATE][0]=bsp_get_slice_value();
			ret = cur->resume_late(cur);
			cur->debug_time[RES_LATE][1]=bsp_get_slice_value();
			dpm_ctrl.flag = 0;
			if(OK != ret)
			{
				cur->debug_count[RES_LATE]++;
				goto failed;
			}
		}
		/*resume成功执行后，移入到prepared链表*/
		list_move(&cur->entry,&(dpm_ctrl.dpm_prepared_list));
		if(cur->complete)
		{
			dpm_ctrl.current_callback = cur->complete;
			dpm_ctrl.flag = 1;
			cur->debug_time[COMPLETE][0]=bsp_get_slice_value();
			ret = cur->complete(cur);
			cur->debug_time[COMPLETE][1]=bsp_get_slice_value();
			dpm_ctrl.flag = 0;
			if(OK != ret)
			{
				cur->debug_count[COMPLETE]++;
				goto failed;
			}
		}
		/*complete成功执行后，移入到dpm_list链表*/
		list_move(&cur->entry,&(dpm_ctrl.dpm_list));
		spin_unlock_irqrestore(&(dpm_ctrl.dpm_list_mtx),flags);/*lint !e40*/
		return OK;
	}
	failed:
		spin_unlock_irqrestore(&(dpm_ctrl.dpm_list_mtx),flags);/*lint !e40*/
		return ERROR;
}

void bsp_dpm_help()
{
    
    dpm_print("dpm cnt 0x%x\n",dpm_ctrl.dpm_count[DPM_CNT_S_TOTAL]);
    dpm_print("dpm dump addr 0x%x\n",DPM_DUMP_START);
    dpm_print("for more info try: %s\n",__FUNCTION__);
}

void bsp_dpm_show()
{
	struct dpm_device *dev;/*lint !e830*/
	dpm_print("devnode_name=%s,current_callback = 0x%x,  flag = %d\n",dpm_ctrl.device_name,dpm_ctrl.current_callback,dpm_ctrl.flag);
	dpm_print("[dpm count] suspend:%d  resume:%d\n",\
            dpm_ctrl.dpm_count[DPM_CNT_S_TOTAL],dpm_ctrl.dpm_count[DPM_CNT_R_TOTAL]);
	dpm_print("[dpm count] pre_err:%d  sus_early_err:%d  sus_err:%d late_err:%d  \n",\
            dpm_ctrl.dpm_count[DPM_FAIL_CNT_S_PREPARE],dpm_ctrl.dpm_count[DPM_FAIL_CNT_S_EARLY],\
            dpm_ctrl.dpm_count[DPM_FAIL_CNT_S_SUSPEND],dpm_ctrl.dpm_count[DPM_FAIL_CNT_S_LATE]);
	dpm_print("-------------------dpm list info:  dev_info:-----------------------\n");
	list_for_each_entry(dev,&(dpm_ctrl.dpm_list),entry)
	{
		dpm_print("[%s]:\n",dev->device_name);
        if(dev->prepare)
            dpm_print("prepare   begin:0x%x end:0x%x, max_duration:%x, fail count:%d.\n",\
                dev->debug_time[PREPARE][0], dev->debug_time[PREPARE][1],\
                dev->max_duration[PREPARE] , dev->debug_count[PREPARE]);
        if(dev->suspend_early)
            dpm_print("sus early begin:0x%x end:0x%x, max_duration:%x, fail count:%d.\n",\
                dev->debug_time[SUS_EARLY][0], dev->debug_time[SUS_EARLY][1],\
                dev->max_duration[SUS_EARLY] , dev->debug_count[SUS_EARLY]);
        if(dev->suspend)
            dpm_print("suspend   begin:0x%x end:0x%x, max_duration:%x, fail count:%d.\n",\
                dev->debug_time[SUSPEND][0], dev->debug_time[SUSPEND][1],\
                dev->max_duration[SUSPEND] , dev->debug_count[SUSPEND]);
        if(dev->suspend_late)
            dpm_print("sus late  begin:0x%x end:0x%x, max_duration:%x, fail count:%d.\n",\
                dev->debug_time[LATE][0], dev->debug_time[LATE][1],\
                dev->max_duration[LATE] ,dev->debug_count[LATE]);
        if(dev->resume_early)
            dpm_print("res early begin:0x%x end:0x%x, max_duration:%x.\n",\
                dev->debug_time[EARLY][0], dev->debug_time[EARLY][1], dev->max_duration[EARLY]);
        if(dev->resume)
            dpm_print("resume    begin:0x%x end:0x%x, max_duration:%x.\n",\
                dev->debug_time[RESUME][0], dev->debug_time[RESUME][1], dev->max_duration[RESUME]);
        if(dev->resume_late)
            dpm_print("res  late begin:0x%x end:0x%x, max_duration:%x.\n",\
                dev->debug_time[RES_LATE][0], dev->debug_time[RES_LATE][1], dev->max_duration[RES_LATE]);
        if(dev->complete)
            dpm_print("complete  begin:0x%x end:0x%x, max_duration:%x.\n",\
                dev->debug_time[COMPLETE][0] ,dev->debug_time[COMPLETE][1], dev->max_duration[COMPLETE]);
	}
    dpm_print("\n");
    dpm_print("-------------------dpm list info:  dev_name:-----------------------\n");
	list_for_each_entry(dev,&(dpm_ctrl.dpm_list),entry)
	{
		dpm_print("\t\t%s:\n",dev->device_name);
	}
    dpm_print("\n");
	dpm_print("-------------------dpm prepared  list info:  dev_name:-----------------------\n");
	list_for_each_entry(dev,&(dpm_ctrl.dpm_prepared_list),entry)
	{
		dpm_print("\t\t%s:\n",dev->device_name);
	}
    dpm_print("\n");
	dpm_print("--------------------dpm sus early list info:   dev_name:---------------------------\n");
	list_for_each_entry(dev,&(dpm_ctrl.dpm_sus_early_list),entry)
	{
		dpm_print("\t\t%s:\n",dev->device_name);
	}
    dpm_print("\n");
	dpm_print("--------------------dpm suspend list info:   dev_name:---------------------------\n");
	list_for_each_entry(dev,&(dpm_ctrl.dpm_suspend_list),entry)
	{
		dpm_print("\t\t%s:\n",dev->device_name);
	}
    dpm_print("\n");
	dpm_print("--------------------dpm late early list info:   dev_name:---------------------------\n");
	list_for_each_entry(dev,&(dpm_ctrl.dpm_late_early_list),entry)
	{
		dpm_print("\t\t%s:\n",dev->device_name);
	}
}
/*lint -restore +e516*/


