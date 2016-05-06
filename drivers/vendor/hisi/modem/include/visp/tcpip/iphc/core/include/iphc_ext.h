/*************************************************************************
 *
 *              Copyright 2005, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 * 
 *-----------------------------------------------------------------------*
 *
 *                         iphc_ext.h 
 *
 *  Project Code: VISP
 *   Module Name: IPHC
 *  Date Created: 2002/06/25
 *        Author: wangyue
 *   Description: 本头文件包含iphc模块的宏定义；   
 *
 *
 *-----------------------------------------------------------------------*
 *  Modification History
 *  DATE            NAME            DESCRIPTION
 *  2006-03-30      xiehuaguo       Adjust for D00647
 *  2006-05-13      l48923          Delete useless code
 *
 ************************************************************************/
 
#ifndef _IPHC_EXT_H_
#define _IPHC_EXT_H_

#ifdef  __cplusplus
extern "C"{
#endif

#include "tcpip/public/tcpip_basefun.h"

extern ULONG  EXEC_OutString(ULONG ulLineIndex, CHAR * szOutString);
extern ULONG EXEC_OutStringWait ( ULONG ulExecID, CHAR * szOutString, ULONG * ulCurLine );
extern ULONG  EXEC_GetUserLanMode(ULONG ulExecID);
extern VOID * IF_WaitListGet( VOID *pParam,VOID **pNewParam ) ;
extern IFNET_S * IF_SearchIfFromChain( IFNET_S * pIf , ULONG ulSearch );
ULONG IPHC_Cmd_CallCenter( VOID* pMsgRcv, VOID** ppMsgSnd );
extern ULONG CLI_NewDefineCmdElement ( CHAR  szTypeName[ CLI_CMDELEMENT_LENGTH + 1 ] , ULONG  ulOID ,
        ULONG ulModule , ULONG ulBelowValue,
        ULONG (* CheckFunc)(CHAR * , PVECTOR_S , PVECTOR_S ),
        ULONG (* HelpFunc)( CHAR * , PVECTOR_S , PVECTOR_S , PVECTOR_S * ),
        ULONG ulReturnCondition , ULONG ulValid , ULONG ulInvalid , 
        VOID *  pInfoEntry, ULONG   ulInfoID,
        PVECTOR_S * NewCmdDesVec );
extern ULONG CFG_ModuleRegister( ULONG ulModuleID, ULONG ulTaskID, ULONG ulQueueID, ULONG ulEventFlag, 
        ULONG (*msgProcCallBack)(VOID *, VOID**));
extern VOID IP_StrIpOptions(register MBUF_S *, MBUF_S *);
extern USHORT IN_Cksum(MBUF_S*, LONG);

extern IFNET_S *g_pstIfConfigNet;
extern ULONG DEBUG_IPHC_TCP ;
extern ULONG DEBUG_IPHC_RTP ;
extern ULONG gulMaxBoardNum;


#ifdef  __cplusplus
}
#endif  /* end of __cplusplus */

#endif  

