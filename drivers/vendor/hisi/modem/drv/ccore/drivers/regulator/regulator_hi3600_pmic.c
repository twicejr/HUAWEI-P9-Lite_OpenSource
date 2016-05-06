/*************************************************************************
*   版权所有(C) 2008-2013, 深圳华为技术有限公司.
*
*   文 件 名 :  regulator_hi3600_pmic.c
*
*   作    者 :  y00221789
*
*   描    述 :
*
*   修改记录 :  2014年12月6日  v1.00  y00221789  创建
*************************************************************************/

#ifdef __cplusplus
extern "C"
{
#endif
/*lint --e{539, 830}*/
#include <string.h>
#include <securec.h>
#include <osl_types.h>
#include <osl_bio.h>
#include <osl_sem.h>
#include <osl_malloc.h>
#include <bsp_ipc.h>
#include <bsp_sram.h>
#include <of.h>
#include <bsp_regulator.h>
#include "regulator_balong.h"

#define HI3600_REGU_CB_TIMEOUT 				(10)

osl_sem_id g_sem_hi3600_get_volt = 0;
osl_sem_id g_sem_hi3600_isenable = 0;
int g_hi3600_isenable = 0;
int g_hi3600_getvolt = 0;

static int balong_regulator_hi6421_opscb(u32 channel_id , u32 len, void* context)
{
	s32 ret = BSP_OK;
	struct regulator_msg msg = {0};
	ret = bsp_icc_read(channel_id, (u8*)&msg, len);

	if(len != (u32)ret)
	{
		regu_pr_err("balong_cpufreq_cb_getload error \r\n");
		return BSP_ERROR;
	}
	switch  (msg.ops_flag)
	{
		case REGULATOR_OPS_ENABLE:
			regu_pr_info("enable\n");
			break;
		case REGULATOR_OPS_DISABLE:
			regu_pr_info("disable\n");
			break;
		case REGULATOR_OPS_IS_ENABLED:
			regu_pr_info("is_enabled sem\n");
			g_hi3600_isenable = msg.result;
			osl_sem_up(&g_sem_hi3600_isenable);
			break;
		case REGULATOR_OPS_GET_VOLT:
			regu_pr_info("get voltage\n");
			g_hi3600_getvolt = msg.result;
			osl_sem_up(&g_sem_hi3600_get_volt);
			break;
		case REGULATOR_OPS_SET_VOLT:
			regu_pr_info("set voltage\n");
			break;
		default:
			break;
	}
	return BSP_OK;
}


int balong_regulator_icc_send(struct regulator_msg *msg)
{
#if 0
	u32 channel_id = ICC_CHN_MCORE_CCORE << 16 | MCORE_CCORE_FUNC_REGULATOR;
	s32 ret = 0;
	u32 msg_len = sizeof(struct regulator_msg);
	regu_pr_info("send icc to mcore volt_id:%d min_uV:%d max_uV:%d ops_flag:%d\n", msg->volt_id, msg->min_uV, msg->max_uV, msg->ops_flag);

	ret = bsp_icc_send(ICC_CPU_MCU, channel_id, (u8 *)msg, msg_len);
	if((ret < 0))// && (ret != BSP_ERR_ICC_CCORE_RESETTING)) 缺少该宏
	{
		regu_pr_err("mcore return an ERROR\n");
		return BSP_ERROR;
	}
#endif
    return BSP_OK;
}

int hi3600_enable_regu(int id)
{
	struct regulator_msg msg = {0,0,0,0,0};
	msg.volt_id = (u32)id;
	msg.ops_flag = REGULATOR_OPS_ENABLE;
	(void)balong_regulator_icc_send(&msg);

	return 0;
}
int hi3600_disable_regu(int id)
{
	struct regulator_msg msg = {0,0,0,0,0};
	msg.volt_id = (u32)id;
	msg.ops_flag = REGULATOR_OPS_DISABLE;
	(void)balong_regulator_icc_send(&msg);

	return 0;
}

int hi3600_is_enabled_regu(int id)
{
	struct regulator_msg msg = {0,0,0,0,0};
	int ret = 0;
	msg.volt_id = (u32)id;
	msg.ops_flag = REGULATOR_OPS_IS_ENABLED;
	(void)balong_regulator_icc_send(&msg);
	/*获取信号量*/
	ret = osl_sem_downtimeout(&g_sem_hi3600_isenable, HI3600_REGU_CB_TIMEOUT);
	if (OK != ret)
	{
		regu_pr_err("semTake error:%d\n", ret);
	}
	return g_hi3600_isenable;
}

int hi3600_get_voltage_regu(int id)
{
	struct regulator_msg msg = {0,0,0,0,0};
	int ret = 0;
	msg.volt_id = (u32)id;
	msg.ops_flag = REGULATOR_OPS_GET_VOLT;
	(void)balong_regulator_icc_send(&msg);
	/*获取信号量*/
	ret = osl_sem_downtimeout(&g_sem_hi3600_get_volt, HI3600_REGU_CB_TIMEOUT);
	if (OK != ret)
	{
		regu_pr_err("semTake error:%d\n", ret);
	}
	return g_hi3600_getvolt;
}

int hi3600_set_voltage_regu(int id, int min_uV, int max_uV, unsigned *selector)
{
	struct regulator_msg msg = {0,0,0,0,0};
	msg.volt_id = (u32)id;
	msg.ops_flag = REGULATOR_OPS_SET_VOLT;
	msg.min_uV = (u32)min_uV;
	msg.max_uV = (u32)max_uV;
	*selector = 0;
	(void)balong_regulator_icc_send(&msg);

	return 0;
}

static struct regulator_id_ops hi3600_ops = {
		.set_voltage = hi3600_set_voltage_regu,
		.get_voltage = hi3600_get_voltage_regu,
		.is_enabled = hi3600_is_enabled_regu,
		.enable = hi3600_enable_regu,
		.disable = hi3600_disable_regu,
};

void regulator_pmic_hi3600_init(void)
{
	s32 ret = 0;
	u32 channel_id_set = ICC_CHN_MCORE_CCORE << 16 | MCORE_CCORE_FUNC_REGULATOR;
	
	osl_sem_init(SEM_EMPTY, &g_sem_hi3600_get_volt);
	osl_sem_init(SEM_EMPTY, &g_sem_hi3600_isenable);
    ret = bsp_icc_event_register(channel_id_set, (read_cb_func)balong_regulator_hi6421_opscb, (void *)NULL, (write_cb_func)NULL, (void *)NULL);
    if (ret != BSP_OK)
	{
		regu_pr_err("icc register failed %d\n", ret);
	}
	
	ret = regulator_pmic_ops_register(&hi3600_ops, "hi3600_pmic");
	if (ret)
	{
		regu_pr_err("register hi3600_pmic ops failed\n");
		return;
	}
	regu_pr_err("register hi3600_pmic ops ok\n");
}


#ifdef __cplusplus
}
#endif

