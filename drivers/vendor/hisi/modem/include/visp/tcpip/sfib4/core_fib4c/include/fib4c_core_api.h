/*******************************************************************************
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              fib4c_core_api.h
*
* Project Code: VISPV100R005
*  Module Name: SFIB4
* Date Created: 2003-07-08
*       Author: Zhang Hongyan
*  Description: apis provided for com interface to be called by shell 
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2003-07-08   Zhang Hongyan           Create
*  2006-03-30   Jiangtao                Adjust for D00646
*  2006-04-21   Jiangtao                Adjust for D00859
*
*******************************************************************************/

#ifdef  __cplusplus
extern  "C"{
#endif

#ifndef _FIB4C_CORE_API_H
#define _FIB4C_CORE_API_H

/*apis provided for com interface, to be called by shell */

/* Management apis */
ULONG IP4_FIBContainer_Init_Com( COM_ID_INFO_S *pComInfo, ULONG  ulComLen);
ULONG IP4_FIBContainer_Activate_Com ();
ULONG IP4_FIBContainer_SetModuleInfo (IP4_FIBContainer_MOD_INFO_S *pMInfo);
/*f47854 modify : 函数参数或者返回值类型与函数指针定义不匹配*/
ULONG IP4_FIBContainer_RegShellApi(IP4_FIBContainer_SHELL_EV_CALLBACUP_SET_S *);

/* Functional api's */
/* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
ULONG IP4_FIB_GetBulkFIBData ( UINTPTR ulWaitListHandle,
                               ULONG ulVrfIndex,
                               ULONG ulNumOfEntryWanted,
                               ULONG *pulNumOfEntryReturn,                                    
                               RT4_ENTRY_S **ppstFIBData);

ULONG IP4_FIB_GetBulkFIBData_PT(UINTPTR ulWaitListHandle,
                                ULONG ulVrfIndex,
                                ULONG ulNumOfEntryWanted,
                                ULONG *pulNumOfEntryReturn,                                    
                                RT4_ENTRY_S **ppstFIBData);
/* End: VISP1.7C03 VRF qinyun , 2009-01-20 */

ULONG IP4_FIB_Request_PT(RTMSG4_S * pstRtMsgIn);


#endif

#ifdef  __cplusplus
}
#endif
