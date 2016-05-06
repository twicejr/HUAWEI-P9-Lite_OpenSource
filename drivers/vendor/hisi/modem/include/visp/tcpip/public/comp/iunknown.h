/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              iunknown.h
*
*  Project Code: VISPV100R005
*   Module Name: PUBLIC  
*  Date Created: 2003-3-11
*        Author: Tian Bo(09354)
*   Description: 组件接口公共头文件
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2003-3-11 Tian Bo(09354)     Creat the first version.
*  2006-4-27 wang xin(03278)    根据编程规范，对文件进行规范化整理
*******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif /* __cpluscplus */



#ifndef _INCLUDE_IUNKNOWN_H
#define _INCLUDE_IUNKNOWN_H


#ifdef  TCPIP_USE_CPLUSPLUS
/********************************
 * The IUnknown interface lets clients get pointers to other interfaces on a 
 * given object through the QueryInterface method.
 * All other interfaces are inherited, directly or indirectly, from IUnknown. 
 * Therefore, the method QueryInterface in IUnknown is the first entries in the VTable 
 * for every interface. 
 * You must implement IUnknown as part of every interface. 
********************************/
DECLARE_INTERFACE(IUnknown)
{
public:
    /*************************
     * Returns a pointer to a specified interface on an object to which a client 
     * currently holds an interface pointer. 
     * This function must call AddRef on the pointer it returns. 
     *@param iid, a indentifier of the requested interface
     *@param ppvObj, Address of pointer variable that receives the interface 
     * pointer requested in riid. Upon successful return, *ppvObject contains 
     * the requested interface pointer to the object. 
     * If the object does not support the interface specified 
     * in iid, *ppvObject is set to NULL. 
     *@return VOS_OK if the interface is supported, VOS_ERR if not.
    *************************/
    virtual ULONG COMP_CALL QueryInterface(COMP_IID iid, LPVOID * ppvObj)=0;

};

#else

#undef THIS
#define THIS IUnknown * This


DECLARE_INTERFACE(IUnknown)
{
    METHOD(QueryInterface)(IUnknown * This, COMP_IID iid, LPVOID * ppvObj);
};

#define IUNKNOWN_METHODS    \
    METHOD(QueryInterface)(IUnknown * This, COMP_IID iid, LPVOID * ppvObj);

/*Expand this interface
struct IUnknown 
{
    struct IUnknownVtbl *lpVtbl ;
};

typedef struct IUnknown IUnknown ;
typedef IUnknown *PIUnknown ;
struct IUnknownVtbl 
{
    VOS_UINT32 ( *QueryInterface)(IUnknown *This , COMP_IID iid, void** ppvObj) ;
};
*/

#endif

#define IID_IUNKNOWN 0X748429F6


#endif  /*_INCLUDE_IUNKNOWN_H*/



#ifdef __cplusplus
}
#endif /* __cpluscplus */

