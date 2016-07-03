

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "PsLib.h"

#include "PsCommonDef.h"
#include "PsTypeDef.h"
#include "TafLog.h"
#include "Taf_Aps.h"
#include "TafSmInterface.h"
#include "TafApsSndSm.h"
#include "TafApsCtx.h"


#ifdef __cplusplus
#if __cplusplus
    extern "C" {
#endif
#endif

/*lint -e958*/

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_TAF_APS_SNDSM_C

/******************************************************************************
   2 外部函数变量声明
******************************************************************************/

/******************************************************************************
   3 私有定义
******************************************************************************/


/******************************************************************************
   4 全局变量定义
*****************************************************************************/


/******************************************************************************
   5 函数实现
******************************************************************************/

MSG_HEADER_STRU*  TAF_APS_AllocMsgToSmAndFillMsgHeader(SM_TAF_MSG_ID_ENUM_UINT32 enMsgId)
{
    VOS_UINT8                           ucLoop;
    MSG_HEADER_STRU                    *pstMsg;
    APS_SM_MSG_ID_MAP_TO_LEN_STRU       astMsgIdMapsToLen[] = {
                    {ID_SMREG_PDP_ACTIVATE_REQ,         sizeof(SMREG_PDP_ACTIVATE_REQ_STRU)},
                    {ID_SMREG_PDP_ACTIVATE_SEC_REQ,     sizeof(SMREG_PDP_ACTIVATE_SEC_REQ_STRU)},
                    {ID_SMREG_PDP_ACTIVATE_REJ_RSP,     sizeof(SMREG_PDP_ACTIVATE_REJ_RSP_STRU)},
                    {ID_SMREG_PDP_DEACTIVATE_REQ,       sizeof(SMREG_PDP_DEACTIVATE_REQ_STRU)},
                    {ID_SMREG_PDP_MODIFY_REQ,           sizeof(SMREG_PDP_MODIFY_REQ_STRU)},
                    {ID_SMREG_PDP_MODIFY_RSP,           sizeof(SMREG_PDP_MODIFY_RSP_STRU)},
                    {ID_SMREG_PDP_MODIFY_REJ_RSP,       sizeof(SMREG_PDP_MODIFY_REJ_RSP_STRU)},
                    {ID_SMREG_PDP_ABORT_REQ,            sizeof(SMREG_PDP_ABORT_REQ_STRU)},
                    {ID_SMREG_PDP_LOCAL_DEACTIVATE_REQ, sizeof(SMREG_PDP_LOCAL_DEACTIVATE_REQ_STRU)}
#if (FEATURE_ON == FEATURE_LTE)
                   ,{ID_SMREG_BEARER_ACTIVATE_IND,      sizeof(SMREG_BEARER_ACTIVATE_IND_STRU)},
                    {ID_SMREG_BEARER_MODIFY_IND,        sizeof(SMREG_BEARER_MODIFY_IND_STRU)},
                    {ID_SMREG_BEARER_DEACTIVATE_IND,    sizeof(SMREG_BEARER_DEACTIVATE_IND_STRU)}
#endif
                    };

    for (ucLoop = 0; ucLoop < (sizeof(astMsgIdMapsToLen) / sizeof(APS_SM_MSG_ID_MAP_TO_LEN_STRU)); ucLoop++)
    {
        if (astMsgIdMapsToLen[ucLoop].enMsgId == enMsgId)
        {
            break;
        }
    }

    if (ucLoop == (sizeof(astMsgIdMapsToLen) / sizeof(APS_SM_MSG_ID_MAP_TO_LEN_STRU)))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_APS_AllocMsgToSmAndFillMsgHeader: Invalid Msg Id.");
        return VOS_NULL_PTR;
    }

    /* 构造消息 */
    pstMsg = (MSG_HEADER_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF, astMsgIdMapsToLen[ucLoop].ulMsgLen);
    if (VOS_NULL_PTR == pstMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_APS_AllocMsgToSmAndFillMsgHeader: Memory alloc failed..");
        return VOS_NULL_PTR;
    }

    /* 初始化消息 */
    PS_MEM_SET((VOS_CHAR*)pstMsg + VOS_MSG_HEAD_LENGTH,
               0x00,
               astMsgIdMapsToLen[ucLoop].ulMsgLen - VOS_MSG_HEAD_LENGTH);

    /* 填写消息头 */
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = WUEPS_PID_SM;
    pstMsg->ulMsgName       = enMsgId;

    return pstMsg;
}



VOS_VOID TAF_APS_SndSmPdpAbortReq(
    VOS_UINT8                           ucPdpId
)
{
    SMREG_PDP_ABORT_REQ_STRU            *pstSmPdpAbortReq;

    /* 构造消息并填充消息头 */
    pstSmPdpAbortReq = (SMREG_PDP_ABORT_REQ_STRU *)TAF_APS_AllocMsgToSmAndFillMsgHeader(ID_SMREG_PDP_ABORT_REQ);
    if (VOS_NULL_PTR == pstSmPdpAbortReq)
    {
        return;
    }

    /* 填写 ConnectId (CR)，当前CR等同于Pdp Id */
    pstSmPdpAbortReq->ucConnectId = ucPdpId;

    /* 发送消息 */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TAF, pstSmPdpAbortReq))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_APS_SndSmPdpAbortReq: Send message failed.");
        return;
    }

    return;
}


VOS_VOID TAF_APS_SndSmPdpLocalDeactivateReq(
    VOS_UINT8                           ucPdpId
)
{
    SMREG_PDP_LOCAL_DEACTIVATE_REQ_STRU *pstSmPdpLocalDeactivateReq;

    /* 构造消息并填充消息头 */
    pstSmPdpLocalDeactivateReq = (SMREG_PDP_LOCAL_DEACTIVATE_REQ_STRU *)TAF_APS_AllocMsgToSmAndFillMsgHeader(ID_SMREG_PDP_LOCAL_DEACTIVATE_REQ);
    if (VOS_NULL_PTR == pstSmPdpLocalDeactivateReq)
    {
        return;
    }

    /* 填写 ConnectId (CR)，当前CR等同于Pdp Id */
    pstSmPdpLocalDeactivateReq->ucConnectId   = ucPdpId;

    /* 发送消息 */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TAF, pstSmPdpLocalDeactivateReq))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_APS_SndSmPdpLocalDeactivateReq: Send message failed.");
        return;
    }

    return;
}


/*lint +e958*/


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



