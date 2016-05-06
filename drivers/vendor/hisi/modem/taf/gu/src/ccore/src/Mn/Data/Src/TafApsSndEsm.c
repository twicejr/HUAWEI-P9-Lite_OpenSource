/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafApsSndEsm.c　
  版 本 号   : 初稿
  作    者   : w00316404
  生成日期   : 2015年12月7日
  最近修改   :
  功能描述   : 给Esm的消息发送函数
  函数列表   :

  修改历史   :
  1.日    期   : 2015年12月7日
    作    者   : w00316404
    修改内容   : 创建文件

******************************************************************************/
#ifdef __cplusplus
#if __cplusplus
    extern "C" {
#endif
#endif

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "TafApsSndEsm.h"

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_TAF_APS_SNDESM_C

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
/*****************************************************************************
 函 数 名  : TAF_APS_SndEsmPdpSetupReq
 功能描述  : 发送ID_APP_ESM_PDP_SETUP_REQ消息函数
 输入参数  : pstSetPdpCtxStateReq       - +CGACT命令信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月7日
    作    者   : w00316404
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_SndEsmSetCgactPdpSetupReq(
    TAF_PS_SET_PDP_STATE_REQ_STRU      *pstSetPdpCtxStateReq
)
{
    APP_ESM_PDP_SETUP_REQ_STRU         *pstPsActReq;
    VOS_UINT32                          ulLoop;

    /* 构造消息 */
    pstPsActReq = (APP_ESM_PDP_SETUP_REQ_STRU*)TAF_APS_ALLOC_MSG_WITH_HDR(
                            sizeof(APP_ESM_PDP_SETUP_REQ_STRU));

    if (VOS_NULL_PTR == pstPsActReq)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndEsmSetCgactPdpSetupReq: Memory alloc failed.");
        return;
    }

    /* 初始化消息 */
    PS_MEM_SET(TAF_APS_GET_MSG_ENTITY(pstPsActReq), 0x00, TAF_APS_GET_MSG_LENGTH(pstPsActReq));

    /* 填写消息头 */
    TAF_APS_CFG_ESM_MSG_HDR(pstPsActReq, ID_APP_ESM_PDP_SETUP_REQ);

    /* 遍历copy所有CID */
    for (ulLoop = 1; ulLoop <= TAF_MAX_CID; ulLoop++ )
    {
        if(pstSetPdpCtxStateReq->stCidListStateInfo.aucCid[ulLoop])
        {
            break;
        }
    }

    /* 填写消息内容 */
    pstPsActReq->enSetupType         = APP_ESM_PDP_SETUP_TYPE_NORMAL;
    pstPsActReq->ulCid               = ulLoop;

    /* 发送消息 */
    TAF_APS_SEND_MSG(pstPsActReq);

    return;

}

/*****************************************************************************
 函 数 名  : TAF_APS_SndEsmPdpReleaseReq
 功能描述  : 发送ID_APP_ESM_PDP_RELEASE_REQ消息函数
 输入参数  : pstSetPdpCtxStateReq       - +CGACT命令信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月7日
    作    者   : w00316404
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_SndEsmSetCgactPdpReleaseReq(
    TAF_PS_SET_PDP_STATE_REQ_STRU      *pstSetPdpCtxStateReq
)
{
    APP_ESM_PDP_RELEASE_REQ_STRU       *pstPsDeactReq;
    VOS_UINT32                          ulLoop;

    /* 构造消息 */
    pstPsDeactReq = (APP_ESM_PDP_RELEASE_REQ_STRU*)TAF_APS_ALLOC_MSG_WITH_HDR(
                            sizeof(APP_ESM_PDP_RELEASE_REQ_STRU));

    if (VOS_NULL_PTR == pstPsDeactReq)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndEsmSetCgactPdpReleaseReq: Memory alloc failed.");
        return;
    }

    /* 初始化消息 */
    PS_MEM_SET(TAF_APS_GET_MSG_ENTITY(pstPsDeactReq), 0x00, TAF_APS_GET_MSG_LENGTH(pstPsDeactReq));

    /* 填写消息头 */
    TAF_APS_CFG_ESM_MSG_HDR(pstPsDeactReq, ID_APP_ESM_PDP_RELEASE_REQ);

    /* 遍历copy所有CID */
    for (ulLoop = 1; ulLoop <= TAF_MAX_CID; ulLoop++ )
    {
        if(pstSetPdpCtxStateReq->stCidListStateInfo.aucCid[ulLoop])
        {
            break;
        }
    }

    /* 填写消息内容 */
    pstPsDeactReq->ulCid               = ulLoop;

    /* 发送消息 */
    TAF_APS_SEND_MSG(pstPsDeactReq);

    return;

}


/*****************************************************************************
 函 数 名  : TAF_APS_SndEsmSetCgactReq
 功能描述  : +CGACT REQ入口函数
 输入参数  : ucPdpId                    - APS实体索引
             pstSetPdpCtxStateReq       - +CGACT命令信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月7日
    作    者   : w00316404
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_SndEsmSetCgactMsgDistr(
    VOS_UINT8                           ucPdpId,
    TAF_PS_SET_PDP_STATE_REQ_STRU      *pstSetPdpCtxStateReq
)
{
    if (APS_ESM_PDP_STATE_ACTIVE == pstSetPdpCtxStateReq->stCidListStateInfo.ucState)
    {
        TAF_APS_SndEsmSetCgactPdpSetupReq(pstSetPdpCtxStateReq);
    }
    else
    {
        TAF_APS_SndEsmSetCgactPdpReleaseReq(pstSetPdpCtxStateReq);
    }

    return;

}

/*****************************************************************************
 函 数 名  : TAF_APS_SndEsmPppDialSetupReq
 功能描述  : 发送ID_APP_ESM_PDP_SETUP_REQ消息, 发起拨号
 输入参数  : pstPppDialOrigReq          - 拨号参数
             pstAuthInfo                - 鉴权信息
             pstIpcpInfo                - IPCP信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月7日
    作    者   : w00316404
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_APS_SndEsmPppDialSetupReq(
    TAF_PS_PPP_DIAL_ORIG_REQ_STRU      *pstPppDialOrigReq,
    TAF_APS_AUTH_INFO_STRU             *pstAuthInfo,
    TAF_APS_IPCP_INFO_STRU             *pstIpcpInfo
)
{
    APP_ESM_PDP_SETUP_REQ_STRU         *pstReq;

    /* 构造消息 */
    pstReq = (APP_ESM_PDP_SETUP_REQ_STRU*)TAF_APS_ALLOC_MSG_WITH_HDR(
                            sizeof(APP_ESM_PDP_SETUP_REQ_STRU));

    if (VOS_NULL_PTR == pstReq)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndEsmPppDialSetupReq: Memory alloc failed.");
        return;
    }

    /* 初始化消息 */
    PS_MEM_SET(TAF_APS_GET_MSG_ENTITY(pstReq), 0x00, TAF_APS_GET_MSG_LENGTH(pstReq));

    /* 填写消息头 */
    TAF_APS_CFG_ESM_MSG_HDR(pstReq, ID_APP_ESM_PDP_SETUP_REQ);

    /* 填写消息内容 */
    pstReq->enSetupType             = APP_ESM_PDP_SETUP_TYPE_PPP;
    pstReq->ulCid                   = pstPppDialOrigReq->stPppDialParaInfo.ucCid;

    PS_MEM_CPY((VOS_UINT8*)(&pstReq->stPppInfo.stAuthInfo),
               (VOS_UINT8*)(pstAuthInfo),
               sizeof(APP_ESM_AUTH_INFO_STRU));

    PS_MEM_CPY((VOS_UINT8*)(&pstReq->stPppInfo.stIpcpInfo),
               (VOS_UINT8*)(pstIpcpInfo),
               sizeof(APP_ESM_IPCP_INFO_STRU));

    /* 发送消息 */
    TAF_APS_SEND_MSG(pstReq);

    return;

}

/*****************************************************************************
 函 数 名  : TAF_APS_SndEsmNdisconnReq
 功能描述  : 发送ID_APP_ESM_NDISCONN_REQ消息, 发起拨号
 输入参数  : pstCallOrigReq             - 拨号参数
 输出参数  : 无
 返 回 值  : VOS_OK                     - 发送消息成功
             VOS_ERR                    - 发送消息失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月7日
    作    者   : w00316404
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_APS_SndEsmNdisconnReq(
    TAF_PS_CALL_ORIG_REQ_STRU          *pstCallOrigReq
)
{
    APP_ESM_NDISCONN_REQ_STRU          *pstReq;

    /* 构造消息 */
    pstReq = (APP_ESM_NDISCONN_REQ_STRU*)TAF_APS_ALLOC_MSG_WITH_HDR(
                            sizeof(APP_ESM_NDISCONN_REQ_STRU));
    if (VOS_NULL_PTR == pstReq)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndEsmNdisconnReq: Memory alloc failed.");
        return VOS_ERR;
    }

    /* 初始化消息 */
    PS_MEM_SET(TAF_APS_GET_MSG_ENTITY(pstReq), 0x00, TAF_APS_GET_MSG_LENGTH(pstReq));

    /* 填写消息头 */
    TAF_APS_CFG_ESM_MSG_HDR(pstReq, ID_APP_ESM_NDISCONN_REQ);

    /* 填写消息内容 */
    pstReq->ulCid                       = pstCallOrigReq->stDialParaInfo.ucCid;

    pstReq->bitOpPdnType                = 1;
    pstReq->bitOpApn                    = 1;  /* 缺省承载无关联的CID*/
    pstReq->bitOpGwAuth                 = 1;

    pstReq->bitOpIpv4AddrAlloc          = pstCallOrigReq->stDialParaInfo.bitOpIpv4AddrAlloc;
    pstReq->bitOpPcscfDiscovery         = pstCallOrigReq->stDialParaInfo.bitOpPcscfDiscovery;
    pstReq->bitOpImCnSignalFlg          = pstCallOrigReq->stDialParaInfo.bitOpImCnSignalFlg;

    pstReq->enIpv4AddrAlloc             = pstCallOrigReq->stDialParaInfo.enIpv4AddrAlloc;
    pstReq->enPcscfDiscovery            = pstCallOrigReq->stDialParaInfo.enPcscfDiscovery;
    pstReq->enImCnSignalFlg             = pstCallOrigReq->stDialParaInfo.enImCnSignalFlg;

    pstReq->enPdnType                   = pstCallOrigReq->stDialParaInfo.enPdpType;

    if ((VOS_TRUE                      == pstCallOrigReq->stDialParaInfo.bitOpReqType)
     && (TAF_PDP_REQUEST_TYPE_HANDOVER == pstCallOrigReq->stDialParaInfo.enPdpRequestType))
    {
        pstReq->enPdnReqestType = APP_ESM_PDN_REQUEST_TYPE_HANDOVER;
    }
    else
    {
        pstReq->enPdnReqestType = APP_ESM_PDN_REQUEST_TYPE_INITIAL;
    }

    if (VOS_TRUE == pstCallOrigReq->stDialParaInfo.bitOpEmergencyInd)
    {
        pstReq->enEmergencyInd          = pstCallOrigReq->stDialParaInfo.enEmergencyInd;
    }
    else
    {
        pstReq->enEmergencyInd          = APS_L4A_PDP_NOT_FOR_EMC;
    }


    if (VOS_TRUE == pstCallOrigReq->stDialParaInfo.bitOpApn)
    {
        pstReq->stApnInfo.ucApnLen      = (VOS_UINT8)VOS_StrLen((VOS_CHAR *)pstCallOrigReq->stDialParaInfo.aucApn);
        PS_MEM_CPY(pstReq->stApnInfo.aucApnName,
                   pstCallOrigReq->stDialParaInfo.aucApn,
                   pstReq->stApnInfo.ucApnLen);

        PIH_GetVsimAPN(APS_L4A_MAX_APN_LEN, pstReq->stApnInfo.aucApnName, &pstReq->stApnInfo.ucApnLen);
    }

    if ( (VOS_TRUE == pstCallOrigReq->stDialParaInfo.bitOpAuthType )
      && (TAF_PDP_AUTH_TYPE_NONE != pstCallOrigReq->stDialParaInfo.enAuthType))
    {
        /* USER NAME*/
        if (VOS_TRUE == pstCallOrigReq->stDialParaInfo.bitOpUserName)
        {
            pstReq->stGwAuthInfo.ucUserNameLen = (VOS_UINT8)VOS_StrLen((VOS_CHAR *)pstCallOrigReq->stDialParaInfo.aucUserName);
            PS_MEM_CPY(pstReq->stGwAuthInfo.aucUserName,
                       pstCallOrigReq->stDialParaInfo.aucUserName,
                       sizeof(pstReq->stGwAuthInfo.aucUserName));
        }

        /* PASSWORD*/
        if (VOS_TRUE == pstCallOrigReq->stDialParaInfo.bitOpPassWord)
        {
            pstReq->stGwAuthInfo.ucPwdLen = (VOS_UINT8)VOS_StrLen((VOS_CHAR *)pstCallOrigReq->stDialParaInfo.aucPassWord);
            PS_MEM_CPY(pstReq->stGwAuthInfo.aucPwd,
                       pstCallOrigReq->stDialParaInfo.aucPassWord,
                       sizeof(pstReq->stGwAuthInfo.aucPwd));
        }

        pstReq->stGwAuthInfo.enGwAuthType = (VOS_UINT8)pstCallOrigReq->stDialParaInfo.enAuthType;
    }

    /* 发送消息 */
    TAF_APS_SEND_MSG(pstReq);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : TAF_APS_SndEsmPdpModifyReq
 功能描述  : 发送ID_APP_ESM_PDP_MODIFY_REQ消息, 断开拨号
 输入参数  : pstCallModifyReq           - 修改EPS承载参数
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月7日
    作    者   : w00316404
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_SndEsmPdpModifyReq(
    TAF_PS_CALL_MODIFY_REQ_STRU        *pstCallModifyReq
)
{
    APP_ESM_INQ_PARA_REQ_STRU          *pstModifyReq;
    VOS_UINT32                          ulLoop;

    /* 构造消息 */
    pstModifyReq = (APP_ESM_INQ_PARA_REQ_STRU*)TAF_APS_ALLOC_MSG_WITH_HDR(
                            sizeof(APP_ESM_INQ_PARA_REQ_STRU));

    if (VOS_NULL_PTR == pstModifyReq)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndEsmPdpModifyReq: Memory alloc failed.");
        return;
    }

    /* 初始化消息 */
    PS_MEM_SET(TAF_APS_GET_MSG_ENTITY(pstModifyReq), 0x00, TAF_APS_GET_MSG_LENGTH(pstModifyReq));

    /* 填写消息头 */
    TAF_APS_CFG_ESM_MSG_HDR(pstModifyReq, ID_APP_ESM_PDP_MODIFY_REQ);

    /* 填写消息内容 */

    /* 拷贝所有的CID */
    for (ulLoop = 1; ulLoop <= TAF_MAX_CID; ulLoop++ )
    {
        if(pstCallModifyReq->stCidListInfo.aucCid[ulLoop])
        {
            break;
        }
    }

    pstModifyReq->ulCid                 = ulLoop;

    if ( pstModifyReq->ulCid == TAF_MAX_CID + 1 )
    {
        PS_MEM_FREE(WUEPS_PID_TAF, pstModifyReq);
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndEsmCallModifyReq: cid is error.");
        return;
    }

    /* 发送消息 */
    TAF_APS_SEND_MSG(pstModifyReq);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_SndEsmPdpReleaseReq
 功能描述  : 发送ID_APP_ESM_PDP_RELEASE_REQ消息, 断开拨号
 输入参数  : pstCalEndReq               - 断开拨号参数
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月7日
    作    者   : w00316404
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_APS_SndEsmPdpReleaseReq(
    TAF_PS_CALL_END_REQ_STRU           *pstCalEndReq
)
{
    APP_ESM_PDP_RELEASE_REQ_STRU       *pstReleaseReq;

    /* 构造消息 */
    pstReleaseReq = (APP_ESM_PDP_RELEASE_REQ_STRU*)TAF_APS_ALLOC_MSG_WITH_HDR(
                            sizeof(APP_ESM_PDP_RELEASE_REQ_STRU));

    if (VOS_NULL_PTR == pstReleaseReq)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndEsmPdpReleaseReq: Memory alloc failed.");
        return;
    }

    /* 初始化消息 */
    PS_MEM_SET(TAF_APS_GET_MSG_ENTITY(pstReleaseReq), 0x00, TAF_APS_GET_MSG_LENGTH(pstReleaseReq));

    /* 填写消息头 */
    TAF_APS_CFG_ESM_MSG_HDR(pstReleaseReq, ID_APP_ESM_PDP_RELEASE_REQ);

    /* 填写消息内容 */
    pstReleaseReq->ulCid = pstCalEndReq->ucCid;

    /* 发送消息 */
    TAF_APS_SEND_MSG(pstReleaseReq);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_SndEsmPdpManagerRsp
 功能描述  : 发送ID_APP_ESM_PDP_MANAGE_RSP消息, 应答网络激活
 输入参数  : ulSetupRslt           - 应答EPS激活是否接受
             ucCid                 - CID
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月7日
    作    者   : w00316404
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_SndEsmPdpManagerRsp(
    APS_ESM_BEARER_ACT_RESULT_ENUM_UINT32   ulSetupRslt,
    VOS_UINT8                               ucCid
)
{
    APP_ESM_PDP_MANAGER_RSP_STRU       *pstManageRsp;

    /* 构造消息 */
    pstManageRsp = (APP_ESM_PDP_MANAGER_RSP_STRU*)TAF_APS_ALLOC_MSG_WITH_HDR(
                            sizeof(APP_ESM_PDP_MANAGER_RSP_STRU));

    if (VOS_NULL_PTR == pstManageRsp)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndEsmPdpManagerRsp: Memory alloc failed.");
        return;
    }

    /* 初始化消息 */
    PS_MEM_SET(TAF_APS_GET_MSG_ENTITY(pstManageRsp), 0x00, TAF_APS_GET_MSG_LENGTH(pstManageRsp));

    /* 填写消息头 */
    TAF_APS_CFG_ESM_MSG_HDR(pstManageRsp, ID_APP_ESM_PDP_MANAGER_RSP);

    /* 填写消息内容 */
    pstManageRsp->ulCid                 = ucCid;
    pstManageRsp->ulSetupRslt           = ulSetupRslt;

    /* 发送消息 */
    TAF_APS_SEND_MSG(pstManageRsp);

    return;
}



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


