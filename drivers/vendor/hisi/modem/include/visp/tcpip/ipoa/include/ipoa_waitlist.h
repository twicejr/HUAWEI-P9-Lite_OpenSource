
/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ipoa_waitlist.h
*
*  Project Code: node
*   Module Name:   
*  Date Created: 2008-07-30
*        Author: wangbin (62223)
*   Description: 
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2008-07-30   wangbin (62223)         Create
*
*******************************************************************************/
#ifndef _IPOA_WAITLIST_H_
#define _IPOA_WAITLIST_H_

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */


#define CFGAPI_COMM_DISPLAY_SIZE 10

typedef struct tagCFGAPI_COMM_DISPLAY_NODE
{
    ULONG ulPrevIdx;
    ULONG ulNextIdx;
    BOOL_T bInUsed;
    UCHAR aucReserved[2];/*four bit padding*/
    VOID *pNodeInfo;
}CFGAPI_COMM_DISPLAY_NODE_S;

/*it's our method to carry out display interface to product,and 
 this struture no use for product*/
typedef struct tagCFGAPI_COMM_DISPLAY_GROUP
{
    ULONG ulUsedHeadIdx;
    ULONG ulFreeHeadIdx;
    CFGAPI_COMM_DISPLAY_NODE_S astNodeArray[CFGAPI_COMM_DISPLAY_SIZE + 1];
}CFGAPI_COMM_DISPLAY_GROUP_S;

#define CFGAPI_COMM_MEM_MALLOC(ulInfo, ulSize) VOS_SimpleAlloc (ulInfo, ulSize)
#define CFGAPI_COMM_MEM_FREE(pBuf) VOS_Free(pBuf)




#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* _IPOA_WAITLIST_H_ */

