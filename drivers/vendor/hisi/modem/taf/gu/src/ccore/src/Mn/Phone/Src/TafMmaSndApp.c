/******************************************************************************

                  版权所有 (C), 2013-2014, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafMmaSndApp.h
  版 本 号   : 初稿
  作    者   : w00167002
  生成日期   : 2014年2月14日
  最近修改   :
  功能描述   : TafMmaSndApp.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年2月14日
    作    者   : w00167002
    修改内容   : 创建文件

******************************************************************************/


/*****************************************************************************
   1 头文件包含
*****************************************************************************/
#include "PsTypeDef.h"
#include "MnComm.h"
#include "TafSdcCtx.h"
#include "TafLog.h"
#include "TafMmaSndApp.h"
#include "MmaMsccInterface.h"
#include "MmaAppLocal.h"
#include "TafStdlib.h"

#include "TafMmaCtx.h"

#include "TafMmaComFunc.h"

#include "NasMntn.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_TAF_MMA_SND_APP_C


/*****************************************************************************
   2 全局变量定义和宏
****************************************************************************/

/*lint -save -e958 */

/*****************************************************************************
   3 函数实现
*****************************************************************************/
/* Added by w00167002 for L-C互操作项目, 2014-2-14, begin */
/*****************************************************************************
 函 数 名  : TAF_MMA_SndSysCfgSetCnf
 功能描述  : 给MSG发送模式变更通知
 输入参数  : pstCtrl                    - 接收模块信息
             usErrorCause
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年2月14日
    作    者   : w00167002
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_MMA_SndSysCfgSetCnf(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCause
)
{
    TAF_MMA_SYS_CFG_CNF_STRU           *pstSndMsg   = VOS_NULL_PTR;

    pstSndMsg = (TAF_MMA_SYS_CFG_CNF_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                             WUEPS_PID_MMA,
                                             sizeof(TAF_MMA_SYS_CFG_CNF_STRU));
    if (VOS_NULL_PTR == pstSndMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA,"TAF_MMA_SndSysCfgSetCnf:Alloc Msg Failed");
        return;
    }

    PS_MEM_SET( (VOS_INT8 *)pstSndMsg + VOS_MSG_HEAD_LENGTH, 0X00,
            sizeof(TAF_MMA_SYS_CFG_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstSndMsg->ulSenderCpuId            = VOS_LOCAL_CPUID;
    pstSndMsg->ulSenderPid              = WUEPS_PID_MMA;
    pstSndMsg->ulReceiverCpuId          = VOS_LOCAL_CPUID;
    pstSndMsg->ulReceiverPid            = pstCtrl->ulModuleId;
    pstSndMsg->ulMsgName                = ID_TAF_MMA_SYS_CFG_SET_CNF;
    pstSndMsg->usClientId               = pstCtrl->usClientId;
    pstSndMsg->ucOpid                   = pstCtrl->ucOpId;

    if (TAF_ERR_NO_ERROR != enErrorCause)
    {
        pstSndMsg->enRslt = TAF_MMA_APP_OPER_RESULT_FAILURE;
    }
    else
    {
        pstSndMsg->enRslt = TAF_MMA_APP_OPER_RESULT_SUCCESS;
    }

    pstSndMsg->enErrorCause             = enErrorCause;

    PS_SEND_MSG(WUEPS_PID_MMA, pstSndMsg);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_SndEonsUcs2Rsp
 功能描述  : 发消息回复EONSUCS2查询结果
 输入参数  : pstCtrl                    - 接收模块信息
             enRslt                     - 查询结果
             usErrorCause               - 错误码
             pstEonsUcs2PlmnName        - 查询结果的结构体
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月12日
    作    者   : c00318887
    修改内容   : 新生成函数
*****************************************************************************/

VOS_VOID TAF_MMA_SndEonsUcs2Rsp(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    TAF_MMA_APP_OPER_RESULT_ENUM_UINT32 enRslt,
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCause,
    TAF_MMA_EONS_UCS2_PLMN_NAME_STRU   *pstEonsUcs2PlmnName
)
{
    TAF_MMA_EONS_UCS2_CNF_STRU         *pstSndMsg   = VOS_NULL_PTR;
    VOS_UINT32                          ulRst;

    pstSndMsg = (TAF_MMA_EONS_UCS2_CNF_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                        WUEPS_PID_MMA,
                                        sizeof(TAF_MMA_EONS_UCS2_CNF_STRU));
    if (VOS_NULL_PTR == pstSndMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA,"TAF_MMA_SndEonsUcs2Rsp:Alloc Msg Failed");
        return;
    }

    PS_MEM_SET( (VOS_INT8 *)pstSndMsg + VOS_MSG_HEAD_LENGTH, 0X00,
            sizeof(TAF_MMA_EONS_UCS2_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstSndMsg->ulSenderCpuId            = VOS_LOCAL_CPUID;
    pstSndMsg->ulSenderPid              = WUEPS_PID_MMA;
    pstSndMsg->ulReceiverCpuId          = VOS_LOCAL_CPUID;
    pstSndMsg->ulReceiverPid            = pstCtrl->ulModuleId;
    pstSndMsg->ulMsgName                = ID_TAF_MSG_MMA_EONS_UCS2_CNF;
    pstSndMsg->usClientId               = pstCtrl->usClientId;
    pstSndMsg->ucOpId                   = pstCtrl->ucOpId;
    pstSndMsg->enRslt                   = enRslt;
    pstSndMsg->enErrorCause             = enErrorCause;

    if (VOS_NULL_PTR != pstEonsUcs2PlmnName)
    {
        PS_MEM_CPY(&pstSndMsg->stEonsUcs2PlmnName,
                    pstEonsUcs2PlmnName,
                    sizeof(TAF_MMA_EONS_UCS2_PLMN_NAME_STRU));
    }

    ulRst = PS_SEND_MSG(WUEPS_PID_MMA, pstSndMsg);

    if (VOS_OK != ulRst)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA,"TAF_MMA_SndEonsUcs2Rsp:Send Msg Failed");
        return;
    }

    return;

}


/*****************************************************************************
 函 数 名  : TAF_MMA_SndPhoneModeSetCnf
 功能描述  : 给MSG发送模式变更通知
 输入参数  : pstCtrl                    - 接收模块信息
             enRslt
             pstPdpDnsInfo              - PDP DNS信息
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年2月14日
    作    者   : w00167002
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_MMA_SndPhoneModeSetCnf(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    TAF_PH_MODE                         ucPhMode,
    TAF_MMA_APP_OPER_RESULT_ENUM_UINT32 enRslt,
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCause
)
{
    TAF_MMA_PHONE_MODE_SET_CNF_STRU    *pstSndMsg   = VOS_NULL_PTR;
    VOS_UINT32                          ulRst;

    pstSndMsg = (TAF_MMA_PHONE_MODE_SET_CNF_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                             WUEPS_PID_MMA,
                                             sizeof(TAF_MMA_PHONE_MODE_SET_CNF_STRU));
    if (VOS_NULL_PTR == pstSndMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA,"TAF_MMA_SndPhoneModeSetCnf:Alloc Msg Failed");

        return;
    }

    PS_MEM_SET( (VOS_INT8 *)pstSndMsg + VOS_MSG_HEAD_LENGTH, 0X00,
            sizeof(TAF_MMA_PHONE_MODE_SET_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstSndMsg->ulSenderCpuId            = VOS_LOCAL_CPUID;
    pstSndMsg->ulSenderPid              = WUEPS_PID_MMA;
    pstSndMsg->ulReceiverCpuId          = VOS_LOCAL_CPUID;
    pstSndMsg->ulReceiverPid            = pstCtrl->ulModuleId;
    pstSndMsg->ulMsgName                = ID_TAF_MMA_PHONE_MODE_SET_CNF;
    pstSndMsg->usClientId               = pstCtrl->usClientId;
    pstSndMsg->ucOpid                   = pstCtrl->ucOpId;
    pstSndMsg->ucPhMode                 = ucPhMode;
    pstSndMsg->enRslt                   = enRslt;
    pstSndMsg->enErrorCause             = enErrorCause;

    ulRst = PS_SEND_MSG(WUEPS_PID_MMA, pstSndMsg);

    if (VOS_OK != ulRst)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA,"TAF_MMA_SndPhoneModeSetCnf:Send Msg Failed");

        return;
    }

    return;

}

/* Added by w00167002 for L-C互操作项目, 2014-2-14, end */

/* Added by b00269685 for L-C互操作项目, 2014-2-14, begin */
/*****************************************************************************
 函 数 名  : TAF_MMA_SndAcqBestNetworkCnf
 功能描述  : 给MSG发送模式变更通知
 输入参数  : pstCtrl                    - 接收模块信息
             enRslt
             pstAcqCnfMsg
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年2月14日
    作    者   : b00269685
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_MMA_SndAcqBestNetworkCnf(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    TAF_MMA_APP_OPER_RESULT_ENUM_UINT32 enRslt,
    MSCC_MMA_ACQ_CNF_STRU               *pstAcqCnfMsg
)
{
    TAF_MMA_ACQ_CNF_STRU               *pstSndMsg   = VOS_NULL_PTR;
    VOS_UINT32                          ulRst;

    pstSndMsg = (TAF_MMA_ACQ_CNF_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                         WUEPS_PID_MMA,
                                         sizeof(TAF_MMA_ACQ_CNF_STRU));
    if (VOS_NULL_PTR == pstSndMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA,"TAF_MMA_SndAcqBestNetworkCnf:Alloc Msg Failed");
        return;
    }

    PS_MEM_SET( (VOS_INT8 *)pstSndMsg + VOS_MSG_HEAD_LENGTH, 0X00,
            sizeof(TAF_MMA_ACQ_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstSndMsg->ulSenderCpuId            = VOS_LOCAL_CPUID;
    pstSndMsg->ulSenderPid              = WUEPS_PID_MMA;
    pstSndMsg->ulReceiverCpuId          = VOS_LOCAL_CPUID;
    pstSndMsg->ulReceiverPid            = pstCtrl->ulModuleId;
    pstSndMsg->ulMsgName                = ID_TAF_MMA_ACQ_BEST_NETWORK_CNF;
    pstSndMsg->usClientId               = pstCtrl->usClientId;
    pstSndMsg->ucOpid                   = pstCtrl->ucOpId;
    pstSndMsg->enRslt                   = enRslt;
    pstSndMsg->stPlmnId.Mcc             = pstAcqCnfMsg->stPlmnId.ulMcc;
    pstSndMsg->stPlmnId.Mnc             = pstAcqCnfMsg->stPlmnId.ulMnc;
    pstSndMsg->ulArfcn                  = pstAcqCnfMsg->ulArfcn;

    /* 转换并设置当前的Plmn Priority Class */
    TAF_MMA_ConvertPlmnPriorityClass(pstAcqCnfMsg->enPrioClass, &(pstSndMsg->enPrioClass));

    ulRst = PS_SEND_MSG(WUEPS_PID_MMA, pstSndMsg);

    if (VOS_OK != ulRst)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA,"TAF_MMA_SndAcqBestNetworkCnf:Send Msg Failed");
        return;
    }

    return;

}

/* Added by b00269685 for L-C互操作项目, 2014-2-14, begin */
/*****************************************************************************
 函 数 名  : TAF_MMA_SndRegCnf
 功能描述  : 给MSG发送模式变更通知
 输入参数  : pstCtrl                    - 接收模块信息
             enRslt
             pstRegCnfMsg
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年2月14日
    作    者   : b00269685
    修改内容   : 新生成函数
  2.日    期   : 2015年4月22日
    作    者   : wx270776
    修改内容   : DTS2015031602665:将LMM ATTACH注册状态带给CMMCA
*****************************************************************************/
VOS_VOID TAF_MMA_SndRegCnf(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    TAF_MMA_APP_OPER_RESULT_ENUM_UINT32 enRslt,
    MSCC_MMA_REG_CNF_STRU               *pstRegCnfMsg
)
{
    TAF_MMA_REG_CNF_STRU               *pstSndMsg   = VOS_NULL_PTR;
    VOS_UINT32                          ulRst;

    pstSndMsg = (TAF_MMA_REG_CNF_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                         WUEPS_PID_MMA,
                                         sizeof(TAF_MMA_REG_CNF_STRU));
    if (VOS_NULL_PTR == pstSndMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA,"TAF_MMA_SndRegCnf:Alloc Msg Failed");
        return;
    }

    PS_MEM_SET( (VOS_INT8 *)pstSndMsg + VOS_MSG_HEAD_LENGTH, 0X00,
            sizeof(TAF_MMA_REG_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstSndMsg->ulSenderCpuId            = VOS_LOCAL_CPUID;
    pstSndMsg->ulSenderPid              = WUEPS_PID_MMA;
    pstSndMsg->ulReceiverCpuId          = VOS_LOCAL_CPUID;
    pstSndMsg->ulReceiverPid            = pstCtrl->ulModuleId;
    pstSndMsg->ulMsgName                = ID_TAF_MMA_REG_CNF;
    pstSndMsg->usClientId               = pstCtrl->usClientId;
    pstSndMsg->ucOpid                   = pstCtrl->ucOpId;
    pstSndMsg->enRslt                   = enRslt;
    pstSndMsg->stPlmnId.Mcc             = pstRegCnfMsg->stPlmnId.ulMcc;
    pstSndMsg->stPlmnId.Mnc             = pstRegCnfMsg->stPlmnId.ulMnc;
    pstSndMsg->ulArfcn                  = pstRegCnfMsg->ulArfcn;

    /* 转换并设置当前的Plmn Priority Class */
    TAF_MMA_ConvertPlmnPriorityClass(pstRegCnfMsg->enPrioClass, &(pstSndMsg->enPrioClass));
    pstSndMsg->enLmmAttachRegStatus     = pstRegCnfMsg->enLmmAttachClRegStatus;

    ulRst = PS_SEND_MSG(WUEPS_PID_MMA, pstSndMsg);

    if (VOS_OK != ulRst)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA,"TAF_MMA_SndRegCnf:Send Msg Failed");
        return;
    }

    return;

}

/*****************************************************************************
 函 数 名  : TAF_MMA_SndPowerSaveCnf
 功能描述  : 给MSG发送模式变更通知
 输入参数  : pstCtrl                     - 接收模块信息
             enRslt
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年2月14日
    作    者   : b00269685
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_MMA_SndPowerSaveCnf(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    TAF_MMA_APP_OPER_RESULT_ENUM_UINT32 enRslt
)
{
    TAF_MMA_POWER_SAVE_CNF_STRU        *pstSndMsg   = VOS_NULL_PTR;
    VOS_UINT32                          ulRst;

    pstSndMsg = (TAF_MMA_POWER_SAVE_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                 WUEPS_PID_MMA,
                                                 sizeof(TAF_MMA_POWER_SAVE_CNF_STRU));
    if (VOS_NULL_PTR == pstSndMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA,"TAF_MMA_SndPowerSaveCnf:Alloc Msg Failed");
        return;
    }

    PS_MEM_SET( (VOS_INT8 *)pstSndMsg + VOS_MSG_HEAD_LENGTH, 0X00,
            sizeof(TAF_MMA_POWER_SAVE_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstSndMsg->ulSenderCpuId            = VOS_LOCAL_CPUID;
    pstSndMsg->ulSenderPid              = WUEPS_PID_MMA;
    pstSndMsg->ulReceiverCpuId          = VOS_LOCAL_CPUID;
    pstSndMsg->ulReceiverPid            = pstCtrl->ulModuleId;
    pstSndMsg->ulMsgName                = ID_TAF_MMA_POWER_SAVE_CNF;
    pstSndMsg->usClientId               = pstCtrl->usClientId;
    pstSndMsg->ucOpid                   = pstCtrl->ucOpId;
    pstSndMsg->enRslt                   = enRslt;

    ulRst = PS_SEND_MSG(WUEPS_PID_MMA, pstSndMsg);

    if (VOS_OK != ulRst)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA,"TAF_MMA_SndPowerSaveCnf:Send Msg Failed");
        return;
    }

    return;

}

/*****************************************************************************
 函 数 名  : TAF_MMA_SndDetachCnf
 功能描述  : Detach结果回复
 输入参数  : ulRcvPid        ---  接收模块PID
            : usCliendId     ---  外部模块CliendId
            ucOpId           ---  外部模块OpId
            enDetachRslt     ---  Detach结果
 输出参数  : 无
 返 回 值  : VOS_TRUE:成功,VOS_FALSE:失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月27日
    作    者   : s00246516
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_SndDetachCnf(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    TAF_MMA_APP_OPER_RESULT_ENUM_UINT32 enDetachRslt,
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCause
)
{
    TAF_MMA_DETACH_CNF_STRU            *pstDetachCnf = VOS_NULL_PTR;

    /* 申请消息包TAF_MMA_DETACH_CNF_STRU */
    pstDetachCnf = (TAF_MMA_DETACH_CNF_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                           WUEPS_PID_MMA,
                                           sizeof(TAF_MMA_DETACH_CNF_STRU));

    /* 内存申请失败，返回 */
    if (VOS_NULL_PTR == pstDetachCnf)
    {
        return;
    }

    PS_MEM_SET( (VOS_INT8 *)pstDetachCnf + VOS_MSG_HEAD_LENGTH, 0X00,
            sizeof(TAF_MMA_DETACH_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 根据输入参数填充TAF_MMA_DETACH_CNF_STRU */
    pstDetachCnf->ulSenderPid       = WUEPS_PID_MMA;
    pstDetachCnf->ulReceiverPid     = pstCtrl->ulModuleId;
    pstDetachCnf->ulMsgName         = ID_TAF_MMA_DETACH_CNF;

    pstDetachCnf->usClientId        = pstCtrl->usClientId;
    pstDetachCnf->ucOpid            = pstCtrl->ucOpId;
    pstDetachCnf->enRslt            = enDetachRslt;
    pstDetachCnf->enErrorCause      = enErrorCause;

    /* 发送消息 */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_MMA, pstDetachCnf))
    {
        return;
    }

    return;

}

#if (FEATURE_ON == FEATURE_CL_INTERWORK)

/*****************************************************************************
 函 数 名  : TAF_MMA_SndCmmcaServiceInd
 功能描述  : 发送服务状态消息给CMMCA
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年2月14日
   作    者   : s00246516
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_MMA_SndCmmcaServiceInd(VOS_VOID)
{
    TAF_MMA_SERVICE_STATUS_IND_STRU    *pstSndMsg    = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;

    /* 申请内存  */
    pstSndMsg = (TAF_MMA_SERVICE_STATUS_IND_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMA,
                           sizeof(TAF_MMA_SERVICE_STATUS_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstSndMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndCmmcaServiceInd: Memory allocation is failure");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstSndMsg) + VOS_MSG_HEAD_LENGTH, 0, sizeof(TAF_MMA_SERVICE_STATUS_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* fill in header information */
    pstSndMsg->ulSenderCpuId      = VOS_LOCAL_CPUID;
    pstSndMsg->ulSenderPid        = WUEPS_PID_MMA;
    pstSndMsg->ulReceiverCpuId    = VOS_LOCAL_CPUID;
    pstSndMsg->ulReceiverPid      = WUEPS_PID_CMMCA;
    pstSndMsg->ulLength           = sizeof(TAF_MMA_SERVICE_STATUS_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    /* fill in message name */
    pstSndMsg->ulMsgName          = ID_TAF_MMA_SERVICE_STATUS_IND;

    /* fill in clientid and opid */
    pstSndMsg->usClientId         = CMMCA_CLIENT_ID;
    pstSndMsg->ucOpid             = 0x0;

    /* fill in message content */
    TAF_MMA_ConvertServiceStatus(TAF_SDC_GetCsServiceStatus(), &(pstSndMsg->CsSrvSta));
    TAF_MMA_ConvertServiceStatus(TAF_SDC_GetPsServiceStatus(), &(pstSndMsg->PsSrvSta));

    pstSndMsg->ucCsSimValid       = TAF_SDC_GetSimCsRegStatus();
    pstSndMsg->ucPsSimValid       = TAF_SDC_GetSimPsRegStatus();

    /* send message */
    ulRet = PS_SEND_MSG(WUEPS_PID_MMA, pstSndMsg);
    if (VOS_OK != ulRet)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndCmmcaServiceInd: Send message is failure");
    }

    return;
}


/*****************************************************************************
 函 数 名  : TAF_MMA_SndAcqInd
 功能描述  : 给MSG发送模式变更通知
 输入参数  : enRslt
             pstAcqIndMsg
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年2月14日
    作    者   : b00269685
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_MMA_SndAcqInd(
    TAF_MMA_APP_OPER_RESULT_ENUM_UINT32 enRslt,
    MSCC_MMA_ACQ_IND_STRU               *pstAcqIndMsg
)
{
    TAF_MMA_ACQ_IND_STRU               *pstSndMsg   = VOS_NULL_PTR;
    VOS_UINT32                          ulRst;

    pstSndMsg = (TAF_MMA_ACQ_IND_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                         WUEPS_PID_MMA,
                                         sizeof(TAF_MMA_ACQ_IND_STRU));
    if (VOS_NULL_PTR == pstSndMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA,"TAF_MMA_SndAcqInd:Alloc Msg Failed");
        return;
    }

    PS_MEM_SET( (VOS_INT8 *)pstSndMsg + VOS_MSG_HEAD_LENGTH, 0X00,
            sizeof(TAF_MMA_ACQ_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    pstSndMsg->ulSenderCpuId            = VOS_LOCAL_CPUID;
    pstSndMsg->ulSenderPid              = WUEPS_PID_MMA;
    pstSndMsg->ulReceiverCpuId          = VOS_LOCAL_CPUID;
    pstSndMsg->ulReceiverPid            = WUEPS_PID_CMMCA;
    pstSndMsg->ulMsgName                = ID_TAF_MMA_ACQ_IND;
    pstSndMsg->usClientId               = CMMCA_CLIENT_ID;
    pstSndMsg->ucOpid                   = 0;
    pstSndMsg->enRslt                   = enRslt;
    pstSndMsg->stPlmnId.Mcc             = pstAcqIndMsg->stPlmnId.ulMcc;
    pstSndMsg->stPlmnId.Mnc             = pstAcqIndMsg->stPlmnId.ulMnc;
    pstSndMsg->ulArfcn                  = pstAcqIndMsg->ulArfcn;

    /* 转换并设置当前的Plmn Priority Class */
    TAF_MMA_ConvertPlmnPriorityClass(pstAcqIndMsg->enPrioClass, &(pstSndMsg->enPrioClass));

    ulRst = PS_SEND_MSG(WUEPS_PID_MMA, pstSndMsg);

    if (VOS_OK != ulRst)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA,"TAF_MMA_SndAcqInd:Send Msg Failed");
        return;
    }

    return;

}


/*****************************************************************************
 函 数 名  : TAF_MMA_SndCmmcaSysInfoInd
 功能描述  : 给MSG发送模式变更通知
 输入参数  : ulMcc
             ulMnc
             usArfcn
             enPrioClass
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月14日
    作    者   : b00269685
    修改内容   : 新生成函数
  2.日    期   : 2015年7月20日
   作    者   : w000316404
   修改内容   : R11协议升级(LTE频点配置值扩展)
*****************************************************************************/
VOS_VOID TAF_MMA_SndCmmcaSysInfoInd(
    VOS_UINT32                                              ulMcc,
    VOS_UINT32                                              ulMnc,
    VOS_UINT32                                              ulArfcn,
    NAS_MSCC_PIF_PLMN_PRIORITY_CLASS_ENUM_UINT8             enPrioClass
)
{
    TAF_MMA_SYS_INFO_IND_STRU          *pstSndMsg   = VOS_NULL_PTR;
    VOS_UINT32                          ulRst;

    pstSndMsg = (TAF_MMA_SYS_INFO_IND_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                             WUEPS_PID_MMA,
                                             sizeof(TAF_MMA_SYS_INFO_IND_STRU));
    if (VOS_NULL_PTR == pstSndMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA,"TAF_MMA_SndSysInfoInd:Alloc Msg Failed");
        return;
    }

    PS_MEM_SET( (VOS_INT8 *)pstSndMsg + VOS_MSG_HEAD_LENGTH, 0X00,
            sizeof(TAF_MMA_SYS_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    pstSndMsg->ulSenderCpuId            = VOS_LOCAL_CPUID;
    pstSndMsg->ulSenderPid              = WUEPS_PID_MMA;
    pstSndMsg->ulReceiverCpuId          = VOS_LOCAL_CPUID;
    pstSndMsg->ulReceiverPid            = WUEPS_PID_CMMCA;
    pstSndMsg->ulMsgName                = ID_TAF_MMA_SYS_INFO_IND;
    pstSndMsg->usClientId               = CMMCA_CLIENT_ID;
    pstSndMsg->ucOpid                   = 0;
    pstSndMsg->stPlmnId.Mcc             = ulMcc;
    pstSndMsg->stPlmnId.Mnc             = ulMnc;
    pstSndMsg->ulArfcn                  = ulArfcn;

    /* 转换并设置当前的Plmn Priority Class */
    TAF_MMA_ConvertPlmnPriorityClass(enPrioClass, &(pstSndMsg->enPrioClass));

    ulRst = PS_SEND_MSG(WUEPS_PID_MMA, pstSndMsg);

    if (VOS_OK != ulRst)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA,"TAF_MMA_SndSysInfoInd:Send Msg Failed");
        return;
    }

    return;

}



/*****************************************************************************
 函 数 名  : TAF_MMA_SndSysInfoInd
 功能描述  : 给MSG发送模式变更通知
 输入参数  : ulMcc
             ulMnc
             usArfcn
             enPrioClass
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月20日
    作    者   : w00167002
    修改内容   : 新生成函数
  2.日    期   : 2015年2月6日
    作    者   : h00313353
    修改内容   : USIMM卡接口调整
*****************************************************************************/
VOS_VOID TAF_MMA_SndSimStatusInd(
    TAF_MMA_USIMM_CARD_TYPE_ENUM_UINT32           enCardType,                    /* 卡类型:SIM、USIM、ROM-SIM  */
    TAF_MMA_CARD_STATUS_ENUM_UINT8                enCardStatus
)
{
    TAF_MMA_SIM_STATUS_IND_STRU        *pstSndMsg   = VOS_NULL_PTR;
    VOS_UINT32                          ulRst;

    pstSndMsg = (TAF_MMA_SIM_STATUS_IND_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                             WUEPS_PID_MMA,
                                             sizeof(TAF_MMA_SIM_STATUS_IND_STRU));
    if (VOS_NULL_PTR == pstSndMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA,"TAF_MMA_SndSimStatusInd:Alloc Msg Failed");
        return;
    }

    PS_MEM_SET( (VOS_INT8 *)pstSndMsg + VOS_MSG_HEAD_LENGTH, 0X00,
            sizeof(TAF_MMA_SIM_STATUS_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    pstSndMsg->ulSenderCpuId            = VOS_LOCAL_CPUID;
    pstSndMsg->ulSenderPid              = WUEPS_PID_MMA;
    pstSndMsg->ulReceiverCpuId          = VOS_LOCAL_CPUID;
    pstSndMsg->ulReceiverPid            = WUEPS_PID_CMMCA;
    pstSndMsg->ulMsgName                = ID_TAF_MMA_SIM_STATUS_IND;
    pstSndMsg->usClientId               = CMMCA_CLIENT_ID;
    pstSndMsg->ucOpid                   = 0;
    pstSndMsg->enCardType               = enCardType;
    pstSndMsg->enCardStatus             = enCardStatus;

    ulRst = PS_SEND_MSG(WUEPS_PID_MMA, pstSndMsg);
    if (VOS_OK != ulRst)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA,"TAF_MMA_SndSimStatusInd:Send Msg Failed");
        return;
    }

    return;

}

#endif

/* Added by b00269685 for L-C互操作项目, 2014-2-14, end */

/* 移该函数实现到TafMmaSndTaf.c */

/*lint -restore */
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
 函 数 名  : TAF_MMA_SndCdmaCsqSetCnf
 功能描述  : 给AT发送ID_TAF_MMA_CDMACSQ_SET_CNF
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月25日
    作    者   : m00312079
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_MMA_SndCdmaCsqSetCnf(
    TAF_MMA_CTRL_STRU                                      *pstCtrl,
    TAF_MMA_APP_OPER_RESULT_ENUM_UINT32                     enRslt
)
{
    TAF_MMA_CDMACSQ_SET_CNF_STRU            *pstCdmaCsqCnf   = VOS_NULL_PTR;

    /* 申请消息包TAF_MMA_CDMACSQ_SET_CNF_STRU */
    pstCdmaCsqCnf = (TAF_MMA_CDMACSQ_SET_CNF_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                           WUEPS_PID_MMA,
                                           sizeof(TAF_MMA_CDMACSQ_SET_CNF_STRU));

    /* 内存申请失败，返回 */
    if (VOS_NULL_PTR == pstCdmaCsqCnf)
    {
        return;
    }

    PS_MEM_SET( (VOS_INT8 *)pstCdmaCsqCnf + VOS_MSG_HEAD_LENGTH, 0X00,
            sizeof(TAF_MMA_CDMACSQ_SET_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 根据输入参数填充TAF_MMA_CDMACSQ_SET_CNF_STRU */
    pstCdmaCsqCnf->ulSenderPid       = WUEPS_PID_MMA;
    pstCdmaCsqCnf->ulReceiverPid     = pstCtrl->ulModuleId;
    pstCdmaCsqCnf->ulMsgName         = ID_TAF_MMA_CDMACSQ_SET_CNF;

    pstCdmaCsqCnf->usClientId        = pstCtrl->usClientId;
    pstCdmaCsqCnf->ucOpId            = pstCtrl->ucOpId;
    pstCdmaCsqCnf->enRslt            = enRslt;

    /* 发送消息 */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_MMA, pstCdmaCsqCnf))
    {
        return;
    }

    return;

}

/*****************************************************************************
 函 数 名  : TAF_MMA_SndCdmaCsqInd
 功能描述  : 给AT发送ID_TAF_MMA_CDMACSQ_IND
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :


 修改历史      :
  1.日    期   : 2014年12月25日
    作    者   : m00312079
    修改内容   : 新生成函数

  2.日    期   : 2015年10月16日
    作    者   : m00312079
    修改内容   : DTS2015101505057:添加ec/Io的上报门限
*****************************************************************************/
VOS_VOID TAF_MMA_SndCdmaCsqInd(VOS_INT16 sCdmaRssi,VOS_INT16 sCdmaEcIo)
{
    TAF_MMA_CDMACSQ_IND_STRU           *pstCdmaCsqInd = VOS_NULL_PTR;

    /* 申请消息包TAF_MMA_CDMACSQ_SET_CNF_STRU */
    pstCdmaCsqInd = (TAF_MMA_CDMACSQ_IND_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                           WUEPS_PID_MMA,
                                           sizeof(TAF_MMA_CDMACSQ_IND_STRU));

    /* 内存申请失败，返回 */
    if (VOS_NULL_PTR == pstCdmaCsqInd)
    {
        return;
    }

    PS_MEM_SET( (VOS_INT8 *)pstCdmaCsqInd + VOS_MSG_HEAD_LENGTH, 0X00,
            sizeof(TAF_MMA_CDMACSQ_IND_STRU) - VOS_MSG_HEAD_LENGTH);


    /* 填写消息头部信息 */
    pstCdmaCsqInd->ulReceiverPid = WUEPS_PID_AT;
    pstCdmaCsqInd->ulMsgName     = ID_TAF_MMA_CDMACSQ_IND;
    pstCdmaCsqInd->usClientId    = MN_GetRealClientId(MMA_CLIENTID_BROADCAST, WUEPS_PID_MMA);
    pstCdmaCsqInd->ucOpid        = MMA_OP_ID_INTERNAL;
    pstCdmaCsqInd->sCdmaRssi     = sCdmaRssi;
    pstCdmaCsqInd->sCdmaEcIo     = sCdmaEcIo;

     /* 发送消息 */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_MMA, pstCdmaCsqInd))
    {
        MMA_ERRORLOG("TAF_MMA_SndCdmaCsqInd: Send Msg Error!");
    }

    return;
}


/*****************************************************************************
 函 数 名  : TAF_MMA_SndCFreqLockSetCnf
 功能描述  : MMA向AT发送锁频设置的结果
 输入参数  : TAF_MMA_CFREQ_LOCK_SET_REQ_STRU *pstCFreqLockSetReq
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月29日
    作    者   : y00307564
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_MMA_SndCFreqLockSetCnf(
    TAF_MMA_CFREQ_LOCK_SET_REQ_STRU    *pstCFreqLockSetReq,
    VOS_UINT32                          ulRslt
)
{
    TAF_MMA_CFREQ_LOCK_SET_CNF_STRU    *pstCFreqLockSetCnf    = VOS_NULL_PTR;

    pstCFreqLockSetCnf =
            (TAF_MMA_CFREQ_LOCK_SET_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MMA,
                                                                        sizeof(TAF_MMA_CFREQ_LOCK_SET_CNF_STRU));
    if (VOS_NULL_PTR == pstCFreqLockSetCnf)
    {
        return VOS_FALSE;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstCFreqLockSetCnf + VOS_MSG_HEAD_LENGTH),
               0x00,
               (sizeof(TAF_MMA_CFREQ_LOCK_SET_CNF_STRU) - VOS_MSG_HEAD_LENGTH));

    /* 填写消息头部信息 */
    pstCFreqLockSetCnf->ulReceiverPid          = pstCFreqLockSetReq->ulModuleId;
    pstCFreqLockSetCnf->ulMsgName              = ID_TAF_MMA_CDMA_FREQ_LOCK_SET_CNF;
    pstCFreqLockSetCnf->stCtrl.ulModuleId      = pstCFreqLockSetReq->ulModuleId;
    pstCFreqLockSetCnf->stCtrl.usClientId      = pstCFreqLockSetReq->usClientId;
    pstCFreqLockSetCnf->stCtrl.ucOpId          = pstCFreqLockSetReq->ucOpId;
    pstCFreqLockSetCnf->ulRslt                 = ulRslt;

    /* 发送消息 */
    PS_SEND_MSG(WUEPS_PID_MMA, pstCFreqLockSetCnf);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_SndCTimeInd
 功能描述  : send ctime ind
 输入参数  :
            pstTimezoneCTime  -- 时区时间信息
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月26日
    作    者   : x00314862
    修改内容   :
*****************************************************************************/
VOS_UINT32 TAF_MMA_SndCTimeInd(
    TAF_MMA_TIME_ZONE_CTIME_STRU       *pstTimezoneCTime
)
{
    TAF_MMA_CTIME_IND_STRU             *pstCTimeInd;

    pstCTimeInd = (TAF_MMA_CTIME_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MMA,
                                                                             sizeof(TAF_MMA_CTIME_IND_STRU));
    if (VOS_NULL_PTR == pstCTimeInd)
    {
        MMA_ERRORLOG("TAF_MMA_SndCTimeInd: ERROR:ALLOC MEMORY FAIL.");
        return VOS_ERR;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstCTimeInd + VOS_MSG_HEAD_LENGTH),
               0x00,
               (sizeof(TAF_MMA_CTIME_IND_STRU) - VOS_MSG_HEAD_LENGTH));

    /* fill head message info */
    pstCTimeInd->ulReceiverPid = WUEPS_PID_AT;
    pstCTimeInd->ulMsgName     = ID_TAF_MMA_CTIME_IND;
    pstCTimeInd->usClientId    = MN_GetRealClientId(MMA_CLIENTID_BROADCAST, WUEPS_PID_MMA);
    pstCTimeInd->ucOpid        = MMA_OP_ID_INTERNAL;

    PS_MEM_CPY(&(pstCTimeInd->stTimezoneCTime), pstTimezoneCTime, sizeof(TAF_MMA_TIME_ZONE_CTIME_STRU));

    /* send message */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_MMA, pstCTimeInd))
    {
        MMA_ERRORLOG("TAF_MMA_SndCTimeInd: Send Msg Error!");
        return VOS_ERR;
    }

    return VOS_OK;
}
/*****************************************************************************
 函 数 名  : TAF_MMA_FillCTimeIndStru
 功能描述  : fill ctime ind structure
 输入参数  :
            XSD_MMA_1X_SYS_TIME_STRU           *pstSysTime,
            TAF_MMA_TIME_ZONE_CTIME_STRU       *pstTimezoneCTime

 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月26日
    作    者   : x00314862
    修改内容   :
  2.日    期   : 2015年3月4日
    作    者   : f00279542
    修改内容   : 系统时间的秒数只需要减去lp sec，上报的时间是UTC时间
*****************************************************************************/
VOS_UINT32 TAF_MMA_FillCTimeIndStru(
    NAS_MSCC_PIF_1X_SYS_TIME_STRU      *pstSysTime,
    TAF_MMA_TIME_ZONE_CTIME_STRU       *pstTimezoneCTime
)
{
    TAF_STD_TIME_ZONE_TYPE_STRU         stUniversalTimeandLocalTimeZone;
    VOS_UINT32                          ulHighSystemTime;
    VOS_UINT32                          ulLowSystemTime;
    VOS_UINT32                          ulHighTmp;
    VOS_UINT32                          ulLowTmp;
    VOS_UINT32                          ulRemainder;
    VOS_UINT32                          ulRslt;

    ulHighTmp = 0;
    ulLowTmp  = 0;
    ulHighSystemTime = 0;
    ulLowSystemTime  = 0;
    ulRemainder = 0;

    PS_MEM_SET(&stUniversalTimeandLocalTimeZone, 0X00, sizeof(TAF_STD_TIME_ZONE_TYPE_STRU));

    /*
    SYS_TIME - System time.
    The base station shall set this field to the System Time as of
    four Sync Channel superframes (320 ms) after the end of the
    last superframe containing any part of this  Sync Channel
    Message, minus the pilot PN sequence offset, in units of 80
    ms (see 1.3 of [2]).
    */
    TAF_STD_ConvertSystemTimeToHighLow(pstSysTime->aucSysTime, &ulHighSystemTime, &ulLowSystemTime);

    /*
    LTM_OFF - Offset of local time from System Time.
    The base station shall set this field to the two抯 complement
    offset of local time from System Time, in units of 30 minutes.
    The local time of day, in units of 80 ms, as of four Sync
    Channel superframes (320 ms) after the end of the last
    superframe containing any part of this Sync Channel Message,
    minus the pilot PN sequence offset, is equal to SYS_TIME -
    (LP_SEC*12.5) + (LTM_OFF *22500).
     */
    ulRslt = TAF_STD_64Sub32(ulHighSystemTime, ulLowSystemTime,
                   (VOS_UINT32)((pstSysTime->ucLpSec * TAF_MMA_MILLISECOND_FOR_ONE_SECOND) / TAF_MMA_EIGHTY_MILLISECOND_UNIT),
                   &ulHighTmp, &ulLowTmp);
    if (VOS_OK != ulRslt)
    {
        return VOS_ERR;
    }
    /* 把system time换算成秒数 */
    ulRslt = VOS_64Multi32(ulHighTmp, ulLowTmp, TAF_MMA_EIGHTY_MILLISECOND_UNIT, &ulHighSystemTime, &ulLowSystemTime);
    if (VOS_OK != ulRslt)
    {
        return VOS_ERR;
    }

    ulRslt = VOS_64Div32(ulHighSystemTime, ulLowSystemTime, TAF_MMA_MILLISECOND_FOR_ONE_SECOND, &ulHighTmp, &ulLowTmp, &ulRemainder);
    if (VOS_OK != ulRslt)
    {
        return VOS_ERR;
    }

    /* 把当前系统的时间转化成年月日 时分秒 */
    ulRslt = TAF_STD_ConvertTimeFromSecsToTimeZone(ulHighTmp, ulLowTmp, &stUniversalTimeandLocalTimeZone);
    if (VOS_OK != ulRslt)
    {
        return VOS_ERR;
    }

    /* 当前的系统时间大于等于2100年时，为非法值，目前该算法暂不支持大于等于2100的时间转换 */
    if (stUniversalTimeandLocalTimeZone.usYear >= TAF_STD_TIME_ZONE_MAX_YEAR)
    {
        return VOS_ERR;
    }
    pstTimezoneCTime->ucYear   = (VOS_UINT8)(stUniversalTimeandLocalTimeZone.usYear % 100);
    pstTimezoneCTime->ucMonth  = (VOS_UINT8)stUniversalTimeandLocalTimeZone.usMonth;
    pstTimezoneCTime->ucDay    = (VOS_UINT8)stUniversalTimeandLocalTimeZone.usDay;
    pstTimezoneCTime->ucHour   = (VOS_UINT8)stUniversalTimeandLocalTimeZone.usHour;
    pstTimezoneCTime->ucMinute = (VOS_UINT8)stUniversalTimeandLocalTimeZone.usMinute;
    pstTimezoneCTime->ucSecond = (VOS_UINT8)stUniversalTimeandLocalTimeZone.usSecond;

    /*
    LTM_OFF - Offset of local time from System Time.
    The base station shall set this field to the two抯 complement
    offset of local time from System Time, in units of 30 minutes.
    The local time of day, in units of 80 ms, as of four Sync
    Channel superframes (320 ms) after the end of the last
    superframe containing any part of this Sync Channel Message,
    minus the pilot PN sequence offset, is equal to SYS_TIME -
    (LP_SEC*12.5) + (LTM_OFF *22500).
     */
    /* 全球UTC偏移量的取值范围为UTC-12:00,到 UTC+14:00,单位:60分钟，详见维基百科的时区条目 */
    if (!((pstSysTime->cLtmOff >= TAF_MMA_TIME_ZONE_MIN) && (pstSysTime->cLtmOff <= TAF_MMA_TIME_ZONE_MAX)))
    {
        return VOS_ERR;
    }
    else
    {
        pstTimezoneCTime->cTimeZone = pstSysTime->cLtmOff;
    }

    pstTimezoneCTime->ucDayltSavings = pstSysTime->ucDaylt;

    return VOS_OK;
}
/*****************************************************************************
 函 数 名  : TAF_MMA_ProcessCSystemTime
 功能描述  : Process system time
 输入参数  : XSD_MMA_1X_SYS_TIME_STRU *pstSysTime

 输出参数  : 无ta
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月26日
    作    者   : x00314862
    修改内容   :
*****************************************************************************/
VOS_VOID TAF_MMA_ProcessCSystemTime(NAS_MSCC_PIF_1X_SYS_TIME_STRU *pstSysTime)
{
    TAF_MMA_TIME_ZONE_CTIME_STRU        stTimezoneCTime;
    TAF_SDC_CURC_RPT_CTRL_STRU         *pstCurcRptCtrl;
    VOS_UINT32                          ulRlst;

    pstCurcRptCtrl  = TAF_SDC_GetCurcRptCtrl();

    /* ^CTIME at command controlled by CURC */
    if (VOS_TRUE != TAF_SDC_CheckRptCmdStatus(pstCurcRptCtrl->aucRptCfg, TAF_SDC_CMD_RPT_CTRL_BY_CURC, TAF_SDC_RPT_CMD_CTIME))
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_ProcessCSystemTime: TAF_SDC_CheckRptCmdStatus Failed");
        return;
    }

    /* fill the structure of TimeZoneCTime */
    PS_MEM_SET(&stTimezoneCTime, 0x00, sizeof(TAF_MMA_TIME_ZONE_CTIME_STRU));
    ulRlst = TAF_MMA_FillCTimeIndStru(pstSysTime, &stTimezoneCTime);
    if (VOS_OK != ulRlst)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_ProcessCSystemTime: TAF_MMA_FillCTimeIndStru Failed");

        /* 获取时区信息失败时候，以80/01/06,00:00:00,+0,00上报 */
        stTimezoneCTime.ucYear          = 80;
        stTimezoneCTime.ucMonth         = 1;
        stTimezoneCTime.ucDay           = 6;
        stTimezoneCTime.ucHour          = 0;
        stTimezoneCTime.ucMinute        = 0;
        stTimezoneCTime.ucSecond        = 0;
        stTimezoneCTime.cTimeZone       = 0;
        stTimezoneCTime.ucDayltSavings  = 0;
    }

    /* send CTime */
    ulRlst = TAF_MMA_SndCTimeInd(&stTimezoneCTime);
    if (VOS_OK != ulRlst)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_ProcessCSystemTime: TAF_MMA_SndCTimeInd Failed");
        return;
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_Snd1xChanSetCnf
 功能描述  : MMA向AT发送channel设置的结果
 输入参数  : TAF_MMA_1XCHAN_SET_REQ_STRU *pstCFreqLockSetReq
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年05月18日
    作    者   : z00316370
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_Snd1xChanSetCnf(
    TAF_MMA_CFREQ_LOCK_SET_REQ_STRU    *pstCFreqLockSetReq,
    VOS_UINT32                          ulRslt
)
{
    TAF_MMA_CFREQ_LOCK_SET_CNF_STRU    *pstCFreqLockSetCnf    = VOS_NULL_PTR;

    pstCFreqLockSetCnf =
            (TAF_MMA_CFREQ_LOCK_SET_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MMA,
                                                                        sizeof(TAF_MMA_CFREQ_LOCK_SET_CNF_STRU));
    if (VOS_NULL_PTR == pstCFreqLockSetCnf)
    {
        MMA_ERRORLOG("TAF_MMA_Snd1xChanSetCnf: ERROR:ALLOC MEMORY FAIL.");
        return;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstCFreqLockSetCnf + VOS_MSG_HEAD_LENGTH),
               0x00,
               (sizeof(TAF_MMA_CFREQ_LOCK_SET_CNF_STRU) - VOS_MSG_HEAD_LENGTH));

    /* 填写消息头部信息 */
    pstCFreqLockSetCnf->ulReceiverPid          = pstCFreqLockSetReq->ulModuleId;
    pstCFreqLockSetCnf->ulMsgName              = ID_TAF_MMA_1XCHAN_SET_CNF;
    pstCFreqLockSetCnf->stCtrl.ulModuleId      = pstCFreqLockSetReq->ulModuleId;
    pstCFreqLockSetCnf->stCtrl.usClientId      = pstCFreqLockSetReq->usClientId;
    pstCFreqLockSetCnf->stCtrl.ucOpId          = pstCFreqLockSetReq->ucOpId;
    pstCFreqLockSetCnf->ulRslt                 = ulRslt;

    /* 发送消息 */
    PS_SEND_MSG(WUEPS_PID_MMA, pstCFreqLockSetCnf);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_SndGetStaQryCnf
 功能描述  : 给AT发送ID_TAF_MMA_CDMACSQ_SET_CNF
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年05月22日
    作    者   : z00316370
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_MMA_SndGetStaQryCnf(
    TAF_MMA_CTRL_STRU                                      *pstCtrl,
    TAF_MMA_HANDSET_STATE_STRU                             *pstHandsetSta,
    TAF_MMA_APP_OPER_RESULT_ENUM_UINT32                     enRslt
)
{
    TAF_MMA_STATE_QUERY_CNF_STRU       *pstStateCnf   = VOS_NULL_PTR;

    /* 申请消息包TAF_MMA_CDMACSQ_SET_CNF_STRU */
    pstStateCnf = (TAF_MMA_STATE_QUERY_CNF_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                           WUEPS_PID_MMA,
                                           sizeof(TAF_MMA_STATE_QUERY_CNF_STRU));

    /* 内存申请失败，返回 */
    if (VOS_NULL_PTR == pstStateCnf)
    {
        MMA_ERRORLOG("TAF_MMA_SndGetStaQryCnf: ERROR:ALLOC MEMORY FAIL.");
        return;
    }

    PS_MEM_SET( (VOS_INT8 *)pstStateCnf + VOS_MSG_HEAD_LENGTH, 0X00,
            sizeof(TAF_MMA_STATE_QUERY_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 根据输入参数填充TAF_MMA_STATE_QUERY_CNF_STRU */
    pstStateCnf->ulSenderPid       = WUEPS_PID_MMA;
    pstStateCnf->ulReceiverPid     = pstCtrl->ulModuleId;
    pstStateCnf->ulMsgName         = ID_TAF_MMA_GETSTA_QUERY_CNF;

    pstStateCnf->stAtAppCtrl.usClientId         = pstCtrl->usClientId;
    pstStateCnf->stAtAppCtrl.ucOpId             = pstCtrl->ucOpId;
    pstStateCnf->ulRslt                         = enRslt;

    if (VOS_NULL_PTR != pstHandsetSta)
    {
        PS_MEM_CPY(&(pstStateCnf->stHandsetSta),
                   pstHandsetSta,
                   sizeof(TAF_MMA_HANDSET_STATE_STRU));
    }

    /* 发送消息 */
    PS_SEND_MSG(WUEPS_PID_MMA, pstStateCnf);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_SndCHVerQryCnf
 功能描述  : 给AT发送ID_TAF_MMA_CDMACSQ_SET_CNF
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年05月22日
    作    者   : z00316370
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_MMA_SndCHVerQryCnf(
    TAF_MMA_CTRL_STRU                                      *pstCtrl,
    TAF_MMA_1X_CAS_P_REV_ENUM_UINT8                         enHighRev,
    TAF_MMA_APP_OPER_RESULT_ENUM_UINT32                     enRslt
)
{
    TAF_MMA_CHIGHVER_QUERY_CNF_STRU    *pstCHVerCnf   = VOS_NULL_PTR;

    /* 申请消息包TAF_MMA_CDMACSQ_SET_CNF_STRU */
    pstCHVerCnf = (TAF_MMA_CHIGHVER_QUERY_CNF_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                           WUEPS_PID_MMA,
                                           sizeof(TAF_MMA_CHIGHVER_QUERY_CNF_STRU));

    /* 内存申请失败，返回 */
    if (VOS_NULL_PTR == pstCHVerCnf)
    {
        MMA_ERRORLOG("TAF_MMA_SndCHVerQryCnf: ERROR:ALLOC MEMORY FAIL.");
        return;
    }

    PS_MEM_SET( (VOS_INT8 *)pstCHVerCnf + VOS_MSG_HEAD_LENGTH, 0X00,
            sizeof(TAF_MMA_CHIGHVER_QUERY_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 根据输入参数填充TAF_MMA_CHIGHVER_QUERY_CNF_STRU */
    pstCHVerCnf->ulSenderPid       = WUEPS_PID_MMA;
    pstCHVerCnf->ulReceiverPid     = pstCtrl->ulModuleId;
    pstCHVerCnf->ulMsgName         = ID_TAF_MMA_CHIGHVER_QUERY_CNF;

    pstCHVerCnf->stAtAppCtrl.usClientId        = pstCtrl->usClientId;
    pstCHVerCnf->stAtAppCtrl.ucOpId            = pstCtrl->ucOpId;
    pstCHVerCnf->enHighRev                     = enHighRev;
    pstCHVerCnf->ulRslt                        = enRslt;

    /* 发送消息 */
    PS_SEND_MSG(WUEPS_PID_MMA, pstCHVerCnf);

    return;

}

/*****************************************************************************
 函 数 名  : TAF_MMA_SndQuitCallBackCnf
 功能描述  : 通知app退出callback模式的结果
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月10日
    作    者   : y00322978
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_SndQuitCallBackCnf(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCode
)
{

    TAF_MMA_QUIT_CALLBACK_SET_CNF_STRU *pstSndMsg = VOS_NULL_PTR;

    /* 申请内存  */
    pstSndMsg = (TAF_MMA_QUIT_CALLBACK_SET_CNF_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMA,
                           sizeof(TAF_MMA_QUIT_CALLBACK_SET_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if ( VOS_NULL_PTR == pstSndMsg )
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndQuitCallBackCnf:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstSndMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(TAF_MMA_QUIT_CALLBACK_SET_CNF_STRU) - VOS_MSG_HEAD_LENGTH);


    /* 根据输入参数填充TAF_MMA_CDMACSQ_SET_CNF_STRU */
    pstSndMsg->ulSenderPid       = WUEPS_PID_MMA;
    pstSndMsg->ulReceiverPid     = WUEPS_PID_AT;
    pstSndMsg->ulMsgName         = ID_TAF_MMA_QUIT_CALLBACK_SET_CNF;
    pstSndMsg->enErrorCode       = enErrorCode;

    PS_MEM_CPY(&(pstSndMsg->stCtrl), pstCtrl, sizeof(TAF_MMA_CTRL_STRU));

    /* 调用VOS发送原语 */
    PS_SEND_MSG( WUEPS_PID_MMA, pstSndMsg );

}

/*****************************************************************************
 函 数 名  : TAF_MMA_SndSetCSidListCnf
 功能描述  : set csidlist 消息 发给mma的发送函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月13日
    作    者   : y00322978
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_SndSetCSidListCnf(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCode
)
{
    TAF_MMA_CSIDLIST_SET_CNF_STRU      *pstSndMsg = VOS_NULL_PTR;

    /* 申请内存  */
    pstSndMsg = (TAF_MMA_CSIDLIST_SET_CNF_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMA,
                           sizeof(TAF_MMA_CSIDLIST_SET_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if ( VOS_NULL_PTR == pstSndMsg )
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndQuitCallBackCnf:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstSndMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(TAF_MMA_CSIDLIST_SET_CNF_STRU) - VOS_MSG_HEAD_LENGTH);


    /* 根据输入参数填充TAF_MMA_CDMACSQ_SET_CNF_STRU */
    pstSndMsg->ulSenderPid       = WUEPS_PID_MMA;
    pstSndMsg->ulReceiverPid     = WUEPS_PID_AT;
    pstSndMsg->ulMsgName         = ID_TAF_MMA_CSIDLIST_SET_CNF;
    pstSndMsg->enErrorCode       = enErrorCode;

    PS_MEM_CPY(&(pstSndMsg->stCtrl), pstCtrl, sizeof(TAF_MMA_CTRL_STRU));

    /* 调用VOS发送原语 */
    PS_SEND_MSG( WUEPS_PID_MMA, pstSndMsg );
}


/*****************************************************************************
 函 数 名  : TAF_MMA_SndCdmaCsqSetCnf
 功能描述  : 给AT发送ID_TAF_MMA_CDMACSQ_SET_CNF
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月21日
    作    者   : c00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_MMA_SndHdrCsqSetCnf(
    TAF_MMA_CTRL_STRU                                      *pstCtrl,
    TAF_MMA_APP_OPER_RESULT_ENUM_UINT32                     enRslt
)
{
    MMA_TAF_HDR_CSQ_SET_CNF_STRU            *pstHdrCsqCnf   = VOS_NULL_PTR;

    /* 申请消息包TAF_MMA_HDRCSQ_SET_CNF_STRU */
    pstHdrCsqCnf = (MMA_TAF_HDR_CSQ_SET_CNF_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                           WUEPS_PID_MMA,
                                           sizeof(MMA_TAF_HDR_CSQ_SET_CNF_STRU));

    /* 内存申请失败，返回 */
    if (VOS_NULL_PTR == pstHdrCsqCnf)
    {
        return;
    }

    PS_MEM_SET( (VOS_INT8 *)pstHdrCsqCnf + VOS_MSG_HEAD_LENGTH, 0X00,
            sizeof(MMA_TAF_HDR_CSQ_SET_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 根据输入参数填充TAF_MMA_CDMACSQ_SET_CNF_STRU */
    pstHdrCsqCnf->ulSenderPid       = WUEPS_PID_MMA;
    pstHdrCsqCnf->ulReceiverPid     = pstCtrl->ulModuleId;
    pstHdrCsqCnf->ulMsgName         = ID_MMA_TAF_HDR_CSQ_SET_CNF;

    PS_MEM_CPY(&pstHdrCsqCnf->stCtrl, pstCtrl, sizeof(TAF_MMA_CTRL_STRU));
    pstHdrCsqCnf->enRslt            = enRslt;

    /* 发送消息 */
    PS_SEND_MSG(WUEPS_PID_MMA, pstHdrCsqCnf);

    return;

}

/*****************************************************************************
 函 数 名  : TAF_MMA_SndHdrCsqInd
 功能描述  : 给AT发送ID_TAF_MMA_HDR_CSQ_IND
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月21日
    作    者   : c00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_MMA_SndHdrCsqInd(
    VOS_INT16                           sHdrRssi,
    VOS_INT16                           sHdrSnr,
    VOS_INT16                           sHdrEcio
)
{
    MMA_TAF_HDR_CSQ_VALUE_IND_STRU     *pstHdrCsqInd   = VOS_NULL_PTR;

    /* 申请消息包TAF_MMA_HDRCSQ_SET_CNF_STRU */
    pstHdrCsqInd = (MMA_TAF_HDR_CSQ_VALUE_IND_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                           WUEPS_PID_MMA,
                                           sizeof(MMA_TAF_HDR_CSQ_VALUE_IND_STRU));

    /* 内存申请失败，返回 */
    if (VOS_NULL_PTR == pstHdrCsqInd)
    {
        return;
    }

    PS_MEM_SET( (VOS_INT8 *)pstHdrCsqInd + VOS_MSG_HEAD_LENGTH, 0X00,
            sizeof(MMA_TAF_HDR_CSQ_VALUE_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 根据输入参数填充TAF_MMA_CDMACSQ_SET_CNF_STRU */
    pstHdrCsqInd->ulReceiverPid         = WUEPS_PID_AT;
    pstHdrCsqInd->stCtrl.usClientId     = MN_GetRealClientId(MMA_CLIENTID_BROADCAST, WUEPS_PID_MMA);

    pstHdrCsqInd->ulMsgName             = ID_MMA_TAF_HDR_CSQ_VALUE_IND;

    pstHdrCsqInd->sHdrRssi              = sHdrRssi;
    pstHdrCsqInd->sHdrSnr               = sHdrSnr;
    pstHdrCsqInd->sHdrEcio              = sHdrEcio;

    /* 发送消息 */
    PS_SEND_MSG(WUEPS_PID_MMA, pstHdrCsqInd);

    return;

}




/*****************************************************************************
 函 数 名  : TAF_MMA_SndCLModeInd
 功能描述  : 给AT发送ID_TAF_MMA_CLMODE_IND
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :


 修改历史      :
  1.日    期   : 2015年10月22日
    作    者   : f00279542
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_MMA_SndCLModeInd(VOS_VOID)
{
    TAF_MMA_CLMODE_IND_STRU            *pstCLModeInd = VOS_NULL_PTR;

    /* 申请消息包TAF_MMA_CLMODE_IND_STRU */
    pstCLModeInd = (TAF_MMA_CLMODE_IND_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                           WUEPS_PID_MMA,
                                           sizeof(TAF_MMA_CLMODE_IND_STRU));

    /* 内存申请失败，返回 */
    if (VOS_NULL_PTR == pstCLModeInd)
    {
        return;
    }

    PS_MEM_SET( (VOS_INT8 *)pstCLModeInd + VOS_MSG_HEAD_LENGTH, 0X00,
            sizeof(TAF_MMA_CLMODE_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填写消息头部信息 */
    pstCLModeInd->ulReceiverPid = WUEPS_PID_AT;
    pstCLModeInd->ulMsgName     = ID_TAF_MMA_CLMODE_IND;
    pstCLModeInd->usClientId    = MN_GetRealClientId(MMA_CLIENTID_BROADCAST, WUEPS_PID_MMA);
    pstCLModeInd->ucOpid        = MMA_OP_ID_INTERNAL;

    if (VOS_TRUE == TAF_SDC_IsConfigCLMode())
    {
        pstCLModeInd->ucIsCLMode = VOS_TRUE;
    }
    else
    {
        pstCLModeInd->ucIsCLMode = VOS_FALSE;
    }

    /* 发送消息 */
    PS_SEND_MSG(WUEPS_PID_MMA, pstCLModeInd);

    return;
}

#endif
/*****************************************************************************
 函 数 名  : TAF_MMA_BuildRssiInd
 功能描述  : 构造RSSIIND消息上报给AT
 输入参数  : TAF_PHONE_EVENT_INFO_STRU  上报给AT的事件
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月16日
    作    者   : s00217060
    修改内容   : 新增函数

  2.日    期   : 2015年3月31日
    作    者   : g00261581
    修改内容   : 消息结构重构
  3.日    期   : 2015年10月8日
    作    者   : l00324781
    修改内容   : Iteration 18 ,CL模服务状态显示优化
*****************************************************************************/
VOS_VOID TAF_MMA_BuildRssiInd(
    TAF_MMA_RSSI_INFO_IND_STRU         *pstRssiInd
)
{
    TAF_SDC_APPNETWORK_INFO            *pstAppNwInfo              = VOS_NULL_PTR;
    TAF_SDC_SYS_MODE_ENUM_UINT8         enAppSysMode;
    TAF_SDC_CURC_RPT_CTRL_STRU         *pstCurcRptCtrl           = VOS_NULL_PTR;
    TAF_SDC_UNSOLICITED_RPT_CTRL_STRU  *pstUnsolicitedRptCtrl    = VOS_NULL_PTR;

    pstCurcRptCtrl          = TAF_SDC_GetCurcRptCtrl();
    pstUnsolicitedRptCtrl   = TAF_SDC_GetUnsolicitedRptCtrl();

    /* 增加主动上报相关全局变量的值 */
    PS_MEM_CPY(pstRssiInd->aucCurcRptCfg, pstCurcRptCtrl->aucRptCfg, TAF_MMA_RPT_CFG_MAX_SIZE);
    PS_MEM_CPY(pstRssiInd->aucUnsolicitedRptCfg, pstUnsolicitedRptCtrl->aucRptCfg, TAF_MMA_RPT_CFG_MAX_SIZE);

    pstAppNwInfo  = TAF_SDC_GetAppNetworkInfo();
    enAppSysMode  = TAF_SDC_GetAppSysMode();

    /*仅做上报一个小区的相关信息*/
    pstRssiInd->stRssiInfo.ucRssiNum = 1;
    pstRssiInd->stRssiInfo.enRatType              = TAF_SDC_GetAppSysMode();
    pstRssiInd->stRssiInfo.ucCurrentUtranMode     = TAF_SDC_GetAppUtranMode();
    pstRssiInd->stRssiInfo.aRssi[0].ucChannalQual = pstAppNwInfo->stAppSigQuaInfo.st3GppRssiInfo.ucChannalQual;

    switch(enAppSysMode)
    {
        case TAF_SDC_SYS_MODE_GSM:
             pstRssiInd->stRssiInfo.aRssi[0].u.stGCellSignInfo.sRssiValue = pstAppNwInfo->stAppSigQuaInfo.st3GppRssiInfo.u.st2GCellSignInfo.sRssiValue;

             MMA_GetRssiLevelFromValue(pstAppNwInfo->stAppSigQuaInfo.st3GppRssiInfo.u.st2GCellSignInfo.sRssiValue,
                                     &(pstRssiInd->stRssiInfo.aRssi[0].ucRssiValue));

            break;

        case TAF_SDC_SYS_MODE_WCDMA:
             pstRssiInd->stRssiInfo.aRssi[0].u.stWCellSignInfo.sRscpValue = pstAppNwInfo->stAppSigQuaInfo.st3GppRssiInfo.u.st3GCellSignInfo.sRscpValue;
             pstRssiInd->stRssiInfo.aRssi[0].u.stWCellSignInfo.sEcioValue = pstAppNwInfo->stAppSigQuaInfo.st3GppRssiInfo.u.st3GCellSignInfo.sEcioValue;

             MMA_GetRssiLevelFromValue(pstAppNwInfo->stAppSigQuaInfo.st3GppRssiInfo.u.st3GCellSignInfo.sRscpValue,
                                     &(pstRssiInd->stRssiInfo.aRssi[0].ucRssiValue));

            break;

#if (FEATURE_ON == FEATURE_LTE)
        case TAF_SDC_SYS_MODE_LTE:
        case TAF_SDC_SYS_MODE_SVLTE:
             pstRssiInd->stRssiInfo.enRatType                                  = TAF_SDC_SYS_MODE_LTE;

             pstRssiInd->stRssiInfo.aRssi[0].ucChannalQual                     = TAF_PH_BER_UNKNOWN;
             pstRssiInd->stRssiInfo.aRssi[0].u.stLCellSignInfo.sRssi           = pstAppNwInfo->stAppSigQuaInfo.st3GppRssiInfo.u.st4GCellSignInfo.sRssi;
             pstRssiInd->stRssiInfo.aRssi[0].u.stLCellSignInfo.sRsd            = pstAppNwInfo->stAppSigQuaInfo.st3GppRssiInfo.u.st4GCellSignInfo.sRsd;
             pstRssiInd->stRssiInfo.aRssi[0].u.stLCellSignInfo.sRsrp           = pstAppNwInfo->stAppSigQuaInfo.st3GppRssiInfo.u.st4GCellSignInfo.sRsrp;
             pstRssiInd->stRssiInfo.aRssi[0].u.stLCellSignInfo.sRsrq           = pstAppNwInfo->stAppSigQuaInfo.st3GppRssiInfo.u.st4GCellSignInfo.sRsrq;
             pstRssiInd->stRssiInfo.aRssi[0].u.stLCellSignInfo.lSINR           = pstAppNwInfo->stAppSigQuaInfo.st3GppRssiInfo.u.st4GCellSignInfo.lSINR;
             pstRssiInd->stRssiInfo.aRssi[0].u.stLCellSignInfo.stCQI.usRI      = pstAppNwInfo->stAppSigQuaInfo.st3GppRssiInfo.u.st4GCellSignInfo.stCQI.usRI;
             pstRssiInd->stRssiInfo.aRssi[0].u.stLCellSignInfo.stCQI.ausCQI[0] = pstAppNwInfo->stAppSigQuaInfo.st3GppRssiInfo.u.st4GCellSignInfo.stCQI.ausCQI[0];
             pstRssiInd->stRssiInfo.aRssi[0].u.stLCellSignInfo.stCQI.ausCQI[1] = pstAppNwInfo->stAppSigQuaInfo.st3GppRssiInfo.u.st4GCellSignInfo.stCQI.ausCQI[1];

             TAF_MMA_GetRssiLevelFromLteRssi(pstAppNwInfo->stAppSigQuaInfo.st3GppRssiInfo.u.st4GCellSignInfo.sRssi,
                                           &(pstRssiInd->stRssiInfo.aRssi[0].ucRssiValue));

            break;
#endif
        default:
            MMA_ERRORLOG("TAF_MMA_BuildRssiInd:RAT is INVALID.");
            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_SndAtRssiInd
 功能描述  : 上报RSSIIND消息上报给AT
 输入参数  : TAF_PHONE_EVENT_INFO_STRU  上报给AT的事件
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月16日
    作    者   : s00217060
    修改内容   : 新增函数

*****************************************************************************/
VOS_VOID TAF_MMA_SndAtRssiInd(VOS_VOID)
{
    TAF_MMA_RSSI_INFO_IND_STRU          *pstRssiInd;

    if (VOS_TRUE != TAF_MMA_IsRssiChangeNeedRpt())
    {
        return;
    }

    pstRssiInd = (TAF_MMA_RSSI_INFO_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MMA,
                                                                            sizeof(TAF_MMA_RSSI_INFO_IND_STRU));

    if (VOS_NULL_PTR == pstRssiInd)
    {
        MMA_ERRORLOG("TAF_MMA_SndAtRssiInd:ERROR:ALLOC MEMORY FAIL.");
        return;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstRssiInd + VOS_MSG_HEAD_LENGTH),
               0x00,
               (sizeof(TAF_MMA_RSSI_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH));

    /* 填写消息头部信息 */
    pstRssiInd->ulReceiverPid             = WUEPS_PID_AT;
    pstRssiInd->ulMsgName                 = ID_TAF_MMA_RSSI_INFO_IND;
    pstRssiInd->usClientId                = MN_GetRealClientId(MMA_CLIENTID_BROADCAST, WUEPS_PID_MMA);
    pstRssiInd->ucOpId                    = MMA_OP_ID_INTERNAL;

    TAF_MMA_BuildRssiInd(pstRssiInd);

    /* 发送消息 */
    PS_SEND_MSG(WUEPS_PID_MMA, pstRssiInd);

    return;
}
/*lint +e429*/



#if (FEATURE_ON == FEATURE_IMS)
/*****************************************************************************
 函 数 名  : TAF_MMA_SndImsSwitchSetCnf
 功能描述  : 发送IMS开关设置结果通知APP
 输入参数  : pstCtrl       ---  控制结构
             enResult      ---  设置结果
             usErrorCause  ---  失败原因
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年02月04日
    作    者   : f00179208
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_MMA_SndImsSwitchSetCnf(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    TAF_MMA_APP_OPER_RESULT_ENUM_UINT32 enResult,
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCause
)
{
    TAF_MMA_IMS_SWITCH_SET_CNF_STRU    *pstSndMsg   = VOS_NULL_PTR;
    VOS_UINT32                          ulRst;

    pstSndMsg = (TAF_MMA_IMS_SWITCH_SET_CNF_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                             WUEPS_PID_MMA,
                                             sizeof(TAF_MMA_IMS_SWITCH_SET_CNF_STRU));
    if (VOS_NULL_PTR == pstSndMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndImsSwitchSetCnf:Alloc Msg Failed");

        return;
    }

    PS_MEM_SET((VOS_INT8 *)pstSndMsg + VOS_MSG_HEAD_LENGTH, 0,
               sizeof(TAF_MMA_IMS_SWITCH_SET_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstSndMsg->ulSenderCpuId            = VOS_LOCAL_CPUID;
    pstSndMsg->ulSenderPid              = WUEPS_PID_MMA;
    pstSndMsg->ulReceiverCpuId          = VOS_LOCAL_CPUID;
    pstSndMsg->ulReceiverPid            = pstCtrl->ulModuleId;
    pstSndMsg->ulMsgName                = ID_TAF_MMA_IMS_SWITCH_SET_CNF;
    pstSndMsg->usClientId               = pstCtrl->usClientId;
    pstSndMsg->ucOpid                   = pstCtrl->ucOpId;
    pstSndMsg->enResult                 = enResult;
    pstSndMsg->enErrorCause             = enErrorCause;

    ulRst = PS_SEND_MSG(WUEPS_PID_MMA, pstSndMsg);
    if (VOS_OK != ulRst)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndImsSwitchSetCnf:Send Msg Failed");
    }

    return;
}


/*****************************************************************************
 函 数 名  : TAF_MMA_SndImsSwitchQryCnf
 功能描述  : 发送IMS开关状态查询结果通知APP
 输入参数  : pstCtrl
             ucImsSwitch
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年02月04日
    作    者   : f00179208
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_MMA_SndImsSwitchQryCnf(
    TAF_MMA_CTRL_STRU                          *pstCtrl,
    VOS_UINT8                                   ucImsSwitch
)
{
    TAF_MMA_IMS_SWITCH_QRY_CNF_STRU    *pstSndMsg   = VOS_NULL_PTR;
    VOS_UINT32                          ulRst;

    pstSndMsg = (TAF_MMA_IMS_SWITCH_QRY_CNF_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                             WUEPS_PID_MMA,
                                             sizeof(TAF_MMA_IMS_SWITCH_QRY_CNF_STRU));
    if (VOS_NULL_PTR == pstSndMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndImsSwitchQryCnf:Alloc Msg Failed");

        return;
    }

    PS_MEM_SET((VOS_INT8 *)pstSndMsg + VOS_MSG_HEAD_LENGTH, 0,
               sizeof(TAF_MMA_IMS_SWITCH_QRY_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstSndMsg->ulSenderCpuId            = VOS_LOCAL_CPUID;
    pstSndMsg->ulSenderPid              = WUEPS_PID_MMA;
    pstSndMsg->ulReceiverCpuId          = VOS_LOCAL_CPUID;
    pstSndMsg->ulReceiverPid            = pstCtrl->ulModuleId;
    pstSndMsg->ulMsgName                = ID_TAF_MMA_IMS_SWITCH_QRY_CNF;
    pstSndMsg->usClientId               = pstCtrl->usClientId;
    pstSndMsg->ucOpid                   = pstCtrl->ucOpId;
    pstSndMsg->enImsSwitch              = ucImsSwitch;

    ulRst = PS_SEND_MSG(WUEPS_PID_MMA, pstSndMsg);
    if (VOS_OK != ulRst)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndImsSwitchSetCnf:Send Msg Failed");

        return;
    }

    return;
}
#endif

/*****************************************************************************
 函 数 名  : TAF_MMA_SndVoiceDomainSetCnf
 功能描述  : 发送语音优选域设置结果通知APP
 输入参数  : pstCtrl       ---  控制结构
             enResult      ---  设置结果
             usErrorCause  ---  失败原因
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年02月04日
    作    者   : f00179208
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_MMA_SndVoiceDomainSetCnf(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    TAF_MMA_APP_OPER_RESULT_ENUM_UINT32 enResult,
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCause
)
{
    TAF_MMA_VOICE_DOMAIN_SET_CNF_STRU  *pstSndMsg   = VOS_NULL_PTR;
    VOS_UINT32                          ulRst;

    pstSndMsg = (TAF_MMA_VOICE_DOMAIN_SET_CNF_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                             WUEPS_PID_MMA,
                                             sizeof(TAF_MMA_VOICE_DOMAIN_SET_CNF_STRU));
    if (VOS_NULL_PTR == pstSndMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndVoiceDomainSetCnf:Alloc Msg Failed");

        return;
    }

    PS_MEM_SET((VOS_INT8 *)pstSndMsg + VOS_MSG_HEAD_LENGTH, 0,
               sizeof(TAF_MMA_VOICE_DOMAIN_SET_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstSndMsg->ulSenderCpuId            = VOS_LOCAL_CPUID;
    pstSndMsg->ulSenderPid              = WUEPS_PID_MMA;
    pstSndMsg->ulReceiverCpuId          = VOS_LOCAL_CPUID;
    pstSndMsg->ulReceiverPid            = pstCtrl->ulModuleId;
    pstSndMsg->ulMsgName                = ID_TAF_MMA_VOICE_DOMAIN_SET_CNF;
    pstSndMsg->usClientId               = pstCtrl->usClientId;
    pstSndMsg->ucOpid                   = pstCtrl->ucOpId;
    pstSndMsg->enResult                 = enResult;
    pstSndMsg->enErrorCause             = enErrorCause;

    ulRst = PS_SEND_MSG(WUEPS_PID_MMA, pstSndMsg);
    if (VOS_OK != ulRst)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndVoiceDomainSetCnf:Send Msg Failed");

        return;
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_SndVoiceDomainQryCnf
 功能描述  : 发送语音优选域查询结果通知APP
 输入参数  : pstCtrl
             enVoiceDomain
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年02月04日
    作    者   : f00179208
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_MMA_SndVoiceDomainQryCnf(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    TAF_MMA_VOICE_DOMAIN_ENUM_UINT32    enVoiceDomain
)
{
    TAF_MMA_VOICE_DOMAIN_QRY_CNF_STRU  *pstSndMsg   = VOS_NULL_PTR;
    VOS_UINT32                          ulRst;

    pstSndMsg = (TAF_MMA_VOICE_DOMAIN_QRY_CNF_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                             WUEPS_PID_MMA,
                                             sizeof(TAF_MMA_VOICE_DOMAIN_QRY_CNF_STRU));
    if (VOS_NULL_PTR == pstSndMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndVoiceDomainQryCnf:Alloc Msg Failed");

        return;
    }

    PS_MEM_SET((VOS_INT8 *)pstSndMsg + VOS_MSG_HEAD_LENGTH, 0,
               sizeof(TAF_MMA_VOICE_DOMAIN_QRY_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstSndMsg->ulSenderCpuId            = VOS_LOCAL_CPUID;
    pstSndMsg->ulSenderPid              = WUEPS_PID_MMA;
    pstSndMsg->ulReceiverCpuId          = VOS_LOCAL_CPUID;
    pstSndMsg->ulReceiverPid            = pstCtrl->ulModuleId;
    pstSndMsg->ulMsgName                = ID_TAF_MMA_VOICE_DOMAIN_QRY_CNF;
    pstSndMsg->usClientId               = pstCtrl->usClientId;
    pstSndMsg->ucOpid                   = pstCtrl->ucOpId;
    pstSndMsg->enVoiceDomain            = enVoiceDomain;

    ulRst = PS_SEND_MSG(WUEPS_PID_MMA, pstSndMsg);
    if (VOS_OK != ulRst)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndVoiceDomainQryCnf:Send Msg Failed");

        return;
    }

    return;
}


/*****************************************************************************
 函 数 名  : TAF_MMA_SndCFPlmnSetCnf
 功能描述  : 给AT发送ID_TAF_MMA_CFPLMN_CNF
 输入参数  : pstCtrl         :
             enRslt          : 返回的结果
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :


 修改历史      :
  1.日    期   : 2015年2月7日
    作    者   : f00279542
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_MMA_SndCFPlmnSetCnf(
    TAF_MMA_CTRL_STRU                                      *pstCtrl,
    TAF_MMA_APP_CFPLMN_OPER_RESULT_ENUM_UINT32              enRslt
)
{
    TAF_MMA_CFPLMN_SET_CNF_STRU        *pstSndMsg = VOS_NULL_PTR;

    pstSndMsg = (TAF_MMA_CFPLMN_SET_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                               WUEPS_PID_MMA,
                                               sizeof(TAF_MMA_CFPLMN_SET_CNF_STRU));
    if (VOS_NULL_PTR == pstSndMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA,"TAF_MMA_SndCFPlmnSetCnf:Alloc Msg Failed");
        return;
    }

    PS_MEM_SET((VOS_INT8 *)pstSndMsg + VOS_MSG_HEAD_LENGTH, 0X00,
               sizeof(TAF_MMA_CFPLMN_SET_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstSndMsg->ulSenderCpuId            = VOS_LOCAL_CPUID;
    pstSndMsg->ulSenderPid              = WUEPS_PID_MMA;
    pstSndMsg->ulReceiverCpuId          = VOS_LOCAL_CPUID;
    pstSndMsg->ulReceiverPid            = pstCtrl->ulModuleId;
    pstSndMsg->ulMsgName                = ID_TAF_MMA_CFPLMN_SET_CNF;

    PS_MEM_CPY(&pstSndMsg->stCtrl, pstCtrl, sizeof(TAF_MMA_CTRL_STRU));

    pstSndMsg->enRslt                   = enRslt;

    PS_SEND_MSG(WUEPS_PID_MMA, pstSndMsg);
    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_SndCFPlmnQueryCnf
 功能描述  : 给AT发送ID_TAF_MMA_CFPLMN_query CNF
 输入参数  : pstCtrl         :
             enRslt          : 返回的结果
             pstCFPlmnCnfMsg : 回复的消息
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :


 修改历史      :
  1.日    期   : 2015年2月7日
    作    者   : f00279542
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_MMA_SndCFPlmnQueryCnf(
    TAF_MMA_CTRL_STRU                                      *pstCtrl,
    TAF_MMA_APP_CFPLMN_OPER_RESULT_ENUM_UINT32              enRslt,
    MSCC_MMA_CFPLMN_QUERY_CNF_STRU                         *pstCFPlmnCnfMsg
)
{
    TAF_MMA_CFPLMN_QUERY_CNF_STRU      *pstSndMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulLoop;

    pstSndMsg = (TAF_MMA_CFPLMN_QUERY_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                 WUEPS_PID_MMA,
                                                 sizeof(TAF_MMA_CFPLMN_QUERY_CNF_STRU));
    if (VOS_NULL_PTR == pstSndMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA,"TAF_MMA_SndCFPlmnQueryCnf:Alloc Msg Failed");
        return;
    }

    PS_MEM_SET((VOS_INT8 *)pstSndMsg + VOS_MSG_HEAD_LENGTH, 0X00,
               sizeof(TAF_MMA_CFPLMN_QUERY_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstSndMsg->ulSenderCpuId            = VOS_LOCAL_CPUID;
    pstSndMsg->ulSenderPid              = WUEPS_PID_MMA;
    pstSndMsg->ulReceiverCpuId          = VOS_LOCAL_CPUID;
    pstSndMsg->ulReceiverPid            = pstCtrl->ulModuleId;
    pstSndMsg->ulMsgName                = ID_TAF_MMA_CFPLMN_QUERY_CNF;

    PS_MEM_CPY(&pstSndMsg->stCtrl, pstCtrl, sizeof(TAF_MMA_CTRL_STRU));

    pstSndMsg->enRslt                   = enRslt;

    if (VOS_NULL_PTR != pstCFPlmnCnfMsg)
    {
        pstSndMsg->usPlmnNum = pstCFPlmnCnfMsg->ucPlmnNum;

        if (pstSndMsg->usPlmnNum > NAS_MSCC_PIF_MAX_CFPLMN_NUM)
        {
            pstSndMsg->usPlmnNum = NAS_MSCC_PIF_MAX_CFPLMN_NUM;
        }

        for (ulLoop = 0; ulLoop < pstSndMsg->usPlmnNum; ulLoop++)
        {
            pstSndMsg->astPlmn[ulLoop].Mcc = pstCFPlmnCnfMsg->astPlmn[ulLoop].ulMcc;
            pstSndMsg->astPlmn[ulLoop].Mnc = pstCFPlmnCnfMsg->astPlmn[ulLoop].ulMnc;

            /* PLMN格式转换 */
            MMA_PlmnId2Bcd(&pstSndMsg->astPlmn[ulLoop]);
        }
    }

    PS_SEND_MSG(WUEPS_PID_MMA, pstSndMsg);
    return;
}
/*****************************************************************************
 函 数 名  : TAF_MMA_ProcPlmnAutoReselCnf
 功能描述  : 给AT发送ID_TAF_MMA_PLMN_AUTO_RESEL_CNF
 输入参数  : enRslt          : 返回的结果

 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :


 修改历史      :
  1.日    期   : 2015年3月23日
    作    者   : f00279542
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_MMA_ProcPlmnAutoReselCnf(
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCause
)
{
    TAF_MMA_OPER_CTX_STRU              *pstMmaOperCtx = VOS_NULL_PTR;
    VOS_UINT8                           ucCtxIndex;

    pstMmaOperCtx = TAF_MMA_GetOperCtxAddr();

    /* 从全局变量g_stTafMmaCtx.astMmaOperCtx查找ID_TAF_MMA_PLMN_AUTO_RESEL_REQ对应的记录项 */
    if (VOS_TRUE == TAF_MMA_GetSpecOperTypeIndex(TAF_MMA_OPER_PLMN_AUTO_RESEL_REQ, &ucCtxIndex))
    {
        /*  回复AutoReselSetCnf */
        TAF_MMA_SndPlmnAutoReselCnf(&(pstMmaOperCtx[ucCtxIndex].stCtrl), enErrorCause);

        TAF_MMA_ClearOperCtx(ucCtxIndex);
    }

    return;
}
/*****************************************************************************
 函 数 名  : TAF_MMA_SndPlmnAutoReselCnf
 功能描述  : 给AT发送ID_TAF_MMA_PLMN_AUTO_RESEL_CNF
 输入参数  : enRslt          : 返回的结果

 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :


 修改历史      :
  1.日    期   : 2015年3月23日
    作    者   : f00279542
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_MMA_SndPlmnAutoReselCnf(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCode
)
{
    TAF_MMA_PLMN_AUTO_RESEL_CNF_STRU   *pstSndMsg = VOS_NULL_PTR;

    pstSndMsg = (TAF_MMA_PLMN_AUTO_RESEL_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                    WUEPS_PID_MMA,
                                                    sizeof(TAF_MMA_PLMN_AUTO_RESEL_CNF_STRU));
    if (VOS_NULL_PTR == pstSndMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA,"TAF_MMA_SndPlmnAutoReselCnf:Alloc Msg Failed");
        return;
    }

    PS_MEM_SET((VOS_INT8 *)pstSndMsg + VOS_MSG_HEAD_LENGTH, 0X00,
               sizeof(TAF_MMA_PLMN_AUTO_RESEL_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstSndMsg->ulReceiverPid            = pstCtrl->ulModuleId;
    pstSndMsg->ulMsgName                = ID_TAF_MMA_PLMN_AUTO_RESEL_CNF;
    PS_MEM_CPY(&pstSndMsg->stCtrl, pstCtrl, sizeof(TAF_MMA_CTRL_STRU));
    pstSndMsg->enErrorCause             = enErrorCode;

    PS_SEND_MSG(WUEPS_PID_MMA, pstSndMsg);
    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_ProcPlmnSpecialSelCnf
 功能描述  : 给AT发送ID_TAF_MMA_PLMN_SPECIAL_SEL_CNF
 输入参数  : enRslt          : 返回的结果

 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :


 修改历史      :
  1.日    期   : 2015年3月23日
    作    者   : f00279542
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_MMA_ProcPlmnSpecialSelCnf(
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCause
)
{
    TAF_MMA_OPER_CTX_STRU              *pstMmaOperCtx = VOS_NULL_PTR;
    VOS_UINT8                           ucCtxIndex;

    pstMmaOperCtx = TAF_MMA_GetOperCtxAddr();

    /* 从全局变量g_stTafMmaCtx.astMmaOperCtx查找ID_TAF_MMA_PLMN_SPECIAL_SEL_REQ对应的记录项 */
    if (VOS_TRUE == TAF_MMA_GetSpecOperTypeIndex(TAF_MMA_OPER_PLMN_SPEC_SEL_REQ, &ucCtxIndex))
    {
        /*  回复plmn special sel CNF */
        TAF_MMA_SndPlmnSpecialSelCnf(&(pstMmaOperCtx[ucCtxIndex].stCtrl), enErrorCause);

        TAF_MMA_ClearOperCtx(ucCtxIndex);
    }

    return;
}
/*****************************************************************************
 函 数 名  : TAF_MMA_SndPlmnSpecialSelCnf
 功能描述  : 给AT发送ID_TAF_MMA_PLMN_SPECIAL_SEL_CNF
 输入参数  : pstCtrl         :
             enRslt          : 返回的结果
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :


 修改历史      :
  1.日    期   : 2015年3月23日
    作    者   : f00279542
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_MMA_SndPlmnSpecialSelCnf(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCode
)
{
    TAF_MMA_PLMN_SPECIAL_SEL_CNF_STRU  *pstSndMsg = VOS_NULL_PTR;

    pstSndMsg = (TAF_MMA_PLMN_SPECIAL_SEL_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                               WUEPS_PID_MMA,
                                               sizeof(TAF_MMA_PLMN_SPECIAL_SEL_CNF_STRU));
    if (VOS_NULL_PTR == pstSndMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA,"TAF_MMA_SndPlmnSpecialSelCnf:Alloc Msg Failed");
        return;
    }

    PS_MEM_SET((VOS_INT8 *)pstSndMsg + VOS_MSG_HEAD_LENGTH, 0X00,
               sizeof(TAF_MMA_PLMN_SPECIAL_SEL_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstSndMsg->ulReceiverPid            = pstCtrl->ulModuleId;
    pstSndMsg->ulMsgName                = ID_TAF_MMA_PLMN_SPECIAL_SEL_CNF;
    PS_MEM_CPY(&pstSndMsg->stCtrl, pstCtrl, sizeof(TAF_MMA_CTRL_STRU));
    pstSndMsg->enErrorCause             = enErrorCode;

    PS_SEND_MSG(WUEPS_PID_MMA, pstSndMsg);
    return;
}
#if (FEATURE_ON == FEATURE_CSG)
/*****************************************************************************
 函 数 名  : TAF_MMA_SndCsgListAbortCnf
 功能描述  : 给AT发送csg list Abort cnf
 输入参数  : pstCtrl         : 控制信息
             enRslt          : 返回的结果
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :


 修改历史      :
  1.日    期   : 2015年9月21日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_VOID TAF_MMA_SndCsgListAbortCnf(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCode
)
{
    TAF_MMA_CSG_LIST_ABORT_CNF_STRU    *pstSndMsg = VOS_NULL_PTR;

    pstSndMsg = (TAF_MMA_CSG_LIST_ABORT_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                               WUEPS_PID_MMA,
                                               sizeof(TAF_MMA_CSG_LIST_ABORT_CNF_STRU));
    if (VOS_NULL_PTR == pstSndMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA,"TAF_MMA_SndCsgListAbortCnf:Alloc Msg Failed");
        return;
    }

    PS_MEM_SET((VOS_INT8 *)pstSndMsg + VOS_MSG_HEAD_LENGTH, 0X00,
               sizeof(TAF_MMA_CSG_LIST_ABORT_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstSndMsg->ulSenderCpuId            = VOS_LOCAL_CPUID;
    pstSndMsg->ulSenderPid              = WUEPS_PID_MMA;
    pstSndMsg->ulReceiverCpuId          = VOS_LOCAL_CPUID;
    pstSndMsg->ulReceiverPid            = pstCtrl->ulModuleId;
    pstSndMsg->enMsgName                = ID_TAF_MMA_CSG_LIST_ABORT_CNF;
    PS_MEM_CPY(&pstSndMsg->stCtrl, pstCtrl, sizeof(TAF_MMA_CTRL_STRU));
    pstSndMsg->enErrorCause             = enErrorCode;

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_MMA, pstSndMsg))
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA,"TAF_MMA_SndCsgListAbortCnf:Send Msg Failed");
    }
    return;
}


/*****************************************************************************
 函 数 名  : TAF_MMA_SndCsgListSearchCnf
 功能描述  : 给AT发送列表搜结果
 输入参数  : pstCtrl            - 接收模块信息
             pstPlmnListCnfPara - csg list搜网结果
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月28日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增

*****************************************************************************/
VOS_VOID TAF_MMA_SndCsgListSearchCnf(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    TAF_MMA_CSG_LIST_CNF_PARA_STRU     *pstPlmnListCnfPara
)
{
    TAF_MMA_CSG_LIST_SEARCH_CNF_STRU   *pstSndMsg   = VOS_NULL_PTR;
    VOS_UINT32                          ulRst;

    pstSndMsg = (TAF_MMA_CSG_LIST_SEARCH_CNF_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                             WUEPS_PID_MMA,
                                             sizeof(TAF_MMA_CSG_LIST_SEARCH_CNF_STRU));
    if (VOS_NULL_PTR == pstSndMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA,"TAF_MMA_SndCsgListSearchCnf:Alloc Msg Failed");
        return;
    }

    PS_MEM_SET( (VOS_INT8 *)pstSndMsg + VOS_MSG_HEAD_LENGTH, 0X00,
            sizeof(TAF_MMA_CSG_LIST_SEARCH_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstSndMsg->ulSenderCpuId            = VOS_LOCAL_CPUID;
    pstSndMsg->ulSenderPid              = WUEPS_PID_MMA;
    pstSndMsg->ulReceiverCpuId          = VOS_LOCAL_CPUID;
    pstSndMsg->ulReceiverPid            = pstCtrl->ulModuleId;
    pstSndMsg->enMsgName                = ID_TAF_MMA_CSG_LIST_SEARCH_CNF;
    pstSndMsg->usClientId               = pstCtrl->usClientId;
    pstSndMsg->ucOpId                   = pstCtrl->ucOpId;

    PS_MEM_CPY(&pstSndMsg->stCsgListCnfPara, pstPlmnListCnfPara, sizeof(pstSndMsg->stCsgListCnfPara));

    ulRst = PS_SEND_MSG(WUEPS_PID_MMA, pstSndMsg);

    if (VOS_OK != ulRst)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA,"TAF_MMA_SndCsgListSearchCnf:Send Msg Failed");
        return;
    }

    return;

}

#endif

/*****************************************************************************
 函 数 名  : TAF_MMA_SndPlmnListAbortCnf
 功能描述  : 给AT发送ID_TAF_MMA_PLMN_LIST_ABORT_CNF
 输入参数  : pstCtrl         :
             enRslt          : 返回的结果
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :


 修改历史      :
  1.日    期   : 2015年3月23日
    作    者   : f00279542
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_MMA_SndPlmnListAbortCnf(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCode
)
{
    TAF_MMA_PLMN_LIST_ABORT_CNF_STRU   *pstSndMsg = VOS_NULL_PTR;

    pstSndMsg = (TAF_MMA_PLMN_LIST_ABORT_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                               WUEPS_PID_MMA,
                                               sizeof(TAF_MMA_PLMN_LIST_ABORT_CNF_STRU));
    if (VOS_NULL_PTR == pstSndMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA,"TAF_MMA_SndPlmnListAbortCnf:Alloc Msg Failed");
        return;
    }

    PS_MEM_SET((VOS_INT8 *)pstSndMsg + VOS_MSG_HEAD_LENGTH, 0X00,
               sizeof(TAF_MMA_PLMN_LIST_ABORT_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstSndMsg->ulReceiverPid            = WUEPS_PID_AT;
    pstSndMsg->ulMsgName                = ID_TAF_MMA_PLMN_LIST_ABORT_CNF;
    PS_MEM_CPY(&pstSndMsg->stCtrl, pstCtrl, sizeof(TAF_MMA_CTRL_STRU));
    pstSndMsg->enErrorCause             = enErrorCode;

    PS_SEND_MSG(WUEPS_PID_MMA, pstSndMsg);
    return;
}
/*****************************************************************************
 函 数 名  : TAF_MMA_ProcPlmnListAbortCnf
 功能描述  : 给AT发送ID_TAF_MMA_PLMN_LIST_ABORT_CNF
 输入参数  : pstCtrl         :
             enRslt          : 返回的结果
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :


 修改历史      :
  1.日    期   : 2015年3月23日
    作    者   : f00279542
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_MMA_ProcPlmnListAbortCnf(
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCode
)
{
    TAF_MMA_OPER_CTX_STRU              *pstMmaOperCtx = VOS_NULL_PTR;
    VOS_UINT8                           ucCtxIndex;

    pstMmaOperCtx = TAF_MMA_GetOperCtxAddr();

    /* 从全局变量g_stTafMmaCtx.astMmaOperCtx查找ID_TAF_MMA_PLMN_LIST_ABORT_REQ对应的记录项 */
    if (VOS_TRUE == TAF_MMA_GetSpecOperTypeIndex(TAF_MMA_OPER_PLMN_LIST_ABORT_REQ, &ucCtxIndex))
    {
        /*  回复MMA_CFPLMN_CNF */
        TAF_MMA_SndPlmnListAbortCnf(&(pstMmaOperCtx[ucCtxIndex].stCtrl), enErrorCode);

        TAF_MMA_ClearOperCtx(ucCtxIndex);

        if (VOS_TRUE == TAF_MMA_GetSpecOperTypeIndex(TAF_MMA_OPER_PLMN_LIST_REQ, &ucCtxIndex))
        {
            TAF_MMA_ClearOperCtx(ucCtxIndex);
            return;
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_SndCFPlmnQueryCnf
 功能描述  : 给AT发送ID_TAF_MMA_LOCINFO_QRY_CNF CNF
 输入参数  : pstCtrl         :
             enRslt          : 返回的结果
             pstCFPlmnCnfMsg : 回复的消息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :


 修改历史      :
  1.日    期   : 2015年3月26日
    作    者   : f00279542
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_MMA_SndLocInfoQryCnf(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    TAF_MMA_LOCATION_INFO_QRY_CNF_STRU *pstLocInfoQryCnfMsg
)
{
    TAF_MMA_LOCATION_INFO_QRY_CNF_STRU       *pstSndMsg = VOS_NULL_PTR;

    pstSndMsg = (TAF_MMA_LOCATION_INFO_QRY_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                      WUEPS_PID_MMA,
                                                      sizeof(TAF_MMA_LOCATION_INFO_QRY_CNF_STRU));
    if (VOS_NULL_PTR == pstSndMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA,"TAF_MMA_SndLocInfoQryCnf:Alloc Msg Failed");
        return;
    }

    PS_MEM_SET((VOS_INT8 *)pstSndMsg + VOS_MSG_HEAD_LENGTH, 0X00,
               sizeof(TAF_MMA_LOCATION_INFO_QRY_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstSndMsg->ulReceiverPid            = pstCtrl->ulModuleId;
    pstSndMsg->ulMsgName                = ID_TAF_MMA_LOCATION_INFO_QRY_CNF;
    PS_MEM_CPY(&pstSndMsg->stCtrl, pstCtrl, sizeof(TAF_MMA_CTRL_STRU));
    pstSndMsg->ulResult                 = pstLocInfoQryCnfMsg->ulResult;
    pstSndMsg->ulMcc                    = pstLocInfoQryCnfMsg->ulMcc;
    pstSndMsg->ulMnc                    = pstLocInfoQryCnfMsg->ulMnc;
    pstSndMsg->usLac                    = pstLocInfoQryCnfMsg->usLac;
    pstSndMsg->ucRac                    = pstLocInfoQryCnfMsg->ucRac;
    pstSndMsg->ucRsv                    = pstLocInfoQryCnfMsg->ucRsv;
    pstSndMsg->ulCellid                 = pstLocInfoQryCnfMsg->ulCellid;

    PS_SEND_MSG(WUEPS_PID_MMA, pstSndMsg);

    return;
}
/*****************************************************************************
 函 数 名  : TAF_MMA_SndPrefPlmnSetCnf
 功能描述  : 给AT发送ID_TAF_MMA_CPLS_SET_CNF CNF
 输入参数  : pstCtrl         :
             enRslt          : 返回的结果
             pstCFPlmnCnfMsg : 回复的消息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :


 修改历史      :
  1.日    期   : 2015年3月26日
    作    者   : f00279542
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_MMA_SndPrefPlmnTypeSetCnf(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCause,
    MN_PH_PREF_PLMN_TYPE_ENUM_U8        enPrefPlmnType
)
{
    TAF_MMA_PREF_PLMN_TYPE_SET_CNF_STRU          *pstSndMsg = VOS_NULL_PTR;

    pstSndMsg = (TAF_MMA_PREF_PLMN_TYPE_SET_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                       WUEPS_PID_MMA,
                                                       sizeof(TAF_MMA_PREF_PLMN_TYPE_SET_CNF_STRU));
    if (VOS_NULL_PTR == pstSndMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA,"TAF_MMA_SndPrefPlmnTypeSetCnf:Alloc Msg Failed");
        return;
    }

    PS_MEM_SET((VOS_INT8 *)pstSndMsg + VOS_MSG_HEAD_LENGTH, 0X00,
               sizeof(TAF_MMA_PREF_PLMN_TYPE_SET_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstSndMsg->ulReceiverPid            = pstCtrl->ulModuleId;
    pstSndMsg->ulMsgName                = ID_TAF_MMA_PREF_PLMN_TYPE_SET_CNF;

    PS_MEM_CPY(&pstSndMsg->stCtrl, pstCtrl, sizeof(TAF_MMA_CTRL_STRU));

    pstSndMsg->enErrorCause             = enErrorCause;
    pstSndMsg->enPrefPlmnType           = enPrefPlmnType;

    PS_SEND_MSG(WUEPS_PID_MMA, pstSndMsg);

    return;
}
/*****************************************************************************
 函 数 名  : TAF_MMA_SndMtPowrDownCnf
 功能描述  : 给AT发送ID_TAF_MMA_CPLS_SET_CNF CNF
 输入参数  : pstCtrl         :
             enRslt          : 返回的结果
             pstCFPlmnCnfMsg : 回复的消息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :


 修改历史      :
  1.日    期   : 2015年3月26日
    作    者   : f00279542
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_MMA_SndMtPowrDownCnf(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCause
)
{
    TAF_MMA_MT_POWER_DOWN_CNF_STRU     *pstSndMsg = VOS_NULL_PTR;

    pstSndMsg = (TAF_MMA_MT_POWER_DOWN_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                 WUEPS_PID_MMA,
                                                 sizeof(TAF_MMA_MT_POWER_DOWN_CNF_STRU));
    if (VOS_NULL_PTR == pstSndMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA,"TAF_MMA_SndMtPowrDownCnf:Alloc Msg Failed");
        return;
    }

    PS_MEM_SET((VOS_INT8 *)pstSndMsg + VOS_MSG_HEAD_LENGTH, 0X00,
               sizeof(TAF_MMA_MT_POWER_DOWN_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstSndMsg->ulReceiverPid            = pstCtrl->ulModuleId;
    pstSndMsg->ulMsgName                = ID_TAF_MMA_MT_POWER_DOWN_CNF;
    pstSndMsg->enErrorCause             = enErrorCause;

    PS_MEM_CPY(&pstSndMsg->stCtrl, pstCtrl, sizeof(TAF_MMA_CTRL_STRU));

    PS_SEND_MSG(WUEPS_PID_MMA, pstSndMsg);

    return;
}
/*****************************************************************************
 函 数 名  : TAF_MMA_SndPrefPlmnQueryCnf
 功能描述  : 发送prefplmn query cnf消息到taf
 输入参数  : TAF_MMA_CTRL_STRU                                          *pstCtrl,
             TAF_MMA_APP_PREF_PLMN_OPER_RESULT_ENUM_UINT32               enRslt
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年02月05日
    作    者   : y00307564
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_SndPrefPlmnSetCnf(
    TAF_MMA_CTRL_STRU                                      *pstCtrl,
    TAF_MMA_APP_PREF_PLMN_OPER_RESULT_ENUM_UINT32           enRslt
)
{
    TAF_MMA_PREF_PLMN_SET_CNF_STRU     *pstPrefPlmnCnf   = VOS_NULL_PTR;

    /* 申请消息包TAF_MMA_PREF_PLMN_SET_CNF_STRU */
    pstPrefPlmnCnf = (TAF_MMA_PREF_PLMN_SET_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                           WUEPS_PID_MMA,
                                           sizeof(TAF_MMA_PREF_PLMN_SET_CNF_STRU));

    /* 内存申请失败，返回 */
    if (VOS_NULL_PTR == pstPrefPlmnCnf)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndPrefPlmnSetCnf ERROR: Memory Alloc Error for pstPrefPlmnCnf");
        return;
    }

    PS_MEM_SET((VOS_INT8 *)pstPrefPlmnCnf + VOS_MSG_HEAD_LENGTH, 0X00,
        sizeof(TAF_MMA_PREF_PLMN_SET_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 根据输入参数填充TAF_MMA_PREF_PLMN_SET_CNF_STRU */
    pstPrefPlmnCnf->ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstPrefPlmnCnf->ulSenderPid       = WUEPS_PID_MMA;
    pstPrefPlmnCnf->ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstPrefPlmnCnf->ulReceiverPid     = pstCtrl->ulModuleId;
    pstPrefPlmnCnf->ulMsgName         = ID_TAF_MMA_PREF_PLMN_SET_CNF;

    pstPrefPlmnCnf->usClientId        = pstCtrl->usClientId;
    pstPrefPlmnCnf->ucOpId            = pstCtrl->ucOpId;
    pstPrefPlmnCnf->enRslt            = enRslt;

    /* 发送消息 */
    PS_SEND_MSG(WUEPS_PID_MMA, pstPrefPlmnCnf);

    return;
}
/*****************************************************************************
 函 数 名  : TAF_MMA_SndPrefPlmnQueryCnf
 功能描述  : 发送prefplmn query cnf消息到taf
 输入参数  : TAF_MMA_CTRL_STRU                                      *pstCtrl,
             TAF_MMA_APP_PREF_PLMN_OPER_RESULT_ENUM_UINT32           enRslt,
             MSCC_MMA_PREF_PLMN_QUERY_CNF_STRU                      *pstRcvMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年02月05日
    作    者   : y00307564
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_SndPrefPlmnQueryCnf(
    TAF_MMA_CTRL_STRU                                      *pstCtrl,
    TAF_MMA_APP_PREF_PLMN_OPER_RESULT_ENUM_UINT32           enRslt,
    MSCC_MMA_PREF_PLMN_QUERY_CNF_STRU                      *pstRcvMsg
)
{
    TAF_MMA_PREF_PLMN_QUERY_CNF_STRU                       *pstPrefPlmnCnf      = VOS_NULL_PTR;
    TAF_PH_OPERATOR_NAME_FORMAT_OP_STRU                     stOperName;
    VOS_UINT32                                              i;

    /* 申请内存  */
    pstPrefPlmnCnf = (TAF_MMA_PREF_PLMN_QUERY_CNF_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMA,
                           sizeof(TAF_MMA_PREF_PLMN_QUERY_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstPrefPlmnCnf)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndPrefPlmnQueryCnf ERROR: Memory Alloc Error for pstPrefPlmnCnf");
        return;
    }

    PS_MEM_SET((VOS_INT8 *)pstPrefPlmnCnf + VOS_MSG_HEAD_LENGTH, 0,
                           sizeof(TAF_MMA_PREF_PLMN_QUERY_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填写消息头部信息 */
    pstPrefPlmnCnf->ulSenderCpuId          = VOS_LOCAL_CPUID;
    pstPrefPlmnCnf->ulSenderPid            = WUEPS_PID_MMA;
    pstPrefPlmnCnf->ulReceiverCpuId        = VOS_LOCAL_CPUID;
    pstPrefPlmnCnf->ulReceiverPid          = pstCtrl->ulModuleId;
    pstPrefPlmnCnf->ulMsgName              = ID_TAF_MMA_PREF_PLMN_QUERY_CNF;

    /* 填写消息体 */
    pstPrefPlmnCnf->usClientId             = pstCtrl->usClientId;
    pstPrefPlmnCnf->ucOpId                 = pstCtrl->ucOpId;
    pstPrefPlmnCnf->enRslt                 = enRslt;

    if (VOS_NULL_PTR != pstRcvMsg)
    {
        /* 填写消息体 */
        pstPrefPlmnCnf->ulFromIndex            = pstRcvMsg->ulFromIndex;
        pstPrefPlmnCnf->ulValidPlmnNum         = pstRcvMsg->ulValidPlmnNum;

        PS_MEM_CPY(&(pstPrefPlmnCnf->stPlmnName), &(pstRcvMsg->stPlmnName), sizeof(TAF_PLMN_NAME_LIST_STRU));

        for (i = 0; i < pstPrefPlmnCnf->stPlmnName.ulPlmnNum; i++ )
        {
            /* 由于核间通信最多只能传4K，所以不能获取所有的优先网络列表的长短名。*/
            PS_MEM_SET(&stOperName, 0, sizeof(stOperName));
            stOperName.OperName.PlmnId.Mcc  = pstPrefPlmnCnf->stPlmnName.astPlmnName[i].PlmnId.Mcc;
            stOperName.OperName.PlmnId.Mnc  = pstPrefPlmnCnf->stPlmnName.astPlmnName[i].PlmnId.Mnc;
            stOperName.ListOp               = TAF_PH_OPER_NAME_PLMN2ALPHANUMERICNAME;

            /* 获取优先网络的长短名 */
            if (MMA_SUCCESS == Taf_PhoneGetNetworkNameForListPlmn(&stOperName))
            {
                PS_MEM_CPY(pstPrefPlmnCnf->stPlmnName.astPlmnName[i].aucOperatorNameLong,
                           stOperName.OperName.aucOperatorNameLong,
                           TAF_PH_OPER_NAME_LONG);

                PS_MEM_CPY(pstPrefPlmnCnf->stPlmnName.astPlmnName[i].aucOperatorNameShort,
                           stOperName.OperName.aucOperatorNameShort,
                           TAF_PH_OPER_NAME_SHORT);
            }
            else
            {
                pstPrefPlmnCnf->stPlmnName.astPlmnName[i].aucOperatorNameLong[0]  = '\0';
                pstPrefPlmnCnf->stPlmnName.astPlmnName[i].aucOperatorNameShort[0] = '\0';
            }

        }

    }

    /* 发送消息 */
    PS_SEND_MSG(WUEPS_PID_MMA, pstPrefPlmnCnf);

    return;

}

/*****************************************************************************
 函 数 名  : TAF_MMA_SndPrefPlmnTestCnf
 功能描述  : 发送prefplmn test cnf消息到taf
 输入参数  : TAF_MMA_CTRL_STRU                                      *pstCtrl,
             TAF_MMA_APP_PREF_PLMN_OPER_RESULT_ENUM_UINT32           enRslt,
             MSCC_MMA_PREF_PLMN_QUERY_CNF_STRU                      *pstRcvMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年02月05日
    作    者   : y00307564
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_SndPrefPlmnTestCnf(
    TAF_MMA_CTRL_STRU                                      *pstCtrl,
    TAF_MMA_APP_PREF_PLMN_OPER_RESULT_ENUM_UINT32           enRslt,
    MSCC_MMA_PREF_PLMN_QUERY_CNF_STRU                      *pstRcvMsg
)
{
    TAF_MMA_PREF_PLMN_TEST_CNF_STRU    *pstPrefPlmnCnf      = VOS_NULL_PTR;

    /* 申请内存  */
    pstPrefPlmnCnf = (TAF_MMA_PREF_PLMN_TEST_CNF_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMA,
                           sizeof(TAF_MMA_PREF_PLMN_TEST_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstPrefPlmnCnf)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndPrefPlmnTestCnf ERROR: Memory Alloc Error for pstPrefPlmnCnf");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstPrefPlmnCnf + VOS_MSG_HEAD_LENGTH, 0,
                sizeof(TAF_MMA_PREF_PLMN_TEST_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填写消息头部信息 */
    pstPrefPlmnCnf->ulSenderCpuId          = VOS_LOCAL_CPUID;
    pstPrefPlmnCnf->ulSenderPid            = WUEPS_PID_MMA;
    pstPrefPlmnCnf->ulReceiverCpuId        = VOS_LOCAL_CPUID;
    pstPrefPlmnCnf->ulReceiverPid          = pstCtrl->ulModuleId;
    pstPrefPlmnCnf->ulMsgName              = ID_TAF_MMA_PREF_PLMN_TEST_CNF;

    /* 填充消息体 */
    pstPrefPlmnCnf->usClientId             = pstCtrl->usClientId;
    pstPrefPlmnCnf->ucOpId                 = pstCtrl->ucOpId;
    pstPrefPlmnCnf->enRslt                 = enRslt;

    if (VOS_NULL_PTR != pstRcvMsg)
    {
        /* 填充消息体 */
        pstPrefPlmnCnf->usPlmnNum          = pstRcvMsg->usPlmnNum;
    }

    /* 发送消息 */
    PS_SEND_MSG(WUEPS_PID_MMA, pstPrefPlmnCnf);

    return;
}


/*****************************************************************************
 函 数 名  : TAF_MMA_SndAtRegStatus
 功能描述  : 上报注册状态给AT
 输入参数  : enCnDomainId:服务域
             enRegState:注册状态
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年02月15日
    作    者   : s00217060
    修改内容   : 新增函数

*****************************************************************************/
VOS_VOID TAF_MMA_SndAtRegStatus(
    NAS_MSCC_PIF_SRVDOMAIN_ENUM_UINT32  enCnDomainId,
    NAS_MSCC_PIF_REG_STATE_ENUM_UINT8   enRegState
)
{
    TAF_SDC_PLMN_ID_STRU               *pstPlmnId     = VOS_NULL_PTR;

    TAF_PH_REG_STATE_STRU               stRegStatus;

    pstPlmnId     = TAF_SDC_GetCurrCampPlmnId();

    PS_MEM_SET(&stRegStatus, 0, sizeof(TAF_PH_REG_STATE_STRU));

    /* 填写CREG/CGREG对应的OP项 */
    if (NAS_MSCC_PIF_SRVDOMAIN_CS == enCnDomainId)
    {
        stRegStatus.OP_CsRegState = VOS_TRUE;
        stRegStatus.OP_Lac        = VOS_TRUE;
        stRegStatus.OP_CellId     = VOS_TRUE;
        stRegStatus.OP_ucAct      = VOS_TRUE;
        stRegStatus.RegState      = enRegState;
    }
    else if (NAS_MSCC_PIF_SRVDOMAIN_PS == enCnDomainId)
    {
        stRegStatus.OP_PsRegState = VOS_TRUE;
        stRegStatus.OP_Lac        = VOS_TRUE;
        stRegStatus.OP_Rac        = VOS_TRUE;
        stRegStatus.OP_CellId     = VOS_TRUE;
        stRegStatus.OP_ucAct      = VOS_TRUE;
        stRegStatus.ucPsRegState  = enRegState;
    }
    else
    {
        /* 服务域填的不对，释放已经分配的内存空间，直接返回 */
        return;
    }

    /* 驻留信息 */
    stRegStatus.ucRac               = TAF_SDC_GetCurrCampRac();
    stRegStatus.CellId.ucCellNum    = 1;
    stRegStatus.CellId.aulCellId[0] = TAF_SDC_GetCurrCampCellId();
    stRegStatus.usLac               = TAF_SDC_GetCurrCampLac();

    PS_MEM_CPY(&stRegStatus.Plmn, pstPlmnId, sizeof(TAF_PLMN_ID_STRU));

    /* 将MMC上报的系统子模式转为+CREG/+CGREG命令参数[ACT]中协议规定的接入技术值 */
    NAS_MMA_TransferSysSubMode2ActForAtCmdCreg(TAF_SDC_GetSysSubMode(), &(stRegStatus.ucAct));

    switch (TAF_SDC_GetCampSysMode())
    {
#if (FEATURE_ON == FEATURE_LTE)
        case TAF_SDC_SYS_MODE_LTE:
            stRegStatus.ucRatType = TAF_PH_INFO_LTE_RAT;
            break;
#endif

        case TAF_SDC_SYS_MODE_WCDMA:
            stRegStatus.ucRatType = TAF_PH_INFO_WCDMA_RAT;
            break;

        case TAF_SDC_SYS_MODE_GSM:
            stRegStatus.ucRatType = TAF_PH_INFO_GSM_RAT;
            break;

        default:
            stRegStatus.ucRatType = TAF_PH_INFO_NONE_RAT;
            break;
    }

    if (VOS_TRUE != TAF_MMA_IsRegStatusChangeNeedRpt(&stRegStatus))
    {
        return;
    }

    TAF_MMA_RecordRegStatusReportFlag(enCnDomainId, enRegState);

    TAF_MMA_SndRegStatusInd(&stRegStatus);

    return;
}
/*****************************************************************************
 函 数 名  : TAF_MMA_GetCardInfo
 功能描述  : 根据消息中Usim和Csim卡状态和卡类型选择上报给AT的数据
 输入参数  : USIMM_CARDSTATUS_IND_STRU *pStPsUsimStatusInd: 消息结构体
 输出参数  : USIMM_CARD_TYPE_ENUM_UINT32 enCardType: 卡类型
             USIMM_CARD_SERVIC_ENUM_UINT32 enCardStatus: 卡状态
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月7日
    作    者   : h00313353
    修改内容   : 新增函数

*****************************************************************************/
VOS_VOID TAF_MMA_GetCardInfo(
    USIMM_CARDSTATUS_IND_STRU          *pStPsUsimStatusInd,
    USIMM_CARD_TYPE_ENUM_UINT32        *enCardType,
    USIMM_CARD_SERVIC_ENUM_UINT32      *enCardStatus
)
{
    /* 如果USIM应用可用，取USIM状态 */
    if (USIMM_CARD_SERVIC_AVAILABLE == pStPsUsimStatusInd->stUsimSimInfo.enCardService)
    {

        *enCardStatus    = USIMM_CARD_SERVIC_AVAILABLE;
        *enCardType      = pStPsUsimStatusInd->stUsimSimInfo.enCardType;
    }
    else if (USIMM_CARD_SERVIC_ABSENT != pStPsUsimStatusInd->stUsimSimInfo.enCardService)
    {
        /* 如果CSIM可用，取CSIM状态 */
        if (USIMM_CARD_SERVIC_AVAILABLE == pStPsUsimStatusInd->stCsimUimInfo.enCardService)
        {
            *enCardStatus    = USIMM_CARD_SERVIC_AVAILABLE;
            *enCardType      = pStPsUsimStatusInd->stCsimUimInfo.enCardType;
        }
        else
        {
            /* 如果USIM不是不存在，取USIM状态 */
            *enCardStatus    = pStPsUsimStatusInd->stUsimSimInfo.enCardService;
            *enCardType      = pStPsUsimStatusInd->stUsimSimInfo.enCardType;
        }
    }
    else
    {
        /* 如果USIM不存在，CSIM不是不存在，取CSIM状态 */
        if (USIMM_CARD_SERVIC_ABSENT != pStPsUsimStatusInd->stCsimUimInfo.enCardService)
        {
            *enCardStatus    = pStPsUsimStatusInd->stCsimUimInfo.enCardService;
            *enCardType      = pStPsUsimStatusInd->stCsimUimInfo.enCardType;
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_SndATUsimmStatusInd
 功能描述  : 向AT发送卡状态消息
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月7日
    作    者   : h00313353
    修改内容   : 新增函数

*****************************************************************************/
VOS_VOID TAF_MMA_SndATUsimmStatusInd(
    USIMM_CARDSTATUS_IND_STRU          *pStPsUsimStatusInd,
    VOS_UINT8                          *pucIMSI
)
{
    AT_MMA_USIM_STATUS_IND_STRU        *pstAtMmaUsimStatusIndMsg;
    USIMM_CARD_TYPE_ENUM_UINT32         enCardType;
    USIMM_CARD_SERVIC_ENUM_UINT32       enCardStatus;

    enCardType      = USIMM_CARD_NOCARD;
    enCardStatus    = USIMM_CARD_SERVIC_ABSENT;

    /* 申请消息内存并初始化 */
    pstAtMmaUsimStatusIndMsg = (AT_MMA_USIM_STATUS_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                             WUEPS_PID_MMA,
                                             sizeof(AT_MMA_USIM_STATUS_IND_STRU));
    if( VOS_NULL_PTR == pstAtMmaUsimStatusIndMsg )
    {
        TAF_LOG(WUEPS_PID_MMA, VOS_NULL, PS_LOG_LEVEL_ERROR, "MMA_PhUsimStatusInd:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8 *)pstAtMmaUsimStatusIndMsg + VOS_MSG_HEAD_LENGTH,
               0X00,
               sizeof(AT_MMA_USIM_STATUS_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 获取卡类型和卡状态 */
    TAF_MMA_GetCardInfo(pStPsUsimStatusInd, &enCardType, &enCardStatus);

    /* 填写消息 */
    pstAtMmaUsimStatusIndMsg->ulReceiverPid          = WUEPS_PID_AT;
    pstAtMmaUsimStatusIndMsg->ulMsgName              = ID_TAF_MMA_USIM_STATUS_IND;
    pstAtMmaUsimStatusIndMsg->enCardType             = enCardType;
    pstAtMmaUsimStatusIndMsg->enCardStatus           = enCardStatus;
    pstAtMmaUsimStatusIndMsg->enPhyCardType          = pStPsUsimStatusInd->enPhyCardType;
    pstAtMmaUsimStatusIndMsg->ucIMSILen              = PS_MIN(pucIMSI[0], NAS_MAX_IMSI_LENGTH);
    PS_MEM_CPY(pstAtMmaUsimStatusIndMsg->aucIMSI, pucIMSI, pstAtMmaUsimStatusIndMsg->ucIMSILen);

    NAS_TRACE_HIGH("\nTAF_MMA_SndATUsimmStatusInd: CardType: %d , CardStatus: %d , ulSenderPid: %d",
                   enCardType, enCardStatus, pstAtMmaUsimStatusIndMsg->ulSenderPid);

    /* 发送消息 */
    PS_SEND_MSG(WUEPS_PID_MMA, pstAtMmaUsimStatusIndMsg);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_SndPlmnListCnf
 功能描述  : 给MSG发送列表搜结果
 输入参数  : pstCtrl                    - 接收模块信息
             enRslt
             usErrorCause
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月12日
    作    者   : b00269685
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_MMA_SndPlmnListCnf(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    TAF_MMA_PLMN_LIST_CNF_PARA_STRU    *pstPlmnListCnfPara
)
{
    TAF_MMA_PLMN_LIST_CNF_STRU         *pstSndMsg   = VOS_NULL_PTR;
    VOS_UINT32                          ulRst;

    pstSndMsg = (TAF_MMA_PLMN_LIST_CNF_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                             WUEPS_PID_MMA,
                                             sizeof(TAF_MMA_PLMN_LIST_CNF_STRU));
    if (VOS_NULL_PTR == pstSndMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA,"TAF_MMA_SndPlmnListCnf:Alloc Msg Failed");
        return;
    }

    PS_MEM_SET( (VOS_INT8 *)pstSndMsg + VOS_MSG_HEAD_LENGTH, 0X00,
            sizeof(TAF_MMA_PLMN_LIST_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstSndMsg->ulSenderCpuId            = VOS_LOCAL_CPUID;
    pstSndMsg->ulSenderPid              = WUEPS_PID_MMA;
    pstSndMsg->ulReceiverCpuId          = VOS_LOCAL_CPUID;
    pstSndMsg->ulReceiverPid            = pstCtrl->ulModuleId;
    pstSndMsg->ulMsgName                = ID_TAF_MMA_PLMN_LIST_CNF;
    pstSndMsg->usClientId               = pstCtrl->usClientId;
    pstSndMsg->ucOpId                   = pstCtrl->ucOpId;
    PS_MEM_CPY(&pstSndMsg->stPlmnListCnfPara, pstPlmnListCnfPara, sizeof(TAF_MMA_PLMN_LIST_CNF_PARA_STRU));

    ulRst = PS_SEND_MSG(WUEPS_PID_MMA, pstSndMsg);

    if (VOS_OK != ulRst)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA,"TAF_MMA_SndSysCfgSetCnf:Send Msg Failed");
        return;
    }

    return;

}

/*****************************************************************************
 函 数 名  : TAF_MMA_SndCerssiSetCnf
 功能描述  : Mma Snd Cerssi Set Cnf
 输入参数  : TAF_MMA_CTRL_STRU                  *pstCtrl
             TAF_ERROR_CODE_ENUM_UINT32          enErrorCause
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月23日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_SndCerssiSetCnf(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCause
)
{
    TAF_MMA_CERSSI_SET_CNF_STRU        *pstSetCerssiCnf   = VOS_NULL_PTR;

    /* 申请消息内存TAF_MMA_CERSSI_SET_CNF_STRU */
    pstSetCerssiCnf = (TAF_MMA_CERSSI_SET_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                     WUEPS_PID_MMA,
                                                     sizeof(TAF_MMA_CERSSI_SET_CNF_STRU));

    /* 内存申请失败，返回 */
    if (VOS_NULL_PTR == pstSetCerssiCnf)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndCerssiSetCnf ERROR: Memory Alloc Error for pstSetCerssiCnf");
        return;
    }

    PS_MEM_SET((VOS_INT8 *)pstSetCerssiCnf + VOS_MSG_HEAD_LENGTH, 0X00,
        sizeof(TAF_MMA_CERSSI_SET_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 根据输入参数填充TAF_MMA_CERSSI_SET_CNF_STRU */
    pstSetCerssiCnf->ulSenderCpuId          = VOS_LOCAL_CPUID;
    pstSetCerssiCnf->ulSenderPid            = WUEPS_PID_MMA;
    pstSetCerssiCnf->ulReceiverCpuId        = VOS_LOCAL_CPUID;
    pstSetCerssiCnf->ulReceiverPid          = pstCtrl->ulModuleId;
    pstSetCerssiCnf->ulMsgName              = ID_TAF_MMA_CERSSI_SET_CNF;

    PS_MEM_CPY(&pstSetCerssiCnf->stCtrl, pstCtrl, sizeof(TAF_MMA_CTRL_STRU));

    pstSetCerssiCnf->enErrorCause           = enErrorCause;

    /* 发送消息 */
    PS_SEND_MSG(WUEPS_PID_MMA, pstSetCerssiCnf);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_SndAccessModeQryCnf
 功能描述  : MMA Snd Access Mode Qry Cnf
 输入参数  : TAF_MMA_CTRL_STRU                  *pstCtrl
             MN_MMA_CPAM_RAT_TYPE_ENUM_UINT8     enAccessMode
             TAF_PH_PLMN_PRIO                    ucPlmnPrio
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月27日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_SndAccessModeQryCnf(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    MN_MMA_CPAM_RAT_TYPE_ENUM_UINT8     enAccessMode,
    TAF_PH_PLMN_PRIO                    ucPlmnPrio
)
{
    TAF_MMA_ACCESS_MODE_QRY_CNF_STRU  *pstAccessModeCnf = VOS_NULL_PTR;

    /* 申请消息包TAF_MMA_DETACH_CNF_STRU */
    pstAccessModeCnf = (TAF_MMA_ACCESS_MODE_QRY_CNF_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                          WUEPS_PID_MMA,
                                                          sizeof(TAF_MMA_ACCESS_MODE_QRY_CNF_STRU));

    /* 内存申请失败，返回 */
    if (VOS_NULL_PTR == pstAccessModeCnf)
    {
        return;
    }

    PS_MEM_SET( (VOS_INT8 *)pstAccessModeCnf + VOS_MSG_HEAD_LENGTH, 0X00,
                 sizeof(TAF_MMA_ACCESS_MODE_QRY_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 根据输入参数填充TAF_MMA_ACCESS_MODE_QRY_CNF_STRU */
    pstAccessModeCnf->ulReceiverPid          = pstCtrl->ulModuleId;
    pstAccessModeCnf->ulMsgName              = ID_TAF_MMA_ACCESS_MODE_QRY_CNF;
    pstAccessModeCnf->stCtrl.usClientId      = pstCtrl->usClientId;
    pstAccessModeCnf->stCtrl.ucOpId          = pstCtrl->ucOpId;

    pstAccessModeCnf->enAccessMode           = enAccessMode;
    pstAccessModeCnf->ucPlmnPrio             = ucPlmnPrio;

    /* 发送消息 */
    PS_SEND_MSG(WUEPS_PID_MMA, pstAccessModeCnf);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_SndCopsQryCnf
 功能描述  : Mma Snd Cops Qry Cnf
 输入参数  : TAF_MMA_CTRL_STRU                  *pstCtrl
             TAF_PH_NETWORKNAME_STRU            *pstCopsInfo
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月27日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_SndCopsQryCnf(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    TAF_PH_NETWORKNAME_STRU            *pstCopsInfo
)
{
    TAF_MMA_COPS_QRY_CNF_STRU          *pstCopsCnf = VOS_NULL_PTR;

    /* 申请消息包TAF_MMA_DETACH_CNF_STRU */
    pstCopsCnf = (TAF_MMA_COPS_QRY_CNF_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                             WUEPS_PID_MMA,
                                             sizeof(TAF_MMA_COPS_QRY_CNF_STRU));

    /* 内存申请失败，返回 */
    if (VOS_NULL_PTR == pstCopsCnf)
    {
        return;
    }

    PS_MEM_SET( (VOS_INT8 *)pstCopsCnf + VOS_MSG_HEAD_LENGTH, 0X00,
                 sizeof(TAF_MMA_COPS_QRY_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 根据输入参数填充TAF_MMA_ACCESS_MODE_QRY_CNF_STRU */
    pstCopsCnf->ulReceiverPid          = pstCtrl->ulModuleId;
    pstCopsCnf->ulMsgName              = ID_TAF_MMA_COPS_QRY_CNF;
    pstCopsCnf->usClientId             = pstCtrl->usClientId;
    pstCopsCnf->ucOpId                 = pstCtrl->ucOpId;

    PS_MEM_CPY(&(pstCopsCnf->stCopsInfo), pstCopsInfo, sizeof(TAF_PH_NETWORKNAME_STRU));

    /* 发送消息 */
    PS_SEND_MSG(WUEPS_PID_MMA, pstCopsCnf);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_SndRegStateQryCnf
 功能描述  : Mma Snd Creg Cnf
 输入参数  : TAF_MMA_CTRL_STRU                  *pstCtrl
             TAF_PH_REG_STATE_STRU              *pstRegInfo
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月27日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_SndRegStateQryCnf(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    TAF_PH_REG_STATE_STRU              *pstRegInfo
)
{
    TAF_MMA_REG_STATE_QRY_CNF_STRU     *pstRegStateQryCnf = VOS_NULL_PTR;

    /* 申请消息包TAF_MMA_REG_STATE_QRY_CNF_STRU */
    pstRegStateQryCnf = (TAF_MMA_REG_STATE_QRY_CNF_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                         WUEPS_PID_MMA,
                                                         sizeof(TAF_MMA_REG_STATE_QRY_CNF_STRU));

    /* 内存申请失败，返回 */
    if (VOS_NULL_PTR == pstRegStateQryCnf)
    {
        return;
    }

    PS_MEM_SET( (VOS_INT8 *)pstRegStateQryCnf + VOS_MSG_HEAD_LENGTH, 0X00,
                 sizeof(TAF_MMA_REG_STATE_QRY_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 根据输入参数填充TAF_MMA_REG_STATE_QRY_CNF_STRU */
    pstRegStateQryCnf->ulReceiverPid          = pstCtrl->ulModuleId;
    pstRegStateQryCnf->ulMsgName              = ID_TAF_MMA_REG_STATE_QRY_CNF;

    PS_MEM_CPY(&pstRegStateQryCnf->stCtrl, pstCtrl, sizeof(TAF_MMA_CTRL_STRU));
    PS_MEM_CPY(&(pstRegStateQryCnf->stRegInfo), pstRegInfo, sizeof(TAF_PH_REG_STATE_STRU));

    /* 发送消息 */
    PS_SEND_MSG(WUEPS_PID_MMA, pstRegStateQryCnf);

    return;
}


/*****************************************************************************
 函 数 名  : TAF_MMA_SndSystemInfoQryCnf
 功能描述  : Mma Snd System Info Qry Cnf
 输入参数  : TAF_MMA_CTRL_STRU                  *pstCtrl
             TAF_PH_SYSINFO_STRU                *pstSysInfo
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月28日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_SndSystemInfoQryCnf(
    TAF_MMA_SYSINFO_QRY_REQ_STRU       *pstSysInfoQryReq,
    TAF_PH_SYSINFO_STRU                *pstSysInfo
)
{
    TAF_MMA_SYSINFO_QRY_CNF_STRU       *pstSysInfoCnf = VOS_NULL_PTR;

    TAF_MMA_CTRL_STRU                  *pstCtrl       = VOS_NULL_PTR;

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    VOS_UINT32                          ulIsConfigCLMode;

    ulIsConfigCLMode = TAF_SDC_IsConfigCLMode();
#endif

    pstCtrl          = &(pstSysInfoQryReq->stCtrl);



    /* 申请消息包TAF_MMA_SYSINFO_QRY_CNF_STRU */
    pstSysInfoCnf = (TAF_MMA_SYSINFO_QRY_CNF_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                      WUEPS_PID_MMA,
                                                      sizeof(TAF_MMA_SYSINFO_QRY_CNF_STRU));

    /* 内存申请失败，返回 */
    if (VOS_NULL_PTR == pstSysInfoCnf)
    {
        return;
    }

    PS_MEM_SET( (VOS_INT8 *)pstSysInfoCnf + VOS_MSG_HEAD_LENGTH, 0X00,
                 sizeof(TAF_MMA_SYSINFO_QRY_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 根据输入参数填充TAF_MMA_SYSINFO_QRY_CNF_STRU */
    pstSysInfoCnf->ulReceiverPid          = pstCtrl->ulModuleId;
    pstSysInfoCnf->ulMsgName              = ID_TAF_MMA_SYSINFO_QRY_CNF;
    pstSysInfoCnf->usClientId             = pstCtrl->usClientId;
    pstSysInfoCnf->ucOpId                 = pstCtrl->ucOpId;

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if ((VOS_TRUE  == ulIsConfigCLMode)
     && (VOS_FALSE == pstSysInfoQryReq->ulSysInfoExFlag))
    {
        pstSysInfoCnf->ucIsSupport        = VOS_FALSE;
    }
    else
    {
        pstSysInfoCnf->ucIsSupport        = VOS_TRUE;
    }
#else
        pstSysInfoCnf->ucIsSupport        = VOS_TRUE;
#endif

    PS_MEM_CPY(&(pstSysInfoCnf->stSysInfo), pstSysInfo, sizeof(TAF_PH_SYSINFO_STRU));


    /* 发送消息 */
    PS_SEND_MSG(WUEPS_PID_MMA, pstSysInfoCnf);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_SndAntennaInfoQryCnf
 功能描述  : Mma Snd Antenna Info Qry Cnf
 输入参数  : TAF_MMA_CTRL_STRU                  *pstCtrl
             TAF_ERROR_CODE_ENUM_UINT32          enErrorCause
             MN_MMA_ANQUERY_PARA_STRU           *pstAnqueryInfo
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月30日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_SndAntennaInfoQryCnf(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCause,
    MN_MMA_ANQUERY_PARA_STRU           *pstAnqueryInfo
)
{
    TAF_MMA_ANTENNA_INFO_QRY_CNF_STRU  *pstAnqueryCnf = VOS_NULL_PTR;

    /* 申请消息包TAF_MMA_ANTENNA_INFO_QRY_CNF_STRU */
    pstAnqueryCnf = (TAF_MMA_ANTENNA_INFO_QRY_CNF_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                        WUEPS_PID_MMA,
                                                        sizeof(TAF_MMA_ANTENNA_INFO_QRY_CNF_STRU));

    /* 内存申请失败，返回 */
    if (VOS_NULL_PTR == pstAnqueryCnf)
    {
        return;
    }

    PS_MEM_SET( (VOS_INT8 *)pstAnqueryCnf + VOS_MSG_HEAD_LENGTH, 0X00,
                 sizeof(TAF_MMA_ANTENNA_INFO_QRY_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 根据输入参数填充TAF_MMA_ANTENNA_INFO_QRY_CNF_STRU */
    pstAnqueryCnf->ulReceiverPid          = pstCtrl->ulModuleId;
    pstAnqueryCnf->ulMsgName              = ID_TAF_MMA_ANTENNA_INFO_QRY_CNF;
    PS_MEM_CPY(&pstAnqueryCnf->stCtrl, pstCtrl, sizeof(TAF_MMA_CTRL_STRU));

    pstAnqueryCnf->enErrorCause             = enErrorCause;

    PS_MEM_CPY(&(pstAnqueryCnf->stAntennaInfo), pstAnqueryInfo, sizeof(MN_MMA_ANQUERY_PARA_STRU));

    /* 发送消息 */
    PS_SEND_MSG(WUEPS_PID_MMA, pstAnqueryCnf);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_SndApHplmnCnf
 功能描述  : Mma Snd Aphplmn Qry Cnf
 输入参数  : VOS_UINT16                          usClientId
             VOS_UINT8                           ucOpId
             TAF_ERROR_CODE_ENUM_UINT32          enErrorCause,
             TAF_MMA_HPLMN_WITH_MNC_LEN_STRU    *pstHplmnWithMnc
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月30日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_SndApHplmnCnf(
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCause,
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    TAF_MMA_EHPLMN_INFO_STRU           *pstEHplmnInfo
)
{
    TAF_MMA_HOME_PLMN_QRY_CNF_STRU     *pstHplmnQryCnf = VOS_NULL_PTR;

    /* 申请消息内存 */
    pstHplmnQryCnf = (TAF_MMA_HOME_PLMN_QRY_CNF_STRU*)TAF_MMA_ALLOC_MSG_WITH_HDR(
                                        sizeof(TAF_MMA_HOME_PLMN_QRY_CNF_STRU));

    if (VOS_NULL_PTR == pstHplmnQryCnf)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndApHplmnCnf:ERROR: Memory Alloc Error for pstHplmnQryCnf");

        return;
    }

    /* 清空消息内容 */
    TAF_MMA_CLR_MSG_ENTITY(pstHplmnQryCnf);

    /* 填写消息头 */
    TAF_MMA_CFG_MSG_HDR(pstHplmnQryCnf, WUEPS_PID_AT, ID_TAF_MMA_HOME_PLMN_QRY_CNF);

    /* 填写消息内容 */
    pstHplmnQryCnf->enErrorCause             = enErrorCause;

    if (VOS_NULL_PTR != pstCtrl)
    {
        PS_MEM_CPY(&(pstHplmnQryCnf->stCtrl), pstCtrl, sizeof(TAF_MMA_CTRL_STRU));
    }

    if (VOS_NULL_PTR != pstEHplmnInfo)
    {
        PS_MEM_CPY(&(pstHplmnQryCnf->stEHplmnInfo), pstEHplmnInfo, sizeof(TAF_MMA_EHPLMN_INFO_STRU));
    }

    /* 发送消息 */
    TAF_MMA_SEND_MSG(pstHplmnQryCnf);

    return;
}


/*****************************************************************************
 函 数 名  : TAF_MMA_SndCsqQryCnf
 功能描述  : csq查询消息上报接口
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月28日
    作    者   : y00322978
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_SndCsqQryCnf(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    TAF_PH_RSSI_STRU                   *pstCsqPara
)
{
    TAF_MMA_CSQ_QRY_CNF_STRU     *pstCsqCnf = VOS_NULL_PTR;

    /* 申请消息包TAF_MMA_CSQ_QRY_CNF_STRU */
    pstCsqCnf = (TAF_MMA_CSQ_QRY_CNF_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                           WUEPS_PID_MMA,
                                           sizeof(TAF_MMA_CSQ_QRY_CNF_STRU));

    /* 内存申请失败，返回 */
    if (VOS_NULL_PTR == pstCsqCnf)
    {
        return;
    }

    PS_MEM_SET( (VOS_INT8 *)pstCsqCnf + VOS_MSG_HEAD_LENGTH, 0X00,
                 sizeof(TAF_MMA_CSQ_QRY_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 根据输入参数填充TAF_MMA_CSQ_QRY_CNF_STRU */
    pstCsqCnf->ulReceiverPid          = pstCtrl->ulModuleId;
    pstCsqCnf->ulMsgName              = ID_TAF_MMA_CSQ_QRY_CNF;
    PS_MEM_CPY(&pstCsqCnf->stCtrl, pstCtrl, sizeof(TAF_MMA_CTRL_STRU));
    pstCsqCnf->enErrorCause           = TAF_ERR_NO_ERROR;

    if (VOS_NULL_PTR != pstCsqPara )
    {
        PS_MEM_CPY(&(pstCsqCnf->stCsq), pstCsqPara, sizeof(TAF_PH_RSSI_STRU));
    }

    /* 发送消息 */
    PS_SEND_MSG(WUEPS_PID_MMA, pstCsqCnf);

    return;

}
/*****************************************************************************
 函 数 名  : TAF_MMA_SndCsqLvlQryCnf
 功能描述  : CSQLVL查询消息上报接口
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月28日
    作    者   : y00322978
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_SndCsqLvlQryCnf(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    TAF_MMA_CSQLVL_PARA_STRU           *pstCsqlvlPara,
    TAF_MMA_CSQLVLEXT_PARA_STRU        *stCsqLvlExtPara,
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCause
)
{
    TAF_MMA_CSQLVL_QRY_CNF_STRU     *pstCsqlvlCnf = VOS_NULL_PTR;

    /* 申请消息包TAF_MMA_CSQLVL_QRY_CNF_STRU */
    pstCsqlvlCnf = (TAF_MMA_CSQLVL_QRY_CNF_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                 WUEPS_PID_MMA,
                                                 sizeof(TAF_MMA_CSQLVL_QRY_CNF_STRU));

    /* 内存申请失败，返回 */
    if (VOS_NULL_PTR == pstCsqlvlCnf)
    {
        return;
    }

    PS_MEM_SET( (VOS_INT8 *)pstCsqlvlCnf + VOS_MSG_HEAD_LENGTH, 0X00,
                 sizeof(TAF_MMA_CSQLVL_QRY_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 根据输入参数填充TAF_MMA_CSQLVL_QRY_CNF_STRU */
    pstCsqlvlCnf->ulReceiverPid          = pstCtrl->ulModuleId;
    pstCsqlvlCnf->ulMsgName              = ID_TAF_MMA_CSQLVL_QRY_CNF;
    PS_MEM_CPY(&pstCsqlvlCnf->stCtrl, pstCtrl, sizeof(TAF_MMA_CTRL_STRU));

    if ( TAF_ERR_NO_ERROR != enErrorCause)
    {
        pstCsqlvlCnf->enErrorCause= TAF_ERR_GET_CSQLVL_FAIL;

    }
    else
    {
        pstCsqlvlCnf->enErrorCause= TAF_ERR_NO_ERROR;
    }
    PS_MEM_CPY(&(pstCsqlvlCnf->stCsqLvlPara), pstCsqlvlPara, sizeof(TAF_MMA_CSQLVL_PARA_STRU));
    PS_MEM_CPY(&(pstCsqlvlCnf->stCsqLvlExtPara), stCsqLvlExtPara, sizeof(TAF_MMA_CSQLVLEXT_PARA_STRU));

    /* 发送消息 */
    PS_SEND_MSG(WUEPS_PID_MMA, pstCsqlvlCnf);
    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_SndAutoAttachSetCnf
 功能描述  : auto attach set 结果返回接口
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月30日
    作    者   : y00322978
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_SndAutoAttachSetCnf(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    TAF_PARA_SET_RESULT                 ucRslt
)
{
    TAF_MMA_AUTO_ATTACH_SET_CNF_STRU   *pstAutoAttachSetCnf;
    pstAutoAttachSetCnf = (TAF_MMA_AUTO_ATTACH_SET_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MMA,
                                                              sizeof(TAF_MMA_AUTO_ATTACH_SET_CNF_STRU));
    if (VOS_NULL_PTR == pstAutoAttachSetCnf)
    {
        MMA_ERRORLOG("TAF_MMA_SndAutoAttachSetCnf: ERROR:ALLOC MEMORY FAIL.");
        return;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstAutoAttachSetCnf + VOS_MSG_HEAD_LENGTH),
               0x00,
               (sizeof(TAF_MMA_AUTO_ATTACH_SET_CNF_STRU) - VOS_MSG_HEAD_LENGTH));

    /* 填写消息头部信息 */
    pstAutoAttachSetCnf->ulReceiverPid          = WUEPS_PID_AT;
    pstAutoAttachSetCnf->ulMsgName              = ID_TAF_MMA_AUTO_ATTACH_SET_CNF;
    PS_MEM_CPY(&pstAutoAttachSetCnf->stCtrl, pstCtrl, sizeof(TAF_MMA_CTRL_STRU));
    pstAutoAttachSetCnf->ucResult               = ucRslt;

    PS_SEND_MSG(WUEPS_PID_MMA, pstAutoAttachSetCnf);
    return;

}

/*****************************************************************************
 函 数 名  : TAF_MMA_SndCrpnQryCnf
 功能描述  : crpn qry 返回结果发送接口
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月30日
    作    者   : y00322978
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_SndCrpnQryCnf(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    TAF_MMA_CRPN_QRY_INFO_STRU         *pstMnMmaCrpnQryCnf,
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCause
)
{
    TAF_MMA_CRPN_QRY_CNF_STRU          *pstCrpnQryCnf;
    TAF_MMA_CRPN_QRY_INFO_STRU         *pData;

    pData = pstMnMmaCrpnQryCnf;

    pstCrpnQryCnf = (TAF_MMA_CRPN_QRY_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MMA,
                                                           sizeof(TAF_MMA_CRPN_QRY_CNF_STRU));
    if (VOS_NULL_PTR == pstCrpnQryCnf)
    {
        MMA_ERRORLOG("TAF_MMA_SndCrpnQryCnf: ERROR:ALLOC MEMORY FAIL.");
        return;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstCrpnQryCnf + VOS_MSG_HEAD_LENGTH),
               0x00,
               (sizeof(TAF_MMA_CRPN_QRY_CNF_STRU) - VOS_MSG_HEAD_LENGTH));

    /* 填写消息头部信息 */
    pstCrpnQryCnf->ulReceiverPid          = WUEPS_PID_AT;
    pstCrpnQryCnf->ulMsgName              = ID_TAF_MMA_CRPN_QRY_CNF;
    PS_MEM_CPY(&pstCrpnQryCnf->stCtrl, pstCtrl, sizeof(TAF_MMA_CTRL_STRU));
    pstCrpnQryCnf->enErrorCause               = enErrorCause;

    if (VOS_NULL_PTR != pData)
    {
        PS_MEM_CPY(&pstCrpnQryCnf->stCrpnQryInfo, pData, sizeof(TAF_MMA_CRPN_QRY_INFO_STRU));
    }

    PS_SEND_MSG(WUEPS_PID_MMA, pstCrpnQryCnf);
    return;

}


VOS_VOID TAF_MMA_SndBatteryCapacityQryCnf(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    TAF_MMA_BATTERYPOWER_STRU          *pstBatteryStatus
)
{
    TAF_MMA_BATTERY_CAPACITY_QRY_CNF_STRU                  *pstCbcQryCnf = VOS_NULL_PTR;

    /* 申请消息包TAF_MMA_CBC_QRY_CNF_STRU */
    pstCbcQryCnf = (TAF_MMA_BATTERY_CAPACITY_QRY_CNF_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                              WUEPS_PID_MMA,
                                              sizeof(TAF_MMA_BATTERY_CAPACITY_QRY_CNF_STRU));

    /* 内存申请失败，返回 */
    if (VOS_NULL_PTR == pstCbcQryCnf)
    {
        TAF_LOG(WUEPS_PID_MMA, VOS_NULL_PTR, PS_LOG_LEVEL_ERROR,
                "TAF_MMA_SndBatteryCapacityQryCnf: Memory Alloc Error for pstCbcQryCnf!");
        return;
    }

    PS_MEM_SET( (VOS_INT8 *)pstCbcQryCnf + VOS_MSG_HEAD_LENGTH, 0X00,
                (VOS_SIZE_T)(sizeof(TAF_MMA_BATTERY_CAPACITY_QRY_CNF_STRU) - VOS_MSG_HEAD_LENGTH) );

    /* 根据输入参数填充TAF_MMA_CBC_QRY_CNF_STRU */
    pstCbcQryCnf->ulReceiverPid          = pstCtrl->ulModuleId;
    pstCbcQryCnf->ulMsgName              = ID_TAF_MMA_BATTERY_CAPACITY_QRY_CNF;
    PS_MEM_CPY(&pstCbcQryCnf->stCtrl, pstCtrl, sizeof(TAF_MMA_CTRL_STRU));

    PS_MEM_CPY(&(pstCbcQryCnf->stBatteryStatus), pstBatteryStatus, sizeof(TAF_MMA_BATTERYPOWER_STRU));

    /* 发送消息 */
    PS_SEND_MSG(WUEPS_PID_MMA, pstCbcQryCnf);
}


VOS_VOID TAF_MMA_SndHandShakeQryCnf(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    VOS_UINT8                          *pPara
)
{
    TAF_MMA_HAND_SHAKE_QRY_CNF_STRU    *pstHsQryCnf = VOS_NULL_PTR;

    /* 申请消息包TAF_MMA_HS_QRY_CNF_STRU */
    pstHsQryCnf = (TAF_MMA_HAND_SHAKE_QRY_CNF_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                            WUEPS_PID_MMA,
                                            sizeof(TAF_MMA_HAND_SHAKE_QRY_CNF_STRU));

    /* 内存申请失败，返回 */
    if (VOS_NULL_PTR == pstHsQryCnf)
    {
        TAF_LOG(WUEPS_PID_MMA, VOS_NULL_PTR, PS_LOG_LEVEL_ERROR,
                "TAF_MMA_SndHandShakeQryCnf: Memory Alloc Error for pstHsQryCnf!");
        return;
    }

    PS_MEM_SET( (VOS_INT8 *)pstHsQryCnf + VOS_MSG_HEAD_LENGTH, 0X00,
                (VOS_SIZE_T)(sizeof(TAF_MMA_HAND_SHAKE_QRY_CNF_STRU) - VOS_MSG_HEAD_LENGTH) );

    /* 根据输入参数填充TAF_MMA_HS_QRY_CNF_STRU */
    pstHsQryCnf->ulReceiverPid          = pstCtrl->ulModuleId;
    pstHsQryCnf->ulMsgName              = ID_TAF_MMA_HAND_SHAKE_QRY_CNF;
    PS_MEM_CPY(&pstHsQryCnf->stCtrl, pstCtrl, sizeof(TAF_MMA_CTRL_STRU));

    PS_MEM_CPY(pstHsQryCnf->aucBuf, pPara, (sizeof(VOS_UINT8) * AT_HS_PARA_MAX_LENGTH));

    /* 发送消息 */
    PS_SEND_MSG(WUEPS_PID_MMA, pstHsQryCnf);
}

/*****************************************************************************
 函 数 名  : TAF_MMA_SndSrvStatusInd
 功能描述  : Mma Snd Service Status
 输入参数  : TAF_PHONE_CHANGED_SERVICE_STATUS    ucSrvStatus
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月31日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_SndSrvStatusInd(
    TAF_PHONE_CHANGED_SERVICE_STATUS    ucSrvStatus
)
{
    TAF_MMA_SRV_STATUS_IND_STRU        *pstSrvStatus;

    pstSrvStatus = (TAF_MMA_SRV_STATUS_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MMA,
                                                                             sizeof(TAF_MMA_SRV_STATUS_IND_STRU));
    if (VOS_NULL_PTR == pstSrvStatus)
    {
        MMA_ERRORLOG("TAF_MMA_SndSrvStatusInd: ERROR:ALLOC MEMORY FAIL.");
        return;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstSrvStatus + VOS_MSG_HEAD_LENGTH),
               0x00,
               (sizeof(TAF_MMA_SRV_STATUS_IND_STRU) - VOS_MSG_HEAD_LENGTH));

    /* 填写消息头部信息 */
    pstSrvStatus->ulReceiverPid = WUEPS_PID_AT;
    pstSrvStatus->ulMsgName     = ID_TAF_MMA_SRV_STATUS_IND;
    pstSrvStatus->usClientId    = MN_GetRealClientId(MMA_CLIENTID_BROADCAST, WUEPS_PID_MMA);
    pstSrvStatus->ucOpid        = MMA_OP_ID_INTERNAL;
    pstSrvStatus->ucSrvStatus   = ucSrvStatus;

    /* 发送消息 */
    PS_SEND_MSG(WUEPS_PID_MMA, pstSrvStatus);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_SndRegStatusInd
 功能描述  : Mma Snd Reg Status Ind
 输入参数  : TAF_PH_REG_STATE_STRU              *pstRegState
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月31日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_SndRegStatusInd(
    TAF_PH_REG_STATE_STRU              *pstRegState
)
{
    TAF_MMA_REG_STATUS_IND_STRU        *pstRegStatusInd;

    pstRegStatusInd = (TAF_MMA_REG_STATUS_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MMA,
                                                                                  sizeof(TAF_MMA_REG_STATUS_IND_STRU));
    if (VOS_NULL_PTR == pstRegStatusInd)
    {
        MMA_ERRORLOG("TAF_MMA_SndRegStatusInd: ERROR:ALLOC MEMORY FAIL.");
        return;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstRegStatusInd + VOS_MSG_HEAD_LENGTH),
               0x00,
               (sizeof(TAF_MMA_REG_STATUS_IND_STRU) - VOS_MSG_HEAD_LENGTH));

    /* 填写消息头部信息 */
    pstRegStatusInd->ulReceiverPid             = WUEPS_PID_AT;
    pstRegStatusInd->ulMsgName                 = ID_TAF_MMA_REG_STATUS_IND;
    pstRegStatusInd->usClientId                = MN_GetRealClientId(MMA_CLIENTID_BROADCAST, WUEPS_PID_MMA);
    pstRegStatusInd->ucOpId                    = MMA_OP_ID_INTERNAL;

    PS_MEM_CPY(&(pstRegStatusInd->stRegStatus), pstRegState, sizeof(TAF_PH_REG_STATE_STRU));

    /* 发送消息 */
    PS_SEND_MSG(WUEPS_PID_MMA, pstRegStatusInd);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_SndRegRejInfoInd
 功能描述  : Mma Snd Reg Rej Info IND
 输入参数  : TAF_PH_REG_REJ_INFO_STRU           *pstRejInfo
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月31日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_SndRegRejInd(
    TAF_PH_REG_REJ_INFO_STRU           *pstRejInfo
)
{
    TAF_MMA_REG_REJ_INFO_IND_STRU      *pstRegRejInd;

    pstRegRejInd = (TAF_MMA_REG_REJ_INFO_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MMA,
                                                                                 sizeof(TAF_MMA_REG_REJ_INFO_IND_STRU));
    if (VOS_NULL_PTR == pstRegRejInd)
    {
        MMA_ERRORLOG("TAF_MMA_SndRegRejInfoInd: ERROR:ALLOC MEMORY FAIL.");
        return;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstRegRejInd + VOS_MSG_HEAD_LENGTH),
               0x00,
               (sizeof(TAF_MMA_REG_REJ_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH));

    /* 填写消息头部信息 */
    pstRegRejInd->ulReceiverPid             = WUEPS_PID_AT;
    pstRegRejInd->ulMsgName                 = ID_TAF_MMA_REG_REJ_INFO_IND;
    pstRegRejInd->usClientId                = MN_GetRealClientId(MMA_CLIENTID_BROADCAST, WUEPS_PID_MMA);
    pstRegRejInd->ucOpId                    = MMA_OP_ID_INTERNAL;

    PS_MEM_CPY(&(pstRegRejInd->stRegRejInfo), pstRejInfo, sizeof(TAF_PH_REG_REJ_INFO_STRU));

    /* 发送消息 */
    PS_SEND_MSG(WUEPS_PID_MMA, pstRegRejInd);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_SndPlmnSelectionInd
 功能描述  : Mma snd plmn Select ind
 输入参数  : TAF_MMA_PLMN_SELECTION_INFO_STRU                        *pstPlmnSelectInfo
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月31日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_SndPlmnSelectionInd(
    TAF_MMA_PLMN_SELECTION_INFO_STRU    *pstPlmnSelectInfo
)
{
    TAF_MMA_PLMN_SElECTION_INFO_IND_STRU                   *pstPlmnSelecInd;

    pstPlmnSelecInd = (TAF_MMA_PLMN_SElECTION_INFO_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MMA,
                                                                                           sizeof(TAF_MMA_PLMN_SElECTION_INFO_IND_STRU));
    if (VOS_NULL_PTR == pstPlmnSelecInd)
    {
        MMA_ERRORLOG("TAF_MMA_SndRegRejInfoInd: ERROR:ALLOC MEMORY FAIL.");
        return;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstPlmnSelecInd + VOS_MSG_HEAD_LENGTH),
               0x00,
               (sizeof(TAF_MMA_PLMN_SElECTION_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH));

    /* 填写消息头部信息 */
    pstPlmnSelecInd->ulReceiverPid             = WUEPS_PID_AT;
    pstPlmnSelecInd->ulMsgName                 = ID_TAF_MMA_PLMN_SELECTION_INFO_IND;
    pstPlmnSelecInd->usClientId                = MN_GetRealClientId(MMA_CLIENTID_BROADCAST, WUEPS_PID_MMA);
    pstPlmnSelecInd->ucOpId                    = MMA_OP_ID_INTERNAL;

    PS_MEM_CPY(&(pstPlmnSelecInd->stPlmnSelectInfo), pstPlmnSelectInfo, sizeof(TAF_MMA_PLMN_SELECTION_INFO_STRU));

    /* 发送消息 */
    PS_SEND_MSG(WUEPS_PID_MMA, pstPlmnSelecInd);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_SndCipherQryCnf
 功能描述  : Mma Snd Cipher Qry Cnf
 输入参数  : VOS_UINT16                          usClientId
             VOS_UINT8                           ucOpId
             VOS_UINT32                          ulResult
             VOS_UINT8                           ucCipherInfo
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月16日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_SndCipherQryCnf(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT8                           ucCipherInfo,
    VOS_UINT32                          ulResult
)
{
    TAF_MMA_CIPHER_QRY_CNF_STRU        *pstCipherQryCnf;

    pstCipherQryCnf = (TAF_MMA_CIPHER_QRY_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                     WUEPS_PID_MMA,
                                                     sizeof(TAF_MMA_CIPHER_QRY_CNF_STRU));
    if( VOS_NULL_PTR == pstCipherQryCnf )
    {
        MMA_ERRORLOG("TAF_MMA_SndRegRejInfoInd: ERROR:ALLOC MEMORY FAIL.");
        return;
    }

    /* 初始化消息 */
    PS_MEM_SET((VOS_CHAR*)pstCipherQryCnf + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(TAF_MMA_CIPHER_QRY_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填写消息 */
    pstCipherQryCnf->ulReceiverPid          = WUEPS_PID_AT;
    pstCipherQryCnf->ulMsgName              = ID_TAF_MMA_CIPHER_QRY_CNF;
    pstCipherQryCnf->usClientId             = usClientId;
    pstCipherQryCnf->ucOpId                 = ucOpId;
    pstCipherQryCnf->ucCipherInfo           = ucCipherInfo;
    pstCipherQryCnf->ulResult               = ulResult;

    /* 发送消息 */
    PS_SEND_MSG(WUEPS_PID_MMA, pstCipherQryCnf);
}


VOS_VOID TAF_MMA_SndNetScanCnf(
    TAF_MMA_NET_SCAN_CNF_STRU          *pstRcvNetScanCnf
)
{
    TAF_MMA_NET_SCAN_CNF_STRU          *pstNetScanCnf = VOS_NULL_PTR;

    pstNetScanCnf = (TAF_MMA_NET_SCAN_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                 WUEPS_PID_MMA,
                                                 sizeof(TAF_MMA_NET_SCAN_CNF_STRU));
    if (VOS_NULL_PTR == pstNetScanCnf)
    {
        MMA_ERRORLOG("TAF_MMA_SendNetScanCnf:ERROR:ALLOC MEMORY FAIL.");
        return;
    }

    PS_MEM_SET( (VOS_UINT8 *)pstNetScanCnf + VOS_MSG_HEAD_LENGTH, 0x00,
                (VOS_SIZE_T)(sizeof(TAF_MMA_NET_SCAN_CNF_STRU) - VOS_MSG_HEAD_LENGTH) );

    PS_MEM_CPY(pstNetScanCnf, pstRcvNetScanCnf,sizeof(TAF_MMA_NET_SCAN_CNF_STRU));

    pstNetScanCnf->ulSenderPid            = WUEPS_PID_MMA;
    pstNetScanCnf->ulSenderCpuId          = VOS_LOCAL_CPUID;
    pstNetScanCnf->ulReceiverPid          = WUEPS_PID_AT;
    pstNetScanCnf->ulReceiverCpuId        = VOS_LOCAL_CPUID;
    pstNetScanCnf->ulLength               = sizeof(TAF_MMA_NET_SCAN_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstNetScanCnf->ulMsgName              = ID_TAF_MMA_NET_SCAN_CNF;

    /* Sending message */
    PS_SEND_MSG(WUEPS_PID_MMA, pstNetScanCnf);

    return;
}


/*****************************************************************************
 函 数 名  : TAF_MMA_SndAutoAttachQryCnf
 功能描述  : Mma Snd Auto Attach Qry Cnf
 输入参数  : TAF_MMA_CTRL_STRU                  *pstCtrl
             TAF_ERROR_CODE_ENUM_UINT32          enErrCause
             VOS_UINT8                           ucAutoAttachFlag
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月28日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_SndAutoAttachQryCnf(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCause,
    VOS_UINT8                           ucAutoAttachFlag
)
{
    TAF_MMA_AUTO_ATTACH_QRY_CNF_STRU         *pstAutoAttachQryCnf = VOS_NULL_PTR;

    /* 申请消息包TAF_MMA_AUTOATTACH_QRY_CNF_STRU */
    pstAutoAttachQryCnf = (TAF_MMA_AUTO_ATTACH_QRY_CNF_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                             WUEPS_PID_MMA,
                                                             sizeof(TAF_MMA_AUTO_ATTACH_QRY_CNF_STRU));

    /* 内存申请失败，返回 */
    if (VOS_NULL_PTR == pstAutoAttachQryCnf)
    {
        return;
    }

    PS_MEM_SET( (VOS_INT8 *)pstAutoAttachQryCnf + VOS_MSG_HEAD_LENGTH, 0X00,
                 sizeof(TAF_MMA_AUTO_ATTACH_QRY_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 根据输入参数填充TAF_MMA_AUTOATTACH_QRY_CNF_STRU */
    pstAutoAttachQryCnf->ulReceiverPid          = pstCtrl->ulModuleId;
    pstAutoAttachQryCnf->ulMsgName              = ID_TAF_MMA_AUTO_ATTACH_QRY_CNF;
    PS_MEM_CPY(&pstAutoAttachQryCnf->stCtrl, pstCtrl, sizeof(TAF_MMA_CTRL_STRU));

    pstAutoAttachQryCnf->enErrorCause             = enErrorCause;
    pstAutoAttachQryCnf->ucAutoAttachFlag       = ucAutoAttachFlag;

    /* 发送消息 */
    PS_SEND_MSG(WUEPS_PID_MMA, pstAutoAttachQryCnf);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_SndAttachCnf
 功能描述  : 发送ID_TAF_MMA_ATTACH_CNF消息
 输入参数  : TAF_MMA_CTRL_STRU                  *pstCtrl
             TAF_MMA_APP_OPER_RESULT_ENUM_UINT32 enRslt
             TAF_PHONE_ERROR                     usErrorCause
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月11日
    作    者   : l00301449
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_SndAttachCnf(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    TAF_MMA_APP_OPER_RESULT_ENUM_UINT32 enRslt,
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCause
)
{
    TAF_MMA_ATTACH_CNF_STRU            *pstAttachCnfMsg   = VOS_NULL_PTR;

    pstAttachCnfMsg = (TAF_MMA_ATTACH_CNF_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                          WUEPS_PID_MMA,
                                          sizeof(TAF_MMA_ATTACH_CNF_STRU));
    if (VOS_NULL_PTR == pstAttachCnfMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA,"TAF_MMA_SndAttachCnf:Alloc Msg Failed");
        return;
    }

    PS_MEM_SET( (VOS_INT8 *)pstAttachCnfMsg + VOS_MSG_HEAD_LENGTH, 0X00,
            sizeof(TAF_MMA_ATTACH_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstAttachCnfMsg->ulSenderCpuId            = VOS_LOCAL_CPUID;
    pstAttachCnfMsg->ulSenderPid              = WUEPS_PID_MMA;
    pstAttachCnfMsg->ulReceiverCpuId          = VOS_LOCAL_CPUID;
    pstAttachCnfMsg->ulReceiverPid            = pstCtrl->ulModuleId;
    pstAttachCnfMsg->enMsgName                = ID_TAF_MMA_ATTACH_CNF;
    pstAttachCnfMsg->stCtrl.usClientId        = pstCtrl->usClientId;
    pstAttachCnfMsg->stCtrl.ucOpId            = pstCtrl->ucOpId;
    pstAttachCnfMsg->stCtrl.ulModuleId        = pstCtrl->ulModuleId;
    pstAttachCnfMsg->enRslt                   = enRslt;
    pstAttachCnfMsg->enErrorCause             = enErrorCause;

    PS_SEND_MSG(WUEPS_PID_MMA, pstAttachCnfMsg);

    return;

}

/*****************************************************************************
 函 数 名  : TAF_MMA_SndAttachStatusQryCnf
 功能描述  : 发送ID_TAF_MMA_ATTACH_CNF消息
 输入参数  : TAF_MMA_ATTACH_STATUS_QRY_REQ_STRU *pstRcvMsg,
             TAF_MMA_APP_OPER_RESULT_ENUM_UINT32 enRslt,
             TAF_PHONE_ERROR                     usErrorCause,
             TAF_MMA_ATTACH_STATUS_ENUM_UINT8    enCsStatus,
             TAF_MMA_ATTACH_STATUS_ENUM_UINT8    enPsStatus
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月11日
    作    者   : h00313353
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_SndAttachStatusQryCnf(
    TAF_MMA_ATTACH_STATUS_QRY_REQ_STRU *pstRcvMsg,
    TAF_MMA_APP_OPER_RESULT_ENUM_UINT32 enRslt,
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCause,
    TAF_MMA_ATTACH_STATUS_ENUM_UINT8    enCsStatus,
    TAF_MMA_ATTACH_STATUS_ENUM_UINT8    enPsStatus
)
{
    TAF_MMA_ATTACH_STATUS_QRY_CNF_STRU *pstAttachStatusQryCnfMsg    = VOS_NULL_PTR;

    pstAttachStatusQryCnfMsg = (TAF_MMA_ATTACH_STATUS_QRY_CNF_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                          WUEPS_PID_MMA,
                                          sizeof(TAF_MMA_ATTACH_STATUS_QRY_CNF_STRU));
    if (VOS_NULL_PTR == pstAttachStatusQryCnfMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndAttachStatusQryCnf:Alloc Msg Failed");
        return;
    }

    PS_MEM_SET((VOS_INT8 *)pstAttachStatusQryCnfMsg + VOS_MSG_HEAD_LENGTH, 0X00,
            sizeof(TAF_MMA_ATTACH_STATUS_QRY_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstAttachStatusQryCnfMsg->ulSenderPid              = WUEPS_PID_MMA;
    pstAttachStatusQryCnfMsg->ulReceiverPid            = pstRcvMsg->stCtrl.ulModuleId;
    pstAttachStatusQryCnfMsg->enMsgName                = ID_TAF_MMA_ATTACH_STATUS_QRY_CNF;
    pstAttachStatusQryCnfMsg->stCtrl.usClientId        = pstRcvMsg->stCtrl.usClientId;
    pstAttachStatusQryCnfMsg->stCtrl.ucOpId            = pstRcvMsg->stCtrl.ucOpId;
    pstAttachStatusQryCnfMsg->stCtrl.ulModuleId        = pstRcvMsg->stCtrl.ulModuleId;
    pstAttachStatusQryCnfMsg->enRslt                   = enRslt;
    pstAttachStatusQryCnfMsg->enErrorCause             = enErrorCause;
    pstAttachStatusQryCnfMsg->enDomainType             = pstRcvMsg->enDomainType;
    pstAttachStatusQryCnfMsg->enCsStatus               = enCsStatus;
    pstAttachStatusQryCnfMsg->enPsStatus               = enPsStatus;

    PS_SEND_MSG(WUEPS_PID_MMA, pstAttachStatusQryCnfMsg);

    return;

}

/*****************************************************************************
 函 数 名  : TAF_MMA_ConvertMmlRatTypeToTafRatType
 功能描述  : 进行RAT类型转换:NAS_MML_NET_RAT_TYPE_ENUM_UINT8->TAF_PH_RAT_TYPE_ENUM_UINT8
 输入参数  : NAS_MML_NET_RAT_TYPE_ENUM_UINT8 enMmRatType MM层的RAT TYPE
 输出参数  : 无
 返 回 值  : TAF_PH_RAT_TYPE_ENUM_UINT8上报给TAF的RAT TYPE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月15日
    作    者   : h00285180
    修改内容   : 新增函数
*****************************************************************************/
TAF_MMA_RAT_TYPE_ENUM_UINT8 TAF_MMA_ConvertMmlRatTypeToTafRatType(
    NAS_MSCC_PIF_NET_RAT_TYPE_ENUM_UINT8                    enMmlRatType
)
{
    switch (enMmlRatType)
    {
        case NAS_MSCC_PIF_NET_RAT_TYPE_GSM:
             return TAF_MMA_RAT_GSM;

        case NAS_MSCC_PIF_NET_RAT_TYPE_WCDMA:
             return TAF_MMA_RAT_WCDMA;

        case NAS_MSCC_PIF_NET_RAT_TYPE_LTE:
             return TAF_MMA_RAT_LTE;

        case NAS_MSCC_PIF_NET_RAT_TYPE_1X:
             return TAF_MMA_RAT_1X;

        case NAS_MSCC_PIF_NET_RAT_TYPE_HRPD:
             return TAF_MMA_RAT_HRPD;

        default:
            TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_ConvertMmlRatTypeToTafRatType:WARNING: The input in invalid");
            return TAF_MMA_RAT_BUTT;
    }
}

/*****************************************************************************
 函 数 名  : TAF_MMA_SndDplmnQryCnf
 功能描述  : MMA给AT发送ID_TAF_MMA_DPLMN_QRY_CNF消息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月16日
    作    者   : n00355355
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_SndDplmnQryCnf(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    VOS_UINT8                          *pucVersion
)
{
    TAF_MMA_DPLMN_QRY_CNF_STRU         *pstSndMsg      = VOS_NULL_PTR;
    VOS_UINT32                          ulRst;

    /* 申请消息包*/
    pstSndMsg = (TAF_MMA_DPLMN_QRY_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                        WUEPS_PID_MMA,
                                        sizeof(TAF_MMA_DPLMN_QRY_CNF_STRU));
    if (VOS_NULL_PTR == pstSndMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA,"TAF_MMA_SndDplmnQryCnf:Alloc Msg Failed");
        return;
    }

    /* 清空消息内容 */
    PS_MEM_SET((VOS_INT8 *)pstSndMsg + VOS_MSG_HEAD_LENGTH,
                0x00,
                sizeof(TAF_MMA_DPLMN_QRY_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填写消息头*/
    pstSndMsg->ulSenderCpuId            = VOS_LOCAL_CPUID;
    pstSndMsg->ulSenderPid              = WUEPS_PID_MMA;
    pstSndMsg->ulReceiverCpuId          = VOS_LOCAL_CPUID;
    pstSndMsg->ulReceiverPid            = WUEPS_PID_AT;
    pstSndMsg->ulMsgName                = ID_TAF_MMA_DPLMN_QRY_CNF;
    pstSndMsg->stCtrl.usClientId        = pstCtrl->usClientId;
    pstSndMsg->stCtrl.ucOpId            = pstCtrl->ucOpId;
    pstSndMsg->stCtrl.ulModuleId        = pstCtrl->ulModuleId;

    /* 填写消息内容*/
    PS_MEM_CPY( pstSndMsg->aucVersionId, pucVersion, sizeof(VOS_UINT8) * NAS_VERSION_LEN);

    /* 发送消息*/
    ulRst = PS_SEND_MSG(WUEPS_PID_MMA, pstSndMsg);
    if (VOS_OK != ulRst)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA,"TAF_MMA_SndDplmnQryCnf:Send Msg Failed");
    }

    return;
}


/*****************************************************************************
 函 数 名  : TAF_MMA_SndDplmnSetCnf
 功能描述  : MMA给AT发送ID_TAF_MMA_DPLMN_SET_CNF 消息
 输入参数  : TAF_MMA_CTRL_STRU                  *pstCtrl
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月12日
    作    者   : n00355355
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_SndDplmnSetCnf(
    VOS_UINT32                          ulRslt,
    TAF_MMA_CTRL_STRU                   stCtrl
)
{
    TAF_MMA_DPLMN_SET_CNF_STRU         *pstSndMsg      = VOS_NULL_PTR;
    VOS_UINT32                          ulRst;

    /* 申请消息包 */
    pstSndMsg = (TAF_MMA_DPLMN_SET_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                        WUEPS_PID_MMA,
                                        sizeof(TAF_MMA_DPLMN_SET_CNF_STRU));
    if (VOS_NULL_PTR == pstSndMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA,"TAF_MMA_SndDplmnSetCnf:Alloc Msg Failed");
        return;
    }

    /* 清空消息内容 */
    PS_MEM_SET((VOS_INT8 *)pstSndMsg + VOS_MSG_HEAD_LENGTH,
                0x00,
                sizeof(TAF_MMA_DPLMN_SET_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填写消息头 */
    pstSndMsg->ulSenderCpuId            = VOS_LOCAL_CPUID;
    pstSndMsg->ulSenderPid              = WUEPS_PID_MMA;
    pstSndMsg->ulReceiverCpuId          = VOS_LOCAL_CPUID;
    pstSndMsg->ulReceiverPid            = WUEPS_PID_AT;
    pstSndMsg->ulMsgName                = ID_TAF_MMA_DPLMN_SET_CNF;
    pstSndMsg->stCtrl.usClientId        = stCtrl.usClientId;
    pstSndMsg->stCtrl.ulModuleId        = stCtrl.ulModuleId;
    pstSndMsg->stCtrl.ucOpId            = stCtrl.ucOpId;

    /* 填写消息内容 */
    pstSndMsg->ulRslt                   = ulRslt;

    /* 发送消息 */
    ulRst = PS_SEND_MSG(WUEPS_PID_MMA, pstSndMsg);
    if (VOS_OK != ulRst)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA,"TAF_MMA_SndDplmnSetCnf:Send Msg Failed");
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_SndSrchedPlmnInfoInd
 功能描述  : 向AT发送 searched plmn info
 输入参数  : MSCC_MMA_SRCHED_PLMN_INFO_IND_STRU  *pstSrchedPlmnInfoInd
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月15日
    作    者   : h00285180
    修改内容   : 新增函数
*****************************************************************************/
VOS_VOID TAF_MMA_SndSrchedPlmnInfoInd(
    MSCC_MMA_SRCHED_PLMN_INFO_IND_STRU *pstSrchedPlmnInfoInd
)
{
    TAF_MMA_SRCHED_PLMN_INFO_IND_STRU  *pstSndMsg      = VOS_NULL_PTR;
    VOS_UINT32                          i;
    VOS_UINT32                          ulRst;

    pstSndMsg = (TAF_MMA_SRCHED_PLMN_INFO_IND_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                         WUEPS_PID_MMA,
                                         sizeof(TAF_MMA_SRCHED_PLMN_INFO_IND_STRU));
    if (VOS_NULL_PTR == pstSndMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA,"TAF_MMA_SndSrchedPlmnInfoInd:Alloc Msg Failed");
        return;
    }
    PS_MEM_SET( (VOS_INT8 *)pstSndMsg + VOS_MSG_HEAD_LENGTH, 0X00,
            sizeof(TAF_MMA_SRCHED_PLMN_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填充上报事件 */
    pstSndMsg->ulSenderCpuId            = VOS_LOCAL_CPUID;
    pstSndMsg->ulSenderPid              = WUEPS_PID_MMA;
    pstSndMsg->ulReceiverCpuId          = VOS_LOCAL_CPUID;
    pstSndMsg->ulReceiverPid            = WUEPS_PID_AT;
    pstSndMsg->ulMsgName                = ID_TAF_MMA_SRCHED_PLMN_INFO_IND;
    pstSndMsg->usClientId               = MN_GetRealClientId(MMA_CLIENTID_BROADCAST, WUEPS_PID_MMA);
    pstSndMsg->ucOpid                   = MMA_OP_ID_INTERNAL;

    pstSndMsg->enRat = TAF_MMA_ConvertMmlRatTypeToTafRatType(pstSrchedPlmnInfoInd->enRat);

    if (MSCC_MMA_MAX_SRCHED_LAI_NUM < pstSrchedPlmnInfoInd->ulLaiNum)
    {
        pstSrchedPlmnInfoInd->ulLaiNum = MSCC_MMA_MAX_SRCHED_LAI_NUM;
    }
    pstSndMsg->ulLaiNum = pstSrchedPlmnInfoInd->ulLaiNum;
    if (TAF_MMA_MAX_SRCHED_LAI_NUM < pstSndMsg->ulLaiNum)
    {
        pstSndMsg->ulLaiNum = TAF_MMA_MAX_SRCHED_LAI_NUM;
    }

    for (i = 0; i < pstSndMsg->ulLaiNum; i++)
    {
        pstSndMsg->astLai[i].stPlmnId.Mcc = pstSrchedPlmnInfoInd->astLai[i].stPlmnId.ulMcc;
        pstSndMsg->astLai[i].stPlmnId.Mnc = pstSrchedPlmnInfoInd->astLai[i].stPlmnId.ulMnc;

        /* 将PLMN ID转为BCD格式 */
        MMA_PlmnId2Bcd(&pstSndMsg->astLai[i].stPlmnId);

        pstSndMsg->astLai[i].usLac        = pstSrchedPlmnInfoInd->astLai[i].usLac;
    }

    ulRst = PS_SEND_MSG(WUEPS_PID_MMA, pstSndMsg);
    if (VOS_OK != ulRst)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA,"TAF_MMA_SndSrchedPlmnInfoInd:Send Msg Failed");
    }
}


/*****************************************************************************
 函 数 名  : TAF_MMA_SndAtInitLocInfoInd
 功能描述  : 向AT发送TAF_MMA_INIT_LOC_INFO_IND信息，上报初搜的lte的国家码和x模的sid信息，帮助AP侧确定是否是漫游
 输入参数  : VOS_UINT32       ulMcc
             VOS_INT32        lSid
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月10日
    作    者   : l00324781
    修改内容   : 新增函数
*****************************************************************************/
VOS_VOID TAF_MMA_SndAtInitLocInfoInd(
    VOS_UINT32                          ulMcc,
    VOS_INT32                           lSid
)
{
    TAF_MMA_INIT_LOC_INFO_IND_STRU     *pstInitLocInfoInd = VOS_NULL_PTR;

    /* 申请消息包TAF_MMA_INIT_LOC_INFO_IND_STRU */
    pstInitLocInfoInd = (TAF_MMA_INIT_LOC_INFO_IND_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                           WUEPS_PID_MMA,
                                           sizeof(TAF_MMA_INIT_LOC_INFO_IND_STRU));
    /* 内存申请失败，返回 */
    if (VOS_NULL_PTR == pstInitLocInfoInd)
    {
        return;
    }

    PS_MEM_SET( (VOS_INT8 *)pstInitLocInfoInd + VOS_MSG_HEAD_LENGTH, 0X00,
            sizeof(TAF_MMA_INIT_LOC_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填写消息头部信息 */
    pstInitLocInfoInd->ulReceiverPid = WUEPS_PID_AT;
    pstInitLocInfoInd->ulMsgName     = ID_TAF_MMA_INIT_LOC_INFO_IND;
    pstInitLocInfoInd->usClientId    = MN_GetRealClientId(MMA_CLIENTID_BROADCAST, WUEPS_PID_TAF);
    pstInitLocInfoInd->ucOpid        = MMA_OP_ID_INTERNAL;
    pstInitLocInfoInd->ulMcc         = ulMcc;
    pstInitLocInfoInd->lSid          = lSid;

     /* 发送消息 */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_MMA, pstInitLocInfoInd))
    {
        MMA_ERRORLOG("TAF_MMA_SndInitLocInfoInd: Send Msg Error!");
    }

    return;
}

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif



