/************************************************************************
 *
 *    Copyright 2003, Huawei Technologies Co. Ltd  India Institute  
 *                     ALL RIGHTS RESERVED                           
 *                                                 
 *----------------------------------------------------------------------*
 *
 *                             natpt_sh_func.h
 *
 *  Project Code:       VRPv5 
 *  Create Date:        2003-7-7
 *  Author:             Soumya   (VRPv5 IPv6 Team) 
 *  Document:
 *  Function Description:
 *  
 *----------------------------------------------------------------------*
 *  Modification History 
 *  DATE        NAME             DESCRIPTION
 *  
 *  2003-12-2  Usha             For Defect BYAD04881   
 *  2004-01-12 Archana PV       For Defect BYAD06698
 ************************************************************************/

#ifndef _NATPT_SH_FUNC_H
#define _NATPT_SH_FUNC_H

#ifdef  __cplusplus
extern  "C"{
#endif


/* hided by Leonru*/
/*
#include "config/cmdline/cmdline.h"
#include "ifnet/ifinc/if_pub.h"

#include "ipv6trans/natpt/shell/include/natpt_sh_stub.h"
#include "ipv6trans/natpt/shell/include/natpt_shdef.h"
*/
/*added by Desh*/

  
/*----------------------------------------------*
 * Functions 
 *----------------------------------------------*/
VOID NATPT_RegCmd(VOID);
/* Functions related to Command Installing */
VOID NATPT_Cmd_Enable(VOID);
VOID NATPT_Cmd_SetStaticV6V4bound(VOID);
VOID NATPT_Cmd_SetStaticV4V6bound(VOID);
VOID NATPT_Cmd_AgeOut(VOID);
VOID NATPT_Cmd_SetMaxSessions(VOID);
VOID NATPT_Cmd_Clear(VOID);
VOID NATPT_Cmd_Debug(VOID);
VOID NATPT_Cmd_ConfIpv4AddrGrp(VOID);
VOID NATPT_Cmd_DynV6Bound(VOID);
VOID NATPT_Cmd_DynV6BoundNoPAT(VOID);
VOID NATPT_Cmd_DynV4Bound(VOID);
VOID NATPT_Cmd_Prefix(VOID);
VOID NATPT_Cmd_Display(VOID);
/* for defect BYAD04881 */
VOID NATPT_Cmd_TrafficClass (VOID);
/* end of defect BYAD04881 */

/* for defect BYAD11433 */
VOID NATPT_Cmd_AllowPrivateAddr (VOID);
/* end of defect BYAD11433 */

/*Added by Archan for MST*/
ULONG NATPT_Shell_Interface_Delete(ULONG ulInfIndex);
ULONG NATPT_Shell_Board_PlugOut(ULONG ulSlot );
VOID NATPT_Shell_IfnetHotNotifyCB (ULONG ulEvent, ULONG ulSot, VOID *pstIfnet, ULONG ulIfIndex);

/* Functions related to Command Processing */

ULONG NATPT_ConfigProc( VOID *pMsg,VOID **ppMsgSnd );
ULONG NATPT_Enable( VOID *pMsg,VOID **ppReplyMsg );
ULONG NATPT_StaticV6V4BoundAddr(VOID *pMsg,VOID **ppReplyMsg);
ULONG NATPT_StaticV4V6BoundAddr(VOID *pMsg,VOID **ppReplyMsg);
ULONG NATPT_AgeOut(VOID *pMsg,VOID **ppReplyMsg);
ULONG NATPT_MaxSessions( VOID *pMsg,VOID **ppReplyMsg );
ULONG NATPT_Clear( VOID *pMsg,VOID **ppReplyMsg );
ULONG NATPT_ConfIpv4AddrGrp(VOID *pMsg,VOID **ppReplyMsg);
ULONG NATPT_DynV4Bound( VOID *pMsg,VOID **ppReplyMsg );
ULONG NATPT_DynV6Bound( VOID *pMsg,VOID **ppReplyMsg );
ULONG NATPT_Prefix(VOID *pMsg,VOID **ppReplyMsg);
ULONG NATPT_Debug(VOID *pMsg,VOID **ppReplyMsg);
ULONG NATPT_Display(VOID *pMsg,VOID **ppReplyMsg);
ULONG NATPT_DisplayIpv4AddrGrp( ULONG ulExecID,ULONG *pulLines );
ULONG NATPT_DisplayAgingTime( ULONG ulExecID,ULONG *pulLines );
ULONG NATPT_DisplayV4BDynInfo( ULONG ulExecID,ULONG *pulLines );
ULONG NATPT_DisplayV6BDynInfo( ULONG ulExecID,ULONG *pulLines );
/*For Defect BYAD06698*/
ULONG NATPT_DisplaySessions( ULONG ulExecID,ULONG *pulLines,ULONG ulSlot,ULONG ulPro );
ULONG NATPT_MainDisplaySession ( ULONG ulExecID,ULONG *pulLines,ULONG ulPro);
/*End of Defect BYAD06698*/
ULONG NATPT_DisplayFrag( ULONG ulExecID,ULONG *pulLines,ULONG ulSlot );
ULONG NATPT_MainDisplayFrag ( ULONG ulExecID,ULONG *pulLines);

ULONG NATPT_DisplayPrefixInfo( ULONG ulExecID,ULONG *pulLines );

/* For defect BYAD04881 */
ULONG NATPT_TrafClass(VOID *pMsg,VOID **ppReplyMsg);
/* end of defect BYAD04881 */

/* For defect BYAD11433 */
ULONG NATPT_AllowPrvAddr (VOID *pMsg,VOID **ppReplyMsg);
/* End of defect BYAD11433 */

VOID NATPT_Cmd_ClearStatistics(VOID);

ULONG NATPT_DisplayStatistics( ULONG ulExecID,ULONG *pulLines,ULONG ulSlot );
ULONG NATPT_DisplayAddrMapping( ULONG ulExecID,ULONG *pulLines );

/* Functions related to Build */

ULONG NATPT_BuildRun( CHAR * szSectionName, CHAR** pszBuildRunInfo );
ULONG NATPT_BuildInterface( CHAR * szSectionName, CHAR** pszBuildRunInfo );
VOID NATPT_RegBuild(VOID);

/* Functions related to validation */


/* functions of natpt_sh_debug.c */



ULONG NATPT_getMainboardId();

extern ULONG  IP_FIB_AllocValid( ROUTE_S *pRo );
extern VOID ACL_PacketFilterWithParam(UCHAR, ULONG, ULONG, ULONG, ULONG *);
extern ULONG ACL_PacketFilterWithParamByName (UCHAR protocol, CHAR *  szListName, ULONG srcaddr, 
                                                       ULONG dstaddr,ULONG *iRet); 

extern ULONG IP_Output( MBUF_S *pstMBuf, MBUF_S *pstMOpt, ROUTE_S *pstRo, LONG lFlags, IPMOPTIONS_S *pstIpMo );
extern VOID ICMP_Error(MBUF_S *pstMBuf, LONG ltype, LONG lcode, ULONG ulnlDest, IFNET_S *pstIfNet );

extern ULONG IFNET_SlotCheckWithMainBoard(CHAR *pCheckStr, PVECTOR_S UserCmd,PVECTOR_S CmdElementVec);
extern ULONG IFNET_SlotCheckWithoutMainBoard( CHAR *pCheckStr, PVECTOR_S UserCmd,PVECTOR_S CmdElementVec);
extern ULONG  CFG_SendReplyMsg ( VOID * pMsgRep );
VOID NATPT_DebugToIC(CHAR * szString, ULONG ulLevel);



VOID* NATPT_Shell_HA_MemAllocate (ULONG ulPayloadSize );
/* ULONG HA_Register(ULONG ulModuleID, ULONG ulSubID, ULONG ulPriority, PF_HACALLBACK pfHACallback) ; */
ULONG  NATPT_Shell_HA_MemFree (VOID * );
ULONG NATPT_HA_RTBackupSend (UCHAR *pucData ,ULONG ulLength ) ;
ULONG NATPT_HA_BatchBackupSend (UCHAR *pucData ,ULONG ulLength ) ;
BOOL_T  NATPT_HA_IsSMBExisting ( VOID );
VOID NATPT_RegToIC(VOID);
LONG NATPT_DebugAll(VOID);
LONG NATPT_DebugAll(VOID);
LONG NATPT_NoDebugAll(VOID);
VOID NATPT_Analyse_Result_Multicast(VOID* pSendData , ULONG ulslot );
LONG NATPT_ShowDebugging( CHAR *pszStatusStr,ULONG ulMaxLen, ULONG ulIfIndex,
            ULONG *pulWaitListIndex, ULONG ulInterface );
ULONG NATPT_LCS_PAF_Init() ;

/*Added for License CLI Enable / Disable*/
ULONG NATPT_Sh_DPAT_NotifyChange(ULONG ulCLIState);
ULONG NATPT_Sh_PAT_NotifyChange(ULONG ulCLIState);
ULONG NATPT_SH_CliChangeNotifyAll(ULONG ulCliState,ULONG ulChagePos);
ULONG NATPT_SH_RegisterCliChangeNotify(ULONG (* pfNATPT_NotifyCliChange)(ULONG ulCliState),ULONG ulChangeParam);

extern ULONG getSelfBoardId(VOID);
extern ULONG    CFM_InstallBuildRun (CHAR *, ULONG, ULONG (*)( CHAR *, CHAR** ) );
extern ULONG getMainboardId(VOID);
extern IFNET_S * IF_GetIfByFullName(CHAR *);
extern ULONG IP_Get_IF_MainIpAddr(IFNET_S *pstIf);
extern ULONG    EXEC_OutStringWait ( ULONG ulExecID, CHAR * szOutString, ULONG * ulCurLine );
extern ULONG OutStringConsole (CHAR *);

extern LONG  IC_RegDebugOperateCB( ULONG ulModuNo,
                                   CHAR* szModuName ,
                                   IF_SELECT_TYPE * pstIfType,
                                   IC_DebugAll_PF  pfMyDebugAll,
                                   IC_NoDebugAll_PF  pfMyNoDebugAll,
                                   IC_ShowDebugging_PF  pfMyShowDebugging);

#ifdef  _cplusplus
}
#endif

#endif

