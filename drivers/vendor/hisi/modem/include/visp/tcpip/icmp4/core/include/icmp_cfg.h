/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              icmp_cfg.h
*
* Project Code: VISPV100R005
*  Module Name: ICMP4
* Date Created: 2006-01-24
*       Author: Li LiXiang
*  Description: 声明了Icmp中的配置函数声明和宏定义
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2006-01-24   Li LiXiang              Create
*  2006-04-21   Jiangtao                根据编程规范，对文件进行规范化整理
*
*******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif


#ifndef _ICMP_CFG_H_
#define _ICMP_CFG_H_


#define ICMP_DEBUG_ON                   1
#define ICMP_DEBUG_OFF                  0

#define ICMP_CLEAR_COUNTERS_ALL         0
#define ICMP_CLEAR_COUNTERS_MAIN        1
#define ICMP_CLEAR_COUNTERS_IO          2
#define ICMP_CLEAR_COUNTERS_INTERFACE   3

ULONG IP_ICMP_SetDebugFlag(ULONG ulDebugFlag);
ULONG IP_ICMP_GetDebugFlag(ULONG *pulDebugFlag);
ULONG IP_ICMP_GetStatics(ICMPSTAT_S * pstStat);
ULONG IP_ICMP_ClearCounters(ULONG ulSlotNumber);
ULONG IP_ICMP_ClearInterface( IPIFNET_S * pstIpIf);

/* add by z62531 ,禁ping功能设置/获取开关状态接口 */
ULONG IP_ICMP_SetPingForbidFlag(ULONG ulValue);
ULONG IP_ICMP_GetPingForbidFlag(ULONG * pulValue);

ULONG IP_ICMP_GetIcmpStatbyVrf(ULONG ulVrfIndex, ICMPSTATVRF_S *pstStat);
ULONG IP_ICMP_ClearIcmpStatbyVrf(ULONG ulVrfIndex);
ULONG IP_ICMP_ClearIcmpFlowStat(UCHAR ucFlowStatType, ULONG ulVrfIndex);
ULONG IP_ICMP_CreateIcmpFlowStat(UCHAR ucFlowStatType, UCHAR ucNumber);
ULONG IP_ICMP_GetIcmpFlowStat(UCHAR ucFlowStatType, ULONG ulVrfIndex, UCHAR *pucNumber, VOID *pStat);
ULONG IP_ICMP_EnableIcmpStat(ULONG ulOper);

#endif  /* end of _ICMP_CFG_H_ */ 

#ifdef __cplusplus
}
#endif/* end of __cplusplus */

