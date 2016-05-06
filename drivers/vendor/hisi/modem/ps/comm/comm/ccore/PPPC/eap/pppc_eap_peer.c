/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : pppc_eap_peer.c
  版 本 号   : 初稿
  作    者   : c00184031
  生成日期   : 2015年11月7日
  最近修改   :
  功能描述   : EAP Peer状态机处理
  函数列表   :
  修改历史   :
  1.日    期   : 2015年11月7日
    作    者   : c00184031
    修改内容   : 创建文件

******************************************************************************/



/*****************************************************************************
  1 头文件包含
*****************************************************************************/

#include "ppp_inc.h"
#include "pppc_eap_aka.h"
#include "pppc_ctrl.h"



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID          PS_FILE_ID_PPPC_EAP_PEER_C
/*lint +e767*/



/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

#if (VRP_MODULE_LINK_PPP_EAP == VRP_YES)
/* 事件状态处理函数 */
PPPC_EAP_PEER_EVENT_PROC_FUNC g_pfunEventProc[PPPC_EAP_PEER_STATE_BUTT][PPPC_EAP_PEER_EVENT_BUTT] =
{
    /* PPPC_EAP_PEER_IDLE_STATE */
    {
        PPPC_EAP_PeerIdleIdentityReq,
        PPPC_EAP_PeerNotifyReq,
        PPPC_EAP_PeerIdleNak,
        PPPC_EAP_PeerIdleAuthReq,
        VOS_NULL_PTR,
        PPPC_EAP_PeerIdleSuccess,
        PPPC_EAP_PeerIdleFailure,
        PPPC_EAP_PeerTimeout,
    },
    /* PPPC_EAP_PEER_AUTHENTICATING_STATE */
    {
        VOS_NULL_PTR,
        PPPC_EAP_PeerNotifyReq,
        VOS_NULL_PTR,
        PPPC_EAP_PeerAuthAuthReq,
        PPPC_EAP_PeerAuthNotifyAuthInd,
        PPPC_EAP_PeerAuthNotifySuccess,
        PPPC_EAP_PeerAuthNotifyFailure,
        PPPC_EAP_PeerTimeout,
    },
    /* PPPC_EAP_PEER_NOTIFYING_STATE */
    {
        VOS_NULL_PTR,
        PPPC_EAP_PeerNotifyReq,
        VOS_NULL_PTR,
        PPPC_EAP_PeerNotifyAuthReq,
        PPPC_EAP_PeerAuthNotifyAuthInd,
        PPPC_EAP_PeerAuthNotifySuccess,
        PPPC_EAP_PeerAuthNotifyFailure,
        PPPC_EAP_PeerTimeout,
    },
    /* PPPC_EAP_PEER_CLOSING_STATE */
    {
        VOS_NULL_PTR,
        PPPC_EAP_PeerClosingNotifyReq,
        VOS_NULL_PTR,
        PPPC_EAP_PeerClosingAuthReq,
        PPPC_EAP_PeerClosingAuthInd,
        PPPC_EAP_PeerClosingSuccess,
        PPPC_EAP_PeerClosingFailure,
        PPPC_EAP_PeerTimeout,
    },
    /* PPPC_EAP_PEER_CLOSED_STATE */
    {
        VOS_NULL_PTR,
        VOS_NULL_PTR,
        VOS_NULL_PTR,
        VOS_NULL_PTR,
        VOS_NULL_PTR,
        VOS_NULL_PTR,
        VOS_NULL_PTR,
        VOS_NULL_PTR,
    }
};

/* 方法处理函数 */
PPPC_EAP_METHOD_CB_STRU g_stMethodProcCB[PPPC_EAP_INTERNAL_TYPE_BUTT] =
{
    {
        VOS_NULL_PTR,
        VOS_NULL_PTR,
        VOS_NULL_PTR,
        VOS_NULL_PTR,
        VOS_NULL_PTR,
    },
    {
        VOS_NULL_PTR,
        VOS_NULL_PTR,
        VOS_NULL_PTR,
        PPPC_EAP_MD5_ProcessPkt,
        VOS_NULL_PTR,
    },
    {
        PPPC_EAP_AKA_Init,
        PPPC_EAP_AKA_InitState,
        PPPC_EAP_AKA_NotifyResult,
        PPPC_EAP_AKA_ProcessPkt,
        PPPC_EAP_AKA_PreProcessPkt,
    },
    {
        PPPC_EAP_AKA_Init,
        PPPC_EAP_AKA_InitState,
        PPPC_EAP_AKA_NotifyResult,
        PPPC_EAP_AKA_ProcessPkt,
        PPPC_EAP_AKA_PreProcessPkt,
    }
};


/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*lint -save -e958 */
/*****************************************************************************
 函 数 名  : PPPC_EAP_PreferIdenType
 功能描述  : 获取Identity的策略，目前只会返回AKA'类型，接口后续可扩展使用
 输入参数  : 无
 输出参数  : 无
 返 回 值  : PPPC_EAP_METHODS_TYPE_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月09日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
PPPC_EAP_METHODS_TYPE_ENUM_UINT8 PPPC_EAP_PreferIdenType(VOS_VOID)
{
    return PPPC_EAP_AKA_PRIME_TYPE;
}

/*****************************************************************************
 函 数 名  : PPPC_EAP_InitState
 功能描述  : 初始化方法和PEER的状态
 输入参数  : pstEapInfo     EAP实体信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月09日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_EAP_InitState
(
    PPPC_EAP_INFO_STRU                 *pstEapInfo
)
{
    /* 鉴权协商结束,初始化方法的状态  */
    if (VOS_NULL_PTR != g_stMethodProcCB[pstEapInfo->enInterType].pfuncInitMethodState)
    {
        g_stMethodProcCB[pstEapInfo->enInterType].pfuncInitMethodState();
    }

    /* 初始化PEER的状态 */
    pstEapInfo->enEapPeerState  = PPPC_EAP_PEER_IDLE_STATE;

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_EAP_SyncState
 功能描述  : 由于网络的鉴权结果报文是非确认的，传输过程中可能被丢弃导致两端
             鉴权状态不一致；如果本端鉴权结果是OK但是没有收到网络的鉴权成功
             报文却收到了VSNCP报文，说明网络已经鉴权通过了，直接将状态迁移
             到PPP_PHASE_NETWORK
 输入参数  : pstPppInfo     PPP实体信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-11-9
    作    者   : c00184031
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_EAP_SyncState(PPPINFO_S *pstPppInfo)
{
    PPPC_EAP_INFO_STRU                  *pstEapInfo;


    pstEapInfo  = (PPPC_EAP_INFO_STRU *)pstPppInfo->pstEapInfo;
    if (VOS_NULL_PTR == pstEapInfo)
    {
        PPPC_WARNING_LOG("EAP did not create");
        return;
    }

    /* 删除定时器 */
    PPPC_EAP_DeleteTimer(pstEapInfo);

    if ((VOS_OK == pstEapInfo->ulLocalResult)
        && (PPPC_EAP_PEER_CLOSING_STATE == pstEapInfo->enEapPeerState))
    {
        PPPC_EAP_InitState(pstEapInfo);

        pstPppInfo->bAuthClient = VOS_NO;

        pstPppInfo->usPhase = (VOS_UINT16)PPP_PHASE_NETWORK;
    }
    else
    {
        PPPC_WARNING_LOG2("Enter VSNCP without auth result of AN",
            pstEapInfo->ulLocalResult, pstEapInfo->enEapPeerState);
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_EAP_InitMethod
 功能描述  : 初始化方法
 输入参数  : pstEapInfo     EAP实体信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月09日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_EAP_InitMethod
(
    PPPC_EAP_INFO_STRU                 *pstEapInfo
)
{
    if ((pstEapInfo->enInterType < PPPC_EAP_INTERNAL_MD5_TYPE)
        || (pstEapInfo->enInterType >= PPPC_EAP_INTERNAL_TYPE_BUTT))
    {
        /* LCP UP时内部映射类型可能为初始值，此时不需要初始化方法 */
        return;
    }

    /* 方法初始化 */
    if (VOS_NULL_PTR != g_stMethodProcCB[pstEapInfo->enInterType].pfuncInitMethod)
    {
        g_stMethodProcCB[pstEapInfo->enInterType].pfuncInitMethod(pstEapInfo->enSelectMethod);
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_EAP_FillPayload
 功能描述  : 填充TYPE-DATA域
 输入参数  : pstEapInfo     EAP实体信息
             aucTypeData    TYPE-DATA域
             usTypeDataLen  TYPE-DATA域长度
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月09日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_EAP_FillPayload
(
    PPPC_EAP_INFO_STRU                 *pstEapInfo,
    VOS_UINT8                           aucTypeData[],
    VOS_UINT16                          usTypeDataLen
)
{
    PPPC_EAP_HEADER_STRU               *pstRespPayload;
    VOS_UINT16                          usPktLen;


    /* 填充payload域 */
    pstRespPayload  = (PPPC_EAP_HEADER_STRU *)pstEapInfo->aucRespPkt;
    pstRespPayload->ucEAPCode   = PPPC_EAP_RESPONSE_TYPE;
    pstRespPayload->ucEAPID     = pstEapInfo->ucRequestID;
    pstRespPayload->enEAPType   = pstEapInfo->enRequestType;

    usPktLen    = (VOS_UINT16)(PPPC_EAP_HEADERLEN
                + PPPC_EAP_TYPE_FIELD_LEN + usTypeDataLen);

    /* EAP报文长度填充 */
    PPPC_EAP_UpdateLen(pstEapInfo->aucRespPkt, &(pstEapInfo->usRespPktLen), usPktLen);

    /* 偏移过Code+Id+Len+Type，从TYPE-DATA域开始拷贝 */
    PS_MEM_CPY(pstEapInfo->aucRespPkt + PPPC_EAP_HEADERLEN
            + PPPC_EAP_TYPE_FIELD_LEN, aucTypeData, usTypeDataLen);

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_EAP_GetSupportMethodList
 功能描述  : 获取Identity的策略，目前只会返回AKA'类型，接口后续可扩展使用
 输入参数  : aenMethod          指示具体的方法
 输出参数  : pucMethodNum       方法的个数
 返 回 值  : PPPC_EAP_METHODS_TYPE_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月09日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPPC_EAP_GetSupportMethodList
(
    PPPC_EAP_METHODS_TYPE_ENUM_UINT8    aenMethod[],
    VOS_UINT8                          *pucMethodNum
)
{
    aenMethod[0]    = PPPC_EAP_AKA_PRIME_TYPE;
    aenMethod[1]    = PPPC_EAP_AKA_TYPE;
    aenMethod[2]    = PPPC_EAP_MD5_TYPE;

    *pucMethodNum   = 3;

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPPC_EAP_GetMethod
 功能描述  : 获取选中的方法
 输入参数  : pstEapInfo         EAP实体信息
 输出参数  : 无
 返 回 值  : VOS_OK:已选中合法的方法 VOS_ERR:未选方法
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月09日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPPC_EAP_GetMethod
(
    PPPC_EAP_INFO_STRU                 *pstEapInfo
)
{
    /* 内部调用，保证如参非空 */

    if ((pstEapInfo->enSelectMethod <= PPPC_EAP_NAK_TYPE)
        || (PPPC_EAP_EXPAND_NAK_TYPE == pstEapInfo->enSelectMethod))
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPPC_EAP_MappingMethodType
 功能描述  : 在Init状态下收到Identity Req的处理
 输入参数  : enType             协议规定的方法类型
 输出参数  : penInternalType    内部映射的方法类型
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月09日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPPC_EAP_MappingMethodType
(
    PPPC_EAP_METHODS_TYPE_ENUM_UINT8            enType,
    PPPC_EAP_METHODS_INTERNAL_TYPE_ENUM_UINT8  *penInternalType
)
{
    VOS_UINT32                          ulRet = VOS_OK;


    switch (enType)
    {
        case PPPC_EAP_MD5_TYPE:

            *penInternalType = PPPC_EAP_INTERNAL_MD5_TYPE;

            break;

        case PPPC_EAP_AKA_TYPE:

            *penInternalType = PPPC_EAP_INTERNAL_AKA_TYPE;

            break;

        case PPPC_EAP_AKA_PRIME_TYPE:

            *penInternalType = PPPC_EAP_INTERNAL_AKA_PRIME_TYPE;

            break;

        default:

            ulRet   = VOS_ERR;
            PPPC_WARNING_LOG1("Invalid input type", enType);

            break;
    }

    return ulRet;
}

/*****************************************************************************
 函 数 名  : PPPC_EAP_SelectMethod
 功能描述  : 选择方法
 输入参数  : pstEapInfo     EAP实体信息
             enMethod       需要选择的方法
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月09日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPPC_EAP_SelectMethod
(
    PPPC_EAP_INFO_STRU                 *pstEapInfo,
    PPPC_EAP_METHODS_TYPE_ENUM_UINT8    enMethod
)
{
    PPPC_EAP_METHODS_INTERNAL_TYPE_ENUM_UINT8   enInterType;
    VOS_UINT32                                  ulRet;


    /* 内部调用，保证如参合法 */

    /* 映射到内部类型 */
    ulRet   = PPPC_EAP_MappingMethodType(enMethod, &enInterType);
    if (VOS_OK != ulRet)
    {
        return VOS_ERR;
    }

    pstEapInfo->enSelectMethod  = enMethod;

    pstEapInfo->enInterType = enInterType;

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPPC_EAP_MethodProc
 功能描述  : 调用方法的回调函数处理报文
 输入参数  : pstEapInfo     EAP实体
             pData          报文指针
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月09日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
PS_BOOL_ENUM_UINT8 PPPC_EAP_MethodProc
(
    PPPC_EAP_INFO_STRU                 *pstEapInfo,
    VOS_VOID                           *pData
)
{
    PPPC_EAP_HEADER_STRU               *pstPayload;
    PPPC_EAP_HEADER_STRU               *pstRespPkt;
    PPPINFO_S                          *pstPppInfo;
    PPPC_EAP_METHOD_OUTPUT_STRU         stMethodOutput;
    PPPC_EAP_METHOD_INPUT_STRU          stMethodInput;
    VOS_UINT16                          usPktLen;
    PS_BOOL_ENUM_UINT8                  enPreProcResult = PS_FALSE;


    /* 内部调用保证指针非空 */

    pstPppInfo   = pstEapInfo->pstPppInfo;
    if (VOS_NULL_PTR == pstPppInfo)
    {
        PPPC_WARNING_LOG("PPP did not create!");
        return PS_FALSE;
    }

    pstPayload   = (PPPC_EAP_HEADER_STRU *)pData;

    if (pstEapInfo->enInterType >= PPPC_EAP_INTERNAL_TYPE_BUTT)
    {
        PPPC_WARNING_LOG2("Invalid method type",
                pstEapInfo->enInterType, pstEapInfo->enSelectMethod);
        return PS_FALSE;
    }

    /* 调用对应方法处理函数 */
    if (VOS_NULL_PTR != g_stMethodProcCB[pstEapInfo->enInterType].pfuncProcMethodPkt)
    {
        /* 填充Response报文头 */
        pstRespPkt  = (PPPC_EAP_HEADER_STRU *)pstEapInfo->aucRespPkt;
        pstRespPkt->ucEAPCode   = PPPC_EAP_RESPONSE_TYPE;
        pstRespPkt->ucEAPID     = pstPayload->ucEAPID;
        pstRespPkt->enEAPType   = pstPayload->enEAPType;

        usPktLen    = PPPC_EAP_HEADERLEN + PPPC_EAP_TYPE_FIELD_LEN;

        /* EAP报文长度填充 */
        PPPC_EAP_UpdateLen(pstEapInfo->aucRespPkt, &(pstEapInfo->usRespPktLen), usPktLen);

        /* 封装方法出参 */
        stMethodOutput.ulPppId      = pstPppInfo->ulRPIndex;
        stMethodOutput.pucPktData   = pstEapInfo->aucRespPkt;
        stMethodOutput.pusRespLen   = &(pstEapInfo->usRespPktLen);

        /* 填充方法入参 */
        stMethodInput.ucEAPID   = pstPayload->ucEAPID;
        stMethodInput.usEAPLen  = VOS_NTOHS(pstPayload->usEAPLen);
        stMethodInput.enEAPType = pstPayload->enEAPType;
        stMethodInput.pucPktData= (VOS_UINT8 *)pstPayload;

        /* 返回预处理结果决定是否需要切到Auth状态 */
        if (VOS_NULL_PTR != g_stMethodProcCB[pstEapInfo->enInterType].pfuncPreProc)
        {
            enPreProcResult = g_stMethodProcCB[pstEapInfo->enInterType].pfuncPreProc(&stMethodInput);
        }

        g_stMethodProcCB[pstEapInfo->enInterType].pfuncProcMethodPkt(&stMethodOutput, &stMethodInput);
    }

    return enPreProcResult;
}

/*****************************************************************************
 函 数 名  : PPPC_EAP_FillNakResponse
 功能描述  : 填充NAK Response消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月09日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPPC_EAP_FillNakResponse
(
    PPPC_EAP_INFO_STRU                 *pstEapInfo
)
{
    VOS_UINT32                          ulRet;
    PPPC_EAP_HEADER_STRU               *pstRespPayload;
    PPPC_EAP_METHODS_TYPE_ENUM_UINT8    aenMethodList[PPPC_EAP_TYPE_BUTT];
    VOS_UINT16                          usPktLen;
    VOS_UINT8                           ucMethodNum;


    /* 获取本端能支持的方法列表 */
    ulRet = PPPC_EAP_GetSupportMethodList(aenMethodList, &ucMethodNum);
    if (VOS_OK != ulRet)
    {
        PPPC_WARNING_LOG1("Get method list fail!", ulRet);
        return VOS_ERR;
    }

    pstRespPayload  = (PPPC_EAP_HEADER_STRU *)pstEapInfo->aucRespPkt;
    pstRespPayload->ucEAPCode   = PPPC_EAP_RESPONSE_TYPE;
    pstRespPayload->ucEAPID     = pstEapInfo->ucRequestID;
    pstRespPayload->enEAPType   = PPPC_EAP_NAK_TYPE;

    usPktLen    = PPPC_EAP_HEADERLEN
                + PPPC_EAP_TYPE_FIELD_LEN + ucMethodNum;

    /* EAP报文长度填充 */
    PPPC_EAP_UpdateLen(pstEapInfo->aucRespPkt, &(pstEapInfo->usRespPktLen), usPktLen);

    PS_MEM_CPY(pstEapInfo->aucRespPkt + PPPC_EAP_HEADERLEN + PPPC_EAP_TYPE_FIELD_LEN,
            aenMethodList, ucMethodNum);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPPC_EAP_FillExpandNakResponse
 功能描述  : 填充扩展NAK Response消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月09日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPPC_EAP_FillExpandNakResponse
(
    PPPC_EAP_INFO_STRU                 *pstEapInfo
)
{
    VOS_UINT32                          ulRet;
    PPPC_EAP_HEADER_STRU               *pstRespPayload;
    PPPC_EAP_METHODS_TYPE_ENUM_UINT8    aenMethodList[PPPC_EAP_TYPE_BUTT];
    PPPC_EAP_EXPAND_NAK_TYPE_DATA_STRU *pstExpandNakData;
    VOS_UINT8                           ucMethodNum;
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulType;
    VOS_UINT16                          usPktLen;


    /* 获取本端能支持的方法列表 */
    ulRet = PPPC_EAP_GetSupportMethodList(aenMethodList, &ucMethodNum);
    if (VOS_OK != ulRet)
    {
        PPPC_WARNING_LOG1("Get method list fail!", ulRet);
        return VOS_ERR;
    }

    pstRespPayload  = (PPPC_EAP_HEADER_STRU *)pstEapInfo->aucRespPkt;

    pstRespPayload->ucEAPCode   = PPPC_EAP_RESPONSE_TYPE;
    pstRespPayload->ucEAPID     = pstEapInfo->ucRequestID;

    /* 协议参考RFC3748,chapter 5.3 */
    /*0                   1                   2                   3
     0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    |     2         |  Identifier   |           Length=28           |
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    |   Type=254    |                0 (IETF)                       |
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    |                                3 (Nak)                        |
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    |   Type=254    |                0 (IETF)                       |
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    |                                4 (MD5)                        |
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    |   Type=254    |                0 (IETF)                       |
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    |                                23(AKA)                        |
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    |   Type=254    |                0 (IETF)                       |
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    |                                50(AKA')                       |
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    */

    usPktLen    = (VOS_UINT16)(PPPC_EAP_HEADERLEN
                + (PPPC_EAP_EXPAND_NAK_ELEM_LEN * (ucMethodNum + 1)));

    /* EAP报文长度填充 */
    PPPC_EAP_UpdateLen(pstEapInfo->aucRespPkt, &(pstEapInfo->usRespPktLen), usPktLen);

    pstExpandNakData = (PPPC_EAP_EXPAND_NAK_TYPE_DATA_STRU *)(((VOS_UINT8 *)pstRespPayload) + PPPC_EAP_HEADERLEN);
    pstExpandNakData->enEAPType = PPPC_EAP_EXPAND_NAK_TYPE;
    ulType                      = PPPC_EAP_NAK_TYPE;
    pstExpandNakData->ulType    = VOS_HTONL(ulType);
    pstExpandNakData++;

    for (ulLoop = 0; ulLoop < ucMethodNum; ulLoop++)
    {
        pstExpandNakData->enEAPType = PPPC_EAP_EXPAND_NAK_TYPE;
        ulType                      = aenMethodList[ulLoop];
        pstExpandNakData->ulType    = VOS_HTONL(ulType);
        PS_MEM_SET(pstExpandNakData->aucIETF, 0, sizeof(pstExpandNakData->aucIETF));
        pstExpandNakData++;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPPC_EAP_PeerTransferState
 功能描述  : PEER状态状态更新
 输入参数  : pstEapInfo     EAP实体
             enEvent        事件通知
             pData          报文或其他参数
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月09日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_EAP_PeerTransferState
(
    PPPC_EAP_INFO_STRU                 *pstEapInfo,
    PPPC_EVENT_USER_DATA               *pstPppEventData
)
{
    /* 状态迁移 */
    pstEapInfo->enEapPeerState  = (PPPC_EAP_PEER_STATE_MACHINE_ENUM_UINT16)pstPppEventData->ulNewState;

    /* 上报事件 */
    PPPC_MNTN_SndEvent(MSPS_PID_PPPC, DIAG_MODE_COMM, PPPC_LOG_EVENT_STATE_UPDATE,
            pstPppEventData, sizeof(PPPC_EVENT_USER_DATA));

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_EAP_PeerProcessEvent
 功能描述  : PEER状态机事件通知
 输入参数  : pstEapInfo     EAP实体
             enEvent        事件通知
             pData          报文或其他参数
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月09日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_EAP_PeerProcessEvent
(
    VOS_UINT32                          ulPppId,
    PPPC_EAP_PEER_EVENT_ENUM_UINT16     enEvent,
    VOS_VOID                           *pData
)
{
    PPPINFO_S                          *pstPppInfo;
    PPPC_EAP_INFO_STRU                 *pstEapInfo;


    /* 指针在调用处已经判空检查 */

    if (PPP_MAX_USER_NUM < ulPppId)
    {
        PPPC_WARNING_LOG1("Invalid input ppp id", ulPppId);
        return;
    }

    pstPppInfo                  = &g_astPppPool[ulPppId];
    pstEapInfo                  = (PPPC_EAP_INFO_STRU *)pstPppInfo->pstEapInfo;
    if (VOS_NULL_PTR == pstEapInfo)
    {
        PPPC_WARNING_LOG1("EAP did not create", ulPppId);
        return;
    }

    /* 检查入参 */
    if (enEvent >= PPPC_EAP_PEER_EVENT_BUTT)
    {
        PPPC_WARNING_LOG1("Invalid input param!", enEvent);
        return;
    }

    if (pstEapInfo->enEapPeerState >= PPPC_EAP_PEER_STATE_BUTT)
    {
        PPPC_WARNING_LOG2("Invalid state", pstEapInfo->enEapPeerState, enEvent);
        return;
    }

    /* PEER状态机处理函数 */
    if (VOS_NULL_PTR != g_pfunEventProc[pstEapInfo->enEapPeerState][enEvent])
    {
        g_pfunEventProc[pstEapInfo->enEapPeerState][enEvent](pstPppInfo, pData);
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_EAP_PeerIdleIdentityReq
 功能描述  : 在Idle状态下收到Identity Req的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月09日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_EAP_PeerIdleIdentityReq
(
    PPPINFO_S                          *pstPppInfo,
    VOS_VOID                           *pData
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT8                           aucIdentity[PPPC_EAP_ID_MAX_LEN];
    VOS_UINT16                          usIdentityLen;
    PPPC_EAP_METHODS_TYPE_ENUM_UINT8    enMethodType;
    PPPC_EAP_INFO_STRU                 *pstEapInfo;


    /* 内部调用保证入参非空 */

    pstEapInfo = (PPPC_EAP_INFO_STRU *)pstPppInfo->pstEapInfo;
    if (VOS_NULL_PTR == pstEapInfo)
    {
        PPPC_WARNING_LOG("EAP did not create!");
        return;
    }

    /* 获取Idenity的策略，目前只会获取AKA'类型 */
    enMethodType    = PPPC_EAP_PreferIdenType();

    /* 获取Identity */
    ulRet   = PPPC_EAP_GetIdentity(enMethodType, aucIdentity, &usIdentityLen);
    if (VOS_OK != ulRet)
    {
        PPPC_WARNING_LOG1("Get identity fail!", ulRet);
        return;
    }

    if ((usIdentityLen >= PPPC_EAP_ID_MAX_LEN) || (0 == usIdentityLen))
    {
        PPPC_WARNING_LOG1("Get identity len invalid!", usIdentityLen);
        return;
    }

    /* Stay in Init State */

    /* 填充TYPE-DATA域 */
    /*  TYPE  |  TYPE-DATA */
    /* 1Byte  |  type-data len */
    PPPC_EAP_FillPayload(pstEapInfo, aucIdentity, usIdentityLen);

    PPPC_EAP_SendResponse(pstPppInfo->ulRPIndex);

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_EAP_PeerNotifyReq
 功能描述  : 在Init状态下收到Notify Req的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月09日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_EAP_PeerNotifyReq
(
    PPPINFO_S                          *pstPppInfo,
    VOS_VOID                           *pData
)
{
    PPPC_EAP_INFO_STRU                 *pstEapInfo  = VOS_NULL_PTR;


    /* 内部调用保证入参非空 */

    pstEapInfo = (PPPC_EAP_INFO_STRU *)pstPppInfo->pstEapInfo;
    if (VOS_NULL_PTR == pstEapInfo)
    {
        PPPC_WARNING_LOG("EAP did not create!");
        return;
    }

    /* Stay in Init State */

    /* 填写RESPONSE */
    PPPC_EAP_FillPayload(pstEapInfo, VOS_NULL_PTR, 0);

    PPPC_EAP_SendResponse(pstPppInfo->ulRPIndex);

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_EAP_PeerIdleNak
 功能描述  : 在Idle状态下收到NAK事件的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月09日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_EAP_PeerIdleNak
(
    PPPINFO_S                          *pstPppInfo,
    VOS_VOID                           *pData
)
{
    PPPC_EAP_INFO_STRU                 *pstEapInfo  = VOS_NULL_PTR;
    PPPC_EAP_HEADER_STRU               *pstpktPayload;
    VOS_UINT32                          result;


    /* PPP实体判空已经在调用处做过检查 */

    if (VOS_NULL_PTR == pData)
    {
        PPPC_WARNING_LOG("Data is null!");
        return;
    }

    pstEapInfo = (PPPC_EAP_INFO_STRU *)pstPppInfo->pstEapInfo;
    if (VOS_NULL_PTR == pstEapInfo)
    {
        PPPC_WARNING_LOG("EAP did not create!");
        return;
    }

    /* Stay in Init State */

    pstpktPayload   = (PPPC_EAP_HEADER_STRU *)pData;

    if (PPPC_EAP_EXPAND_NAK_TYPE == pstpktPayload->enEAPType)
    {
        result = PPPC_EAP_FillExpandNakResponse(pstEapInfo);
    }
    else
    {
        result = PPPC_EAP_FillNakResponse(pstEapInfo);
    }

    if (VOS_OK == result)
    {
        PPPC_EAP_SendResponse(pstPppInfo->ulRPIndex);
    }
    return;
}

/*****************************************************************************
 函 数 名  : PPPC_EAP_PeerIdleAuthReq
 功能描述  : 在Idle状态下收到鉴权报文的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月09日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_EAP_PeerIdleAuthReq
(
    PPPINFO_S                          *pstPppInfo,
    VOS_VOID                           *pData
)
{
    VOS_UINT32                          ulRet;
    PPPC_EAP_INFO_STRU                 *pstEapInfo;
    PPPC_EAP_HEADER_STRU               *pstPaload;
    PPPC_EVENT_USER_DATA                stPppEventData;
    PS_BOOL_ENUM_UINT8                  enPreProcResult;


    /* PPP实体判空已经在调用处做过检查 */

    if (VOS_NULL_PTR == pData)
    {
        PPPC_WARNING_LOG("Data is null!");
        return;
    }

    pstEapInfo = (PPPC_EAP_INFO_STRU *)pstPppInfo->pstEapInfo;
    if (VOS_NULL_PTR == pstEapInfo)
    {
        PPPC_WARNING_LOG("EAP did not create!");
        return;
    }

    pstPaload   = (PPPC_EAP_HEADER_STRU *)pData;

    /* 获取并选择方法,同时初始化对应方法的处理函数 */
    ulRet       = PPPC_EAP_GetMethod(pstEapInfo);
    if (VOS_OK != ulRet)
    {
        ulRet   = PPPC_EAP_SelectMethod(pstEapInfo, pstPaload->enEAPType);
        if (VOS_OK != ulRet)
        {
            return;
        }

        /* 初始化鉴权结果 */
        pstEapInfo->ulLocalResult   = VOS_ERR;
        pstEapInfo->ulRemoteResult  = VOS_ERR;

        /* 初始化方法 */
        if (VOS_NULL_PTR != g_stMethodProcCB[pstEapInfo->enInterType].pfuncInitMethod)
        {
            g_stMethodProcCB[pstEapInfo->enInterType].pfuncInitMethod(pstEapInfo->enSelectMethod);
        }
    }

    enPreProcResult = PPPC_EAP_MethodProc(pstEapInfo, pData);
    if (PS_TRUE == enPreProcResult)
    {
        /* 迁移到Authenticating状态 */
        PS_MEM_SET(&stPppEventData, 0, sizeof(stPppEventData));
        stPppEventData.ulOldState   = pstEapInfo->enEapPeerState;
        stPppEventData.ulNewState   = PPPC_EAP_PEER_AUTHENTICATING_STATE;
        stPppEventData.ulPppId      = pstPppInfo->ulRPIndex;
        stPppEventData.enEntityId   = PPPC_ENTITY_ID_EAP;
        stPppEventData.ucPdnId      = 0xff;
        PPPC_EAP_PeerTransferState(pstEapInfo, &stPppEventData);
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_EAP_PeerIdleSuccess
 功能描述  : 在Idle状态下收到SUCCESS报文的处理
 输入参数  : pstPppInfo     PPP实体信息
             pData          报文指针
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月09日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_EAP_PeerIdleSuccess
(
    PPPINFO_S                          *pstPppInfo,
    VOS_VOID                           *pData
)
{
    /* 内部调用保证入参非空 */

    /* 此时需要迁移到CLOSED状态，然而协商成功后PEER还需要恢复到INIT状态
        因此状态机不需要迁移，仍旧保留在INIT状态 */

    /* 发送鉴权成功事件 */
    PPP_Core_ReceiveEventFromProtocol(pstPppInfo, (VOS_UINT32)PPP_EVENT_EAPSUCCESS, NULL);

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_EAP_PeerIdleFailure
 功能描述  : 在Init状态下收到FAILURE报文的处理
 输入参数  : pstPppInfo     PPP实体信息
             pData          报文指针
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月09日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_EAP_PeerIdleFailure
(
    PPPINFO_S                          *pstPppInfo,
    VOS_VOID                           *pData
)
{
    /* 内部调用保证入参非空 */

    /* 此时需要迁移到CLOSED状态，然而协商失败后PEER还需要恢复到INIT状态
        因此状态机不需要迁移，仍旧保留在INIT状态 */

    PPPC_EAP_Init(pstPppInfo);

    /* 发送鉴权失败事件 */
    PPP_Core_ReceiveEventFromProtocol(pstPppInfo, (VOS_UINT32)PPP_EVENT_EAPFAILED, NULL);

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_EAP_PeerTimeout
 功能描述  : 鉴权协商超时处理
 输入参数  : ulPppId
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月09日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_EAP_PeerTimeout(PPPINFO_S *pstPppInfo, VOS_VOID *pData)
{
    PPPC_EAP_INFO_STRU                 *pstEapInfo;
    CTTF_PPPC_AUTH_INFO_STRU            stPppAuthInfo;

    /* 内部调用保证入参非空 */

    pstEapInfo  = (PPPC_EAP_INFO_STRU *)pstPppInfo->pstEapInfo;
    if (VOS_NULL_PTR == pstEapInfo)
    {
        PPPC_WARNING_LOG("Did not create EAP!");
    }

    PPPC_GetPppAuthInfo(&stPppAuthInfo);
    PPPC_MntnTraceAuthResult((VOS_UINT8)pstPppInfo->ulRPIndex,
                    PPP_EAP, VOS_ERR, &stPppAuthInfo);

    PPPC_EAP_Init(pstPppInfo);

    /* 发送鉴权失败事件 */
    PPP_Core_ReceiveEventFromProtocol(pstPppInfo, (VOS_UINT32)PPP_EVENT_EAPFAILED, VOS_NULL_PTR);

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_EAP_PeerAuthAuthReq
 功能描述  : 在AUTH状态下收到鉴权方法的报文
 输入参数  : pstPppInfo     PPP实体
             pData          报文指针
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月09日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_EAP_PeerAuthAuthReq
(
    PPPINFO_S                          *pstPppInfo,
    VOS_VOID                           *pData
)
{
    PPPC_EAP_INFO_STRU                 *pstEapInfo  = VOS_NULL_PTR;
    PPPC_EAP_HEADER_STRU               *pstPaload;


    /* PPP实体判空已经在调用处做过检查 */

    if (VOS_NULL_PTR == pData)
    {
        PPPC_WARNING_LOG("Data is null!");
        return;
    }

    pstEapInfo = (PPPC_EAP_INFO_STRU *)pstPppInfo->pstEapInfo;
    if (VOS_NULL_PTR == pstEapInfo)
    {
        PPPC_WARNING_LOG("EAP did not create!");
        return;
    }

    pstPaload   = (PPPC_EAP_HEADER_STRU *)pData;

    if (pstEapInfo->enSelectMethod != pstPaload->enEAPType)
    {
        PPPC_WARNING_LOG2("Method mismach!",
                pstEapInfo->enSelectMethod, pstPaload->enEAPType);
        return;
    }

    /* 仍停留在AUTH状态 */

    (VOS_VOID)PPPC_EAP_MethodProc(pstEapInfo, pData);

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_EAP_PeerAuthNotifyAuthInd
 功能描述  : 在AUTH/NOTIFY状态下收到方法的成功或失败指示
 输入参数  : pstPppInfo     PPP实体
             pData          本端鉴权成功或失败指示
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月09日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_EAP_PeerAuthNotifyAuthInd
(
    PPPINFO_S                          *pstPppInfo,
    VOS_VOID                           *pData
)
{
    PPPC_EAP_INFO_STRU                 *pstEapInfo;
    PPPC_EVENT_USER_DATA                stPppEventData;


    if (VOS_NULL_PTR == pData)
    {
        PPPC_WARNING_LOG("Input data is null!");
        return;
    }

    /* PPP实体已经在调用处判空 */
    pstEapInfo = (PPPC_EAP_INFO_STRU *)pstPppInfo->pstEapInfo;
    if (VOS_NULL_PTR == pstEapInfo)
    {
        PPPC_WARNING_LOG("EAP did not create!");
        return;
    }

    pstEapInfo->ulLocalResult   = *(VOS_UINT32 *)pData;

    /* 迁移到CLOSING状态 */
    PS_MEM_SET(&stPppEventData, 0, sizeof(stPppEventData));
    stPppEventData.ulOldState   = pstEapInfo->enEapPeerState;
    stPppEventData.ulNewState   = PPPC_EAP_PEER_CLOSING_STATE;
    stPppEventData.ulPppId      = pstPppInfo->ulRPIndex;
    stPppEventData.enEntityId   = PPPC_ENTITY_ID_EAP;
    stPppEventData.ucPdnId      = 0xff;
    PPPC_EAP_PeerTransferState(pstEapInfo, &stPppEventData);

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_EAP_PeerAuthNotifySuccess
 功能描述  : 在AUTH/NONTIFY状态下收到网络的鉴权成功消息
 输入参数  : pstPppInfo     PPP实体
             pData          本端鉴权成功或失败指示
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月09日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_EAP_PeerAuthNotifySuccess
(
    PPPINFO_S                          *pstPppInfo,
    VOS_VOID                           *pData
)
{
    PPPC_EAP_INFO_STRU                 *pstEapInfo  = VOS_NULL_PTR;
    PPPC_EVENT_USER_DATA                stPppEventData;


    /* 内部调用保证入参非空 */

    pstEapInfo = (PPPC_EAP_INFO_STRU *)pstPppInfo->pstEapInfo;
    if (VOS_NULL_PTR == pstEapInfo)
    {
        PPPC_WARNING_LOG("EAP did not create!");
        return;
    }

    /* 迁移到CLOSING状态 */
    PS_MEM_SET(&stPppEventData, 0, sizeof(stPppEventData));
    stPppEventData.ulOldState   = pstEapInfo->enEapPeerState;
    stPppEventData.ulNewState   = PPPC_EAP_PEER_CLOSING_STATE;
    stPppEventData.ulPppId      = pstPppInfo->ulRPIndex;
    stPppEventData.enEntityId   = PPPC_ENTITY_ID_EAP;
    stPppEventData.ucPdnId      = 0xff;
    PPPC_EAP_PeerTransferState(pstEapInfo, &stPppEventData);

    /* 存储网络的鉴权结果 */
    pstEapInfo->ulRemoteResult  = VOS_OK;

    if (VOS_NULL_PTR != g_stMethodProcCB[pstEapInfo->enInterType].pfuncNotifyMethodRes)
    {
        g_stMethodProcCB[pstEapInfo->enInterType].pfuncNotifyMethodRes(VOS_OK);
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_EAP_PeerAuthNotifyFailure
 功能描述  : 在AUTH/NOTIFY状态下收到网络的失败消息
 输入参数  : pstPppInfo     PPP实体
             pData          本端鉴权成功或失败指示
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月09日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_EAP_PeerAuthNotifyFailure
(
    PPPINFO_S                          *pstPppInfo,
    VOS_VOID                           *pData
)
{
    PPPC_EAP_INFO_STRU                 *pstEapInfo  = VOS_NULL_PTR;
    PPPC_EVENT_USER_DATA                stPppEventData;
    CTTF_PPPC_AUTH_INFO_STRU            stPppAuthInfo;


    /* 内部调用保证入参非空 */

    pstEapInfo = (PPPC_EAP_INFO_STRU *)pstPppInfo->pstEapInfo;
    if (VOS_NULL_PTR == pstEapInfo)
    {
        PPPC_WARNING_LOG("EAP did not create!");
        return;
    }

    /* 存储网络的鉴权结果 */
    pstEapInfo->ulRemoteResult  = VOS_ERR;

    /* 迁移到CLOSED状态 */
    PS_MEM_SET(&stPppEventData, 0, sizeof(stPppEventData));
    stPppEventData.ulOldState   = PPPC_EAP_PEER_CLOSING_STATE;
    stPppEventData.ulNewState   = PPPC_EAP_PEER_CLOSED_STATE;
    stPppEventData.ulPppId      = pstPppInfo->ulRPIndex;
    stPppEventData.enEntityId   = PPPC_ENTITY_ID_EAP;
    stPppEventData.ucPdnId      = 0xff;
    PPPC_EAP_PeerTransferState(pstEapInfo, &stPppEventData);

    PPPC_GetPppAuthInfo(&stPppAuthInfo);
    PPPC_MntnTraceAuthResult((VOS_UINT8)pstPppInfo->ulRPIndex,
                PPP_EAP, VOS_ERR, &stPppAuthInfo);

    if (VOS_NULL_PTR != g_stMethodProcCB[pstEapInfo->enInterType].pfuncNotifyMethodRes)
    {
        g_stMethodProcCB[pstEapInfo->enInterType].pfuncNotifyMethodRes(VOS_ERR);
    }

    PPPC_EAP_Init(pstPppInfo);

    /* 发送鉴权失败事件 */
    PPP_Core_ReceiveEventFromProtocol(pstPppInfo, (VOS_UINT32)PPP_EVENT_EAPFAILED, VOS_NULL_PTR);

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_EAP_PeerNotifyAuthReq
 功能描述  : 在NOTIFY状态下收到网络的鉴权消息
 输入参数  : pstPppInfo     PPP实体
             pData          报文指针
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月09日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_EAP_PeerNotifyAuthReq
(
    PPPINFO_S                          *pstPppInfo,
    VOS_VOID                           *pData
)
{
    PPPC_EAP_INFO_STRU                 *pstEapInfo  = VOS_NULL_PTR;
    PPPC_EAP_HEADER_STRU               *pstPaload;
    PPPC_EVENT_USER_DATA                stPppEventData;
    PS_BOOL_ENUM_UINT8                  enPreProcResult;


    /* PPP实体判空已经在调用处做过检查 */

    if (VOS_NULL_PTR == pData)
    {
        PPPC_WARNING_LOG("Data is null!");
        return;
    }

    pstEapInfo = (PPPC_EAP_INFO_STRU *)pstPppInfo->pstEapInfo;
    if (VOS_NULL_PTR == pstEapInfo)
    {
        PPPC_WARNING_LOG("EAP did not create!");
        return;
    }

    pstPaload   = (PPPC_EAP_HEADER_STRU *)pData;

    if (pstEapInfo->enSelectMethod != pstPaload->enEAPType)
    {
        PPPC_WARNING_LOG2("Method mismach!",
                pstEapInfo->enSelectMethod, pstPaload->enEAPType);
        return;
    }

    enPreProcResult = PPPC_EAP_MethodProc(pstEapInfo, pData);
    if (PS_TRUE == enPreProcResult)
    {
        /* 迁移到AUTH状态 */
        PS_MEM_SET(&stPppEventData, 0, sizeof(stPppEventData));
        stPppEventData.ulOldState   = PPPC_EAP_PEER_NOTIFYING_STATE;
        stPppEventData.ulNewState   = PPPC_EAP_PEER_AUTHENTICATING_STATE;
        stPppEventData.ulPppId      = pstPppInfo->ulRPIndex;
        stPppEventData.enEntityId   = PPPC_ENTITY_ID_EAP;
        stPppEventData.ucPdnId      = 0xff;
        PPPC_EAP_PeerTransferState(pstEapInfo, &stPppEventData);
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_EAP_PeerClosingNotifyReq
 功能描述  : 在CLOSING状态下收到NOTIFY消息
 输入参数  : pstPppInfo     PPP实体
             pData          报文指针
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月09日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_EAP_PeerClosingNotifyReq
(
    PPPINFO_S                          *pstPppInfo,
    VOS_VOID                           *pData
)
{
    PPPC_EAP_INFO_STRU                 *pstEapInfo  = VOS_NULL_PTR;
    PPPC_EVENT_USER_DATA                stPppEventData;


    /* 内部调用保证入参非空 */

    pstEapInfo = (PPPC_EAP_INFO_STRU *)pstPppInfo->pstEapInfo;
    if (VOS_NULL_PTR == pstEapInfo)
    {
        PPPC_WARNING_LOG("EAP did not create!");
        return;
    }

    /* 迁移到NOTIFYING状态 */
    PS_MEM_SET(&stPppEventData, 0, sizeof(stPppEventData));
    stPppEventData.ulOldState   = PPPC_EAP_PEER_CLOSING_STATE;
    stPppEventData.ulNewState   = PPPC_EAP_PEER_NOTIFYING_STATE;
    stPppEventData.ulPppId      = pstPppInfo->ulRPIndex;
    stPppEventData.enEntityId   = PPPC_ENTITY_ID_EAP;
    stPppEventData.ucPdnId      = 0xff;
    PPPC_EAP_PeerTransferState(pstEapInfo, &stPppEventData);

    /* 填充TYPE-DATA域 */
    /* 填上一个字节的TYPE域 */
    pstEapInfo->enRequestType   = PPPC_EAP_NOTIFY_TYPE;
    PPPC_EAP_FillPayload(pstEapInfo, VOS_NULL_PTR, 0);

    PPPC_EAP_SendResponse(pstPppInfo->ulRPIndex);

    /* 迁移到CLOSING状态 */
    pstEapInfo->enEapPeerState  = PPPC_EAP_PEER_CLOSING_STATE;

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_EAP_PeerClosingAuthReq
 功能描述  : 在CLOSING状态下收到AUTH消息
 输入参数  : pstPppInfo     PPP实体
             pData          报文指针
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月09日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_EAP_PeerClosingAuthReq
(
    PPPINFO_S                          *pstPppInfo,
    VOS_VOID                           *pData
)
{
    PPPC_EAP_INFO_STRU                 *pstEapInfo  = VOS_NULL_PTR;
    PPPC_EAP_HEADER_STRU               *pstPaload;
    PPPC_EVENT_USER_DATA                stPppEventData;
    PS_BOOL_ENUM_UINT8                  enPreProcResult;


    /* PPP实体判空已经在调用处做过检查 */

    if (VOS_NULL_PTR == pData)
    {
        PPPC_WARNING_LOG("Data is null!");
        return;
    }

    pstEapInfo = (PPPC_EAP_INFO_STRU *)pstPppInfo->pstEapInfo;
    if (VOS_NULL_PTR == pstEapInfo)
    {
        PPPC_WARNING_LOG("EAP did not create!");
        return;
    }

    pstPaload   = (PPPC_EAP_HEADER_STRU *)pData;

    if (pstEapInfo->enSelectMethod != pstPaload->enEAPType)
    {
        PPPC_WARNING_LOG2("Method mismach!",
                pstEapInfo->enSelectMethod, pstPaload->enEAPType);
        return;
    }


    enPreProcResult = PPPC_EAP_MethodProc(pstEapInfo, pData);
    if (PS_TRUE == enPreProcResult)
    {
        /* 迁移到AUTH状态 */
        PS_MEM_SET(&stPppEventData, 0, sizeof(stPppEventData));
        stPppEventData.ulOldState   = PPPC_EAP_PEER_CLOSING_STATE;
        stPppEventData.ulNewState   = PPPC_EAP_PEER_AUTHENTICATING_STATE;
        stPppEventData.ulPppId      = pstPppInfo->ulRPIndex;
        stPppEventData.enEntityId   = PPPC_ENTITY_ID_EAP;
        stPppEventData.ucPdnId      = 0xff;
        PPPC_EAP_PeerTransferState(pstEapInfo, &stPppEventData);
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_EAP_PeerClosingAuthInd
 功能描述  : 在CLOSING状态下收到本端鉴权结果
 输入参数  : pstPppInfo     PPP实体
             pData          本端鉴权结果
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月09日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_EAP_PeerClosingAuthInd
(
    PPPINFO_S                          *pstPppInfo,
    VOS_VOID                           *pData
)
{
    PPPC_EAP_INFO_STRU                 *pstEapInfo;
    PPPC_EVENT_USER_DATA                stPppEventData;
    CTTF_PPPC_AUTH_INFO_STRU            stPppAuthInfo;


    if (VOS_NULL_PTR == pData)
    {
        PPPC_WARNING_LOG("Input data is null!");
        return;
    }

    /* PPP实体已经在调用处判空 */
    pstEapInfo = (PPPC_EAP_INFO_STRU *)pstPppInfo->pstEapInfo;
    if (VOS_NULL_PTR == pstEapInfo)
    {
        PPPC_WARNING_LOG("EAP did not create!");
        return;
    }

    pstEapInfo->ulLocalResult   = *(VOS_UINT32 *)pData;

    /* 迁移到CLOSED状态 */
    PS_MEM_SET(&stPppEventData, 0, sizeof(stPppEventData));
    stPppEventData.ulOldState   = PPPC_EAP_PEER_CLOSING_STATE;
    stPppEventData.ulNewState   = PPPC_EAP_PEER_CLOSED_STATE;
    stPppEventData.ulPppId      = pstPppInfo->ulRPIndex;
    stPppEventData.enEntityId   = PPPC_ENTITY_ID_EAP;
    stPppEventData.ucPdnId      = 0xff;
    PPPC_EAP_PeerTransferState(pstEapInfo, &stPppEventData);

    if ((VOS_OK == pstEapInfo->ulLocalResult) && (VOS_OK == pstEapInfo->ulRemoteResult))
    {
        PPPC_GetPppAuthInfo(&stPppAuthInfo);
        PPPC_MntnTraceAuthResult((VOS_UINT8)pstPppInfo->ulRPIndex,
                        PPP_EAP, VOS_OK, &stPppAuthInfo);

        /* 删除定时器 */
        PPPC_EAP_DeleteTimer(pstEapInfo);

        /* 鉴权成功初始化PEER和方法的状态 */
        PPPC_EAP_InitState(pstEapInfo);

        /* 发送鉴权成功事件 */
        PPP_Core_ReceiveEventFromProtocol(pstPppInfo, (VOS_UINT32)PPP_EVENT_EAPSUCCESS, VOS_NULL_PTR);
    }
    else
    {
        PPPC_GetPppAuthInfo(&stPppAuthInfo);
        PPPC_MntnTraceAuthResult((VOS_UINT8)pstPppInfo->ulRPIndex,
                    PPP_EAP, VOS_ERR, &stPppAuthInfo);

        /* 鉴权失败完全清除 */
        PPPC_EAP_Init(pstPppInfo);

        /* 发送鉴权失败事件 */
        PPP_Core_ReceiveEventFromProtocol(pstPppInfo, (VOS_UINT32)PPP_EVENT_EAPFAILED, VOS_NULL_PTR);
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_EAP_PeerClosingSuccess
 功能描述  : 在CLOSING状态下收到网络的成功报文
 输入参数  : pstPppInfo     PPP实体
             pData          报文指针
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月09日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_EAP_PeerClosingSuccess
(
    PPPINFO_S                          *pstPppInfo,
    VOS_VOID                           *pData
)
{
    PPPC_EAP_INFO_STRU                 *pstEapInfo;
    PPPC_EVENT_USER_DATA                stPppEventData;
    CTTF_PPPC_AUTH_INFO_STRU            stPppAuthInfo;


    /* 内部调用保证入参非空 */

    pstEapInfo = (PPPC_EAP_INFO_STRU *)pstPppInfo->pstEapInfo;
    if (VOS_NULL_PTR == pstEapInfo)
    {
        PPPC_WARNING_LOG("EAP did not create!");
        return;
    }

    /* 迁移到CLOSED状态,并上报可维可测 */
    PS_MEM_SET(&stPppEventData, 0, sizeof(stPppEventData));
    stPppEventData.ulOldState   = PPPC_EAP_PEER_CLOSING_STATE;
    stPppEventData.ulNewState   = PPPC_EAP_PEER_CLOSED_STATE;
    stPppEventData.ulPppId      = pstPppInfo->ulRPIndex;
    stPppEventData.enEntityId   = PPPC_ENTITY_ID_EAP;
    stPppEventData.ucPdnId      = 0xff;
    PPPC_EAP_PeerTransferState(pstEapInfo, &stPppEventData);

    if (VOS_NULL_PTR != g_stMethodProcCB[pstEapInfo->enInterType].pfuncNotifyMethodRes)
    {
        g_stMethodProcCB[pstEapInfo->enInterType].pfuncNotifyMethodRes(VOS_OK);
    }

    pstEapInfo->ulRemoteResult  = VOS_OK;
    if ((VOS_OK == pstEapInfo->ulLocalResult) && (VOS_OK == pstEapInfo->ulRemoteResult))
    {
        PPPC_GetPppAuthInfo(&stPppAuthInfo);
        PPPC_MntnTraceAuthResult((VOS_UINT8)pstPppInfo->ulRPIndex,
                PPP_EAP, VOS_OK, &stPppAuthInfo);

        /* 删除定时器 */
        PPPC_EAP_DeleteTimer(pstEapInfo);

        /* 鉴权成功初始化PEER和方法的状态 */
        PPPC_EAP_InitState(pstEapInfo);

        /* 发送鉴权成功事件 */
        PPP_Core_ReceiveEventFromProtocol(pstPppInfo, (VOS_UINT32)PPP_EVENT_EAPSUCCESS, VOS_NULL_PTR);
    }
    else
    {
        PPPC_GetPppAuthInfo(&stPppAuthInfo);
        PPPC_MntnTraceAuthResult((VOS_UINT8)pstPppInfo->ulRPIndex,
                    PPP_EAP, VOS_ERR, &stPppAuthInfo);

        /* 鉴权失败完全清除 */
        PPPC_EAP_Init(pstPppInfo);

        /* 发送鉴权失败事件 */
        PPP_Core_ReceiveEventFromProtocol(pstPppInfo, (VOS_UINT32)PPP_EVENT_EAPFAILED, VOS_NULL_PTR);
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_EAP_PeerClosingFailure
 功能描述  : 在CLOSING状态下收到网络的失败报文
 输入参数  : pstPppInfo     PPP实体
             pData          报文指针
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月09日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_EAP_PeerClosingFailure
(
    PPPINFO_S                          *pstPppInfo,
    VOS_VOID                           *pData
)
{
    PPPC_EAP_INFO_STRU                 *pstEapInfo  = VOS_NULL_PTR;
    PPPC_EVENT_USER_DATA                stPppEventData;
    CTTF_PPPC_AUTH_INFO_STRU            stPppAuthInfo;


    /* 内部调用保证入参非空 */

    pstEapInfo = (PPPC_EAP_INFO_STRU *)pstPppInfo->pstEapInfo;
    if (VOS_NULL_PTR == pstEapInfo)
    {
        PPPC_WARNING_LOG("EAP did not create!");
        return;
    }

    pstEapInfo->ulRemoteResult  = VOS_ERR;

    /* 迁移到CLOSED状态 */
    PS_MEM_SET(&stPppEventData, 0, sizeof(stPppEventData));
    stPppEventData.ulOldState   = PPPC_EAP_PEER_CLOSING_STATE;
    stPppEventData.ulNewState   = PPPC_EAP_PEER_CLOSED_STATE;
    stPppEventData.ulPppId      = pstPppInfo->ulRPIndex;
    stPppEventData.enEntityId   = PPPC_ENTITY_ID_EAP;
    stPppEventData.ucPdnId      = 0xff;
    PPPC_EAP_PeerTransferState(pstEapInfo, &stPppEventData);

    PPPC_GetPppAuthInfo(&stPppAuthInfo);
    PPPC_MntnTraceAuthResult((VOS_UINT8)pstPppInfo->ulRPIndex,
                PPP_EAP, VOS_ERR, &stPppAuthInfo);

    if (VOS_NULL_PTR != g_stMethodProcCB[pstEapInfo->enInterType].pfuncNotifyMethodRes)
    {
        g_stMethodProcCB[pstEapInfo->enInterType].pfuncNotifyMethodRes(VOS_ERR);
    }

    PPPC_EAP_Init(pstPppInfo);

    /* 发送鉴权失败事件 */
    PPP_Core_ReceiveEventFromProtocol(pstPppInfo, (VOS_UINT32)PPP_EVENT_EAPFAILED, VOS_NULL_PTR);

    return;
}

#endif

/*lint -restore */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
