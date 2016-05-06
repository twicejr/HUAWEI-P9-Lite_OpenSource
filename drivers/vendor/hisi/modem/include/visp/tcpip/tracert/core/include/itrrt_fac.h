/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              Itrrt_fac.h
*
*  Project Code: VISP1.5
*   Module Name: Traceroute Module 
*  Date Created: 2003-07-14
*        Author: suraj( )
*   Description: declare trrt Component factory creation and Query
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME                 DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2003-07-14  suraj( )         Creat the first version.
*
*******************************************************************************/

#ifndef    _TRRT_FAC_H_
#define    _TRRT_FAC_H_
#ifdef    __cplusplus
extern "C"{
#endif

/* Component interface of function */
extern struct  IIF_TRRT_ComIntFUN     g_Trrt_ComIntFun ; 
/* Component interface of configration */
extern struct  IIF_TRRT_ComIntCFG  g_Trrt_ComIntCfg ; 
ULONG ImplTrrtFactoryQueryInterface(IUnknown * This, COMP_IID iid, LPVOID * ppvObj);
ULONG ImplTrrtFactoryCreateInstance(IComponentFactory *This,  COMP_IID iid, VOID **ppvObj );


#ifdef __cplusplus
}
#endif

#endif 
