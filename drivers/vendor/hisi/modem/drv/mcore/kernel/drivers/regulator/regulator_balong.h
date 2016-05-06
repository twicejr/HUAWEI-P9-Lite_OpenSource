/*************************************************************************
*   版权所有(C) 2008-2012, 深圳华为技术有限公司.
*
*   文 件 名 :  regulator_balong.h
*
*   作    者 :  y00221789
*
*   描    述 :
*
*   修改记录 :  2013年1月30日  v1.00  y00221789  创建
*   todo:

*************************************************************************/

#ifndef __REGULATOR_BALONG_H__
#define __REGULATOR_BALONG_H__

#ifdef __cplusplus /* __cplusplus */
extern "C"
{
#endif /* __cplusplus */

#ifndef BSP_OK
#define BSP_OK              (0)
#endif

#ifndef BSP_ERROR
#define BSP_ERROR           (-1)
#endif

#define BALONG_HI6421_VOLT18					(0x1)
#define BALONG_HI6421_VOLT30					(0x6)

#define BALONG_SIM_VOLT18						(1800000)
#define BALONG_SIM_VOLT30						(3000000)

struct regulator_msg {
	u32 volt_id;
	u32 min_uV;
	u32 max_uV;
	u32 ops_flag;   /*0:enable; 1:disable; 2:is_enabled; 3:get_voltage; 4:set_voltage*/
	s32 result;    /*0:success; 1:failed*/
};

void modem_regulator_init(void);

#ifdef __cplusplus /* __cplusplus */
}
#endif /* __cplusplus */

#endif