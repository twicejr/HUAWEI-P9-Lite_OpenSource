/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : MnMsgSendSpm.c
  版 本 号   : 初稿
  作    者   : y00245242
  生成日期   : 2013年12月13日
  最近修改   :
  功能描述   : 实现MSG模块发送消息到SPM模块的函数接口
  函数列表   :
  修改历史   :
  1.日    期   : 2013年12月13日
    作    者   : y00245242
    修改内容   : 创建文件
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "MnMsgInclude.h"
#include "MnMsgSendSpm.h"


#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_MNMSG_SENDSPM_C

#if (FEATURE_ON == FEATURE_IMS)
/*****************************************************************************
  2 函数实现
*****************************************************************************/
/* Added by s00217060 for VoLTE_PhaseII  项目, 2013-09-24, begin */
/*****************************************************************************
 函 数 名  : TAF_MSG_SendSpmSmmaInd
 功能描述  : 短信储存空间从满到可用时发送SMMA IND到SPM进行域选择
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月24日
    作    者   : s00217060
    修改内容   : 新生成函数
  1.日    期   : 2014年1月11日
    作    者   : y00245242
    修改内容   : 增加IMS换域重拨功能
*****************************************************************************/
VOS_VOID TAF_MSG_SendSpmSmmaInd(VOS_VOID)
{
    TAF_SPM_SMMA_IND_STRU              *pstSmaMsg = VOS_NULL_PTR;

    pstSmaMsg = (TAF_SPM_SMMA_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,sizeof(TAF_SPM_SMMA_IND_STRU));

    if (VOS_NULL_PTR == pstSmaMsg)
    {
        MN_WARN_LOG("TAF_MSG_SendSpmSmmaInd:ERROR: VOS_AllocMsg fails");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstSmaMsg) + VOS_MSG_HEAD_LENGTH, 0, sizeof(TAF_SPM_SMMA_IND_STRU) - VOS_MSG_HEAD_LENGTH);
    
    pstSmaMsg->ulSenderCpuId        = VOS_LOCAL_CPUID;
    pstSmaMsg->ulSenderPid          = WUEPS_PID_TAF;
    pstSmaMsg->ulReceiverCpuId      = VOS_LOCAL_CPUID;
    pstSmaMsg->ulReceiverPid        = WUEPS_PID_TAF;
    pstSmaMsg->ulMsgId              = ID_TAF_SPM_SMMA_IND;
    pstSmaMsg->clientId             = INTERNAL_CLIENT_ID_SMMA;    

    if ( VOS_OK != PS_SEND_MSG( WUEPS_PID_TAF, pstSmaMsg ) )
    {
        MN_WARN_LOG( "TAF_MSG_SendSpmSmmaInd:WARNING:SEND ID_TAF_SPM_SMMA_IND msg FAIL!" );
    }

    return;
}
/* Added by s00217060 for VoLTE_PhaseII  项目, 2013-09-24, end */

/*****************************************************************************
 函 数 名  : TAF_MSG_SpmMsgReportInd
 功能描述  : 通知SPM短信发送report事件信息

 输入参数  : pstSubmitRptEvt  -- report事件信息地址
             pstMoEnity       -- MO实体地址
             ucSignallingType -- 当前消息发送信令类型

 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年12月13日
   作    者   : y00245242
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_MSG_SpmMsgReportInd(
    MN_MSG_SUBMIT_RPT_EVT_INFO_STRU    *pstSubmitRptEvt,
    MN_MSG_MO_ENTITY_STRU              *pstMoEntity,  
    TAF_MSG_SIGNALLING_TYPE_ENUM_UINT32 enSignallingType
)
{
    TAF_SPM_MSG_REPORT_IND_STRU        *pstMsg = VOS_NULL_PTR;

    pstMsg = (TAF_SPM_MSG_REPORT_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                                                                         sizeof(TAF_SPM_MSG_REPORT_IND_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        MN_WARN_LOG("TAF_MSG_SpmMsgReportInd:ERROR: message alloctiaon fail!");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstMsg) + VOS_MSG_HEAD_LENGTH, 
               0, 
               sizeof(TAF_SPM_MSG_REPORT_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->ulSenderCpuId        = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid          = WUEPS_PID_TAF;
    pstMsg->ulReceiverCpuId      = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid        = WUEPS_PID_TAF;
    pstMsg->ulMsgId              = ID_TAF_SPM_MSG_REPORT_IND;

    pstMsg->usClientId           = pstMoEntity->clientId;
    pstMsg->ucOpId               = pstMoEntity->opId;

    pstMsg->enSignallingType     = enSignallingType;
    pstMsg->ucReportFlag         = (VOS_UINT8)(pstMoEntity->bReportFlag);
    pstMsg->enSmsMoType          = pstMoEntity->enSmsMoType;
    pstMsg->ucBcOpId             = MN_MSG_GetBCopId();
    
    PS_MEM_CPY(&(pstMsg->stRptEvtInfo), pstSubmitRptEvt, sizeof(MN_MSG_SUBMIT_RPT_EVT_INFO_STRU));
    
    if ( VOS_OK != PS_SEND_MSG( WUEPS_PID_TAF, pstMsg ) )
    {
        MN_WARN_LOG( "TAF_MSG_SpmMsgReportInd:WARNING:SEND ID_TAF_SPM_MSG_REPORT_IND msg FAIL!" );
    }

    return;
}
#endif

/*****************************************************************************
 函 数 名  : TAF_MSG_SendSpmMsgCheckResultInd
 功能描述  : 通知SPM短信FDN 和Control检查失败
 输入参数  :
 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年11月14日
   作    者   : j00174725
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_MSG_SendSpmMsgCheckResultInd(
    MN_CLIENT_ID_T                      usClientId,
    MN_OPERATION_ID_T                   ucOpId,
    TAF_MSG_ERROR_ENUM_UINT32           enRslt
)
{
    TAF_SPM_MSG_CHECK_RESULT_IND_STRU  *pstMsg = VOS_NULL_PTR;

    pstMsg = (TAF_SPM_MSG_CHECK_RESULT_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                                                                         sizeof(TAF_SPM_MSG_CHECK_RESULT_IND_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        MN_WARN_LOG("TAF_MSG_SendSpmMsgCheckResultInd:ERROR: message alloctiaon fail!");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstMsg) + VOS_MSG_HEAD_LENGTH,
               0,
               sizeof(TAF_SPM_MSG_CHECK_RESULT_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->ulSenderCpuId        = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid          = WUEPS_PID_TAF;
    pstMsg->ulReceiverCpuId      = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid        = WUEPS_PID_TAF;
    pstMsg->ulMsgId              = ID_TAF_SPM_MSG_CHECK_RESULT_IND;

    pstMsg->usClientId           = usClientId;
    pstMsg->ucOpId               = ucOpId;
    pstMsg->enRslt               = enRslt;

    if ( VOS_OK != PS_SEND_MSG( WUEPS_PID_TAF, pstMsg ) )
    {
        MN_WARN_LOG( "TAF_MSG_SpmMsgReportInd:WARNING:SEND ID_TAF_SPM_MSG_REPORT_IND msg FAIL!" );
    }

    return;
}







#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

