/******************************************************************************

                  版权所有 (C), 2001-2012, 华为技术有限公司

 ******************************************************************************
  文 件 名      : comm_adapter.c
  版 本 号      : 初稿
  作    者      : g47350
  生成日期      : 2012年12月05日
  最近修改      :
  功能描述      : 该C文件给出了OSA适配模块的实现
  函数列表      :
  修改历史      :
  1.日    期    : 2012年12月05日
    作    者    : g47350
    修改内容    : 创建文件

******************************************************************************/
#ifdef __cplusplus
  #if __cplusplus
  extern "C"{
  #endif
#endif

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "comm_adapter.h"

/*****************************************************************************
  2 全局变量声明
*****************************************************************************/

/*****************************************************************************
  3 函数申明
*****************************************************************************/

#if (VOS_VXWORKS == VOS_OS_VER)

/*****************************************************************************
 函 数 名  : _VOS_SmCCreate
 功能描述  : 创建信号量操作
 输入参数  : acSmName: 信号量名字
             ulSmInit: 信号量初始化值
             ulFlags: 信号量类型
             pulSmID: 保存信号量ID的地址

 输出参数  : pulSmID: 保存信号量ID的地址

 返 回 值  : VOS_OK:成功、VOS_ERR:失败

 修改历史      :
 1.日    期    : 2012年12月05日
   作    者    : g47350
   修改内容    : NV升级项目开发
*****************************************************************************/
VOS_UINT32 _VOS_SmCCreate(VOS_CHAR   acSmName[4],
                          VOS_UINT32 ulSmInit,
                          VOS_UINT32 ulFlags,
                          VOS_SEM   *pulSmID)
{
    SEM_ID                              SemId;
    VOS_INT                             iOptions = 0;

    if ((ulFlags & VOS_SEMA4_PRIOR))
    {
        iOptions |= SEM_Q_PRIORITY;
    }
    else
    {
        iOptions |= SEM_Q_FIFO;
    }

    if ((ulFlags & VOS_SEMA4_INVERSION_SAFE) && (0xFFFFFFFF == ulSmInit))
    {
        iOptions |= SEM_INVERSION_SAFE;
    }

    if (0xFFFFFFFF == ulSmInit)
    {
        SemId = semMCreate(iOptions);
    }
    else
    {
        SemId = semCCreate(iOptions , (VOS_INT)ulSmInit);
    }

    if (NULL == SemId)
    {
        return VOS_ERR;
    }

    *pulSmID = (VOS_SEM)SemId;

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : _VOS_SmP
 功能描述  : 等待信号量
 输入参数  : ulSemId: 信号量ID
             ulTimeOutInMillSec: 超时时间(ms)

 输出参数  : 无

 返 回 值  : VOS_OK:成功、VOS_ERR:失败

 修改历史      :
 1.日    期    : 2012年12月05日
   作    者    : g47350
   修改内容    : NV升级项目开发
*****************************************************************************/
VOS_UINT32 _VOS_SmP(VOS_SEM ulSemId, VOS_UINT32 ulTimeOutInMillSec)
{
    VOS_INT                             iTimeOut;

    iTimeOut = (0 == ulTimeOutInMillSec) ?
        -1 : (VOS_INT)ulTimeOutInMillSec/10;

    if (VOS_OK == semTake((SEM_ID)ulSemId, iTimeOut))
    {
        return VOS_OK;
    }

    return VOS_ERR;
}

#elif (VOS_RTOSCK == VOS_OS_VER)

/*****************************************************************************
 函 数 名  : _VOS_SmCCreate
 功能描述  : 创建信号量操作
 输入参数  : acSmName: 信号量名字
             ulSmInit: 信号量初始化值
             ulFlags: 信号量类型
             pulSmID: 保存信号量ID的地址

 输出参数  : pulSmID: 保存信号量ID的地址

 返 回 值  : VOS_OK:成功、VOS_ERR:失败

 修改历史      :
 1.日    期    : 2012年12月05日
   作    者    : g47350
   修改内容    : NV升级项目开发
*****************************************************************************/
VOS_UINT32 _VOS_SmCCreate(VOS_CHAR   acSmName[4],
                          VOS_UINT32 ulSmInit,
                          VOS_UINT32 ulFlags,
                          VOS_SEM   *pulSmID)
{
    SEM_HANDLE_T                        SemId;
    OS_SEM_MODE_E                       iOptions;
    VOS_UINT32                          ulResult;

    if( (ulFlags & VOS_SEMA4_PRIOR) )
    {
        iOptions = SEM_MODE_PRIOR;
    }
    else
    {
        iOptions = SEM_MODE_FIFO;
    }

    if(ulSmInit == 0xFFFFFFFF)
    {
        /* RTOSck中只有二进制信号量支持优先级翻转 */
        if ((VOS_SEMA4_PRIOR | VOS_SEMA4_INVERSION_SAFE)
            == (ulFlags & (VOS_SEMA4_PRIOR | VOS_SEMA4_INVERSION_SAFE)))
        {
            ulResult = SRE_SemBCreate(OS_SEM_FULL, &SemId, iOptions);
        }
        else
        {
            ulResult = SRE_SemCCreate(OS_SEM_FULL, &SemId, iOptions);
            SRE_SemCMaxCountSet(SemId, OS_SEM_FULL);
        }
    }
    else
    {
        ulResult = SRE_SemCCreate(ulSmInit, &SemId, iOptions);
    }

    if (SRE_OK != ulResult)
    {
        return VOS_ERR;
    }

    *pulSmID = (VOS_SEM)SemId;

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : _VOS_SmP
 功能描述  : 等待信号量
 输入参数  : ulSemId: 信号量ID
             ulTimeOutInMillSec: 超时时间(ms)

 输出参数  : 无

 返 回 值  : VOS_OK:成功、VOS_ERR:失败

 修改历史      :
 1.日    期    : 2012年12月05日
   作    者    : g47350
   修改内容    : NV升级项目开发
*****************************************************************************/
VOS_UINT32 _VOS_SmP(VOS_SEM ulSemId, VOS_UINT32 ulTimeOutInMillSec)
{
    VOS_INT                             iTimeOut;

    iTimeOut = (0 == ulTimeOutInMillSec) ?
        -1 : (VOS_INT)ulTimeOutInMillSec/10;

    if (SRE_OK == SRE_SemPend((SEM_HANDLE_T)ulSemId, (VOS_UINT32)iTimeOut))
    {
        return VOS_OK;
    }

    return VOS_ERR;
}

#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

