

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "BST_PAL_Sync.h"
/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_BST_PAL_SYNC_C
/*lint +e767*/

/******************************************************************************
   2 函数实现
******************************************************************************/


BST_ERR_ENUM_UINT8 BST_OS_PalRecvSem(
    BST_OS_PAL_SEM_T    stSemHandle,
    BST_UINT32          ulTimeOut )
{

    if( BST_PAL_IsSemInValid( stSemHandle ) )
    {
        return BST_ERR_ILLEGAL_PARAM;
    }
    
#if (VOS_RTOSCK == VOS_OS_VER)
    if( VOS_OK == VOS_SmP(stSemHandle, ulTimeOut))
#else
    if( OK == semTake(stSemHandle, (BST_INT32)ulTimeOut))
#endif
    {
        return BST_NO_ERROR_MSG;
    }
    else
    {
        return BST_ERR_SYNC_TIMEOUT;
    }
}

BST_ERR_ENUM_UINT8  BST_OS_PalSendSem(
    BST_OS_PAL_SEM_T    stSemHandle,
    BST_VOID           *pvArg )
{
    if( BST_PAL_IsSemInValid( stSemHandle ) )
    {
        return BST_ERR_ILLEGAL_PARAM;
    }
    
#if (VOS_RTOSCK == VOS_OS_VER)
    if( VOS_OK == VOS_SmV(stSemHandle) )
#else
    if( OK == semGive(stSemHandle) )
#endif
    {
        return BST_NO_ERROR_MSG;
    }
    else
    {
        return BST_ERR_ILLEGAL_PARAM;
    }
}

BST_ERR_ENUM_UINT8  BST_OS_PalDeleteSem( BST_OS_PAL_SEM_T stSemHandle )
{
    if( BST_PAL_IsSemInValid( stSemHandle ) )
    {
        return BST_ERR_ILLEGAL_PARAM;
    }
    
#if (VOS_RTOSCK == VOS_OS_VER)
    VOS_SmDelete( stSemHandle );
#else
    semDelete( stSemHandle );
#endif

    return BST_NO_ERROR_MSG;
}

BST_OS_PAL_SEM_T  BST_OS_PalCreateSem( BST_UINT32 ulSmInit )
{
    #if (VOS_RTOSCK == VOS_OS_VER) 
    BST_OS_PAL_SEM_T stSemHandle;
    if(VOS_OK != VOS_SmCCreate("BST",ulSmInit,VOS_SEMA4_PRIOR,&stSemHandle))
    {
        return BST_NULL_PTR;
    }
    else
    {
        return stSemHandle;
    }
    #else
    return semCCreate(SEM_Q_PRIORITY, (BST_INT32)ulSmInit);
    #endif
}


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


