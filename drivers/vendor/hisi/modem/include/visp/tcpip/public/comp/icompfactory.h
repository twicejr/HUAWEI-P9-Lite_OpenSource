/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              icompfactory.h
*
*  Project Code: VISPV100R005
*   Module Name: PUBLIC 
*  Date Created: 2003-3-11
*        Author: Tian Bo(09354)
*   Description: 组件工厂头文件
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2003-3-11  Tian Bo(09354)    Creat the first version.
*  2006-4-27  wang xin(03278)   根据编程规范，对文件进行规范化整理
*******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif /* __cpluscplus */


#ifndef _INCLUDE_COMPONENTFACTORY_H
#define _INCLUDE_COMPONENTFACTORY_H

#ifdef  TCPIP_USE_CPLUSPLUS

/**************************
 * This interface intended to deal with componet generation, and so 
 * it is to be implemented on each component (identified by a COMP_ID). 
 * The method CreateInstance creates an uninitialized component 
 * instance of a specified CLSID
***************************/
DECLARE_INTERFACE_(IComponentFactory, IUnknown)
{
public:
    /*****************************
     * Create a uninitialized component instance.
     *@param iid, ID of the interface to be used to communicate with the 
     * new created instance.
     *@param ppvObj, Address of pointer variable that receives the 
     * interface pointer requested in iid. 
     * Upon successful return, *ppvObj contains the requested interface pointer. 
     * otherwise (the component does not support the interface specified), 
     * the value of *ppvObj is VOS_NULL_PTR
     *@return VOS_OK on success, other indicates a failure.  
     ******************************/
    virtual ULONG COMP_CALL CreateInstance( COMP_IID iid, VOS_VOID ** ppvObj )=0;
};

#else

#undef THIS
#define THIS IComponentFactory * This


DECLARE_INTERFACE(IComponentFactory)
{
    IUNKNOWN_METHODS
    METHOD(CreateInstance)(IComponentFactory * This, COMP_IID iid, VOID ** ppvObj );
};

#define ICOMPONENTFACTORY_METHODS                          \
IUNKNOWN_METHODS                                            \
METHOD(CreateInstance)(IComponentFactory * This, COMP_IID iid, VOID ** ppvObj )

/*Expand this interface
struct IComponentFactory
{
    struct IComponentFactoryVtbl *lpVtbl ;
};

typedef struct IComponentFactory IComponentFactory ;
typedef IComponentFactory *  PIComponentFactory ;

struct IComponentFactoryVtbl
{
    VOS_UINT32 (*QueryInterface)(IComponentFactory *This , COMP_IID iid, void** ppvObj) ;
    VOS_UINT32 (*CreateInstance)(IComponentFactory* This, COMP_IID iid, VOS_VOID ** ppvObj);
};
*/

#endif  /* #ifdef __cplusplus */

#define IID_ICOMPONENTFCTORY 0x11DB04E4

#endif  /*_INCLUDE_COMPONENTFACTORY_H*/


#ifdef __cplusplus
}
#endif /* __cpluscplus */


