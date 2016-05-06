/*************************************************************************
*   版权所有(C) 2008-2013, 深圳华为技术有限公司.
*
*   文 件 名 :  regulator_balong.c
*
*   作    者 :  y00221789
*
*   描    述 :
*
*   修改记录 :
*
*************************************************************************/
#include <cmsis_os.h>
#include <osl_common.h>
#include <hisi_lpm3.h>
#include <bsp_icc.h>
#include <bsp_regulator.h>
#include "regulator_balong.h"

#ifdef __cplusplus /* __cplusplus */
extern "C"
{
#endif /* __cplusplus */

int balong_regulator_icc_send(struct regulator_msg *msg)
{
	u32 channel_id = ICC_CHN_MCORE_CCORE << 16 | MCORE_CCORE_FUNC_REGULATOR;
	s32 ret = 0;
	u32 msg_len = sizeof(struct regulator_msg);
	
	ret = bsp_icc_send(ICC_CPU_MODEM, channel_id, (u8 *)msg, msg_len);
	if(ret != msg_len)
	{
		//regu_pr_err("mcore return an ERROR\n");
		return BSP_ERROR;
	}
    return BSP_OK;
}
#define HI6421_LDO11_CTRL			(0x8a)
#define HI6421_LDO12_CTRL			(0x8b)
#define HI6421_LSW53_CTRL			(0xAF)
#define HI6421_PMU_BASEADDR	(0x40234000)
int bsp_hi6421_volt_is_enabled(int volt_id)
{
	int reg_value = 0;
	switch (volt_id)
	{
		case  (K3_REGU_SIM0 - K3_REGULATOR_BASE_NUM):
			reg_value = LDO_ENABLED(LDO11); 
			break;
		case  (K3_REGU_SIM1 - K3_REGULATOR_BASE_NUM):
			reg_value = LDO_ENABLED(LDO12);
			break;
		case (K3_REGU_PASTAR - K3_REGULATOR_BASE_NUM):
			//reg_value = LSW_ENABLED(LSW53);
			break;
		default:
			break;
	}
	return reg_value;
}

int bsp_hi6421_volt_enable(int volt_id)
{
	int reg_value = 0;
	switch (volt_id)
	{
		case (K3_REGU_SIM0 - K3_REGULATOR_BASE_NUM):
			LDO_ENABLE(LDO11); 
			break;
		case (K3_REGU_SIM1 - K3_REGULATOR_BASE_NUM):
			LDO_ENABLE(LDO12);
			break;
		case (K3_REGU_PASTAR - K3_REGULATOR_BASE_NUM):
			LSW_ENABLE(LSW53);
			break;
		default:
			break;
	}
	return reg_value;
}

int bsp_hi6421_volt_disable(int volt_id)
{
	int reg_value = 0;
	switch (volt_id)
	{
		case (K3_REGU_SIM0 - K3_REGULATOR_BASE_NUM):
			LDO_DISABLE(LDO11); 
			break;
		case (K3_REGU_SIM1 - K3_REGULATOR_BASE_NUM):
			LDO_DISABLE(LDO12);
			break;
		case (K3_REGU_PASTAR - K3_REGULATOR_BASE_NUM):
			LSW_DISABLE(LSW53);
			break;
		default:
			break;
	}
	return reg_value;	
}

int bsp_hi6421_volt_get_voltage(int volt_id)
{
	int reg_value = 0;
	int ret = 0;
	switch (volt_id)
	{
		case (K3_REGU_SIM0 - K3_REGULATOR_BASE_NUM):
			reg_value = LDO_GET_VOLT(LDO11); 
			break;
		case (K3_REGU_SIM1 - K3_REGULATOR_BASE_NUM):
			reg_value = LDO_GET_VOLT(LDO12);
			break;
		case (K3_REGU_PASTAR - K3_REGULATOR_BASE_NUM):
			break;
		default:
			break;
	}
	if (BALONG_HI6421_VOLT18 == reg_value)
	{
		ret = BALONG_SIM_VOLT18;
	}
	else if (BALONG_HI6421_VOLT30 == reg_value)
	{
		ret = BALONG_SIM_VOLT30;
	}
	else
	{
		ret = -1;
	}
	return ret;	
}

int bsp_hi6421_volt_set_voltage(int volt_id, int volt_uV)
{
	int reg_value = 0;
	switch (volt_id)
	{
		case  (K3_REGU_SIM0 - K3_REGULATOR_BASE_NUM):
			LDO_SET_VOLT(LDO11, volt_uV); 
			break;
		case  (K3_REGU_SIM1 - K3_REGULATOR_BASE_NUM):
			LDO_SET_VOLT(LDO12, volt_uV);
			break;
		default:
			break;
	}
	return reg_value;
}

int bsp_hi6421_volt(int mV)
{
	int ret = 0;
	if (BALONG_SIM_VOLT18 == mV)
	{
		ret = BALONG_HI6421_VOLT18;
	}
	else if (BALONG_SIM_VOLT30 == mV)
	{
		ret = BALONG_HI6421_VOLT30;
	}
	else
	{
		ret = -1;
	}
	return ret;
}
static int balong_regulator_hi6421_opscb(u32 channel_id , u32 len, void* context)
{
	s32 ret = BSP_OK;
	int volt_id = 0;
	int volt_mV = 0;
	struct regulator_msg msg = {0};
	struct regulator_msg send_msg = {0};
	ret = bsp_icc_read(channel_id, (u8*)&msg, len);
	if(len != ret)
	{
		return BSP_ERROR;
	}
	volt_id = msg.volt_id;
	volt_mV = bsp_hi6421_volt(msg.min_uV);
	switch  (msg.ops_flag)
	{
		case HI6421_OPS_ENABLE:
			bsp_hi6421_volt_enable(volt_id);
			break;
		case HI6421_OPS_DISABLE:
			bsp_hi6421_volt_disable(volt_id);
			break;
		case HI6421_OPS_IS_ENABLED:
			send_msg.result = bsp_hi6421_volt_is_enabled(volt_id);
			send_msg.ops_flag = HI6421_OPS_IS_ENABLED;
			balong_regulator_icc_send(&send_msg);
			break;
		case HI6421_OPS_GET_VOLT:
			send_msg.result = bsp_hi6421_volt_get_voltage(volt_id);
			send_msg.ops_flag = HI6421_OPS_GET_VOLT;
			balong_regulator_icc_send(&send_msg);
			break;
		case HI6421_OPS_SET_VOLT:
			if (volt_mV != -1)
			{
				bsp_hi6421_volt_set_voltage(volt_id, volt_mV);
			}
			break;
		default:
			break;
	}
	return BSP_OK;
}

void modem_regulator_init(void)
{
	u32 ret = 0;
	u32 channel_id_set = ICC_CHN_MCORE_CCORE << 16 | MCORE_CCORE_FUNC_REGULATOR;

	ret = bsp_icc_event_register(channel_id_set, (read_cb_func)balong_regulator_hi6421_opscb, (void *)NULL, (write_cb_func)NULL, (void *)NULL);
	//regu_pr_info("register icc \n");
	ret = ret;
    return;
}

#ifdef __cplusplus /* __cplusplus */
}
#endif /* __cplusplus */


