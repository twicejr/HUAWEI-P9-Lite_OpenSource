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


#include <bsp_sram.h>
#include "regulator_balong.h"
#ifdef __cplusplus
extern "C" {
#endif

struct regulator *regulator_get(unsigned char *name, char *supply)
{
	return NULL;
}
void regulator_put(struct regulator *regulator)
{
	return;
}

int regulator_is_enabled(struct regulator *regulator)
{
	int ret = 0;
	return ret;
}

int regulator_enable(struct regulator *regulator)
{
	int ret = 0;
	return ret;
}


int regulator_disable(struct regulator *regulator)
{
	int ret = 0;
	return ret;
}

int regulator_set_voltage(struct regulator *regulator, s32 min_uV, s32 max_uV)
{
	int ret = 0;
	return ret;
}


int regulator_get_voltage(struct regulator *regulator)
{
	int ret = 0;
	return ret;
}

int regulator_set_mode(struct regulator *regulator, u32 mode)
{
	/*mutex start*/
	int ret = 0;

	/*下面调用PMU的接口*/

	/*mutex end*/
	return ret;
}

unsigned int regulator_get_mode(struct regulator *regulator)
{
	/*mutex start*/
	int ret = 0;

	/*下面调用PMU的接口*/

	/*mutex end*/
	return ret;
}

void regulator_init(void)
{
	BUCK3_ONOFF_FLAG = 0;
}

int regulator_pmic_ops_register(struct regulator_id_ops *pmic_ops, char *pmic_type)
{
	return OK;
}
#ifdef __cplusplus
}
#endif
