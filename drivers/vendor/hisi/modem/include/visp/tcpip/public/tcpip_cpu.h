/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              tcpip_cpu.h
*
*  Project Code: VISP V1R6C02
*   Module Name: PUBLIC  
*  Date Created: 2008-04-08
*        Author: mafeng(59090)
*   Description: 定义编译器CPU类型
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2008-04-08   mafeng(59090)           Create
*
*******************************************************************************/
#ifndef _TCPIP_CPU_H_
#define _TCPIP_CPU_H_


#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

#ifdef TCPIP_CPUTYPE
#define VISP_CPUTYPE TCPIP_CPUTYPE
#else
#define VISP_CPUTYPE 0
#endif


#define CPU_INTEL       0    /* 0 Intel CPU */
#define CPU_PPC604      1    /* 1 PowerPC 604 */
#define CPU_PPC860      2    /* 2 */
#define CPU_PPC603      3    /* 3 */
#define CPU_PPC85XX     4    /* 4 */   
#define CPU_XSCALE      5    /* 5 */
#define CPU_PPCEC603    6    /* 6 */ 
#define CPU_MIPS32      7    /* 7 */   
#define CPU_MIPS64      8    /* 8 */
#define CPU_ARM926      9    /* 9 */
#define CPU_PPC32       10   /* 10 PowerPC 32*/
#define CPU_MAX         11   /* 枚举上限 */


#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif  /* end of _TCPIP_CPU_H_ */


