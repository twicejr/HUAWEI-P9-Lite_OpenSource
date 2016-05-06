/*************************************************************************
*   版权所有(C) 2008-2015, 深圳华为技术有限公司.
*
*   文 件 名 :  adp_pm_om.c
*
*   作    者 :  y00184236
*
*   描    述 :  pm_om对上层适配文件
*
*   修改记录 : 2014年11月17日  v1.00  y00184236  创建
*************************************************************************/
#include <bsp_om.h>
#include <bsp_pm_om.h>

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

int bsp_pm_om_log_init(void)
{
	pmom_pr_err("is stub\n");
	return 0;
}