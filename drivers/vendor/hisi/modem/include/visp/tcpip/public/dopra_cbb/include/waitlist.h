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

#ifndef _WAITLIST_H_
#define _WAITLIST_H_

#ifdef    __cplusplus
extern "C"{
#endif

#define        VOS_WAITLIST_SUCCESS             0
#define        ERR_WAITLIST_INVALID_MAINTYPE    1
#define        ERR_WAITLIST_INVALID_SUBTYPE     2
#define        ERR_WAITLIST_NOMEM               3
#define        ERR_WAITLIST_INVALID_HANDLE      4

/* 得到下一个数据指针的函数 */
typedef VOID * (*WAITLIST_GETNEXTFUNC)(VOID *pParam,VOID **pNewParam);

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
typedef struct VOS_WAITLIST_HANDLE
{
    VOID        *pData;                          /* 保护的数据指针            */
    WAITLIST_GETNEXTFUNC    pfGetNextFunc;       /* 得到下一个数据指针的函数  */
    VOID        *pParamOfGetNext;                /* 传给pGetNextFunc的参数    */
    struct VOS_WAITLIST_HANDLE    *pstRBrother;  /* 右兄弟指针                */
    struct VOS_WAITLIST_MAIN_TYPE    *pstParent; /* 父节点指针                */
}VOS_WAITLIST_HANDLE_S;

/****************************************************************************
*                        main type结构                                        
****************************************************************************/
typedef struct VOS_WAITLIST_MAIN_TYPE
{
    ULONG                 ulMainID;                  /* main type 节点ID    */
    struct VOS_WAITLIST_MAIN_TYPE    *pstRBrother;   /* 右兄弟指针          */
    struct VOS_WAITLIST_HANDLE    *pstFirstSon;      /* 第一个儿子的指针    */
}VOS_WAITLIST_MAIN_TYPE_S;

ULONG VOS_WaitListRegister(ULONG ulMainType, UINTPTR *pulHandle, WAITLIST_GETNEXTFUNC pfGetNextFunc );

ULONG VOS_WaitListSet(UINTPTR ulHandle, VOID *pListData, VOID *pParamOfGetNext );

ULONG VOS_WaitListGet(UINTPTR ulHandle,VOID **ppListData );

ULONG VOS_WaitListGetParam(UINTPTR ulHandle, VOID **ppRetParam);

ULONG VOS_WaitListDelFromList(ULONG ulMainType, VOID *pDataToDel );

ULONG VOS_WaitListUnregister( UINTPTR ulHandle );


#ifdef    __cplusplus
}
#endif    /* end of __cplusplus */

#endif    /* end of _WAITLIST_H_ */


