/*****************************************************************
*        Copyright 2003-2006  Huawei Technologies India Private Limited
*                          All Rights Reserved
*-----------------------------------------------------------------
*                              Tcp6_sh_init_api.h
*
*    Project Code : VRP5.0
*    Module Name  : IP6 TCP6
*     Version     : Initial Draft
*    Create Date  : 2003/06/27
*    Author       : Naina Gupta
*    Description  : Initialize the shell and main loop process funtion apis
*-----------------------------------------------------------------
*  Modification History
*  DATE        NAME           DESCRIPTION
*-----------------------------------------------------------------
*  2003-06-27  Naina Gupta    Create
*  2006-06-02  Alok           Updated for 14 Fly-Check rules adherence
*                             for IPOSIR-V1R1-IPv6
******************************************************************
*/
#ifndef _TCP6_SH_INIT_API_H
#define _TCP6_SH_INIT_API_H

#ifdef  __cplusplus
extern "C"{
#endif

#define IP6_TCP6_ENABLE_CLI     1
#define IP6_TCP6_DISABLE_CLI    0

ULONG IP6_TCP6_SH_Init();
ULONG IP6_TCP6_SH_DeInit();

#ifdef  __cplusplus
}
#endif  /* end of __cplusplus */

#endif  /* #ifndef _TCP6_SH_INIT__API_H */
