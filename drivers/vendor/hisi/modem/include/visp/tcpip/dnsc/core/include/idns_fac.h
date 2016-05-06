/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              Idns_fac.h
*
*  Project Code: VISP1.5
*   Module Name: DNSC Module  
*  Date Created: 2004-03-12
*        Author: Zhang Hongyan(19316)
*   Description: 
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME                 DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2004-03-12  Zhang Hongyan(19316)         Creat the first version.
*
*******************************************************************************/

#ifdef  __cplusplus
extern  "C"{
#endif

#ifndef _I_DNSC_FAC_H_
#define _I_DNSC_FAC_H_

/* For implement of QuerfyInstance() */
typedef struct tag_DNSC_INT_OBJ_S
{
    IIF_COMP_DNSC_ComIntFUN   *ComInt_Dnsc_FUN ;
    IIF_COMP_DNSC_ComIntCFG   *ComInt_Dnsc_CFG;
    IIF_COMP_DNSC_ComIntSSA   *ComInt_Dnsc_SSA;
}DNSC_INT_OBJ_S;

ULONG ImplIDnscFactoryQueryInterface(IUnknown * This, COMP_IID iid, LPVOID * ppvObj);
ULONG ImplIDnscFactoryCreateInstance(IComponentFactory *This,  COMP_IID iid, VOID **ppvObj );

/* dns component Instance */
extern DNSC_INT_OBJ_S   g_stIP_DNSC_INT_OBJ;
/* Component interface of function */
extern IIF_COMP_DNSC_ComIntFUN g_IComInt_Dnsc_FUN ;
/* Component interface of configration */
extern IIF_COMP_DNSC_ComIntCFG g_IComInt_Dnsc_CFG;
/* Component interface of SSA */
extern IIF_COMP_DNSC_ComIntSSA g_IComInt_Dnsc_SSA;
#endif  /*  _I_PP4_H_  */


#ifdef  __cplusplus
}
#endif

