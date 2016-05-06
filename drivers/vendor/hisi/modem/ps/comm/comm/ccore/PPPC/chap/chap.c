/************************************************************************
*                                                                      *
*                             chap.c                                   *
*                                                                      *
*  Project Code:       VRP3.0                                          *
*  Create Date:        2000/06/05                                      *
*  Author:             Zhu Fengzhi                                     *
*  Modify Date:                                                        *
*  Document:                                                           *
*  Function:           PPP的CHAP协议模块                               *
*  Others:                                                             *
*----------------------------------------------------------------------*
*                                                                      *
* Copyright 2000-2002 VRP3.0 Team Beijing Institute HuaWei Tech, Inc.  *
*                     ALL RIGHTS RESERVED                              *
*                                                                      *
*----------------------------------------------------------------------*
*                                                                      *
*   这个文件定义了CHAP协议模块的全部接口函数和内部处理函数             *
*                                                                      *
************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "ppp_inc.h"
#include "pppc_ctrl.h"
#include "ppp_func.h"
#include "pppc_uim.h"
#include "pppc_md5.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
#define         THIS_FILE_ID            PS_FILE_ID_PPPC_CHAP_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
PS_BOOL_ENUM_UINT8  g_enGetChapRespSelf = PS_TRUE;

/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*lint -save -e958 */
/****************************************************************************
* CREATE DATE  ：2000/06/12                                                 *
* CREATED BY   ：Zhu Feng Zhi                                               *
* FUNCTION     ：CHAP初始化CHAP控制块                                        *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstPppInfo:PPP控制块指针                                   *
* OUTPUT       ：                                                           *
* RETURN       ：                                                            *
* CALLED BY    ：PPP_Core_AuthenticatePhase                                    *
****************************************************************************/
VOID PPP_CHAP_Init(PPPINFO_S *pstPppInfo)
{
    PPPCHAPINFO_S *pstChapInfo;
    PPPCONFIGINFO_S *pstConfig;


    /* 初始化为自己算Resposne */
    g_enGetChapRespSelf = PS_TRUE;

    if (pstPppInfo == 0)
    {
        return;
    }

    pstChapInfo = pstPppInfo->pstChapInfo;
    pstConfig = pstPppInfo->pstUsedConfigInfo;
    if ((pstChapInfo == 0) || (pstConfig == 0))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_35);
        return;
    }

    PPP_MemSet((VOID*)pstChapInfo, 0, sizeof(PPPCHAPINFO_S));

    pstChapInfo->pstPppInfo = pstPppInfo;
    pstChapInfo->ucUsed = 1;
    pstChapInfo->ucClientState = CHAP_STATE_CLIENT_INITIAL;
    pstChapInfo->ucServerState = CHAP_STATE_SERVER_INITIAL;
    pstChapInfo->ucChalId = 0;
    pstChapInfo->ucRespId = 0;
    pstChapInfo->ulChalTransmits = 0;
    pstChapInfo->ulRespTransmits = 0;
    pstChapInfo->ulChalTimeoutID = 0;
    pstChapInfo->ulRespTimeoutID = 0;
    pstChapInfo->usAuthServerFailureTimes = 0;
    pstChapInfo->usAuthClientFailureTimes = 0;

    pstChapInfo->ulTimeOutTime  = pstConfig->ulNegTimeOut;
    pstChapInfo->ulMaxTransmits = PPP_DEFMAXCONFREQS;

    /*设置周期验证间隔, 暂不启动此功能*/
    pstChapInfo->ulChalInterval = 0;

    /*设置hash算法*/
    pstChapInfo->ucRespType = CHAP_DIGEST_MD5;
    pstChapInfo->ucChalType = CHAP_DIGEST_MD5;

    pstChapInfo->ulWaitAuthRspTimeout = CHAP_WAITAAARSPTIMEOUT;
    pstChapInfo->ulAuthMaxTransmits = CHAP_MAXAUTHTRANSMITS;
    pstChapInfo->ucAuthTransmits  = 0;
    pstChapInfo->pstAAAAuthReqMsg = NULL;
    pstChapInfo->ulWaitLnsAuthTimeOut = CHAP_WAITLNSAUTHTIME;

    /*输出事件调试信息*/
    CHAP_Debug_Event(pstPppInfo, CHAP_INITIALIZATION);

    return;
}

/****************************************************************************
* CREATE DATE  ：2000/06/12                                                 *
* CREATED BY   ：Zhu Feng Zhi                                               *
* FUNCTION     ：CHAP接收外部事件.事件包括：ClientUp、ServerUp、Down            *                                           Open、Close            *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstPppInfo:PPP控制块指针                                   *
*                ulCmd:命令字, 可以为如下值:                                *
*                    CHAP_EVENT_CLIENTLOWERUP:本地下层UP                        *
*                    CHAP_EVENT_SERVERLOWERUP:对端下层UP                        *
*                    CHAP_EVENT_LOWERDOWN:下层DOWN                            *
*                pPara:事件的参数, 为NULL                                   *
* OUTPUT       ：                                                           *
* RETURN       ：NULL                                                       *
* CALLED BY    ：PPP_Core_ReceiveEventFromShell                                *
****************************************************************************/
VOID PPP_CHAP_ReceiveEventFromCore (PPPINFO_S *pstPppInfo, VOS_UINT32 ulCmd, CHAR *pPara)
{
    if (pstPppInfo == 0)
    {
        return;
    }

    switch (ulCmd)
    {
        case CHAP_EVENT_CLIENTLOWERUP:
            PPP_CHAP_ClientLowerUp(pstPppInfo);
            break;

        case CHAP_EVENT_SERVERLOWERUP:
            PPP_CHAP_ServerLowerUp(pstPppInfo);
            break;

        case CHAP_EVENT_LOWERDOWN:
            PPP_CHAP_LowerDown(pstPppInfo);
            break;

        default:
            PPP_DBG_ERR_CNT(PPP_PHERR_36);

            /*输出错误调试信息*/
            CHAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, "CHAP Receive UNKNOWN Event!");
            break;
    }

    return;
}

/****************************************************************************
* CREATE DATE  ：2000/06/12                                                 *
* CREATED BY   ：Zhu Feng Zhi                                               *
* FUNCTION     ：CHAP Client 端LowerUp,由对端验证我端                        *
*                 进入CHAP_STATE_LISTEN_CHALLENGE状态, 等待对端送出CHALLENGE    *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstPppInfo:PPP控制块指针                                   *
* OUTPUT       ：                                                           *
* RETURN       ：                                                            *
* CALLED BY    ：PPP_CHAP_ReceiveEventFromCore                                *
****************************************************************************/
VOID PPP_CHAP_ClientLowerUp(PPPINFO_S *pstPppInfo)
{
    PPPCHAPINFO_S * pstChapInfo = pstPppInfo->pstChapInfo;
    PPPCONFIGINFO_S *pstConfig = pstPppInfo->pstUsedConfigInfo;
    VOS_UINT32                          ulRet;


    if ((pstChapInfo == NULL) || (pstConfig == NULL))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_37);
        return;
    }

    ulRet = PPP_GetConfigUserName(pstChapInfo->szHostName, pstPppInfo->ulRPIndex);
    if (VOS_OK != ulRet)
    {
        PPPC_WARNING_LOG("Get username fail when chap client up.");
    }

    pstChapInfo->ulTimeOutTime = pstConfig->ulNegTimeOut;
    pstChapInfo->ulRespTransmits = 0;
    pstChapInfo->ucRespId = 0;
    pstChapInfo->ulRespTimeoutID = 0;
    pstChapInfo->usAuthClientFailureTimes = 0;

    /* 输出事件调试信息 */
    CHAP_Debug_Event(pstPppInfo, CHAP_CLIENTLOWERUP);

    /* 输出状态转换调试信息 */
    CHAP_Debug_StateChange(pstPppInfo, CHAP_STATE_LISTEN_CHALLENGE, CHAP_CLIENT_STATE);
    pstChapInfo->ucClientState = CHAP_STATE_LISTEN_CHALLENGE;

    return;
}

/****************************************************************************
* CREATE DATE  ：2000/06/09                                                 *
* CREATED BY   ：Zhu Feng Zhi                                               *
* FUNCTION     ：CHAP Server 端LowerUp,由我端向对端发送Challenge             *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstPppInfo:PPP控制块指针                                   *
* OUTPUT       ：                                                           *
* RETURN       ：                                                            *
* CALLED BY    ：PPP_CHAP_ReceiveEventFromCore                                *
****************************************************************************/
VOID PPP_CHAP_ServerLowerUp(PPPINFO_S *pstPppInfo)
{
    PPPCHAPINFO_S * pstChapInfo = pstPppInfo->pstChapInfo;
    PPPCONFIGINFO_S *pstConfig = pstPppInfo->pstUsedConfigInfo;

    if ((pstChapInfo == NULL) || (pstConfig == NULL))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_38);
        return;
    }

    (VOID)VOS_StrCpy((VOS_CHAR *)pstChapInfo->szHostName, (VOS_CHAR *)pstConfig->cChapHostName);
    pstChapInfo->ulChalTransmits = 0;
    pstChapInfo->ulTimeOutTime = pstConfig->ulNegTimeOut;
    pstChapInfo->ucChalId = 0;
    pstChapInfo->ulChalTransmits = 0;
    pstChapInfo->ulChalTimeoutID = 0;
    pstChapInfo->usAuthServerFailureTimes = 0;

    /* 输出事件调试信息 */
    CHAP_Debug_Event(pstPppInfo, CHAP_SERVERLOWERUP);

    PPP_CHAP_GenChallenge(pstChapInfo);        /* 产生challenge */
    PPP_CHAP_SendChallenge(pstPppInfo);        /* 送出challenge */

    PPP_PerfInc(&g_stPppPerfStatistic.ulChapTotal, PERF_TYPE_PPPC_CHAP_AUTHEN_NUM, pstPppInfo->bEhrpdUser);

    return;
}

/****************************************************************************
* CREATE DATE  ：2000/06/12                                                 *
* CREATED BY   ：Zhu Feng Zhi                                               *
* FUNCTION     ：CHAPLowerDown                                                *
*                 进入CHAP_STATE_SERVER_INITIAL ,CHAP_STATE_CLIENT_INITIAL状态        *
*                 同时删除定时器                                                *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstPppInfo:PPP控制块指针                                   *
* OUTPUT       ：                                                           *
* RETURN       ：                                                            *
* CALLED BY    ：PPP_CHAP_ReceiveEventFromCore                                *
****************************************************************************/
VOID PPP_CHAP_LowerDown(PPPINFO_S *pstPppInfo)
{
    PPPCHAPINFO_S *pstChapInfo = pstPppInfo->pstChapInfo;

    if (pstChapInfo == NULL)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_40);
        return;
    }

    /* 输出事件调试信息 */
    CHAP_Debug_Event(pstPppInfo, CHAP_LOWERDOWN);

    /* 删除定时器 */
    PPP_CHAP_DeleteTimer(pstPppInfo);

    /* 输出调试信息 */
    CHAP_Debug_StateChange(pstPppInfo, CHAP_STATE_CLIENT_INITIAL, CHAP_CLIENT_STATE);
    CHAP_Debug_StateChange(pstPppInfo, CHAP_STATE_SERVER_INITIAL, CHAP_SERVER_STATE);

    /* 改变状态 */
    pstChapInfo->ucClientState = CHAP_STATE_CLIENT_INITIAL;
    pstChapInfo->ucServerState = CHAP_STATE_SERVER_INITIAL;

    return;
}

/****************************************************************************
* CREATE DATE  ：2000/06/12                                                 *
* CREATED BY   ：Zhu Feng Zhi                                               *
* FUNCTION     ：CHAP收到chap 数据包, 分析报文头并作相应处理                *
*                pHead:存放报文内存的头指针包括协议号, 应负责释放这段内存   *
*                pPacket:报文头位置                                         *
*                ulLen:报文长度                                             *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstPppInfo:PPP控制块指针                                   *
* OUTPUT       ：                                                           *
* RETURN       ：                                                            *
* CALLED BY    ：PPP_Core_ReceivePacketFromShell                            *
****************************************************************************/
VOID PPP_CHAP_ReceivePacket (PPPINFO_S *pstPppInfo, UCHAR* pHead, UCHAR* pPacket, VOS_UINT32 ulLen)
{
    PPPCHAPINFO_S *pstChapInfo;
    UCHAR ucCode, ucId;
    VOS_UINT32 ulCiLen;

    PPPC_INFO_LOG("\r\n-------enter PPP_CHAP_ReceivePacket--------");
    if (pstPppInfo == 0)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_41);
        PPPC_INFO_LOG("pstPppInfo == 0");
        return;
    }

    pstChapInfo = pstPppInfo->pstChapInfo;
    if (pstChapInfo == 0)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_42);
        CHAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, "pstChapInfo == 0");
        return;
    }

    /*输出事件调试信息*/
    CHAP_Debug_Packet(pstPppInfo, pPacket, ulLen, PPP_CHAP, 1);

    /*分析报文头(ucCode,ucId, length)*/

    if (ulLen < FSM_HDRLEN)        /* 如果报文包太短则丢弃 */
    {
        /*输出错误调试信息*/
        CHAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, "Too short packet!");
        PPP_DBG_ERR_CNT(PPP_PHERR_43);
        return;
    }

    /* 获得报文中字段值, 并移动报文指针 */
    PPP_GETCHAR(ucCode, pPacket);
    PPP_GETCHAR(ucId, pPacket);
    PPP_GETSHORT(ulCiLen, pPacket);

    if (ulCiLen < CHAP_HEADERLEN)
    {
        /*输出错误调试信息*/
        CHAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, "Too short packet!");
        PPP_DBG_ERR_CNT(PPP_PHERR_44);
        return;
    }

    ulCiLen -= CHAP_HEADERLEN;

    /* 依照 ucCode 采用相应的动作 */
    switch (ucCode)
    {
        case CHAP_PACKET_CODE_CHALLENGE:
            PPP_CHAP_ReceiveChallenge(pstPppInfo, pPacket, ucId, ulCiLen);
            break;

        case CHAP_PACKET_CODE_RESPONSE:
            PPP_CHAP_ReceiveResponse(pstPppInfo, pPacket, ucId, ulCiLen);
            break;

        case CHAP_PACKET_CODE_FAILURE:
            PPP_CHAP_ReceiveFailure(pstPppInfo);
            break;

        case CHAP_PACKET_CODE_SUCCESS:
            PPP_CHAP_ReceiveSuccess(pstPppInfo);
            break;

        default:
            PPP_DBG_ERR_CNT(PPP_PHERR_45);
            PPP_CHAP_ReceiveUnknownCode(pstPppInfo);
            break;
    }
    return;
}

/*****************************************************************************
 函 数 名  : PPP_CHAP_GetHrpdResponse
 功能描述  : PPPC模块通知SIM卡计算CHAP鉴权response值,并根据卡类型决定使用MD5或者CAVE算法
 输入参数  : pstPppInfo    携带PPP信息
             pstMsg        构造发送给卡计算response的消息
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-08-27
    作    者   : c00184031
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 PPP_CHAP_GetHrpdResponse
(
    PPPINFO_S                          *pstPppInfo,
    PPPC_AUTH_MSG_STRU                 *pstMsg
)
{
    PPPC_RAT_MODE_ENUM_UINT8            enRatMode;
    VOS_UINT32                          ulRandu = 0;
    PS_BOOL_ENUM_UINT8                  enIsCaveAlgorithmEnable;
    PS_BOOL_ENUM_UINT8                  enIsMD5AlgorithmEnable;


    /* 如果是HRPD模式，由USIM卡来计算Response */
    enRatMode = PPPC_GetRatMode();
    if ((PPPC_RAT_MODE_HRPD == enRatMode) || (PPPC_RAT_MODE_EHRPD == enRatMode))
    {
        /*lint -e701*/
        ulRandu = ((VOS_UINT8)(pstMsg->szPwd[0]) << 24)
                 | ((VOS_UINT8)(pstMsg->szPwd[1]) << 16)
                 | ((VOS_UINT8)(pstMsg->szPwd[2]) << 8)
                 | ((VOS_UINT8)(pstMsg->szPwd[3]));
        /*lint +e701*/
        PPPC_SaveRunCaveRandu(ulRandu);

        enIsCaveAlgorithmEnable = PPPC_IsCaveAlgorithmEnable();
        enIsMD5AlgorithmEnable  = PPPC_MD5Active();
        /* 不支持CAVE算法 或 支持CAVE算法且MD5算法可用 时让USIM卡使用MD5算法 */
        if ((PS_FALSE == enIsCaveAlgorithmEnable) || (PS_TRUE == enIsMD5AlgorithmEnable))
        {
            /* 使用MD5算法 */
            PPPC_UIM_MD5ChapAuthReq(pstPppInfo, pstMsg);
            return VOS_OK;
        }
        else
        {
            /* 使用CAVE算法 */
            PPPC_UIM_RunCaveAuthReq(ulRandu);
            return VOS_OK;
        }
    }

    PPPC_WARNING_LOG2("It is 1X mode,should not let sim compute response\r\n", enRatMode, ulRandu);

    return VOS_ERR;
}

/****************************************************************************
* CREATE DATE  ：2000/06/12                                                 *
* CREATED BY   ：Zhu Feng Zhi                                               *
* FUNCTION     ：CHAP收到对端的Challenge包                                    *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstPppInfo:PPP控制块指针                                   *
*                 pPacket:报文头位置                                            *
*                 ucId:报文ID                                                *
*                ulLen:报文数据长度                                            *
* OUTPUT       ：                                                           *
* RETURN       ：                                                            *
* CALLED BY    ：PPP_CHAP_ReceivePacket                                        *
****************************************************************************/
VOID PPP_CHAP_ReceiveChallenge(PPPINFO_S *pstPppInfo, UCHAR *pPacket, UCHAR ucId, VOS_UINT32 ulLen)
{
    PPPCHAPINFO_S                      *pstChapInfo;
    PPPC_AUTH_MSG_STRU                  stMsg;
    VOS_INT32                           lLen = (VOS_INT32)ulLen;
    VOS_UINT32                          ulRet;
    PS_BOOL_ENUM_UINT8                  enIsDoingAccessAuth;


    if (pstPppInfo == NULL)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_46);
        return;
    }

    pstChapInfo = pstPppInfo->pstChapInfo;
    if (pstChapInfo == NULL)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_47);
        return;
    }

    PPP_MemSet((VOID *)&stMsg, 0, sizeof(PPPC_AUTH_MSG_STRU));

    /*输出事件调试信息*/
    CHAP_Debug_Event(pstPppInfo, CHAP_RECEIVECHALLENGE);
    if (pstChapInfo->ucClientState == CHAP_STATE_CLIENT_INITIAL)
    {
        /*输出错误调试信息*/
        CHAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, "CHAP receive Challenge packet on CHAP_STATE_CLIENT_INITIAL!");
        PPP_DBG_ERR_CNT(PPP_PHERR_48);
        return;
    }

    /*取出Challenge,用于产生Response*/
    PPP_GETCHAR(stMsg.ucPwdLen, pPacket);
    (VOID)VOS_MemCpy((CHAR * )stMsg.szPwd, pPacket, (VOS_UINT32)stMsg.ucPwdLen);

    /*pPacket指针移动*/
    PPP_INCPTR(stMsg.ucPwdLen, pPacket);

    /* 计算Name域长度 */
    lLen -= (LONG)sizeof (UCHAR) + (LONG)(stMsg.ucPwdLen);
    if (lLen < 0) /*是否过短*/
    {
        /*输出错误调试信息*/
        PPP_DBG_ERR_CNT(PPP_PHERR_49);
        CHAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, "Too short packet!");
        return;
    }

    if (lLen >= PPP_MAXUSERNAMELEN)   /*是否过长*/
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_50);
        lLen = PPP_MAXUSERNAMELEN;
    }

    /*保存Challenge ID*/
    pstChapInfo->ucRespId = ucId;

    /*取得对端Hostname,用于产生Response*/
    stMsg.ucUsrNameLen = (UCHAR )lLen;
    (VOID)VOS_MemCpy((CHAR * )stMsg.szUsrName, pPacket, (VOS_UINT32)lLen);

    /*取得Challeng Id,用于产生Response */
    stMsg.ucPktID = ucId;

    /*删除等待RespTimeoutID超时定时器*/
    if (pstChapInfo->ulRespTimeoutID != 0)
    {
        (VOID)VOS_StopRelTimer(&(pstChapInfo->ulRespTimeoutID));
        pstChapInfo->ulRespTimeoutID = 0;
    }

    /* 接入鉴权不需要从节点获取密码 */
    enIsDoingAccessAuth = PPPC_IsDoingAccessAuth((VOS_UINT8)pstPppInfo->ulRPIndex);
    if (PS_TRUE == enIsDoingAccessAuth)
    {
        /* 接入鉴权必须用SIM卡算,不管内部用MD5/CAVE算法或者成功失败都直接退出 */
        (VOS_VOID)PPP_CHAP_GetHrpdResponse(pstPppInfo, &stMsg);
        return;
    }
    else
    {
        /*取本地的password,作为产生Response的备用secret */
        ulRet = PPP_GetConfigPassWord((VOS_UINT8 *)stMsg.szResponse);
        if (VOS_OK != ulRet)
        {
            PPPC_WARNING_LOG("Get pass word fail when when receive challenge.");
        }

        stMsg.ucResponseLen = (UCHAR )VOS_StrLen((VOS_CHAR *)(stMsg.szResponse));
    }

    if (PS_TRUE != g_enGetChapRespSelf)
    {
        ulRet = PPP_CHAP_GetHrpdResponse(pstPppInfo, &stMsg);
        if (VOS_OK == ulRet)
        {
            /* 返回OK说明是HRPD模式,可以用SIM卡算,否则需要MS自己用MD5算法计算 */
            return;
        }

    }
    else
    {
        g_enGetChapRespSelf = PS_FALSE;
    }

    /*根据Challeng Id,Challenge,secret(由对端Hostname得出)产生Response */
    if (PPPC_MD5_GenResponse( &stMsg ))
    {
        /*保存Response 及长度*/
        (VOID)VOS_MemCpy((CHAR *)pstChapInfo->szResponse, (UCHAR*)(stMsg.szResponse),
                           (VOS_UINT32 )stMsg.ucResponseLen );
        pstChapInfo->szResponse[stMsg.ucResponseLen] = 0;
        pstChapInfo->ucRespLen = stMsg.ucResponseLen;
        PPP_CHAP_SendResponse(pstPppInfo);
    }
    else
    {
        /*输出错误调试信息*/
        CHAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, "Generate response error!");
        PPP_DBG_ERR_CNT(PPP_PHERR_51);

        /* 删除定时器 */
        PPP_CHAP_DeleteTimer(pstPppInfo);

        /* 向内核报CHAP验证失败 */
        PPP_Core_ReceiveEventFromProtocol(pstPppInfo, (VOS_UINT32)PPP_EVENT_CHAPFAILED, NULL);
    }

    return;
}

/****************************************************************************
* CREATE DATE  ：2000/06/12                                                 *
* CREATED BY   ：Zhu Feng Zhi                                               *
* FUNCTION     ：CHAP收到对端的Response包, 向AAA请求验证                    *
* MODIFY DATE  ：modified by gxf for GGSN80 20030220                        *
* INPUT        ：pstPppInfo:PPP控制块指针                                   *
*                 pPacket:报文头位置                                            *
*                 ucId:报文ID                                                *
*                ulLen:报文数据长度                                            *
* OUTPUT       ：                                                           *
* RETURN       ：                                                            *
* CALLED BY    ：PPP_CHAP_ReceivePacket                                        *
****************************************************************************/
VOID PPP_CHAP_ReceiveResponse(PPPINFO_S *pstPppInfo, UCHAR *pPacket, UCHAR ucId, VOS_UINT32 ulLen)
{
    PPPCHAPINFO_S *pstChapInfo = pstPppInfo->pstChapInfo;
    AAA_AUTHREQ_S *pstMsg;

    UCHAR ucValueSize;
    LONG lLen = (LONG)ulLen;

    if (pstChapInfo == NULL)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_52);
        return;
    }

    /*输出事件调试信息*/
    CHAP_Debug_Event(pstPppInfo, CHAP_RECEIVERESPONSE);

    if ((pstChapInfo->ucServerState == CHAP_STATE_SERVER_INITIAL)
        || (pstChapInfo->ucServerState == CHAP_STATE_WAITING_AAA))
    {
        /*输出错误调试信息*/
        CHAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING,
                         "CHAP receive Response ON CHAP_STATE_SERVER_INITIAL or CHAP_STATE_WAITING_AAA phase!");
        PPP_DBG_ERR_CNT(PPP_PHERR_53);
        return;
    }

    if (ucId != pstChapInfo->ucChalId)    /*ID 不匹配 */
    {
        HSGW_EmsTraceByRpIndex(pstPppInfo->ulRPIndex, HSGW_EMS_MODULE_PPP, EMS_PPP_19);
        /*输出错误调试信息*/
        CHAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, "unmatched ID!");
        PPP_DBG_ERR_CNT(PPP_PHERR_54_RESP_CHAID_ERR);
        return;
    }

    /* 收到多次或假的Response依然要回送与第一次收到Response一样的answer(Success/Failure)*/
    if (pstChapInfo->ucServerState != CHAP_STATE_SEND_CHALLENGE)
    {
         /*Modified by liushuang for DTS2011112802965. L2TP用户建立隧道时收到
           终端的response消息，直接丢弃*/
        if ( ( 0 == pstPppInfo->bReNego )
                && (0 == pstPppInfo->bPppClient)
                 && (1 == pstPppInfo->bPppMode))
        {
            PPP_DBG_OK_CNT(PPP_PHOK_820);
        }
        else
        {
            PPP_CHAP_SendStatus(pstPppInfo, pstChapInfo->ucServerState); /* return auth-result */
        }
        return;
    }

    if ((pstPppInfo->ulPeerIPAddr) && (0 == pstPppInfo->bReNego))
    {
        PPP_DBG_OK_CNT(PPP_PHOK_821);
    }

    /*删除等待Response 超时定时器*/
    if (pstChapInfo->ulChalTimeoutID != 0)
    {
        (VOID)VOS_StopRelTimer(&(pstChapInfo->ulChalTimeoutID));
        pstChapInfo->ulChalTimeoutID = 0;
    }

    if (pstChapInfo->pstAAAAuthReqMsg)
    {
        pstMsg = pstChapInfo->pstAAAAuthReqMsg;
    }
    else
    {
        pstMsg = (AAA_AUTHREQ_S *)PPP_Malloc(sizeof(AAA_AUTHREQ_S));
        if (!pstMsg)
        {
            CHAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, "Malloc error!");
            PPP_DBG_ERR_CNT(PPP_PHERR_55);
            return;
        }

        pstChapInfo->pstAAAAuthReqMsg = pstMsg;
    }

    PPP_MemSet((VOID *)pstMsg, 0, sizeof(AAA_AUTHREQ_S));

    /* Response消息中的ResponseLen、Response */
    PPP_GETCHAR(ucValueSize, pPacket);        /* 取得MD 长度 */
    /* 构造验证信息块stMsg  */
    if (ucValueSize > CHAP_MAX_RESPONSE_LENGTH)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_822);
        pstMsg->ucChapResponseLen = CHAP_MAX_RESPONSE_LENGTH;
    }
    else
    {
        pstMsg->ucChapResponseLen = ucValueSize;
    }

    /* 取出 response 中的secret到 msg */
    (VOID)VOS_MemCpy((CHAR *)pstMsg->ucChapResponse, pPacket, (VOS_UINT32 )pstMsg->ucChapResponseLen);
    pstMsg->ucChapResponse[pstMsg->ucChapResponseLen] = 0x0;

    /* 取出 CHAP 控制块中的 challenge 到 msg */
    pstMsg->ucChapChallengeLen = pstChapInfo->ucChalLen;
    (VOID)VOS_MemCpy((CHAR *)pstMsg->ucChapChallenge, pstChapInfo->szChallenge, (VOS_UINT32)pstMsg->ucChapChallengeLen);
    pstMsg->ucChapChallenge[pstMsg->ucChapChallengeLen] = 0x0;

    /* 取出 response 中的name到 msg */
    PPP_INCPTR(ucValueSize, pPacket);
    lLen -= (LONG)sizeof (UCHAR) + (LONG)ucValueSize;

    /* Modified start by lvyanfang 00110869 at 2008-05-12 PDSN9660V800R005C02B018SP04 for 允许Chap Response消息中不带用户名属性 */
    if ((0 == (g_ulSoftPara567 & 0x01)) && (lLen <= 0))
    {
        HSGW_EmsTraceByRpIndex(pstPppInfo->ulRPIndex, HSGW_EMS_MODULE_PPP, EMS_PPP_20);
        SNMP_SetFailReason(pstPppInfo, FSM_ALARM_AUTH_ERROR_ACCOUNT);
        /*End of liushuang*/
        PPP_CHAP_AAAAuthFailed(pstChapInfo);
        CHAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, "Too short packet!");
        PPP_DBG_ERR_CNT(PPP_PHERR_56);
        return;
    }
    else
    {
        /* 兼容R1C3B047 版本允许不携带用户名属性 */
        if (lLen < 0)
        {
            SNMP_SetFailReason(pstPppInfo, FSM_ALARM_AUTH_ERROR_ACCOUNT);
            /*End of liushuang*/
            PPP_CHAP_AAAAuthFailed(pstChapInfo);
            CHAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, "Too short packet!");
            PPP_DBG_ERR_CNT(PPP_PHERR_57);
            return;
        }
    }
    /* Modified end by lvyanfang 00110869 at 2008-05-12 PDSN9660V800R005C02B018SP04 for 允许Chap Response消息中不带用户名属性 */

    if (lLen > A11_MAX_NAI_LENGTH)
    {
        HSGW_EmsTraceByRpIndex(pstPppInfo->ulRPIndex, HSGW_EMS_MODULE_PPP, EMS_PPP_21);
        PPP_CHAP_SendStatus(pstPppInfo, CHAP_STATE_SERVER_FAILED);
        A11_ReqNumSubProc(pstPppInfo);

        SNMP_SetFailReason(pstPppInfo, FSM_ALARM_AUTH_ERROR_ACCOUNT);
        /*End of liushuang*/
        PPP_CHAP_AAAAuthFailed(pstChapInfo);
        PPP_DBG_ERR_CNT(PPP_PHERR_58);
        PPPC_INFO_LOG1("\r\n PPP_CHAP_ReceiveResponse: NAI Len(%u) > 63", lLen);
        return;
    }

    pstMsg->ucUsernameLen = (UCHAR)lLen;
    (VOID)VOS_MemCpy((CHAR *)pstMsg->ucUsername, pPacket, (VOS_UINT32)pstMsg->ucUsernameLen);
    pstMsg->ucUsername[pstMsg->ucUsernameLen] = 0x0;

    if ((0 != pstPppInfo->ucNAI[0]) && 0 != VOS_StrCmp((CHAR*)(pstMsg->ucUsername), (CHAR*)(pstPppInfo->ucNAI)))
    {
        HSGW_EmsTraceByRpIndex(pstPppInfo->ulRPIndex, HSGW_EMS_MODULE_PPP, EMS_PPP_22);
        SNMP_SetFailReason(pstPppInfo, FSM_ALARM_AUTH_ERROR_ACCOUNT);
        /*End of liushuang*/
        PPP_CHAP_SendStatus(pstPppInfo, CHAP_STATE_SERVER_FAILED);
        PPP_CHAP_AAAAuthFailed(pstChapInfo);
        CHAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, "NAI != username");
        PPP_DBG_ERR_CNT(PPP_PHERR_59);
        return;
    }

  #ifdef    __PRODUCT_TYPE_PDSN80

    PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
               "\r\n PPP_CHAP_ReceiveResponse:the domainindex is (%u)(%u)",
               pstPppInfo->usCDBIndex,
               pstPppInfo->usVirtualDomainIdx);

    if ((pstPppInfo->usCDBIndex >= RM_MAX_APN_NUM)
       && (pstPppInfo->usVirtualDomainIdx >= RM_MAX_APN_NUM))
    {
        PPP_DBG_OK_CNT(PPP_PHOK_823);
        if (VOS_OK != PPP_GetDomainInfoByName(pstPppInfo, pstMsg->ucUsername))
        {

            SNMP_SetFailReason(pstPppInfo, FSM_ALARM_AUTH_ERROR_ACCOUNT);
            /*End of liushuang*/
            PPP_CHAP_AAAAuthFailed(pstChapInfo);
            PPP_DBG_ERR_CNT(PPP_PHERR_60);
            return;
        }
    }

    A11_UpdateDomainIndexAtEntryState(pstPppInfo->ulRPIndex, pstPppInfo->usCDBIndex, VOS_FALSE);

    (VOID)VOS_sprintf((char*)pstPppInfo->ucNAI, "%s", pstMsg->ucUsername);


    /* 判断CPU是否过载
    if (1 == g_ulSpuOverloadFlag)
    {
        DebugOut((VOS_UINT32)FSU_TID_PPPC, 1, "\r\nPPP_CHAP_ReceiveAuthReq:The cpu is over loading.");
        PPP_CHAP_AAAAuthFailed(pstChapInfo);
        return;
    }*/

    /* 根据LOCK标志判断是否允许激活，如是被LOCK，则不允许它激活，返回协商失败 */
    if ((PPP_DOMAIN_LOCKED == g_pstApnByIndex[pstPppInfo->usCDBIndex].ucLock)
        || (PPP_DOMAIN_LOCKED == g_pstApnByIndex[pstPppInfo->usVirtualDomainIdx].ucLock))
    {
        HSGW_EmsTraceByRpIndex(pstPppInfo->ulRPIndex, HSGW_EMS_MODULE_PPP, EMS_PPP_23);
        PPP_DBG_ERR_CNT(PPP_PHERR_61);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                     "\r\n PPP_CHAP_ReceiveResponse:The domain is locked, the domainindex is (%u)(%u)",
                     pstPppInfo->usCDBIndex,
                     pstPppInfo->usVirtualDomainIdx);
        PPP_CHAP_AAAAuthFailed(pstChapInfo);
        return;
    }

    if(VOS_TRUE == pstPppInfo->bAuthFlag)
    {
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                            "\r\n [ppp]PPP_CHAP_ReceiveResponse: pstPppInfo->bAuthFlag is %u bPpcAAAFlag %d",
                            pstPppInfo->bAuthFlag,
                            pstPppInfo->bPpcAAAFlag);

        /* 不需要到AAA鉴权 */
        if (0 == pstPppInfo->bPpcAAAFlag)
        {
            PPP_CHAP_SendStatus(pstPppInfo, CHAP_STATE_SERVER_SUCCESS);
            PPP_PerfInc(&g_stPppPerfStatistic.ulChapSuccess, PERF_TYPE_PPPC_CHAP_AUTHEN_SUCC_NUM, pstPppInfo->bEhrpdUser);

            if (NULL != pstChapInfo->pstAAAAuthReqMsg)
            {
                PPP_Free( pstChapInfo->pstAAAAuthReqMsg);
                pstChapInfo->pstAAAAuthReqMsg = NULL;
                pstMsg = NULL;
            }

            PPP_DBG_OK_CNT(PPP_PHOK_824);
            pstPppInfo->bAuthServer = VRP_NO;
            PPP_Core_ReceiveEventFromProtocol(pstPppInfo, (VOS_UINT32)PPP_EVENT_CHAPSUCCESS, NULL);

            return;
        }
    }

  #endif
    pstMsg->ulMsgType  = PPPC_AAA_CREAT_REQ;
    pstMsg->ulSDBIndex = pstPppInfo->ulRPIndex;
    pstMsg->usCDBIndex = pstPppInfo->usCDBIndex;
    /*pstMsg->usVPNID = pstPppInfo->usVPNID;*/
    pstMsg->ucPktID = ucId;
    pstMsg->stIMSI = pstPppInfo->stIMSI;

    /* Add by g00127633 for 预付费重协商*/
    pstMsg->ucRenegoFlag = pstPppInfo->bPpcAAAFlag;
    /* 输出状态转换调试信息 */
    CHAP_Debug_StateChange(pstPppInfo, CHAP_STATE_WAITING_AAA, CHAP_SERVER_STATE);
    pstChapInfo->ucServerState = CHAP_STATE_WAITING_AAA;

#if (VRP_MODULE_SEC_L2TP == VRP_YES)
    /* 设置PPP 与 L2TP 通信数据 */
    if (pstPppInfo->pL2tpPara != NULL)
    {
        L2TP_SESSIONPARA_S *pstOptionalPara = (L2TP_SESSIONPARA_S*)pstPppInfo->pL2tpPara;

        /* 设置验证类型 */
        pstOptionalPara->usAuthenType = L2TP_PPP_CHAP;

        /* 设置被验证用户名 */
        VOS_MemCpy(pstOptionalPara->szAuthenName,
                        pstMsg->ucUsername,
                        pstMsg->ucUsernameLen);
        pstOptionalPara->szAuthenName[pstMsg->ucUsernameLen] = 0x0;

        /* 设置Challenge */
        pstOptionalPara->ulChallengeLen = pstMsg->ucChapChallengeLen;
        VOS_MemCpy(pstOptionalPara->szChallenge,
                        pstMsg->ucChapChallenge,
                        pstMsg->ucChapChallengeLen);
        pstOptionalPara->szChallenge[pstMsg->ucChapChallengeLen] = 0x0;

        /* 设置Response */
        pstOptionalPara->ulResponseLen = pstMsg->ucChapResponseLen;
        VOS_MemCpy(pstOptionalPara->szResponse,
                        pstMsg->ucChapResponse,
                        pstMsg->ucChapResponseLen);
        pstOptionalPara->szResponse[pstMsg->ucChapResponseLen] = 0x0;

        pstOptionalPara->usAuthenID = pstChapInfo->ucChalId;
    }
#endif

    /*向AAA 申请验证*/
    /*PPP_Shell_AuthRequest(pstPppInfo->ulIfIndex, &stMsg);*/
#if 0
    PPP_CHAP_SendAAAAuthReq(pstChapInfo);
#endif
    return;
}

#if 0
/*****************************************************************************
 函 数 名  : PPP_CHAP_ReceiveAAAResult
 功能描述  : Chap模块收到AAA鉴权消息
 输入参数  : AAA_AUTHRSP_S *pMsg
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月30日
    作    者   : luofang
    修改内容   : 新生成函数

*****************************************************************************/
VOID PPP_CHAP_ReceiveAAAResult(AAA_AUTHRSP_S *pMsg)
{
    UCHAR ucResult;
    PPPINFO_S *pstPppInfo;
    PPPCHAPINFO_S *pstChapInfo;

    PPP_TRACE("\r\n---Into PPP_CHAP_ReceiveAAAResult---\r\n");

    /*判断输入参数的有效性*/
    if (NULL == pMsg)
    {
        VOS_DBGASSERT(pMsg);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n PPP_CHAP_ReceiveAAAResult: Invalid input parameter!");
        return;
    }

    PPP_DBG_OK_CNT(PPP_PHOK_825);
    GETPPPINFOPTRBYRP(pstPppInfo, pMsg->ulSDBIndex);
    if (pstPppInfo == NULL)
    {
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n PPP_CHAP_ReceiveAAAResult: User %d isn't exist!", pMsg->ulSDBIndex);
        PPP_DBG_ERR_CNT(PPP_PHERR_62);
        return;
    }

    pstChapInfo = pstPppInfo->pstChapInfo;
    if (pstChapInfo == NULL)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_63);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n PPP_CHAP_ReceiveAAAResult: User %d  pstChapInfo isn't exist!",
                     pMsg->ulSDBIndex);
        return;
    }

    /* 删除定时器 */
    if (pstChapInfo->ulChalTimeoutID)
    {
        (VOID)VOS_StopRelTimer(&(pstChapInfo->ulChalTimeoutID));
        pstChapInfo->ulChalTimeoutID = 0;
    }

    /* 释放AAA认证请求消息 */
    if (pstChapInfo->pstAAAAuthReqMsg)
    {
        PPP_Free(pstChapInfo->pstAAAAuthReqMsg);
        pstChapInfo->pstAAAAuthReqMsg = NULL;
    }

    /*输出事件调试信息*/
    CHAP_Debug_Event(pstPppInfo, CHAP_AAARESULT);
    if (pstChapInfo->ucServerState != CHAP_STATE_WAITING_AAA)    /* 状态与事件不符 */
    {
        /*输出错误调试信息*/
        CHAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, "Illegal event!");
        PPP_DBG_ERR_CNT(PPP_PHERR_64);
        return;
    }

    /* 认证成功 */
    if (pMsg->ucResult == 0)
    {
        PPP_PerfInc(g_stPppPerfStatistic.pulChapSuccess, PERF_TYPE_PPPC_CHAP_AUTHEN_SUCC_NUM, pstPppInfo->bEhrpdUser);

        /* 验证通过 */
        ucResult = CHAP_STATE_SERVER_SUCCESS;
        PPP_CHAP_SendStatus(pstPppInfo, ucResult);
        PPP_DBG_OK_CNT(PPP_PHOK_826);

        /* 删除定时器 */
        PPP_CHAP_DeleteTimer(pstPppInfo);

        if (pstChapInfo->ulChalInterval != 0)
        {
            if (pstChapInfo->ulChalTimeoutID == 0)
            {
                /* 设置下次chap验证时间 */
                (VOID)VOS_Timer_Create(g_ulPPPTaskId,
                                                       g_ulPppTimeQueID,
                                                       pstChapInfo->ulChalInterval,
                                                       PPP_CHAP_Rechallenge,
                                                       (VOID *) pstPppInfo->ulRPIndex,
                                                       &(pstChapInfo->ulChalTimeoutID), VOS_TIMER_LOOP );
            }
            else
            {
                PPP_DBG_ERR_CNT(PPP_PHERR_65);
                VOS_DBGASSERT(0);
            }
        }

        /* 通知内核 chap Server端验证通过 */
        pstPppInfo->bAuthServer = VRP_NO;
        PPP_Core_ReceiveEventFromProtocol(pstPppInfo, (VOS_UINT32)PPP_EVENT_CHAPSUCCESS, (CHAR*)pMsg);
    }
    else
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_66);

        /* 验证未通过 */
        ucResult = CHAP_STATE_SERVER_FAILED;
        PPP_CHAP_SendStatus(pstPppInfo, ucResult);

        /* 输出状态转换调试信息 */
        CHAP_Debug_StateChange(pstPppInfo, CHAP_STATE_SERVER_FAILED, CHAP_SERVER_STATE);
        pstChapInfo->ucClientState = CHAP_STATE_SERVER_FAILED;/* 改变状态 */
        /* 删除定时器 */
        PPP_CHAP_DeleteTimer(pstPppInfo);

        /* 超过验证失败次数, 向内核报CHAP验证失败 */
        PPP_SET_REL_CODE(pstPppInfo, AM_RELCODE_PPP_CHAP_NAK);
        PPP_Core_ReceiveEventFromProtocol(pstPppInfo, (VOS_UINT32)PPP_EVENT_CHAPFAILED, NULL);
        A11_PPP_TermTag(pstPppInfo->ulRPIndex, Authentication_Fail);
    }

    return;
}


/*****************************************************************************
 函 数 名  : PPP_CHAP_SendAAAAuthReq
 功能描述  : 向AAA发送鉴权请求
 输入参数  : PPPCHAPINFO_S *pstChapInfo
             AAA_AUTHREQ_S *pstMsg
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2003年2月21日
    作    者   : gxf
    修改内容   : 新生成函数

*****************************************************************************/
VOID PPP_CHAP_SendAAAAuthReq(PPPCHAPINFO_S *pstChapInfo)
{
    AAA_AUTHREQ_S *pstMsg = NULL;
    VOS_UINT32 ulRet;
    PPPINFO_S *pstPppInfo;

    PPP_TRACE("\r\n---Into PPP_CHAP_SendAAAAuthReq---\r\n");
    PPP_DBG_OK_CNT(PPP_PHOK_827);

    if (NULL == pstChapInfo)
    {
        VOS_DBGASSERT(0);
        PPP_DBG_ERR_CNT(PPP_PHERR_67);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "PPP_CHAP_SendAAAAuthReq: pstChapInfo=NULL");
        return;
    }

    pstMsg = pstChapInfo->pstAAAAuthReqMsg;
    if (NULL == pstMsg)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_68);
        VOS_DBGASSERT(0);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "PPP_CHAP_SendAAAAuthReq: pstMsg=NULL");
        return;
    }

    pstPppInfo = pstChapInfo->pstPppInfo;
    if (NULL == pstPppInfo)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_69);
        VOS_DBGASSERT(0);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "PPP_CHAP_SendAAAAuthReq: pstChapInfo->pstPppInfo=NULL");
        return;
    }

    /* 用于控制是否将NAI转换成小写软参 */
    if (1 == M_SPM_USER_NAME_LOWERCASE)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_828);
        VOS_lowercase((CHAR*)(((AAA_AUTHREQ_S*)pstMsg)->ucUsername));
    }

    ((AAA_AUTHREQ_S*)pstMsg)->ucPPPFlag =1;
    ulRet = PPP_SendRtMsg(PPP_SELF_CSI,
                         g_ullPppAuthCsi,
                         AUTH_MSG_TYPE_PPP,
                         PPP_AUTH_FLAG,
                         (UCHAR *)pstMsg,
                         sizeof( AAA_AUTHREQ_S ));
    if ( VOS_OK != ulRet )
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_70);
        PPP_Debug_CoreEvent(pstPppInfo, PPP_LOG_ERROR, "PPP_CHAP_SendAAAAuthReq: OSS_Que_Write Err!!");
        return;
    }
    ///TODO:luofang 是否需要内部消息跟踪
    /* 内部消息跟踪 */
    /*  是否需要
    PPP_InternalMsgTrc(PPP_INNERTRC_AAA_REQ, pstMsg, pstPppInfo->ulRPIndex);
    */

    /* 设置超时定时器 */
    VOS_DBGASSERT(pstChapInfo->ulChalTimeoutID == 0);
    ulRet = PGP_Timer_Create(PPP_SELF_CSI,
                             PPP_MSG_TYPE_TIMER,
                             pstChapInfo->ulWaitAuthRspTimeout,
                             PPP_CHAP_AuthRspTimeout,
                             (VOID*)pstPppInfo->ulRPIndex,
                             &(pstChapInfo->ulChalTimeoutID),
                             VOS_TIMER_LOOP);
    if (ulRet != VOS_OK)
    {
        CHAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, "PGP_Timer_Create error!");
        PPP_DBG_ERR_CNT(PPP_PHERR_71);
        /*PPP_CHAP_AAAAuthFailed(pstChapInfo);*/
    }
    PPP_DBG_OK_CNT(PPP_PHOK_829);

    ++pstChapInfo->ucAuthTransmits;
    return ;
}
#endif

/****************************************************************************
* CREATE DATE  ：2000/06/12                                                 *
* CREATED BY   ：Zhu Feng Zhi                                               *
* FUNCTION     ：CHAP收到对端验证成功回应, 进入新状态并报CHAP SUCCESS        *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstPppInfo:PPP控制块指针                                   *
*                 ucId:报文ID                                                *
* OUTPUT       ：                                                           *
* RETURN       ：                                                            *
* CALLED BY    ：PPP_CHAP_ReceivePacket                                        *
****************************************************************************/
VOID PPP_CHAP_ReceiveSuccess(PPPINFO_S *pstPppInfo)
{
    PPPCHAPINFO_S                      *pstChapInfo = pstPppInfo->pstChapInfo;
    PS_BOOL_ENUM_UINT8                  enIsDoingAccesAuth;
    VOS_UINT32                          ulRet;
    CTTF_PPPC_AUTH_INFO_STRU            stPppAuthInfo;


    if (pstChapInfo == NULL)
    {
        PPPC_WARNING_LOG1("chapinfo is null:pppId", pstPppInfo->ulRPIndex);
        return;
    }


    if (pstChapInfo->ucClientState != CHAP_STATE_SEND_RESPONSE)
    {
        PPPC_WARNING_LOG1("Illegal event!:ucClientState", pstChapInfo->ucClientState);
        return;
    }

    /*删除等待对端验证结果超时定时器*/
    if (pstChapInfo->ulRespTimeoutID != 0)
    {
        (VOID)VOS_StopRelTimer(&(pstChapInfo->ulRespTimeoutID));
        pstChapInfo->ulRespTimeoutID = 0;
    }

    pstChapInfo->ucClientState = CHAP_STATE_CLIENT_SUCCESS; /* 改变状态 */
    /*向内核报 CHAP Client 端验证成功 */
    pstPppInfo->bAuthClient = VRP_NO;

    /* 删除定时器 */
    PPP_CHAP_DeleteTimer(pstPppInfo);

    /* 可维可测 */
    /* PPPC CHAP鉴权成功报文跟踪 */
    PPPC_GetPppAuthInfo(&stPppAuthInfo);
    PPPC_MntnTraceAuthResult((VOS_UINT8)pstPppInfo->ulRPIndex,
                PPP_CHAP, VOS_OK, &stPppAuthInfo);

    enIsDoingAccesAuth = PPPC_IsDoingAccessAuth((VOS_UINT8)pstPppInfo->ulRPIndex);
    if (PS_TRUE == enIsDoingAccesAuth)
    {
        ulRet = PPP_StopNegoTimer((VOS_UINT8)pstPppInfo->ulRPIndex);
        if (VOS_OK != ulRet)
        {
            PPPC_WARNING_LOG2("Stop timer fail!\r\n", pstPppInfo->ulRPIndex, enIsDoingAccesAuth);
        }

        /* 接入鉴权完成需要删除PPP实体的节点 */
        PPP_NodeDelete(0);

        if (PS_FALSE != PPPC_GetInitAccessAuthMode())
        {
            /* 初始接入鉴权只要设置一次即可 */
            PPPC_SetInitAccessAuthMode(PS_FALSE);
        }

        /* 接入鉴权标志位恢复需要提前做 */
        PPPC_AccessAuthSuccProc();

        /* 通知RPA接入鉴权结束 */
        PPPC_HRPD_SendRpaAccessAuthRsp(CTTF_HRPD_PPP_ACCESS_AUTH_RCV_CHAP_SUCC);

        /* 如果正在进行接入鉴权,不切换到IPCP阶段 */
        PPPC_ChangeAccessAuthState(PS_FALSE, (VOS_UINT8)(pstPppInfo->ulRPIndex));

        return;
    }

    PPP_Core_ReceiveEventFromProtocol (pstPppInfo, (VOS_UINT32)PPP_EVENT_CHAPSUCCESS, NULL);

    return;
}

/****************************************************************************
* CREATE DATE  ：2000/06/12                                                 *
* CREATED BY   ：Zhu Feng Zhi                                               *
* FUNCTION     ：CHAP收到对端验证失败回应, 进入新状态，                        *
*                并向内核报CHAP Client 端验证失败                            *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstPppInfo:PPP控制块指针                                   *
*                 pPacket:报文头位置                                            *
*                 ucId:报文ID                                                *
*                ulLen:报文数据长度                                            *
* OUTPUT       ：                                                           *
* RETURN       ：                                                            *
* CALLED BY    ：PPP_CHAP_ReceivePacket                                        *
****************************************************************************/
VOID PPP_CHAP_ReceiveFailure(PPPINFO_S *pstPppInfo)
{
    PPPCHAPINFO_S *pstChapInfo = pstPppInfo->pstChapInfo;
    CHAR cErrstr[100];
    PS_BOOL_ENUM_UINT8                  enIsDoingAccesAuth;
    CTTF_PPPC_AUTH_INFO_STRU            stPppAuthInfo;

    if (pstChapInfo == NULL)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_74);
        return;
    }

    /*更新OM可维可测信息*/
    g_stPppcStatRpt.stPppcStatisticInfo.ulNameOrPwdAuthFailCnt++;
    PPP_MNTN_CMO_SendOmResourceStateInfo();

    /*输出事件调试信息*/
    CHAP_Debug_Event(pstPppInfo, CHAP_AUTHFAILURE);

    if (pstChapInfo->ucClientState != CHAP_STATE_SEND_RESPONSE)
    {
        /*输出错误调试信息*/
        CHAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, "Illegal event!");
        PPP_DBG_ERR_CNT(PPP_PHERR_75);
        return;
    }

    /*删除等待对端验证结果超时定时器*/
    if (pstChapInfo->ulRespTimeoutID != 0)
    {
        (VOID)VOS_StopRelTimer(&(pstChapInfo->ulRespTimeoutID));
        pstChapInfo->ulRespTimeoutID = 0;
    }

    /*Client端验证失败次数加一*/
    pstChapInfo->usAuthClientFailureTimes += 1;

    /*输出错误调试信息*/
    (VOID)VOS_sprintf(cErrstr, "Client auth failed No. %2d !",
                      pstChapInfo->usAuthClientFailureTimes );
    CHAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, cErrstr);

    /* 验证失败次数过多, 向上报CHAP DOWN */
    PPP_DBG_ERR_CNT(PPP_PHERR_76);
    /* 输出状态转换调试信息 */
    CHAP_Debug_StateChange(pstPppInfo, CHAP_STATE_CLIENT_FAILED, CHAP_CLIENT_STATE);
    pstChapInfo->ucClientState = CHAP_STATE_CLIENT_FAILED; /* 改变状态 */
    /* 删除定时器 */
    PPP_CHAP_DeleteTimer(pstPppInfo);

    PPPC_GetPppAuthInfo(&stPppAuthInfo);
    PPPC_MntnTraceAuthResult((VOS_UINT8)(pstPppInfo->ulRPIndex), PPP_CHAP,
                    VOS_ERR, &stPppAuthInfo);


    enIsDoingAccesAuth = PPPC_IsDoingAccessAuth((VOS_UINT8)pstPppInfo->ulRPIndex);
    if (PS_TRUE == enIsDoingAccesAuth)
    {
        if (PS_FALSE != PPPC_GetInitAccessAuthMode())
        {
            /* 初始接入鉴权只要设置一次即可 */
            PPPC_SetInitAccessAuthMode(PS_FALSE);
        }

        PPPC_StopAllAccessAuthDelayProcTimer();

        /* 通知RPA接入鉴权结束 */
        PPPC_HRPD_SendRpaAccessAuthRsp(CTTF_HRPD_PPP_ACCESS_AUTH_RCV_CHAP_REJECT);

        /* 如果正在进行接入鉴权,清除标志位 */
        PPPC_ChangeAccessAuthState(PS_FALSE, (VOS_UINT8)(pstPppInfo->ulRPIndex));
    }
    else
    {
        /* 电信规范要求业务协商时Chap鉴权失败需要发送Lcp Terminate Req进行PPP断链 */
        PPP_Core_ReceiveEventFromProtocol(pstPppInfo,PPP_EVENT_CHAPFAILED, NULL);
    }

    return;
}

/****************************************************************************
* CREATE DATE  ：2000/06/12                                                 *
* CREATED BY   ：Zhu Feng Zhi                                               *
* FUNCTION     ：CHAP向对端发出验证challenge                                *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstPppInfo:PPP控制块指针                                   *
* OUTPUT       ：                                                           *
* RETURN       ：                                                            *
* CALLED BY    ：PPP_CHAP_ServerLowerUp,PPP_CHAP_ChallengeTimeout,            *
*                 PPP_CHAP_ServerSuccess,PPP_CHAP_Rechallenge                *
****************************************************************************/
VOID PPP_CHAP_SendChallenge(PPPINFO_S *pstPppInfo)
{
    PPPCHAPINFO_S *pstChapInfo = pstPppInfo->pstChapInfo;
    UCHAR *pHead, *pPacket;
    VOS_UINT16 usChal_len, usName_len;
    VOS_UINT16 usOutLen;
    VOS_UINT32 ulOffset;
    VOS_UINT32 ulErrorCode;

    PPPC_INFO_LOG("\r\n---Into PPP_CHAP_SendChallenge---\r\n");

    if (pstChapInfo == NULL)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_77);
        return;
    }

    /* 预留出打PPP报文头的空间 */
    ulOffset = PPP_RESERVED_PACKET_HEADER;

    /* 申请内存 */
    pHead = g_ucPppSendPacketHead;

    /* 防止IP泄露，增加异常打点计数 */
    if (pstPppInfo->ulPeerIPAddr && (0 == pstPppInfo->bReNego))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_79);
    }

    pPacket = pHead + ulOffset;

    usChal_len = pstChapInfo->ucChalLen;
    usName_len = (VOS_UINT16 )VOS_StrLen((VOS_CHAR *)(pstChapInfo->szHostName));
    usOutLen = CHAP_HEADERLEN + 1 + usChal_len + usName_len;

    PPP_PUTCHAR(CHAP_PACKET_CODE_CHALLENGE, pPacket);            /*CHAP CODE */
    PPP_PUTCHAR(pstChapInfo->ucChalId, pPacket);        /*CHAP ID */
    PPP_PUTSHORT(usOutLen, pPacket);                    /*CHAP LENGTH */

    /* 写challege Length,challenge以及Name*/
    PPP_PUTCHAR(usChal_len, pPacket);
    (VOID)VOS_MemCpy((CHAR *)pPacket, pstChapInfo->szChallenge, (VOS_UINT32) usChal_len);
    PPP_INCPTR(usChal_len, pPacket);
    (VOID)VOS_MemCpy((CHAR *)pPacket, pstChapInfo->szHostName, (VOS_UINT32)usName_len);
    PPP_INCPTR(usName_len, pPacket );
    pPacket -= usOutLen;

    /*输出调试信息*/
    CHAP_Debug_Packet(pstPppInfo, pPacket, (VOS_UINT32)usOutLen, PPP_CHAP, 0);

    /* 直接调用外壳的发送函数 */
    ulErrorCode = PPP_Shell_GetPacketFromCore((CHAR *)pstPppInfo, pHead, pPacket, (VOS_UINT32) usOutLen, PPP_CHAP);
    if (ulErrorCode != VOS_OK)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_80);
        /*输出调试信息*/
        CHAP_Debug_Error(pstPppInfo, PPP_LOG_ERROR, "Send Packet Failed!");
    }

    if (pstChapInfo->ulChalTimeoutID == 0)
    {
        /* 设置重传chap验证时间 */
        (VOS_VOID)VOS_StartRelTimer((HTIMER *)&(pstChapInfo->ulChalTimeoutID), MID_PPPC,
            pstChapInfo->ulTimeOutTime, pstPppInfo->ulRPIndex, PPPC_CHAP_CHALLENGE_RESEND_TIMER,
            VOS_TIMER_LOOP, VOS_TIMER_PRECISION_0);
    }
    else
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_81);
    }

    /* 输出状态转换调试信息 */
    CHAP_Debug_StateChange(pstPppInfo, CHAP_STATE_SEND_CHALLENGE, CHAP_SERVER_STATE);
    pstChapInfo->ucServerState = CHAP_STATE_SEND_CHALLENGE; /* 改变状态 */

    ++pstChapInfo->ulChalTransmits;

    return;
}

/****************************************************************************
* CREATE DATE  ：2000/06/12                                                 *
* CREATED BY   ：Zhu Feng Zhi                                               *
* FUNCTION     ：CHAP向对端送出验证成功/失败报文                            *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstPppInfo:PPP控制块指针                                   *
*                 ucResult: 验证结果                                            *
* OUTPUT       ：                                                           *
* RETURN       ：                                                            *
* CALLED BY    ：PPP_CHAP_ReceiveResponse,PPP_CHAP_ServerSuccess            *
****************************************************************************/
VOID PPP_CHAP_SendStatus(PPPINFO_S *pstPppInfo, UCHAR ucResult)
{
    PPPCHAPINFO_S *pstChapInfo = pstPppInfo->pstChapInfo;
    UCHAR *pPacket, *pHead;
    VOS_UINT16 usOutLen, usMsgLen;
    VOS_UINT32 ulOffset;
    CHAR msg[256];
    VOS_UINT32 ulErrorCode;

    if (pstChapInfo == NULL)
    {
        return;
    }

    PPP_DBG_OK_CNT(PPP_PHOK_830);

    /* 预留出打PPP报文头的空间 */
    ulOffset = PPP_RESERVED_PACKET_HEADER;

    /* 申请内存 */
    pHead = g_ucPppSendPacketHead;

    pPacket = pHead + ulOffset;

    /* 输出状态转换调试信息 */
    CHAP_Debug_StateChange(pstPppInfo, ucResult, CHAP_SERVER_STATE);
    pstChapInfo->ucServerState = ucResult;    /* 改变状态 */

    if (ucResult == CHAP_PACKET_CODE_SUCCESS)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_831);
        (VOID)VOS_sprintf(msg, "Welcome to %s.", pstChapInfo->szHostName);
    }
    else
    {
        PPP_DBG_OK_CNT(PPP_PHOK_832);
        (VOID)VOS_sprintf(msg, "Illegal user or password.");
    }

    usMsgLen = (VOS_UINT16)VOS_StrLen(msg);

    /*计算报文长度 */
    usOutLen = (VOS_UINT16)(CHAP_HEADERLEN + usMsgLen);

    PPP_PUTCHAR(ucResult, pPacket);                /*CHAP CODE */
    PPP_PUTCHAR(pstChapInfo->ucChalId, pPacket);    /*CHAP ID */
    PPP_PUTSHORT(usOutLen, pPacket);                /*CHAP LENGTH */
    /* 报文message */
    (VOID)VOS_MemCpy((CHAR *)pPacket, msg, (VOS_UINT32) usMsgLen);
    PPP_INCPTR(usMsgLen, pPacket);

    pPacket -= usOutLen; /* 恢复指向 CHAP 报文头 */

    /*输出报文调试信息*/
    CHAP_Debug_Packet(pstPppInfo, pPacket, (VOS_UINT32)usOutLen, PPP_CHAP, 0);

    /* 直接调用外壳的发送函数 */
    ulErrorCode = PPP_Shell_GetPacketFromCore((CHAR *)pstPppInfo, pHead, pPacket, (VOS_UINT32 )usOutLen, PPP_CHAP);
    if (ulErrorCode != VOS_OK)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_83);
        /*输出调试信息*/
        CHAP_Debug_Error(pstPppInfo, PPP_LOG_ERROR, "Send Packet Failed!");
    }
    PPP_DBG_OK_CNT(PPP_PHOK_833);

    return;
}

/****************************************************************************
* CREATE DATE  ：2000/06/12                                                 *
* CREATED BY   ：Zhu Feng Zhi                                               *
* FUNCTION     ：产生一个随机字符串, 同时 Challenge ID 加 1                    *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstChapInfo:CHAP控制块指针                                 *
* OUTPUT       ：随机字符串放入pstChapInfo->szChallenge                        *
*                 随机字符串长度放入pstChapInfo->len                            *
* RETURN       ：                                                            *
* CALLED BY    ：PPP_CHAP_ReceiveResponse,PPP_CHAP_ServerSuccess            *
****************************************************************************/
VOID PPP_CHAP_GenChallenge(PPPCHAPINFO_S *pstChapInfo)
{
    UCHAR ucChalLen;
    UCHAR *ptr;
    UCHAR i;
    VOS_UINT32 ulRand = 0;

    ptr = pstChapInfo->szChallenge;

    /* 选出一长度在MIN_CHALLENGE_LENGTH和MAX_CHALLENGE_LENGTH之间的随机长度 */
    ucChalLen = CHAP_MAX_CHALLENGE_LENGTH;
    pstChapInfo->ucChalLen = ucChalLen;

    /*CHAP 控制块 Challenge Id 加 1 */
    pstChapInfo->ucChalId++;

    /*add by y00125257 CR20110607034 DTS2012020303820: 打开软参则使用固定的chap challenge*/
    /* 产生随机字符串 */

    for (i = 0; i < ucChalLen; i++)
    {
        (VOID)PPPC_CRYPT_random((UCHAR*)&ulRand, (SEC_UINT32)sizeof(VOS_UINT32));
        *ptr = (UCHAR )(ulRand * 0xff);
        ptr++;
    }

    return;
}

/****************************************************************************
* CREATE DATE  ：2000/06/12                                                 *
* CREATED BY   ：Zhu Feng Zhi                                               *
* FUNCTION     ：CHAP向对端送出response报文, 并改变状态                        *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstPppInfo:PPP控制块指针                                   *
* OUTPUT       ：                                                           *
* RETURN       ：                                                            *
* CALLED BY    ：PPP_CHAP_ReceiveResponse,PPP_CHAP_ServerSuccess            *
****************************************************************************/
VOID PPP_CHAP_SendResponse(PPPINFO_S *pstPppInfo)
{
    PPPCHAPINFO_S *pstChapInfo = pstPppInfo->pstChapInfo;
    UCHAR *pPacket, *pHead;
    UCHAR  *pName;
    VOS_UINT16 usOutLen, usMdLen, usNameLen;
    VOS_UINT32 ulOffset;
    VOS_UINT32 ulErrorCode;

    if (pstChapInfo == NULL)
    {
        return;
    }

    /* 预留出打PPP报文头的空间 */
    ulOffset = PPP_RESERVED_PACKET_HEADER;

    /* 申请内存 */
    pHead = g_ucPppSendPacketHead;

    pPacket = pHead + ulOffset;

    pName     = pstChapInfo->szHostName;
    usMdLen   = pstChapInfo->ucRespLen;
    usNameLen = (VOS_UINT16) VOS_StrLen((VOS_CHAR *)pName);

    /* 如果查不到用户名就再查一次防止SIM卡回复慢导致用户名为空 */
    if (0 == usNameLen)
    {
        (VOS_VOID)PPP_GetConfigUserName((VOS_UINT8 *)pstChapInfo->szHostName, pstPppInfo->ulRPIndex);
        pName     = pstChapInfo->szHostName;
        usNameLen = (VOS_UINT16) VOS_StrLen((VOS_CHAR *)pName);
    }

    usOutLen = CHAP_HEADERLEN + sizeof (UCHAR) + usMdLen + usNameLen;

    PPP_PUTCHAR(CHAP_PACKET_CODE_RESPONSE, pPacket);        /* CHAP CODE -RESPONSE */
    PPP_PUTCHAR(pstChapInfo->ucRespId, pPacket);    /* CHAP ID */
    PPP_PUTSHORT(usOutLen, pPacket);                /* CHAP LENGTH */

    /* secret长度和secret  */
    PPP_PUTCHAR(usMdLen, pPacket);
    (VOID)VOS_MemCpy((CHAR * )pPacket, pstChapInfo->szResponse, (VOS_UINT32)usMdLen);
    PPP_INCPTR(usMdLen, pPacket);

    /* 添加NAME */
    (VOID)VOS_MemCpy((CHAR *)pPacket, pName, (VOS_UINT32)usNameLen);
    PPP_INCPTR(usNameLen, pPacket);
    pPacket -= usOutLen; /* 恢复指向 CHAP 报文头 */

    /*输出报文调试信息*/
    CHAP_Debug_Packet(pstPppInfo, pPacket, (VOS_UINT32)usOutLen, PPP_CHAP, 0);

    /* 直接调用外壳的发送函数 */
    ulErrorCode = PPP_Shell_GetPacketFromCore((CHAR *)pstPppInfo, pHead, pPacket, (VOS_UINT32)usOutLen, PPP_CHAP);
    if (ulErrorCode != VOS_OK)
    {
        /*输出调试信息*/
        CHAP_Debug_Error(pstPppInfo, PPP_LOG_ERROR, "Send Packet Failed!");
    }

    if (pstChapInfo->ulRespTimeoutID == 0)
    {
        /* 设置重传response时间 */
        (VOS_VOID)VOS_StartRelTimer((HTIMER *)&(pstChapInfo->ulRespTimeoutID), MID_PPPC,
            pstChapInfo->ulTimeOutTime, pstPppInfo->ulRPIndex, PPPC_CHAP_RESPONSE_RESEND_TIMER,
            VOS_TIMER_LOOP, VOS_TIMER_PRECISION_0);
    }
    else
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_85);
    }

    ++pstChapInfo->ulRespTransmits;

    /* 输出状态转换调试信息 */
    CHAP_Debug_StateChange(pstPppInfo, CHAP_STATE_SEND_RESPONSE, CHAP_CLIENT_STATE);
    pstChapInfo->ucClientState = CHAP_STATE_SEND_RESPONSE;/* 改变状态 */
    PPP_DBG_OK_CNT(PPP_PHOK_834);

    return;
}

/****************************************************************************
* CREATE DATE  ：2000/06/12                                                 *
* CREATED BY   ：Zhu Feng Zhi                                               *
* FUNCTION     ：CHAP发送Challenge 超时，进行相应处理                        *
*                 超过最大重传次数，向内核报CHAP 验证失败                    *
*                 否则再次发送Challenge                                        *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstPppInfo:PPP控制块指针                                   *
* OUTPUT       ：                                                           *
* RETURN       ：                                                            *
* CALLED BY    ：CHAP 定时器ulChalTimeoutID触发                                *
****************************************************************************/
VOS_VOID PPP_CHAP_ChallengeTimeout(VOS_UINT32 ulPppId)
{
    PPPINFO_S *pstPppInfo;
    PPPCHAPINFO_S *pstChapInfo;
    CHAR cErrstr[100];

    GETPPPINFOPTRBYRP(pstPppInfo, ulPppId);
    if (pstPppInfo == 0)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_86);
        return;
    }

    pstChapInfo = pstPppInfo->pstChapInfo;
    if (pstChapInfo == 0)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_87);
        return;
    }

    /*输出事件调试信息*/
    CHAP_Debug_Event(pstPppInfo, CHAP_CHALLENGETIMEOUT);

    /*清除定时器*/
    if (pstChapInfo->ulChalTimeoutID)
    {
        (VOID)VOS_StopRelTimer(&(pstChapInfo->ulChalTimeoutID));
        pstChapInfo->ulChalTimeoutID = 0;
    }

    if (pstChapInfo->ucServerState != CHAP_STATE_SEND_CHALLENGE)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_88);
        /*输出错误调试信息*/
        CHAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, "Illegal event!");
        return;
    }

    /*输出错误调试信息*/
    (VOID)VOS_sprintf(cErrstr, "Send Challenge No. %2lu !", pstChapInfo->ulChalTransmits);
    CHAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, cErrstr);

    if (pstChapInfo->ulChalTransmits >= pstChapInfo->ulMaxTransmits)
    {
        pstChapInfo->ulChalTransmits = 0;

        /* 输出状态转换调试信息 */
        CHAP_Debug_StateChange(pstPppInfo, CHAP_STATE_SERVER_FAILED, CHAP_SERVER_STATE);
        pstChapInfo->ucServerState = CHAP_STATE_SERVER_FAILED; /* 改变状态 */
        /* 删除定时器 */
        PPP_CHAP_DeleteTimer(pstPppInfo);

        SNMP_SetFailReason(pstPppInfo, FSM_ALARM_AUTH_MS_NO_RSP);
        HSGW_EmsTraceByRpIndex(pstPppInfo->ulRPIndex, HSGW_EMS_MODULE_PPP, EMS_PPP_24);


        /*向内核报CHAP 验证失败*/
        PPP_SET_REL_CODE(pstPppInfo, AM_RELCODE_PPP_CHAP_CHLTIMEOUT);
        PPP_Core_ReceiveEventFromProtocol(pstPppInfo, (VOS_UINT32)PPP_EVENT_CHAPFAILED, NULL);


        A11_ReqNumSubProc(pstPppInfo);
        PPP_DBG_ERR_CNT(PPP_PHERR_89);


        return;
    }

    pstChapInfo->ucChalId++;
    /*End of liushuang*/

    PPP_DBG_OK_CNT(PPP_PHOK_835);
    PPP_CHAP_SendChallenge(pstPppInfo);        /*重传 challenge */
}

/****************************************************************************
* CREATE DATE  ：2000/06/12                                                 *
* CREATED BY   ：Zhu Feng Zhi                                               *
* FUNCTION     ：CHAP发送Response 超时，进行相应处理                        *
*                 再次发送Response                                            *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstPppInfo:PPP控制块指针                                   *
* OUTPUT       ：                                                           *
* RETURN       ：                                                            *
* CALLED BY    ：CHAP 定时器ulRespTimeoutID触发                                *
****************************************************************************/
VOS_VOID PPP_CHAP_ResponseTimeout(VOS_UINT32 ulPppId)
{
    PPPINFO_S *pstPppInfo;
    PPPCHAPINFO_S *pstChapInfo;
    CHAR cErrstr[100];

    GETPPPINFOPTRBYRP(pstPppInfo, ulPppId);
    if (pstPppInfo == 0)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_91);
        return;
    }

    pstChapInfo = pstPppInfo->pstChapInfo;
    if (pstChapInfo == 0)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_92);
        return;
    }

    /*输出事件调试信息*/
    CHAP_Debug_Event(pstPppInfo, CHAP_RESPONSETIMEOUT);

    /*清除定时器*/
    (VOID)VOS_StopRelTimer(&(pstChapInfo->ulRespTimeoutID));
    pstChapInfo->ulRespTimeoutID = 0L;

    if (pstChapInfo->ucClientState != CHAP_STATE_SEND_RESPONSE)
    {
        /*输出错误调试信息*/
        CHAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, "Illegal event!" );
        PPP_DBG_ERR_CNT(PPP_PHERR_93);
        return;
    }

    /*输出错误调试信息*/
    (VOID)VOS_sprintf(cErrstr, "Send Response No. %2lu !", pstChapInfo->ulRespTransmits);
    CHAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, cErrstr);

    if (pstChapInfo->ulRespTransmits >= pstChapInfo->ulMaxTransmits)
    {
        /* 输出状态转换调试信息 */
        CHAP_Debug_StateChange(pstPppInfo, CHAP_STATE_CLIENT_FAILED, CHAP_CLIENT_STATE);
        pstChapInfo->ucClientState = CHAP_STATE_CLIENT_FAILED; /* 改变状态 */
        /* 删除定时器 */
        PPP_CHAP_DeleteTimer(pstPppInfo);

        /*向内核报CHAP 验证失败*/
        PPP_SET_REL_CODE(pstPppInfo, AM_RELCODE_PPP_CHAP_RSPTIMEOUT);
        PPP_Core_ReceiveEventFromProtocol(pstPppInfo, (VOS_UINT32)PPP_EVENT_CHAPFAILED, NULL);
        PPP_DBG_ERR_CNT(PPP_PHERR_94);
        return;
    }
    PPP_DBG_OK_CNT(PPP_PHOK_836);

    PPP_CHAP_SendResponse(pstPppInfo);        /* 重传 response */

    return;
}

/*****************************************************************************
 函 数 名  : PPP_CHAP_AuthRspTimeout
 功能描述  : CHAP等待AAA验证结果超时
 输入参数  : VOID *pMsg
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2003年2月21日
    作    者   : gxf
    修改内容   : 新生成函数

*****************************************************************************/
VOID PPP_CHAP_AuthRspTimeout(VOID *ulIndex)
{
#if 0
    PPPINFO_S *pstPppInfo = NULL;
    PPPCHAPINFO_S *pstChapInfo = NULL;
    AAA_AUTHREQ_S *pstAuthRspMsg = NULL;
    VOS_UINT32 ulIdxTmp = (VOS_UINT32)ulIndex;

    PPP_TRACE("\r\n---Into PPP_CHAP_AuthRspTimeout---\r\n");
    PPP_DBG_OK_CNT(PPP_PHOK_837);

    GETPPPINFOPTRBYRP(pstPppInfo, (VOS_UINT32)ulIndex);
    if (NULL == pstPppInfo)
    {
        VOS_DBGASSERT(0);
        PPP_DBG_ERR_CNT(PPP_PHERR_95);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "PPP_CHAP_AuthRspTimeout: ulIdxTmp(%d)pstPppInfo=NULL", ulIdxTmp);
        return;
    }

    pstChapInfo = (PPPCHAPINFO_S *)pstPppInfo->pstChapInfo;
    if (NULL == pstChapInfo)
    {
        //VOS_DBGASSERT(0);
        PPP_DBG_ERR_CNT(PPP_PHERR_96);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "PPP_CHAP_AuthRspTimeout: ulIdxTmp(%d)pstChapInfo=NULL", ulIdxTmp);
        return;
    }

    pstAuthRspMsg = pstChapInfo->pstAAAAuthReqMsg;
    if(NULL == pstAuthRspMsg)
    {
        VOS_DBGASSERT(0);
        PPP_DBG_ERR_CNT(PPP_PHERR_97);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "PPP_CHAP_AuthRspTimeout: ulIdxTmp(%d)pstAuthRspMsg=NULL", ulIdxTmp);
        return;
    }

    pstPppInfo = pstChapInfo->pstPppInfo;
    if(NULL == pstPppInfo)
    {
        VOS_DBGASSERT(0);
        PPP_DBG_ERR_CNT(PPP_PHERR_98);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "PPP_CHAP_AuthRspTimeout: ulIdxTmp(%d)pstChapInfo->pstPppInfo=NULL", ulIdxTmp);
        return;
    }

    if(pstChapInfo->ucServerState != CHAP_STATE_WAITING_AAA)
    {
        VOS_DBGASSERT(0);
        PPP_DBG_ERR_CNT(PPP_PHERR_99);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "PPP_CHAP_AuthRspTimeout: ulIdxTmp(%d)pstChapInfo->ucServerState(%d)",
                         ulIdxTmp, pstChapInfo->ucServerState);
        return;
    }

    /* 输出事件调试信息 */
    CHAP_Debug_Event(pstPppInfo, CHAP_AAARESULTTIMEOUT);

    /* 清除定时器 */
    VOS_DBGASSERT(pstChapInfo->ulChalTimeoutID);
    (VOID)VOS_StopRelTimer(&(pstChapInfo->ulChalTimeoutID));
    pstChapInfo->ulChalTimeoutID = 0;

    if (pstChapInfo->ucAuthTransmits >= pstChapInfo->ulAuthMaxTransmits)
    {
        HSGW_EmsTraceByRpIndex(pstPppInfo->ulRPIndex, HSGW_EMS_MODULE_PPP, EMS_PPP_25);
        PPP_DBG_ERR_CNT(PPP_PHERR_100);
        SNMP_SetFailReason(pstPppInfo, FSM_ALARM_AUTH_AAA_NO_RSP);
        /*End of liushuang*/
        PPP_SET_REL_CODE(pstPppInfo, AM_RELCODE_PPP_CHAP_AAATIMEOUT);
        PPP_CHAP_AAAAuthFailed(pstChapInfo);
    }
    else
    {
        PPP_DBG_OK_CNT(PPP_PHOK_838);
        PPP_CHAP_SendAAAAuthReq(pstChapInfo);
    }
#endif
    return;
}

/****************************************************************************
* CREATE DATE  ：2000/06/12                                                 *
* CREATED BY   ：Zhu Feng Zhi                                               *
* FUNCTION     ：CHAP定时向对端发送challenge                                *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstPppInfo:PPP控制块指针                                   *
* OUTPUT       ：                                                           *
* RETURN       ：                                                            *
* CALLED BY    ：CHAP 定时器ulChalTimeoutID触发                                *
****************************************************************************/
VOID PPP_CHAP_Rechallenge(VOID *ulIndex)
{
    PPPINFO_S *pstPppInfo = NULL;
    PPPCHAPINFO_S *pstChapInfo;

    GETPPPINFOPTRBYRP(pstPppInfo, (VOS_UINT32)ulIndex);
    if (NULL == pstPppInfo)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_101);
        return;
    }

    pstChapInfo = pstPppInfo->pstChapInfo;

    /*输出事件调试信息*/
    CHAP_Debug_Event(pstPppInfo, CHAP_RECHANLLENGE);

    /*清除定时器*/
    (VOID)VOS_StopRelTimer(&(pstChapInfo->ulChalTimeoutID));
    pstChapInfo->ulChalTimeoutID = 0;

    if (pstChapInfo->ucServerState != CHAP_STATE_SERVER_SUCCESS)
    {
        /*输出错误调试信息*/
        CHAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, "Illegal event!" );
        PPP_DBG_ERR_CNT(PPP_PHERR_102);
        return;
    }
    PPP_DBG_OK_CNT(PPP_PHOK_839);

    /*向内核报CHAP 重新验证*/
    PPP_Core_ReceiveEventFromProtocol(pstPppInfo, (VOS_UINT32)PPP_EVENT_RECHALLENGE, NULL);

    PPP_CHAP_GenChallenge(pstChapInfo);    /*产生challege */
    PPP_CHAP_SendChallenge(pstPppInfo);    /*发送challege */

    return;
}

/****************************************************************************
* CREATE DATE  ：2000/06/12                                                 *
* CREATED BY   ：Zhu Feng Zhi                                               *
* FUNCTION     ：CHAP收到一非法协议, 通知底层DOWN                            *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstPppInfo:PPP控制块指针                                   *
* OUTPUT       ：                                                           *
* RETURN       ：                                                            *
* CALLED BY    ：                                                            *
****************************************************************************/
VOID PPP_CHAP_ReceiveUnknownCode(PPPINFO_S *pstPppInfo)
{
    /*输出调试信息*/
    CHAP_Debug_Event(pstPppInfo, CHAP_CODEREJECT);

    return;
}

/****************************************************************************
* CREATE DATE  ：2000/06/09                                                 *
* CREATED BY   ：Zhu Feng Zhi                                               *
* FUNCTION     ：删除定时器                                                    *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstPppInfo:PPP控制块指针                                   *
* OUTPUT       ：                                                           *
* RETURN       ：                                                            *
* CALLED BY    ：                                                            *
****************************************************************************/
VOID PPP_CHAP_DeleteTimer(PPPINFO_S *pstPppInfo)
{
    PPPCHAPINFO_S *pstChapInfo = (PPPCHAPINFO_S *)pstPppInfo->pstChapInfo;

    if (pstChapInfo == NULL)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_103);
        return;
    }

    if (pstChapInfo->ulChalTimeoutID != 0)
    {
        (VOID)VOS_StopRelTimer(&(pstChapInfo->ulChalTimeoutID));   /* 删除challenge定时器 */
        pstChapInfo->ulChalTimeoutID = 0;
    }

    if (pstChapInfo->ulRespTimeoutID != 0)
    {
        (VOID)VOS_StopRelTimer(&(pstChapInfo->ulRespTimeoutID));    /* 删除Response 定时器 */
        pstChapInfo->ulRespTimeoutID = 0;
    }

    return;
}


/*lint -restore */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
