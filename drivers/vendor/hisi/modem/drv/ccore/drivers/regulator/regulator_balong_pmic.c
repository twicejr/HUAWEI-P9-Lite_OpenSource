/*************************************************************************
*   版权所有(C) 2008-2013, 深圳华为技术有限公司.
*
*   文 件 名 :  regulator_balong.c
*
*   作    者 :  y00221789
*
*   描    述 :
*
*   修改记录 :  2013年3月28日  v1.00  y00221789  创建
*************************************************************************/

#ifdef __cplusplus
extern "C"
{
#endif
/*lint --e{539, 701, 830} */
#include <string.h>
#include <securec.h>
#include <osl_types.h>
#include <osl_bio.h>
#include <osl_malloc.h>
#include <bsp_ipc.h>
#include <bsp_sram.h>
#include <of.h>
#include <bsp_pmu.h>
#include <bsp_regulator.h>
#include <bsp_hardtimer.h>
#include <bsp_sysctrl.h>
#include "regulator_balong.h"

struct mtcmos_pm_om_log {
	u32 mtcmos_id;
	u32 status;
	u32 ops;
	u32 buck3_flag;
};
extern void regulator_pmic_hi3600_init(void);

int universal_is_enabled_mtcmos(int id);

static int dummy_list_voltage(int volt_id, unsigned selector)
{
	regu_pr_info("dummy list id:%d \n", volt_id);
	return 0;
}
static int dummy_set_voltage(int volt_id, int min_uV, int max_uV, unsigned *selector)
{
	regu_pr_info("dummy_set_voltage id:%d \n", volt_id);
	return 0;
}
static int dummy_get_voltage(int volt_id)
{
	regu_pr_info("dummy_get_voltage id:%d \n", volt_id);
	return 0;
}
#if 0
static int dummy_is_enabled(int volt_id)
{
	regu_pr_info("dummy_is_enabled id:%d \n", volt_id);
	return 0;
}
#endif
static int dummy_enable(int volt_id)
{
	regu_pr_info("dummy_enable id:%d \n", volt_id);
	return 0;
}
static int dummy_disable(int volt_id)
{
	regu_pr_err("dummy_disable id:%d \n", volt_id);
	return 0;
}
static int dummy_set_mode(int volt_id, unsigned int mode)
{
	regu_pr_info("dummy_set_mode id:%d \n", volt_id);
	return 0;
}
static unsigned int dummy_get_mode(int volt_id)
{
	regu_pr_info("dummy get_mode id:%d \n", volt_id);
	return 0;
}
static struct regulator_id_ops dummy_ops = {
		.list_voltage = dummy_list_voltage,
		.set_voltage = dummy_set_voltage,
		.get_voltage = dummy_get_voltage,
		//.is_enabled = dummy_is_enabled,
		.enable = dummy_enable,
		.disable = dummy_disable,
		.set_mode = dummy_set_mode,
		.get_mode = dummy_get_mode,
		.set_current = dummy_set_voltage,
		.get_current_limit = dummy_get_voltage,
};
void regulator_pmic_mtcmos_init(void);
void regulator_pmic_dummy_init(void)
{
	int ret = 0;
	ret = regulator_pmic_ops_register(&dummy_ops, "dummy_pmic");
	if (ret)
	{
		regu_pr_err("register dummy ops failed\n");
	}
	regu_pr_err("register dummy ops ok\n");
	regulator_pmic_mtcmos_init();
	regulator_pmic_hi3600_init();
}

/*****************************************mtcmos ops***********************************************/




static struct regulator_mtcmos_ops *universal_mtcmos_reg = NULL;
static int universal_mtcmos_max_count = 0;
static int universal_mtcmos_min_count = 0;
static inline void mtcmos_pm_om_log(int id, int ops)
{
	struct mtcmos_pm_om_log mtcmos_log = {(unsigned int)id, 0, (unsigned int)ops, 0};
	mtcmos_log.status = (unsigned int)universal_is_enabled_mtcmos(id);
	mtcmos_log.buck3_flag = BUCK3_ONOFF_FLAG;
	(void)bsp_pm_log_type(PM_OM_REGU, MTCMOS_TYPE, sizeof(struct mtcmos_pm_om_log), &mtcmos_log);
}
int universal_enable_mtcmos(int id)
{
	unsigned int ret = 0;
	unsigned int mt_addr = 0;
	regu_pr_debug("v7r2 mtcmos enable id is : %d\n", id);
	if (id < universal_mtcmos_min_count || id > universal_mtcmos_max_count)
	{
		regu_pr_err("error enable id is : %d\n", id);
		return ERROR;
	}
	mt_addr = universal_mtcmos_reg[id].mtcmos_addr;
	ret =  mt_addr+ universal_mtcmos_reg[id].mtcmos_stat_offset[0];
	
	writel(0x1U << universal_mtcmos_reg[id].mtcmos_en_offset[1], mt_addr + universal_mtcmos_reg[id].mtcmos_en_offset[0]);
	while(!(readl(ret) & (0x1 << universal_mtcmos_reg[id].mtcmos_stat_offset[1])))
	{
		;
	}
	udelay(30);
	writel(0x1U << universal_mtcmos_reg[id].srs_dis_offset[1], mt_addr + universal_mtcmos_reg[id].srs_dis_offset[0]);
	writel(0x1U << universal_mtcmos_reg[id].ios_dis_offset[1], mt_addr + universal_mtcmos_reg[id].ios_dis_offset[0]);
	writel(0x1U << universal_mtcmos_reg[id].clk_en_offset[1], mt_addr + universal_mtcmos_reg[id].clk_en_offset[0]);
	if (0 == id)
		BUCK3_ONOFF_FLAG = 1;

	mtcmos_pm_om_log(id, REGULATOR_OPS_ENABLE);
	
	return 0;
}

int universal_disable_mtcmos(int id)
{
	unsigned int mt_addr = 0;
	regu_pr_debug("v7r2 mtcmos disable id is : %d\n", id);
	if (id < universal_mtcmos_min_count || id > universal_mtcmos_max_count)
	{
		regu_pr_err("error disable id is : %d\n", id);
		return ERROR;
	}
	if (0 == id)
		BUCK3_ONOFF_FLAG = 0;
	mt_addr = universal_mtcmos_reg[id].mtcmos_addr;
	writel(0x1U << universal_mtcmos_reg[id].clk_dis_offset[1], mt_addr + universal_mtcmos_reg[id].clk_dis_offset[0]);
	writel(0x1U << universal_mtcmos_reg[id].ios_en_offset[1], mt_addr + universal_mtcmos_reg[id].ios_en_offset[0]);
	writel(0x1U << universal_mtcmos_reg[id].srs_en_offset[1], mt_addr + universal_mtcmos_reg[id].srs_en_offset[0]);
	writel(0x1U << universal_mtcmos_reg[id].mtcmos_dis_offset[1], mt_addr + universal_mtcmos_reg[id].mtcmos_dis_offset[0]);

	mtcmos_pm_om_log(id, REGULATOR_OPS_DISABLE);
	
	return 0;
}
int universal_is_enabled_mtcmos(int id)
{
	unsigned int ret = 0;
	unsigned int mt_addr = 0;
	regu_pr_debug("v7r2 mtcmos is enabled id is : %d\n", id);
	if (id < universal_mtcmos_min_count || id > universal_mtcmos_max_count)
	{
		regu_pr_err("error isenabled id is : %d\n", id);
		return ERROR;
	}
	mt_addr = universal_mtcmos_reg[id].mtcmos_addr;
	ret = readl(mt_addr + universal_mtcmos_reg[id].mtcmos_stat_offset[0]) & (0x1 << universal_mtcmos_reg[id].mtcmos_stat_offset[1]);
	return (int)ret;
}

static struct regulator_id_ops universal_mtcmos_ops = {
		.is_enabled = universal_is_enabled_mtcmos,
		.enable = universal_enable_mtcmos,
		.disable = universal_disable_mtcmos,
};

struct device_node *mtcmos_node = NULL;
void regulator_pmic_mtcmos_init(void)
{
	unsigned int i = 0, ret = 0;
	unsigned int mt_addr = 0;
	unsigned int mtcmos_count = 0;
	unsigned int len = 0;
	struct device_node *mtcmos_node_child = NULL;
	BUCK3_ONOFF_FLAG = 0;
	mtcmos_node = of_find_compatible_node(NULL, NULL, "hisilicon,regulator_balong_mtcmos");
	if (!mtcmos_node)
	{
		regu_pr_err("regulator mtcmos dts node not found!\n");
		return;
	}
	(void)of_property_read_u32_array(mtcmos_node, "hisilicon,hisi_regulator_mtcmos_count", &mtcmos_count, 1);
	universal_mtcmos_max_count = (int)mtcmos_count - 1;
	len = sizeof( struct regulator_mtcmos_ops) * mtcmos_count;
	universal_mtcmos_reg = (struct regulator_mtcmos_ops *)osl_malloc(len);
	if (NULL == universal_mtcmos_reg)
	{
		regu_pr_err("malloc reg failed\n");
		return;
	}
	(void)memset_s(universal_mtcmos_reg, len, 0, len);
	for_each_child_of_node(mtcmos_node, mtcmos_node_child)
	{
		(void)of_property_read_u32_array(mtcmos_node_child, "hisilicon,mtcmos_id", &i, 1);
		(void)of_property_read_u32_array(mtcmos_node_child, "hisilicon,mtcmos_addr", &mt_addr, 1);
		universal_mtcmos_reg[i].mtcmos_addr = (unsigned int)bsp_sysctrl_addr_get((void *)mt_addr);
		(void)of_property_read_u32_array(mtcmos_node_child, "mtcmos_en_offset", universal_mtcmos_reg[i].mtcmos_en_offset, 2);
		(void)of_property_read_u32_array(mtcmos_node_child, "mtcmos_dis_offset", universal_mtcmos_reg[i].mtcmos_dis_offset, 2);
		(void)of_property_read_u32_array(mtcmos_node_child, "clk_en_offset", universal_mtcmos_reg[i].clk_en_offset, 2);
		(void)of_property_read_u32_array(mtcmos_node_child, "clk_dis_offset", universal_mtcmos_reg[i].clk_dis_offset, 2);
		(void)of_property_read_u32_array(mtcmos_node_child, "ios_en_offset", universal_mtcmos_reg[i].ios_en_offset, 2);
		(void)of_property_read_u32_array(mtcmos_node_child, "ios_dis_offset", universal_mtcmos_reg[i].ios_dis_offset, 2);
		(void)of_property_read_u32_array(mtcmos_node_child, "srs_en_offset", universal_mtcmos_reg[i].srs_en_offset, 2);
		(void)of_property_read_u32_array(mtcmos_node_child, "srs_dis_offset", universal_mtcmos_reg[i].srs_dis_offset, 2);
		(void)of_property_read_u32_array(mtcmos_node_child, "mtcmos_stat_offset", universal_mtcmos_reg[i].mtcmos_stat_offset, 2);
	}	
	ret = (unsigned int)regulator_pmic_ops_register(&universal_mtcmos_ops, "mtcmos_pmic");
	if (ret)
	{
		regu_pr_err("register mtcmos ops failed\n");
		return;
	}
	regu_pr_err("register mtcmos ops ok\n");
}

/*****************************************mtcmos ops***********************************************/

#ifdef __cplusplus
}
#endif

