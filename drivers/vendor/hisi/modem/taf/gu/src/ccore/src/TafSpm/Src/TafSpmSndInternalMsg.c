/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafSpmSndInternalMsg.c
  版 本 号   : 初稿
  作    者   : w00176964
  生成日期   : 2013年5月9日
  最近修改   :
  功能描述   : spm发给spm的消息的处理
  函数列表   :
  修改历史   :
  1.日    期   : 2013年5月9日
    作    者   : w00176964
    修改内容   : 创建文件

******************************************************************************/
/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "TafLog.h"
#include "TafSpmCtx.h"
#include "TafSpmSndInternalMsg.h"
#include "TafInternalInterface.h"



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_TAF_SPM_SND_INTERNAL_MSG_C

/*****************************************************************************
  2 全局变量
*****************************************************************************/

/*****************************************************************************
  3 宏定义
*****************************************************************************/

/*lint -save -e958 */

/*****************************************************************************
  4 函数实现
*****************************************************************************/
/*****************************************************************************
 函 数 名  : TAF_SPM_SndServiceCtrlRsltInd
 功能描述  : 发送service ctrl结果消息
 输入参数  : enRslt                     - 状态机退出结果
             ulCause                    - 失败时携带的caue值
             usClientId                 - 当前进行FDN CALL CTRL检查的client ID
             pstEntryMsg                - 修改过的入口消息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年05月15日
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_SPM_SndServiceCtrlRsltInd(
    TAF_SPM_SERVICE_CTRL_RESULT_ENUM_UINT32                 enRslt,
    VOS_UINT32                                              ulCause,
    VOS_UINT16                                              usClientId,
    TAF_SPM_ENTRY_MSG_STRU                                 *pstEntryMsg
)
{
    TAF_SPM_SERVICE_CTRL_RSLT_STRU      *pstServiceCtrlRstInd = VOS_NULL_PTR;

    /* 构造消息 */
    pstServiceCtrlRstInd = (TAF_SPM_SERVICE_CTRL_RSLT_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                                WUEPS_PID_TAF,
                                                                sizeof(TAF_SPM_SERVICE_CTRL_RSLT_STRU));
    if (VOS_NULL_PTR == pstServiceCtrlRstInd)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_SPM_SndServiceCtrlRsltInd: ERROR:Memory Alloc Error for pstMsg!");

        return;
    }

    /* 初始化消息 */
    PS_MEM_SET(((VOS_INT8*)pstServiceCtrlRstInd) + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(TAF_SPM_SERVICE_CTRL_RSLT_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填写消息头 */
    pstServiceCtrlRstInd->MsgHeader.ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstServiceCtrlRstInd->MsgHeader.ulSenderPid                 = WUEPS_PID_TAF;
    pstServiceCtrlRstInd->MsgHeader.ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstServiceCtrlRstInd->MsgHeader.ulReceiverPid               = WUEPS_PID_TAF;
    pstServiceCtrlRstInd->MsgHeader.ulLength                    = sizeof(TAF_SPM_SERVICE_CTRL_RSLT_STRU) - VOS_MSG_HEAD_LENGTH;
    pstServiceCtrlRstInd->MsgHeader.ulMsgName                   = TAF_SPM_INTERNAL_SERVICE_CTRL_RESULT_IND;

    /* 填写消息内容 */
    pstServiceCtrlRstInd->enResult                  = enRslt;
    pstServiceCtrlRstInd->ulCause                   = ulCause;
    pstServiceCtrlRstInd->usClientId                = usClientId;
    pstServiceCtrlRstInd->stEntryMsg.ulEventType    = pstEntryMsg->ulEventType;

    PS_MEM_CPY(pstServiceCtrlRstInd->stEntryMsg.aucEntryMsgBuffer,
                pstEntryMsg->aucEntryMsgBuffer,
                sizeof(pstEntryMsg->aucEntryMsgBuffer));

    /* 发送内部消息 */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TAF, pstServiceCtrlRstInd))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_SPM_SndServiceCtrlRsltInd: Send message failed.");
    }

    return;
}

/* 放到IMS宏开关外面公共使用 */
/* Added by y00245242 for VoLTE_PhaseII 项目, 2013-9-25, begin */
/*****************************************************************************
 函 数 名  : TAF_SPM_SndInternalDomainSelectionInd
 功能描述  : 发送业务域选择指示给SPM，触发缓存消息的域选择
 输入参数  : 无

 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年09月24日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_SPM_SndInternalDomainSelectionInd(VOS_VOID)
{
    TAF_SPM_DOMAIN_SEL_IND_STRU        *pstDomainSelInd = VOS_NULL_PTR;

    /* allocate memory for message */
    pstDomainSelInd = (TAF_SPM_DOMAIN_SEL_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                        WUEPS_PID_TAF,
                                                        sizeof(TAF_SPM_DOMAIN_SEL_IND_STRU));
    /* return if memory allocation is failure */
    if (VOS_NULL_PTR == pstDomainSelInd)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
                      "TAF_SPM_SndInternalDomainSelectionInd: ERROR: Memory allocation is failure!");

        return;
    }

    /* initialize message */
    PS_MEM_SET(((VOS_INT8*)pstDomainSelInd) + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(TAF_SPM_DOMAIN_SEL_IND_STRU) - VOS_MSG_HEAD_LENGTH);


    /* fill message header */
    pstDomainSelInd->MsgHeader.ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstDomainSelInd->MsgHeader.ulSenderPid                 = WUEPS_PID_TAF;
    pstDomainSelInd->MsgHeader.ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstDomainSelInd->MsgHeader.ulReceiverPid               = WUEPS_PID_TAF;
    pstDomainSelInd->MsgHeader.ulLength                    = sizeof(TAF_SPM_DOMAIN_SEL_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstDomainSelInd->MsgHeader.ulMsgName                   = TAF_SPM_INTERNAL_DOMAIN_SEL_IND;

    /* send domain selection indication message to self */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TAF, pstDomainSelInd))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
                      "TAF_SPM_SndInternalDomainSelectionInd: ERROR: Send message failed.");
    }

    return;
}

#if (FEATURE_IMS == FEATURE_ON)
/*****************************************************************************
 函 数 名  : TAF_SPM_SendMsgSmmaRsp
 功能描述  : SPM向MSG模块发送SMMA RSP消息,携带信令类型
 输入参数  : enMsgSignallingType---信令类型
 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月17日
    作    者   : s00217060
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_SPM_SendMsgSmmaRsp(
    TAF_MSG_SIGNALLING_TYPE_ENUM_UINT32 enMsgSignallingType,
    struct MsgCB                       *pstMsg
)
{
    TAF_SPM_SMMA_RSP_STRU              *pstSmmaRsp = VOS_NULL_PTR;
    TAF_SPM_SMMA_IND_STRU              *pstSmmaInd = VOS_NULL_PTR;

    pstSmmaRsp = (TAF_SPM_SMMA_RSP_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,sizeof(TAF_SPM_SMMA_RSP_STRU));

    if (VOS_NULL_PTR == pstSmmaRsp)
    {
        MN_WARN_LOG("TAF_SPM_SendMsgSmmaRsp:ERROR: VOS_AllocMsg fail.");
        return;
    }

    pstSmmaInd  = (TAF_SPM_SMMA_IND_STRU *)pstMsg;
    
    PS_MEM_SET(pstSmmaRsp, 0, sizeof(TAF_SPM_SMMA_RSP_STRU));

    pstSmmaRsp->ulSenderCpuId        = VOS_LOCAL_CPUID;
    pstSmmaRsp->ulSenderPid          = WUEPS_PID_TAF;
    pstSmmaRsp->ulReceiverCpuId      = VOS_LOCAL_CPUID;
    pstSmmaRsp->ulReceiverPid        = WUEPS_PID_TAF;
    pstSmmaRsp->ulLength             = sizeof(TAF_SPM_SMMA_RSP_STRU) - VOS_MSG_HEAD_LENGTH;
    pstSmmaRsp->ulMsgId              = ID_TAF_SPM_SMMA_RSP;
    pstSmmaRsp->clientId             = pstSmmaInd->clientId;
    pstSmmaRsp->opId                 = pstSmmaInd->opId;
    pstSmmaRsp->enMsgSignallingType  = enMsgSignallingType;

    if ( VOS_OK != PS_SEND_MSG( WUEPS_PID_TAF, pstSmmaRsp ) )
    {
        MN_WARN_LOG( "TAF_SPM_SendMsgSmmaRsp:WARNING:SEND ID_TAF_SPM_SMMA_RSP msg FAIL!" );
    }

    return;
}
#endif
/* Added by y00245242 for VoLTE_PhaseII 项目, 2013-9-25, end */

/* Added by y00245242 for V3R3C60_eCall项目, 2014-4-26, begin */
#if (FEATURE_ON == FEATURE_ECALL)
/*****************************************************************************
 函 数 名  : TAF_SPM_SndTafRelCallReq
 功能描述  : 发送消息通知CALL模块释放所有正常呼叫请求，如果有紧急呼叫存在，不
             处理，返回失败；

 输入参数  : 无

 输出参数  : 无
 返 回 值  : VOS_TRUE                     - 发送内部消息成功
             VOS_FASLE                    - 发送内部消息失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年09月24日
    作    者   : y00245242
    修改内容   : 为eCall特性增加
*****************************************************************************/
VOS_VOID TAF_SPM_SndTafRelCallReq(
    MN_CLIENT_ID_T                      usClientId,
    MN_OPERATION_ID_T                   ucOpId,
    TAF_CALL_REL_CALL_TYPE_ENUM_UINT8   enRelType
)
{
    TAF_CALL_TAF_REL_CALL_REQ_STRU     *pstRelCallReq = VOS_NULL_PTR;

    pstRelCallReq = (TAF_CALL_TAF_REL_CALL_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                        sizeof(TAF_CALL_TAF_REL_CALL_REQ_STRU));

    if (VOS_NULL_PTR == pstRelCallReq)
    {
        MN_WARN_LOG("TAF_SPM_SndTafRelCallReq:ERROR: VOS_AllocMsg fail.");
        return;
    }

    PS_MEM_SET(pstRelCallReq, 0, sizeof(TAF_CALL_TAF_REL_CALL_REQ_STRU));

    pstRelCallReq->ulSenderCpuId        = VOS_LOCAL_CPUID;
    pstRelCallReq->ulSenderPid          = WUEPS_PID_TAF;
    pstRelCallReq->ulReceiverCpuId      = VOS_LOCAL_CPUID;
    pstRelCallReq->ulReceiverPid        = WUEPS_PID_TAF;
    pstRelCallReq->ulLength             = sizeof(TAF_CALL_TAF_REL_CALL_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstRelCallReq->ulMsgId              = TAF_CALL_TAF_REL_CALL_REQ;

    pstRelCallReq->usClientId           = usClientId;
    pstRelCallReq->ucOpId               = ucOpId;
    pstRelCallReq->enRelType            = enRelType;

    if ( VOS_OK != PS_SEND_MSG(WUEPS_PID_TAF, pstRelCallReq))
    {
        MN_WARN_LOG( "TAF_SPM_SndTafRelCallReq:WARNING:SEND TAF_SPM_SndTafRelCallReq msg FAIL!" );
    }

    return;
}
#endif
/* Added by y00245242 for V3R3C60_eCall项目, 2014-4-26, end */
/*lint -restore */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


