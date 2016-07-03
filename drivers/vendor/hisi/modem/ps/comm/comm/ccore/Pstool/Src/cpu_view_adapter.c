
#ifdef __cplusplus
#if __cplusplus
    extern "C" {
#endif
#endif

/******************************************************************************
   1 头文件包含
******************************************************************************/
#include "vos.h"
#include "cpu_view_adapter.h"


/******************************************************************************
   1 宏定义
******************************************************************************/

/******************************************************************************
   6 函数实现
******************************************************************************/
/*lint -save -e958 */

VOS_UINT16 OS_GetTaskIdList(int iTaskIdList[], int iTaskMaxNum)
{
    VOS_UINT16              usTaskNum   = (VOS_UINT16)iTaskMaxNum;

    if (VOS_NULL_PTR == iTaskIdList)
    {
        return VOS_NULL;
    }

#if (VOS_VXWORKS == VOS_OS_VER)
    usTaskNum = (VOS_UINT16)taskIdListGet(iTaskIdList, usTaskNum);
#elif ((VOS_RTOSCK== VOS_OS_VER) || (VOS_NUCLEUS == VOS_OS_VER) || (VOS_WIN32 == VOS_OS_VER))
    if (SRE_OK != SRE_TaskIDList((UINT16 *)&usTaskNum, (UINT32 *)iTaskIdList))
    {
        return VOS_NULL;
    }
#else
    return VOS_NULL;
#endif

    return usTaskNum;
}


char * OS_GetTaskName(VOS_UINT32 ulTaskId)
{
    char                   *pucTaskName = VOS_NULL_PTR;

#if (VOS_VXWORKS == VOS_OS_VER)
    pucTaskName = taskName((int)ulTaskId);
#elif ((VOS_RTOSCK == VOS_OS_VER) || (VOS_NUCLEUS == VOS_OS_VER) || (VOS_WIN32 == VOS_OS_VER))
    if (SRE_OK != SRE_TaskNameGet((TSK_HANDLE_T)ulTaskId, &pucTaskName))
    {
        return VOS_NULL_PTR;
    }
#else
    return VOS_NULL_PTR;
#endif

    return pucTaskName;
}
/*lint -restore */

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

