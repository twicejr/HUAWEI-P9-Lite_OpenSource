/************************************************************************
  Copyright   : 2005-2007, Huawei Tech. Co., Ltd.
  File name   : Nasrrcinterface.h
  Author      : ---
  Version     : V200R001
  Date        : 2005-08-17
  Description : 该头文件定义了 AS 提供给 NAS 接口数据结构以及函数
  History     :
  1. Date:2005-08-17
     Author: ---
     Modification:Create
************************************************************************/

#ifndef _WUEPS_CONFIG_H_
#define _WUEPS_CONFIG_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

/* 把打印通过OM输出到PSTAS的控制开关 */
#if 1
#define PS_OM_DUMP_SWITCH 1
#endif

/******************************产品或者仪器兼容性开关******************************/
#define  WUEPS_RNC_SWICTH_ON        0
#define  WUEPS_CMU200_SWICTH_ON     1
#define  WUEPS_CRTUW_SWICTH_ON      2
// #define  WUEPS_RRM_SWICTH_ON        3

/*默认编译开关为RNC*/
#define  WUEPS_PRODUCT_SWITCH       WUEPS_RNC_SWICTH_ON

/* 等待标志定义 */
#define WUEPS_MSG_WAIT      ((VOS_UINT32)(-1))       /* 等待     */
#define WUEPS_MSG_NO_WAIT   (VOS_UINT32)0            /* 不等待   */

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif

