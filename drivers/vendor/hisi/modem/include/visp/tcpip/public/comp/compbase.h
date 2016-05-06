/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              compbase.h
*
*  Project Code: VISPV100R005
*   Module Name: PUBLIC  
*  Date Created: 2003-3-11
*        Author: Tian Bo(09354)
*   Description: 组件公共基础头文件
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


#ifndef _INCLUDE_COMPBASE_H
#define _INCLUDE_COMPBASE_H

typedef ULONG COMP_CID;   /* Comp ID */
typedef ULONG COMP_IID;   /* interface ID */
typedef ULONG COMP_ID;    /* component ID */

typedef void * LPVOID;

#ifdef  TCPIP_USE_CPLUSPLUS
#define COMP_CALL  /* __stdcall */
#define interface               class
#define DECLARE_INTERFACE(iface)    interface iface
#define DECLARE_INTERFACE_(iface, baseiface)    interface iface : public baseiface

#else
#define COMP_CALL /* __cdecl */

#define interface               struct

#define DECLARE_INTERFACE(iface) \
struct iface##Vtbl;  \
interface iface { \
    struct iface##Vtbl * lpVtbl; \
}; \
typedef interface iface iface; \
typedef iface * P##iface;\
struct iface##Vtbl

#endif

#ifdef TCPIP_USE_CPLUSPLUS
#define METHOD(method)      public: ULONG  (COMP_CALL * method)
#else
#define METHOD(method)       ULONG  (COMP_CALL * method)
#endif

#define METHOD_(type,method) type (COMP_CALL * method)

/*************************
 * ComponetInfo Definition
************************/
typedef struct tagTypeVersion
{
    UCHAR n1;
    UCHAR n2;
    UCHAR n3;
    UCHAR n4;
}TypeVersion;

typedef TypeVersion ComponentVersion;

interface IComponentFactory;

/*The name size decideing by component specification document */
#define COMP_NAME_SIZE    32 
#define COMP_DES_SIZE     64
#define COMP_MAX_NUM      128

typedef struct ComponentInfo
{
    COMP_ID cid;
    CHAR szName[COMP_NAME_SIZE];
    CHAR szDescription[COMP_DES_SIZE];
    ComponentVersion Version;
    interface IComponentFactory * pFactory;
}ComponentInfo;

/* This macro is for Single-Instance-Single-Interface Component only */
#define DECLARE_SISI_COMPONENT(Comp,iFace_IID ,iFace) \
ULONG Impl##Comp##FactoryQueryInterface(IComponentFactory * This, COMP_IID iid, LPVOID * ppvObj);\
ULONG Impl##Comp##FactoryCreateInstance(IComponentFactory * This, COMP_IID iid, VOID ** ppvObj );\
\
struct IComponentFactoryVtbl m_##Comp##FactoryVtbl =\
{\
Impl##Comp##FactoryQueryInterface,\
Impl##Comp##FactoryCreateInstance\
};\
IComponentFactory m_##Comp##Factory = { &m_##Comp##FactoryVtbl};\
\
struct iFace##Vtbl m_##iFace##Vtbl;\
iFace * m_p##iFace;\
\
ULONG Impl##Comp##FactoryQueryInterface(IComponentFactory * This, COMP_IID iid, LPVOID * ppvObj){\
if( iid == IID_IUNKNOWN || iid == IID_ICOMPONENTFCTORY ) {\
    *ppvObj = (VOID *)This;\
    return VOS_OK;    }\
else \
    return ERR_COMP_NOINTERFACE; \
}\
ULONG Impl##Comp##FactoryCreateInstance(IComponentFactory * This, COMP_IID iid, VOID ** ppvObj ){\
ULONG ulRet;\
if( iid != IID_IUNKNOWN && iid != iFace_IID ) {   \
    *ppvObj = VOS_NULL_PTR;\
    ulRet =  ERR_COMP_NOINTERFACE;    }\
else    {\
    *ppvObj = m_p##iFace;\
    ulRet = VOS_OK;    }\
return ulRet;\
}


/*define for com info transfered between shell and core*/
typedef struct tagCOM_ID_INFO
{
    CHAR        *pchComName;
    COMP_ID     idCID; /* terry changed to ID from CID */
    CHAR        *pchIFName;
    COMP_IID    idIID;
}COM_ID_INFO_S;


#include "iunknown.h"
#include "icompfactory.h"


extern ULONG COMP_RegisterComponentInfo(const ComponentInfo * pInfo);
extern ULONG COMP_CreateInstance(COMP_ID cid, COMP_IID iid, LPVOID * ppv);

#ifdef  TCPIP_USE_CPLUSPLUS
interface IComponetFactory;
extern ULONG COMP_GetComponentFactory(COMP_ID cid, interface IComponentFactory ** ppFactoty);
#else
extern ULONG COMP_GetComponentFactory(COMP_ID cid, interface IComponentFactory ** ppFactory);
#endif


extern ULONG COMP_GetComponentInfo(COMP_ID cid, ComponentInfo ** ppCompInfo);
extern ULONG COMP_GetComponentInfoByName( CHAR * strName,  ComponentInfo ** ppCompInfo);
extern ULONG COMP_GetInstance(COMP_ID cid, COMP_IID iid, LPVOID * ppv);
extern ULONG COMP_GetVTable(COMP_ID cid, COMP_IID iid, LPVOID * ppv);
extern ULONG MISC_VersionToStr(TypeVersion * v1, char * str);

#define ERR_COMP_NOINTERFACE 0x10102ddf


#endif  /*_INCLUDE_COMPBASE_H*/


#ifdef __cplusplus
}
#endif /* __cpluscplus */

