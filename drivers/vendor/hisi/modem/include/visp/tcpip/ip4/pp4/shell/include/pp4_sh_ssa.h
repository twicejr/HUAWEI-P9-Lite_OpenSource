/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              pp4_sh_ssa.h
*
* Project Code: VISPV100R005
*  Module Name: PP4
* Date Created: 2002-06-18
*       Author: chenshuanglong(28510)
*  Description: PP4模块shell系统支持辅助结构体，变量和函数声明
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2002-06-18   chenshuanglong(28510)   Create
*  2006-11-07   zhoutong(43740)         规范性整改
*
*******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif


#ifndef _PP4_SH_SSA_H_
#define _PP4_SH_SSA_H_


#define IP_PP4_INPUT_QUEUE_LEN              5000
#define IP_PP4_IN_PKTS_PER_DISPATCH         500

/* Packet Queue Initialization */
extern ULONG IP_PP4_SH_PktQueInit();

#endif   /* end of _PP4_SH_SSA_H_ */ 

#ifdef __cplusplus
}
#endif/* end of __cplusplus */


