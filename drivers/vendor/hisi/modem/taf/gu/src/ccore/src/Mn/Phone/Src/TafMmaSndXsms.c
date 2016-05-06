/******************************************************************************

                  版权所有 (C), 2013-2014, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafMmaSndXsms.c
  版 本 号   : 初稿
  作    者   : c00299063
  生成日期   : 2015年4月25日
  最近修改   :
  功能描述   : MMA模块发送到XSMS的消息文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年4月25日
    作    者   : c00299063
    修改内容   : 创建文件

******************************************************************************/


/*****************************************************************************
   1 头文件包含
*****************************************************************************/
#include "TafMmaSndXsms.h"
#include "MmaXsmsInterface.h"

#include "PsTypeDef.h"
#include "TafLog.h"
#include "TafSdcCtx.h"



#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_TAF_MMA_SND_XSMS_C

/*****************************************************************************
   2 全局变量定义和宏
****************************************************************************/

/*lint -save -e958 */

/*****************************************************************************
   3 函数实现
*****************************************************************************/


VOS_VOID TAF_MMA_SndXsmsServiceStatusInd(
    TAF_SDC_SYS_MODE_ENUM_UINT8         enRatType,
    VOS_UINT8                           ucIsNewSession
)
{
    MMA_XSMS_SERVICE_STATUS_IND_STRU    *pstSndMsg = VOS_NULL_PTR;

    pstSndMsg = (MMA_XSMS_SERVICE_STATUS_IND_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                            WUEPS_PID_MMA,
                                            sizeof(MMA_XSMS_SERVICE_STATUS_IND_STRU));
    if ( VOS_NULL_PTR == pstSndMsg )
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA,"TAF_MMA_SndXsmsServiceStatusInd:Alloc Msg Failed");
        return;
    }

    pstSndMsg->ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstSndMsg->ulSenderPid       = WUEPS_PID_MMA;
    pstSndMsg->ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstSndMsg->ulReceiverPid     = UEPS_PID_XSMS;
    pstSndMsg->ulLength          = sizeof(MMA_XSMS_SERVICE_STATUS_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstSndMsg->usMsgName         = ID_MMA_XSMS_SERVICE_STATUS_IND;
    pstSndMsg->usOpId            = 0;
    pstSndMsg->enRatType         = enRatType;
    pstSndMsg->ucIsNewSession    = ucIsNewSession;

    PS_SEND_MSG(WUEPS_PID_MMA, pstSndMsg);

    return;
}

/*lint -restore */


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif







