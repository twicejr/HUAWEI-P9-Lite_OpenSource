/************************************************************************
*                                                                      *
*                             Eap.c                                    *
*                                                                      *
*  Project Code:       VRP3.0                                          *
*  Create Date:        2010/07/05                                      *
*  Author:             WANGYONG                                        *
*  Modify Date:                                                        *
*  Document:                                                           *
*  Function:           PPP的EAP协议模块                                *
*  Others:                                                             *
*----------------------------------------------------------------------*
*                                                                      *
* Copyright 2000-2010 VRP3.0 Team Beijing Institute HuaWei Tech, Inc.  *
*                     ALL RIGHTS RESERVED                              *
*                                                                      *
*----------------------------------------------------------------------*
*                                                                      *
*   这个文件定义了EAP协议模块的全部接口函数和内部处理函数              *
*                                                                      *
************************************************************************/



/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "ppp_inc.h"



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID          PS_FILE_ID_PPPC_EAP_MGR_C
/*lint +e767*/



/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

#if (VRP_MODULE_LINK_PPP_EAP == VRP_YES)

/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*lint -save -e958 */

/*****************************************************************************
 函 数 名  : PPPC_EAP_Init
 功能描述  : EAP模块初始化.
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
VOID PPPC_EAP_Init(PPPINFO_S *pstPppInfo)
{
    PPPC_EAP_INFO_STRU                 *pstEapInfo;


    if (VOS_NULL_PTR == pstPppInfo)
    {
        PPPC_WARNING_LOG("pstPppInfo=NULL");
        return;
    }

    pstEapInfo  = (PPPC_EAP_INFO_STRU *)pstPppInfo->pstEapInfo;
    if (VOS_NULL_PTR == pstEapInfo)
    {
        PPPC_WARNING_LOG("pstEapInfo=NULL or pstConfig=NULL");
        return;
    }

    PPPC_EAP_InitMethod(pstEapInfo);

    PPPC_EAP_DeleteTimer(pstEapInfo);

    PPP_MemSet((VOID*)pstEapInfo, 0, sizeof(PPPC_EAP_INFO_STRU));

    pstEapInfo->pstPppInfo      = pstPppInfo;

    /* 初始化为0xffff防止初始化值与网络发送的第一个Request重复 */
    pstEapInfo->usEAPLastReqID  = 0xffff;

    return;
}


/****************************************************************************
* CREATE DATE  ：2010/07/12                                                 *
* CREATED BY   ：WANGYONG                                                   *
* FUNCTION     ：EAP接收外部事件.事件包括：ServerUp、Down                   *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstPppInfo:PPP控制块指针                                   *
*                ulCmd:命令字, 可以为如下值:                                *
*                EAP_EVENT_SERVERLOWERUP:对端下层UP                         *
*                EAP_EVENT_LOWERDOWN:下层DOWN                               *
*                pPara:事件的参数, 为NULL                                   *
* OUTPUT       ：                                                           *
* RETURN       ：NULL                                                       *
* CALLED BY    ：PPP_Core_ReceiveEventFromShell                             *
****************************************************************************/
VOS_VOID PPPC_EAP_ReceiveEventFromCore
(
    PPPINFO_S *pstPppInfo, VOS_UINT32 ulCmd, VOS_UINT8 *pPara
)
{
    if (VOS_NULL_PTR == pstPppInfo)
    {
        PPPC_WARNING_LOG("pstPppInfo=NULL");
        return;
    }

    switch (ulCmd)
    {
        case EAP_EVENT_LOWERDOWN:
            PPPC_EAP_LowerDown(pstPppInfo);
            break;

        default:
            /*输出错误调试信息*/
            PPPC_WARNING_LOG1("EAP Receive UNKNOWN Event!", ulCmd);
            break;
    }

    return;
}

/****************************************************************************
* CREATE DATE  ：2010/07/12                                                 *
* CREATED BY   ：WANGYONG                                                   *
* FUNCTION     ：PPP_EAP_LowerDown                                          *
*                进入EAP_STATE_SERVER_INITIAL状态                           *
*                同时删除定时器                                             *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstPppInfo:PPP控制块指针                                   *
* OUTPUT       ：                                                           *
* RETURN       ：                                                           *
* CALLED BY    ：PPP_EAP_ReceiveEventFromCore                               *
****************************************************************************/
VOID PPPC_EAP_LowerDown(PPPINFO_S *pstPppInfo)
{
    PPPC_EAP_INFO_STRU                 *pstEapInfo;

    if (VOS_NULL_PTR == pstPppInfo)
    {
        PPPC_WARNING_LOG("pstPppInfo=NULL");
        return;
    }

    pstEapInfo = (PPPC_EAP_INFO_STRU *)pstPppInfo->pstEapInfo;
    if (VOS_NULL_PTR == pstEapInfo)
    {
        PPPC_WARNING_LOG("pstEapInfo=NULL");
        return;
    }

    /* 删除定时器 */
    PPPC_EAP_DeleteTimer(pstEapInfo);

    PPPC_EAP_Init(pstPppInfo);

    /* 改变状态 */
    pstEapInfo->enEapPeerState  = PPPC_EAP_PEER_IDLE_STATE;

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_EAP_SendResponse
 功能描述  : 发送EAP Response报文
 输入参数  : pstPppInfo     PPP实体
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月09日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_EAP_SendResponse(VOS_UINT32 ulPppId)
{
    PPPC_EAP_INFO_STRU                 *pstEapInfo;
    PPPINFO_S                          *pstPppInfo;
    VOS_UINT8                          *pucHead;
    VOS_UINT8                          *pucPacket;
    VOS_UINT32                          ulOffset;
    VOS_UINT32                          ulErrorCode;
    PPPC_EAP_HEADER_STRU               *pstPayload;


    if (PPP_MAX_USER_NUM < ulPppId)
    {
        PPPC_WARNING_LOG1("Invalid ppp id", ulPppId);
        return;
    }

    pstPppInfo                  = &g_astPppPool[ulPppId];
    pstEapInfo                  = (PPPC_EAP_INFO_STRU *)pstPppInfo->pstEapInfo;

    if (VOS_NULL_PTR == pstEapInfo)
    {
        PPPC_WARNING_LOG("pstEapInfo=NULL");
        return;
    }

    /* 预留出打PPP报文头的空间 */
    ulOffset = PPP_RESERVED_PACKET_HEADER;

    PS_MEM_SET(g_ucPppSendPacketHead, 0,
        sizeof(g_ucPppSendPacketHead));

    /* 获取内存 */
    pucHead     = g_ucPppSendPacketHead;
    pucPacket   = pucHead + ulOffset;

    if (pstEapInfo->usRespPktLen >= PPPC_EAP_MAX_RESPONSE_LEN)
    {
        PPPC_WARNING_LOG1("Invalid payload len!", pstEapInfo->usRespPktLen);
        return;
    }

    /* 将EAP报文写入发送内存 */
    PS_MEM_CPY(pucPacket, pstEapInfo->aucRespPkt, pstEapInfo->usRespPktLen);

    pstPayload  = (PPPC_EAP_HEADER_STRU *)pstEapInfo->aucRespPkt;

    /* 保存发送的ID，用于下次收包时的重复帧检查 */
    pstEapInfo->usEAPLastReqID  = pstPayload->ucEAPID;

    /* 直接调用外壳的发送函数 */
    ulErrorCode = PPP_Shell_GetPacketFromCore((VOS_CHAR *)pstPppInfo,
                                              pucHead,
                                              pucPacket,
                                              pstEapInfo->usRespPktLen,
                                              PPP_EAP);
    if (VOS_OK != ulErrorCode)
    {
        /* 报文发送失败，清除Response相关变量 */
        PS_MEM_SET(pstEapInfo->aucRespPkt, 0, sizeof(pstEapInfo->aucRespPkt));
        pstEapInfo->usRespPktLen        = 0;
        pstEapInfo->usEAPLastReqID      = 0xffff;

        /*输出调试信息*/
        PPPC_WARNING_LOG1("Send EAP response fail", ulErrorCode);
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_EAP_DeleteTimer
 功能描述  : 停定时器
 输入参数  : pstEapInfo     EAP实体信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-11-9
    作    者   : c00184031
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_EAP_DeleteTimer(PPPC_EAP_INFO_STRU *pstEapInfo)
{
    VOS_UINT32                              ulRet;


    /* 内部调用保证指针非空 */

    if (VOS_NULL_PTR != pstEapInfo->hReqTimeoutID)
    {
        /* 停定时器 */
        ulRet = VOS_StopRelTimer((HTIMER*)&pstEapInfo->hReqTimeoutID);
        if (VOS_OK != ulRet)
        {
            PPPC_WARNING_LOG1("Stop timer fail!", ulRet);
        }
    }

    pstEapInfo->hReqTimeoutID   = VOS_NULL_PTR;

    return;
}

#endif

/*lint -restore */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
