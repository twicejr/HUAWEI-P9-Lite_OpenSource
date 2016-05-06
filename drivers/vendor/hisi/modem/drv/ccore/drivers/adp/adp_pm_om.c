/*************************************************************************
*   版权所有(C) 2008-2015, 深圳华为技术有限公司.
*
*   文 件 名 :  adp_pm_om.c
*
*   作    者 :  y00184236
*
*   描    述 :  pm_om(including modem log)对上层适配文件
*
*   修改记录 : 2014年11月17日  v1.00  y00184236  创建
*************************************************************************/
#include <mdrv_pm.h>
#include <bsp_ring_buffer.h>
#include <bsp_pm_om.h>

#ifndef CONFIG_PM_OM
int bsp_pm_log(u32 magic, u32 data_len , void *data)
{
	return -1;
}

int bsp_pm_log_type(u32 magic, u32 type, u32 data_len , void *data)
{
	return -1;
}

void* bsp_pm_log_addr_get(void)
{
	return NULL;
}

void* bsp_pm_dump_get(u32 magic, u32 len)
{
	return NULL;
}

int bsp_pm_om_dump_init(void)
{
	pmom_pr_err("is stub\n");
	return 0;
}
void bsp_pm_wakeup_debug_init(void)
{
	pmom_pr_err("is stub\n");
	return ;
}
int bsp_pm_om_log_init(void)
{
	pmom_pr_err("is stub\n");
	return 0;
}

void pm_om_wakeup_stat(void){;}
void pm_om_wakeup_log(void){;}

int bsp_ring_buffer_in(struct ring_buffer *rb, void *data, u32 len, MEMCPY_FUNC memcpy_func)
{
	pmom_pr_err("is stub\n");
	return 0;
}
int bsp_ring_buffer_out(struct ring_buffer *rb, void *data, u32 len, MEMCPY_FUNC memcpy_func)
{
	pmom_pr_err("is stub\n");
	return 0;
}

s32 bsp_modem_log_register(struct log_usr_info *usr_info)
{
	char *dev_name = NULL;
	if (usr_info)
	{
		dev_name = usr_info->dev_name;
	}
	pmom_pr_err("is stub caller is %s\n", dev_name);
	return 0;
}
void bsp_modem_log_fwrite_trigger(struct log_usr_info *usr_info)
{
	char *dev_name = NULL;
	if (usr_info)
	{
		dev_name = usr_info->dev_name;
	}
	pmom_pr_err("is stub caller is %s\n", dev_name);
}
void modem_log_ring_buffer_get(struct log_usr_info * usr_info, struct ring_buffer *rb)
{
	char *dev_name = NULL;
	if (usr_info)
	{
		dev_name = usr_info->dev_name;
	}
	pmom_pr_err("is stub caller is %s\n", dev_name);
}
int bsp_modem_log_init(void)
{
	pmom_pr_err("is stub\n");
	return 0;
}

#endif /* CONFIG_PM_OM */

int mdrv_pm_log(int mod_id,  unsigned int data_len , void *data)
{
	if (PM_MOD_AP_OSA == mod_id)
		mod_id = PM_OM_AOSA;
	else if (PM_MOD_CP_OSA == mod_id)
		mod_id = PM_OM_COSA;
	else if (PM_MOD_CP_MSP == mod_id)
		mod_id = PM_OM_CMSP;
	else
		pmom_pr_err("err: invalid mod_id\n");
	return bsp_pm_log((u32)mod_id, data_len, data);
}