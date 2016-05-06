/*************************************************************************
*   版权所有(C) 2008-2012, 深圳华为技术有限公司.
*
*   文 件 名 :  regulator_balong.c
*
*   作    者 :  y00221789
*
*   描    述 :
*
*   修改记录 :  2013年1月30日  v1.00  y00221789  创建
*   todo:

*************************************************************************/

#ifdef __cplusplus /* __cplusplus */
extern "C"
{
#endif /* __cplusplus */

#ifdef __OS_VXWORKS
#include <vxWorks.h>
#include <intLib.h>
#include <errnoLib.h>
#include <sioLib.h>
#endif

#include <string.h>
#include <securec.h>

#include <product_config.h>
#include <osl_types.h>
#include <osl_sem.h>
#include <osl_bio.h>
#include <osl_irq.h>
#include <osl_malloc.h>
#include <osl_thread.h>
#include <bsp_ipc.h>
#include <bsp_sram.h>
#include <of.h>
#include "regulator_balong.h"
/*lint --e{413, 525, 537, 830}*/

LIST_HEAD(regulator_list);
LIST_HEAD(regulator_map_list);
LIST_HEAD(regulator_pmic_list);
osl_sem_id regulator_list_mutex = 0;

static inline void regulator_pm_om_log(struct regulator *regulator, int opsid)
{
	struct regulator_pm_om_log regu_log = {(unsigned int)opsid, (unsigned int)regulator->id, (unsigned int)regulator->use_count, 0};
	
	regu_log.task_id = (unsigned int)osl_task_self();
	(void)memcpy_s(regu_log.pmutype, sizeof(char)*(PMU_TYPE_LEN - 1), regulator->regulator_pmic_type, sizeof(char)*(PMU_TYPE_LEN - 1));
	regu_log.pmutype[(PMU_TYPE_LEN - 1)]= '\0';
	(void)bsp_pm_log_type(PM_OM_REGU, REGULATOR_TYPE, sizeof(struct regulator_pm_om_log), &regu_log);
}

static inline void _regulator_print_debug(struct regulator *regulator)
{
	regu_pr_debug("id:%d, name:%s, type:%s, use_flag:%d\n", 
				regulator->id, regulator->name, regulator->regulator_pmic_type, regulator->use_count_valid);
}
static int _regulator_is_enabled(struct regulator *regulator)
{
	int ret = 0;
	
	if (regulator->regulator_pmic_ops && regulator->regulator_pmic_ops->is_enabled)
	{
		ret = regulator->regulator_pmic_ops->is_enabled((int)regulator->id);
	}
	else
	{
		ret = (int)regulator->is_enabled_flag;
	}
	return ret;
}
int regulator_is_enabled(struct regulator *regulator)
{
	int ret = 0;
	if (NULL == regulator)
	{
		regu_pr_err("argc point is null\n");
		return ERROR;
	}
	_regulator_print_debug(regulator);
	osl_sem_down(&regulator->mutex);
	ret = _regulator_is_enabled(regulator);
	osl_sem_up(&regulator->mutex);

	return ret;
}
static int _regulator_enable(struct regulator *regulator)
{
	int ret = 0;
	if ((0 == regulator->use_count) || !(regulator->use_count_valid))
	{
		ret = _regulator_is_enabled(regulator);
		if ((0 == ret) && (regulator->regulator_pmic_ops) && (regulator->regulator_pmic_ops->enable))
		{
			ret = regulator->regulator_pmic_ops->enable((int)regulator->id);
			if (ret != 0)
			{
				regu_pr_err("failed enable regulator  %s\n", regulator->name);
				return ret;
			}
			else
			{
				regulator->is_enabled_flag = 1;
			}
		}
	}
	if (regulator->use_count_valid)
	{
		regulator->use_count++;
	}
	else
	{
		regulator->use_count = 1;
	}
	
	(void)regulator_pm_om_log(regulator, REGULATOR_OPS_ENABLE);
	
	return 0;
}
int regulator_enable(struct regulator *regulator)
{
	int ret = 0;
	if (NULL == regulator)
	{
		regu_pr_err("argc point is null\n");
		return ERROR;
	}
	_regulator_print_debug(regulator);
	osl_sem_down(&regulator->mutex);
	if (regulator->parent)
	{
		/*引用计数可用，直接开父节点，
		   不可用时，且没有打开过该子节点才开父节点*/
		if ((regulator->use_count_valid) || (!(regulator->use_count_valid) && !(regulator->use_count)))
		{
			ret = regulator_enable(regulator->parent);
			if (ret != 0)
			{
				osl_sem_up(&regulator->mutex);
				return ret;
			}
		}
	}
	ret = _regulator_enable(regulator);
	if (ret != 0 && regulator->parent)
	{
		if ((regulator->use_count_valid) || (!(regulator->use_count_valid) && !(regulator->use_count)))
		{
			(void)regulator_disable(regulator->parent);
		}
	}
	osl_sem_up(&regulator->mutex);

	return ret;
}
static int _regulator_disable(struct regulator *regulator)
{
	int ret = 0;
	
	if ((regulator->use_count_valid) && (regulator->use_count <= 0))
		regu_pr_err("unbalanced disables for %s", regulator->name);

	if ((1 == regulator->use_count) || (!(regulator->use_count_valid)))
	{
		ret = _regulator_is_enabled(regulator);
		if (ret != 0 && (regulator->regulator_pmic_ops) && (regulator->regulator_pmic_ops->disable))
		{
			ret = regulator->regulator_pmic_ops->disable((int)regulator->id);
			if (ret != 0)
			{
				regu_pr_err("failed disable regulator  %s\n", regulator->name);
				return ret;
			}
			else
			{
				regulator->is_enabled_flag = 0;
			}
		}
		regulator->use_count = 0;
	}

	if ((regulator->use_count > 1) && (regulator->use_count_valid))
	{
		regulator->use_count--;
	}
	
	regulator_pm_om_log(regulator, REGULATOR_OPS_DISABLE);
	
	return ret;
}
int regulator_disable(struct regulator *regulator)
{
	int ret = 0;
	int mask = 0;
	if (NULL == regulator)
	{
		regu_pr_err("argc point is null\n");
		return ERROR;
	}
	_regulator_print_debug(regulator);
	osl_sem_down(&regulator->mutex);
	mask = regulator->use_count;
	ret = _regulator_disable(regulator);

	if (0 == ret  && regulator->parent)
	{
		if ((regulator->use_count_valid) || (!(regulator->use_count_valid) && (mask)))
			(void)regulator_disable(regulator->parent);
	}
	osl_sem_up(&regulator->mutex);

	return ret;
}

int regulator_get_voltage(struct regulator *regulator)
{
	int ret = 0;
	if (NULL == regulator)
	{
		regu_pr_err("argc point is null\n");
		return ERROR;
	}
	_regulator_print_debug(regulator);
	osl_sem_down(&regulator->mutex);
	if (regulator->regulator_pmic_ops && regulator->regulator_pmic_ops->get_voltage)
		ret = regulator->regulator_pmic_ops->get_voltage((int)regulator->id);
	osl_sem_up(&regulator->mutex);
	
	return ret;
}
int regulator_set_voltage(struct regulator *regulator, int min_uV, int max_uV)
{
	int ret = 0;
	unsigned int selector = 0;
	if (NULL == regulator)
	{
		regu_pr_err("argc point is null\n");
		return ERROR;
	}
	regu_pr_debug("volt:%d", max_uV);
	_regulator_print_debug(regulator);
	osl_sem_down(&regulator->mutex);
	if (regulator->regulator_pmic_ops && regulator->regulator_pmic_ops->set_voltage)
		ret = regulator->regulator_pmic_ops->set_voltage((int)regulator->id, min_uV, max_uV, &selector);
	osl_sem_up(&regulator->mutex);

	return ret;
}
struct regulator * regulator_get(unsigned char *name, char *supply)
{
	struct regulator *regulator = NULL;
	struct regulator_consumer_map *node = NULL;

	if (NULL == supply)
	{
		regu_pr_err("argc supply is null  check it\n");
		return regulator;
	}
	osl_sem_down(&regulator_list_mutex);
	list_for_each_entry(node, &regulator_map_list, list)
	{
		if (!strcmp(supply, node->supply))
		{
			regulator = node->regulator;
		}
	}
	osl_sem_up(&regulator_list_mutex);
	return regulator;
}


void regulator_put(struct regulator *regulator)
{
	return;
}
struct regulator *regulator_lookup_name(const char *regulator_name)
{
	struct regulator *regulator = NULL;
	struct regulator *node = NULL;
	if (NULL == regulator_name)
	{
		regu_pr_err("argc is null return\n");
		return regulator;
	}

	list_for_each_entry(node, &regulator_list, list)
	{
		if (!strcmp(node->name, regulator_name))
		{
			regulator = node;
			break;
		}
	}
	
	return regulator;
}
struct regulator_id_ops *regulator_get_pmic_ops(char *regulator_pmic_type)
{
	unsigned long irqlock = 0;
	struct regulator_type_map *node = NULL;
	struct regulator_id_ops *regu_ops = NULL;
	if (NULL == regulator_pmic_type)
	{
		regu_pr_err("argc is null check it\n");
		return regu_ops;
	}
	local_irq_save(irqlock);
	list_for_each_entry(node, &regulator_pmic_list, list)
	{
		if (!strcmp(node->regulator_type, regulator_pmic_type))
		{
			regu_ops = node->ops;
			break;
		}
	}

	local_irq_restore(irqlock);
	return regu_ops;
}
int regulator_pmic_ops_register(struct regulator_id_ops *pmic_ops, char *pmic_type)
{
	unsigned long irqlock = 0;
	unsigned int len = 0;
	struct regulator_type_map *regulator_type = NULL;
	struct regulator_type_map *regulator_pmic_type = NULL;
	if (NULL == pmic_type || NULL == pmic_ops)
	{
		regu_pr_err("argc is NULL check it\n");
		return ERROR;
	}
	regulator_pmic_type = (struct regulator_type_map *)osl_malloc(sizeof(struct regulator_type_map));
	if (NULL == regulator_pmic_type)
	{
		regu_pr_err("regulator_type_map malloc failed %d\n", regulator_pmic_type);
		return ERROR;
	}
	len = strlen(pmic_type);
	regulator_pmic_type->regulator_type = (char *)osl_malloc(len+1);
	if (NULL == regulator_pmic_type->regulator_type)
	{
		regu_pr_err("regulator_type malloc failed %d\n", regulator_pmic_type->regulator_type);
		osl_free(regulator_pmic_type);
		return ERROR;
	}
	
	local_irq_save(irqlock);
	list_for_each_entry(regulator_type, &regulator_pmic_list, list)
	{
		if (!strcmp(regulator_type->regulator_type, pmic_type))
		{
			regu_pr_err("we have the same pmic_type (%s),check dts or your pmic name\n", pmic_type);
			/*lint --e{801 }*/
			goto pmic_err;
		}
	}

	INIT_LIST_HEAD(&regulator_pmic_type->list);
	(void)strcpy_s(regulator_pmic_type->regulator_type, (size_t)(len + 1), pmic_type);
	regulator_pmic_type->ops = pmic_ops;
    regulator_pmic_type->is_enabled_flag = 0;
	list_add(&regulator_pmic_type->list, &regulator_pmic_list);
pmic_err:
	local_irq_restore(irqlock);

	return OK;	
}
int regulator_set_consumer_supply(struct regulator *regulator, const char *supply)
{
	struct regulator_consumer_map *regulator_map = NULL;
	struct regulator_consumer_map *node = NULL;

	if (NULL == supply || NULL == regulator)
	{
		regu_pr_err("argc is null ,supply is? check it\n");
		return ERROR;
	}
	list_for_each_entry(node, &regulator_map_list, list)
	{
		if (!strcmp(node->supply, supply))
		{
			regu_pr_err("have same supply, failed ,check dts   %s\n", supply);
			return ERROR;
		}
	}
	regulator_map = (struct regulator_consumer_map *)osl_malloc(sizeof(struct regulator_consumer_map));
	if (NULL == regulator_map)
	{
		regu_pr_err("node malloc failed  %d\n", regulator_map);
		return ERROR;
	}
	regulator_map->regulator = regulator;
	regulator_map->supply = supply;
    INIT_LIST_HEAD(&regulator_map->list);
	list_add(&regulator_map->list, &regulator_map_list);
	return OK;
}
int regulator_init_consumers(struct regulator *regulator, struct device_node *regu_node_child)
{
	int ret = 0;
	unsigned int i = 0;
	regulator->consumer_supplies = (struct regulator_consumer_supply *)osl_malloc(sizeof(struct regulator_consumer_supply) * (regulator->num_consumer_supplies));
	if (NULL == regulator->consumer_supplies)
	{
		regu_pr_err("consumer_supplies malloc failed  %d\n", regulator->consumer_supplies);
		return ERROR;
	}
	for (i = 0; i < regulator->num_consumer_supplies; i++)
	{
		ret = of_property_read_string_index(regu_node_child, "hisilicon,hisi_regulator_consumer", (int)i, &regulator->consumer_supplies[i].supply);
		if (ret != 0) {
			regu_pr_err("failed to get regulator consumers resource! ret=%d.i:%d\n", ret, i);
			continue;
		}
		/*检查supply_consumer 唯一性,并添加至consumer_map list*/
		ret = regulator_set_consumer_supply(regulator, regulator->consumer_supplies[i].supply);
		if (ret)
		{
			regu_pr_err("please check regulator: %s 's supply\n", regulator->name);
			continue;
		}
	}
	return OK;
}

void regulator_init_property(struct regulator *regulator, struct device_node *regu_node_child)
{
	if(of_property_read_u32_array(regu_node_child, "hisilicon,hisi_regulator_id", &regulator->id, 1))
	{
		regulator->id = 9876;
	}
	if(of_property_read_u32_array(regu_node_child, "regulator_usecount_valid", &regulator->use_count_valid, 1))
	{
		regulator->use_count_valid = 0;
	}
	regulator->name = of_get_property(regu_node_child, "regulator_name", NULL);
	regulator->parent_name = of_get_property(regu_node_child, "regulator_supply", NULL);
	regulator->num_consumer_supplies = (unsigned int)of_property_count_strings(regu_node_child, "hisilicon,hisi_regulator_consumer");

	regulator->regulator_pmic_type = (char *)of_get_property(regu_node_child, "hisilicon,hisi_pmic_type", NULL);
	regulator->regulator_pmic_ops = regulator_get_pmic_ops(regulator->regulator_pmic_type);
	if (NULL == regulator->regulator_pmic_ops)
	{
		regu_pr_err("get <%s> pmic ops failed  use dummy ops\n", regulator->regulator_pmic_type);
		regulator->regulator_pmic_ops  = regulator_get_pmic_ops("dummy_pmic");
	}
}
extern void regulator_pmic_dummy_init(void);
/*new code for regulator*/
/*
	完成regulator的初始化及链表的挂接
*/
struct device_node *regu_node = NULL;
void regulator_init(void)
{
	int ret = 0;
	struct regulator *regulator = NULL;
	struct device_node *regu_node_child = NULL;
	
	regu_node = of_find_compatible_node(NULL, NULL, "hisilicon,regulator_balong");
	if (!regu_node)
	{
		regu_pr_err("regulator dts node not found!\n");
		return;
	}
	regulator_pmic_dummy_init();
	osl_sem_init(SEM_FULL, &regulator_list_mutex);
	osl_sem_down(&regulator_list_mutex);
	for_each_child_of_node(regu_node, regu_node_child)
	{
		regulator = (struct regulator *) osl_malloc (sizeof(struct regulator));
		if (NULL == regulator)
		{
			regu_pr_err("malloc error child num\n");
			continue;
		}
		(void)memset_s(regulator, sizeof(struct regulator), 0, sizeof(struct regulator));
		osl_sem_init(1, &(regulator->mutex));
		INIT_LIST_HEAD(&regulator->list);
		INIT_LIST_HEAD(&regulator->consumer_list);
		
		regulator_init_property(regulator, regu_node_child);		
		
		ret = regulator_init_consumers(regulator, regu_node_child);
		if (ret != OK)
		{
			regu_pr_err("init consumers failed check it\n");
			continue;
		}
		if (regulator->parent_name)
		{
			regulator->parent = regulator_lookup_name(regulator->parent_name);
		}
		list_add(&regulator->list, &regulator_list);
	}
	osl_sem_up(&regulator_list_mutex);
	regu_pr_err("regulator init ok\n");
	return;
}


void regulator_print_status(void)
{
	int ret = 0;
	int i = 0;
	struct regulator *regulator = NULL;
    list_for_each_entry(regulator, &regulator_list, list)
    {
        regu_pr_err("~~~~\n");
    	ret = regulator_is_enabled(regulator);
    	regu_pr_err("name: %s\n", regulator->name);
		regu_pr_err("status: %d\n", ret);
		regu_pr_err("count: %d\n", regulator->use_count);
		if (regulator->regulator_pmic_type)
		    regu_pr_err("pmic name:%s\n", regulator->regulator_pmic_type);
		if (regulator->regulator_pmic_ops && regulator->regulator_pmic_ops->get_voltage)
			regu_pr_err("volt: %d\n", regulator_get_voltage(regulator));
		regu_pr_err("consumers:\n");
		for (i = 0; i < (s32)regulator->num_consumer_supplies; i++)
		{
           regu_pr_err("%s\t\n", regulator->consumer_supplies[i].supply);
		}
    }
    regu_pr_err("buck3:%d\n", BUCK3_ONOFF_FLAG);
}

#ifdef __cplusplus /* __cplusplus */
}
#endif /* __cplusplus */
