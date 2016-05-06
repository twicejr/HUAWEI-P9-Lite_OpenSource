/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              am4_sh_init.h
*
* Project Code: VISPV100R005
*  Module Name: AM4
* Date Created: 2006-01-04
*       Author: Li LiXiang
*  Description: 声明shell初始化相关变量和函数原型
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2006-01-04   Li LiXiang              Create
*  2006-04-21   Jiangtao                根据编程规范，对文件进行规范化整理
*  2006-11-07   zhoutong(43740)         规范性整改
*
*******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif


#ifndef _AM4_SH_INIT_H_
#define _AM4_SH_INIT_H_


#define IP_AM4_SH_INIT    ((SYSTRC_IP_AM4_BASE << 8) + 40) 
#define IP_AM4_SH_IC      ((SYSTRC_IP_AM4_BASE << 8) + 41) 
#define IP_AM4_SH_CONFIG  ((SYSTRC_IP_AM4_BASE << 8) + 42) 

/* shell使用到的虚表指针 */
extern struct IIF_IP_PP4_ComIntFunVtbl      * g_pstAm4ShPPVtbl ;
extern struct IIF_IPV4_IP_AM4_ComIntSSAVtbl * g_pstAM4ComSSATable;
extern struct IIF_IPV4_IP_AM4_ComIntCFGVtbl * g_pstAM4ComCfgTable;
extern struct IIF_IPV4_IP_AM4_ComIntFUNVtbl * g_pstAM4ComFunTable;

/* 错误信息语种(中英文)索引 */
extern ULONG g_ulAM4ErrInfoIndex;

/* AM4模块调试开关 */
extern ULONG g_ulIPAm4DebugFlag;

extern VOID IP_AM4_SetDebugSwitch(ULONG ulSwitch);
#endif  /* end of _AM4_SH_INIT_H_ */ 


#ifdef __cplusplus
}
#endif/* end of __cplusplus */

