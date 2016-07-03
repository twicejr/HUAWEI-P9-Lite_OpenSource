

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "vos.h"

#include "PsCommonDef.h"
#include "SmInclude.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -e958*/

#define    THIS_FILE_ID        PS_FILE_ID_NAS_SM_MULTI_MODE_C


#if (FEATURE_ON == FEATURE_LTE)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


/*****************************************************************************
  3 函数实现
*****************************************************************************/


VOS_VOID NAS_SM_SndRabmBearerActivateInd(
    VOS_UINT8                           ucNsapi,
    NAS_SM_PDP_CONTEXT_INFO_STRU       *pstPdpCtxInfo
)
{
    SM_RABM_BEARER_ACTIVATE_IND_STRU   *pstBearerActivateInd;
    VOS_UINT8                           ucAddrIndex;

    ucAddrIndex = pstPdpCtxInfo->ucAddrIndex;

    /* 构造消息 */
    pstBearerActivateInd = (SM_RABM_BEARER_ACTIVATE_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                            WUEPS_PID_SM,
                            sizeof(SM_RABM_BEARER_ACTIVATE_IND_STRU));
    if (VOS_NULL_PTR == pstBearerActivateInd)
    {
        NAS_ERROR_LOG(WUEPS_PID_SM,
            "NAS_SM_SndRabmBearerActivateInd: Memory alloc failed.");
        return;
    }

    /* 初始化消息 */
    PS_MEM_SET((VOS_CHAR*)pstBearerActivateInd + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(SM_RABM_BEARER_ACTIVATE_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填写消息头 */
    pstBearerActivateInd->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstBearerActivateInd->stMsgHeader.ulReceiverPid   = WUEPS_PID_RABM;
    pstBearerActivateInd->stMsgHeader.ulMsgName       = ID_SM_RABM_BEARER_ACTIVATE_IND;

    /* 填写消息内容 */
    pstBearerActivateInd->ulNsapi         = ucNsapi;
    pstBearerActivateInd->ulLinkdNsapi    = NAS_SM_GetPdpLinkedNsapi(ucAddrIndex);
    pstBearerActivateInd->stQos.ulLength  = pstPdpCtxInfo->QoS.ulQosLength;

    PS_MEM_CPY(pstBearerActivateInd->stQos.aucQosValue,
               pstPdpCtxInfo->QoS.aucQosValue,
               pstPdpCtxInfo->QoS.ulQosLength);

    /* 发送消息 */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_SM, pstBearerActivateInd))
    {
        NAS_ERROR_LOG(WUEPS_PID_SM,
            "NAS_SM_SndRabmBearerActivateInd: Send message failed.");
    }

    return;

}


VOS_VOID NAS_SM_SndRabmBearerModifyInd(
    VOS_UINT8                           ucNsapi,
    NAS_SM_PDP_CONTEXT_INFO_STRU       *pstPdpCtxInfo
)
{
    SM_RABM_BEARER_MODIFY_IND_STRU     *pstBearerModifyInd;

    /* 构造消息 */
    pstBearerModifyInd = (SM_RABM_BEARER_MODIFY_IND_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                            WUEPS_PID_SM,
                            sizeof(SM_RABM_BEARER_MODIFY_IND_STRU));
    if (VOS_NULL_PTR == pstBearerModifyInd)
    {
        NAS_ERROR_LOG(WUEPS_PID_SM,
            "NAS_SM_SndRabmBearerModifyInd: Memory alloc failed.");
        return;
    }

    /* 初始化消息 */
    PS_MEM_SET((VOS_CHAR*)pstBearerModifyInd + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(SM_RABM_BEARER_MODIFY_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填写消息头 */
    pstBearerModifyInd->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstBearerModifyInd->stMsgHeader.ulReceiverPid   = WUEPS_PID_RABM;
    pstBearerModifyInd->stMsgHeader.ulMsgName       = ID_SM_RABM_BEARER_MODIFY_IND;

    /* 填写消息内容 */
    pstBearerModifyInd->ulNsapi         = ucNsapi;
    pstBearerModifyInd->stQos.ulLength  = pstPdpCtxInfo->QoS.ulQosLength;

    PS_MEM_CPY(pstBearerModifyInd->stQos.aucQosValue,
               pstPdpCtxInfo->QoS.aucQosValue,
               pstPdpCtxInfo->QoS.ulQosLength);

    /* 发送消息 */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_SM, pstBearerModifyInd))
    {
        NAS_ERROR_LOG(WUEPS_PID_SM,
            "NAS_SM_SndRabmBearerModifyInd: Send message failed.");
    }

    return;

}


VOS_VOID NAS_SM_SndRabmBearerDeactivateInd(
    VOS_UINT8                           ucNsapi,
    NAS_SM_PDP_CONTEXT_INFO_STRU       *pstPdpCtxInfo
)
{
    SM_RABM_BEARER_DEACTIVATE_IND_STRU *pstBearerDeactivateInd;

    /* 构造消息 */
    pstBearerDeactivateInd = (SM_RABM_BEARER_DEACTIVATE_IND_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                WUEPS_PID_SM,
                                sizeof(SM_RABM_BEARER_DEACTIVATE_IND_STRU));
    if (VOS_NULL_PTR == pstBearerDeactivateInd)
    {
        NAS_ERROR_LOG(WUEPS_PID_SM,
            "NAS_SM_SndRabmBearerDeactivateInd: Memory alloc failed.");
        return;
    }

    /* 初始化消息 */
    PS_MEM_SET((VOS_CHAR*)pstBearerDeactivateInd + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(SM_RABM_BEARER_DEACTIVATE_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填写消息头 */
    pstBearerDeactivateInd->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstBearerDeactivateInd->stMsgHeader.ulReceiverPid   = WUEPS_PID_RABM;
    pstBearerDeactivateInd->stMsgHeader.ulMsgName       = ID_SM_RABM_BEARER_DEACTIVATE_IND;

    /* 填写消息内容 */
    pstBearerDeactivateInd->ulNsapi                     = ucNsapi;

    /* 发送消息 */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_SM, pstBearerDeactivateInd))
    {
        NAS_ERROR_LOG(WUEPS_PID_SM,
            "NAS_SM_SndRabmBearerDeactivateInd: Send message failed.");
    }

    return;

}



VOS_VOID NAS_SM_RcvTafBearerActivateInd(
    SMREG_BEARER_ACTIVATE_IND_STRU     *pstBearerActivateInd
)
{
    NAS_SM_PDP_CONTEXT_INFO_STRU       *pstPdpCtxInfo;
    NAS_SM_PDP_ADDR_INFO_STRU          *pstPdpAddrInfo;
    VOS_UINT8                           ucTi;
    VOS_UINT8                           ucCr;
    VOS_UINT8                           ucAddrIndex;
    VOS_UINT8                           ucNsapiCnt;
    VOS_UINT8                           ucPdpCtxIndex;
    VOS_UINT8                           ucLinkedPdpCtxIndex;

    /*----------------------------------------------------------------
       提取TI: 根据TiFlag决定TI的取值范围, 以网侧下发TI为准
               若TiFlag为TRUE(SM_TI_MS_ORG), TI取值区间[128, 254]
               若TiFlag为FALSE(SM_TI_NET_ORG), TI取值区间[0, 127]
    ----------------------------------------------------------------*/
    ucTi = (VOS_FALSE == pstBearerActivateInd->stTransId.ucTiFlag) ?
           (pstBearerActivateInd->stTransId.ucTiValue) :
           (pstBearerActivateInd->stTransId.ucTiValue + 0x80);

    /* 提取CR(PDPID) */
    ucCr = pstBearerActivateInd->ucConnectId;

    /* 检查是否存在和TI和CR对应的PDP CONTEXT */
    if (0xFF != NAS_SM_GetNsapiFromTiMap(ucTi))
    {
        NAS_ERROR_LOG(WUEPS_PID_SM,
            "NAS_SM_RcvTafBearerActivateInd: NSAPI is used by other PDP.");
        return;
    }

    /* 获取NSAPI对应的PDP CONTEXT索引: PDP_INDEX = NSPAI - NSAPI_OFFSET(5) */
    ucPdpCtxIndex           = pstBearerActivateInd->ucNsapi - SM_NSAPI_OFFSET;

    /* 获取当前PDP CONTEXT内容地址 */
    pstPdpCtxInfo           = NAS_SM_GetPdpCtxInfoAddr(ucPdpCtxIndex);

    if (SM_PDP_ACTIVE_PENDING == pstPdpCtxInfo->ucState)
    {
        /* 将SM实体状态置为INACTIVE */
        pstPdpCtxInfo->ucState  = SM_PDP_INACTIVE;

        /* 清除TI与PDP INDEX的映射关系 */
        NAS_SM_ClearNsapiToTiMap(pstPdpCtxInfo->ucTi);

        /* 清除CR与PDP INDEX的映射关系 */
        NAS_SM_ClearNsapiToCrMap(ucCr);

        /* 清除对应的PDP实体信息 */
        SM_ComClearPdpCntxt(ucPdpCtxIndex);
        SM_ComDelNsapiFromAddr(NAS_SM_GetPdpAddrIndex(ucPdpCtxIndex), ucPdpCtxIndex);

        /* 通知GMM更新PDP CONTEXT状态 */
        NAS_SM_SndGmmPdpStatusInd();

        /* 通知RABM更新状态 */
        SM_SndRabmSmDeactivateInd(1, &ucPdpCtxIndex);

        /* 通知GMM清除SM缓存 */
        NAS_SM_SndGmmAbortReq();

        NAS_SM_SndGmmPdpDeactivatedInd();
    }

    /* 更新PDP实体状态为SM_PDP_INACTIVE */
    pstPdpCtxInfo->ucState  = SM_PDP_ACTIVE;

    /* 更新TI、CR(PDPID)与NSAPI的映射表 */
    NAS_SM_SetNsapiToTiMap(ucTi, ucPdpCtxIndex);
    NAS_SM_SetNsapiToCrMap(ucCr, ucPdpCtxIndex);

    /* 更新TI信息 */
    if (VOS_FALSE == pstBearerActivateInd->stTransId.ucTiFlag)
    {
        pstPdpCtxInfo->ucTiFlg = SM_TI_NET_ORG;
    }
    else
    {
        pstPdpCtxInfo->ucTiFlg = SM_TI_MS_ORG;
    }

    pstPdpCtxInfo->ucTi       = ucTi;

    /* 更新PDP CONTEXT信息中的CR, USER CHID, RADIO PRIORITY */
    pstPdpCtxInfo->ucCr       = ucCr;

    if (VOS_TRUE == pstBearerActivateInd->bitOpRadioPriority)
    {
        pstPdpCtxInfo->ucRadioPri = pstBearerActivateInd->ucRadioPriority;
    }

    /* 更新PDP ADDR和APN信息 */
    if (VOS_TRUE != pstBearerActivateInd->bitOpLinkedNsapi)
    {
        /* 获取未使用的PDP ADDRESS索引 */
        ucAddrIndex     = SM_ComFindNullAddrApn();
        pstPdpAddrInfo  = NAS_SM_GetPdpAddrInfoAddr(ucAddrIndex);

        /* 更新PDP CONTEXT信息中的ADRESS INDEX */
        pstPdpCtxInfo->ucAddrIndex  = ucAddrIndex;

        /* 更新PDP ADDRESS信息中的NSAPI(PDP实体索引) */
        pstPdpAddrInfo->ucNsapiCnt  = 1;
        pstPdpAddrInfo->aucNsapi[0] = ucPdpCtxIndex;

        /* 更新PDP ADDRESS信息 */
        NAS_SM_SetPdpAddrFlg(ucAddrIndex);
        pstPdpAddrInfo->PdpAddrInfo.ulAddrLength = pstBearerActivateInd->stPdpAddr.ulPdpAddrLen;
        PS_MEM_CPY(pstPdpAddrInfo->PdpAddrInfo.aucAddrValue,
                   pstBearerActivateInd->stPdpAddr.aucPdpAddr,
                   pstBearerActivateInd->stPdpAddr.ulPdpAddrLen);

        /* 更新APN信息 */
        if (VOS_TRUE == pstBearerActivateInd->bitOpApn)
        {
            pstPdpAddrInfo->PdpApn.ulApnLength = pstBearerActivateInd->stApn.ulApnLen;

            PS_MEM_CPY(pstPdpAddrInfo->PdpApn.aucApnValue,
                       pstBearerActivateInd->stApn.aucApnAddr,
                       NAS_SM_MAX_APN_LEN);
        }
    }
    else
    {
        /* 获取LINKED NSAPI对应的PDP CONTEXT索引: LINKED_PDP_INDEX = LINKED_NSPAI - NSAPI_OFFSET(5) */
        ucLinkedPdpCtxIndex = pstBearerActivateInd->ucLinkedNsapi - SM_NSAPI_OFFSET;

        /* 根据LINKED NSAPI获取对应的PRIMARY PDP ADDR信息 */
        ucAddrIndex     = NAS_SM_GetPdpAddrIndex(ucLinkedPdpCtxIndex);
        pstPdpAddrInfo  = NAS_SM_GetPdpAddrInfoAddr(ucAddrIndex);

        /* 更新PDP CONTEXT信息中的PDP ADDRESS索引 */
        pstPdpCtxInfo->ucAddrIndex = ucAddrIndex;

        /* 更新PDP ADDRESS信息中的NSAPI(PDP实体索引) */
        ucNsapiCnt  = pstPdpAddrInfo->ucNsapiCnt;
        pstPdpAddrInfo->aucNsapi[ucNsapiCnt] = ucPdpCtxIndex;
        pstPdpAddrInfo->ucNsapiCnt++;
    }

    /* 更新QOS信息 */
    if (VOS_TRUE == pstBearerActivateInd->bitOpPdpQos)
    {
        pstPdpCtxInfo->QoS.ulQosLength = pstBearerActivateInd->stNegQos.ulQosLen;

        PS_MEM_CPY(pstPdpCtxInfo->QoS.aucQosValue,
                   pstBearerActivateInd->stNegQos.aucQos,
                   NAS_SM_MAX_QOS_LEN);
    }
    else
    {
        pstPdpCtxInfo->QoS.ulQosLength = 0;
        PS_MEM_SET(pstPdpCtxInfo->QoS.aucQosValue,
                   0x00,
                   sizeof(pstPdpCtxInfo->QoS.aucQosValue));
    }

    /* 通知GMM更新PDP CONTEXT状态 */
    NAS_SM_SndGmmPdpStatusInd();

    /* 通知RABM更新状态 */
    NAS_SM_SndRabmBearerActivateInd(pstBearerActivateInd->ucNsapi, pstPdpCtxInfo);

}


VOS_VOID NAS_SM_RcvTafBearerModifyInd(
    SMREG_BEARER_MODIFY_IND_STRU       *pstBearerModifyInd
)
{
    NAS_SM_PDP_CONTEXT_INFO_STRU       *pstPdpCtxInfo;
    VOS_UINT8                           ucPdpCtxIndex;
    VOS_UINT8                           ucTi;
    VOS_UINT8                           ucNsapi;

    /*----------------------------------------------------------------
       提取TI: 根据TiFlag决定TI的取值范围, 以网侧下发TI为准
               若TiFlag为TRUE(SM_TI_MS_ORG), TI取值区间[128, 254]
               若TiFlag为FALSE(SM_TI_NET_ORG), TI取值区间[0, 127]
    ----------------------------------------------------------------*/
    ucTi = (VOS_FALSE == pstBearerModifyInd->stTransId.ucTiFlag) ?
           (pstBearerModifyInd->stTransId.ucTiValue) :
           (pstBearerModifyInd->stTransId.ucTiValue + 0x80);


    /* 获取TI对应的PDP CONTEXT索引 */
    ucPdpCtxIndex = NAS_SM_GetNsapiFromTiMap(ucTi);

    /* 检查是否存在和TI和CR对应的PDP CONTEXT */
    if (0xFF == ucPdpCtxIndex)
    {
        NAS_ERROR_LOG(WUEPS_PID_SM,
            "NAS_SM_RcvTafBearerModifyInd: NSAPI is not used.");
        return;
    }

    /* 获取PDP CONTEXT索引对应的NSAPI: NSAPI = PDP_INDEX - NSAPI_OFFSET(5) */
    ucNsapi         = ucPdpCtxIndex + SM_NSAPI_OFFSET;

    /* 获取当前PDP CONTEXT内容地址 */
    pstPdpCtxInfo = NAS_SM_GetPdpCtxInfoAddr(ucPdpCtxIndex);

    /* 更新RADIO PRIORITY */
    if (VOS_TRUE == pstBearerModifyInd->bitOpRadioPriority)
    {
        pstPdpCtxInfo->ucRadioPri = pstBearerModifyInd->ucRadioPriority;
    }

    /* 更新QOS信息 */
    if (VOS_TRUE == pstBearerModifyInd->bitOpPdpQos)
    {
        pstPdpCtxInfo->QoS.ulQosLength = pstBearerModifyInd->stNegQos.ulQosLen;

        PS_MEM_CPY(pstPdpCtxInfo->QoS.aucQosValue,
                   pstBearerModifyInd->stNegQos.aucQos,
                   NAS_SM_MAX_QOS_LEN);
    }

    /* 通知RABM更新状态 */
    NAS_SM_SndRabmBearerModifyInd(ucNsapi, pstPdpCtxInfo);
}


VOS_VOID NAS_SM_RcvTafBearerDeactivateInd(
    SMREG_BEARER_DEACTIVATE_IND_STRU   *pstBearerDeactivateInd
)
{
    NAS_SM_PDP_CONTEXT_INFO_STRU       *pstPdpCtxInfo;
    VOS_UINT8                           ucTi;
    VOS_UINT8                           ucCr;
    VOS_UINT8                           ucPdpCtxIndex;
    VOS_UINT8                           ucAddrIndex;
    VOS_UINT8                           ucNsapi;

    /*----------------------------------------------------------------
       提取TI: 根据TiFlag决定TI的取值范围, 以网侧下发TI为准
               若TiFlag为TRUE(SM_TI_MS_ORG), TI取值区间[0, 127]
               若TiFlag为FALSE(SM_TI_NET_ORG), TI取值区间[128, 254]
    ----------------------------------------------------------------*/
    ucTi = (VOS_FALSE == pstBearerDeactivateInd->stTransId.ucTiFlag) ?
           (pstBearerDeactivateInd->stTransId.ucTiValue) :
           (pstBearerDeactivateInd->stTransId.ucTiValue + 0x80);


    ucCr            = pstBearerDeactivateInd->ucConnectId;

    /* 获取TI对应的PDP CONTEXT索引 */
    ucPdpCtxIndex   = NAS_SM_GetNsapiFromTiMap(ucTi);

    /* 获取PDP CONTEXT索引对应的NSAPI: NSAPI = PDP_INDEX - NSAPI_OFFSET(5) */
    ucNsapi         = ucPdpCtxIndex + SM_NSAPI_OFFSET;

    /* 检查是否存在和TI和CR对应的PDP CONTEXT */
    if (0xFF == ucPdpCtxIndex)
    {
        NAS_ERROR_LOG(WUEPS_PID_SM,
            "NAS_SM_RcvTafBearerDeactivateInd: NSAPI is not used.");
        return;
    }

    /* 获取当前PDP CONTEXT内容地址 */
    pstPdpCtxInfo   = NAS_SM_GetPdpCtxInfoAddr(ucPdpCtxIndex);

    /* 获取PDP ADDRESS索引 */
    ucAddrIndex     = NAS_SM_GetPdpAddrIndex(ucPdpCtxIndex);

    /* 更新PDP实体状态为SM_PDP_INACTIVE */
    pstPdpCtxInfo->ucState  = SM_PDP_INACTIVE;

    /* 清除TI与PDP INDEX的映射关系 */
    NAS_SM_ClearNsapiToTiMap(ucTi);

    /* 清除CR与PDP INDEX的映射关系 */
    NAS_SM_ClearNsapiToCrMap(ucCr);

    /* 清除对应的PDP实体信息 */
    SM_ComClearPdpCntxt(ucPdpCtxIndex);
    SM_ComDelNsapiFromAddr(ucAddrIndex, ucPdpCtxIndex);

    /* 通知GMM更新PDP CONTEXT状态 */
    NAS_SM_SndGmmPdpStatusInd();

    /* 通知RABM更新状态 */
    NAS_SM_SndRabmBearerDeactivateInd(ucNsapi, pstPdpCtxInfo);

}
#endif

/*lint +e958*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


