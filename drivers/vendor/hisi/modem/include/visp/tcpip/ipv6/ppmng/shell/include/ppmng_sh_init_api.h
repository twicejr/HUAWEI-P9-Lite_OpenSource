/*****************************************************************
*        Copyright 2003-2006  Huawei Technologies India Private Limited        
*                          All Rights Reserved                                 
*-----------------------------------------------------------------
*                              pp_sh_init_api.h                                
*                                                                              
*    Project Code:  VRP5.0                                                     
*    Module Name:  IP6 PP                                                      
*    Create Date:  2003/06/09                                                  
*    Author:       Mahaveera Jain                                              
*    Description:  Initialize the shell and main loop process funtion apis     
*-----------------------------------------------------------------
*  Modification History                                                        
*  DATE        NAME             DESCRIPTION                                   
*  ----------------------------------------------------------------
*  2003-06-09  Mahaveer Jain    Create                                                                                                                       
*******************************************************************/
#ifndef _PP_SH_INIT_API_H
#define _PP_SH_INIT_API_H

#ifdef      __cplusplus
extern "C" {
#endif        /* end of __cplusplus */

/*w39533 2004-11-08 sync D24*/
/* Modified by Rajesh for Product support Defect id BYAD11615 */
VOID  IP6_PP_ProductRegister(IP6_PRODUCT  eProduct , ULONG ulValue);
VOID  IP6_PP_ProductUnRegister(IP6_PRODUCT  eProduct , ULONG ulValue);


ULONG IP6_PP_SH_GlobalInit();
ULONG IP6_PP_SH_Init();
ULONG IP6_PP_SH_DeInit();
ULONG IP6_PP_SH_Function_GetStatus();

#ifdef      __cplusplus
}
#endif        /* end of __cplusplus */

#endif

