
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