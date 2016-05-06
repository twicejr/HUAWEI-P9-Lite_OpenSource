/***********************************************************************
*        Copyright 2003-2006  Huawei Technologies India Private Limited        
*                          All Rights Reserved                                 
*-----------------------------------------------------------------------
*                              pp_sh_ssa.h           
*    Project Code: VRP5.0                                                      
*    Module Name:  IP6 BASIC PP                                                
*    Create Date:  2003/06/10                                                  
*         Author:  Mahaveer Jain                                               
*     Description: Shell ssa implement header file for PP module                
*-----------------------------------------------------------------------
*  Modification History                                                        
*  DATE        NAME             DESCRIPTION                                    
*  ----------------------------------------------------------------------
*  2003-06-10  Mahaveer Jain    Create                                         
*************************************************************************/
#ifndef _PP_SH_SSA_H
#define _PP_SH_SSA_H

#ifdef      __cplusplus
extern "C" {
#endif        /* end of __cplusplus */

#define IP6_PP_TIMER_TIMEOUT 0x1

ULONG IP6_PP_SH_AsynEnQue(IP6_PP_Timer_MSG_S *pstMsg);
ULONG IP6_PP_SH_TimerQCallBack(IP6_PP_Timer_MSG_S *pstMsg);
ULONG IP6_PP_SH_PktQueInit();
VOID IP6_PP_SH_ReceivePacket (MBUF_S *pstMBuf);

#ifndef pfRCV_FUN
typedef    VOID   (*pfRCV_FUN)(MBUF_S *,ULONG ); /*用于MBUF_TR_RegisterReceiver中强制类型转换*/
#endif

#ifdef      __cplusplus
}
#endif      /* end of __cplusplus */

#endif

