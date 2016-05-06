/************************************************************************
*                                                                      *
*                             ppp_core.c                               *
*                                                                      *
*  Project Code:       VRP3.0                                          *
*  Create Date:        2000/04/04                                      *
*  Author:             Deng Yi Ou                                      *
*  Modify Date:                                                        *
*  Document:                                                           *
*  Function:           PPP流程控制模块及内核与外壳的接口               *
*  Others:                                                             *
*----------------------------------------------------------------------*
*                                                                      *
*  Copyright 2000-2002 VRP3.0 Team Beijing Institute HuaWei Tech, Inc. *
*                      ALL RIGHTS RESERVED                             *
*                                                                      *
*----------------------------------------------------------------------*
*                                                                      *
*  PPP流程控制模块及内核与外壳的接口                                   *
*                                                                      *
************************************************************************/



/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "ppp_inc.h"
#include "pppc_ctrl.h"



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
#define         THIS_FILE_ID            PS_FILE_ID_PPPC_CORE_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

VOS_UINT32 g_ulHsgwA10TestDbgFlg = VOS_FALSE;

S_CFG_DOMAINNODE g_pstApnByIndex[5];

/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*lint -save -e958 */
/*****************************************************************************
 函 数 名  : PPP_GetUserTypeByIpv4cpReq
 功能描述  : 根据Ipv4请求消息分析用户类型 SIPV4\CMIP
 输入参数  : UCHAR* pPacket
             VOS_UINT32 ulLen
             VOS_UINT32* pulMsgType
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月30日
    作    者   : luofang
    修改内容   : 新生成函数

*****************************************************************************/
/*lint -e550*/
VOS_UINT32 PPP_GetUserTypeByIpv4cpReq(PPPINFO_S *pstPppInfo, UCHAR* pPacket,VOS_UINT32 ulLen, VOS_UINT32* pulMsgType)
{
    VOS_UINT32 ulCiLen = 0;
    UCHAR ucResult = 0;
    UCHAR ucCode = 0;
    UCHAR ucId = 0;
    if ((VOS_NULL == pPacket)||(VOS_NULL == pulMsgType))
    {
        PPPC_WARNING_LOG("\r\n PPP_GetUserTypeByIpv4cpReq input para null");
        return VOS_ERR;
    }

    if (ulLen < FSM_HDRLEN)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_340);
        PPPC_WARNING_LOG("\r\n PPP_GetUserTypeByIpv4cpReq ulLen error!");
        return VOS_ERR;
    }

    /*报文解析*/
    PPP_GETCHAR(ucCode, pPacket);
    PPP_GETCHAR(ucId, pPacket);
    PPP_GETSHORT(ulCiLen, pPacket);

    if (ulCiLen > ulLen)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_341);
        PPPC_WARNING_LOG("\r\n PPP_GetUserTypeByIpv4cpReq ulCiLen error!");
        return VOS_ERR;
    }

    if (ulCiLen < FSM_HDRLEN)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_342);
        PPPC_WARNING_LOG("\r\n PPP_GetUserTypeByIpv4cpReq ulCiLen too short!");
        return VOS_ERR;
    }

    /* 报文长度减去FSM头的长度 */
    ulCiLen -= FSM_HDRLEN;
    /*判断SIP/MIP 1为SIP,0为MIP*/
    ucResult = (UCHAR)PPP_IPCP_IsSip((UCHAR *)pPacket, &ulCiLen);

    if (VOS_TRUE == ucResult)
    {
        *pulMsgType = E_FSM_ID_SIPV4;
        PPP_DBG_OK_CNT(PPP_PHOK_955);

        /* 此处判断原始类型是否无效，避免重协商类型变化 */
        PPP_SET_IPTECH(pstPppInfo, PPP_USERTYPE_SIP);
    }
    else
    {
        *pulMsgType = E_FSM_ID_CMIP;

        PPP_DBG_OK_CNT(PPP_PHOK_956);
        /* 此处判断原始类型是否无效，避免重协商类型变化 */
        PPP_SET_IPTECH(pstPppInfo, PPP_USERTYPE_MIP);
    }

    (VOS_VOID)ucId;
    (VOS_VOID)ucCode;
    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPP_CopyIpv4cpMsg
 功能描述  : 缓存用户发来的第一条Ipv4请求消息
 输入参数  : PPPINFO_S *pstPppInfo
             UCHAR *pHead
             UCHAR *pPacket
             VOS_UINT32 ulMsgLen
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月30日
    作    者   : luofang
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPP_CopyIpv4cpMsg(PPPINFO_S *pstPppInfo, UCHAR *pHead, UCHAR *pPacket, VOS_UINT32 ulMsgLen)
{

    UCHAR *pucCopyMsg = VOS_NULL;

    if ((VOS_NULL == pstPppInfo)||(VOS_NULL == pHead)||(VOS_NULL == pPacket))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_343);
        PPPC_WARNING_LOG(" \r\n PPP_CopyIpv4cpMsg: invalid paras.");
        return VOS_ERR;
    }

    /* 获取IPCP控制块 */
    if (NULL == pstPppInfo->pstIpcpInfo)
    {
        PPP_GETIPCPADDR(pstPppInfo->pstIpcpInfo, pstPppInfo->ulRPIndex);
        if (NULL == pstPppInfo->pstIpcpInfo)
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_344);
            /* Malloc Error */
            PPPC_WARNING_LOG(" \r\n PPP_CopyIpv4cpMsg: malloc ipcp CB fail!");
            return VOS_ERR;
        }
        PPP_MemSet(pstPppInfo->pstIpcpInfo, 0, sizeof(PPPIPCPINFO_S));
        PPP_IPCP_Init(pstPppInfo, pstPppInfo->ulIPAddr, pstPppInfo->ulPeerIPAddr);
    }

    if ( VOS_NULL != ((PPPIPCPINFO_S*)(pstPppInfo->pstIpcpInfo))->pucIpv4cpMsg )
    {
        (VOID)PPP_Free(((PPPIPCPINFO_S*)(pstPppInfo->pstIpcpInfo))->pucIpv4cpMsg);
        ((PPPIPCPINFO_S*)(pstPppInfo->pstIpcpInfo))->pucIpv4cpMsg = NULL;
    }

    pucCopyMsg = PPP_Malloc(ulMsgLen+PPP_RESERVED_PACKET_HEADER);
    if ( VOS_NULL == pucCopyMsg )
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_345);
        PPPC_WARNING_LOG(" \r\n PPP_CopyIpv4cpMsg: malloc pucCopyMsg fail!");
        return VOS_ERR;
    }
    ((PPPIPCPINFO_S*)(pstPppInfo->pstIpcpInfo))->pucIpv4cpMsg = pucCopyMsg;

    VOS_MemCpy(pucCopyMsg, pHead, PPP_RESERVED_PACKET_HEADER);
    VOS_MemCpy(pucCopyMsg+PPP_RESERVED_PACKET_HEADER, pPacket, ulMsgLen);

    ((PPPIPCPINFO_S*)(pstPppInfo->pstIpcpInfo))->ulIpv4cpLen = ulMsgLen;

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : PPP_CopyIpv6cpMsg
 功能描述  : 缓存用户发来的第一条Ipv6cp请求消息
 输入参数  : PPPINFO_S *pstPppInfo
             UCHAR *pHead
             UCHAR *pPacket
             VOS_UINT32 ulMsgLen
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月30日
    作    者   : luofang
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPP_CopyIpv6cpMsg(PPPINFO_S *pstPppInfo, UCHAR *pHead, UCHAR *pPacket, VOS_UINT32 ulMsgLen)
{
    UCHAR *pucCopyMsg = VOS_NULL;


    if ((VOS_NULL == pstPppInfo)||(VOS_NULL == pHead)||(VOS_NULL == pPacket))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_346);
        PPPC_WARNING_LOG(" \r\n PPP_CopyIpv6cpMsg: invalid paras.");
        return VOS_ERR;
    }

    /* 获取IPV6CP控制块 */
    if (NULL == pstPppInfo->pstIpV6cpInfo)
    {
        PPP_GETIPV6CPADDR(pstPppInfo->pstIpV6cpInfo, pstPppInfo->ulRPIndex);
        if (NULL == pstPppInfo->pstIpV6cpInfo)
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_347);
            /* Malloc Error */
            PPPC_WARNING_LOG(" \r\n PPP_CopyIpv6cpMsg: malloc ipv6cp CB fail!");
            return VOS_ERR;
        }
        PPP_MemSet(pstPppInfo->pstIpV6cpInfo, 0, sizeof(PPPIPV6CPINFO_S));
        PPP_IPV6CP_Init(pstPppInfo, pstPppInfo->usIpv6Addr, pstPppInfo->usPeerIPv6Addr);
    }

    if ( VOS_NULL != ((PPPIPV6CPINFO_S*)pstPppInfo->pstIpV6cpInfo)->pucIpv6cpMsg )
    {
        (VOID)PPP_Free(((PPPIPV6CPINFO_S*)pstPppInfo->pstIpV6cpInfo)->pucIpv6cpMsg);
        ((PPPIPV6CPINFO_S*)pstPppInfo->pstIpV6cpInfo)->pucIpv6cpMsg = NULL;
    }

    pucCopyMsg = PPP_Malloc(ulMsgLen+PPP_RESERVED_PACKET_HEADER);
    if ( VOS_NULL == pucCopyMsg )
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_348);
        PPPC_WARNING_LOG(" \r\n PPP_CopyIpv6cpMsg: malloc pucCopyMsg fail!");
        return VOS_ERR;
    }
    ((PPPIPV6CPINFO_S*)pstPppInfo->pstIpV6cpInfo)->pucIpv6cpMsg = pucCopyMsg;

    VOS_MemCpy(pucCopyMsg, pHead, PPP_RESERVED_PACKET_HEADER);
    VOS_MemCpy(pucCopyMsg+PPP_RESERVED_PACKET_HEADER, pPacket, ulMsgLen);

    ((PPPIPV6CPINFO_S*)(pstPppInfo->pstIpV6cpInfo))->ulIpv6cpLen = ulMsgLen;

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : PPP_CopyVsncpReqMsg
 功能描述  : 缓存ehrpd切换过程中的vsncp请求消息
 输入参数  : PPPINFO_S *pstPppInfo,
             UCHAR *pHead,
             UCHAR *pPacket,
             VOS_UINT32 ulLen,
             UCHAR ucCode
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月25日
    作    者   : wangyong 00138171
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPP_CopyVsncpReqMsg(PPPINFO_S *pstPppInfo,
                          UCHAR *pHead,
                          UCHAR *pPacket,
                          VOS_UINT32 ulLen,
                          UCHAR ucCode)
{
    UCHAR *pucCopyMsg = NULL;
    VOS_UINT32 ulReturn = VOS_OK;
    SDB_PDSN_RP_CONTEXT_S *pstRpContext = NULL;


    if (CONFREQ == ucCode)
    {
        ulReturn = (VOS_UINT32)SDB_GetRpContextByIndex(pstPppInfo->ulRPIndex, (VOS_VOID **)&pstRpContext);
        if (VOS_OK != ulReturn)
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_772);
            PPPC_WARNING_LOG1("\r\n PPP_CopyVsncpReqMsg: query context fail,RpIndex=%u",
                         pstPppInfo->ulRPIndex);
            return VOS_ERR;
        }

        if (NULL != pstRpContext->pucVsncpReq)
        {
            PPP_DBG_OK_CNT(PPP_PHOK_1470);
            PPP_Free(pstRpContext->pucVsncpReq);
            pstRpContext->pucVsncpReq = NULL;
        }

        pucCopyMsg = PPP_Malloc(ulLen + PPP_RESERVED_PACKET_HEADER + sizeof(VOS_UINT32));
        if (VOS_NULL == pucCopyMsg)
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_773);
            PPPC_WARNING_LOG1("\r\n PPP_CopyVsncpReqMsg: malloc pucVsncpReq fail[%u]!", ulLen);
            return VOS_ERR;
        }
        pstRpContext->pucVsncpReq = pucCopyMsg;
        *((VOS_UINT32 *)pucCopyMsg) = ulLen;

        VOS_MemCpy((pucCopyMsg + sizeof(VOS_UINT32)), pHead, PPP_RESERVED_PACKET_HEADER);
        VOS_MemCpy((pucCopyMsg + sizeof(VOS_UINT32) + PPP_RESERVED_PACKET_HEADER), pPacket, ulLen);

        PPP_DBG_OK_CNT(PPP_PHOK_1471);
    }
    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPP_Core_IpcpV4FinProc
 功能描述  : 单栈删除收到ipcp finished事件处理函数
 输入参数  : PPPINFO_S *pstPppInfo
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年1月13日
    作    者   : T62595
    修改内容   : 新生成函数

*****************************************************************************/
VOID PPP_Core_IpcpV4FinProc( PPPINFO_S *pstPppInfo )
{
    PPPIPCPINFO_S *pstIpcpInfo = NULL ;

    if ((NULL == pstPppInfo->pstLcpInfo) || (NULL == pstPppInfo->pstIpcpInfo))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_349);
        return;
    }

    pstIpcpInfo = (PPPIPCPINFO_S *)pstPppInfo->pstIpcpInfo;

    /*1、ipv6链路和ipv4链路同时DOWN掉,通知用户退网；
        2、重协商也会进入该分支
        3、终端发起退网也会进入该分支*/




    PPP_DBG_OK_CNT(PPP_PHOK_957);

    /*添加对于定时器的保护*/
    if (pstIpcpInfo->stFsm.ulTimeOutID)
    {
        (VOID)VOS_StopRelTimer(&(pstIpcpInfo->stFsm.ulTimeOutID));
        pstIpcpInfo->stFsm.ulTimeOutID = 0;
    }

    /*删除协商链等待定时器*/
    if (PPP_STATE_SUCCESS == pstPppInfo->bPppStateFlgV6)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_958);
        (VOID)PPP_NodeDelete(pstPppInfo->ulRPIndex);
    }

    /*删除重协商控制块*/
    if (pstPppInfo->bReNego)
    {
        pstPppInfo->bReNego = 0;

        /*ipcp控制块为空或者v4重协商标记无效则释放控制块*/
        if ((pstPppInfo->pstPppRenegoInfo)&&(!pstPppInfo->bReNegoV6))
        {
            (VOID)PPP_Free(pstPppInfo->pstPppRenegoInfo);
            pstPppInfo->pstPppRenegoInfo = 0;
        }
    }

    if (pstPppInfo->bVjFlag)
    {
        PPP_CompUserNumDel(pstPppInfo, PPP_USERSTAT_VJ);
    }

    /*释放缓存消息内存*/
    if ( VOS_NULL != ((PPPIPCPINFO_S*)(pstPppInfo->pstIpcpInfo))->pucIpv4cpMsg )
    {
        (VOID)PPP_Free(((PPPIPCPINFO_S*)(pstPppInfo->pstIpcpInfo))->pucIpv4cpMsg);
        ((PPPIPCPINFO_S*)(pstPppInfo->pstIpcpInfo))->pucIpv4cpMsg = NULL;
        ((PPPIPCPINFO_S*)(pstPppInfo->pstIpcpInfo))->ulIpv4cpLen = 0;
    }

    pstIpcpInfo->ucUsedFlag = 0;
    pstPppInfo->pstIpcpInfo = NULL;
    pstPppInfo->bPppStateFlg = PPP_STATE_FAIL;
    pstPppInfo->ulPeerIPAddr = 0;
    pstPppInfo->ucV4NcpReleaseCode = 0;

    PPP_DBG_OK_CNT(PPP_PHOK_959);


    /* 对于ipcp重协商失败后，需要判断ipv6cp的状态，如果是open态需要再次设置为success，否则用户下线后会出现失败统计 */
    if ((pstPppInfo->pstIpV6cpInfo)
        && (((PPPIPV6CPINFO_S*)pstPppInfo->pstIpV6cpInfo)->stFsm.ucState == PPP_STATE_OPENED))
    {
        M_SET_NEWPHASE(pstPppInfo, PPP_SNMP_PERF_PHASE_SUCCESS);
        PPP_DBG_OK_CNT(PPP_PHOK_960);
    }

    return;
}


/*****************************************************************************
 函 数 名  : PPP_Core_IpcpV6FinProc
 功能描述  : 单栈删除收到ipv6cp finished事件处理函数
 输入参数  : PPPINFO_S *pstPppInfo
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年1月13日
    作    者   : T62595
    修改内容   : 新生成函数

*****************************************************************************/
VOID PPP_Core_IpcpV6FinProc( PPPINFO_S *pstPppInfo )
{
   PPPIPV6CPINFO_S *pstIpv6cpInfo = NULL ;

   if ((NULL == pstPppInfo->pstLcpInfo) || (NULL == pstPppInfo->pstIpV6cpInfo))
   {
       PPP_DBG_ERR_CNT(PPP_PHERR_350);
       return;
   }

   pstIpv6cpInfo = (PPPIPV6CPINFO_S *)pstPppInfo->pstIpV6cpInfo;

   /*1、ipv6链路和ipv4链路同时DOWN掉,通知用户退网；
     2、重协商也会进入该分支
     3、终端发起退网也会进入该分支*/



   PPP_DBG_OK_CNT(PPP_PHOK_961);

   /*添加对于定时器的保护*/
   if (pstIpv6cpInfo->stFsm.ulTimeOutID)
   {
       (VOID)VOS_StopRelTimer(&(pstIpv6cpInfo->stFsm.ulTimeOutID));
       pstIpv6cpInfo->stFsm.ulTimeOutID = 0;
   }


   /*删除协商链等待定时器*/
   if (PPP_STATE_SUCCESS == pstPppInfo->bPppStateFlg)
   {
       PPP_DBG_OK_CNT(PPP_PHOK_962);
       (VOID)PPP_NodeDelete(pstPppInfo->ulRPIndex);
   }

   /*删除重协商控制块*/
   if (pstPppInfo->bReNegoV6)
   {
       pstPppInfo->bReNegoV6 = 0;

       /*ipcp控制块为空或者v4重协商标记无效则释放控制块*/
       if ((pstPppInfo->pstPppRenegoInfo)&&(!pstPppInfo->bReNego))
       {
           (VOID)PPP_Free(pstPppInfo->pstPppRenegoInfo);
           pstPppInfo->pstPppRenegoInfo = 0;
       }
   }

   /* 释放缓存消息内存 */
   if ( VOS_NULL != ((PPPIPV6CPINFO_S*)pstPppInfo->pstIpV6cpInfo)->pucIpv6cpMsg )
   {
       (VOID)PPP_Free(((PPPIPV6CPINFO_S*)pstPppInfo->pstIpV6cpInfo)->pucIpv6cpMsg);
       ((PPPIPV6CPINFO_S*)pstPppInfo->pstIpV6cpInfo)->pucIpv6cpMsg = NULL;
       ((PPPIPV6CPINFO_S*)pstPppInfo->pstIpV6cpInfo)->ulIpv6cpLen = 0;
   }

   if (0 != pstIpv6cpInfo->ucUsedFlag)
   {
       pstIpv6cpInfo->ucUsedFlag = 0;
       PPP_DBG_OK_CNT(PPP_PHOK_963);
   }

   pstPppInfo->pstIpV6cpInfo = NULL;
   pstPppInfo->bPppStateFlgV6 = PPP_STATE_FAIL;
   pstPppInfo->ucV6NcpReleaseCode = 0;
   VOS_MemSet((void *)pstPppInfo->usPeerIPv6Addr,0,IPV6_ADDR_LEN);

   PPP_DBG_OK_CNT(PPP_PHOK_964);
   return;
}





/*****************************************************************************
 函 数 名  : PPP_Core_ReceivePacketFromShell
 功能描述  : PPP内核收到外壳发来的协商报文
 输入参数  : PPPINFO_S *pstPppInfo
             UCHAR*     pHead
             UCHAR*     pPacket
             VOS_UINT32      ulLen
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月30日
    作    者   : luofang
    修改内容   : 新生成函数

*****************************************************************************/
VOID PPP_Core_ReceivePacketFromShell_TestStub(PPPINFO_S *pstPppInfo,
                                     UCHAR*     pHead,
                                     UCHAR*     pPacket,
                                     VOS_UINT32      ulLen)
{
    PPPLCPINFO_S *pstLcpInfo = NULL;
    VOS_UINT32 ulOffset;
    VOS_UINT16 usProtocol;
    UCHAR ucCode = 0;
    VOS_UINT32 ulUserType = 0;
    PPPC_INFO_LOG("\r\n---Into PPP_Core_ReceivePacketFromShell---\r\n");

    /* 报文情况 */

    /*
     |--------PPP Head(bytes) -------|
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |  ff   |  03   |    protocol   |  Data ...
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |
    pPacket
     */
    if ((VOS_NULL_PTR == pPacket) || (VOS_NULL_PTR == pHead) || (VOS_NULL_PTR == pstPppInfo))
    {
        return;
    }

    /* 获得协议号,并返回PPP头长度 */
    ulOffset = PPP_Core_GetProtocol(pstPppInfo, (UCHAR*)pPacket, (VOS_UINT16*) &usProtocol);
    if ((ulOffset == 0) || (ulLen < ulOffset))
    {
        /* 提示:错误的报文 */
        PPP_DBG_ERR_CNT(PPP_PHERR_351);
        /* 输出错误信息 added by gxf 20030528 */
        PPP_Debug_CoreEvent(pstPppInfo, PPP_LOG_ERROR, "Receive Bad Packet!!");
        return;
    }

    /* 移动指针 */
    pPacket += ulOffset;
    ulLen -= ulOffset;
    ucCode = *pPacket;
    /* 报文情况 */

    /*
     |--------PPP Head(bytes) -------|
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |  ff   |  03   |    protocol   |  Data ...
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |---------- ulOffset -----------|
                                    pPacket
     */

    /* 消息跟踪 */
    PPP_OmMsgTrc(pstPppInfo->ulRPIndex, usProtocol, pPacket, ulLen, PPP_TRACE_IN, 0, &(pstPppInfo->stIMSI), pstPppInfo->bEhrpdUser);


    switch (usProtocol)
    {
        case PPP_LCP:
            PPP_DBG_OK_CNT(PPP_PHOK_965);

            /* 输出调试信息 */
            if (VRP_YES == pstPppInfo->stPppDebugInfo.bDebug_Lcp_Packet)
            {
                PPP_Debug_FsmPacket(pstPppInfo,
                                    pPacket,
                                    ulLen,
                                    usProtocol,
                                    (UCHAR)PPP_DEBUG_PACKET_IN);
            }

            /* 如果没有创建LCP控制块,则创建之 */
            if (NULL == pstPppInfo->pstLcpInfo)
            {
                PPP_GETLCPADDR(pstPppInfo->pstLcpInfo, pstPppInfo->ulRPIndex);
                if (pstPppInfo->pstLcpInfo == NULL)
                {
                    PPP_Debug_CoreEvent(pstPppInfo, PPP_LOG_ERROR, "Fail:Malloc LCP CB Failed");
                    return;
                }

                VOS_MemSet(pstPppInfo->pstLcpInfo, 0, sizeof(PPPLCPINFO_S));
                PPP_LCP_Init(pstPppInfo);/*luofeng37050notify 协商参数*/
            }

            pstLcpInfo = (PPPLCPINFO_S*)pstPppInfo->pstLcpInfo;

            /* ISLUP事件只在LCP状态为Initial或Starting时才有效 */
            if ((pstLcpInfo->stFsm.ucState == (UCHAR)PPP_STATE_INITIAL)
                || (pstLcpInfo->stFsm.ucState == (UCHAR)PPP_STATE_STARTING))
            {
                PPP_Core_EstablishPhase(pstPppInfo);
            }

            if (pstPppInfo->pstLcpInfo)
            {
                PPP_LCP_ReceivePacket(pstPppInfo->pstLcpInfo, pHead, pPacket, ulLen);
                PPP_DBG_OK_CNT(PPP_PHOK_966);
                return;
            }

            break;

        case PPP_IPCP:
            PPP_DBG_OK_CNT(PPP_PHOK_967);

            /* 输出调试信息 */
            if (pstPppInfo->stPppDebugInfo.bDebug_Ipcp_Packet == VRP_YES)
            {
                PPP_Debug_FsmPacket(pstPppInfo,
                                    pPacket,
                                    ulLen,
                                    usProtocol,
                                    (UCHAR)PPP_DEBUG_PACKET_IN);
            }

            /* BEGIN: Added for PN:PDSN融合 by wangyong 00138171, 2013/1/19 */
            if (VOS_TRUE == pstPppInfo->bEhrpdUser)
            {
                /* 输出debug信息 */
                PPP_DBG_ERR_CNT(PPP_PHERR_352);
                break;
            }
            /* END:   Added for PN:PDSN融合 by wangyong 00138171, 2013/1/19 */

            /* 判断是否为网络协商阶段*/
            if (pstPppInfo->usPhase != (VOS_UINT16)PPP_PHASE_NETWORK)
            {
                /* 输出debug信息 */
                PPP_DBG_ERR_CNT(PPP_PHERR_353);
                return;
            }

            /* 简单IP未获取到IP地址时收到的第一条请求消息 */
            if (CONFREQ == ucCode)
            {
                if ((NULL == pstPppInfo->pstIpcpInfo)
                    && (0 == pstPppInfo->ulPeerIPAddr && PPP_USERTYPE_MIP != pstPppInfo->bIPTech))
                {
                    /*解析用户类型*/
                    if(VOS_OK != PPP_GetUserTypeByIpv4cpReq(pstPppInfo, pPacket, ulLen, &ulUserType))
                    {
                        PPP_DBG_ERR_CNT(PPP_PHERR_354);
                        /*回复Reject消息*/
                        break;
                    }

                    /* PMIPv6 PDN需要从缓存消息中获取IP地址，先创建IPV4控制块、缓存消息 */
                    if(VOS_OK != PPP_CopyIpv4cpMsg(pstPppInfo, pHead, pPacket, ulLen))
                    {
                         PPP_ClearCB_IPCP(pstPppInfo->pstIpcpInfo);
                         pstPppInfo->pstIpcpInfo = NULL;
                         PPP_DBG_ERR_CNT(PPP_PHERR_355);
                         break;
                    }

#if 0
                    /* 通知PDN(携带用户类型，栈类型,RpIndex) */
                    if(VOS_OK != PDN_PppStartSubNet(pstPppInfo->ulRPIndex, ulUserType))
                    {
                         PPP_DebugOut(MID_PPPC,PPP_DEBUG_INFO,"\r\n Call PDN_PppStartSubNet fail !");
                         /*清资源，退网*/
                         PPP_ClearCB_IPCP(pstPppInfo->pstIpcpInfo);
                         pstPppInfo->pstIpcpInfo = NULL;
                         PPP_DBG_ERR_CNT(PPP_PHERR_356);
                         /* 回复Reject消息 */
                         break;
                    }
#endif
                    pstPppInfo->ucIpCapability |= PDSN_PPP_IPTYE_IPV4;

                    return;
                }

                /*有IPV4控制块并且 IPCP控制块状态机状态*/
                if(pstPppInfo->pstIpcpInfo && (PPP_STATE_INITIAL== ((PPPIPCPINFO_S*)pstPppInfo->pstIpcpInfo)->stFsm.ucState))
                {
                    /*跟新缓存消息*/
                    if(VOS_OK != PPP_CopyIpv4cpMsg(pstPppInfo, pHead, pPacket, ulLen))
                    {
                         PPP_DBG_ERR_CNT(PPP_PHERR_357);
                         break;
                    }
                    PPP_DBG_OK_CNT(PPP_PHOK_968);
                    return;
                }
            }

            /*否则进入正常协商流程*/
            PPP_IPCP_ReceivePacket(pstPppInfo->pstIpcpInfo, pHead, pPacket, ulLen);
            PPP_DBG_OK_CNT(PPP_PHOK_969);
            return ;

        case PPP_IPV6CP:
            /* BEGIN: Added for PN:PDSN融合 by wangyong 00138171, 2013/1/19 */
            /* ehrpd用户直接break，到后面回protocol rej消息 */
            if (VOS_TRUE == pstPppInfo->bEhrpdUser)
            {
                /* 输出debug信息 */
                PPP_DBG_ERR_CNT(PPP_PHERR_358);
                break;
            }
            /* END:   Added for PN:PDSN融合 by wangyong 00138171, 2013/1/19 */

            /* 判断阶段状态是否正确 */
            if (pstPppInfo->usPhase != (VOS_UINT16)PPP_PHASE_NETWORK)
            {
                /* 输出debug信息 */
                PPP_DBG_ERR_CNT(PPP_PHERR_359);
                return;
            }

            if (CONFREQ == ucCode)
            {
                if ((NULL == pstPppInfo->pstIpV6cpInfo)
                    && (VOS_OK != PPP_ipv6_addr_check(pstPppInfo->usPeerIPv6Addr)))
                {
#if 0
                    /* 通知PDN(携带用户类型，栈类型,RpIndex) */
                    if(VOS_OK != PDN_PppStartSubNet(pstPppInfo->ulRPIndex, E_FSM_ID_SIPV6))
                    {
                         PPP_DBG_ERR_CNT(PPP_PHERR_360);
                         /*清资源，退网*/
                         /* 回复Reject消息 */
                         break;
                    }
#endif
                    PPP_SET_IPTECH(pstPppInfo, PPP_USERTYPE_SIP);

                    /*创建IPV6控制块、缓存消息 */
                    if (VOS_OK != PPP_CopyIpv6cpMsg(pstPppInfo, pHead, pPacket, ulLen))
                    {
                         PPP_DBG_ERR_CNT(PPP_PHERR_361);
                         PPP_ClearCB_IPV6CP(pstPppInfo->pstIpV6cpInfo);
                         pstPppInfo->pstIpV6cpInfo = NULL;
                         /* 回复Reject消息 */
                         break;
                    }
                    pstPppInfo->ucIpCapability |= PDSN_PPP_IPTYE_IPV6;
                    return;
                }

                if (pstPppInfo->pstIpV6cpInfo && (PPP_STATE_INITIAL== ((PPPIPV6CPINFO_S*)pstPppInfo->pstIpV6cpInfo)->stFsm.ucState))
                {
                   /*更新缓存消息*/
                    if(VOS_OK != PPP_CopyIpv6cpMsg(pstPppInfo, pHead, pPacket, ulLen))
                    {
                         PPP_DBG_ERR_CNT(PPP_PHERR_362);
                         /* 回复Reject消息 */
                         break;
                    }
                    PPP_DBG_OK_CNT(PPP_PHOK_970);
                    return;
                }
            }

            /*否则进入正常协商流程*/
            PPP_IPV6CP_Pactket_Proc(pstPppInfo, pHead, pPacket, ulLen);
            return;
     /* BEGIN: Added for PN:PDSN融合 by wangyong 00138171, 2013/1/19 */
     case PPP_VSNCP:
#if 0
            ulRet = USM_GetVsncpNegoFlag(pstPppInfo->ulRPIndex);
            if (ulRet != VOS_OK)
            {
                PPP_DebugOut(MID_PPPC,PPP_DEBUG_INFO,
                             "\r\n PPP_Core_ReceivePacketFromShell  ulRet = %u",
                             ulRet);
                PPP_DBG_ERR_CNT(PPP_PHERR_363);
                return;
            }
#endif
            if (pstPppInfo->bEhrpdUser != VOS_TRUE)
            {
                /* 输出debug信息 */
                PPP_DBG_ERR_CNT(PPP_PHERR_364);
                break;
            }

            /*否则进入正常协商流程*/
            PPP_VSNCP_PactketProc(pstPppInfo, pHead, pPacket, ulLen, ucCode);
            return;
     /* END:   Added for PN:PDSN融合 by wangyong 00138171, 2013/1/19 */
 #if (VRP_MODULE_LINK_PPP_CCP == VRP_YES)
        case PPP_CCP:

            /* 输出调试信息 */
            if (pstPppInfo->stPppDebugInfo.bDebug_Ccp_Packet == VRP_YES)
            {
                PPP_Debug_FsmPacket(pstPppInfo,
                                    pPacket,
                                    ulLen,
                                    usProtocol,
                                    (UCHAR)PPP_DEBUG_PACKET_IN);
            }
            /* BEGIN: Added for PN:PDSN融合 by wangyong 00138171, 2013/1/19 */
            if (VOS_TRUE == pstPppInfo->bEhrpdUser)
            {
                /* 输出debug信息 */
                PPP_DBG_ERR_CNT(PPP_PHERR_365);
                break;
            }
            /* END:   Added for PN:PDSN融合 by wangyong 00138171, 2013/1/19 */

            /* 如果是因为协议未到Network阶段pstCcpInfo才为0，
                 则抛弃报文，但不发protocol reject。
                 参见RFC1661。
             */
            if (pstPppInfo->usPhase != (VOS_UINT16)PPP_PHASE_NETWORK)
            {
                PPP_DBG_ERR_CNT(PPP_PHERR_366);
                return;
            }

            if (pstPppInfo->pstCcpInfo)
            {
                PPP_DBG_OK_CNT(PPP_PHOK_971);
                PPP_CCP_ReceivePacket(pstPppInfo->pstCcpInfo, pHead, pPacket, ulLen, pstPppInfo->ulRPIndex);/* Modified by liutao 38563 at 2004-09-22 V800R002 for PPP压缩移植 */
                return;
            }

            /* BEGIN: M by h50774 for CR20100825049,修改为CCP可支持被动协商, 2010/8/26 */
            /*lint -e746*/
            if(VOS_OK == PPP_CheckCcpLimit())
            /*lint +e746*/
            {
                PPP_DBG_OK_CNT(PPP_PHOK_972);
                PPP_GETCCPADDR(pstPppInfo->pstCcpInfo, pstPppInfo->ulRPIndex);
                if (pstPppInfo->pstCcpInfo)
                {
                    PPP_DBG_OK_CNT(PPP_PHOK_973);
                    PPP_MemSet(pstPppInfo->pstCcpInfo, 0, sizeof(PPP_CCP_INFO_S));

                    /* 初始化CCP控制块 */
                    PPP_CCP_init(pstPppInfo);

                    /*设置CCP超时定时器*/
                    (VOS_VOID)VOS_StartRelTimer((HTIMER)&(((PPP_CCP_INFO_S*)((PPPINFO_S*)pstPppInfo)->pstCcpInfo)->ulCcpTimeoutID),
                                                MID_PPPC,
                                                ((PPP_CCP_INFO_S*)((PPPINFO_S*)pstPppInfo)->pstCcpInfo)->ulTimeOutTime,
                                                pstPppInfo->ulRPIndex,
                                                PPPC_CCP_TIMEOUT_TIMER,
                                                VOS_TIMER_LOOP,
                                                VOS_TIMER_PRECISION_0);

                    /* 向CCP发送消息,触发CCP开始协商 */
                    PPP_CCP_ReceiveEventFromCore(pstPppInfo->pstCcpInfo, (VOS_UINT32)PPP_EVENT_FSM_OPEN, NULL );
                    PPP_CCP_ReceiveEventFromCore(pstPppInfo->pstCcpInfo, (VOS_UINT32)PPP_EVENT_FSM_UP, NULL );
                    PPP_CCP_ReceivePacket(pstPppInfo->pstCcpInfo, pHead, pPacket, ulLen, pstPppInfo->ulRPIndex);
                    return;
                }
            }
            else
            {
                PPP_DBG_ERR_CNT(PPP_PHERR_367);
                /*写日志*/
                PPP_Debug_CoreEvent(pstPppInfo, PPP_LOG_WARNING,
                                    " PPP_Core_ReceivePacketFromShell:  g_ucPppCcpSwitch=0 or no license , please confirm it");

                PPP_Core_ReceiveUnknownProtocol(pstPppInfo, pHead, pPacket, ulLen, usProtocol, ucCode);
                return;
            }
            /* End: M by h50774 for CR20100825049,修改为CCP可支持被动协商, 2010/8/26 */

            /* 否则到下面执行PPP_Core_ReceiveUnknownProtocol */

            break;
 #endif
        case PPP_EAP:
#if 0
            if (pstPppInfo->bEhrpdUser != VOS_TRUE)
            {
                /* 输出debug信息 */
                PPP_DBG_ERR_CNT(PPP_PHERR_368);
                break;
            }
            PPP_DBG_OK_CNT(PPP_PHOK_974);
            if (pstPppInfo->pstEapInfo)
            {
                PPPC_EAP_ReceivePacket(pstPppInfo, pHead, pPacket, ulLen);
                PPP_DBG_OK_CNT(PPP_PHOK_975);
                return;
            }

            /* 如果是因为协议未到Authenticate阶段pstChapInfo才为0，
             则抛弃报文，但不发protocol reject。
             参见RFC1661。
            */
            if (pstPppInfo->usPhase != (VOS_UINT16)PPP_PHASE_AUTHENTICATE)
            {
                PPP_DBG_ERR_CNT(PPP_PHERR_369);
                return;
            }
#endif
            break;

        case PPP_PAP:

            if (VOS_TRUE == pstPppInfo->bEhrpdUser)
            {
                /* 输出debug信息 */
                PPP_DBG_ERR_CNT(PPP_PHERR_370);
                break;
            }

            PPP_DBG_OK_CNT(PPP_PHOK_976);
            if (pstPppInfo->pstPapInfo)
            {
                PPP_PAP_ReceivePacket(pstPppInfo, pHead, pPacket, ulLen);
                PPP_DBG_OK_CNT(PPP_PHOK_977);
                return;
            }

            /* 如果是因为协议未到Authenticate阶段pstPapInfo才为0，
               则抛弃报文，但不发protocol reject。
               参见RFC1661。
             */
            if (pstPppInfo->usPhase != (VOS_UINT16)PPP_PHASE_AUTHENTICATE)
            {
                PPP_DBG_ERR_CNT(PPP_PHERR_371);
                return;
            }

            /* 否则到下面执行PPP_Core_ReceiveUnknownProtocol */

            break;

        case PPP_CHAP:
            PPP_DBG_OK_CNT(PPP_PHOK_978);

            if (VOS_TRUE == pstPppInfo->bEhrpdUser)
            {
                /* 输出debug信息 */
                PPP_DBG_ERR_CNT(PPP_PHERR_372);
                break;
            }

            if (pstPppInfo->pstChapInfo)
            {
                PPP_CHAP_ReceivePacket(pstPppInfo, pHead, pPacket, ulLen);
                PPP_DBG_OK_CNT(PPP_PHOK_979);
                return;
            }

            /* 如果是因为协议未到Authenticate阶段pstChapInfo才为0，
               则抛弃报文，但不发protocol reject。
               参见RFC1661。
             */
            if (pstPppInfo->usPhase != (VOS_UINT16)PPP_PHASE_AUTHENTICATE)
            {
                PPP_DBG_ERR_CNT(PPP_PHERR_373);
                return;
            }

            /* 否则到下面执行PPP_Core_ReceiveUnknownProtocol */

            break;

        default:
            PPP_DBG_ERR_CNT(PPP_PHERR_374);
            break;
    }

    PPP_Core_ReceiveUnknownProtocol(pstPppInfo, pHead, pPacket, ulLen, usProtocol, ucCode);

    return;
}



/*****************************************************************************
 函 数 名  : PDN_PppStartSubNet
 功能描述  : PPP收到第一条IPCP请求消息后，启动网络子状态机
 输入参数  : VOS_UINT32 ulRpIndex
             VOS_UINT32 ulFsmType
 输出参数  :
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月22日
    作    者   : h50774
    修改内容   : 新生成函数

*****************************************************************************/
VOID PPP_TEST_TIMESTAMP(VOS_UINT32 ulStart, VOS_UINT32 ulEnd, VOS_UINT32 ulRpIndex)
{
    VOS_UINT32 ulRet = VOS_OK;
    SDB_PDSN_RP_CONTEXT_S *pstRpContext = VOS_NULL;
    PDN_CONTEXT_S *pstPdnContext = VOS_NULL;

    ulRet = SDB_GetRpContextByIndex(ulRpIndex, (VOS_VOID **)&pstRpContext);
    if ((VOS_OK != ulRet) || (VOS_NULL == pstRpContext))
    {
        return;
    }

    ulRet = SDB_GetPdnContextByIndex((VOS_UINT32)pstRpContext->ausPdnIndexArray[0], (VOS_VOID **)&pstPdnContext);
    if ((VOS_OK != ulRet) || (VOS_NULL == pstPdnContext))
    {
        return;
    }

    if (E_PDNTYPE_PMIPV6 == pstPdnContext->ucPdnType)
    {
        if ((ulEnd -  ulStart) > g_ulPppDBGStatisc[PPP_PHOK_1458])
        {
            g_ulPppDBGStatisc[PPP_PHOK_1458] = (ulEnd -  ulStart);
        }
    }

    return;
}


/*****************************************************************************
 函 数 名  : PPP_Core_ReceivePacketFromShell
 功能描述  : PPP内核收到外壳发来的协商报文
 输入参数  : PPPINFO_S *pstPppInfo
             UCHAR*     pHead
             UCHAR*     pPacket
             VOS_UINT32      ulLen
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月30日
    作    者   : luofang
    修改内容   : 新生成函数

*****************************************************************************/
VOID PPP_Core_ReceivePacketFromShell(PPPINFO_S *pstPppInfo,
                                     VOS_UINT8*     pHead,
                                     VOS_UINT8*     pPacket,
                                     VOS_UINT32      ulLen)
{
    VOS_UINT32 ulOffset;
    VOS_UINT16 usProtocol;
    UCHAR ucCode = 0;
    VOS_UINT32 ulUserType = 0;
    VOS_UINT32 ulTimeStamp = 0;
    VOS_UINT32 ulTimeStamp1 = 0;

    PPPC_INFO_LOG("\r\n---Into PPP_Core_ReceivePacketFromShell---\r\n");

    if ( VOS_TRUE == g_ulHsgwA10TestDbgFlg )
    {
         PPP_Core_ReceivePacketFromShell_TestStub(pstPppInfo, pHead, pPacket, ulLen);
         return;
    }

    /* 报文情况 */

    /*
     |--------PPP Head(bytes) -------|
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |  ff   |  03   |    protocol   |  Data ...
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |
    pPacket
     */
    if ((VOS_NULL_PTR == pPacket) || (VOS_NULL_PTR == pHead) || (VOS_NULL_PTR == pstPppInfo))
    {
        return;
    }

    /* 获得协议号,并返回PPP头长度 */
    ulOffset = PPP_Core_GetProtocol(pstPppInfo, (UCHAR*)pPacket, (VOS_UINT16*) &usProtocol);
    if ((ulOffset == 0) || (ulLen < ulOffset))
    {
        /* 提示:错误的报文 */
        PPP_DBG_ERR_CNT(PPP_PHERR_375);
        /* 输出错误信息 added by gxf 20030528 */
        PPP_Debug_CoreEvent(pstPppInfo, PPP_LOG_ERROR, "Receive Bad Packet!!");
        return;
    }

    /* 移动指针 */
    pPacket += ulOffset;
    ulLen -= ulOffset;
    ucCode = *pPacket;
    /* 报文情况 */

    /*
     |--------PPP Head(bytes) -------|
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |  ff   |  03   |    protocol   |  Data ...
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |---------- ulOffset -----------|
                                    pPacket
     */

    /* 消息跟踪 */
    PPP_OmMsgTrc(pstPppInfo->ulRPIndex, usProtocol, pPacket, ulLen, PPP_TRACE_IN, 0, &(pstPppInfo->stIMSI), pstPppInfo->bEhrpdUser);


    switch (usProtocol)
    {
        case PPP_LCP:
            PPP_DBG_OK_CNT(PPP_PHOK_980);

            PPPC_INFO_LOG("\r\n Recieve PPP_LCP packet \r\n");

            /* 输出调试信息 */
            if (VRP_YES == pstPppInfo->stPppDebugInfo.bDebug_Lcp_Packet)
            {
                PPP_Debug_FsmPacket(pstPppInfo,
                                    pPacket,
                                    ulLen,
                                    usProtocol,
                                    (UCHAR)PPP_DEBUG_PACKET_IN);
            }

            if (ulLen > PPP_LCP_NEGO_PACKET_MAX_LEN)
            {
                PPP_DBG_ERR_CNT(PPP_PHERR_376);
                PPPC_WARNING_LOG1("\r\n LCP packet len is over 200[%u]!", ulLen);
                return;
            }

            if (pstPppInfo->pstLcpInfo)
            {
                PPP_LCP_ReceivePacket(pstPppInfo->pstLcpInfo, pHead, pPacket, ulLen);
                PPP_DBG_OK_CNT(PPP_PHOK_981);
                return;
            }

            break;

        case PPP_IPCP:
            PPP_DBG_OK_CNT(PPP_PHOK_982);

            /* 输出调试信息 */
            if (pstPppInfo->stPppDebugInfo.bDebug_Ipcp_Packet == VRP_YES)
            {
                PPP_Debug_FsmPacket(pstPppInfo,
                                    pPacket,
                                    ulLen,
                                    usProtocol,
                                    (UCHAR)PPP_DEBUG_PACKET_IN);
            }

            /* BEGIN: Added for PN:PDSN融合 by wangyong 00138171, 2013/1/19 */
            if (VOS_TRUE == pstPppInfo->bEhrpdUser)
            {
                /* 输出debug信息 */
                HSGW_EmsTraceByRpIndex(pstPppInfo->ulRPIndex, HSGW_EMS_MODULE_PPP, EMS_PPP_0);
                PPP_DBG_ERR_CNT(PPP_PHERR_377);
                break;
            }
            /* END:   Added for PN:PDSN融合 by wangyong 00138171, 2013/1/19 */

            /* 判断是否为网络协商阶段*/
            if (pstPppInfo->usPhase != (VOS_UINT16)PPP_PHASE_NETWORK)
            {
                /* 输出debug信息 */
                PPP_DBG_ERR_CNT(PPP_PHERR_378);
                return;
            }

            /* 简单IP未获取到IP地址时收到的第一条请求消息 */
            if (CONFREQ == ucCode)
            {
                if ((NULL == pstPppInfo->pstIpcpInfo)
                    && (0 == pstPppInfo->ulPeerIPAddr && PPP_USERTYPE_MIP != pstPppInfo->bIPTech))
                {
                    /*解析用户类型*/
                    if(VOS_OK != PPP_GetUserTypeByIpv4cpReq(pstPppInfo, pPacket, ulLen, &ulUserType))
                    {
                        PPP_DBG_ERR_CNT(PPP_PHERR_379);
                        /*回复Reject消息*/
                        break;
                    }

                    /* PMIPv6 PDN需要从缓存消息中获取IP地址，先创建IPV4控制块、缓存消息 */
                    if(VOS_OK != PPP_CopyIpv4cpMsg(pstPppInfo, pHead, pPacket, ulLen))
                    {
                         PPP_ClearCB_IPCP(pstPppInfo->pstIpcpInfo);
                         pstPppInfo->pstIpcpInfo = NULL;
                         PPP_DBG_ERR_CNT(PPP_PHERR_380);
                         break;
                    }
                    if (VOS_TRUE == g_ulPppVsncpGetPCO)
                    {
                        ulTimeStamp = (VOS_UINT32)VOS_GetTick();
                    }
#if 0
                    /* 通知PDN(携带用户类型，栈类型,RpIndex) */
                    if(VOS_OK != PDN_PppStartSubNet(pstPppInfo->ulRPIndex, ulUserType))
                    {
                         PPP_DebugOut(MID_PPPC,PPP_DEBUG_INFO,"\r\n Call PDN_PppStartSubNet fail !");
                         /*清资源，退网*/
                         PPP_ClearCB_IPCP(pstPppInfo->pstIpcpInfo);
                         pstPppInfo->pstIpcpInfo = NULL;
                         PPP_DBG_ERR_CNT(PPP_PHERR_381);
                         /* 回复Reject消息 */
                         break;
                    }
#endif
                    if (VOS_TRUE == g_ulPppVsncpGetPCO)
                    {
                        ulTimeStamp1 = (VOS_UINT32)VOS_GetTick();
                        PPP_TEST_TIMESTAMP(ulTimeStamp, ulTimeStamp1, pstPppInfo->ulRPIndex);
                    }

                    pstPppInfo->ucIpCapability |= PDSN_PPP_IPTYE_IPV4;

                    return;
                }

                /*有IPV4控制块并且 IPCP控制块状态机状态*/
                if(pstPppInfo->pstIpcpInfo && (PPP_STATE_INITIAL== ((PPPIPCPINFO_S*)pstPppInfo->pstIpcpInfo)->stFsm.ucState))
                {
                    /*跟新缓存消息*/
                    if(VOS_OK != PPP_CopyIpv4cpMsg(pstPppInfo, pHead, pPacket, ulLen))
                    {
                         PPP_DBG_ERR_CNT(PPP_PHERR_382);
                         break;
                    }
                    PPP_DBG_OK_CNT(PPP_PHOK_983);
                    return;
                }
            }

            /*否则进入正常协商流程*/
            PPP_IPCP_ReceivePacket(pstPppInfo->pstIpcpInfo, pHead, pPacket, ulLen);
            PPP_DBG_OK_CNT(PPP_PHOK_984);
            return ;

        case PPP_IPV6CP:

            /* BEGIN: Added for PN:PDSN融合 by wangyong 00138171, 2013/1/19 */
            /* ehrpd用户直接break，到后面回protocol rej消息 */
            if (VOS_TRUE == pstPppInfo->bEhrpdUser)
            {
                /* 输出debug信息 */
                HSGW_EmsTraceByRpIndex(pstPppInfo->ulRPIndex, HSGW_EMS_MODULE_PPP, EMS_PPP_1);
                PPP_DBG_ERR_CNT(PPP_PHERR_383);
                break;
            }
            /* END:   Added for PN:PDSN融合 by wangyong 00138171, 2013/1/19 */

            /* 判断阶段状态是否正确 */
            if (pstPppInfo->usPhase != (VOS_UINT16)PPP_PHASE_NETWORK)
            {
                /* 输出debug信息 */
                PPP_DBG_ERR_CNT(PPP_PHERR_384);
                return;
            }

            if (CONFREQ == ucCode)
            {
                if ((NULL == pstPppInfo->pstIpV6cpInfo)
                    && (VOS_OK != PPP_ipv6_addr_check(pstPppInfo->usPeerIPv6Addr)))
                {
#if 0
                    /* 通知PDN(携带用户类型，栈类型,RpIndex) */
                    if(VOS_OK != PDN_PppStartSubNet(pstPppInfo->ulRPIndex, E_FSM_ID_SIPV6))
                    {
                         PPP_DBG_ERR_CNT(PPP_PHERR_385);
                         /*清资源，退网*/
                         /* 回复Reject消息 */
                         break;
                    }
#endif
                    PPP_SET_IPTECH(pstPppInfo, PPP_USERTYPE_SIP);

                    /*创建IPV6控制块、缓存消息 */
                    if (VOS_OK != PPP_CopyIpv6cpMsg(pstPppInfo, pHead, pPacket, ulLen))
                    {
                         PPP_DBG_ERR_CNT(PPP_PHERR_386);
                         PPP_ClearCB_IPV6CP(pstPppInfo->pstIpV6cpInfo);
                         pstPppInfo->pstIpV6cpInfo = NULL;
                         /* 回复Reject消息 */
                         break;
                    }
                    pstPppInfo->ucIpCapability |= PDSN_PPP_IPTYE_IPV6;
                    return;
                }

                if (pstPppInfo->pstIpV6cpInfo && (PPP_STATE_INITIAL== ((PPPIPV6CPINFO_S*)pstPppInfo->pstIpV6cpInfo)->stFsm.ucState))
                {
                   /*更新缓存消息*/
                    if(VOS_OK != PPP_CopyIpv6cpMsg(pstPppInfo, pHead, pPacket, ulLen))
                    {
                         PPP_DBG_ERR_CNT(PPP_PHERR_387);
                         /* 回复Reject消息 */
                         break;
                    }
                    PPP_DBG_OK_CNT(PPP_PHOK_985);
                    return;
                }
            }

            /*否则进入正常协商流程*/
            PPP_IPV6CP_Pactket_Proc(pstPppInfo, pHead, pPacket, ulLen);
            return;
     /* BEGIN: Added for PN:PDSN融合 by wangyong 00138171, 2013/1/19 */
     case PPP_VSNCP:

            if (pstPppInfo->bEhrpdUser != VOS_TRUE)
            {
                break;
            }
#if 0
            ulRet = USM_GetVsncpNegoFlag(pstPppInfo->ulRPIndex);
            if (ulRet != EHRPD_VSNCP_PRO_OK)
            {
                if (EHRPD_VSNCP_PRO_COPY == ulRet)
                {
                    (VOID)PPP_CopyVsncpReqMsg(pstPppInfo, pHead, pPacket, ulLen, ucCode);
                }
                PPP_DebugOut(MID_PPPC,PPP_DEBUG_INFO,
                             "\r\n PPP_Core_ReceivePacketFromShell ulRet = %u",
                             ulRet);
                PPP_DBG_ERR_CNT(PPP_PHERR_388);
                return;
            }
#endif
            /*否则进入正常协商流程*/
            PPP_VSNCP_PactketProc(pstPppInfo, pHead, pPacket, ulLen, ucCode);
            return;
     /* END:   Added for PN:PDSN融合 by wangyong 00138171, 2013/1/19 */
 #if (VRP_MODULE_LINK_PPP_CCP == VRP_YES)
        case PPP_CCP:

            /* 输出调试信息 */
            if (pstPppInfo->stPppDebugInfo.bDebug_Ccp_Packet == VRP_YES)
            {
                PPP_Debug_FsmPacket(pstPppInfo,
                                    pPacket,
                                    ulLen,
                                    usProtocol,
                                    (UCHAR)PPP_DEBUG_PACKET_IN);
            }
            /* BEGIN: Added for PN:PDSN融合 by wangyong 00138171, 2013/1/19 */
            if (VOS_TRUE == pstPppInfo->bEhrpdUser)
            {
                /* 输出debug信息 */
                HSGW_EmsTraceByRpIndex(pstPppInfo->ulRPIndex, HSGW_EMS_MODULE_PPP, EMS_PPP_3);
                PPP_DBG_ERR_CNT(PPP_PHERR_390);
                break;
            }
            /* END:   Added for PN:PDSN融合 by wangyong 00138171, 2013/1/19 */

            /* 如果是因为协议未到Network阶段pstCcpInfo才为0，
                 则抛弃报文，但不发protocol reject。
                 参见RFC1661。
             */
            if (pstPppInfo->usPhase != (VOS_UINT16)PPP_PHASE_NETWORK)
            {
                PPP_DBG_ERR_CNT(PPP_PHERR_391);
                return;
            }

            if (pstPppInfo->pstCcpInfo)
            {
                PPP_DBG_OK_CNT(PPP_PHOK_986);
                PPP_CCP_ReceivePacket(pstPppInfo->pstCcpInfo, pHead, pPacket, ulLen, pstPppInfo->ulRPIndex);/* Modified by liutao 38563 at 2004-09-22 V800R002 for PPP压缩移植 */
                return;
            }

            /* BEGIN: M by h50774 for CR20100825049,修改为CCP可支持被动协商, 2010/8/26 */
            /*lint -e746*/
            if(VOS_OK == PPP_CheckCcpLimit())
            /*lint +e746*/
            {
                PPP_DBG_OK_CNT(PPP_PHOK_987);
                PPP_GETCCPADDR(pstPppInfo->pstCcpInfo, pstPppInfo->ulRPIndex);
                if (pstPppInfo->pstCcpInfo)
                {
                    PPP_DBG_OK_CNT(PPP_PHOK_988);
                    PPP_MemSet(pstPppInfo->pstCcpInfo, 0, sizeof(PPP_CCP_INFO_S));

                    /* 初始化CCP控制块 */
                    PPP_CCP_init(pstPppInfo);

                    /*设置CCP超时定时器*/
                    (VOS_VOID)VOS_StartRelTimer((HTIMER)&(((PPP_CCP_INFO_S*)((PPPINFO_S*)pstPppInfo)->pstCcpInfo)->ulCcpTimeoutID),
                                                MID_PPPC,
                                                ((PPP_CCP_INFO_S*)((PPPINFO_S*)pstPppInfo)->pstCcpInfo)->ulTimeOutTime,
                                                pstPppInfo->ulRPIndex,
                                                PPPC_CCP_TIMEOUT_TIMER,
                                                VOS_TIMER_LOOP,
                                                VOS_TIMER_PRECISION_0);

                    /* 向CCP发送消息,触发CCP开始协商 */
                    PPP_CCP_ReceiveEventFromCore(pstPppInfo->pstCcpInfo, (VOS_UINT32)PPP_EVENT_FSM_OPEN, NULL );
                    PPP_CCP_ReceiveEventFromCore(pstPppInfo->pstCcpInfo, (VOS_UINT32)PPP_EVENT_FSM_UP, NULL );
                    PPP_CCP_ReceivePacket(pstPppInfo->pstCcpInfo, pHead, pPacket, ulLen, pstPppInfo->ulRPIndex);
                    return;
                }
            }
            else
            {
                PPP_DBG_ERR_CNT(PPP_PHERR_392);
                /*写日志*/
                PPP_Debug_CoreEvent(pstPppInfo, PPP_LOG_WARNING,
                                    " PPP_Core_ReceivePacketFromShell:  g_ucPppCcpSwitch=0 or no license , please confirm it");

                PPP_Core_ReceiveUnknownProtocol(pstPppInfo, pHead, pPacket, ulLen, usProtocol, ucCode);
                return;
            }
            /* End: M by h50774 for CR20100825049,修改为CCP可支持被动协商, 2010/8/26 */

            /* 否则到下面执行PPP_Core_ReceiveUnknownProtocol */

            break;
 #endif
        case PPP_EAP:

            if (pstPppInfo->bEhrpdUser != VOS_TRUE)
            {
                break;
            }

            if (pstPppInfo->pstEapInfo)
            {
                PPPC_EAP_ReceivePacket(pstPppInfo, pHead, pPacket, ulLen);
                return;
            }

            /* 如果是因为协议未到Authenticate阶段pstChapInfo才为0，
             则抛弃报文，但不发protocol reject。
             参见RFC1661。
            */
            if (pstPppInfo->usPhase != (VOS_UINT16)PPP_PHASE_AUTHENTICATE)
            {
                return;
            }

            break;

        case PPP_PAP:

            if (VOS_TRUE == pstPppInfo->bEhrpdUser)
            {
                HSGW_EmsTraceByRpIndex(pstPppInfo->ulRPIndex, HSGW_EMS_MODULE_PPP, EMS_PPP_6);
                /* 输出debug信息 */
                PPP_DBG_ERR_CNT(PPP_PHERR_395);
                break;
            }

            PPP_DBG_OK_CNT(PPP_PHOK_991);
            if (pstPppInfo->pstPapInfo)
            {
                PPP_PAP_ReceivePacket(pstPppInfo, pHead, pPacket, ulLen);
                PPP_DBG_OK_CNT(PPP_PHOK_992);
                return;
            }

            /* 如果是因为协议未到Authenticate阶段pstPapInfo才为0，
               则抛弃报文，但不发protocol reject。
               参见RFC1661。
             */
            if (pstPppInfo->usPhase != (VOS_UINT16)PPP_PHASE_AUTHENTICATE)
            {
                PPP_DBG_ERR_CNT(PPP_PHERR_396);
                return;
            }

            /* 否则到下面执行PPP_Core_ReceiveUnknownProtocol */

            break;

        case PPP_CHAP:
            PPP_DBG_OK_CNT(PPP_PHOK_993);

            if (VOS_TRUE == pstPppInfo->bEhrpdUser)
            {
                HSGW_EmsTraceByRpIndex(pstPppInfo->ulRPIndex, HSGW_EMS_MODULE_PPP, EMS_PPP_7);
                /* 输出debug信息 */
                PPP_DBG_ERR_CNT(PPP_PHERR_397);
                break;
            }

            if (pstPppInfo->pstChapInfo)
            {
                PPP_CHAP_ReceivePacket(pstPppInfo, pHead, pPacket, ulLen);
                PPP_DBG_OK_CNT(PPP_PHOK_994);
                return;
            }

            /* 如果是因为协议未到Authenticate阶段pstChapInfo才为0，
               则抛弃报文，但不发protocol reject。
               参见RFC1661。
             */
            if (pstPppInfo->usPhase != (VOS_UINT16)PPP_PHASE_AUTHENTICATE)
            {
                PPP_DBG_ERR_CNT(PPP_PHERR_398);
                return;
            }

            /* 否则到下面执行PPP_Core_ReceiveUnknownProtocol */

            break;

        default:
            PPP_DBG_ERR_CNT(PPP_PHERR_399);
            break;
    }

    PPP_Core_ReceiveUnknownProtocol(pstPppInfo, pHead, pPacket, ulLen, usProtocol, ucCode);

    return;
}





/****************************************************************************
* CREATE DATE  ：2000/04/04                                                 *
* CREATED BY   ：Deng Yi Ou                                                 *
* FUNCTION     ：从外壳接收事件的接口函数                                   *
* MODIFY DATE  ：modified by gxf for GGSN80 20030219                        *
* INPUT        ：pstPppInfo:PPP控制块指针                                   *
*                ulCmd:命令字,可以为如下值:                                 *
*                      PPPISLDOWN:底层DOWN                                  *
*                      PPPISLUP:底层UP                                      *
*                      PPPISLRENEGO:底层发起重协商                          *
*                      PPPCHGIPADDR:IP地址改变                              *
*                      PPPCHGIPXADDR:IPX地址改变                            *
*                       PPPL2TPDOWN: L2TP DOWN              zfz 00/07/05        *
*                pPara:事件的参数,一般情况下为NULL                          *
*                      L2TP的LNS端报ISLUP时: 预协商结果                     *
*                      PPPCHGIPADDR时: 新的IP地址                           *
*                      PPPCHGIPXADDR时: 新的IPX地址                         *
* OUTPUT       ：                                                           *
* RETURN       ：NULL                                                       *
* CALLED BY    ：PPP_Shell_ISLIoCtl / PPP_Shell_NiIoCtl                     *
****************************************************************************/
VOID PPP_Core_ReceiveEventFromShell_TestStub(PPPINFO_S *pstPppInfo,
                                    VOS_UINT32      ulCmd,
                                    CHAR *     pPara)
{
    PPPC_INFO_LOG1("\r\n---Into PPP_Core_ReceiveEventFromShell   ulCmd: %d---\r\n", ulCmd);
    if (!pstPppInfo || (ulCmd >= PPPSTCEND))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_400);
        return;
    }

    switch (ulCmd)
    {
        case PPPISLUP:
        {
             pstPppInfo->bLowerIsUp = 1;

            /* 如果没有创建LCP控制块,则创建之 */
            if (NULL == pstPppInfo->pstLcpInfo)
            {
                PPP_GETLCPADDR(pstPppInfo->pstLcpInfo, pstPppInfo->ulRPIndex);
                if (pstPppInfo->pstLcpInfo == NULL)
                {
                    PPP_DBG_ERR_CNT(PPP_PHERR_401);
                    PPP_Debug_CoreEvent(pstPppInfo, PPP_LOG_ERROR, "Fail:Malloc LCP CB Failed");
                    return;
                }

                PPP_MemSet((void *)pstPppInfo->pstLcpInfo, 0, sizeof(PPPLCPINFO_S));
                PPP_LCP_Init(pstPppInfo);/*luofeng37050notify 协商参数*/
            }

            break;
        }
        case PPPISLDOWN:
        {
            pstPppInfo->bLowerIsUp  = 0;
            pstPppInfo->bLoopBacked = 0;

            /* L2TP需要的参数 */
            if (NULL != pstPppInfo->pL2tpPara)
            {
                (VOID)PPP_Free(pstPppInfo->pL2tpPara);
                pstPppInfo->pL2tpPara = NULL;
            }

            /* 通知 LCP Down  */
            if (pstPppInfo->pstLcpInfo)
            {
                PPP_DBG_OK_CNT(PPP_PHOK_995);
                /* 向LCP发送两个消息:LowerDown和Close */
                PPP_LCP_ReceiveEventFromCore(pstPppInfo->pstLcpInfo, (VOS_UINT32)PPP_EVENT_FSM_DOWN, NULL);
                PPP_LCP_ReceiveEventFromCore(pstPppInfo->pstLcpInfo, (VOS_UINT32)PPP_EVENT_FSM_CLOSE, NULL);

                /* 两个消息对应状态机事件的状态转换图:
                 | State
                 |    0         1         2         3         4         5           6         7         8           9
                Events| Initial   Starting  Closed    Stopped   Closing   Stopping   Req-Sent  Ack-Rcvd  Ack-Sent    Opened
                ------+------------------------------------------------------------------------------------------------------
                 Down |    -         -         0       tls/1       0         1          1         1         1         tld/1
                 Close|    0       tlf/0       2         2         4         4      irc,str/4 irc,str/4 irc,str/4 tld,irc,str/4
                 */

                /* 1,发送LowerDown事件,不同状态下动作如下:
                   Opened状态:向上层协议发送LowerDown事件(tld),状态转为Starting
                   Closed/Closing状态:状态转为Initial
                   其他:状态转为Starting

                   2,发送Close事件,初始状态只可能为Initial或Starting.不同状态下动作如下:
                   Starting状态:状态转为Initial;向下层发送Finished事件(tlf).
                   Initial状态:无变化

                   因此,这两个事件发送后会有如下结果:
                   1,最终状态必然会转入Initial
                   2,只要初始状态不是Closed/Closing,则必然会有tlf动作发生
                 */
            }

            if (pstPppInfo->pstPapInfo)
            {
                PPP_PAP_ReceiveEventFromCore(pstPppInfo, PAP_EVENT_LOWERDOWN, NULL);
            }
            if (pstPppInfo->pstChapInfo)
            {
                PPP_CHAP_ReceiveEventFromCore(pstPppInfo, CHAP_EVENT_LOWERDOWN, NULL);
            }

            break;

        }
        case PPPISLRENEGO:/* 重协商 */
        {
            if ((pstPppInfo->pstIpcpInfo)||(pstPppInfo->pstIpV6cpInfo))
            {
                PPP_DBG_OK_CNT(PPP_PHOK_996);
                /* renego后, LCP down, 调用PPP_Core_NotifyNcpDown, IPCP收到down、close事件
                   到达finished状态, 又调用PPP_LCP_NegotiationDown, LCP到达initial状态, 必须
                   发送open、up事件才能再次重协商 */

                /* BEGIN: M by h50774 for 子卡异常情况下重协商, 2010/7/17 */
                /*if (((PPPIPCPINFO_S*)pstPppInfo->pstIpcpInfo)->stFsm.ucState == PPP_STATE_OPENED)*/
                {
                    PPP_LCP_ReceiveEventFromCore(pstPppInfo->pstLcpInfo, (VOS_UINT32)PPP_EVENT_FSM_DOWN, NULL);
                    PPP_LCP_ReceiveEventFromCore(pstPppInfo->pstLcpInfo, (VOS_UINT32)PPP_EVENT_FSM_OPEN, NULL);
                    PPP_LCP_ReceiveEventFromCore(pstPppInfo->pstLcpInfo, (VOS_UINT32)PPP_EVENT_FSM_UP, NULL);

                    /* 稳态连接标记置失败 */
                    pstPppInfo->bPppStateFlg   = PPP_STATE_FAIL;
                    pstPppInfo->bPppStateFlgV6 = PPP_STATE_FAIL;
                }
                /* End: M by h50774 for 子卡异常情况下重协商, 2010/7/17 */
            }
            else
            {
                PPP_DBG_ERR_CNT(PPP_PHERR_402);
                PPP_Debug_CoreEvent(pstPppInfo, PPP_LOG_ERROR,
                                    "PPP_Core_ReceiveEventFromShell: Receive invalid PPP RENEGO event!");
            }

            break;
        }
        default:
            break;
    }

    return;
}


/****************************************************************************
* CREATE DATE  ：2000/04/04                                                 *
* CREATED BY   ：Deng Yi Ou                                                 *
* FUNCTION     ：从外壳接收事件的接口函数                                   *
* MODIFY DATE  ：modified by gxf for GGSN80 20030219                        *
* INPUT        ：pstPppInfo:PPP控制块指针                                   *
*                ulCmd:命令字,可以为如下值:                                 *
*                      PPPISLDOWN:底层DOWN                                  *
*                      PPPISLUP:底层UP                                      *
*                      PPPISLRENEGO:底层发起重协商                          *
*                      PPPCHGIPADDR:IP地址改变                              *
*                      PPPCHGIPXADDR:IPX地址改变                            *
*                       PPPL2TPDOWN: L2TP DOWN              zfz 00/07/05        *
*                pPara:事件的参数,一般情况下为NULL                          *
*                      L2TP的LNS端报ISLUP时: 预协商结果                     *
*                      PPPCHGIPADDR时: 新的IP地址                           *
*                      PPPCHGIPXADDR时: 新的IPX地址                         *
* OUTPUT       ：                                                           *
* RETURN       ：NULL                                                       *
* CALLED BY    ：PPP_Shell_ISLIoCtl / PPP_Shell_NiIoCtl                     *
****************************************************************************/
VOID PPP_Core_ReceiveEventFromShell(PPPINFO_S *pstPppInfo,
                                    VOS_UINT32      ulCmd,
                                    CHAR *     pPara)
{
    PPPLCPINFO_S *pstLcpInfo = NULL;

    if ( VOS_TRUE == g_ulHsgwA10TestDbgFlg )
    {
          PPP_Core_ReceiveEventFromShell_TestStub(pstPppInfo, ulCmd, pPara);
          return;
    }

    PPPC_INFO_LOG1("\r\n---Into PPP_Core_ReceiveEventFromShell   ulCmd: %d---\r\n", ulCmd);
    if (!pstPppInfo || (ulCmd >= PPPSTCEND))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_403);
        return;
    }

    switch (ulCmd)
    {
        case PPPISLUP:
        {
             pstPppInfo->bLowerIsUp = 1;

            /* 如果没有创建LCP控制块,则创建之 */
            if (NULL == pstPppInfo->pstLcpInfo)
            {
                PPP_GETLCPADDR(pstPppInfo->pstLcpInfo, pstPppInfo->ulRPIndex);
                if (pstPppInfo->pstLcpInfo == NULL)
                {
                    PPP_DBG_OK_CNT(PPP_PHOK_997);
                    PPP_Debug_CoreEvent(pstPppInfo, PPP_LOG_ERROR, "Fail:Malloc LCP CB Failed");
                    return;
                }

                PPP_MemSet((void *)pstPppInfo->pstLcpInfo, 0, sizeof(PPPLCPINFO_S));
                PPP_LCP_Init(pstPppInfo);/*luofeng37050notify 协商参数*/
            }

            pstLcpInfo = (PPPLCPINFO_S*)pstPppInfo->pstLcpInfo;

            /* ISLUP事件只在LCP状态为Initial或Starting时才有效 */
            if ((pstLcpInfo->stFsm.ucState == (UCHAR)PPP_STATE_INITIAL)
                || (pstLcpInfo->stFsm.ucState == (UCHAR)PPP_STATE_STARTING))
            {
                PPP_DBG_OK_CNT(PPP_PHOK_998);
                PPP_Core_EstablishPhase(pstPppInfo);
            }

            break;
        }
        case PPPISLDOWN:
        {
            pstPppInfo->bLowerIsUp  = 0;
            pstPppInfo->bLoopBacked = 0;

            /* L2TP需要的参数 */
            if (NULL != pstPppInfo->pL2tpPara)
            {
                (VOID)PPP_Free(pstPppInfo->pL2tpPara);
                pstPppInfo->pL2tpPara = NULL;
            }

            /* 通知 LCP Down  */
            if (pstPppInfo->pstLcpInfo)
            {
                PPP_DBG_OK_CNT(PPP_PHOK_999);
                /* 向LCP发送两个消息:LowerDown和Close */
                PPP_LCP_ReceiveEventFromCore(pstPppInfo->pstLcpInfo, (VOS_UINT32)PPP_EVENT_FSM_DOWN, NULL);
                PPP_LCP_ReceiveEventFromCore(pstPppInfo->pstLcpInfo, (VOS_UINT32)PPP_EVENT_FSM_CLOSE, NULL);

                /* 两个消息对应状态机事件的状态转换图:
                 | State
                 |    0         1         2         3         4         5           6         7         8           9
                Events| Initial   Starting  Closed    Stopped   Closing   Stopping   Req-Sent  Ack-Rcvd  Ack-Sent    Opened
                ------+------------------------------------------------------------------------------------------------------
                 Down |    -         -         0       tls/1       0         1          1         1         1         tld/1
                 Close|    0       tlf/0       2         2         4         4      irc,str/4 irc,str/4 irc,str/4 tld,irc,str/4
                 */

                /* 1,发送LowerDown事件,不同状态下动作如下:
                   Opened状态:向上层协议发送LowerDown事件(tld),状态转为Starting
                   Closed/Closing状态:状态转为Initial
                   其他:状态转为Starting

                   2,发送Close事件,初始状态只可能为Initial或Starting.不同状态下动作如下:
                   Starting状态:状态转为Initial;向下层发送Finished事件(tlf).
                   Initial状态:无变化

                   因此,这两个事件发送后会有如下结果:
                   1,最终状态必然会转入Initial
                   2,只要初始状态不是Closed/Closing,则必然会有tlf动作发生
                 */
            }

            if (pstPppInfo->pstPapInfo)
            {
                PPP_PAP_ReceiveEventFromCore(pstPppInfo, PAP_EVENT_LOWERDOWN, NULL);
            }
            if (pstPppInfo->pstChapInfo)
            {
                PPP_CHAP_ReceiveEventFromCore(pstPppInfo, CHAP_EVENT_LOWERDOWN, NULL);
            }

            break;

        }
        case PPPISLRENEGO:/* 重协商 */
        {
            if ((pstPppInfo->pstIpcpInfo)||(pstPppInfo->pstIpV6cpInfo))
            {
                PPP_DBG_OK_CNT(PPP_PHOK_1000);
                /* renego后, LCP down, 调用PPP_Core_NotifyNcpDown, IPCP收到down、close事件
                   到达finished状态, 又调用PPP_LCP_NegotiationDown, LCP到达initial状态, 必须
                   发送open、up事件才能再次重协商 */

                /* BEGIN: M by h50774 for 子卡异常情况下重协商, 2010/7/17 */
                /*if (((PPPIPCPINFO_S*)pstPppInfo->pstIpcpInfo)->stFsm.ucState == PPP_STATE_OPENED)*/
                {
                    PPP_LCP_ReceiveEventFromCore(pstPppInfo->pstLcpInfo, (VOS_UINT32)PPP_EVENT_FSM_DOWN, NULL);
                    PPP_LCP_ReceiveEventFromCore(pstPppInfo->pstLcpInfo, (VOS_UINT32)PPP_EVENT_FSM_OPEN, NULL);
                    PPP_LCP_ReceiveEventFromCore(pstPppInfo->pstLcpInfo, (VOS_UINT32)PPP_EVENT_FSM_UP, NULL);

                    /* 稳态连接标记置失败 */
                    pstPppInfo->bPppStateFlg   = PPP_STATE_FAIL;
                    pstPppInfo->bPppStateFlgV6 = PPP_STATE_FAIL;
                }
                /* End: M by h50774 for 子卡异常情况下重协商, 2010/7/17 */
            }
            else
            {
                PPP_DBG_ERR_CNT(PPP_PHERR_404);
                PPP_Debug_CoreEvent(pstPppInfo, PPP_LOG_ERROR,
                                    "PPP_Core_ReceiveEventFromShell: Receive invalid PPP RENEGO event!");
            }

            break;
        }
        default:
            break;
    }

    return;
}

/****************************************************************************
* CREATE DATE  ：2000/04/04                                                 *
* CREATED BY   ：Deng Yi Ou                                                 *
* FUNCTION     ：从子协议接收事件的接口函数                                 *
* MODIFY DATE  ：modified by gxf for GGSN80 20030219                        *
* INPUT        ：pstPppInfo:PPP控制块指针                                   *
*                ulCmd:命令字,主要为代表各子协议UP/DOWN的值                 *
*                pPara:事件的参数,一般情况下为NULL                          *
* OUTPUT       ：                                                           *
* RETURN       ：0                                                          *
* CALLED BY    ：PPP_Shell_ISLIoCtl / PPP_Shell_NiIoCtl                     *
****************************************************************************/
VOID PPP_Core_ReceiveEventFromProtocol (PPPINFO_S *pstPppInfo,
                                        VOS_UINT32      ulCmd,
                                        CHAR *     pPara)
{
    VOS_UINT32                               ulMagic;
    PPPFSM_S                           *pstFsm     = NULL;
    PPP_LCP_OPTION_S                   *pstGotOptions;


    PPPC_INFO_LOG1("\r\n---Into PPP_Core_ReceiveEventFromProtocol   ulCmd: %d---\r\n", ulCmd);
    if (!pstPppInfo || (ulCmd >= PPP_EVENT_MAXEVENT))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_405);
        return;
    }

    switch (ulCmd)
    {
        case PPP_EVENT_LCPUP:
        {
            if (VOS_ERR == PPP_Shell_ReceiveEventFromCore(pstPppInfo, PPP_LCP_UP, NULL))
            {
                /* 下发用户信息失败, 拆链   modified by gxf 20030430
                   LCP open状态下发down、close事件到达initil状态, 需要向shell主动下发LCPDOWN事件(见PPP_Core_DeadPhase) */
                PPP_LCP_ReceiveEventFromCore(pstPppInfo->pstLcpInfo, PPP_EVENT_FSM_DOWN, NULL);
                PPP_SET_REL_CODE(pstPppInfo, AM_RELCODE_PPP_LCP_NEGONAK);
                PPP_LCP_ReceiveEventFromCore(pstPppInfo->pstLcpInfo, PPP_EVENT_FSM_CLOSE, NULL);
                (VOID)PPP_Shell_ReceiveEventFromCore(pstPppInfo, PPP_LCP_DOWN, NULL);
                PPP_DBG_ERR_CNT(PPP_PHERR_406);
                return;
            }

            /* 增加IP地址泄漏保护, Add by yangfan */
            if ((pstPppInfo->ulPeerIPAddr) && (0 == pstPppInfo->bReNego))
            {
                PPP_DBG_ERR_CNT(PPP_PHERR_407);
                PPP_SET_REL_CODE(pstPppInfo, AM_RELCODE_PPP_LCP_NEGONAK);
                PPP_LCP_NegotiationDown(pstPppInfo->pstLcpInfo);
                return;
            }
            /* 增加IP地址泄漏保护, Add by yangfan */
            if ((VOS_OK == PPP_ipv6_addr_check(pstPppInfo->usPeerIPv6Addr))
                && (0 == pstPppInfo->bReNegoV6))
            {
                PPP_DBG_ERR_CNT(PPP_PHERR_408);
                PPP_SET_REL_CODE(pstPppInfo, AM_RELCODE_PPP_LCP_NEGONAK);
                PPP_LCP_NegotiationDown(pstPppInfo->pstLcpInfo);
                return;
            }

#if 0    /* EAP-dev */
            /* 如果在做接入鉴权则不需要发送版本能力指示 */
            enIsDoingAccessAuth = PPPC_IsDoingAccessAuth((VOS_UINT8)pstPppInfo->ulRPIndex);
            if (PS_FALSE == enIsDoingAccessAuth)
            {
                /* 发送版本能力指示报文*/
                ulMagic = PPP_GetMagicNumber();
                pstFsm = &(((PPPLCPINFO_S*)pstPppInfo->pstLcpInfo)->stFsm);
                PPP_FSM_SendVendorSpecific(pstFsm, pstFsm->ucVSId, ulMagic,VENDORSPECIFIC_INDICTE);
                pstFsm->ucVSId++;
            }
#else
            /* if current ppp is not access-auth ppp, it ought to be PDSN PPP */
            if (PPPC_PPP_ID_FOR_ACCESS_AUTH != pstPppInfo->ulRPIndex)
            {
                if (VOS_TRUE == pstPppInfo->bEhrpdUser)    /* ppp works on eHRPD */
                {
                    /* 发送版本能力指示报文*/
                    ulMagic = PPP_GetMagicNumber();
                    pstFsm = &(((PPPLCPINFO_S*)pstPppInfo->pstLcpInfo)->stFsm);
                    PPP_FSM_SendVendorSpecific(pstFsm, pstFsm->ucVSId, ulMagic, VENDORSPECIFIC_INDICTE);
                }
            }
#endif

            /* 保存MRU */
            pstGotOptions = &(((PPPLCPINFO_S*)pstPppInfo->pstLcpInfo)->stGotOptions);
            pstPppInfo->pstConfigInfo->usMru = pstGotOptions->mru;

            /* 检查LCP协商结果,确定是否验证 */
            PPP_Core_AuthUp(pstPppInfo,NULL);
            break;
        }
        case PPP_EVENT_LCPDOWN:
        {
            if ((PPPLOWEDOWN != pstPppInfo->bFailFlag) && (1 == pstPppInfo->bReNego ||1 == pstPppInfo->bReNegoV6))
            {
                (VOID)PPP_SendUserInfo(pstPppInfo, MAGICNUM_INVALID);
            }

            PPP_DBG_OK_CNT(PPP_PHOK_1001);
            /* 稳态连接标记置失败 */
            pstPppInfo->bPppStateFlg   = PPP_STATE_FAIL;
            pstPppInfo->bPppStateFlgV6 = PPP_STATE_FAIL;

            /* 协议转入Terminate阶段,重新协商LCP */
            PPP_Core_TerminatePhase(pstPppInfo);
            break;
        }
        case PPP_EVENT_LCPFINISHED:
        {
            PPP_DBG_OK_CNT(PPP_PHOK_1002);

            /*zfz notice: 需要删除PAP/CHAP 控制块 */
            if (pstPppInfo->pstPapInfo)
            {
                PPP_PAP_ReceiveEventFromCore(pstPppInfo, PAP_EVENT_LOWERDOWN, NULL);
            }

            if (pstPppInfo->pstChapInfo)
            {
                PPP_CHAP_ReceiveEventFromCore(pstPppInfo, CHAP_EVENT_LOWERDOWN, NULL);
            }

            if (pstPppInfo->pstEapInfo)
            {
                PPPC_EAP_ReceiveEventFromCore(pstPppInfo, EAP_EVENT_LOWERDOWN, NULL);
            }

            /* 协议转入Dead阶段 */
            PPP_Core_DeadPhase(pstPppInfo);
            break;
        }
        case PPP_EVENT_LCPSTARTING:
            break;

        case PPP_EVENT_IPCPUP:
        {
            if (NULL != pstPppInfo->pstIpcpInfo)
            {
                PPP_DBG_OK_CNT(PPP_PHOK_1003);
                pstPppInfo->bIpcpNoToPDN= VOS_FALSE;   /* 1时不通知PDN */

                /* 向外壳发送IPCP UP事件 */
                if (VOS_ERR == PPP_Shell_ReceiveEventFromCore(pstPppInfo, PPP_IPCP_UP, NULL))
                {
                    /* 下发用户信息失败, 拆链   modified by gxf 20030430
                       LCP open状态下发down、close事件到达initil状态, 需要向shell主动下发LCPDOWN事件(见PPP_Core_DeadPhase) */
                    /* 上面函数中的所有的错误分支都已经开始了lcp down,这里不需要再进行了 */
                    PPP_DBG_OK_CNT(PPP_PHOK_1004);
                    return;
                }
            }

            break;
        }
        case PPP_EVENT_IPCPDOWN:
        {
            if (NULL != pstPppInfo->pstIpcpInfo)
            {
                PPP_DBG_OK_CNT(PPP_PHOK_1005);

                /* 向外壳发送IPCP DOWN事件 */
                (VOID)PPP_Shell_ReceiveEventFromCore(pstPppInfo, PPP_IPCP_DOWN, NULL);
            }
            break;
        }
        case PPP_EVENT_IPCPFINISHED:
        {
            /* 通知PDN IPCP协商失败 */
            /* 判断是否要通知pdn，是则通知 */
            if (VOS_FALSE == pstPppInfo->bIpcpNoToPDN)
            {
                PPP_DBG_OK_CNT(PPP_PHOK_1006);
            }

            PPP_DBG_OK_CNT(PPP_PHOK_1007);
            PPP_Core_IpcpV4FinProc(pstPppInfo);

            break;
        }
        case PPP_EVENT_IPCPSTARTING:
            break;

        case PPP_EVENT_IPV6CPUP:
            if ( NULL != pstPppInfo->pstIpV6cpInfo)
            {
                PPP_DBG_OK_CNT(PPP_PHOK_1008);
                pstPppInfo->bIpv6cpNoToPDN= VOS_FALSE;   /* 1时不通知PDN */

                /* 向外壳发送IPV6CP UP事件 */
                if (VOS_ERR == PPP_Shell_ReceiveEventFromCore(pstPppInfo, PPP_IPV6CP_UP, NULL))
                {
                    /* 下发用户信息失败, 拆链
                       LCP open状态下发down、close事件到达initil状态, 需要向shell主动下发LCPDOWN事件(见PPP_Core_DeadPhase) */
                    PPP_DBG_ERR_CNT(PPP_PHERR_409);
                    return;
                }
            }
            break;

        case PPP_EVENT_IPV6CPDOWN:
            if (NULL != pstPppInfo->pstIpV6cpInfo)
            {
                /* 向外壳发送IPV6CP DOWN事件 */
                (VOID)PPP_Shell_ReceiveEventFromCore(pstPppInfo, PPP_IPV6CP_DOWN, NULL);

                PPP_DBG_OK_CNT(PPP_PHOK_1009);
            }
            break;

        case PPP_EVENT_IPV6CPFINISHED:

            /* 通知PDN IPV6CP协商失败 */
            /* 判断是否要通知pdn，是则通知 */
            if (VOS_FALSE == pstPppInfo->bIpv6cpNoToPDN)
            {
                PPP_DBG_OK_CNT(PPP_PHOK_1010);
            }

            PPP_DBG_OK_CNT(PPP_PHOK_1011);
            PPP_Core_IpcpV6FinProc(pstPppInfo);
            break;

        case PPP_EVENT_IPV6CPSTARTING:
            break;

        /* BEGIN: Added for PN:PDSN融合 by wangyong 00138171, 2013/1/19 */
        case PPP_EVENT_VSNCPUP:
        {
            if (NULL != pstPppInfo->pstVsncpInfo)
            {
                PPP_DBG_OK_CNT(PPP_PHOK_1012);
                /* 向外壳发送VSNCP UP事件 */
                if (VOS_ERR == PPP_Shell_ReceiveEventFromCore(pstPppInfo, PPP_VSNCP_UP, NULL))
                {
                    PPP_DBG_ERR_CNT(PPP_PHERR_410);
                    return;
                }
            }
            break;
        }
        case PPP_EVENT_VSNCPDOWN:
        {
            if (NULL != pstPppInfo->pstVsncpInfo)
            {
                PPP_DBG_OK_CNT(PPP_PHOK_1013);
                /* 向外壳发送VSNCP DOWN事件 */
                (VOID)PPP_Shell_ReceiveEventFromCore(pstPppInfo, PPP_VSNCP_DOWN, NULL);
            }
            break;
        }
        case PPP_EVENT_VSNCPFINISHED:
        {
            PPP_DBG_OK_CNT(PPP_PHOK_1014);
            PPP_CORE_VSNCPFinishProc(pstPppInfo);
            break;
        }
        case PPP_EVENT_VSNCPSTARTING:
            break;
        /* END:   Added for PN:PDSN融合 by wangyong 00138171, 2013/1/19 */

        case PPP_EVENT_PAPSUCCESS:/*PAP验证成功 */
        {
            PPP_DBG_OK_CNT(PPP_PHOK_1015);
            pstPppInfo->bAuthFlag = VOS_TRUE;

            M_SET_NEWPHASE(pstPppInfo, PPP_SNMP_PERF_PHASE_NET);

            PPP_Core_AuthUp(pstPppInfo, (UCHAR *)pPara);

            break;
        }
        case PPP_EVENT_PAPFAILED:/*PAP 验证失败 */
        {
            /*删除PAP控制块*/
            if (pstPppInfo->pstPapInfo)
            {
                PPPPAPINFO_S* pstPapInfo = (PPPPAPINFO_S*)pstPppInfo->pstPapInfo;
                PPP_DBG_OK_CNT(PPP_PHOK_1016);
                if (NULL != pstPapInfo->pstAAAAuthReqMsg)
                {
                    (VOID)PPP_Free(pstPapInfo->pstAAAAuthReqMsg);
                    pstPapInfo->pstAAAAuthReqMsg = NULL;
                }
                /*删除等待Request 超时定时器*/
                if (pstPapInfo->ulServerTimeoutID != 0)
                {
                    (VOID)VOS_StopRelTimer(&(pstPapInfo->ulServerTimeoutID));
                    pstPapInfo->ulServerTimeoutID = 0;
                }

                pstPapInfo->ucUsed = 0;
                pstPppInfo->pstPapInfo = NULL;
            }

            PPP_SET_REL_CODE(pstPppInfo, AM_RELCODE_PPP_PAP_NAK);
            PPP_DBG_OK_CNT(PPP_PHOK_1017);

            /*通知LCP DOWN 或FINISHED */
            PPP_LCP_NegotiationDown(pstPppInfo->pstLcpInfo);
            break;
        }
        case PPP_EVENT_CHAPSUCCESS:/*CHAP验证成功 */
        {
            PPP_DBG_OK_CNT(PPP_PHOK_1018);
            pstPppInfo->bAuthFlag = VOS_TRUE;
            M_SET_NEWPHASE(pstPppInfo, PPP_SNMP_PERF_PHASE_NET);

            PPP_Core_AuthUp(pstPppInfo, (UCHAR *)pPara);

            break;
        }
        case PPP_EVENT_CHAPFAILED: /*CHAP 验证失败 */
        {
            /*删除CHAP控制块*/
            if (pstPppInfo->pstChapInfo)
            {
                PPPCHAPINFO_S* pstChapInfo = (PPPCHAPINFO_S*)pstPppInfo->pstChapInfo;
                PPP_DBG_OK_CNT(PPP_PHOK_1019);

                if (NULL != pstChapInfo->pstAAAAuthReqMsg)
                {
                    (VOID)PPP_Free(pstChapInfo->pstAAAAuthReqMsg);
                    pstChapInfo->pstAAAAuthReqMsg = NULL;
                }

                pstChapInfo->ucUsed = 0;
                pstPppInfo->pstChapInfo = NULL;
            }

            PPP_SET_REL_CODE(pstPppInfo, AM_RELCODE_PPP_CHAP_NAK);
            PPP_DBG_OK_CNT(PPP_PHOK_1020);

            /*通知LCP DOWN 或FINISHED */
            PPP_LCP_NegotiationDown(pstPppInfo->pstLcpInfo);
            break;
        }

#if VRP_MODULE_LINK_PPP_EAP == VOS_YES
        /*EAP验证成功 */
        case PPP_EVENT_EAPSUCCESS:
        {
            PPP_DBG_OK_CNT(PPP_PHOK_1021);
            pstPppInfo->bAuthFlag = VOS_TRUE;
            pstPppInfo->bAuthClient = VOS_NO;

            PPP_Core_AuthUp(pstPppInfo, (UCHAR *)pPara);
            break;
        }
        /* EAP 验证失败 */
        case PPP_EVENT_EAPFAILED:
        {
            /* 删除EAP控制块 */
            if (pstPppInfo->pstEapInfo)
            {
                PPPC_EAP_Init(pstPppInfo);
                pstPppInfo->pstEapInfo = NULL;
            }

            PPP_SET_REL_CODE(pstPppInfo, AM_RELCODE_PPP_EAP_FAIL);
            PPP_DBG_OK_CNT(PPP_PHOK_1023);
            /* 通知LCP DOWN 或FINISHED */
            PPP_LCP_NegotiationDown(pstPppInfo->pstLcpInfo);

            /* 设置Attach失败的原因为EAP鉴权失败 */
            PPPC_SetAttachErrorCode(CNAS_CTTF_EHRPD_ERROR_CODE_LCP_EAP_FAILURE);

            break;
        }
#endif
        case PPP_EVENT_RECHALLENGE:/* CHAP 重新验证,DOWN掉NCP */
        {
            if (pstPppInfo->usPhase == (VOS_UINT16)PPP_PHASE_NETWORK)
            {
                PPP_DBG_OK_CNT(PPP_PHOK_1024);
                /* 通知NCP DOWN  */
                if (pstPppInfo->pstIpcpInfo)
                {
                    PPP_IPCP_ReceiveEventFromCore(pstPppInfo->pstIpcpInfo, PPP_EVENT_FSM_DOWN, NULL );
                    PPP_IPCP_ReceiveEventFromCore(pstPppInfo->pstIpcpInfo, PPP_EVENT_FSM_CLOSE, NULL );

                    /* 释放分配给对端的IP地址 */
                    (VOID)PPP_Shell_ReceiveEventFromCore(pstPppInfo, PPP_FREE_PEERIPADDR, NULL);

                    if ( VOS_NULL != ((PPPIPCPINFO_S*)(pstPppInfo->pstIpcpInfo))->pucIpv4cpMsg )
                    {
                        (VOID)PPP_Free(((PPPIPCPINFO_S*)(pstPppInfo->pstIpcpInfo))->pucIpv4cpMsg);
                        ((PPPIPCPINFO_S*)(pstPppInfo->pstIpcpInfo))->pucIpv4cpMsg = NULL;
                        ((PPPIPCPINFO_S*)(pstPppInfo->pstIpcpInfo))->ulIpv4cpLen = 0;
                    }

                    /* 释放控制块占用标记 */
                    ((PPPIPCPINFO_S*)pstPppInfo->pstIpcpInfo)->ucUsedFlag = 0;
                    pstPppInfo->pstIpcpInfo = NULL;
                }
                pstPppInfo->usPhase = (VOS_UINT16)PPP_PHASE_AUTHENTICATE;
            }

            break;
        }
#if (VRP_MODULE_LINK_PPP_CCP == VRP_YES)
        case PPP_EVENT_CCPUP:
        {
            PPP_DBG_OK_CNT(PPP_PHOK_1025);
            if (VOS_OK != PPP_Shell_ReceiveEventFromCore(pstPppInfo, PPP_CCP_UP, NULL))
            {
                 PPP_DBG_ERR_CNT(PPP_PHERR_411);
                 PPP_CCP_ReceiveEventFromCore(pstPppInfo->pstCcpInfo,PPP_EVENT_FSM_CLOSE, NULL);
            }
            break;
        }
        case PPP_EVENT_CCPDOWN:
        {
            PPP_DBG_OK_CNT(PPP_PHOK_1026);
            (VOID)PPP_Shell_ReceiveEventFromCore(pstPppInfo, PPP_CCP_DOWN, NULL);
            break;
        }
        case PPP_EVENT_CCPFINISHED:
        {
            /* 删除控制块 */
            if (pstPppInfo->pstCcpInfo != NULL)
            {
                PPP_DBG_OK_CNT(PPP_PHOK_1027);
                /*line -e746*/
                PPP_ClearCCPCB(pstPppInfo->pstCcpInfo);
                /*lint +e746*/
            }

            break;
        }
        case PPP_EVENT_CCPSTARTING:
            break;
#endif
        default:
            break;
    }

    return;
}

/****************************************************************************
* CREATE DATE  ：2000/04/04                                                 *
* CREATED BY   ：Deng Yi Ou                                                 *
* FUNCTION     ：对方拒绝协商一个协议,通知该协议:lower down                 *
* MODIFY DATE  ：                                                           *
* INPUT        ：pPppInfo:PPP控制块指针                                     *
*                usRejectedProtocol:被拒绝的协议号                          *
* OUTPUT       ：                                                           *
* RETURN       ：0                                                          *
* CALLED BY    ：PPP_FSM_ReceiveProtocolRej                                 *
****************************************************************************/
VOID PPP_Core_RejectProtocol(VOID *pPppInfo, VOS_UINT16 usRejectedProtocol)
{
    PPPINFO_S *pstPppInfo = NULL;

    if (VOS_NULL_PTR == pPppInfo)
    {
        return;
    }

    pstPppInfo = (PPPINFO_S*)pPppInfo;

    /*    VOS_DBGASSERT(pstPppInfo) ;*/
    PPPC_INFO_LOG("\r\n---Into PPP_Core_RejectProtocol---\r\n");

    switch (usRejectedProtocol)
    {
        case PPP_PAP:
            if (pstPppInfo->pstPapInfo)
            {
                PPP_DBG_OK_CNT(PPP_PHOK_1028);
                /* PAP不遵循PPP标准状态机,不用发送CLOSE事件 */
                PPP_PAP_ReceiveEventFromCore(pstPppInfo, PAP_EVENT_LOWERDOWN, NULL);

                /* 删除PAP控制块 */
                if (NULL != ((PPPPAPINFO_S*)pstPppInfo->pstPapInfo)->pstAAAAuthReqMsg)
                {
                    (VOID)PPP_Free(((PPPPAPINFO_S*)pstPppInfo->pstPapInfo)->pstAAAAuthReqMsg);
                    ((PPPPAPINFO_S*)pstPppInfo->pstPapInfo)->pstAAAAuthReqMsg = NULL;
                }

                /*释放控制块占用标记*/
                ((PPPPAPINFO_S*)pstPppInfo->pstPapInfo)->ucUsed = 0;
                pstPppInfo->pstPapInfo = NULL;
            }

            break;

        case PPP_CHAP:
            if (pstPppInfo->pstChapInfo)
            {
                PPP_DBG_OK_CNT(PPP_PHOK_1029);
                /* CHAP不遵循PPP标准状态机,不用发送CLOSE事件 */
                PPP_CHAP_ReceiveEventFromCore(pstPppInfo, CHAP_EVENT_LOWERDOWN, NULL);

                /* 删除CHAP控制块 */
                if (NULL != ((PPPCHAPINFO_S*)pstPppInfo->pstChapInfo)->pstAAAAuthReqMsg)
                {
                    (VOID)PPP_Free(((PPPCHAPINFO_S*)pstPppInfo->pstChapInfo)->pstAAAAuthReqMsg);
                    ((PPPCHAPINFO_S*)pstPppInfo->pstChapInfo)->pstAAAAuthReqMsg = NULL;
                }

                /*释放控制块占用标记*/
                ((PPPCHAPINFO_S*)pstPppInfo->pstChapInfo)->ucUsed = 0;
                pstPppInfo->pstChapInfo = NULL;
            }

            break;

        default:
            break;
    }

    return;
}

/****************************************************************************
* CREATE DATE  ：2000/04/05                                                 *
* CREATED BY   ：Deng Yi Ou                                                 *
* FUNCTION     ：按照协议号获得对应协议的状态机指针,没有状态机的            *
*                (如PAP / CHAP,或协议状态机没有创建)则返回NULL              *
* MODIFY DATE  ：                                                           *
* INPUT        ：pPppInfo  : PPP控制块                                      *
*                usProtocol: 协议号                                         *
* OUTPUT       ：                                                           *
* RETURN       ：0                                                          *
* CALLED BY    ：PPP_FSM_ReceiveProtocolRej                                 *
****************************************************************************/
PPPFSM_S *PPP_Core_GetFsmByProtocol(VOID *pPppInfo, VOS_UINT16 usProtocol)
{
    PPPINFO_S *pstPppInfo = NULL;
    PPPFSM_S  *pstFsm = NULL;


    if (VOS_NULL_PTR == pPppInfo)
    {
        return VOS_NULL;
    }

    pstPppInfo = (PPPINFO_S*)pPppInfo;

    switch (usProtocol)
    {
        case PPP_IPCP:
            if (pstPppInfo->pstIpcpInfo)
            {
                pstFsm = &(((PPPIPCPINFO_S*)(pstPppInfo->pstIpcpInfo))->stFsm);
            }

            break;
         case PPP_IPV6CP:
             if (pstPppInfo->pstIpV6cpInfo)
             {
                 pstFsm = &(((PPPIPV6CPINFO_S *)(pstPppInfo->pstIpV6cpInfo))->stFsm);
             }

             break;
        case PPP_CCP:
        case PPP_MCP:
        case PPP_SCP:
            if (pstPppInfo->pstCcpInfo)
            {
                pstFsm = &(((PPP_CCP_INFO_S*)(pstPppInfo->pstCcpInfo))->stFsm);
            }

            break;

        default:
            PPP_DBG_ERR_CNT(PPP_PHERR_412);
            break;
    }

    return pstFsm;
}

/****************************************************************************
* CREATE DATE  ：2000/04/04                                                 *
* CREATED BY   ：Deng Yi Ou                                                 *
* FUNCTION     ：获得报文的协议号                                           *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstPppInfo:PPP控制块指针                                   *
*                pPacket:报文头指针                                         *
* OUTPUT       ：                                                           *
*                pusProtocol:要返回的协议号                                 *
* RETURN       ：PPP头长度                                                  *
* CALLED BY    ：PPP_Core_ReceivePacketFromShell                            *
*                PPP_Shell_ISLInput                                         *
****************************************************************************/
VOS_UINT32 PPP_Core_GetProtocol(PPPINFO_S *pstPppInfo,
                           UCHAR *    pPacket,
                           VOS_UINT16 *   pusProtocol)
{
    VOS_UINT32 ulPointerShift = 0;
    VOS_UINT32 ulDataShift = 0;

    if ((NULL == pusProtocol) || (NULL == pPacket))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_413);
        return 0;
    }

    if (pPacket[0] == 0xff)  /** no accmp **/
    {
        if (pPacket[1] != 0x03)
        {
            /*log error here*/
            PPP_DBG_ERR_CNT(PPP_PHERR_414);
            return 0;
        }

        /*
        ____________________________________
         |    |    |    |    |
         | ff | 03 | 00 | 21 |............
         |____|____|____|____|_________________
         |  accmp  |  pcmp   |
         */
        if (pPacket[2] & 0x01)   /** pcmp  **/
        {
            ulPointerShift = 3;
            ulDataShift = 1;

            /*
            _______________________________
             |    |    |    |
             | ff | 03 | 21 |............
             |____|____|____|_________________
             |  accmp  |pcmp|
             */
        }
        else
        {
            ulPointerShift = 4;
            ulDataShift = 2;
        }
    }
    else
    {
        /*如果没有设置地址压缩那么有错*/

        /*
        if (pstPppInfo->pstLcpInfo &&
            ((PPPLCPINFO_S *)pstPppInfo->pstLcpInfo)->stHisOptions.neg_accompression == 0)

        {
            pstPppInfo->stStatisticInfo.ulBadAddressPackets ++;
        }
         */

        if (pPacket[0] & 0x01)   /** pcmp **/
        {
            ulPointerShift = 1;
            ulDataShift = 1;

            /*_____________________
             |    |
             | 21 |............
             |____|_________________
             |pcmp|
             */
        }
        else
        {
            ulPointerShift = 2;
            ulDataShift = 2;

            /*
             ____________________________________
             |    |    |
             | 00 | 21 |............
             |____|____|_________________
             |  pcmp   |
             */
        }
    }

    pPacket += (ulPointerShift - ulDataShift);
    if (ulDataShift == 2)
    {
        PPP_GETSHORT(*pusProtocol, pPacket);
    }
    else
    {
        PPP_GETCHAR(*pusProtocol, pPacket);
    }

    (VOS_VOID)pPacket;
    return ulPointerShift;
}

/****************************************************************************
* CREATE DATE  ：2000/04/04                                                 *
* CREATED BY   ：Deng Yi Ou                                                 *
* FUNCTION     ：收到不能识别或不支持的协议的报文,发送protocol rej报文      *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstPppInfo:PPP控制块指针                                   *
*                pHead:报文所在内存块的头指针                               *
*                pPacket:报文头指针                                         *
*                ulLen:报文长度                                             *
*                usProtocol:报文的协议号                                    *
* OUTPUT       ：                                                           *
* RETURN       ：0                                                          *
* CALLED BY    ：PPP_Core_ReceivePacketFromShell                            *
****************************************************************************/
VOID PPP_Core_ReceiveUnknownProtocol (PPPINFO_S *pstPppInfo,
                                      UCHAR *    pHead,
                                      UCHAR *    pPacket,
                                      VOS_UINT32      ulLen,
                                      VOS_UINT16     usProtocol,
                                      UCHAR      ucCode)
{
    PPPLCPINFO_S *pstLcpInfo = NULL;
    PPPFSM_S *pstFsm = NULL;

    PPPC_INFO_LOG("\r\n---Into PPP_Core_ReceiveUnknownProtocol---\r\n");
    PPP_DBG_OK_CNT(PPP_PHOK_1030);
    if (NULL == pstPppInfo)
    {
        return;
    }

    pstLcpInfo = (PPPLCPINFO_S*)pstPppInfo->pstLcpInfo;
    if (NULL == pstLcpInfo)
    {
        return;
    }

    if ((pstLcpInfo->stFsm.ucState == (UCHAR)PPP_STATE_OPENED))
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1031);
        pstFsm = &(pstLcpInfo->stFsm);

        ulLen = 2;
        if (NULL == pHead)
        {
            return;
        }

        if ((PPP_IPCP == usProtocol) && (CONFREQ == ucCode))
        {
            PPP_DBG_OK_CNT(PPP_PHOK_1032);
            PPP_PerfInc(&g_stPppPerfStatistic.ulIpcpTotal, PERF_TYPE_PPPC_IPCP_NEGO_REQ_NUM, pstPppInfo->bEhrpdUser);
            PPPC_INFO_LOG("****Ipv6cpTotal: Only Support ipv6, IPV4_IPCP_ATTEMPT times! ");
        }

        if((PPP_IPV6CP == usProtocol)&& (CONFREQ == ucCode))
        {
            PPP_DBG_OK_CNT(PPP_PHOK_1033);
            PPPC_INFO_LOG("****Ipv6cpTotal: PPP_Core_ReceivePacketFromShell, IPV6_PerfStatistic Attempt: Enter!");
            A11_OM_PerfStatisticPCFUnit((VOS_UINT32)PERF_TYPE_PCF_PPPC_IPV6CP_NEGO_REQ_NUM, pstPppInfo->ulPcfIP);
        }

        pPacket = pHead + PPP_RESERVED_PACKET_HEADER;

        /* 报文情况 */

        /*
         |---- PPP_RESERVED_PACKET_HEADER ----|---- ulLen ----|
         +-+-+-+-+-+-+--+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
         |               ...                  |       |       |
         +-+-+-+-+-+-+--+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
         |                                    |
        pHead                                pPacket
         */

        PPP_PUTSHORT(usProtocol, pPacket);
        pPacket -= ulLen;

        /* 报文情况 */

        /*
         |---- PPP_RESERVED_PACKET_HEADER ----|---- ulLen ----|
         +-+-+-+-+-+-+--+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
         |               ...                  |    protocol   |
         +-+-+-+-+-+-+--+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
         |                                    |
        pHead                                pPacket
         */

        /* 发送protocol reject */
        PPP_FSM_SendPacket(pstFsm, PROTREJ, pstFsm->ucPktId++, pHead, pPacket, ulLen);
    }
    else
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1034);
    }
}

/****************************************************************************
* CREATE DATE  ：2000/04/04                                                 *
* CREATED BY   ：Deng Yi Ou                                                 *
* FUNCTION     ：PPP协商阶段转换到Dead阶段                                  *
* MODIFY DATE  ：modified by gxf for GGSN80 20030220                        *
* INPUT        ：pstPppInfo:PPP控制块指针                                   *
* OUTPUT       ：                                                           *
* RETURN       ：0                                                          *
* CALLED BY    ：PPP_Core_ReceiveEventFromProtocol                                                         *
****************************************************************************/
VOID PPP_Core_DeadPhase(PPPINFO_S *pstPppInfo)
{
    /* 缺省启动reset定时器 */
    VOS_UINT32 ulReset = 0;

    PPPLCPINFO_S *pstLcpInfo = NULL;


    PPPC_INFO_LOG("\r\n---Into PPP_Core_DeadPhase---\r\n");

    if (!pstPppInfo)
    {
        return;
    }

    /* 改变协商阶段 */
    pstPppInfo->usPhase = (VOS_UINT16)PPP_PHASE_DEAD;

    pstLcpInfo = (PPPLCPINFO_S*)pstPppInfo->pstLcpInfo;
    if ((pstLcpInfo != NULL) && (pstLcpInfo->stFsm.ucState == (UCHAR)PPP_STATE_INITIAL))
    {
        /* LCP状态为Initial,说明是底层down导致LCP finished事件的,
           因此不用通知底层 */

        /* GGSNB03,通知GTPC，L2TP 拆除连接的问题 */
        /*PPP_Shell_ReceiveEventFromCore(pstPppInfo, (VOS_UINT32)PPP_LCP_DOWN, (CHAR*)&ulReset) ;*/
        PPP_DBG_OK_CNT(PPP_PHOK_1035);
    }
    else
    {
        /* LCP状态不为Initial,说明LCP协商导致LCP finished事件的, */

        /* 通知底层:链路已经不再需要，可以拆除链路了 */
        (VOID)PPP_Shell_ReceiveEventFromCore(pstPppInfo, (VOS_UINT32)PPP_LCP_DOWN, (CHAR*)&ulReset);
        PPP_DBG_OK_CNT(PPP_PHOK_1036);
    }

    return;
}

/****************************************************************************
* CREATE DATE  ：2000/04/04                                                 *
* CREATED BY   ：Deng Yi Ou                                                 *
* FUNCTION     ：PPP协商阶段转换到Establish阶段                             *
* MODIFY DATE  ：modified by gxf for GGSN80 20030220                        *
* INPUT        ：pstPppInfo:PPP控制块指针                                   *
* OUTPUT       ：                                                           *
* RETURN       ：0                                                          *
* CALLED BY    ：PPP_Core_ReceiveEventFromShell                             *
****************************************************************************/
VOID PPP_Core_EstablishPhase(PPPINFO_S *pstPppInfo)
{


    PPPC_INFO_LOG("\r\n---Into PPP_Core_EstablishPhase---\r\n");
    if (NULL == pstPppInfo)
    {
        return;
    }

 #if (VRP_MODULE_SEC_L2TP == VRP_YES)
    /* L2TP需要的参数 */
    if ( (VOS_TRUE != pstPppInfo->bEhrpdUser) && (pstPppInfo->pL2tpPara == NULL) )
    {
        pstPppInfo->pL2tpPara = (VOID*)PPP_Malloc(sizeof(L2TP_SESSIONPARA_S));

        /* 申请失败则什么也不做,报给L2TP时表明不带预协商结果即可,
           因此不用对申请失败进行处理 */
    }

    if (pstPppInfo->pL2tpPara != NULL)
    {
        /* 清零 */
        PPP_MemSet(pstPppInfo->pL2tpPara, 0, sizeof(L2TP_SESSIONPARA_S));

        /*代码自检longsirui*/
        ((L2TP_SESSIONPARA_S*)pstPppInfo->pL2tpPara)->usAuthenType = L2TP_NONE;
    }
 #endif

    /* 通知上层LCP down */
    /* 这本来可以不用做,只是为了保证安全而做一些多余的判断 */
    PPP_Core_NotifyUperLcpDown(pstPppInfo);

    /* 修改配置信息指针  *(pstPppInfo->pstUsedConfigInfo) = *(pstTopPppInfo->pstConfigInfo) ;*/

    /* deleted by gxf 20030220
       在PPP_InitConfigInfo中完成配置信息初始化 */

    /*(VOID)VOS_MemCpy((VOID*)(pstPppInfo->pstUsedConfigInfo),(VOID*)(pstTopPppInfo->pstConfigInfo),sizeof(PPPCONFIGINFO_S));*/

    PPP_LCP_ReceiveEventFromCore(pstPppInfo->pstLcpInfo, (VOS_UINT32)PPP_EVENT_FSM_OPEN, NULL );
    PPP_LCP_ReceiveEventFromCore(pstPppInfo->pstLcpInfo, (VOS_UINT32)PPP_EVENT_FSM_UP, NULL );

    /* 改变协商阶段 */
    pstPppInfo->usPhase = (VOS_UINT16)PPP_PHASE_ESTABLISH;
    PPP_DBG_OK_CNT(PPP_PHOK_1037);

    return;
}

/****************************************************************************
* CREATE DATE  ：2000/04/04                                                 *
* CREATED BY   ：Deng Yi Ou                                                 *
* FUNCTION     ：PPP协商阶段转换到Authenticate阶段                          *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstPppInfo:PPP控制块指针                                   *
* OUTPUT       ：                                                           *
* RETURN       ：0                                                          *
* CALLED BY    ：PPP_Core_ReceiveEventFromProtocol                          *
****************************************************************************/
VOID PPP_Core_AuthenticatePhase(PPPINFO_S *pstPppInfo)
{
    PPPLCPINFO_S *pstLcpInfo = VOS_NULL_PTR;

    PPPC_INFO_LOG("\r\n---Into PPP_Core_AuthenticatePhase---\r\n");

    if (NULL == pstPppInfo)
    {
        return;
    }

    pstLcpInfo = (PPPLCPINFO_S*)(pstPppInfo->pstLcpInfo);
    if (NULL == pstLcpInfo)
    {
        return;
    }

    if ((pstLcpInfo->stGotOptions.neg_upap) || (pstLcpInfo->stHisOptions.neg_upap)) /*是否使用PAP验证*/
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1038);
        if (pstPppInfo->pstPapInfo == NULL)
        {
            /*申请PAP控制块*/
            PPP_GETPAPADDR(pstPppInfo->pstPapInfo , pstPppInfo->ulRPIndex);
        }

        if (pstPppInfo->pstPapInfo != NULL)
        {
            PPP_MemSet((void *)pstPppInfo->pstPapInfo, 0, sizeof(PPPPAPINFO_S));
            PPP_PAP_Init(pstPppInfo);        /* 初始化PAP控制块 */
            /* 向PAP发送消息,触发PAP开始协商 */
            if (pstLcpInfo->stGotOptions.neg_upap)
            {
                /*Server端PAP UP */
                PPP_PAP_ReceiveEventFromCore(pstPppInfo, PAP_EVENT_SERVERLOWERUP, NULL );
            }

            if (pstLcpInfo->stHisOptions.neg_upap)
            {
                /*Client端PAP UP */
                PPP_PAP_ReceiveEventFromCore(pstPppInfo, PAP_EVENT_CLIENTLOWERUP, NULL );
            }

            /* 改变协商阶段 */
            pstPppInfo->usPhase = (VOS_UINT16)PPP_PHASE_AUTHENTICATE;
        }
        else
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_415);
            /* 添加调试信息 */
            /*申请PAP控制块失败,向内核报验证失败*/
            PPP_Core_ReceiveEventFromProtocol(pstPppInfo, (VOS_UINT32)PPP_EVENT_PAPFAILED, NULL);
            return;
        }
    }

    if ((pstLcpInfo->stGotOptions.neg_chap) || (pstLcpInfo->stHisOptions.neg_chap)) /* 是否使用CHAP验证 */
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1039);
        if (pstPppInfo->pstChapInfo == NULL)
        {
            /*申请CHAP控制块*/
            PPP_GETCHAPADDR(pstPppInfo->pstChapInfo, pstPppInfo->ulRPIndex);
        }

        if (pstPppInfo->pstChapInfo != NULL)
        {
            PPP_MemSet((void *)pstPppInfo->pstChapInfo, 0, sizeof(PPPCHAPINFO_S));
            PPP_CHAP_Init(pstPppInfo);        /* 初始化CHAP控制块 */
            /* 向CHAP发送消息,触发CHAP开始协商 */
            /*changed by chenmin00265046，手机不会主动要求协商chap鉴权，由网络来决定是否进行chap鉴权,所以由stHisOptions来判断是否要鉴权*/
            if (pstLcpInfo->stHisOptions.neg_chap)
            {
                if (0 == pstPppInfo->bPppClient)
                {
                    /* Server 端CHAP UP */
                    PPP_CHAP_ReceiveEventFromCore(pstPppInfo, CHAP_EVENT_SERVERLOWERUP, NULL );
                }
                else
                {
                    /* Client 端CHAP UP ,Add by chenmin 00265046*/
                    PPP_CHAP_ReceiveEventFromCore(pstPppInfo, CHAP_EVENT_CLIENTLOWERUP, NULL );
                }
            }

            /* 改变协商阶段 */
            pstPppInfo->usPhase = (VOS_UINT16)PPP_PHASE_AUTHENTICATE;
        }
        else
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_416);
            /*申请CHAP控制块失败,向内核报验证失败*/
            /* 添加调试信息 */
            PPP_Core_ReceiveEventFromProtocol(pstPppInfo, (VOS_UINT32)PPP_EVENT_CHAPFAILED, NULL);
            return;
        }
    }
#if VRP_MODULE_LINK_PPP_EAP == VOS_YES
    /* 是否使用EAP验证 */
    if ((pstLcpInfo->stGotOptions.neg_eap) || (pstLcpInfo->stHisOptions.neg_eap))
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1040);
        if (NULL == pstPppInfo->pstEapInfo)
        {
            /*申请EAP控制块*/
            PPP_GETEAPADDR(pstPppInfo->pstEapInfo, pstPppInfo->ulRPIndex);
        }

        if (pstPppInfo->pstEapInfo != NULL)
        {
            /* 初始化EAP控制块 */
            PPPC_EAP_Init(pstPppInfo);

            /* 改变协商阶段 */
            pstPppInfo->usPhase = (VOS_UINT16)PPP_PHASE_AUTHENTICATE;
        }
        else
        {
            /* 申请EAP控制块失败,向内核报验证失败 */
            /* 添加调试信息 */
            PPP_DBG_ERR_CNT(PPP_PHERR_417);
            PPP_Core_ReceiveEventFromProtocol(pstPppInfo, (VOS_UINT32)PPP_EVENT_EAPFAILED, NULL);
            return;
        }
    }
#endif

    /********ZFZ/CM:是否应使用判断PAP控制块是与否申请成功标志 */
    return;
}

/****************************************************************************
* CREATE DATE  ：2000/04/04                                                 *
* CREATED BY   ：Deng Yi Ou                                                 *
* FUNCTION     ：CCP主动协商                                                *
* MODIFY DATE  ：modified by gxf for GGSN80 20030220                        *
* INPUT        ：pstPppInfo:PPP控制块指针                                   *
* OUTPUT       ：                                                           *
* RETURN       ：0                                                          *
* CALLED BY    ：PPP_Core_NetworkPhase                                      *
****************************************************************************/
VOID ppp_Core_CcpInitiativeNego(PPPINFO_S *pstPppInfo)
{
    if (NULL == pstPppInfo)
    {
        return;
    }

    PPPC_INFO_LOG("\r\n---Into ppp_Core_CcpInitiativeNego---\r\n");

#if (VRP_MODULE_LINK_PPP_CCP == VRP_YES)

    /* 在此出判断是否应该协商CCP, 软参BIT1385控制是否主动协商 */
    if((1 == SOFTPARA_BIT1385) && (VOS_OK == PPP_CheckCcpLimit()))
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1041);
        PPP_ClearCCPCB(pstPppInfo->pstCcpInfo);
        PPP_GETCCPADDR(pstPppInfo->pstCcpInfo, pstPppInfo->ulRPIndex);
        if (pstPppInfo->pstCcpInfo)
        {
            PPP_MemSet((void *)pstPppInfo->pstCcpInfo, 0, sizeof(PPP_CCP_INFO_S));

            /* 初始化CCP控制块 */
            PPP_CCP_init(pstPppInfo);

            if (0 == ((PPP_CCP_INFO_S*)((PPPINFO_S*)pstPppInfo)->pstCcpInfo)->ulCcpTimeoutID)
            {
                /*设置CCP超时定时器*/
                (VOS_VOID)VOS_StartRelTimer((HTIMER)&(((PPP_CCP_INFO_S*)((PPPINFO_S*)pstPppInfo)->pstCcpInfo)->ulCcpTimeoutID),
                                            MID_PPPC,
                                            ((PPP_CCP_INFO_S*)((PPPINFO_S*)pstPppInfo)->pstCcpInfo)->ulTimeOutTime,
                                            pstPppInfo->ulRPIndex,
                                            PPPC_CCP_TIMEOUT_TIMER,
                                            VOS_TIMER_LOOP,
                                            VOS_TIMER_PRECISION_0);
            }
            else
            {
                PPP_DBG_ERR_CNT(PPP_PHERR_418);
            }

            /* 向CCP发送消息,触发CCP开始协商 */
            PPP_CCP_ReceiveEventFromCore(pstPppInfo->pstCcpInfo, (VOS_UINT32)PPP_EVENT_FSM_OPEN, NULL );
            PPP_CCP_ReceiveEventFromCore(pstPppInfo->pstCcpInfo, (VOS_UINT32)PPP_EVENT_FSM_UP, NULL );
        }
        else
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_419);
            PPP_Debug_CoreEvent(pstPppInfo, PPP_LOG_ERROR, "Malloc CCP CB Err!!");
        }
    }
    else
    {
        PPPC_INFO_LOG("\r\nppp_Core_CcpInitiativeNego: SOFTPARA_BIT1385 = %lu", SOFTPARA_BIT1385);
    }
#endif/* (VRP_MODULE_LINK_PPP_CCP == VRP_YES) */
    return ;
}

/*****************************************************************************
 函 数 名  : PPP_Core_NetworkPhase
 功能描述  : PPP阶段Lcp和Auth完成后转入网络阶段，通知USM
 输入参数  : PPPINFO_S *pstPppInfo
             UCHAR* pMsg
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月30日
    作    者   : luofang
    修改内容   : 新生成函数

*****************************************************************************/
VOID PPP_Core_NetworkPhase(PPPINFO_S *pstPppInfo,UCHAR* pMsg)
{
    UCHAR ucIsRenego = 0;
    USM_PPP_LINKUP_RESULT_S stMsg ={0};  /* PPP Link up 通知USM的消息结构体 */
    VOS_UINT8               ucPdnId;
    VOS_UINT32              ulRet;


    if (NULL == pstPppInfo)
    {
        /*打印调试信息；*/
        return;
    }

    PPPC_INFO_LOG("\r\n PPP_Core_NetworkPhase. \r\n");

    /* CCP主动协商 */
    ppp_Core_CcpInitiativeNego(pstPppInfo);

    if (VOS_FALSE == pstPppInfo->bEhrpdUser)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1042);
        /* 如果是客户端模式，不申请地址，直接进入IPCP */
        if (PPP_CLIENT_TRUE == pstPppInfo->bPppClient)
        {
            PPP_DBG_OK_CNT(PPP_PHOK_1043);
            _PPP_Core_NetworkPhase(pstPppInfo);
            return;
        }

        /*............................................*/
        /*.............重协商处理流程.................*/
        if (pstPppInfo->ucIpCapability & PDSN_PPP_IPTYE_IPV4 )
        {
            if ((pstPppInfo->ulPeerIPAddr) || (PPP_USERTYPE_MIP == pstPppInfo->bIPTech))
            {
                PPP_DBG_OK_CNT(PPP_PHOK_1044);
                /*重协商，有地址或为CMIP，直接进入IPCP协商*/
                PPP_Ipv4cp_Proc(pstPppInfo);
                ucIsRenego = VOS_TRUE;
            }
            else
            {
                PPP_DBG_OK_CNT(PPP_PHOK_1045);
                pstPppInfo->bReNego = 0;
            }
        }

        if (pstPppInfo->ucIpCapability & PDSN_PPP_IPTYE_IPV6 )
        {
            if (VOS_OK == PPP_ipv6_addr_check(pstPppInfo->usPeerIPv6Addr))
            {
                PPP_DBG_OK_CNT(PPP_PHOK_1046);
                /*重协商，有地址，进入IPV6CP协商*/
                PPP_Ipv6cp_Proc(pstPppInfo);
                ucIsRenego = VOS_TRUE;
            }
            else
            {
                PPP_DBG_OK_CNT(PPP_PHOK_1047);
                pstPppInfo->bReNegoV6 = 0;
            }
        }

        if(ucIsRenego)
        {
            PPP_DBG_OK_CNT(PPP_PHOK_1048);
            return;
        }
    }
    else
    {
        /* EHRPD用户无论是否重协商都通知USM，由USM再通知各PDN进行VSNCP重协商 */
        PPP_DBG_OK_CNT(PPP_PHOK_1049);

        ulRet = PPPC_1XHrpdGetPdnId((VOS_UINT16)pstPppInfo->ulRPIndex, &ucPdnId);
        if (VOS_OK != ulRet)
        {
            PPPC_WARNING_LOG("Get Pdn id fail.");
            return;
        }
        /* PPP发起VSNCP协商 */
        PPP_VSNCP_NotifyVSNCPStart(pstPppInfo, ucPdnId);
    }

    /*Auth鉴权成功终结模式 或者重协商没IP地址，则通知USM*/
    /* 填充发给USM的消息结构体 */
    stMsg.pucMsg = pMsg;
    stMsg.ulRpIndex = pstPppInfo->ulRPIndex;
    stMsg.usDomainIndex = pstPppInfo->usCDBIndex;
    stMsg.usVirtualDomainIndex = pstPppInfo->usVirtualDomainIdx;
    VOS_MemCpy(stMsg.aucNAI, pstPppInfo->ucNAI, NAI_NAME_LEN + 1);

    if (VOS_OK != USM_NotifyPhaseResultFunc(pstPppInfo->ulRPIndex,
                                            E_USM_MSGTYPE_PPP2USM_SETUP,
                                            (UCHAR *)&stMsg))
    {
        PPP_SET_REL_CODE(pstPppInfo, AM_RELCODE_PPP_LCP_NEGONAK);
        PPP_LCP_NegotiationDown(pstPppInfo->pstLcpInfo);
        PPP_DBG_ERR_CNT(PPP_PHERR_420);
        return;
    }

    return;
}

VOS_UINT32 AAA_IPValidCheck(VOS_UINT32 ulAddr)
{
    ulAddr = VOS_HTONL(ulAddr);

    if ((ulAddr == AAA_INADDR_BROADCAST) || (ulAddr == AAA_INADDR_ANY)
        || ((ulAddr & AAA_IN_CLASSA_NET) == AAA_INADDR_LOOP))
    {
        return VOS_ERR;
    }

    if (AAA_IN_CLASSA( ulAddr ))
    {
        if (((ulAddr & AAA_IN_CLASSA_NET) == 0) || ((ulAddr & AAA_IN_CLASSA_HOST) == 0)
            || ((ulAddr & AAA_IN_CLASSA_HOST) == AAA_IN_CLASSA_HOST))
        {
            return VOS_ERR;
        }

        return VOS_OK;
    }

    if (AAA_IN_CLASSB( ulAddr ))
    {
        if (((ulAddr & AAA_IN_CLASSB_NET) == 0) || ((ulAddr & AAA_IN_CLASSB_HOST) == 0)
            || ((ulAddr & AAA_IN_CLASSB_HOST) == AAA_IN_CLASSB_HOST))
        {
            return VOS_ERR;
        }

        return VOS_OK;
    }

    if (AAA_IN_CLASSC( ulAddr ))
    {
        if (((ulAddr & AAA_IN_CLASSC_NET) == 0) || ((ulAddr & AAA_IN_CLASSC_HOST) == 0)
            || ((ulAddr & AAA_IN_CLASSC_HOST) == AAA_IN_CLASSC_HOST))
        {
            return VOS_ERR;
        }

        return VOS_OK;
    }

    return VOS_ERR;
}

/****************************************************************************
* CREATE DATE  ：2000/04/04                                                 *
* CREATED BY   ：Deng Yi Ou                                                 *
* FUNCTION     ：PPP协商阶段转换到Network阶段                               *
* MODIFY DATE  ：modified by gxf for GGSN80 20030220                        *
* INPUT        ：pstPppInfo:PPP控制块指针                                   *
* OUTPUT       ：                                                           *
* RETURN       ：0                                                          *
* CALLED BY    ：PPP_Core_ReceiveEventFromProtocol                          *
****************************************************************************/
VOID _PPP_Core_NetworkPhase(PPPINFO_S *pstPppInfo)
{

    if (NULL == pstPppInfo)
    {
        return;
    }

    PPPC_INFO_LOG("\r\n---Into _PPP_Core_NetworkPhase---\r\n");

    if (PPP_CLIENT_TRUE == pstPppInfo->bPppClient) /* 再生场景PDSN不支持 */
    {
        PPPC_INFO_LOG1("PPPC mode is client. %d", pstPppInfo->ucIpCapability);
        if ((pstPppInfo->pstIpV6cpInfo == NULL)
            && (pstPppInfo->ucIpCapability & PDSN_PPP_IPTYE_IPV6))
        {
            PPP_GETIPV6CPADDR(pstPppInfo->pstIpV6cpInfo, pstPppInfo->ulRPIndex);
            if (NULL == pstPppInfo->pstIpV6cpInfo)
            {
                PPPC_ERROR_LOG("Malloc IPV6CP CB Err!!");
                return;
            }

            PPP_MemSet((void *)pstPppInfo->pstIpV6cpInfo, 0, sizeof(PPPIPV6CPINFO_S));

            PPP_IPV6CP_Init(pstPppInfo, pstPppInfo->usIpv6Addr, pstPppInfo->usPeerIPv6Addr);
            PPP_IPV6CP_ReceiveEventFromCore(pstPppInfo->pstIpV6cpInfo, (VOS_UINT32)PPP_EVENT_FSM_OPEN, NULL );
            PPP_IPV6CP_ReceiveEventFromCore(pstPppInfo->pstIpV6cpInfo, (VOS_UINT32)PPP_EVENT_FSM_UP, NULL );
        }
        if ((pstPppInfo->pstIpcpInfo == NULL)
            && (pstPppInfo->ucIpCapability & PDSN_PPP_IPTYE_IPV4))
        {
            PPP_GETIPCPADDR(pstPppInfo->pstIpcpInfo, pstPppInfo->ulRPIndex);
            if (NULL == pstPppInfo->pstIpcpInfo)
            {
                PPPC_ERROR_LOG("Malloc IPCP CB Err!!");
                return;
            }

            PPP_MemSet((void *)pstPppInfo->pstIpcpInfo, 0, sizeof(PPPIPCPINFO_S));

            PPP_IPCP_Init(pstPppInfo, pstPppInfo->ulIPAddr, pstPppInfo->ulPeerIPAddr);
            PPP_IPCP_ReceiveEventFromCore(pstPppInfo->pstIpcpInfo, (VOS_UINT32)PPP_EVENT_FSM_OPEN, NULL );
            PPP_IPCP_ReceiveEventFromCore(pstPppInfo->pstIpcpInfo, (VOS_UINT32)PPP_EVENT_FSM_UP, NULL );
        }
    }
    else
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1051);
        if ( pstPppInfo->ucIpCapability & PDSN_PPP_IPTYE_IPV4 )
        {
            if ((VOS_OK == AAA_IPValidCheck(pstPppInfo->ulPeerIPAddr))
                || (PPP_USERTYPE_MIP == pstPppInfo->bIPTech))
            {
                PPP_DBG_OK_CNT(PPP_PHOK_1052);
                PPP_Ipv4cp_Proc(pstPppInfo);
            }
        }

        /* 对于IPV6地址获取后的IPCP流程处理 */
        if ((pstPppInfo->ucIpCapability & PDSN_PPP_IPTYE_IPV6))
        {
            if (VOS_OK == PPP_ipv6_addr_check(pstPppInfo->usPeerIPv6Addr))
            {
                PPP_DBG_OK_CNT(PPP_PHOK_1053);
                PPP_Ipv6cp_Proc(pstPppInfo);
            }
        }
    }

 #if (VRP_MODULE_LINK_PPP_CCP == VRP_YES)
    /* 在此出判断是否应该协商CCP, 软参BIT307控制是否主动协商 */
    if((1 == SOFTPARA_BIT1385) && (VOS_OK == PPP_CheckCcpLimit()))
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1054);
        PPP_ClearCCPCB(pstPppInfo->pstCcpInfo);
        PPP_GETCCPADDR(pstPppInfo->pstCcpInfo, pstPppInfo->ulRPIndex);
        if (pstPppInfo->pstCcpInfo)
        {
            PPP_MemSet((void *)pstPppInfo->pstCcpInfo, 0, sizeof(PPP_CCP_INFO_S));

            /* 初始化CCP控制块 */
            PPP_CCP_init(pstPppInfo);

            if (0 == ((PPP_CCP_INFO_S*)((PPPINFO_S*)pstPppInfo)->pstCcpInfo)->ulCcpTimeoutID)
            {
                /*设置CCP超时定时器*/
                (VOS_VOID)VOS_StartRelTimer((HTIMER)&(((PPP_CCP_INFO_S*)((PPPINFO_S*)pstPppInfo)->pstCcpInfo)->ulCcpTimeoutID),
                                            MID_PPPC,
                                            ((PPP_CCP_INFO_S*)((PPPINFO_S*)pstPppInfo)->pstCcpInfo)->ulTimeOutTime,
                                            pstPppInfo->ulRPIndex,
                                            PPPC_CCP_TIMEOUT_TIMER,
                                            VOS_TIMER_LOOP,
                                            VOS_TIMER_PRECISION_0);
            }
            else
            {
                PPP_DBG_ERR_CNT(PPP_PHERR_421);
            }
            PPP_DBG_OK_CNT(PPP_PHOK_1055);

            /* 向CCP发送消息,触发CCP开始协商 */
            PPP_CCP_ReceiveEventFromCore(pstPppInfo->pstCcpInfo, (VOS_UINT32)PPP_EVENT_FSM_OPEN, NULL );
            PPP_CCP_ReceiveEventFromCore(pstPppInfo->pstCcpInfo, (VOS_UINT32)PPP_EVENT_FSM_UP, NULL );
        }
        else
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_422);
            PPP_Debug_CoreEvent(pstPppInfo, PPP_LOG_ERROR, "Malloc CCP CB Err!!");
        }
    }
 #endif/* (VRP_MODULE_LINK_PPP_CCP == VRP_YES) */

    /* 改变协商阶段 */
    pstPppInfo->usPhase = (VOS_UINT16)PPP_PHASE_NETWORK;

    return;
}

/****************************************************************************
* CREATE DATE  ：2000/04/04                                                 *
* CREATED BY   ：Deng Yi Ou                                                 *
* FUNCTION     ：PPP协商阶段转换到Terminate阶段                             *
* MODIFY DATE  ：modified by gxf for GGSN80 20030220                        *
* INPUT        ：pstPppInfo:PPP控制块指针                                   *
* OUTPUT       ：                                                           *
* RETURN       ：0                                                          *
* CALLED BY    ：PPP_Core_ReceiveEventFromProtocol                          *
****************************************************************************/
VOID PPP_Core_TerminatePhase(PPPINFO_S *pstPppInfo)
{

    PPPC_INFO_LOG("\r\n---Into PPP_Core_TerminatePhase---\r\n");

    if (NULL == pstPppInfo)
    {
        return;
    }

    //SNMP_TerminatePhaseProc(pstPppInfo);

     /* 通知上层LCP down */
    PPP_Core_NotifyUperLcpDown(pstPppInfo);

    pstPppInfo->bAuthServer = VRP_NO;
    pstPppInfo->bAuthClient = VRP_NO;

    /* 改变协商阶段 */
    pstPppInfo->usPhase = (VOS_UINT16)PPP_PHASE_TERMINATE;

    return;
}

/****************************************************************************
* CREATE DATE  ：2000/04/04                                                 *
* CREATED BY   ：Deng Yi Ou                                                 *
* FUNCTION     ：通知上层:LCP down                                          *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstPppInfo:PPP控制块指针                                   *
* OUTPUT       ：                                                           *
* RETURN       ：0                                                          *
* CALLED BY    ：PPP_Core_TerminatePhase、PPP_Core_EstablishPhase           *
****************************************************************************/
VOID PPP_Core_NotifyUperLcpDown(PPPINFO_S *pstPppInfo)
{
    PPPC_INFO_LOG("\r\n---Into PPP_Core_NotifyUperLcpDown---\r\n");

    /*判断输入参数的有效性*/
    if (NULL == pstPppInfo)
    {
        return;
    }


    if (pstPppInfo->pstPapInfo)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1056);
        /* 向PAP发送消息,结束本次协商 */
        PPP_PAP_ReceiveEventFromCore(pstPppInfo, (VOS_UINT32)PAP_EVENT_LOWERDOWN, NULL );

        /* 删除控制块 */
        if (NULL != ((PPPPAPINFO_S*)pstPppInfo->pstPapInfo)->pstAAAAuthReqMsg)
        {
            (VOID)PPP_Free(((PPPPAPINFO_S*)pstPppInfo->pstPapInfo)->pstAAAAuthReqMsg);
            ((PPPPAPINFO_S*)pstPppInfo->pstPapInfo)->pstAAAAuthReqMsg = NULL;
        }

        /*释放控制块占用标记*/
        ((PPPPAPINFO_S*)pstPppInfo->pstPapInfo)->ucUsed = 0;
        pstPppInfo->pstPapInfo = NULL;
    }

    if (pstPppInfo->pstChapInfo)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1057);
        /* 向CHAP发送消息,结束本次协商 */
        PPP_CHAP_ReceiveEventFromCore(pstPppInfo, CHAP_EVENT_LOWERDOWN, NULL );

        /* 删除控制块 */
        if (NULL != ((PPPCHAPINFO_S*)pstPppInfo->pstChapInfo)->pstAAAAuthReqMsg)
        {
            (VOID)PPP_Free(((PPPCHAPINFO_S*)pstPppInfo->pstChapInfo)->pstAAAAuthReqMsg);
            ((PPPCHAPINFO_S*)pstPppInfo->pstChapInfo)->pstAAAAuthReqMsg = NULL;
        }
        /*释放控制块占用标记*/
        ((PPPCHAPINFO_S*)pstPppInfo->pstChapInfo)->ucUsed = 0;
        pstPppInfo->pstChapInfo = NULL;
    }

    if (pstPppInfo->pstEapInfo)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1058);
        /* 向EAP发送消息,结束本次协商 */
        PPPC_EAP_ReceiveEventFromCore(pstPppInfo, EAP_EVENT_LOWERDOWN, NULL);

        pstPppInfo->pstEapInfo = NULL;
    }


    PPP_Core_NotifyNcpDown( pstPppInfo );
    return;
}

/*add by houzhipeng*/

/****************************************************************************
* CREATE DATE  ：2000/04/04                                                 *
* CREATED BY   ：Deng Yi Ou                                                 *
* FUNCTION     ：通知 NCP down                                              *
* MODIFY DATE  ：modified by gxf for GGSN80 20030220                        *
* INPUT        ：pstPppInfo:PPP控制块指针                                   *
* OUTPUT       ：                                                           *
* RETURN       ：0                                                          *
* CALLED BY    ：                                                           *
****************************************************************************/
VOID PPP_Core_NotifyNcpDown(PPPINFO_S *pstPppInfo)
{
    PPPC_INFO_LOG("\r\n---Into PPP_Core_NotifyNcpDown---\r\n");

    if (NULL == pstPppInfo)
    {
        return;
    }

    if (pstPppInfo->pstIpcpInfo)
    {
        PPPIPCPINFO_S *pstIpcpInfo = VOS_NULL_PTR;
        PPP_DBG_OK_CNT(PPP_PHOK_1059);

        pstIpcpInfo = (PPPIPCPINFO_S *)(pstPppInfo->pstIpcpInfo);
        if (pstIpcpInfo->stFsm.ulTimeOutID)
        {
            (VOID)VOS_StopRelTimer(&(pstIpcpInfo->stFsm.ulTimeOutID));
            pstIpcpInfo->stFsm.ulTimeOutID = 0;
        }

        pstPppInfo->bIpcpNoToPDN= VOS_TRUE;   /* 1时不通知PDN */

        /* 向IPCP发送消息,结束本次协商 */
        PPP_IPCP_ReceiveEventFromCore(pstPppInfo->pstIpcpInfo, (VOS_UINT32)PPP_EVENT_FSM_DOWN, NULL );
        //PPP_IPCP_ReceiveEventFromCore(pstPppInfo->pstIpcpInfo, (VOS_UINT32)PPP_EVENT_FSM_CLOSE, NULL );

        pstPppInfo->bIpcpNoToPDN= VOS_FALSE;

        /* 判断如果bEnableVJComp为1，则VJ用户数减1 */
        if (1 == ((PPPCONFIGINFO_S*)pstPppInfo->pstConfigInfo)->bEnableVJComp)
        {
            ((PPPCONFIGINFO_S*)pstPppInfo->pstConfigInfo)->bEnableVJComp = 0;
        }


        /*释放控制块占用标记,正常情况下处理close事件是控制块已经释放，这里增加一下保护 */
        if ( NULL != pstPppInfo->pstIpcpInfo )
        {
            if ( VOS_NULL != ((PPPIPCPINFO_S*)(pstPppInfo->pstIpcpInfo))->pucIpv4cpMsg )
            {
                (VOID)PPP_Free(((PPPIPCPINFO_S*)(pstPppInfo->pstIpcpInfo))->pucIpv4cpMsg);
                ((PPPIPCPINFO_S*)(pstPppInfo->pstIpcpInfo))->pucIpv4cpMsg = NULL;
                ((PPPIPCPINFO_S*)(pstPppInfo->pstIpcpInfo))->ulIpv4cpLen = 0;
            }

            ((PPPIPCPINFO_S*)pstPppInfo->pstIpcpInfo)->ucUsedFlag = 0;
            pstPppInfo->pstIpcpInfo = NULL;
        }
    }
/* BEGIN: Added for PN:PDSN融合 by wangyong 00138171, 2013/1/21 */
    if (pstPppInfo->bEhrpdUser)
    {
        PPP_VSNCP_StopRetransmitTimer();
        PPPC_ExtractPdnInfoFromHeadNode();
        PPP_DBG_OK_CNT(PPP_PHOK_1060);
    }
/* END:   Added for PN:PDSN融合 by wangyong 00138171, 2013/1/21 */
    if (pstPppInfo->pstIpV6cpInfo)
    {
        PPPIPV6CPINFO_S *pstIpv6cpInfo = VOS_NULL_PTR;
        PPP_DBG_OK_CNT(PPP_PHOK_1061);

        pstIpv6cpInfo = (PPPIPV6CPINFO_S *)(pstPppInfo->pstIpV6cpInfo);
        if (pstIpv6cpInfo->stFsm.ulTimeOutID)
        {
            (VOID)VOS_StopRelTimer(&(pstIpv6cpInfo->stFsm.ulTimeOutID));
            pstIpv6cpInfo->stFsm.ulTimeOutID = 0;
        }

        pstPppInfo->bIpv6cpNoToPDN = VOS_TRUE;   /* 1时不通知PDN */

        /* 向IPCP发送消息,结束本次协商 */
        PPP_IPV6CP_ReceiveEventFromCore(pstPppInfo->pstIpV6cpInfo, (VOS_UINT32)PPP_EVENT_FSM_DOWN, NULL );
        //PPP_IPV6CP_ReceiveEventFromCore(pstPppInfo->pstIpV6cpInfo, (VOS_UINT32)PPP_EVENT_FSM_CLOSE, NULL );

        /*标志置完之后将标志置回*/
        pstPppInfo->bIpv6cpNoToPDN = VOS_FALSE;

        /*正常情况下处理close事件是控制块已经释放，这里增加一下保护*/
        if ( pstPppInfo->pstIpV6cpInfo )
        {
            /* 释放缓存消息内存 */
            if ( VOS_NULL != ((PPPIPV6CPINFO_S*)pstPppInfo->pstIpV6cpInfo)->pucIpv6cpMsg )
            {
                (VOID)PPP_Free(((PPPIPV6CPINFO_S*)pstPppInfo->pstIpV6cpInfo)->pucIpv6cpMsg);
                ((PPPIPV6CPINFO_S*)pstPppInfo->pstIpV6cpInfo)->pucIpv6cpMsg = NULL;
                ((PPPIPV6CPINFO_S*)pstPppInfo->pstIpV6cpInfo)->ulIpv6cpLen = 0;
            }

            if (0 != ((PPPIPV6CPINFO_S*)pstPppInfo->pstIpV6cpInfo)->ucUsedFlag)
            {
                /* 删除控制块 */
                ((PPPIPV6CPINFO_S*)pstPppInfo->pstIpV6cpInfo)->ucUsedFlag = 0;
                PPP_DBG_OK_CNT(PPP_PHOK_1062);
            }
            pstPppInfo->pstIpV6cpInfo = NULL;
        }
    }


 #if (VRP_MODULE_LINK_PPP_CCP == VRP_YES)
    if (pstPppInfo->pstCcpInfo)
    {
        /*add by huzhiyong 删除重传定时器2002/03/08*/
        PPP_CCP_INFO_S * pstCcpInfo;
        PPP_DBG_OK_CNT(PPP_PHOK_1063);

        pstCcpInfo = (PPP_CCP_INFO_S *)(pstPppInfo->pstCcpInfo);
        if (pstCcpInfo->stFsm.ulTimeOutID)
        {
            (VOID)VOS_StopRelTimer(&(pstCcpInfo->stFsm.ulTimeOutID));
            pstCcpInfo->stFsm.ulTimeOutID = 0;
        }

        /* 向CCP发送消息,结束本次协商 */
        PPP_CCP_ReceiveEventFromCore(pstPppInfo->pstCcpInfo, (VOS_UINT32)PPP_EVENT_FSM_DOWN, NULL );
        PPP_CCP_ReceiveEventFromCore(pstPppInfo->pstCcpInfo, (VOS_UINT32)PPP_EVENT_FSM_CLOSE, NULL );
        PPP_ClearCCPCB(pstPppInfo->pstCcpInfo);
    }
 #endif

    return;
}


/****************************************************************************
* CREATE DATE  ：2000/04/04                                                 *
* CREATED BY   ：Deng Yi Ou                                                 *
* FUNCTION     ：生成Magic Number                                           *
* MODIFY DATE  ：                                                           *
* INPUT        ：                                                           *
* OUTPUT       ：                                                           *
* RETURN       ：0                                                          *
* CALLED BY    ：PPP_LCP_addci、PPP_LCP_nakci、PPP_LCP_reqci                *
****************************************************************************/
VOS_UINT32 PPP_GetMagicNumber()
{
    VOS_UINT32                               ulRetVal = 0;
    VOS_UINT32                          ulSeed;
    VOS_UINT32                          ulRandVal;


#ifdef PPPC_ST
    static VOS_UINT32 ulMagicNumber = 0x78724c47;/*add by chenmin00265046, 为了用例, 魔数设为定值，需删除*/
#endif
    while (ulRetVal == 0)
    {
        /* 获取时间tick数作为种子 */
        ulSeed = VOS_GetTick();
        VOS_SetSeed(ulSeed);

        /* 生成随机数 */
        ulRandVal   = VOS_Rand(0xffffffff);
        ulRetVal    = ulRandVal + ulSeed;

#ifdef PPPC_ST
        ulRetVal = ++ulMagicNumber;/*add by chenmin00265046, 为了用例, 魔数设为定值，需删除*/
#endif
    }

    return ulRetVal;
}

VOID ImsiToString( A11_IMSI_S stImsi ,UCHAR*szTemp)
{
    UCHAR ucLoop;

    UCHAR ucTemp;

    UCHAR* szImsi = (UCHAR*)&stImsi;

    if ( szTemp == NULL)
    {
        return;
    }

    VOS_MemSet(szTemp, 0, 16);

    for( ucLoop = 1; ucLoop <= 15; ucLoop++ )
    {
        if( ucLoop % 2 == 0 )

            ucTemp = (UCHAR)( szImsi[ucLoop/2] & 0x0f );

        else

            ucTemp = (UCHAR)( szImsi[ucLoop/2] >> 4);

        if( ucTemp > 9)

            break;

        szTemp[ucLoop-1] = (UCHAR)(ucTemp + '0');
    }

    szTemp[ucLoop-1] = 0;

    return ;
}

VOS_CHAR*  VOS_StrCat( VOS_CHAR * pcdest, const VOS_CHAR * pcsrc )
{
    return strcat(pcdest, pcsrc);
}

/*****************************************************************************
 函 数 名  : PPP_Core_AuthUp
 功能描述  : LCP up和验证通过后调用此函数,判断是该进入Network阶段
             还是该进入Authenticate阶段(或只是留在Authenticate阶段)
 输入参数  : PPPINFO_S *pstPppInfo
             AAA_AUTHRSP_S* pMsg
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月30日
    作    者   : luofang
    修改内容   : 新生成函数

*****************************************************************************/
VOID PPP_Core_AuthUp(PPPINFO_S *pstPppInfo, UCHAR* pMsg)
{

    PPPCONFIGINFO_S *pstConfigInfo = NULL;


    VOS_UINT32 ulUserNameLen = 0;
    VOS_UINT32 ulDomainNameLen = 0;

    if (NULL == pstPppInfo)
    {
        return;
    }
    pstConfigInfo = pstPppInfo->pstConfigInfo;

    if ((pstPppInfo->bAuthServer == VRP_NO) && (pstPppInfo->bAuthClient == VRP_NO))
    {
        /* PDSN用户如果没有携带NAI,需要根据IMSI和域名构造NAI */
        if ((VOS_FALSE == pstPppInfo->bEhrpdUser) && (0 == VOS_StrLen((VOS_CHAR *)(pstPppInfo->ucNAI))))
        {
            {
                PPP_DBG_OK_CNT(PPP_PHOK_1064);
                /* 由于增加了fa，这样导致，设备配置鉴权时会被拒绝从而domain里的内容为空，流程无法正常进行，因此有了这一段 */
                M_SET_NEWPHASE(pstPppInfo, PPP_SNMP_PERF_PHASE_AUTH);

                pstPppInfo->usCDBIndex = 0;
                pstPppInfo->usVirtualDomainIdx = 0;
                VOS_StrCpy((CHAR*)pstConfigInfo->ucDomainName, (CHAR *)(g_pstApnByIndex[0].aucAPN));

                /* 根据LOCK标志判断是否允许激活，如是被LOCK，则不允许它激活，返回协商失败 */
                if (PPP_DOMAIN_LOCKED == g_pstApnByIndex[pstPppInfo->usCDBIndex].ucLock)
                {
                    HSGW_EmsTraceByRpIndex(pstPppInfo->ulRPIndex, HSGW_EMS_MODULE_PPP, EMS_PPP_8);
                    PPP_DBG_ERR_CNT(PPP_PHERR_423);
                    PPP_SET_REL_CODE(pstPppInfo, AM_RELCODE_PPP_LCP_NEGONAK);
                    PPP_LCP_NegotiationDown(pstPppInfo->pstLcpInfo);
                    return;
                }

                /* 构造NAI */
                ImsiToString( *((A11_IMSI_S*)&pstPppInfo->stIMSI), ( UCHAR* )pstPppInfo->ucNAI);
                VOS_StrCat((CHAR *)pstPppInfo->ucNAI, "@");

                ulUserNameLen = VOS_StrLen((CHAR*)pstPppInfo->ucNAI);
                ulDomainNameLen = VOS_StrLen((CHAR *)pstPppInfo->pstUsedConfigInfo->ucDomainName);

                /* 构造NAI长度不能越界 */
                if ((ulUserNameLen + ulDomainNameLen) >= NAI_NAME_LEN)
                {
                    HSGW_EmsTraceByRpIndex(pstPppInfo->ulRPIndex, HSGW_EMS_MODULE_PPP, EMS_PPP_9);
                    SNMP_SetFailReason(pstPppInfo, FSM_ALARM_AUTH_ERROR_ACCOUNT);
                    PPP_SET_REL_CODE(pstPppInfo, AM_RELCODE_PPP_LCP_NEGONAK);
                    PPP_LCP_NegotiationDown(pstPppInfo->pstLcpInfo);
                    return;
                }
                VOS_StrCat((CHAR *)pstPppInfo->ucNAI, (const char*)(pstPppInfo->pstUsedConfigInfo->ucDomainName));
            }
        }

        M_SET_NEWPHASE(pstPppInfo, PPP_SNMP_PERF_PHASE_NET);

        PPP_DBG_OK_CNT(PPP_PHOK_1065);
        /* 改变协商阶段 */
        pstPppInfo->usPhase = (VOS_UINT16)PPP_PHASE_NETWORK;
        PPP_Core_NetworkPhase(pstPppInfo, (UCHAR*)pMsg);
    }
    else
    {
        if (pstPppInfo->usPhase != (VOS_UINT16)PPP_PHASE_AUTHENTICATE)
        {
            PPP_DBG_OK_CNT(PPP_PHOK_1066);
            M_SET_NEWPHASE(pstPppInfo, PPP_SNMP_PERF_PHASE_AUTH);

            PPP_Core_AuthenticatePhase(pstPppInfo);
        }
        PPP_DBG_OK_CNT(PPP_PHOK_1067);
    }

    return;
}


/*lint -restore */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
