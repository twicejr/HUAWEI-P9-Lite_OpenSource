/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              waitlist.h
*
*  Project Code: VISPV1R5
*   Module Name: WaitList  
*  Date Created: 2000/06/24 
*        Author: 19742
*   Description: WaitList模块提供的接口函数
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2000/06/24  19742         Creat the first version.
*
*******************************************************************************/

#ifndef _COM_WAITLIST_H_
#define _COM_WAITLIST_H_

#ifdef    __cplusplus
extern "C"{
#endif

#define        COM_FILTER_WAITLIST_SUCCESS             0
#define        ERR_COM_FILTER_WAITLIST_INVALID_MAINTYPE    1
#define        ERR_COM_FILTER_WAITLIST_INVALID_SUBTYPE     2
#define        ERR_COM_FILTER_WAITLIST_NOMEM               3
#define        ERR_COM_FILTER_WAITLIST_INVALID_HANDLE      4
#define        ERR_COM_FILTER_WAITLIST_NOENTRY      5

#define COM_WAITLIST_BFD_OSPF_RELATION 1
#define COM_WAITLIST_BFD_OSPF_RULE 2
#define COM_WAITLIST_BFD_STATIC_RELATION 3
#define COM_WAITLIST_BFD_SESSION 4
#define COM_WAITLIST_VLAN_ENTRY 5
#define COM_WAITLIST_ETHARP_ENTRY 6
#define COM_WAITLIST_ACL_ENTRY 7
#define COM_WAITLIST_IPOA_ENTRY 8

#define COM_WAITLIST_ACL6_ENTRY 9

/* Add for DTS2011022102588, by tanyiming00171953, at 2011-02-22. 修改原因: 新增Vlink路由查询接口,增强Vlink维测手段  */
#define COM_WAITLIST_VLINK_RTNODE 10
#define COM_WAITLIST_VRF_ENTRY 11

#define COM_WAITLIST_NB_ENTRY 12

#define COM_WAITLIST_VRF6_ENTRY 13


typedef VOID * (*COM_WAITLIST_GETNEXTFUNC)(VOID *pFilter,VOID *pCurEntry);

/****************************************************************************
* subtype结构和main type结构共同组成一棵两层的树:                           
*                     HEAD                                                  
*                        \                                                  
*            Main type    Ｏ—Ｏ—Ｏ                                        
*                        /     \                                            
*            handle       Ｏ-Ｏ　Ｏ-Ｏ-Ｏ                                   
****************************************************************************/

/****************************************************************************
*                        Handle结构                                         
****************************************************************************/
typedef struct COM_FILTER_WAITLIST_HANDLE
{
    VOID        *pData;                          /* 保护的数据指针            */
    VOID        *pFilterPoint;                /* 传给pGetNextFunc的参数    */
    ULONG      ulPrivData;                  /*用户自定义的私有参数*/
    COM_WAITLIST_GETNEXTFUNC pfGetNextFunc;
    struct COM_FILTER_WAITLIST_HANDLE    *pstRBrother;  /* 右兄弟指针                */
    struct COM_FILTER_WAITLIST_MAIN_TYPE    *pstParent; /* 父节点指针                */
}COM_FILTER_WAITLIST_HANDLE_S;

/****************************************************************************
*                        main type结构                                        
****************************************************************************/
typedef struct COM_FILTER_WAITLIST_MAIN_TYPE
{
    ULONG                 ulMainID;                  /* main type 节点ID    */
    struct COM_FILTER_WAITLIST_MAIN_TYPE    *pstRBrother;   /* 右兄弟指针          */
    struct COM_FILTER_WAITLIST_HANDLE    *pstFirstSon;      /* 第一个儿子的指针    */
}COM_FILTER_WAITLIST_MAIN_TYPE_S;

typedef struct COM_WAITLIST_REG
{
    ULONG ulMainType;
    VOID *pFilter;                   /*过滤器指针，不使用过滤器时设置为NULL*/
    ULONG ulSizeOfFilter;           /*过滤器结构大小，分配内存时使用*/
    ULONG ulPrivData;                /*用户自定义的私有参数*/
    COM_WAITLIST_GETNEXTFUNC pfGetNextFunc; /*支持过滤器的获取函数，由用户实现*/
}COM_WAITLIST_REG_S;

ULONG COM_FilterWaitListRegister(UINTPTR *pulHandle,COM_WAITLIST_REG_S stWaitListReg,VOID *pFstEntry);

ULONG COM_FilterWaitListSet(UINTPTR ulHandle, VOID *pListData);

ULONG COM_FilterWaitListGet(UINTPTR ulHandle,VOID **ppListData );

ULONG COM_FilterWaitListGetParam(UINTPTR ulHandle, VOID **ppRetParam, ULONG *pulPrivData);

ULONG COM_FilterWaitListUnregister( UINTPTR ulHandle );

ULONG COM_FilterWaitListDelFromList(ULONG ulMainType, VOID *pDataToDel);
ULONG COM_FilterWaitListSetParam(UINTPTR ulHandle, ULONG ulPrivData);
    
#ifdef    __cplusplus
}
#endif    /* end of __cplusplus */

#endif    /* end of _COM_WAITLIST_H_ */


