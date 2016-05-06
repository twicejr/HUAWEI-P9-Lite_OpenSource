

#ifdef  __cplusplus
extern  "C"{
#endif

#ifndef _I_ATK_FAC_H_
#define _I_ATK_FAC_H_


/* For implement of QuerfyInstance() */
typedef struct tag_ATK_INT_OBJ_S
{
    IIF_COMP_ATK_ComIntFUN   *ComInt_Atk_FUN ;
    IIF_COMP_ATK_ComIntCFG   *ComInt_Atk_CFG;
}ATK_INT_OBJ_S;

ULONG ImplAtkFactoryQueryInterface(IUnknown * This, COMP_IID iid, LPVOID * ppvObj);
ULONG ImplAtkFactoryCreateInstance(IComponentFactory *This,  COMP_IID iid, VOID **ppvObj );

/* atk component Instance */
extern ATK_INT_OBJ_S   g_stIP_ATK_INT_OBJ;
/* Component interface of function */
extern IIF_COMP_ATK_ComIntFUN g_IComInt_Atk_FUN ;
/* Component interface of configration */
extern IIF_COMP_ATK_ComIntCFG g_IComInt_Atk_CFG;

#endif  /* _I_ATK_FAC_H_ */

#ifdef  __cplusplus
}
#endif

