/***********************************************************************
*        Copyright 2003-2006  Huawei Technologies India Private Limited        
*                          All Rights Reserved                                 
*-----------------------------------------------------------------------
*                              pp_sh_ic.h                                      
*                                                                              
*    Project Code: VRP5.0                                                      
*    Module Name:  IP6 BASIC PP                                                
*    Create Date:  2003/04/29                                                  
*         Author:  Mahaveer Jain                                               
*     Description: Shell ic implement header file for PP module                
*-----------------------------------------------------------------------
*  Modification History                                                        
*  DATE        NAME             DESCRIPTION                                    
*  ----------------------------------------------------------------------
*  2003-06-10  Mahaveer Jain    Create                                         
*************************************************************************/
#ifndef _PP_SH_IC_H
#define _PP_SH_IC_H

#ifdef      __cplusplus
extern "C" {
#endif        /* end of __cplusplus */


#define PPMNG_DBGID_INFO    IC_INFOID_DEF(MID_COMP_PPMNG, IC_INFO_DEBUG, 0)

#define     PPMNG_LOGID_INFO_REASFULL          IC_INFOID_DEF(MID_COMP_PPMNG, IC_INFO_LOG, 0)
#define     PPMNG_LOGID_INFO_REASPAFULL        IC_INFOID_DEF(MID_COMP_PPMNG, IC_INFO_LOG, 1)
/*syn D038 by x36308 2005-7-5*/
#define     PPMNG_LOGID_INFO_RPCCALLFAIL     IC_INFOID_DEF(MID_COMP_PPMNG, IC_INFO_LOG, 2) 

#define NO_USE(var)     (VOID)(var)

LONG IP6_PP_SH_DebugAll();
LONG IP6_PP_SH_NoDebugAll();
ULONG IP6_PP_SH_ShowDebugging(CHAR *szStatusStr,
                                ULONG ulMaxLen,  ULONG ulDebugIndx,
                                ULONG *pulWaitlistHandle,  ULONG ulInterface ) ;
ULONG IP6_PP_SH_Reg2IC();
VOID   IP6_PP_SH_SendInfo2IC (MBUF_S *pstMBuf,  ULONG ulIfIndex,    const CHAR *pszInfo,
                                    const CHAR *pszPrompt);
/*syn D038 x36308 2005-7-5*/
VOID IP6_PP_SH_SendLogInfo2IC (ULONG ulLogType, UCHAR *pszInfo);

#ifdef      __cplusplus
}
#endif        /* end of __cplusplus */


#endif

