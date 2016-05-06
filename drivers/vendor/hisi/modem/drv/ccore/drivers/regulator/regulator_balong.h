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
#ifdef __OS_VXWORKS__
#include <sioLib.h>
#endif
#include <osl_types.h>
#include <bsp_memmap.h>
#include <bsp_pmu.h>
#include <bsp_om.h>
#include <bsp_pm_om.h>
#include <bsp_icc.h>
#include <bsp_regulator.h>
#include <hi_pwrctrl_interface.h>
#define  regu_pr_err(fmt,...)		(bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_REGULATOR, "[regulator]: <%s> <%d>"fmt, __FUNCTION__, __LINE__, ##__VA_ARGS__))
#define  regu_pr_info(fmt,...)		(bsp_trace(BSP_LOG_LEVEL_INFO, BSP_MODU_REGULATOR, "[regulator]: <%s> <%d>"fmt, __FUNCTION__, __LINE__, ##__VA_ARGS__))
#define  regu_pr_debug(fmt,...)		(bsp_trace(BSP_LOG_LEVEL_DEBUG, BSP_MODU_REGULATOR, "[regulator]: <%s> <%d>"fmt, __FUNCTION__, __LINE__, ##__VA_ARGS__))

#ifndef REGU_OK
#define REGU_OK                 (0)
#endif
#ifndef REGU_ERR
#define REGU_ERR                (-1)
#endif
#ifndef EINVAL
#define EINVAL 					(22)
#endif
#ifndef MAX_WAIT_TIMEOUT
#define  MAX_WAIT_TIMEOUT         (0xff)
#endif

#ifndef SEM_Q_PRIORITY
#define SEM_Q_PRIORITY  (0)
#endif

#ifndef SEM_EMPTY
#define SEM_EMPTY 0
#endif
#ifndef ARRAY_SIZE
#define ARRAY_SIZE(a) (sizeof(a)/(sizeof((a)[0])))
#endif

#define REGULATOR_SUPPLY(_name, _dev_name)			\
{								\
	_name,				\
	_dev_name,				\
}
#define REGU_CONS_INIT(_id)	\
	struct regulator_consumer_supply consumer_supplies_##_id[]

#define REGU_INIT(_name, _id, _consumer_id, _num)	\
{_name, _id, _num, consumer_supplies_##_consumer_id }

struct regulator_msg {
	u32 volt_id;
	u32 min_uV;
	u32 max_uV;
	u32 ops_flag;   /*0:enable; 1:disable; 2:is_enabled; 3:get_voltage; 4:set_voltage*/
	s32 result;    /*0:success; 1:failed*/
};
#ifdef __cplusplus /* __cplusplus */
}
#endif /* __cplusplus */

#endif
