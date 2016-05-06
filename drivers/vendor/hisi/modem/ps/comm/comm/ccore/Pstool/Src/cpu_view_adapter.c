/******************************************************************************

                  版权所有 (C), 2001-2014, 华为技术有限公司

 ******************************************************************************
  文 件 名   : cpu_view_adapter.c
  版 本 号   : 初稿
  作    者   : g00178567
  生成日期   : 2013年10月30日
  最近修改   :
  功能描述   : 操作系统适配
  函数列表   :
                OS_GetTaskIdList
                OS_GetTaskName
  修改历史   :
  1.日    期   : 2013年10月30日
    作    者   : g00178567
    修改内容   : 创建文件

******************************************************************************/
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
/******************************************************************************
 Prototype      : OS_GetTaskIdList
 Description    : 获取任务ID和实际任务个数
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        : ---
  1.Date        : 2013-11-06
    Author      : g00178567
    Modification: Created function
******************************************************************************/
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

/******************************************************************************
 Prototype      : OS_GetTaskName
 Description    : 获取任务名称
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        : ---
  1.Date        : 2013-11-06
    Author      : g00178567
    Modification: Created function
******************************************************************************/
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

