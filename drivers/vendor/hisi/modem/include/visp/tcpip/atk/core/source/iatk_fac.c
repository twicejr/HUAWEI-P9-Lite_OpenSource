

#ifdef  __cplusplus
extern  "C"{
#endif

#include "tcpip/atk/include/atk_ext.h"

/******************************************************************************
*
* component factory definition                                               
*
******************************************************************************/
/*Vitual Fucntion table of IComponentFactory*/
struct IComponentFactoryVtbl m_AtkFactoryVtbl =
{
    ImplAtkFactoryQueryInterface,
    ImplAtkFactoryCreateInstance,
};

/*Component Factory for component */
IComponentFactory m_AtkFactory =
{
    /*Assign the Vtbl*/
    &m_AtkFactoryVtbl
};


ULONG ImplAtkFactoryQueryInterface(IUnknown * This, COMP_IID iid, LPVOID * ppvObj)
{
    ULONG ulRetVal = VOS_OK;

    if (NULL == ppvObj) 
    {
        VOS_DBGASSERT (0); 
        return VOS_ERR;   
    }
    
    if ((IID_IUNKNOWN == iid) || (IID_ICOMPONENTFCTORY == iid))
    {
        /* Because that IComponentFactory inherit from IUnknown, the two */
        /* interface can be used interchangeably*/
        *ppvObj = (void *)This;        
    }
    else 
    {
        ulRetVal = ERR_COMP_NOINTERFACE;
    }
    
    /* SYSTRACE (MID_IP_PP4, IP_PP4_FAC, 0, 0, 0, 0); */

    return (ulRetVal);
}


ULONG ImplAtkFactoryCreateInstance (IComponentFactory *This,  COMP_IID iid, VOID **ppvObj )
{  
    ULONG ulRet = VOS_OK;
    if (NULL == ppvObj) 
    {
        VOS_DBGASSERT (0); 
        return VOS_ERR;   
    }
    switch(iid)
    { 
        case IID_IUNKNOWN:
        case IID_COMP_ATK_INTF_FUN:
        {
            *ppvObj = &g_IComInt_Atk_FUN;
            break;
        } 

        case IID_COMP_ATK_INTF_CFG:
        { 
            *ppvObj = &g_IComInt_Atk_CFG;
            break;
        }
        default:
        {
            *ppvObj = NULL;
            ulRet = VOS_ERR;
            break;
        }
    }

    if (This)
    {
        /* do nothing, to remove warning */
    }
       
    return ulRet;   
}
 
#ifdef  __cplusplus
}
#endif

