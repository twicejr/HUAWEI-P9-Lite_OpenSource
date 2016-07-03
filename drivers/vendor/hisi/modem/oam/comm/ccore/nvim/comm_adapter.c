
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

