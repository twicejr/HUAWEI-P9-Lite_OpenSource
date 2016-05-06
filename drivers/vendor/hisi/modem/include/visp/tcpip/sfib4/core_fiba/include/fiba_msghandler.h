/*******************************************************************************
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              fiba_msghandler.h
*
* Project Code: VISPV100R005
*  Module Name: SFIB4
* Date Created: 2003-07-08
*       Author: Zhang Hongyan
*  Description: Prototypes for fib6a_msghandler.h
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


#ifndef _FIBA_MSGHANDLER_H
#define _FIBA_MSGHANDLER_H


#define URT6_IID_INDEX          0
#define FIB6CONTR_IID_INDEX     1

extern ULONG IF_BoardIsUp(ULONG ulSlot);
extern ULONG getSelfBoardId ();
extern ULONG getMainboardId ();
extern ULONG EXEC_OutString(ULONG ulLineIndex, CHAR * szOutString);

ULONG IP6_FIB_KRTMsgSend (RTMSG6_S *pstRtMsg);
ULONG IP_FIB_KRTMsgSend (RTMSG4_S *pstRtMsg);
VOID  IP_FIB_RTMSG_Receive () ;
ULONG IP6_FIBA_AllocValid (ROUTE6_S* pstRoute6, BOOL_T bEnableRouteBal);
ULONG IP_FIB_AllocValid (ROUTE4_S* pstRoute);
/* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
ULONG IP4_GetIfIndexByDstIP(ULONG ulDstIp,ULONG * pulOutIfIndex, ULONG ulVrfIndex);
/* End: VISP1.7C03 VRF qinyun , 2009-01-20 */

ULONG IP_FIBAgent_Init_Com(COM_ID_INFO_S *pstComInfo, ULONG  ulComLen) ;
ULONG IP_FIBAgent_Activate_Com ();
ULONG IP_FIBAgent_SetModuleInfo (IP6_FIBAgent_MOD_INFO_S *pstMInfo);
ULONG IP_FIBAgent_RegShellApi( IP6_FIBAgent_SHELL_EV_CALLBACUP_SET_S *pfCallBackSet );
ULONG IP6_FIBA_RegFENotify (FE_DOWNLOAD_FUNC_SET_S *pstFECallBackSet_Fib6A);
VOID  IP_FIB_SetMemShortageFlag (ULONG ulMSFlag);
ULONG IP_Search_VispFIB (ROUTE4_S* pstRoute);

ULONG IP4_GetPMtuByFIB(ULONG ulDstIp, ULONG *pulPMtu, ULONG ulVrfIndex);

#endif /* #ifndef _FIB6A_MSGHANDLER_H */

#ifdef  __cplusplus
}
#endif

