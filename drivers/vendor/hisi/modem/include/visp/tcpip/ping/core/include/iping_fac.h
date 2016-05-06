/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              Iping_fac.h
*
*  Project Code: VISP1.5
*   Module Name: ping  
*  Date Created: 2006-04-25
*        Author: luyao(60000758)
*   Description: declare ping Component factory creation and Query
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2006-4-28  luyao(60000758)         Creat the first version.
*  2006-04-27  luyao            根据编程规范，对文件进行规范化整理
*
*******************************************************************************/

#ifndef _PING_FAC_H_
#define _PING_FAC_H_
#ifdef  __cplusplus
extern  "C"{
#endif

/*PING  Component interface of function */
extern IIF_PING_ComIntFUN g_IComInt_Ping_FUN;
/*PING Component interface of configration*/
extern IIF_PING_ComIntCFG g_IComInt_Ping_CFG;

ULONG ImplIPPingFactoryQueryInterface(IUnknown * This, COMP_IID iid, LPVOID * ppvObj);
ULONG ImplIPPingFactoryCreateInstance(IComponentFactory *This,  COMP_IID iid, VOID **ppvObj );

#ifdef  __cplusplus
}
#endif
#endif 


