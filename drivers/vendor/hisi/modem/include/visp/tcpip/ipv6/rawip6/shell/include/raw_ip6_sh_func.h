/*****************************************************************
*        Copyright 2003-2006  Huawei Technologies India Private Limited
*                          All Rights Reserved
*-----------------------------------------------------------------
*                              raw_ip6_sh_func.h
*
*    Project Code: VRP5.0
*    Module Name : IP6 RIP6
*    Version     : Initial Draft
*    Create Date : 2003/06/22
*    Author      : Sunil Dutt
*    Description : Contains the Prototypes of RawIP6 Shell Initialization
*                  related Functions
*-----------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------
*  2003-06-22  Sunil Dutt       Create
*  2006-06-02  Aparna           Updated for 14 Fly-Check rules adherence
*                                  for IPOSIR-V1R1-IPv6
*******************************************************************/

#ifndef _RAW_IP6_SH_INIT_API_H
#define _RAW_IP6_SH_INIT_API_H

#ifdef  __cplusplus
extern "C"{
#endif

ULONG IP6_RIP6_SH_Init();
ULONG IP6_RIP6_SH_DeInit();


/*Sandeep Added for IPBIR Version*/
const CHAR * IPBIRVersion_RawIP6();

//extern void vos_printf(char *fmt, ...);

#ifdef  __cplusplus
}
#endif

#endif

