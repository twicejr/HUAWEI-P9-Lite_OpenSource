/*************************************************************************
*   版权所有(C) 2008-2015, 深圳华为技术有限公司.
*
*   文 件 名 :  pm_om.c
*
*   作    者 :  y00184236
*
*   描    述 :  本文件主要完成低功耗可维可测通用流程
*
*   修改记录 :  2014年11月17日  v1.00  y00184236  创建
***************************************************************************/
#include <securec.h>
#include <osl_thread.h>
#include <osl_spinlock.h>
#include <bsp_hardtimer.h>
#include <bsp_pm_om.h>

#define PM_OM_TEST_DUMP_SIZE (u32)(0x4000)
#define PM_OM_TEST_LOG_SIZE  (u32)(64)

/*lint --e{528}*/
struct pm_om_stat
{
	u32 log_cost_min;  /* pm log接口最短调用时间消耗 */
	u32 log_cost_max;  /* pm log接口最长调用时间消耗 */
	u32 log_cost_avg;  /* pm log接口平均调用时间消耗 */
	u32 log_cost_cnt;  /* pm log接口调用次数 */
	u32 log_cost_sum;  /* pm log接口总时间 */
	spinlock_t log_cost_lock;
};

struct pm_om_test
{
	struct pm_om_stat stat;
};

struct pm_om_test g_pmom_test;

/* 对应mcore的pm_om_platform_init */
void pmom_test_init(void)
{

	memset_s((void *)&g_pmom_test, sizeof(g_pmom_test), 0, sizeof(g_pmom_test));

	g_pmom_test.stat.log_cost_min = 0xffffffff;
	spin_lock_init(&g_pmom_test.stat.log_cost_lock);
}

int pmom_dump_test_func(u32 magic, u32 size)
{
	char *dump_addr;
	char name[5];
	static u32 dump_cnt = 0;

	(*(unsigned *)(name)) = magic;
	name[4]=0;
	dump_cnt++;

	dump_addr = bsp_pm_dump_get((u32)magic, size);
	if (NULL == dump_addr)
	{
		pmom_pr_err("no pm om mem\n");
		return (int)(((u32)PM_OM_ERR) << 16 | dump_cnt);/*lint !e648 */
	}
	else
	{
		pmom_pr_err("[%s]0x%p\n", name, dump_addr);
		return PM_OM_OK;
	}
}
int pmom_dump_test(void)
{
	int ret = PM_OM_ERR;
	ret =  pmom_dump_test_func(PM_OM_ABB, PM_OM_TEST_DUMP_SIZE);
	ret |= pmom_dump_test_func(PM_OM_BBP, PM_OM_TEST_DUMP_SIZE);
	ret |= pmom_dump_test_func(PM_OM_DSP, PM_OM_TEST_DUMP_SIZE);
	ret |= pmom_dump_test_func(PM_OM_PMU, PM_OM_TEST_DUMP_SIZE);
	if (ret)
	{
		pmom_pr_err("FAIL, ret=0x%x\n", ret);
	}
	else
	{
		pmom_pr_err("PASS\n");
	}
	return ret;
}

int pmom_dump_test2(void)
{
	int ret = PM_OM_ERR;
	ret = pmom_dump_test_func(PM_OM_ABB, PM_OM_TEST_DUMP_SIZE);
	if (ret)
	{
		pmom_pr_err("FAIL, ret=0x%x\n", ret);
	}
	else
	{
		pmom_pr_err("PASS\n");
	}
	return ret;
}

int pmom_log_test_func(u32 magic)
{
	static u8 write = 0;
	static u8 log[PM_OM_TEST_LOG_SIZE];
	u32 i = 0;
	int ret = PM_OM_ERR;
	unsigned long flags = 0;
	u32 cur_time = 0;
	u32 end_time = 0;
	static u32 cnt = 0;
	UNUSED(flags); /* suppress compile warning */

	cnt++;
	for (i = 0; i < PM_OM_TEST_LOG_SIZE; i++)
	{
		log[write&(PM_OM_TEST_LOG_SIZE-1)] = write;
		write++;
	}

	spin_lock_irqsave(&g_pmom_test.stat.log_cost_lock, flags);
	cur_time = bsp_get_slice_value();
	ret = bsp_pm_log_type(magic, 0, PM_OM_TEST_LOG_SIZE, (void *)log);
	end_time= bsp_get_slice_value();
	cur_time = get_timer_slice_delta(cur_time, end_time);
	spin_unlock_irqrestore(&g_pmom_test.stat.log_cost_lock, flags);

	if (cur_time < g_pmom_test.stat.log_cost_min)
	{
		g_pmom_test.stat.log_cost_min = cur_time;
	}
	if (cur_time > g_pmom_test.stat.log_cost_max)
	{
		g_pmom_test.stat.log_cost_max = cur_time;
	}

	g_pmom_test.stat.log_cost_cnt++;
	g_pmom_test.stat.log_cost_sum += cur_time;
	g_pmom_test.stat.log_cost_avg = g_pmom_test.stat.log_cost_sum / g_pmom_test.stat.log_cost_cnt;

	if (PM_OM_OK != ret)
	{
		pmom_pr_err("pm_log_type err\n");
		return (int)(((u32)ret) << 16 | cnt);
	}
	else
	{
		return PM_OM_OK;
	}
}

int pmom_log_test(u32 print_sw)
{
	static u32 i = 0;
	int ret = PM_OM_ERR;

	if (i == 0)
	{
		ret = pmom_log_test_func(PM_OM_ABB);
		ret |= pmom_log_test_func(PM_OM_ACLK);
	}
	else if (i == 1)
	{
		ret = pmom_log_test_func(PM_OM_AIPC);
		ret |= pmom_log_test_func(PM_OM_AIPF);
	}
	else if (i == 2)
	{
		ret = pmom_log_test_func(PM_OM_BBP);
		ret |= pmom_log_test_func(PM_OM_CCLK);
	}
	else if (i == 3)
	{
		ret = pmom_log_test_func(PM_OM_CIPC);
		ret |= pmom_log_test_func(PM_OM_CIPF);
	}
	else if (i == 4)
	{
		ret = pmom_log_test_func(PM_OM_CPUF);
		ret |= pmom_log_test_func(PM_OM_DSP);
	}
	else if (i == 5)
	{
		ret = pmom_log_test_func(PM_OM_DPM);
		ret |= pmom_log_test_func(PM_OM_PMA);
	}
	else if (i == 6)
	{
		ret = pmom_log_test_func(PM_OM_PMC);
		ret |= pmom_log_test_func(PM_OM_PMM);
		i = 0;
	}
	i++;
	if (ret)
	{
		pmom_pr_err("FAIL, ret=0x%x\n", ret);
	}
	else
	{
		if (print_sw)
		{
			pmom_pr_err("PASS\n");
		}
	}
	return ret;
}

void pmom_performance_dump(void)
{
	pmom_print("++++++++++++++++pm log used time++++++++++++++++\n");
	pmom_print("log_cost_min=%d\n", g_pmom_test.stat.log_cost_min);
	pmom_print("log_cost_max=%d\n", g_pmom_test.stat.log_cost_max);
	pmom_print("log_cost_avg=%d\n", g_pmom_test.stat.log_cost_avg);
}
void pmom_performance_test(void)
{
	u32 i;

	/* test for 5minutes */
	for(i = 0; i < 500; i++)
	{
		(void)pmom_log_test(0);
		osl_task_delay(1);
	}
}

