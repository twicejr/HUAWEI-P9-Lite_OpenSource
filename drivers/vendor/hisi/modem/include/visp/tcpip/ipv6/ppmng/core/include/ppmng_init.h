/******************************************************************************
 *
 *        Copyright 2003-2006  Huawei Technologies India Private Limited
 *                          All Rights Reserved
 *
 *------------------------------------------------------------------------------
 *                            ppmng_init.h
 *    Project Code:  VRP5.0
 *    Module Name:  IP6 PP
 *    Create Date:  2003/06/10
 *         Author:  Arun H S
 *     Description: Initailize the IPv6 Stack.
 *------------------------------------------------------------------------------
 *  Modification History                                                        
 *  DATE        NAME             DESCRIPTION                                    
 *  ----------------------------------------------------------------------------
 *  2003-06-10  Arun H S         Create
 ******************************************************************************/ 
#ifndef _IP6_PPMNGCOREINIT_H
#define _IP6_PPMNGCOREINIT_H

#ifdef __cplusplus
extern "C"{
#endif


typedef VOID  (*pfConvtoVoidFunc)(VOID *); 

/* Function Prototypes. */
VOID IP6_PP_AddNewDomain(IP6_PP_DOMAIN_S  * pstDom);
VOID IP6_PP_Initialize();
VOID IP6_PP_Init();
VOID IP6_PP_Drain ();
LONG IP6_PP_SysCtl(LONG *pstName, ULONG ulNameLen, VOID *pOld, 
                ULONG *pulOldLen, VOID *pNew, ULONG ultNewLen);
/* END: Function Prototypes. */

#ifdef __cplusplus
}
#endif

#endif 

