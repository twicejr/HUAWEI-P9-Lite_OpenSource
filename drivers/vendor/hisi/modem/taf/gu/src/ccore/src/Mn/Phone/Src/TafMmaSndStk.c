/******************************************************************************

                  版权所有 (C), 2001-2012, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafMmaSndStk.c
  版 本 号   : 初稿
  作    者   : l00301449
  生成日期   : 2015年7月3日
  最近修改   :
  功能描述   : mma给stk发送消息的处理
  函数列表   :
  修改历史   :
  1.日    期   : 2015年7月3日
    作    者   : l00301449
    修改内容   : 创建文件

****************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "PsCommonDef.h"
#include "TafLog.h"
#include "TafMmaSndStk.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif

#define THIS_FILE_ID  PS_FILE_ID_TAF_MMA_SND_STK_C

/*****************************************************************************
   2 全局变量定义和宏
****************************************************************************/

/*lint -save -e958 */

/*****************************************************************************
   3 函数实现
*****************************************************************************/
/*****************************************************************************
 函 数 名  : TAF_MMA_SndStk1xServiceInfoInd
 功能描述  : ID_MMA_STK_1X_SERVICE_INFO_IND消息发送函数
 输入参数  : MMA_STK_1X_SYS_INFO_STRU           *pstSysInfo
             NAS_STK_SERVICE_STATUS_INFO_STRU   *pstServiceStatus
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月3日
    作    者   : l00301449
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_SndStk1xServiceInfoInd(
    MMA_STK_1X_SYS_INFO_STRU           *pstSysInfo,
    NAS_STK_SERVICE_STATUS_INFO_STRU   *pstServiceStatus
)
{
    MMA_STK_SERVICE_INFO_IND_STRU      *pstMsg = VOS_NULL_PTR;

    pstMsg = (MMA_STK_SERVICE_INFO_IND_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMA,
                                             sizeof(MMA_STK_SERVICE_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH);
    if (VOS_NULL_PTR == pstMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndStk1xServiceInfoInd:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
               sizeof(MMA_STK_SERVICE_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid    = NAS_GetOamReceivePid(MAPS_STK_PID);
    pstMsg->ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid      = WUEPS_PID_MMA;
    pstMsg->ulLength         = sizeof(MMA_STK_SERVICE_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->ulMsgName        = ID_MMA_STK_1X_SERVICE_INFO_IND;

    PS_MEM_CPY(&(pstMsg->stSysInfo), pstSysInfo, sizeof(MMA_STK_1X_SYS_INFO_STRU));

    PS_MEM_CPY(&(pstMsg->stServiceStatus), pstServiceStatus, sizeof(NAS_STK_SERVICE_STATUS_INFO_STRU));

    /* 调用VOS发送原语 */
    PS_SEND_MSG(WUEPS_PID_MMA, pstMsg);
    return;
}
/*lint -restore */


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

