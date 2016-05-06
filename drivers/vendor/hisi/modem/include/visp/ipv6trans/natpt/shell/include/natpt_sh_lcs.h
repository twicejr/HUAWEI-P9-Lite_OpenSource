/************************************************************************
 *
 *    Copyright 2003, Huawei Technologies Co. Ltd  India Institute  
 *                     ALL RIGHTS RESERVED                           
 *                                                 
 *----------------------------------------------------------------------*
 *
 *                             NATPT_sh_lcs.h
 *
 *  Project Code:       VRPv5 
 *  Create Date:        2003-7-21
 *  Author:             Desh   (VRPv5 IPv6 Team) 
 *  Document:
 *  Function Description:
 *  
 *----------------------------------------------------------------------*
 *  Modification History 
 *  DATE        NAME             DESCRIPTION
 *  
 *  
 ************************************************************************/



#ifndef _NATPT_SH_LCS_H
#define _NATPT_SH_LCS_H

#ifdef	__cplusplus
extern	"C"{
#endif


/*----------------------------------------------*
 * Header Files                
 *----------------------------------------------*/
  #define MAX_SPECS_FOR_NATPT    5
  #define NATPT_MAX_ADDR_MAP    1000
  #define NATPT_MIN_ADDR_MAP    0 
  #define NATPT_AVL_ADDR_MAP    1000
  
  #define NATPT_MAX_DPAT         1000
  #define NATPT_MIN_DPAT         0 
  #define NATPT_AVL_DPAT         1000
  
  #define NATPT_MAX_SESSIONS     50000
  #define NATPT_MIN_SESSIONS    0
  #define NATPT_AVL_SESSIONS     10000
  
  #define NATPT_PAT_ENABLE      1
  
  #define NATPT_DPAT_ENABLE    1

 #define NATPT_LCS_INIT_ERROR_PAF_LCS 10
 #define NATPT_LCS_INIT_ERROR_REGISTER_CALLBACK 20
  
/*----------------------------------------------*
 * External Variables            
 *----------------------------------------------*/
 /*this will be defined in the shell_init*/
  
/*----------------------------------------------*
 * Global Variables    
 *----------------------------------------------*/
 
/*----------------------------------------------*
 * External Functions
 *----------------------------------------------*/

/*----------------------------------------------*
 * Functions
 *----------------------------------------------*/
VOID NATPT_LCS_UpdateCallBack() ;
ULONG NATPT_License_PAF_Apply(struct IIF_IPV6_NATPT_ComINTF_CFGVtbl *pstComCfgTable) ;

ULONG NATPT_License_PAF_Update ();
ULONG NATPT_GetSpecs_Resource(SPECS_RES_VALUE_S *pstResValue);
ULONG NATPT_GetSpecs_Service_Func(SPECS_FUN_VALUE_S *pstFunValue);


#ifdef	__cplusplus
}
#endif

#endif
