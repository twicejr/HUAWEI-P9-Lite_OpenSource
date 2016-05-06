/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasMsccSndMma.c
  版 本 号   : 初稿
  作    者   : y00245242
  生成日期   : 2015年01月27日
  功能描述   : MSCC发送IMSA消息处理
  函数列表   :
  修改历史   :
  1.日    期   : 2015年01月27日
    作    者   : y00245242
    修改内容   : 创建文件
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "NasMsccSndMmc.h"
#include "NasMntn.h"
#include "NasMsccCtx.h"
#include "NasComm.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_NAS_MSCC_SND_MMC_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数定义
*****************************************************************************/
/*****************************************************************************
 函 数 名  : NAS_MSCC_SndMmcImsVoiceCapNotify
 功能描述  : 向mmc发送IMS VOICE CAP消息
 输入参数  : ucImsVoiceAvail           -IMS voice是否可用
             ucIsExistPersistentBearer -persistent eps bearer是否存在标识
 输出参数  : 无
 返 回 值  : 无
 被调函数  :

 修改历史      :
 1.日    期   : 2014年01月27日
   作    者   : y00245242
   修改内容   : 新生成函数
 2.日    期   : 2015年4月25日
   作    者   : z00161729
   修改内容   : 24301 R11 CR升级项目修改
*****************************************************************************/
VOS_VOID NAS_MSCC_SndMmcImsVoiceCapNotify(
    VOS_UINT8                           ucImsVoiceAvail,
    VOS_UINT8                           ucIsExistPersistentBearer
)
{
    MSCC_MMC_IMS_VOICE_CAP_NOTIFY_STRU    *pstMsg = VOS_NULL_PTR;

    /* 申请内存  */
    pstMsg = (MSCC_MMC_IMS_VOICE_CAP_NOTIFY_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                sizeof(MSCC_MMC_IMS_VOICE_CAP_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmcImsVoiceCapNotify: Memory Alloc Error for pMsg");

        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,
                0,
               sizeof(MSCC_MMC_IMS_VOICE_CAP_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->MsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid    = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->MsgHeader.ulLength         = sizeof(MSCC_MMC_IMS_VOICE_CAP_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName        = ID_MSCC_MMC_IMS_VOICE_CAP_NOTIFY;
    pstMsg->ucAvail                    = ucImsVoiceAvail;

    pstMsg->ucIsExistPersistentBearer  = ucIsExistPersistentBearer;

    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* 调用VOS发送原语 */
    PS_SEND_MSG(UEPS_PID_MSCC, pstMsg);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_SndMmcSignalReportReq
 功能描述  : 向mmc发送信号上报配置消息
 输入参数  : pstSigReportReq
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年1月29日
   作    者   : l00208516
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MSCC_SndMmcSignalReportReq(
    MMA_MSCC_SIGN_REPORT_REQ_STRU      *pstSigReportReq
)
{
    MSCC_MMC_SIGN_REPORT_REQ_STRU      *pstMsg = VOS_NULL_PTR;

    /* 申请内存  */
    pstMsg = (MSCC_MMC_SIGN_REPORT_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                           sizeof(MSCC_MMC_SIGN_REPORT_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmcSignalReportReq:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MSCC_MMC_SIGN_REPORT_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->MsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid    = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->MsgHeader.ulLength         = sizeof(MSCC_MMC_SIGN_REPORT_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName        = ID_MSCC_MMC_SIGN_REPORT_REQ;
    pstMsg->ucActionType               = pstSigReportReq->ucActionType;
    pstMsg->ucRrcMsgType               = pstSigReportReq->ucRrcMsgType;
    pstMsg->ucSignThreshold            = pstSigReportReq->ucSignThreshold;
    pstMsg->ucMinRptTimerInterval      = pstSigReportReq->ucMinRptTimerInterval;


    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* 调用VOS发送原语 */
    PS_SEND_MSG( UEPS_PID_MSCC, pstMsg );

    return;

}
/*****************************************************************************
 函 数 名  : NAS_MSCC_SndMmcModeChangeReq
 功能描述  : 向mmc发送模式变更消息
 输入参数  : pstModeChangeReq
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年1月29日
   作    者   : l00208516
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MSCC_SndMmcModeChangeReq(
    MMA_MSCC_MODE_CHANGE_REQ_STRU      *pstModeChangeReq
)
{
    MSCC_MMC_MODE_CHANGE_REQ_STRU      *pstMsg = VOS_NULL_PTR;

    /* 申请内存  */
    pstMsg = (MSCC_MMC_MODE_CHANGE_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                           sizeof(MSCC_MMC_MODE_CHANGE_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmcModeChangeReq:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MSCC_MMC_MODE_CHANGE_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->MsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid    = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->MsgHeader.ulLength         = sizeof(MSCC_MMC_MODE_CHANGE_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName        = ID_MSCC_MMC_MODE_CHANGE_REQ;
    pstMsg->enMsMode                   = pstModeChangeReq->enMsMode;

    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* 调用VOS发送原语 */
    PS_SEND_MSG( UEPS_PID_MSCC, pstMsg );

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_SndMmcAttachReq
 功能描述  : 向mmc发送attach请求消息
 输入参数  : pstAttachReq
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年1月29日
   作    者   : l00208516
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MSCC_SndMmcAttachReq(
    MMA_MSCC_ATTACH_REQ_STRU           *pstAttachReq
)
{
    MSCC_MMC_ATTACH_REQ_STRU           *pstMsg = VOS_NULL_PTR;

    /* 申请内存  */
    pstMsg = (MSCC_MMC_ATTACH_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                           sizeof(MSCC_MMC_ATTACH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmcAttachReq:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MSCC_MMC_ATTACH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->MsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid    = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->MsgHeader.ulLength         = sizeof(MSCC_MMC_ATTACH_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName        = ID_MSCC_MMC_ATTACH_REQ;
    pstMsg->ulOpID                     = pstAttachReq->ulOpID;
    pstMsg->enAttachType               = pstAttachReq->enAttachType;
    pstMsg->enEpsAttachReason          = pstAttachReq->enEpsAttachReason;

    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* 调用VOS发送原语 */
    PS_SEND_MSG( UEPS_PID_MSCC, pstMsg );

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_SndMmcDetachReq
 功能描述  : 向mmc发送detach请求消息
 输入参数  : pstDetachReq
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年1月29日
   作    者   : l00208516
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MSCC_SndMmcDetachReq(
    MMA_MSCC_DETACH_REQ_STRU           *pstDetachReq
)
{
    MSCC_MMC_DETACH_REQ_STRU           *pstMsg = VOS_NULL_PTR;

    /* 申请内存  */
    pstMsg = (MSCC_MMC_DETACH_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                           sizeof(MSCC_MMC_DETACH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmcDetachReq:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MSCC_MMC_DETACH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->MsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid    = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->MsgHeader.ulLength         = sizeof(MSCC_MMC_DETACH_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName        = ID_MSCC_MMC_DETACH_REQ;
    pstMsg->ulOpID                     = pstDetachReq->ulOpID;
    pstMsg->enDetachType               = pstDetachReq->enDetachType;
    pstMsg->enDetachReason             = pstDetachReq->enDetachReason;

    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* 调用VOS发送原语 */
    PS_SEND_MSG( UEPS_PID_MSCC, pstMsg );

    return;
}

#if (FEATURE_ON == FEATURE_CSG)
/*****************************************************************************
 函 数 名  : NAS_MSCC_SndMmcCsgListSearchReq
 功能描述  : 向mmc发送CSG list搜网请求消息
 输入参数  : pstCsgListSearchReq - csg list搜网请求消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年9月10日
   作    者   : z00161729
   修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_VOID NAS_MSCC_SndMmcCsgListSearchReq(
    MMA_MSCC_CSG_LIST_SEARCH_REQ_STRU  *pstCsgListSearchReq
)
{
    MSCC_MMC_CSG_LIST_SEARCH_REQ_STRU   *pstMsg = VOS_NULL_PTR;

    /* 申请内存  */
    pstMsg = (MSCC_MMC_CSG_LIST_SEARCH_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                           sizeof(MSCC_MMC_CSG_LIST_SEARCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmcCsgListSearchReq:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MSCC_MMC_CSG_LIST_SEARCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->MsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid    = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->MsgHeader.ulLength         = sizeof(MSCC_MMC_CSG_LIST_SEARCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName        = ID_MSCC_MMC_CSG_LIST_SEARCH_REQ;

    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* 调用VOS发送原语 */
    PS_SEND_MSG( UEPS_PID_MSCC, pstMsg );

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_SndMmcCsgListAbortReq
 功能描述  : 向mmc发送CSG list搜网终止请求消息
 输入参数  : pstCsgListAbortReq - csg list abort请求
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年9月10日
   作    者   : z00161729
   修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_VOID NAS_MSCC_SndMmcCsgListAbortReq(
    MMA_MSCC_CSG_LIST_ABORT_REQ_STRU   *pstCsgListAbortReq
)
{
    MSCC_MMC_CSG_LIST_ABORT_REQ_STRU   *pstMsg = VOS_NULL_PTR;

    /* 申请内存  */
    pstMsg = (MSCC_MMC_CSG_LIST_ABORT_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                           sizeof(MSCC_MMC_CSG_LIST_ABORT_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmcCsgListAbortReq:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MSCC_MMC_CSG_LIST_ABORT_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->MsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid    = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->MsgHeader.ulLength         = sizeof(MSCC_MMC_CSG_LIST_ABORT_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName        = ID_MSCC_MMC_CSG_LIST_ABORT_REQ;

    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* 调用VOS发送原语 */
    PS_SEND_MSG( UEPS_PID_MSCC, pstMsg );

    return;
}
#endif

/*****************************************************************************
 函 数 名  : NAS_MSCC_SndMmcPlmnListReq
 功能描述  : 向mmc发送list搜网请求消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年1月29日
   作    者   : l00208516
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MSCC_SndMmcPlmnListReq(VOS_VOID)
{
    MSCC_MMC_PLMN_LIST_REQ_STRU        *pstMsg = VOS_NULL_PTR;

    /* 申请内存  */
    pstMsg = (MSCC_MMC_PLMN_LIST_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                           sizeof(MSCC_MMC_PLMN_LIST_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmcPlmnListReq:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MSCC_MMC_PLMN_LIST_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->MsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid    = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->MsgHeader.ulLength         = sizeof(MSCC_MMC_PLMN_LIST_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName        = ID_MSCC_MMC_PLMN_LIST_REQ;

    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* 调用VOS发送原语 */
    PS_SEND_MSG( UEPS_PID_MSCC, pstMsg );

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_SndMmcPlmnListAbortReq
 功能描述  : 向mmc发送list搜网中止请求消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_OK : 消息发送成功
             VOS_ERR: 消息发送失败
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年1月29日
   作    者   : l00208516
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MSCC_SndMmcPlmnListAbortReq(VOS_VOID)
{
    MSCC_MMC_PLMN_LIST_ABORT_REQ_STRU  *pstMsg = VOS_NULL_PTR;

    /* 申请内存  */
    pstMsg = (MSCC_MMC_PLMN_LIST_ABORT_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                           sizeof(MSCC_MMC_PLMN_LIST_ABORT_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmcPlmnListAbortReq:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MSCC_MMC_PLMN_LIST_ABORT_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->MsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid    = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->MsgHeader.ulLength         = sizeof(MSCC_MMC_PLMN_LIST_ABORT_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName        = ID_MSCC_MMC_PLMN_LIST_ABORT_REQ;

    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* 调用VOS发送原语 */
    PS_SEND_MSG( UEPS_PID_MSCC, pstMsg );

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_SndMmcPlmnUserReselReq
 功能描述  : 向mmc发送重选请求消息
 输入参数  : pstPlmnUserReselReq
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年1月29日
   作    者   : l00208516
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MSCC_SndMmcPlmnUserReselReq(
    MMA_MSCC_PLMN_USER_RESEL_REQ_STRU  *pstPlmnUserReselReq
)
{
    MSCC_MMC_PLMN_USER_RESEL_REQ_STRU  *pstMsg = VOS_NULL_PTR;

    /* 申请内存  */
    pstMsg = (MSCC_MMC_PLMN_USER_RESEL_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                           sizeof(MSCC_MMC_PLMN_USER_RESEL_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmcPlmnUserReselReq:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MSCC_MMC_PLMN_USER_RESEL_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->MsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid    = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->MsgHeader.ulLength         = sizeof(MSCC_MMC_PLMN_USER_RESEL_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName        = ID_MSCC_MMC_PLMN_USER_RESEL_REQ;
    pstMsg->enPlmnSelMode              = pstPlmnUserReselReq->enPlmnSelMode;

    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* 调用VOS发送原语 */
    PS_SEND_MSG( UEPS_PID_MSCC, pstMsg );


    return;
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_SndMmcPlmnSpecialReq
 功能描述  : 向mmc发送指定搜网请求
 输入参数  : pstPlmnId    - 指定搜plmn id
             enAccessMode - 接入技术
 输出参数  : 无
 返 回 值  : VOS_OK : 消息发送成功
             VOS_ERR: 消息发送失败
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年1月29日
   作    者   : l00208516
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MSCC_SndMmcPlmnSpecialReq(
    MMA_MSCC_PLMN_SPECIAL_REQ_STRU     *pstPlmnSpecialReq
)
{
    MSCC_MMC_PLMN_SPECIAL_REQ_STRU     *pstMsg = VOS_NULL_PTR;

    pstMsg = (MSCC_MMC_PLMN_SPECIAL_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                           sizeof(MSCC_MMC_PLMN_SPECIAL_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmcPlmnSpecialReq:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MSCC_MMC_PLMN_SPECIAL_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->MsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid    = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->MsgHeader.ulLength         = sizeof(MSCC_MMC_PLMN_SPECIAL_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName        = ID_MSCC_MMC_PLMN_SPECIAL_REQ;
    pstMsg->stPlmnId                   = pstPlmnSpecialReq->stPlmnId;
    pstMsg->enAccessMode               = pstPlmnSpecialReq->enAccessMode;

    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* 调用VOS发送原语 */
    PS_SEND_MSG( UEPS_PID_MSCC, pstMsg );

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_SndMmcSysCfgReq
 功能描述  : 发送syscfg请求消息
 输入参数  : pstSysCfgReq
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :


 修改历史      :
 1.日    期   : 2015年1月29日
   作    者   : l00208516
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  NAS_MSCC_SndMmcSysCfgReq(
    MMA_MSCC_SYS_CFG_SET_REQ_STRU      *pstSysCfgReq
)
{
    MSCC_MMC_SYS_CFG_SET_REQ_STRU      *pstMsg = VOS_NULL_PTR;

    /* 申请消息内存 */
    pstMsg = (MSCC_MMC_SYS_CFG_SET_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                           sizeof(MSCC_MMC_SYS_CFG_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        /* 内存申请失败 */
        NAS_ERROR_LOG(UEPS_PID_MSCC,"NAS_MSCC_SndMmcSysCfgReq():ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MSCC_MMC_SYS_CFG_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->MsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid         = UEPS_PID_MSCC;
    pstMsg->MsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid       = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulMsgName           = ID_MSCC_MMC_SYS_CFG_SET_REQ;

    pstMsg->ucOnlyRoamParaChanged         = VOS_FALSE;

    /*漫游参数填写*/
    pstMsg->enRoamCapability              = pstSysCfgReq->enRoamCapability;

    /*接入模式pMsg->stRatPrioList参数填写*/
    PS_MEM_CPY(&(pstMsg->stRatPrioList), &(pstSysCfgReq->stRatPrioList), sizeof(NAS_MSCC_PIF_RAT_PRIO_STRU));

    /* GU频带设置参数填写*/
    pstMsg->stBand.unGsmBand.ulBand        = pstSysCfgReq->stBand.unGsmBand.ulBand;
    pstMsg->stBand.unWcdmaBand.ulBand      = pstSysCfgReq->stBand.unWcdmaBand.ulBand;

    pstMsg->stBand.unCdmaBand.ulCdmaBand   = pstSysCfgReq->stBand.unCdmaBand.ulCdmaBand;

    /* L频段设置参数填写 */
    pstMsg->stBand.stLteBand.aulLteBand[0] = pstSysCfgReq->stBand.stLteBand.aulLteBand[0];
    pstMsg->stBand.stLteBand.aulLteBand[1] = pstSysCfgReq->stBand.stLteBand.aulLteBand[1];

    pstMsg->ucOnlyRoamParaChanged = pstSysCfgReq->ucOnlyRoamParaChanged;

    pstMsg->ucIsNeedAttachPs = pstSysCfgReq->ucIsNeedAttachPs;

    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /*消息发送*/
    PS_SEND_MSG(UEPS_PID_MSCC, pstMsg);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_SndMmcNetScanMsgReq
 功能描述  : MSCC模块通知MMC模块NetScanReq消息
 输入参数  : pstNetScanReq
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年1月29日
   作    者   : l00208516
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MSCC_SndMmcNetScanMsgReq(
    MMA_MSCC_NET_SCAN_REQ_STRU         *pstNetScanReq
)
{
    MSCC_MMC_NET_SCAN_REQ_STRU         *pstMsg              = VOS_NULL_PTR;

    /* 申请消息内存 */
    pstMsg = (MSCC_MMC_NET_SCAN_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                           sizeof(MSCC_MMC_NET_SCAN_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        /* 内存申请失败 */
        NAS_ERROR_LOG(UEPS_PID_MSCC,"NAS_MSCC_SndNetScanMsgReq():ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MSCC_MMC_NET_SCAN_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid       = UEPS_PID_MSCC;
    pstMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid     = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulLength          = sizeof(MSCC_MMC_NET_SCAN_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName         = ID_MSCC_MMC_NET_SCAN_REQ;

    /* GU频带设置参数填写 */
    pstMsg->stBand.unGsmBand.ulBand     = pstNetScanReq->stBand.unGsmBand.ulBand;
    pstMsg->stBand.unWcdmaBand.ulBand   = pstNetScanReq->stBand.unWcdmaBand.ulBand;
    pstMsg->sCellPow                    = pstNetScanReq->sCellPow;
    pstMsg->usCellNum                   = pstNetScanReq->usCellNum;
    pstMsg->ucRat                       = pstNetScanReq->ucRat;

    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /*消息发送*/
    PS_SEND_MSG( UEPS_PID_MSCC, pstMsg);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_SndMmcAbortNetScanMsgReq
 功能描述  : MSCC模块通知MMC模块打断NetScanReq消息
 输入参数  : pstAbortScanMsgReq
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年1月29日
   作    者   : l00208516
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MSCC_SndMmcAbortNetScanMsgReq(VOS_VOID)
{
    MSCC_MMC_ABORT_NET_SCAN_REQ_STRU   *pstMsg              = VOS_NULL_PTR;

    /* 申请消息内存 */
    pstMsg = (MSCC_MMC_ABORT_NET_SCAN_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                           sizeof(MSCC_MMC_ABORT_NET_SCAN_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        /* 内存申请失败 */
        NAS_ERROR_LOG(UEPS_PID_MSCC,"NAS_MSCC_SndMmcAbortNetScanMsgReq():ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MSCC_MMC_ABORT_NET_SCAN_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid       = UEPS_PID_MSCC;
    pstMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid     = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulLength          = sizeof(MSCC_MMC_ABORT_NET_SCAN_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName         = ID_MSCC_MMC_ABORT_NET_SCAN_REQ;

    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /*消息发送*/
    PS_SEND_MSG( UEPS_PID_MSCC, pstMsg);

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MSCC_SndMmcPlmnSearchReq
 功能描述  : 向mmc发送开机搜网请求消息
 输入参数  : enAcqReason           -- 搜网原因值
             enSrchType            ---搜索类型
             pstInitAcqPlmnInfo    ---初始搜网的PLMN信息
             pstHighPrioPlmnInfo   ---高优先级的PLMN信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年1月29日
   作    者   : l00208516
   修改内容   : 新生成函数
 2.日    期   : 2/4/2015
   作    者   : w00176964
   修改内容   : CDMA Iteration 10 Modified
   修改内容   : 新生成函数
 3.日    期   : 30/5/2015
   作    者   : w00176964
   修改内容   : CDMA Iteration 12
 4.日    期   : 2015/12/11
   作    者   : w00176964
   修改内容   : CL_MUTIMODE_OPTIMIZE调整
*****************************************************************************/
VOS_VOID NAS_MSCC_SndMmcPlmnSearchReq(
    NAS_MSCC_PIF_ACQ_REASON_ENUM_UINT32                     enAcqReason,
    NAS_MSCC_PIF_PLMN_SEARCH_TYPE_ENUM_UINT32               enSrchType,
    NAS_MSCC_PIF_INIT_ACQ_PLMN_INFO_STRU                   *pstInitAcqPlmnInfo,
    NAS_MSCC_PIF_SEARCHED_PLMN_LIST_INFO_STRU              *pstHighPrioPlmnInfo
)
{
    MSCC_MMC_PLMN_SEARCH_REQ_STRU      *pstMsg = VOS_NULL_PTR;

    /* 申请内存  */
    pstMsg = (MSCC_MMC_PLMN_SEARCH_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                           sizeof(MSCC_MMC_PLMN_SEARCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmcPlmnSearchReq:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MSCC_MMC_PLMN_SEARCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->MsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid    = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->MsgHeader.ulLength         = sizeof(MSCC_MMC_PLMN_SEARCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName        = ID_MSCC_MMC_PLMN_SEARCH_REQ;

    pstMsg->enSrchType = enSrchType;

    pstMsg->enAcqReason = enAcqReason;

    if ((NAS_MSCC_PIF_ACQ_REASON_POWER_UP == enAcqReason)
     && (VOS_NULL_PTR                     != pstInitAcqPlmnInfo))
    {
        PS_MEM_CPY(&(pstMsg->stInitAcqPlmnInfo), pstInitAcqPlmnInfo, sizeof(NAS_MSCC_PIF_INIT_ACQ_PLMN_INFO_STRU));
    }

    if ((NAS_MSCC_PIF_ACQ_REASON_HIGH_PRIORITY == enAcqReason)
     && (VOS_NULL_PTR                          != pstHighPrioPlmnInfo))
    {
        PS_MEM_CPY(&(pstMsg->stHighPrioPlmnList), pstHighPrioPlmnInfo, sizeof(NAS_MSCC_PIF_SEARCHED_PLMN_LIST_INFO_STRU));
    }
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* 调用VOS发送原语 */
    PS_SEND_MSG( UEPS_PID_MSCC, pstMsg );

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_SndMmcSpecPlmnSearchAbortReq
 功能描述  : 向mmc发送指定搜网中止请求消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年1月29日
   作    者   : l00208516
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MSCC_SndMmcSpecPlmnSearchAbortReq(VOS_VOID)
{
    MSCC_MMC_SPEC_PLMN_SEARCH_ABORT_REQ_STRU               *pstMsg = VOS_NULL_PTR;

    /* 申请内存  */
    pstMsg = (MSCC_MMC_SPEC_PLMN_SEARCH_ABORT_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                           sizeof(MSCC_MMC_SPEC_PLMN_SEARCH_ABORT_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmcSpecPlmnSearchAbortReq:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MSCC_MMC_SPEC_PLMN_SEARCH_ABORT_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->MsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid    = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->MsgHeader.ulLength         = sizeof(MSCC_MMC_SPEC_PLMN_SEARCH_ABORT_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName        = ID_MSCC_MMC_SPEC_PLMN_SEARCH_ABORT_REQ;

    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* 调用VOS发送原语 */
    PS_SEND_MSG( UEPS_PID_MSCC, pstMsg );

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_SndMmcOmMaintainInfoInd
 功能描述  : 处理OAM发来的TRACE 配置请求
 输入参数  : pstMaintainInfoInd
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年1月29日
   作    者   : l00208516
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MSCC_SndMmcOmMaintainInfoInd(
    MMA_MSCC_OM_MAINTAIN_INFO_IND_STRU *pstMaintainInfoInd
)
{
    MSCC_MMC_OM_MAINTAIN_INFO_IND_STRU *pstMsg = VOS_NULL_PTR;

    /* 申请内存  */
    pstMsg = (MSCC_MMC_OM_MAINTAIN_INFO_IND_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                           sizeof(MSCC_MMC_OM_MAINTAIN_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmcOmMaintainInfoInd:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MSCC_MMC_OM_MAINTAIN_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->MsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid    = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->MsgHeader.ulLength         = sizeof(MSCC_MMC_OM_MAINTAIN_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName        = ID_MSCC_MMC_OM_MAINTAIN_INFO_IND;
    pstMsg->ucOmConnectFlg             = pstMaintainInfoInd->ucOmConnectFlg;
    pstMsg->ucOmPcRecurEnableFlg       = pstMaintainInfoInd->ucOmPcRecurEnableFlg;

    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* 调用VOS发送原语 */
    PS_SEND_MSG( UEPS_PID_MSCC, pstMsg );

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MSCC_SndMmcUpdateUplmnNtf
 功能描述  : mscc给mmc发送UPLMN更新通知
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年1月29日
   作    者   : l00208516
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MSCC_SndMmcUpdateUplmnNotify( VOS_VOID )
{
    MSCC_MMC_UPDATE_UPLMN_NTF_STRU      *pstMsg = VOS_NULL_PTR;

    /* 申请内存  */
    pstMsg = (MSCC_MMC_UPDATE_UPLMN_NTF_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                           sizeof(MSCC_MMC_UPDATE_UPLMN_NTF_STRU) - VOS_MSG_HEAD_LENGTH);

    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmcUpdateUplmnNtf:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MSCC_MMC_UPDATE_UPLMN_NTF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->MsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid    = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->MsgHeader.ulLength         = sizeof(MSCC_MMC_UPDATE_UPLMN_NTF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName        = ID_MSCC_MMC_UPDATE_UPLMN_NTF;

    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* 调用VOS发送原语 */
    PS_SEND_MSG( UEPS_PID_MSCC, pstMsg );

    return;
}

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
/*****************************************************************************
 函 数 名  : NAS_MSCC_SndMmcOtherModemInfoNotify
 功能描述  : 向mmc发送ID_MSCC_MMC_OTHER_MODEM_INFO_NOTIFY请求消息
 输入参数  : pstOtherModemInfoNtf
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年1月29日
   作    者   : l00208516
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MSCC_SndMmcOtherModemInfoNotify(
    MSCC_MMC_OTHER_MODEM_INFO_NOTIFY_STRU                  *pstOtherModemInfoNtf
)
{
    MSCC_MMC_OTHER_MODEM_INFO_NOTIFY_STRU                  *pstMsg = VOS_NULL_PTR;

    /* 申请内存  */
    pstMsg = (MSCC_MMC_OTHER_MODEM_INFO_NOTIFY_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                           sizeof(MSCC_MMC_OTHER_MODEM_INFO_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmcOtherModemInfoNotify:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MSCC_MMC_OTHER_MODEM_INFO_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid    = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->stMsgHeader.ulLength         = sizeof(MSCC_MMC_OTHER_MODEM_INFO_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName        = ID_MSCC_MMC_OTHER_MODEM_INFO_NOTIFY;
    pstMsg->bitOpCurrCampPlmnId          = pstOtherModemInfoNtf->bitOpCurrCampPlmnId;
    pstMsg->stCurrCampPlmnId.ulMcc       = pstOtherModemInfoNtf->stCurrCampPlmnId.ulMcc;
    pstMsg->stCurrCampPlmnId.ulMnc       = pstOtherModemInfoNtf->stCurrCampPlmnId.ulMnc;
    pstMsg->bitOpEplmnInfo               = pstOtherModemInfoNtf->bitOpEplmnInfo;
    pstMsg->stEplmnInfo.ucEquPlmnNum     = pstOtherModemInfoNtf->stEplmnInfo.ucEquPlmnNum;

    PS_MEM_CPY(pstMsg->stEplmnInfo.astEquPlmnAddr, pstOtherModemInfoNtf->stEplmnInfo.astEquPlmnAddr,
               sizeof(pstMsg->stEplmnInfo.astEquPlmnAddr));

    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* 调用VOS发送原语 */
    PS_SEND_MSG(UEPS_PID_MSCC,pstMsg);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_SndMmcOtherModemDplmnNplmnInfoNotify
 功能描述  : 向mmc发送dplmn和nplmn信息
 输入参数  : pstMsg - 消息内容
 输出参数  : 无
 返 回 值  : VOS_OK : 消息发送成功
             VOS_ERR: 消息发送失败
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年2月5日
   作    者   : l00208516
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MSCC_SndMmcOtherModemDplmnNplmnInfoNotify(
    MMA_MSCC_OTHER_MODEM_DPLMN_NPLMN_INFO_NOTIFY_STRU     *pstOhterModemDplmnNplmnInfoNtf
)
{
    MSCC_MMC_OTHER_MODEM_DPLMN_NPLMN_INFO_NOTIFY_STRU      *pstMsg = VOS_NULL_PTR;

    /* 申请内存  */
    pstMsg = (MSCC_MMC_OTHER_MODEM_DPLMN_NPLMN_INFO_NOTIFY_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMA,
                 sizeof(MSCC_MMC_OTHER_MODEM_DPLMN_NPLMN_INFO_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmcOtherModemDplmnNplmnInfoNotify:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MSCC_MMC_OTHER_MODEM_DPLMN_NPLMN_INFO_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid    = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->stMsgHeader.ulLength         = sizeof(MSCC_MMC_OTHER_MODEM_DPLMN_NPLMN_INFO_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName        = ID_MSCC_MMC_OTHER_MODEM_DPLMN_NPLMN_INFO_NOTIFY;

    pstMsg->ucEHplmnNum = pstOhterModemDplmnNplmnInfoNtf->ucEHplmnNum;

    PS_MEM_CPY(pstMsg->aucEHplmnList,
        pstOhterModemDplmnNplmnInfoNtf->aucEHplmnList, NAS_MMC_NVIM_MAX_CFG_HPLMN_NUM);

    PS_MEM_CPY(&(pstMsg->stSelfLearnDplmnNplmnInfo),
        &(pstOhterModemDplmnNplmnInfoNtf->stSelfLearnDplmnNplmnInfo), sizeof(pstMsg->stSelfLearnDplmnNplmnInfo));

    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* 调用VOS发送原语 */
    PS_SEND_MSG( UEPS_PID_MSCC, pstMsg);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_SndMmcNcellInfoNotify
 功能描述  : 向mmc发送ID_MSCC_MMC_TDS_LTE_NCELL_INFO_NOTIFY请求消息
 输入参数  : pstNcellInfoNtf
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年1月29日
   作    者   : l00208516
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MSCC_SndMmcNcellInfoNotify(
    MMA_MSCC_NCELL_INFO_NOTIFY_STRU    *pstNcellInfoNtf
)
{
    MSCC_MMC_NCELL_INFO_NOTIFY_STRU    *pstMsg = VOS_NULL_PTR;

    /* 申请内存  */
    pstMsg = (MSCC_MMC_NCELL_INFO_NOTIFY_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                           sizeof(MSCC_MMC_NCELL_INFO_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmcNcellInfoInd:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MSCC_MMC_NCELL_INFO_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid    = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->stMsgHeader.ulLength         = sizeof(MSCC_MMC_NCELL_INFO_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName        = ID_MSCC_MMC_NCELL_INFO_NOTIFY;

    pstMsg->stTdsNcellInfo.ucTdsArfcnNum = pstNcellInfoNtf->stTdsNcellInfo.ucTdsArfcnNum;
    PS_MEM_CPY(pstMsg->stTdsNcellInfo.ausTdsArfcnList, pstNcellInfoNtf->stTdsNcellInfo.ausTdsArfcnList,
               sizeof(pstMsg->stTdsNcellInfo.ausTdsArfcnList));

    pstMsg->stLteNcellInfo.ucLteArfcnNum = pstNcellInfoNtf->stLteNcellInfo.ucLteArfcnNum;
    PS_MEM_CPY(pstMsg->stLteNcellInfo.aulLteArfcnList, pstNcellInfoNtf->stLteNcellInfo.aulLteArfcnList,
               sizeof(pstMsg->stLteNcellInfo.aulLteArfcnList));

    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* 调用VOS发送原语 */
    PS_SEND_MSG(UEPS_PID_MSCC, pstMsg);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_SndMmcPsTransferNotify
 功能描述  : 向mmc发送ID_MSCC_MMC_PS_TRANSFER_NOTIFY请求消息
 输入参数  : pstPsTransferNtf
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年1月29日
   作    者   : l00208516
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MSCC_SndMmcPsTransferNotify(
    MMA_MSCC_PS_TRANSFER_NOTIFY_STRU   *pstPsTransferNtf
)
{
    MSCC_MMC_PS_TRANSFER_NOTIFY_STRU   *pstMsg = VOS_NULL_PTR;

    /* 申请内存  */
    pstMsg = (MSCC_MMC_PS_TRANSFER_NOTIFY_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                           sizeof(MSCC_MMC_PS_TRANSFER_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmcPsTransferInd:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MSCC_MMC_PS_TRANSFER_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid    = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->stMsgHeader.ulLength         = sizeof(MSCC_MMC_PS_TRANSFER_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName        = ID_MSCC_MMC_PS_TRANSFER_NOTIFY;
    pstMsg->enSolutionCfg                = pstPsTransferNtf->enSolutionCfg;
    pstMsg->ucCause                      = pstPsTransferNtf->ucCause;

    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* 调用VOS发送原语 */
    PS_SEND_MSG(UEPS_PID_MSCC, pstMsg);

    return;
}
#endif


/*****************************************************************************
 函 数 名  : NAS_MSCC_SndMmcEOPlmnSetReq
 功能描述  : MSCC模块通知MMC模块ID_MSCC_MMC_EOPLMN_SET_REQ消息
 输入参数  : pstEOPlmnSetReq
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年1月29日
   作    者   : l00208516
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MSCC_SndMmcEOPlmnSetReq(
    MMA_MSCC_EOPLMN_SET_REQ_STRU       *pstEOPlmnSetReq
)
{
    MSCC_MMC_EOPLMN_SET_REQ_STRU       *pstMsg = VOS_NULL_PTR;

    /* 申请消息内存 */
    pstMsg = (MSCC_MMC_EOPLMN_SET_REQ_STRU*)PS_ALLOC_MSG(
                                         UEPS_PID_MSCC,
                                         sizeof(MSCC_MMC_EOPLMN_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
    if (VOS_NULL_PTR == pstMsg)
    {
        /* 内存申请失败 */
        NAS_ERROR_LOG(UEPS_PID_MSCC,"NAS_MSCC_SndMmcEOPlmnSetReq():ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MSCC_MMC_EOPLMN_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid       = UEPS_PID_MSCC;
    pstMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid     = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulMsgName         = ID_MSCC_MMC_EOPLMN_SET_REQ;
    pstMsg->MsgHeader.ulLength          = sizeof(MSCC_MMC_EOPLMN_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 填充消息内容 */
    pstMsg->ucIndex      = pstEOPlmnSetReq->ucIndex;
    pstMsg->ucOPlmnCount = pstEOPlmnSetReq->ucOPlmnCount;

    PS_MEM_CPY(pstMsg->aucVersion, pstEOPlmnSetReq->aucVersion, sizeof(pstMsg->aucVersion));

    PS_MEM_CPY(pstMsg->aucOPlmnWithRat, pstEOPlmnSetReq->aucOPlmnWithRat, sizeof(pstMsg->aucOPlmnWithRat));

    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /*消息发送*/
    PS_SEND_MSG( UEPS_PID_MSCC, pstMsg);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_SndMmcAcqReq
 功能描述  : 向MMC发送开机搜网请求消息
 输入参数  : stMsccAcqPara
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年1月29日
   作    者   : l00208516
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MSCC_SndMmcAcqReq(
    MMA_MSCC_ACQ_REQ_STRU              *pstAcqReq
)
{
    MSCC_MMC_ACQ_REQ_STRU              *pstMsg = VOS_NULL_PTR;

    /* 申请内存  */
    pstMsg = (MSCC_MMC_ACQ_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                           sizeof(MSCC_MMC_ACQ_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmcAcqReq:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MSCC_MMC_ACQ_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid    = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->stMsgHeader.ulLength         = sizeof(MSCC_MMC_ACQ_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName        = ID_MSCC_MMC_ACQ_REQ;
    pstMsg->enAcqReason                  = pstAcqReq->enAcqReason;
    pstMsg->ucNotRegAfterAcqSucc        = pstAcqReq->ucNotRegAfterAcqSucc;

    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* 调用VOS发送原语 */
    PS_SEND_MSG(UEPS_PID_MSCC, pstMsg);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_SndMmcRegReq
 功能描述  : 向MMC发送开机注册请求消息
 输入参数  : pstRegReq
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年1月29日
   作    者   : l00208516
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MSCC_SndMmcRegReq(
    MMA_MSCC_REG_REQ_STRU              *pstRegReq
)
{
    MSCC_MMC_REG_REQ_STRU              *pstMsg = VOS_NULL_PTR;

    /* 申请内存  */
    pstMsg = (MSCC_MMC_REG_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                           sizeof(MSCC_MMC_REG_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmcRegReq:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MSCC_MMC_REG_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid    = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->stMsgHeader.ulLength         = sizeof(MSCC_MMC_REG_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName        = ID_MSCC_MMC_REG_REQ;
    pstMsg->bitOpPrioClass               = pstRegReq->bitOpPrioClass;
    pstMsg->bitOpCellInfo                = pstRegReq->bitOpCellInfo;
    pstMsg->bitSpare                     = pstRegReq->bitSpare;
    pstMsg->enPrioClass                  = pstRegReq->enPrioClass;

    PS_MEM_CPY(&(pstMsg->stCellInfo), &(pstRegReq->stCellInfo), sizeof(NAS_MSCC_PIF_REG_CELL_INFO_STRU));

    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* 调用VOS发送原语 */
    PS_SEND_MSG(UEPS_PID_MSCC, pstMsg);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_SndMmcPowerSaveReq
 功能描述  : 向MMC发送开机搜网请求消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年1月29日
   作    者   : l00208516
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MSCC_SndMmcPowerSaveReq(VOS_VOID)
{
    MSCC_MMC_POWER_SAVE_REQ_STRU       *pstMsg = VOS_NULL_PTR;

    /* 申请内存  */
    pstMsg = (MSCC_MMC_POWER_SAVE_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                           sizeof(MSCC_MMC_POWER_SAVE_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmcPowerSaveReq:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MSCC_MMC_POWER_SAVE_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid    = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->stMsgHeader.ulLength         = sizeof(MSCC_MMC_POWER_SAVE_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName        = ID_MSCC_MMC_POWER_SAVE_REQ;

    pstMsg->enPowerSaveReason            = NAS_MSCC_PIF_POWER_SAVE_TYPE_UNKNOWN;

    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* 调用VOS发送原语 */
    PS_SEND_MSG(UEPS_PID_MSCC, pstMsg);

    return;
}

#if(FEATURE_ON == FEATURE_DSDS)
/*****************************************************************************
 函 数 名  : NAS_MSCC_SndMmcSrvAcqReq
 功能描述  : 向MMC发送因服务触发的搜网指示请求消息
 输入参数  : pstSrvAcqReq
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年1月29日
   作    者   : l00208516
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MSCC_SndMmcSrvAcqReq(
    MMA_MSCC_SRV_ACQ_REQ_STRU          *pstSrvAcqReq
)
{
    MSCC_MMC_SRV_ACQ_REQ_STRU          *pstMsg = VOS_NULL_PTR;

    /* 申请内存  */
    pstMsg = (MSCC_MMC_SRV_ACQ_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                           sizeof(MSCC_MMC_SRV_ACQ_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmcSrvAcqReq:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MSCC_MMC_SRV_ACQ_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid    = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->stMsgHeader.ulLength         = sizeof(MSCC_MMC_SRV_ACQ_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName        = ID_MSCC_MMC_SRV_ACQ_REQ;
    pstMsg->enSrvType                    = pstSrvAcqReq->enSrvType;

    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* 调用VOS发送原语 */
    PS_SEND_MSG(UEPS_PID_MSCC, pstMsg);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_SndMmcBeginSessionNotify
 功能描述  : 向MMC发送申请资源消息
 输入参数  : enSessionType:Session类型
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年1月29日
   作    者   : l00208516
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MSCC_SndMmcBeginSessionNotify(
    MMA_MSCC_BEGIN_SESSION_NOTIFY_STRU *pstBeginSessionNtf
)
{
    MSCC_MMC_BEGIN_SESSION_NOTIFY_STRU *pstMsg = VOS_NULL_PTR;

    /* 申请内存  */
    pstMsg = (MSCC_MMC_BEGIN_SESSION_NOTIFY_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                           sizeof(MSCC_MMC_BEGIN_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmcBeginSessionNotify:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MSCC_MMC_BEGIN_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid    = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->stMsgHeader.ulLength         = sizeof(MSCC_MMC_BEGIN_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName        = ID_MSCC_MMC_BEGIN_SESSION_NOTIFY;

    pstMsg->enSrvType                    = pstBeginSessionNtf->enSrvType;

    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* 调用VOS发送原语 */
    PS_SEND_MSG(UEPS_PID_MSCC, pstMsg);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_SndMmcEndSessionNotify
 功能描述  : 向MMC发送释放资源消息
 输入参数  : pstEndSessionNtf
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年1月29日
   作    者   : l00208516
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MSCC_SndMmcEndSessionNotify(
    MMA_MSCC_END_SESSION_NOTIFY_STRU   *pstEndSessionNtf
)
{
    MSCC_MMC_END_SESSION_NOTIFY_STRU      *pstMsg = VOS_NULL_PTR;

    /* 申请内存  */
    pstMsg = (MSCC_MMC_END_SESSION_NOTIFY_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                           sizeof(MSCC_MMC_END_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmcEndSessionNotify:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MSCC_MMC_END_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid    = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->stMsgHeader.ulLength         = sizeof(MSCC_MMC_END_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName        = ID_MSCC_MMC_END_SESSION_NOTIFY;

    pstMsg->enSrvType                    = pstEndSessionNtf->enSrvType;

    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* 调用VOS发送原语 */
    PS_SEND_MSG(UEPS_PID_MSCC, pstMsg);

    return;
}
#endif


/*****************************************************************************
 函 数 名  : NAS_MSCC_SndMmcImsSrvInfoNotify
 功能描述  : 向mmc发送ID_MSCC_MMC_IMS_SRV_INFO_NOTIFY
 输入参数  : ucImsCallFlg---IMS call是否存在
 输出参数  : 无
 返 回 值  : 无
 被调函数  :

 修改历史      :
 1.日    期   : 2015年1月29日
   作    者   : l00208516
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MSCC_SndMmcImsSrvInfoNotify(
    MMA_MSCC_IMS_SRV_INFO_NOTIFY_STRU  *pstImsSrvInfoNtf
)
{
    MSCC_MMC_IMS_SRV_INFO_NOTIFY_STRU  *pstMsg = VOS_NULL_PTR;

    /* 申请内存  */
    pstMsg = (MSCC_MMC_IMS_SRV_INFO_NOTIFY_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                           sizeof(MSCC_MMC_IMS_SRV_INFO_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC,"NAS_MSCC_SndMmcImsSrvInfoNotify:ERROR: Memory Alloc Error for pMsg");

        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MSCC_MMC_IMS_SRV_INFO_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid    = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->stMsgHeader.ulLength         = sizeof(MSCC_MMC_IMS_SRV_INFO_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName        = ID_MSCC_MMC_IMS_SRV_INFO_NOTIFY;
    pstMsg->ucImsCallFlg                 = pstImsSrvInfoNtf->ucImsCallFlg;

    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* 调用VOS发送原语 */
    PS_SEND_MSG( UEPS_PID_MSCC, pstMsg );

    return;
}


VOS_VOID NAS_MSCC_TransferMsccToMmcRat(
    NAS_MSCC_PIF_RAT_PRIO_STRU         *pstRatPrio,
    NAS_MSCC_PIF_RAT_PRIO_STRU         *pstPlmnRatPrio,
    NAS_MSCC_PIF_3GPP2_RAT_STRU        *pst3Gpp2Rat
)
{
    VOS_UINT32                          i;

    PS_MEM_SET(pstPlmnRatPrio, 0, sizeof(NAS_MSCC_PIF_RAT_PRIO_STRU));
    PS_MEM_SET(pst3Gpp2Rat, 0, sizeof(NAS_MSCC_PIF_3GPP2_RAT_STRU));

    for (i = 0; i < pstRatPrio->ucRatNum; i++)
    {
        switch (pstRatPrio->aucRatPrio[i])
        {
            case NAS_MSCC_PIF_NET_RAT_TYPE_GSM:
                pstPlmnRatPrio->aucRatPrio[pstPlmnRatPrio->ucRatNum] = NAS_MSCC_PIF_NET_RAT_TYPE_GSM;
                pstPlmnRatPrio->ucRatNum++;
                break;

            case NAS_MSCC_PIF_NET_RAT_TYPE_WCDMA:
                pstPlmnRatPrio->aucRatPrio[pstPlmnRatPrio->ucRatNum] = NAS_MSCC_PIF_NET_RAT_TYPE_WCDMA;
                pstPlmnRatPrio->ucRatNum++;
                break;

            case NAS_MSCC_PIF_NET_RAT_TYPE_LTE:
                pstPlmnRatPrio->aucRatPrio[pstPlmnRatPrio->ucRatNum] = NAS_MSCC_PIF_NET_RAT_TYPE_LTE;
                pstPlmnRatPrio->ucRatNum++;
                break;

            case NAS_MSCC_PIF_NET_RAT_TYPE_1X:
                pst3Gpp2Rat->auc3GPP2Rat[pst3Gpp2Rat->ucRatNum] = NAS_MSCC_PIF_3GPP2_RAT_TYPE_CDMA1X;
                pst3Gpp2Rat->ucRatNum++;
                break;

            case NAS_MSCC_PIF_NET_RAT_TYPE_HRPD:
                pst3Gpp2Rat->auc3GPP2Rat[pst3Gpp2Rat->ucRatNum] = NAS_MSCC_PIF_3GPP2_RAT_TYPE_HRPD;
                pst3Gpp2Rat->ucRatNum++;
                break;

            default:
                break;
        }
    }

}



VOS_VOID NAS_MSCC_SndMmcStartReq(
    MMA_MSCC_START_REQ_STRU            *pstStartReq
)
{
    MSCC_MMC_START_REQ_STRU            *pstMsg = VOS_NULL_PTR;

    /* Allocate memory for Stat request */
    pstMsg = (MSCC_MMC_START_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                           sizeof(MSCC_MMC_START_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmcStartReq:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MSCC_MMC_START_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->MsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid    = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->MsgHeader.ulLength         = sizeof(MSCC_MMC_START_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName        = ID_MSCC_MMC_START_REQ;
    pstMsg->enRegDomain                = pstStartReq->enRegDomain;
    pstMsg->enCsimStatus               = NAS_MSCC_PIF_CARD_STATUS_BUTT;
    pstMsg->enUsimStatus               = pstStartReq->enUsimStatus;

    NAS_MSCC_TransferMsccToMmcRat(&pstStartReq->stRatPrio, &pstMsg->stPlmnRatPrio, &pstMsg->st3Gpp2Rat);

#if (FEATURE_ON == FEATURE_ECALL)
    pstMsg->enCallMode                 = pstStartReq->enCallMode;
#endif
    pstMsg->enRegCtrl                  = pstStartReq->enRegCtrl;

    if (NAS_MSCC_PIF_CARD_STATUS_ABSENT != pstStartReq->enUsimStatus)
    {
        PS_MEM_CPY(pstMsg->aucImsi, pstStartReq->aucImsi, NAS_MAX_IMSI_LENGTH);
    }

    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* 调用VOS发送原语 */
    PS_SEND_MSG( UEPS_PID_MSCC, pstMsg );

    NAS_TRACE_HIGH("SEND MSG!");

    return;
}


VOS_UINT32 NAS_MSCC_SndMmcPowerOffReq(
    NAS_MSCC_PIF_POWER_OFF_CAUSE_ENUM_UINT32 enCause
)
{
    MSCC_MMC_POWER_OFF_REQ_STRU        *pstMsg = VOS_NULL_PTR;

    /* Allocate memory for new message  */
    pstMsg = (MSCC_MMC_POWER_OFF_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                           sizeof(MSCC_MMC_POWER_OFF_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmcPowerOffReq:ERROR: Memory Alloc Error for pMsg");
        return VOS_ERR;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MSCC_MMC_POWER_OFF_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->MsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid    = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->MsgHeader.ulLength         = sizeof(MSCC_MMC_POWER_OFF_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName        = ID_MSCC_MMC_POWER_OFF_REQ;
    pstMsg->enCause                    = enCause;

    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* Send the message */
    PS_SEND_MSG( UEPS_PID_MSCC, pstMsg );

    NAS_TRACE_HIGH("Send Msg!");

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_SndMmcCFPlmnSetReq
 功能描述  : 向MMC发送fplmn的请求消息
 输入参数  : pstCFPlmnReq
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年2月7日
   作    者   : f00279542s
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MSCC_SndMmcCFPlmnSetReq(
    MMA_MSCC_CFPLMN_SET_REQ_STRU       *pstCFPlmnReq
)
{
    MSCC_MMC_CFPLMN_SET_REQ_STRU       *pstMsg = VOS_NULL_PTR;

    /* 申请内存  */
    pstMsg = (MSCC_MMC_CFPLMN_SET_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                                         sizeof(MSCC_MMC_CFPLMN_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmcCFPlmnSetReq:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
               sizeof(MSCC_MMC_CFPLMN_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid    = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->stMsgHeader.ulLength         = sizeof(MSCC_MMC_CFPLMN_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName        = ID_MSCC_MMC_CFPLMN_SET_REQ;
    pstMsg->enCmdType                    = pstCFPlmnReq->enCmdType;
    pstMsg->stPlmnInfo.ulMcc             = pstCFPlmnReq->stPlmnInfo.ulMcc;
    pstMsg->stPlmnInfo.ulMnc             = pstCFPlmnReq->stPlmnInfo.ulMnc;

    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* 调用VOS发送原语 */
    PS_SEND_MSG(UEPS_PID_MSCC, pstMsg);

    return;
}
/*****************************************************************************
 函 数 名  : NAS_MSCC_SndMmcCFPlmnQueryReq
 功能描述  : 向MMC发送fplmn的请求消息
 输入参数  :pstCFPlmnReq : query req info
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年2月7日
   作    者   : f00279542s
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MSCC_SndMmcCFPlmnQueryReq(
    MMA_MSCC_CFPLMN_QUERY_REQ_STRU     *pstCFPlmnReq
)
{
    MSCC_MMC_CFPLMN_QUERY_REQ_STRU     *pstMsg = VOS_NULL_PTR;

    /* 申请内存  */
    pstMsg = (MSCC_MMC_CFPLMN_QUERY_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                                               sizeof(MSCC_MMC_CFPLMN_QUERY_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmcCFPlmnQueryReq:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
               sizeof(MSCC_MMC_CFPLMN_QUERY_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid    = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->stMsgHeader.ulLength         = sizeof(MSCC_MMC_CFPLMN_QUERY_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName        = ID_MSCC_MMC_CFPLMN_QUERY_REQ;

    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* 调用VOS发送原语 */
    PS_SEND_MSG(UEPS_PID_MSCC, pstMsg);

    return;
}
/*****************************************************************************
 函 数 名  : NAS_MSCC_SndMmcSdtConnedInd
 功能描述  : 处理mscc发来的 配置请求
 输入参数  : pstMaintainInfoInd
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年2月7日
   作    者   : f00279542s
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MSCC_SndMmcSdtConnedInd(
    MMA_MSCC_OM_MAINTAIN_INFO_IND_STRU *pstSdtConnInfoInd
)
{
    MSCC_MMC_OM_MAINTAIN_INFO_IND_STRU *pstMsg = VOS_NULL_PTR;

    /* 申请内存  */
    pstMsg = (MSCC_MMC_OM_MAINTAIN_INFO_IND_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                                                   sizeof(MSCC_MMC_OM_MAINTAIN_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH);
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmcSdtConnedInd:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
               sizeof(MSCC_MMC_OM_MAINTAIN_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->MsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid    = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->MsgHeader.ulLength         = sizeof(MSCC_MMC_OM_MAINTAIN_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName        = ID_MSCC_MMC_SDT_CONNECTED_IND;
    pstMsg->ucOmConnectFlg             = pstSdtConnInfoInd->ucOmConnectFlg;
    pstMsg->ucOmPcRecurEnableFlg       = pstSdtConnInfoInd->ucOmPcRecurEnableFlg;

    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* 调用VOS发送原语 */
    PS_SEND_MSG(UEPS_PID_MSCC, pstMsg);
    return;
}
/*****************************************************************************
 函 数 名  : NAS_MSCC_SndMmcPrefPlmnSetReq
 功能描述  : 发送ID_MSCC_MMC_PREF_PLMN_SET_REQ消息
 输入参数  : MMA_MSCC_PREF_PLMN_QUERY_REQ_STRU  *pstMsg
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年02月04日
   作    者   : y00307564
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MSCC_SndMmcPrefPlmnSetReq(
    MMA_MSCC_PREF_PLMN_SET_REQ_STRU    *pstMsg
)
{
    MSCC_MMC_PREF_PLMN_SET_REQ_STRU    *pstPrefPlmnSetReq = VOS_NULL_PTR;

    /* 申请消息包 */
    pstPrefPlmnSetReq = (MSCC_MMC_PREF_PLMN_SET_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                                                     sizeof(MSCC_MMC_PREF_PLMN_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstPrefPlmnSetReq)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmcPrefPlmnSetReq ERROR:Memory Alloc Error for pstPrefPlmnSetReq ");

        return;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstPrefPlmnSetReq) + VOS_MSG_HEAD_LENGTH,
                0,
                sizeof(MSCC_MMC_PREF_PLMN_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填充消息头 */
    pstPrefPlmnSetReq->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstPrefPlmnSetReq->stMsgHeader.ulSenderPid       = UEPS_PID_MSCC;
    pstPrefPlmnSetReq->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstPrefPlmnSetReq->stMsgHeader.ulReceiverPid     = WUEPS_PID_MMC;
    pstPrefPlmnSetReq->stMsgHeader.ulLength          = sizeof(MSCC_MMC_PREF_PLMN_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstPrefPlmnSetReq->stMsgHeader.ulMsgName         = ID_MSCC_MMC_PREF_PLMN_SET_REQ;

    /* 填充消息内容 */
    pstPrefPlmnSetReq->enPrefPlmnParaType            = pstMsg->enPrefPlmnParaType;

    PS_MEM_CPY(&(pstPrefPlmnSetReq->stCtrl),
               &(pstMsg->stCtrl),
               sizeof(NAS_MSCC_CTRL_STRU));

    PS_MEM_CPY(&(pstPrefPlmnSetReq->stPrefPlmnOpt),
               &(pstMsg->stPrefPlmnOpt),
               sizeof(NAS_MSCC_PIF_PREF_PLMN_OPERATE_STRU));

    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstPrefPlmnSetReq);

    /* 发送消息 */
    PS_SEND_MSG(UEPS_PID_MSCC, pstPrefPlmnSetReq);

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MSCC_SndMmcPrefPlmnQueryReq
 功能描述  : 发送ID_MSCC_MMC_PREF_PLMN_QUERY_REQ消息
 输入参数  : MMA_MSCC_PREF_PLMN_QUERY_REQ_STRU  *pstMsg
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年02月04日
   作    者   : y00307564
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MSCC_SndMmcPrefPlmnQueryReq(
    MMA_MSCC_PREF_PLMN_QUERY_REQ_STRU  *pstMsg
)
{
    MSCC_MMC_PREF_PLMN_QUERY_REQ_STRU  *pstPrefPlmnQueryReq = VOS_NULL_PTR;

    /* 申请消息包 */
    pstPrefPlmnQueryReq = (MSCC_MMC_PREF_PLMN_QUERY_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                    sizeof(MSCC_MMC_PREF_PLMN_QUERY_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstPrefPlmnQueryReq)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmcPrefPlmnQueryReq ERROR:Memory Alloc Error for pstPrefPlmnQueryReq ");

        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstPrefPlmnQueryReq) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MSCC_MMC_PREF_PLMN_QUERY_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填充消息头 */
    pstPrefPlmnQueryReq->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstPrefPlmnQueryReq->stMsgHeader.ulSenderPid       = UEPS_PID_MSCC;
    pstPrefPlmnQueryReq->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstPrefPlmnQueryReq->stMsgHeader.ulReceiverPid     = WUEPS_PID_MMC;
    pstPrefPlmnQueryReq->stMsgHeader.ulLength          = sizeof(MSCC_MMC_PREF_PLMN_QUERY_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstPrefPlmnQueryReq->stMsgHeader.ulMsgName         = ID_MSCC_MMC_PREF_PLMN_QUERY_REQ;

    /* 填充消息内容 */
    pstPrefPlmnQueryReq->enCmdType                     = pstMsg->enCmdType;
    pstPrefPlmnQueryReq->bPlmnSelFlg                   = pstMsg->bPlmnSelFlg;
    pstPrefPlmnQueryReq->stCpolInfo.enPrefPLMNType     = pstMsg->stCpolInfo.enPrefPLMNType;
    pstPrefPlmnQueryReq->stCpolInfo.ulFromIndex        = pstMsg->stCpolInfo.ulFromIndex;
    pstPrefPlmnQueryReq->stCpolInfo.ulPlmnNum          = pstMsg->stCpolInfo.ulPlmnNum;
    pstPrefPlmnQueryReq->stCpolInfo.ulValidPlmnNum     = pstMsg->stCpolInfo.ulValidPlmnNum;

    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstPrefPlmnQueryReq);

    /* 发送消息 */
    PS_SEND_MSG(UEPS_PID_MSCC, pstPrefPlmnQueryReq);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_SndMmcDplmnSetReq
 功能描述  : MSCC给MMC发送ID_MSCC_MMC_DPLMN_SET_REQ 消息
 输入参数  : MMA_MSCC_DPLMN_SET_REQ_STRU        *pstRcvMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月12日
    作    者   : n00355355
    修改内容   : 新生成函数
  2.日    期   : 2015年11月2日
    作    者   : l00289540
    修改内容   : 在消息中增加更新Dplmn的场景
*****************************************************************************/
VOS_VOID NAS_MSCC_SndMmcDplmnSetReq(
    MMA_MSCC_DPLMN_SET_REQ_STRU        *pstRcvMsg
)
{
    MSCC_MMC_DPLMN_SET_REQ_STRU        *pstSndMsg = VOS_NULL_PTR;

    /* 申请OSA消息 */
    pstSndMsg = (MSCC_MMC_DPLMN_SET_REQ_STRU *)NAS_MSCC_ALLOC_MSG_WITH_HDR(sizeof(MSCC_MMC_DPLMN_SET_REQ_STRU));

    if (VOS_NULL_PTR == pstSndMsg)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmcDplmnSetReq:ERROR: Memory Alloc Error for pMsg");

        return;
    }

    /* 清空消息内容 */
    NAS_MSCC_CLR_MSG_ENTITY(pstSndMsg);

    /* 填写消息头 */
    NAS_MSCC_CFG_MSG_HDR(pstSndMsg, WUEPS_PID_MMC, ID_MSCC_MMC_DPLMN_SET_REQ);

    /* 填写消息内容 */
    PS_MEM_CPY(&(pstSndMsg->stCtrl), &(pstRcvMsg->stCtrl), sizeof(pstRcvMsg->stCtrl));
    pstSndMsg->ucSeq                    = pstRcvMsg->ucSeq;

    pstSndMsg->enApPresetDplmnScene     = pstRcvMsg->enApPresetDplmnScene;

    PS_MEM_CPY(pstSndMsg->aucVersionId, pstRcvMsg->aucVersionId, MSCC_MMC_VERSION_LEN);
    pstSndMsg->stDplmnInfo.ucEhPlmnNum  = pstRcvMsg->stDplmnInfo.ucEhPlmnNum;
    pstSndMsg->stDplmnInfo.usDplmnNum   = pstRcvMsg->stDplmnInfo.usDplmnNum;
    PS_MEM_CPY(pstSndMsg->stDplmnInfo.astEhPlmnInfo,
               pstRcvMsg->stDplmnInfo.astEhPlmnInfo,
               pstRcvMsg->stDplmnInfo.ucEhPlmnNum * sizeof(NAS_MSCC_PIF_PLMN_ID_STRU));
    PS_MEM_CPY(pstSndMsg->stDplmnInfo.astDplmnList,
               pstRcvMsg->stDplmnInfo.astDplmnList,
               pstRcvMsg->stDplmnInfo.usDplmnNum * sizeof(NAS_MSCC_PIF_PLMN_WITH_RAT_STRU));

    /* 发送消息 */
    NAS_MSCC_SEND_MSG(pstSndMsg);

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MSCC_SndMmcGetGeoReq
 功能描述  : 给MMC发送ID_MSCC_MMC_GET_GEO_REQ消息
 输入参数  : MSCC_MMC_GET_GEO_REQ_STRU          *pstMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月27日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MSCC_SndMmcGetGeoReq(
    MMA_MSCC_GET_GEO_REQ_STRU          *pstMsg
)
{
    MSCC_MMC_GET_GEO_REQ_STRU          *pstSndMsg = VOS_NULL_PTR;

    /* 申请OSA消息 */
    pstSndMsg = (MSCC_MMC_GET_GEO_REQ_STRU *)NAS_MSCC_ALLOC_MSG_WITH_HDR(sizeof(MSCC_MMC_GET_GEO_REQ_STRU));
    if (VOS_NULL_PTR == pstSndMsg)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmcGetGeoReq:ERROR: Memory Alloc Error for pMsg");

        return;
    }

    /* 清空消息内容 */
    NAS_MSCC_CLR_MSG_ENTITY(pstSndMsg);

    /* 填写消息头 */
    NAS_MSCC_CFG_MSG_HDR(pstSndMsg, WUEPS_PID_MMC, ID_MSCC_MMC_GET_GEO_REQ);

    /* 填写消息内容 */

    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstSndMsg);

    /* 发送消息 */
    NAS_MSCC_SEND_MSG(pstSndMsg);

    NAS_TRACE_HIGH("NAS_MSCC_SndMmcGetGeoReq():Mscc Send Get Geo req to mcc");

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_SndMmcStopGetGeoReq
 功能描述  : 给MMC发送ID_MSCC_STOP_MMC_GET_GEO_REQ消息
 输入参数  : MMA_MSCC_STOP_GET_GEO_REQ_STRU          *pstMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年06月01日
    作    者   : f00179208
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MSCC_SndMmcStopGetGeoReq(
    MMA_MSCC_STOP_GET_GEO_REQ_STRU     *pstMsg
)
{
    MSCC_MMC_STOP_GET_GEO_REQ_STRU     *pstSndMsg = VOS_NULL_PTR;

    /* 申请OSA消息 */
    pstSndMsg = (MSCC_MMC_STOP_GET_GEO_REQ_STRU *)NAS_MSCC_ALLOC_MSG_WITH_HDR(sizeof(MSCC_MMC_STOP_GET_GEO_REQ_STRU));
    if (VOS_NULL_PTR == pstSndMsg)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmcStopGetGeoReq:ERROR: Memory Alloc Error for pMsg");

        return;
    }

    /* 清空消息内容 */
    NAS_MSCC_CLR_MSG_ENTITY(pstSndMsg);

    /* 填写消息头 */
    NAS_MSCC_CFG_MSG_HDR(pstSndMsg, WUEPS_PID_MMC, ID_MSCC_MMC_STOP_GET_GEO_REQ);

    /* 填写消息内容 */

    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstSndMsg);

    /* 发送消息 */
    NAS_MSCC_SEND_MSG(pstSndMsg);

    return;
}


#if (FEATURE_ON == FEATURE_IMS)
/*****************************************************************************
 函 数 名  : NAS_MSCC_SndMmcVoiceDomainChangeInd
 功能描述  : 向mmc发送ID_MSCC_MMC_VOICE_DOMAIN_CHANGE_IND消息
 输入参数  : enVoiceDomain
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年04月15日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MSCC_SndMmcVoiceDomainChangeInd(
    NAS_MSCC_PIF_VOICE_DOMAIN_ENUM_UINT32                   enVoiceDomain
)
{
    MSCC_MMC_VOICE_DOMAIN_CHANGE_IND_STRU                  *pstMsg = VOS_NULL_PTR;

    /* 申请内存  */
    pstMsg = (MSCC_MMC_VOICE_DOMAIN_CHANGE_IND_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                           sizeof(MSCC_MMC_VOICE_DOMAIN_CHANGE_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmcVoiceDomainChangeInd:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MSCC_MMC_VOICE_DOMAIN_CHANGE_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid    = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->stMsgHeader.ulLength         = sizeof(MSCC_MMC_VOICE_DOMAIN_CHANGE_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName        = ID_MSCC_MMC_VOICE_DOMAIN_CHANGE_IND;
    pstMsg->enVoiceDomain                = enVoiceDomain;

    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* 调用VOS发送原语 */
    PS_SEND_MSG( UEPS_PID_MSCC, pstMsg );

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_SndMmcImsSwitchStateInd
 功能描述  : 向mmc发送ID_MSCC_MMC_IMS_SWITCH_STATE_IND消息
 输入参数  : enImsSwitch
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年04月15日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MSCC_SndMmcImsSwitchStateInd(
    NAS_MSCC_PIF_IMS_SWITCH_STATE_ENUM_UINT8                enImsSwitch
)
{
    MSCC_MMC_IMS_SWITCH_STATE_IND_STRU                     *pstMsg = VOS_NULL_PTR;

    /* 申请内存  */
    pstMsg = (MSCC_MMC_IMS_SWITCH_STATE_IND_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                           sizeof(MSCC_MMC_IMS_SWITCH_STATE_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmcImsSwitchStateInd:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MSCC_MMC_IMS_SWITCH_STATE_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid    = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->stMsgHeader.ulLength         = sizeof(MSCC_MMC_IMS_SWITCH_STATE_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName        = ID_MSCC_MMC_IMS_SWITCH_STATE_IND;
    pstMsg->enImsSwitch                  = enImsSwitch;

    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* 调用VOS发送原语 */
    PS_SEND_MSG( UEPS_PID_MSCC, pstMsg );

    return;
}

#endif

/*****************************************************************************
 函 数 名  : NAS_MSCC_SndMmcAutoReselSetReq
 功能描述  : 向mmc发送ID_MSCC_MMC_AUTO_RESEL_SET_REQ消息
 输入参数  : ucActiveFlg
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年04月15日
   作    者   : b00269685
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MSCC_SndMmcAutoReselSetReq(
    VOS_UINT8                           ucActiveFlg
)
{
    MSCC_MMC_AUTO_RESEL_SET_REQ_STRU   *pstMsg = VOS_NULL_PTR;

    /* 申请内存  */
    pstMsg = (MSCC_MMC_AUTO_RESEL_SET_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                           sizeof(MSCC_MMC_AUTO_RESEL_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmcImsSwitchStateInd:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MSCC_MMC_AUTO_RESEL_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid    = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->stMsgHeader.ulLength         = sizeof(MSCC_MMC_AUTO_RESEL_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName        = ID_MSCC_MMC_AUTO_RESEL_SET_REQ;
    pstMsg->ucActiveFlg                  = ucActiveFlg;

    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* 调用VOS发送原语 */
    PS_SEND_MSG( UEPS_PID_MSCC, pstMsg );

    return;
}


VOS_VOID NAS_MSCC_SndMmcBgSearchReq(
    VOS_RATMODE_ENUM_UINT32             enRatMode
)
{
    MSCC_MMC_BG_SEARCH_REQ_STRU        *pstMsccMmcBgSearchReq = VOS_NULL_PTR;

    /* 申请消息包 */
    pstMsccMmcBgSearchReq = (MSCC_MMC_BG_SEARCH_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                    sizeof(MSCC_MMC_BG_SEARCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsccMmcBgSearchReq)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmcBgSearchReq ERROR:Memory Alloc Error for pstMsccMmcBgSearchReq ");

        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstMsccMmcBgSearchReq) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MSCC_MMC_BG_SEARCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填充消息头 */
    pstMsccMmcBgSearchReq->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMsccMmcBgSearchReq->stMsgHeader.ulSenderPid       = UEPS_PID_MSCC;
    pstMsccMmcBgSearchReq->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsccMmcBgSearchReq->stMsgHeader.ulReceiverPid     = WUEPS_PID_MMC;
    pstMsccMmcBgSearchReq->stMsgHeader.ulLength          = sizeof(MSCC_MMC_BG_SEARCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsccMmcBgSearchReq->stMsgHeader.ulMsgName         = ID_MSCC_MMC_BG_SEARCH_REQ;

    /* 填充消息内容 */
    pstMsccMmcBgSearchReq->enRatMode                     = enRatMode;

    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsccMmcBgSearchReq);

    /* 发送消息 */
    PS_SEND_MSG(UEPS_PID_MSCC, pstMsccMmcBgSearchReq);

}


VOS_VOID NAS_MSCC_SndMmcStopBgSearchReq(VOS_VOID)
{
    MSCC_MMC_STOP_BG_SEARCH_REQ_STRU   *pstMsccMmcStopBgSearchReq = VOS_NULL_PTR;

    /* 申请消息包 */
    pstMsccMmcStopBgSearchReq = (MSCC_MMC_STOP_BG_SEARCH_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                    sizeof(MSCC_MMC_STOP_BG_SEARCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsccMmcStopBgSearchReq)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmcStopBgSearchReq ERROR:Memory Alloc Error for pstMsccMmcBgSearchReq ");

        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstMsccMmcStopBgSearchReq) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MSCC_MMC_STOP_BG_SEARCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填充消息头 */
    pstMsccMmcStopBgSearchReq->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMsccMmcStopBgSearchReq->stMsgHeader.ulSenderPid       = UEPS_PID_MSCC;
    pstMsccMmcStopBgSearchReq->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsccMmcStopBgSearchReq->stMsgHeader.ulReceiverPid     = WUEPS_PID_MMC;
    pstMsccMmcStopBgSearchReq->stMsgHeader.ulLength          = sizeof(MSCC_MMC_STOP_BG_SEARCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsccMmcStopBgSearchReq->stMsgHeader.ulMsgName         = ID_MSCC_MMC_STOP_BG_SEARCH_REQ;

    /* 填充消息内容 */

    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsccMmcStopBgSearchReq);

    /* 发送消息 */
    PS_SEND_MSG(UEPS_PID_MSCC, pstMsccMmcStopBgSearchReq);

}


/*****************************************************************************
 函 数 名  : NAS_MSCC_SndMmcPlmnPriClassQueryReq
 功能描述  : 发送ID_MSCC_MMC_PLMN_PRI_CLASS_QUERY_REQ消息
 输入参数  : pstPlmnList----查询的plmn 列表
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年05月04日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2015年06月04日
   作    者   : w00176964
   修改内容   : CDMA Iteration 12:modify interface
*****************************************************************************/
VOS_VOID NAS_MSCC_SndMmcPlmnPriClassQueryReq(
    NAS_MSCC_PIF_SEARCHED_PLMN_LIST_INFO_STRU              *pstPlmnList
)
{
    MSCC_MMC_PLMN_PRI_CLASS_QUERY_REQ_STRU                 *pstPlmnPriClassQueryReq = VOS_NULL_PTR;

    /* 申请消息包 */
    pstPlmnPriClassQueryReq = (MSCC_MMC_PLMN_PRI_CLASS_QUERY_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                                sizeof(MSCC_MMC_PLMN_PRI_CLASS_QUERY_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstPlmnPriClassQueryReq)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmcPlmnPriClassQueryReq ERROR:Memory Alloc Error for pstPrefPlmnQueryReq ");

        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstPlmnPriClassQueryReq) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MSCC_MMC_PLMN_PRI_CLASS_QUERY_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填充消息头 */
    pstPlmnPriClassQueryReq->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstPlmnPriClassQueryReq->stMsgHeader.ulSenderPid       = UEPS_PID_MSCC;
    pstPlmnPriClassQueryReq->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstPlmnPriClassQueryReq->stMsgHeader.ulReceiverPid     = WUEPS_PID_MMC;
    pstPlmnPriClassQueryReq->stMsgHeader.ulLength          = sizeof(MSCC_MMC_PLMN_PRI_CLASS_QUERY_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstPlmnPriClassQueryReq->stMsgHeader.ulMsgName         = ID_MSCC_MMC_PLMN_PRI_CLASS_QUERY_REQ;

    PS_MEM_CPY(&pstPlmnPriClassQueryReq->stPlmnListInfo, pstPlmnList, sizeof(NAS_MSCC_PIF_SEARCHED_PLMN_LIST_INFO_STRU));

    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstPlmnPriClassQueryReq);

    /* 发送消息 */
    PS_SEND_MSG(UEPS_PID_MSCC, pstPlmnPriClassQueryReq);

    return;
}


#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
 函 数 名  : NAS_MSCC_SndMmcInterSysHrpdInd
 功能描述  : 发送MSCC_MMC_INTERSYS_HRPD_NTF_STRU消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年05月30日
   作    者   : l00324781
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MSCC_SndMmcInterSysHrpdInd(VOS_VOID)
{
    MSCC_MMC_INTERSYS_HRPD_NTF_STRU    *pstInterSysHrpdInd = VOS_NULL_PTR;

    /* 申请消息包 */
    pstInterSysHrpdInd = (MSCC_MMC_INTERSYS_HRPD_NTF_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                                sizeof(MSCC_MMC_INTERSYS_HRPD_NTF_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstInterSysHrpdInd)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmcInterSysHrpdInd ERROR:Memory Alloc Error for pstInterSysHrpdInd ");

        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstInterSysHrpdInd) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MSCC_MMC_INTERSYS_HRPD_NTF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填充消息头 */
    pstInterSysHrpdInd->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstInterSysHrpdInd->stMsgHeader.ulSenderPid       = UEPS_PID_MSCC;
    pstInterSysHrpdInd->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstInterSysHrpdInd->stMsgHeader.ulReceiverPid     = WUEPS_PID_MMC;
    pstInterSysHrpdInd->stMsgHeader.ulLength          = sizeof(MSCC_MMC_INTERSYS_HRPD_NTF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstInterSysHrpdInd->stMsgHeader.ulMsgName         = ID_MSCC_MMC_INTERSYS_HRPD_NTF;

    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstInterSysHrpdInd);

    /* 发送消息 */
    PS_SEND_MSG(UEPS_PID_MSCC, pstInterSysHrpdInd);

    return;
}
/*****************************************************************************
 函 数 名  : NAS_MSCC_SndMmcCLAssociatedInfoNtf
 功能描述  : 向MMC发送CLAssociatedInfo
 输入参数  : enLteSysPriClass lte的priclass
             ucAllowSrchLteFlg 是否允许搜lte的标志位

 输出参数  : 无
 返 回 值  : 无

 修改历史      :
 1.日    期   : 2015年9月11日
   作    者   : y00346957
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MSCC_SndMmcCLAssociatedInfoNtf(
    NAS_MSCC_PIF_PLMN_PRIORITY_CLASS_ENUM_UINT8             enLteSysPriClass,
    VOS_UINT8                                               ucAllowSrchLteFlg
)
{
    MSCC_MMC_CL_ASSOCIATED_INFO_NTF_STRU                   *pstMsg = VOS_NULL_PTR;

    /* 申请内存  */
    pstMsg = (MSCC_MMC_CL_ASSOCIATED_INFO_NTF_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                           sizeof(MSCC_MMC_CL_ASSOCIATED_INFO_NTF_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmCLAssociatedInfoNtf:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MSCC_MMC_CL_ASSOCIATED_INFO_NTF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid    = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->stMsgHeader.ulLength         = sizeof(MSCC_MMC_CL_ASSOCIATED_INFO_NTF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName        = ID_MSCC_MMC_CL_ASSOCIATED_INFO_NTF;

    pstMsg->ucAllowSrchLteFlg            = ucAllowSrchLteFlg;
    pstMsg->enLteSysPriClass             = enLteSysPriClass;

    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* 调用VOS发送原语 */
    PS_SEND_MSG(UEPS_PID_MSCC, pstMsg);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_SncMmcC2LInterSysStartNtf
 功能描述  : mscc给mmc发送ID_MSCC_MMC_C2L_INTERSYS_START_NTF消息
 输入参数  : 无

 输出参数  : 无
 返 回 值  : 无

 修改历史      :
 1.日    期   : 2016年1月27日
   作    者   : y00346957
   修改内容   : 新建
*****************************************************************************/
VOS_VOID NAS_MSCC_SncMmcCLInterSysStartNtf(
    NAS_MSCC_PIF_INTERSYS_CAUSE_ENUM_UINT32                 enInterSysCause
)
{
    MSCC_MMC_CL_INTERSYS_START_NTF_STRU                   *pstMsg = VOS_NULL_PTR;

    /* 申请内存  */
    pstMsg = (MSCC_MMC_CL_INTERSYS_START_NTF_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                           sizeof(MSCC_MMC_CL_INTERSYS_START_NTF_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SncMmcCLInterSysStartNtf:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MSCC_MMC_CL_INTERSYS_START_NTF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid    = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->stMsgHeader.ulLength         = sizeof(MSCC_MMC_CL_INTERSYS_START_NTF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName        = ID_MSCC_MMC_CL_INTERSYS_START_NTF;
    pstMsg->enInterSysCause              = enInterSysCause;

    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* 调用VOS发送原语 */
    PS_SEND_MSG(UEPS_PID_MSCC, pstMsg);

    return;
}
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



