/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafXpdsSndInternalMsg.c
  版 本 号   : 初稿
  作    者   : g00261581
  生成日期   : 2015年8月21日
  最近修改   :
  功能描述   : XPDS发送给XPDS的消息处理
  函数列表   :
  修改历史   :
  1.日    期   : 2015年8月21日
    作    者   : g00261581
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "TafXpdsSndInternalMsg.h"
#include "TafXpdsMntn.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#define THIS_FILE_ID                    PS_FILE_ID_TAF_XPDS_SND_INTERNAL_MSG_C

#if ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_AGPS))

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*lint -save -e958 -e429 -e830 */

/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*****************************************************************************
 函 数 名  : TAF_XPDS_SndInternalServerBindOperReq
 功能描述  : XPDS模块发送内部消息控制MPC/PDE的Socket链路
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月26日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XPDS_SndInternalServerBindOperReq(
    TAF_XPDS_SERVER_BIND_OPER_ENUM_UINT8                    enMpcBindOpt,
    TAF_XPDS_SERVER_BIND_OPER_ENUM_UINT8                    enPdeBindOpt
)
{
    TAF_XPDS_XPDS_UP_LINK_CTRL_REQ_STRU *pstBindServerReq  = VOS_NULL_PTR;

    pstBindServerReq = (TAF_XPDS_XPDS_UP_LINK_CTRL_REQ_STRU *)PS_MEM_ALLOC(UEPS_PID_XPDS,
                                        sizeof(TAF_XPDS_XPDS_UP_LINK_CTRL_REQ_STRU));

    if (VOS_NULL_PTR == pstBindServerReq)
    {
        XPDS_ERROR_LOG("TAF_XPDS_SndInternalServerBindOperReq: Memory alloc failed");
        return;
    }

    PS_MEM_SET((VOS_UINT8*)pstBindServerReq + VOS_MSG_HEAD_LENGTH, 0,
                sizeof(TAF_XPDS_XPDS_UP_LINK_CTRL_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填写参数 */
    pstBindServerReq->ulSenderCpuId          = VOS_LOCAL_CPUID;
    pstBindServerReq->ulSenderPid            = UEPS_PID_XPDS;
    pstBindServerReq->ulReceiverCpuId        = VOS_LOCAL_CPUID;
    pstBindServerReq->ulReceiverPid          = UEPS_PID_XPDS;
    pstBindServerReq->ulLength               = sizeof(TAF_XPDS_XPDS_UP_LINK_CTRL_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstBindServerReq->enMsgId                = ID_TAF_XPDS_XPDS_UP_LINK_CTRL_REQ;
    pstBindServerReq->enMpcBindOpt           = enMpcBindOpt;
    pstBindServerReq->enPdeBindOpt           = enPdeBindOpt;

    TAF_XPDS_PutMsgInIntMsgQueue((VOS_UINT8*)pstBindServerReq);

    return;


}

/*****************************************************************************
 函 数 名  : TAF_XPDS_SndInternalServerBindRsltCnf
 功能描述  : XPDS Snd Server Bind Result to XPDS
 输入参数  : TAF_XPDS_OPER_RESULT_ENUM_UINT32    enRslt
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月26日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XPDS_SndInternalServerBindRsltCnf(
    TAF_XPDS_POS_PROC_RSLT_ENUM_UINT32  enRslt
)
{
    TAF_XPDS_XPDS_UP_LINK_CTRL_CNF_STRU    *pstBindServerRslt  = VOS_NULL_PTR;

    pstBindServerRslt = (TAF_XPDS_XPDS_UP_LINK_CTRL_CNF_STRU *)PS_MEM_ALLOC(UEPS_PID_XPDS,
                                        sizeof(TAF_XPDS_XPDS_UP_LINK_CTRL_CNF_STRU));

    if (VOS_NULL_PTR == pstBindServerRslt)
    {
        XPDS_ERROR_LOG("TAF_XPDS_SndInternalServerBindRsltCnf: Memory alloc failed");
        return;
    }

    PS_MEM_SET((VOS_UINT8*)pstBindServerRslt + VOS_MSG_HEAD_LENGTH, 0,
                sizeof(TAF_XPDS_XPDS_UP_LINK_CTRL_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填写参数 */
    pstBindServerRslt->ulSenderCpuId          = VOS_LOCAL_CPUID;
    pstBindServerRslt->ulSenderPid            = UEPS_PID_XPDS;
    pstBindServerRslt->ulReceiverCpuId        = VOS_LOCAL_CPUID;
    pstBindServerRslt->ulReceiverPid          = UEPS_PID_XPDS;
    pstBindServerRslt->ulLength               = sizeof(TAF_XPDS_XPDS_UP_LINK_CTRL_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    pstBindServerRslt->enMsgId                = ID_TAF_XPDS_XPDS_UP_LINK_CTRL_CNF;
    pstBindServerRslt->enRslt                 = enRslt;

    TAF_XPDS_PutMsgInIntMsgQueue((VOS_UINT8*)pstBindServerRslt);

    return;
}


/*****************************************************************************
 函 数 名  : TAF_XPDS_SndInternalPdeProcStartReq
 功能描述  : XPDS send PDE proc start to XPDS
 输入参数  : enFixMode - Fix mode
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月28日
    作    者   : y00174758
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XPDS_SndInternalPdeProcStartReq(
    TAF_XPDS_FIX_MODE_ENUM_UINT8                            enFixMode
)
{
    TAF_XPDS_XPDS_PDE_PROC_START_REQ_STRU                  *pstPdeProcStartReq = VOS_NULL_PTR;

    pstPdeProcStartReq = (TAF_XPDS_XPDS_PDE_PROC_START_REQ_STRU *)PS_MEM_ALLOC(UEPS_PID_XPDS,
                                                            sizeof(TAF_XPDS_XPDS_PDE_PROC_START_REQ_STRU));

    if (VOS_NULL_PTR == pstPdeProcStartReq)
    {
        XPDS_ERROR_LOG("TAF_XPDS_SndInternalPdeProcStartReq: Memory alloc failed");
        return;
    }

    PS_MEM_SET((VOS_UINT8*)pstPdeProcStartReq + VOS_MSG_HEAD_LENGTH, 0,
                sizeof(TAF_XPDS_XPDS_PDE_PROC_START_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填写参数 */
    pstPdeProcStartReq->ulSenderCpuId          = VOS_LOCAL_CPUID;
    pstPdeProcStartReq->ulSenderPid            = UEPS_PID_XPDS;
    pstPdeProcStartReq->ulReceiverCpuId        = VOS_LOCAL_CPUID;
    pstPdeProcStartReq->ulReceiverPid          = UEPS_PID_XPDS;
    pstPdeProcStartReq->ulLength               = sizeof(TAF_XPDS_XPDS_PDE_PROC_START_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstPdeProcStartReq->enMsgId                = ID_TAF_XPDS_XPDS_PDE_PROC_START_REQ;
    pstPdeProcStartReq->enFixMode              = enFixMode;

    TAF_XPDS_PutMsgInIntMsgQueue((VOS_UINT8*)pstPdeProcStartReq);

    return;
}


/*****************************************************************************
 函 数 名  : TAF_XPDS_SndInternalPdeProcRsltInd
 功能描述  : XPDS Snd Server PDE Result to XPDS
 输入参数  : TAF_XPDS_POS_PROC_RSLT_ENUM_UINT32    enRslt
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月26日
    作    者   : x00314862
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XPDS_SndInternalPdeProcRsltInd(
    TAF_XPDS_POS_PROC_RSLT_ENUM_UINT32                      enRslt
)
{
    TAF_XPDS_XPDS_PDE_PROC_RSLT_IND_STRU                   *pstPdeProcRsltInd = VOS_NULL_PTR;

    pstPdeProcRsltInd = (TAF_XPDS_XPDS_PDE_PROC_RSLT_IND_STRU *)PS_MEM_ALLOC(UEPS_PID_XPDS,
                                                            sizeof(TAF_XPDS_XPDS_PDE_PROC_RSLT_IND_STRU));

    if (VOS_NULL_PTR == pstPdeProcRsltInd)
    {
        XPDS_ERROR_LOG("TAF_XPDS_SndInternalPdeProcRsltInd: Memory alloc failed");
        return;
    }

    PS_MEM_SET((VOS_UINT8*)pstPdeProcRsltInd + VOS_MSG_HEAD_LENGTH, 0,
                sizeof(TAF_XPDS_XPDS_PDE_PROC_RSLT_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填写参数 */
    pstPdeProcRsltInd->ulSenderCpuId          = VOS_LOCAL_CPUID;
    pstPdeProcRsltInd->ulSenderPid            = UEPS_PID_XPDS;
    pstPdeProcRsltInd->ulReceiverCpuId        = VOS_LOCAL_CPUID;
    pstPdeProcRsltInd->ulReceiverPid          = UEPS_PID_XPDS;
    pstPdeProcRsltInd->ulLength               = sizeof(TAF_XPDS_XPDS_PDE_PROC_RSLT_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstPdeProcRsltInd->enMsgId                = ID_TAF_XPDS_XPDS_PDE_PROC_RSLT_IND;
    pstPdeProcRsltInd->enRslt                 = enRslt;

    TAF_XPDS_PutMsgInIntMsgQueue((VOS_UINT8*)pstPdeProcRsltInd);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_SndInternalCpPdeProcRsltInd
 功能描述  : XPDS Snd control plane Server PDE Result to XPDS
 输入参数  : TAF_XPDS_POS_PROC_RSLT_ENUM_UINT32    enRslt
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月09日
    作    者   : l00902690
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XPDS_SndInternalCpPdeProcRsltInd(
    TAF_XPDS_POS_PROC_RSLT_ENUM_UINT32                      enRslt
)
{
    TAF_XPDS_XPDS_PDE_PROC_RSLT_IND_STRU                   *pstPdeProcRsltInd = VOS_NULL_PTR;

    pstPdeProcRsltInd = (TAF_XPDS_XPDS_PDE_PROC_RSLT_IND_STRU *)PS_MEM_ALLOC(UEPS_PID_XPDS,
                                                            sizeof(TAF_XPDS_XPDS_PDE_PROC_RSLT_IND_STRU));

    if (VOS_NULL_PTR == pstPdeProcRsltInd)
    {
        XPDS_ERROR_LOG("TAF_XPDS_SndInternalPdeProcRsltInd: Memory alloc failed");
        return;
    }

    PS_MEM_SET((VOS_UINT8*)pstPdeProcRsltInd + VOS_MSG_HEAD_LENGTH, 0,
                sizeof(TAF_XPDS_XPDS_PDE_PROC_RSLT_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填写参数 */
    pstPdeProcRsltInd->ulSenderCpuId          = VOS_LOCAL_CPUID;
    pstPdeProcRsltInd->ulSenderPid            = UEPS_PID_XPDS;
    pstPdeProcRsltInd->ulReceiverCpuId        = VOS_LOCAL_CPUID;
    pstPdeProcRsltInd->ulReceiverPid          = UEPS_PID_XPDS;
    pstPdeProcRsltInd->ulLength               = sizeof(TAF_XPDS_XPDS_PDE_PROC_RSLT_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstPdeProcRsltInd->enMsgId                = ID_TAF_XPDS_XPDS_CP_PDE_PROC_RSLT_IND;
    pstPdeProcRsltInd->enRslt                 = enRslt;

    TAF_XPDS_PutMsgInIntMsgQueue((VOS_UINT8*)pstPdeProcRsltInd);

    return;
}


/*****************************************************************************
 函 数 名  : TAF_XPDS_SndInternalForwardPdeDataInd
 功能描述  : 发送ID_TAF_XPDS_XPDS_FORWARD_PDE_DATA_IND内部消息
 输入参数  : ulDataMask - PDE data mask
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月27日
    作    者   : y00174758
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XPDS_SndInternalForwardPdeDataInd(
    VOS_UINT32                                              ulDataMask,
    TAF_XPDS_CALL_TYPE_ENUM_UINT8                           enCallType
)
{
    TAF_XPDS_XPDS_FORWARD_PDE_DATA_IND_STRU                *pstPdeDataInd = VOS_NULL_PTR;;

    pstPdeDataInd = (TAF_XPDS_XPDS_FORWARD_PDE_DATA_IND_STRU*)PS_MEM_ALLOC(
                                                    UEPS_PID_XPDS,
                                                    sizeof(TAF_XPDS_XPDS_FORWARD_PDE_DATA_IND_STRU));

    if (VOS_NULL_PTR == pstPdeDataInd)
    {
        XPDS_ERROR_LOG("TAF_XPDS_SndInternalForwardPdeDataInd: Memory alloc failed");
        return;
    }

    PS_MEM_SET((VOS_UINT8*)pstPdeDataInd + VOS_MSG_HEAD_LENGTH, 0,
                sizeof(TAF_XPDS_XPDS_FORWARD_PDE_DATA_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填写参数 */
    pstPdeDataInd->ulSenderCpuId          = VOS_LOCAL_CPUID;
    pstPdeDataInd->ulSenderPid            = UEPS_PID_XPDS;
    pstPdeDataInd->ulReceiverCpuId        = VOS_LOCAL_CPUID;
    pstPdeDataInd->ulReceiverPid          = UEPS_PID_XPDS;
    pstPdeDataInd->enMsgId                = ID_TAF_XPDS_XPDS_FORWARD_PDE_DATA_IND;
    pstPdeDataInd->ulLength               = sizeof(TAF_XPDS_XPDS_FORWARD_PDE_DATA_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstPdeDataInd->ulDataMask             = ulDataMask;
    pstPdeDataInd->enCallType             = enCallType;

    TAF_XPDS_PutMsgInIntMsgQueue((VOS_UINT8*)pstPdeDataInd);
}


/*****************************************************************************
 函 数 名  : TAF_XPDS_SndInternalStartMpcProcess
 功能描述  :
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月27日
    作    者   : c00299064
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XPDS_SndInternalStartMpcProcess(
    TAF_XPDS_MPC_OPER_TYPE_ENUM_UINT32                      enMpcOperation
)
{
    TAF_XPDS_XPDS_INT_MPC_PROC_START_REQ_STRU                *pstMpcMsg = VOS_NULL_PTR;;

    pstMpcMsg = (TAF_XPDS_XPDS_INT_MPC_PROC_START_REQ_STRU*)PS_MEM_ALLOC(
                                                    UEPS_PID_XPDS,
                                                    sizeof(TAF_XPDS_XPDS_INT_MPC_PROC_START_REQ_STRU));

    if (VOS_NULL_PTR == pstMpcMsg)
    {
        XPDS_ERROR_LOG("TAF_XPDS_SndInternalStartMpcProcess: Memory alloc failed");
        return;
    }

    PS_MEM_SET((VOS_UINT8*)pstMpcMsg + VOS_MSG_HEAD_LENGTH, 0,
                sizeof(TAF_XPDS_XPDS_INT_MPC_PROC_START_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填写参数 */
    pstMpcMsg->ulSenderCpuId          = VOS_LOCAL_CPUID;
    pstMpcMsg->ulSenderPid            = UEPS_PID_XPDS;
    pstMpcMsg->ulReceiverCpuId        = VOS_LOCAL_CPUID;
    pstMpcMsg->ulReceiverPid          = UEPS_PID_XPDS;
    pstMpcMsg->ulLength               = sizeof(TAF_XPDS_XPDS_INT_MPC_PROC_START_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMpcMsg->enMsgId                = ID_TAF_XPDS_XPDS_INT_MPC_PROC_START_REQ;
    pstMpcMsg->ulSenderCpuId          = VOS_LOCAL_CPUID;
    pstMpcMsg->ulReceiverCpuId        = VOS_LOCAL_CPUID;


    pstMpcMsg->enMpcOperation= enMpcOperation;

    TAF_XPDS_PutMsgInIntMsgQueue((VOS_UINT8*)pstMpcMsg);

    return;
}


/*****************************************************************************
 函 数 名  : TAF_XPDS_SndInternalMpcRslt
 功能描述  :
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月27日
    作    者   : c00299064
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XPDS_SndInternalMpcRslt(
    TAF_XPDS_MPC_OPER_TYPE_ENUM_UINT32                      enMpcOperation,
    TAF_XPDS_POS_PROC_RSLT_ENUM_UINT32                      enMpcOperRslt
)
{
    TAF_XPDS_XPDS_INT_MPC_PROC_RSLT_IND_STRU                *pstMpcMsg = VOS_NULL_PTR;;

    pstMpcMsg = (TAF_XPDS_XPDS_INT_MPC_PROC_RSLT_IND_STRU*)PS_MEM_ALLOC(
                                                    UEPS_PID_XPDS,
                                                    sizeof(TAF_XPDS_XPDS_INT_MPC_PROC_RSLT_IND_STRU));

    if (VOS_NULL_PTR == pstMpcMsg)
    {
        XPDS_ERROR_LOG("TAF_XPDS_SndInternalMpcRslt: Memory alloc failed");
        return;
    }

    PS_MEM_SET((VOS_UINT8*)pstMpcMsg + VOS_MSG_HEAD_LENGTH, 0,
                sizeof(TAF_XPDS_XPDS_INT_MPC_PROC_RSLT_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填写参数 */
    pstMpcMsg->ulSenderCpuId          = VOS_LOCAL_CPUID;
    pstMpcMsg->ulSenderPid            = UEPS_PID_XPDS;
    pstMpcMsg->ulReceiverCpuId        = VOS_LOCAL_CPUID;
    pstMpcMsg->ulReceiverPid          = UEPS_PID_XPDS;
    pstMpcMsg->ulLength               = sizeof(TAF_XPDS_XPDS_INT_MPC_PROC_RSLT_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMpcMsg->enMsgId                = ID_TAF_XPDS_XPDS_INT_MPC_PROC_RSLT_IND;
    pstMpcMsg->enMpcOperation         = enMpcOperation;
    pstMpcMsg->enMpcOperRslt          = enMpcOperRslt;

    TAF_XPDS_PutMsgInIntMsgQueue((VOS_UINT8*)pstMpcMsg);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_SndInternalMpcStartPosResp
 功能描述  :
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月27日
    作    者   : c00299064
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XPDS_SndInternalMpcStartPosResp(
    TAF_XPDS_MPC_START_POS_RSP_STRU                         *pstStartPosRsp
)
{
    TAF_XPDS_XPDS_INT_RCV_MPC_START_POS_RESP_STRU                *pstMpcMsg = VOS_NULL_PTR;;

    pstMpcMsg = (TAF_XPDS_XPDS_INT_RCV_MPC_START_POS_RESP_STRU*)PS_MEM_ALLOC(
                                                    UEPS_PID_XPDS,
                                                    sizeof(TAF_XPDS_XPDS_INT_RCV_MPC_START_POS_RESP_STRU));

    if (VOS_NULL_PTR == pstMpcMsg)
    {
        XPDS_ERROR_LOG("TAF_XPDS_SndInternalMpcStartPosResp: Memory alloc failed");
        return;
    }

    PS_MEM_SET((VOS_UINT8*)pstMpcMsg + VOS_MSG_HEAD_LENGTH, 0,
                sizeof(TAF_XPDS_XPDS_INT_RCV_MPC_START_POS_RESP_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填写参数 */
    pstMpcMsg->ulSenderCpuId          = VOS_LOCAL_CPUID;
    pstMpcMsg->ulSenderPid            = UEPS_PID_XPDS;
    pstMpcMsg->ulReceiverCpuId        = VOS_LOCAL_CPUID;
    pstMpcMsg->ulReceiverPid          = UEPS_PID_XPDS;
    pstMpcMsg->ulLength               = sizeof(TAF_XPDS_XPDS_INT_RCV_MPC_START_POS_RESP_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMpcMsg->enMsgId                = ID_TAF_XPDS_XPDS_INT_RCV_MPC_START_POS_RESP;

    PS_MEM_CPY(&pstMpcMsg->stStartPosRsp, pstStartPosRsp, sizeof(TAF_XPDS_MPC_START_POS_RSP_STRU));

    TAF_XPDS_PutMsgInIntMsgQueue((VOS_UINT8*)pstMpcMsg);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_SndInternalMpcPosReportResp
 功能描述  :
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月27日
    作    者   : c00299064
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XPDS_SndInternalMpcPosReportResp(
    TAF_XPDS_MPC_POS_REPORT_RSP_STRU                        *pstPosReportRsp
)
{
    TAF_XPDS_XPDS_INT_RCV_MPC_POS_REPORT_RESP_STRU                *pstMpcMsg = VOS_NULL_PTR;;

    pstMpcMsg = (TAF_XPDS_XPDS_INT_RCV_MPC_POS_REPORT_RESP_STRU*)PS_MEM_ALLOC(
                                                    UEPS_PID_XPDS,
                                                    sizeof(TAF_XPDS_XPDS_INT_RCV_MPC_POS_REPORT_RESP_STRU));

    if (VOS_NULL_PTR == pstMpcMsg)
    {
        XPDS_ERROR_LOG("TAF_XPDS_SndInternalMpcStartPosResp: Memory alloc failed");
        return;
    }

    PS_MEM_SET((VOS_UINT8*)pstMpcMsg + VOS_MSG_HEAD_LENGTH, 0,
                sizeof(TAF_XPDS_XPDS_INT_RCV_MPC_POS_REPORT_RESP_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填写参数 */
    pstMpcMsg->ulSenderCpuId          = VOS_LOCAL_CPUID;
    pstMpcMsg->ulSenderPid            = UEPS_PID_XPDS;
    pstMpcMsg->ulReceiverCpuId        = VOS_LOCAL_CPUID;
    pstMpcMsg->ulReceiverPid          = UEPS_PID_XPDS;
    pstMpcMsg->ulLength               = sizeof(TAF_XPDS_XPDS_INT_RCV_MPC_POS_REPORT_RESP_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMpcMsg->enMsgId                = ID_TAF_XPDS_XPDS_INT_RCV_MPC_POS_REPORT_RESP;

    PS_MEM_CPY(&pstMpcMsg->stPosReportRsp, pstPosReportRsp, sizeof(TAF_XPDS_MPC_POS_REPORT_RSP_STRU));

    TAF_XPDS_PutMsgInIntMsgQueue((VOS_UINT8*)pstMpcMsg);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_SndInternalXsmsCancelNiTracking
 功能描述  :
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月27日
    作    者   : c00299064
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XPDS_SndInternalXsmsCancelNiTracking(
    VOS_VOID
)
{
    TAF_XPDS_XPDS_INT_XSMS_CANCEL_NI_TRACK_SESSION_STRU         *pstMpcMsg = VOS_NULL_PTR;;

    pstMpcMsg = (TAF_XPDS_XPDS_INT_XSMS_CANCEL_NI_TRACK_SESSION_STRU*)PS_MEM_ALLOC(
                                                    UEPS_PID_XPDS,
                                                    sizeof(TAF_XPDS_XPDS_INT_XSMS_CANCEL_NI_TRACK_SESSION_STRU));

    if (VOS_NULL_PTR == pstMpcMsg)
    {
        XPDS_ERROR_LOG("TAF_XPDS_SndInternalMpcStartPosResp: Memory alloc failed");
        return;
    }

    PS_MEM_SET((VOS_UINT8*)pstMpcMsg + VOS_MSG_HEAD_LENGTH, 0,
                sizeof(TAF_XPDS_XPDS_INT_XSMS_CANCEL_NI_TRACK_SESSION_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填写参数 */
    pstMpcMsg->ulSenderCpuId          = VOS_LOCAL_CPUID;
    pstMpcMsg->ulSenderPid            = UEPS_PID_XPDS;
    pstMpcMsg->ulReceiverCpuId        = VOS_LOCAL_CPUID;
    pstMpcMsg->ulReceiverPid          = UEPS_PID_XPDS;
    pstMpcMsg->ulLength               = sizeof(TAF_XPDS_XPDS_INT_XSMS_CANCEL_NI_TRACK_SESSION_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMpcMsg->enMsgId                = ID_TAF_XPDS_XPDS_INT_XSMS_CANCEL_NI_TRACK_SESSION;

    TAF_XPDS_PutMsgInIntMsgQueue((VOS_UINT8*)pstMpcMsg);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_SndInternalXsmsRefreshMrTracking
 功能描述  :
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月27日
    作    者   : c00299064
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XPDS_SndInternalXsmsRefreshMrTracking(
    TAF_XPDS_REJ_MR_TRACK_CAUSE_CODE_ENUM_UINT8             enCauseCode
)
{
    TAF_XPDS_XPDS_INT_XSMS_REFRESH_MR_TRACK_SESSION_STRU   *pstMpcMsg = VOS_NULL_PTR;;

    pstMpcMsg = (TAF_XPDS_XPDS_INT_XSMS_REFRESH_MR_TRACK_SESSION_STRU*)PS_MEM_ALLOC(
                                                    UEPS_PID_XPDS,
                                                    sizeof(TAF_XPDS_XPDS_INT_XSMS_REFRESH_MR_TRACK_SESSION_STRU));

    if (VOS_NULL_PTR == pstMpcMsg)
    {
        XPDS_ERROR_LOG("TAF_XPDS_SndInternalXsmsRefreshMrTracking: Memory alloc failed");
        return;
    }

    PS_MEM_SET((VOS_UINT8*)pstMpcMsg + VOS_MSG_HEAD_LENGTH, 0,
                sizeof(TAF_XPDS_XPDS_INT_XSMS_REFRESH_MR_TRACK_SESSION_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填写参数 */
    pstMpcMsg->ulSenderCpuId          = VOS_LOCAL_CPUID;
    pstMpcMsg->ulSenderPid            = UEPS_PID_XPDS;
    pstMpcMsg->ulReceiverCpuId        = VOS_LOCAL_CPUID;
    pstMpcMsg->ulReceiverPid          = UEPS_PID_XPDS;
    pstMpcMsg->ulLength               = sizeof(TAF_XPDS_XPDS_INT_XSMS_REFRESH_MR_TRACK_SESSION_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMpcMsg->enMsgId                = ID_TAF_XPDS_XPDS_INT_XSMS_REFRESH_MR_TRACK_SESSION;

    pstMpcMsg->enCauseCode            = enCauseCode;

    TAF_XPDS_PutMsgInIntMsgQueue((VOS_UINT8*)pstMpcMsg);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_SndInternalPdeProcStartReq
 功能描述  : XPDS send PDE proc start to XPDS
 输入参数  : enFixMode - Fix mode
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月28日
    作    者   : c00299064
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XPDS_SndInternalCpPdeProcStartReq(
    VOS_VOID
)
{
    TAF_XPDS_XPDS_CP_PDE_PROC_START_REQ_STRU                  *pstPdeProcStartReq = VOS_NULL_PTR;

    pstPdeProcStartReq = (TAF_XPDS_XPDS_CP_PDE_PROC_START_REQ_STRU *)PS_MEM_ALLOC(UEPS_PID_XPDS,
                                                            sizeof(TAF_XPDS_XPDS_CP_PDE_PROC_START_REQ_STRU));

    if (VOS_NULL_PTR == pstPdeProcStartReq)
    {
        XPDS_ERROR_LOG("TAF_XPDS_SndInternalPdeProcStartReq: Memory alloc failed");
        return;
    }

    PS_MEM_SET((VOS_UINT8*)pstPdeProcStartReq + VOS_MSG_HEAD_LENGTH, 0,
                sizeof(TAF_XPDS_XPDS_CP_PDE_PROC_START_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填写参数 */
    pstPdeProcStartReq->ulSenderCpuId          = VOS_LOCAL_CPUID;
    pstPdeProcStartReq->ulSenderPid            = UEPS_PID_XPDS;
    pstPdeProcStartReq->ulReceiverCpuId        = VOS_LOCAL_CPUID;
    pstPdeProcStartReq->ulReceiverPid          = UEPS_PID_XPDS;
    pstPdeProcStartReq->ulLength               = sizeof(TAF_XPDS_XPDS_CP_PDE_PROC_START_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstPdeProcStartReq->enMsgId                = ID_TAF_XPDS_XPDS_CP_PDE_PROC_START_REQ;
    pstPdeProcStartReq->enFixMode              = TAF_XPDS_GetAgpsFixMode();

    TAF_XPDS_PutMsgInIntMsgQueue((VOS_UINT8*)pstPdeProcStartReq);

    return;
}


/*****************************************************************************
 函 数 名  : TAF_XPDS_SndInternalPpmCompleteMsg
 功能描述  : procedure to send the message TAF_XPDS_XPDS_PPM_COMPLETE_MSG_STRU
 输入参数  : None
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月28日
    作    者   : c00299064
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XPDS_SndInternalPpmCompleteMsg(
    VOS_VOID
)
{
    TAF_XPDS_XPDS_PPM_COMPLETE_MSG_STRU     *pstPpmComplMsg;

    pstPpmComplMsg = (TAF_XPDS_XPDS_PPM_COMPLETE_MSG_STRU *)PS_MEM_ALLOC(UEPS_PID_XPDS,
                                                            sizeof(TAF_XPDS_XPDS_PPM_COMPLETE_MSG_STRU));

    if (VOS_NULL_PTR == pstPpmComplMsg)
    {
        XPDS_ERROR_LOG("TAF_XPDS_SndInternalPpmCompleteMsg: Memory alloc failed");
        return;
    }

    PS_MEM_SET((VOS_UINT8*)pstPpmComplMsg + VOS_MSG_HEAD_LENGTH, 0,
                sizeof(TAF_XPDS_XPDS_PPM_COMPLETE_MSG_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填写参数 */
    pstPpmComplMsg->ulSenderCpuId          = VOS_LOCAL_CPUID;
    pstPpmComplMsg->ulSenderPid            = UEPS_PID_XPDS;
    pstPpmComplMsg->ulReceiverCpuId        = VOS_LOCAL_CPUID;
    pstPpmComplMsg->ulReceiverPid          = UEPS_PID_XPDS;
    pstPpmComplMsg->ulLength               = sizeof(TAF_XPDS_XPDS_PPM_COMPLETE_MSG_STRU) - VOS_MSG_HEAD_LENGTH;
    pstPpmComplMsg->enMsgId                = ID_TAF_XPDS_XPDS_PPM_COMPLETE_NI;

    TAF_XPDS_PutMsgInIntMsgQueue((VOS_UINT8*)pstPpmComplMsg);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_SndInternalAbnormalAbortAgpsSessionInd
 功能描述  : 发送内部消息，通知异常Abort Agps Session会话
 输入参数  : TAF_XPDS_POS_PROC_RSLT_ENUM_UINT32                      enAbortScene
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月9日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XPDS_SndInternalAbnormalAbortAgpsSessionInd(
    TAF_XPDS_POS_PROC_RSLT_ENUM_UINT32                      enAbortScene
)
{
    TAF_XPDS_XPDS_INT_ABNORMAL_ABORT_AGPS_SESSION_IND_STRU *pstAbortIndMsg;

    pstAbortIndMsg = (TAF_XPDS_XPDS_INT_ABNORMAL_ABORT_AGPS_SESSION_IND_STRU *)PS_MEM_ALLOC(UEPS_PID_XPDS,
                                                       sizeof(TAF_XPDS_XPDS_INT_ABNORMAL_ABORT_AGPS_SESSION_IND_STRU));

    if (VOS_NULL_PTR == pstAbortIndMsg)
    {
        XPDS_ERROR_LOG("TAF_XPDS_SndInternalAbnormalAbortAgpsSessionInd: Memory alloc failed");
        return;
    }

    PS_MEM_SET((VOS_UINT8*)pstAbortIndMsg + VOS_MSG_HEAD_LENGTH, 0,
                sizeof(TAF_XPDS_XPDS_INT_ABNORMAL_ABORT_AGPS_SESSION_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填写参数 */
    pstAbortIndMsg->ulSenderCpuId          = VOS_LOCAL_CPUID;
    pstAbortIndMsg->ulSenderPid            = UEPS_PID_XPDS;
    pstAbortIndMsg->ulReceiverCpuId        = VOS_LOCAL_CPUID;
    pstAbortIndMsg->ulReceiverPid          = UEPS_PID_XPDS;
    pstAbortIndMsg->ulLength               = sizeof(TAF_XPDS_XPDS_INT_ABNORMAL_ABORT_AGPS_SESSION_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstAbortIndMsg->enMsgId                = ID_TAF_XPDS_XPDS_INT_ABNORMAL_ABORT_AGPS_SESSION_IND;
    pstAbortIndMsg->enAbortScene           = enAbortScene;

    TAF_XPDS_PutMsgInIntMsgQueue((VOS_UINT8*)pstAbortIndMsg);

    return;
}


VOS_UINT32 TAF_XPDS_SndControlPlaneLinkStart_CpLinkCtrl(
   VOS_VOID
)
{
    TAF_XPDS_XPDS_CP_LINK_PROC_START_REQ_STRU *pstCpLinkStart;

    pstCpLinkStart   = (TAF_XPDS_XPDS_CP_LINK_PROC_START_REQ_STRU *) PS_MEM_ALLOC(UEPS_PID_XPDS,
                                                                                                sizeof(TAF_XPDS_XPDS_CP_LINK_PROC_START_REQ_STRU));
    if (VOS_NULL_PTR == pstCpLinkStart)
    {
        XPDS_ERROR_LOG("TAF_XPDS_SndControlPlaneStart_CpLinkCtrl: malloc failed");
        return VOS_ERR;
    }

    pstCpLinkStart->ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstCpLinkStart->ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstCpLinkStart->ulSenderPid         = UEPS_PID_XPDS;
    pstCpLinkStart->ulReceiverPid       = UEPS_PID_XPDS;
    pstCpLinkStart->ulLength            = sizeof(TAF_XPDS_XPDS_CP_LINK_PROC_START_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    pstCpLinkStart->enMsgId   = ID_TAF_XPDS_XPDS_CP_LINK_START_REQ;

    TAF_XPDS_PutMsgInIntMsgQueue((VOS_UINT8*)pstCpLinkStart);

    return VOS_OK;
}


VOS_UINT32 TAF_XPDS_SndInternalCpLinkResultMsg_CpLinkCtrl(
   TAF_XPDS_POS_PROC_RSLT_ENUM_UINT32 enRslt
)
{
    TAF_XPDS_XPDS_CP_LINK_PROC_RSLT_IND_STRU *pstCpLinkRslt;

    pstCpLinkRslt   = (TAF_XPDS_XPDS_CP_LINK_PROC_RSLT_IND_STRU *) PS_MEM_ALLOC(UEPS_PID_XPDS,
                                                                                                sizeof(TAF_XPDS_XPDS_CP_LINK_PROC_RSLT_IND_STRU));
    if (VOS_NULL_PTR == pstCpLinkRslt)
    {
        XPDS_ERROR_LOG("TAF_XPDS_SndInternalCpLinkResultMsg_CpLinkCtrl: malloc failed");
        return VOS_ERR;
    }

    pstCpLinkRslt->ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstCpLinkRslt->ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstCpLinkRslt->ulSenderPid         = UEPS_PID_XPDS;
    pstCpLinkRslt->ulReceiverPid       = UEPS_PID_XPDS;
    pstCpLinkRslt->ulLength            = sizeof(TAF_XPDS_XPDS_CP_LINK_PROC_RSLT_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    pstCpLinkRslt->enMsgId   = ID_TAF_XPDS_XPDS_CP_LINK_RESULT_IND;
    pstCpLinkRslt->enRslt    = enRslt;

    TAF_XPDS_PutMsgInIntMsgQueue((VOS_UINT8*)pstCpLinkRslt);
    return VOS_OK;
}

/*lint -restore*/

#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
