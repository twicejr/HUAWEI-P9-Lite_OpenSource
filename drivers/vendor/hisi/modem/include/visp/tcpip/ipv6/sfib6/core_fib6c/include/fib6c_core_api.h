/*******************************************************************************
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              fib6c_core_api.h
*
* Project Code: VISPV100R005
*  Module Name: SFIB6
* Date Created: 2003-07-08
*       Author: Zhang Hongyan
*  Description: apis provided for com interface to be called by shell 
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2003-07-08   Zhang Hongyan           Create
*  2006-03-30   Jiangtao                Adjust for D00645
*  2006-04-21   Jiangtao                Adjust for D00858 
*
*******************************************************************************/
 
#ifdef  __cplusplus
extern  "C"{
#endif

#ifndef _FIB6C_CORE_API_H
#define _FIB6C_CORE_API_H

/* apis provided for com interface, to be called by shell */

/* Management apis */
ULONG IP6_FIBContainer_Init_Com( COM_ID_INFO_S *pComInfo, ULONG  ulComLen);
ULONG IP6_FIBContainer_Activate_Com ();
ULONG IP6_FIBContainer_SetModuleInfo (IP6_FIBContainer_MOD_INFO_S *pMInfo);
/*f47854 modify : 函数参数或者返回值类型与函数指针定义不匹配*/
ULONG IP6_FIBContainer_RegShellApi(IP6_FIBContainer_SHELL_EV_CALLBACUP_SET_S *);

/* Functional api's */
ULONG IP6_FIB_GetBulkFIBData (USHORT usZoneID,
                              UINTPTR ulWaitlistIndex,
                              ULONG ulNumOfEntryWanted,
                              ULONG *pulNumOfEntryReturn,
                              RT6_ENTRY_S ** ppstFIBData);

#endif

#ifdef  __cplusplus
}
#endif

