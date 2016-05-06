/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              pppmux_sh_disp.h
*
*  Project Code: VISPV100R005
*   Module Name: PPPMUX
*  Date Created: 2006-5-9
*        Author: ZhouTong(43740)
*   Description: PPPMUX相关的查询函数定义
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2006-5-9  ZhouTong(43740)    Create
*
*******************************************************************************/
#ifndef _PPPMUX_SH_DISP_H_
#define _PPPMUX_SH_DISP_H_

#ifdef  __cplusplus
extern  "C"{
#endif

/* 显示指定接口相关的配置信息 */
VOID PPPMUX_ShowMuxConfig(ULONG ulIfIndex);

/* 显示指定接口的PPPMUXCP协议协商结果*/
VOID PPPMUX_ShowMuxNegoResult(ULONG ulIfIndex);

/* 显示指定接口的PPPMUX统计信息 */
VOID PPPMUX_ShowMuxStat(ULONG ulIfIndex);

/* 计算平均值 */
ULONG PPPMUX_GetAverage(ULONG ulDividend, ULONG ulDivisor, ULONG* pulAvgHigh, ULONG* pulAvgLow);

/*DEBUG信息输出*/
VOID PPPMUX_DebugOutput(CHAR *pszMsg);


#ifdef  __cplusplus
}
#endif

#endif/*# end of _PPPMUX_SH_DISP_H_ */

