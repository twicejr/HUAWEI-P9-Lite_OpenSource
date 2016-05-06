/******************************************************************************

                  版权所有 (C), 2014, 华为技术有限公司

 ******************************************************************************
  文 件 名   : BST_PAL_Sync.c
  版 本 号   : 初稿
  作    者   : d00173029
  生成日期   : 2014年06月28日
  最近修改   :
  功能描述   : 实现WIN32操作系统线程通信邮箱、信号量
  函数列表   :
  修改历史   :
  1.日    期   : 2014年06月28日
    作    者   : d00173029
    修改内容   : 建立文件

******************************************************************************/

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

/*****************************************************************************
 函 数 名  : BST_OS_PalRecvSem
 功能描述  : 获取信号量平台适配实现
 输入参数  : BST_OS_PAL_SEM_T stSemHandle,  信号量句柄
             BST_UINT32 ulTimeOut           等待超时时长
 输出参数  : 无
 返 回 值  : BST_ERR_ENUM_UINT8             BST_ERR_ILLEGAL_PARAM   句柄出错
                                            BST_ERR_SYNC_TIMEOUT    等待超时
                                            BST_NO_ERROR_MSG        成功获取
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
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
/*****************************************************************************
 函 数 名  : BST_OS_PalSendSem
 功能描述  : 发送信号量平台适配实现
 输入参数  : BST_OS_PAL_SEM_T stSemHandle,  信号量句柄
             BST_VOID *pvArg                发送参数(Balong平台不需要)
 输出参数  : 无
 返 回 值  : BST_ERR_ENUM_UINT8             BST_ERR_ILLEGAL_PARAM   句柄出错
                                            BST_NO_ERROR_MSG        成功发送
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
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
/*****************************************************************************
 函 数 名  : BST_OS_PalDeleteSem
 功能描述  : 删除一个信号量平台适配实现
 输入参数  : BST_OS_PAL_SEM_T stSemHandle   信号量句柄
 输出参数  : 无
 返 回 值  : BST_ERR_ENUM_UINT8             BST_ERR_ILLEGAL_PARAM   句柄出错
                                            BST_NO_ERROR_MSG        成功删除
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
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
/*****************************************************************************
 函 数 名  : BST_OS_PalCreateSem
 功能描述  :创建一个信号量
 输入参数  : BST_OS_PAL_SEM_T stSemHandle   信号量句柄
 输出参数  : 无
 返 回 值  : BST_ERR_ENUM_UINT8             BST_ERR_ILLEGAL_PARAM   句柄出错
                                            BST_NO_ERROR_MSG        成功创建
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
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


