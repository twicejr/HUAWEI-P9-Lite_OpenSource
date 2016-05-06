/************************************************************************
*                                                                      *
*                             ipv6cp.c                                   *
*                                                                      *
*  Project Code:       IPV6CP .1                                          *
*  Create Date:        2009/12/29                                      *
*  Author:             z00129699                                      *
*  Modify Date:                                                        *
*  Document:                                                           *
*  Function:           PPP的IPv6CP协议模块                               *
*  Others:                                                             *
*----------------------------------------------------------------------*
*                                                                      *
*----------------------------------------------------------------------*
*                                                                      *
*   这个文件定义了IPV6CP协议模块的全部接口函数和内部处理函数             *
*                                                                      *
************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "PsLib.h"
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
#define         THIS_FILE_ID            PS_FILE_ID_PPPC_IPV6CP_C


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
/* IPV6CP回调函数数据结构 */
PPPFSMCALLBACK_S g_stIpv6cpCallbacks =
{
    /* 动作：协商报文处理 */
    PPP_IPV6CP_resetci,   /* 根据配置信息设置协商初始值 */
    PPP_IPV6CP_cilen,      /* 我要发送的request报文长度 */
    PPP_IPV6CP_addci,     /* 组织协商报文 */
    PPP_IPV6CP_ackci,      /* 处理对方的ack报文 */
    PPP_IPV6CP_nakci,      /* 处理对方的nak报文 */
    PPP_IPV6CP_rejci,       /* 处理对方的reject报文 */
    PPP_IPV6CP_reqci,      /* 处理对方的request报文 */
    NULL,                            /* extcode函数,处理协议特有的报文.
                                              IPCP没有特殊类型报文,因此不提供这个函数*/

    /* 事件：协议转入了终止状态 */
    PPP_IPV6CP_up,           /* 协议up */
    PPP_IPV6CP_down,       /* 协议暂时down,马上要重新协商.
                                                与finished的区别是:对于PPPOE、DDR等的情况，
                                                不用通知下层拆除链路 */
    PPP_IPV6CP_finished,   /* 协议结束，通知下层:拆除链路.对于IPCP,则是通知
                                                 LCP:如果没有其他网络层协议,则LCP可以down掉*/
    PPP_IPV6CP_starting,   /* tls(This-Layer-Started)动作中，通知下层:我准
                                               备好了重新协商,如可能,请发一个up事件.
                                               协议对这个动作没有具体规定,可以不实现*/

    /* 子协议信息 */
    "IPV6CP"                       /* 子协议名 */
};

/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*lint -save -e958 */
/*lint -e572*/
/****************************************************************************
* CREATE DATE  ：2000/04/04                                                 *
* CREATED BY   ：Deng Yi Ou                                                 *
* FUNCTION     ：IPCP接收外部事件.事件包括：Up、Down、Open、Close           *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstPppInfo:PPP控制块指针                                   *
*                ulCmd:命令字,可以为如下值:                                 *
*                      PPPFSMLOWERDOWN:下层Down                             *
*                      PPPFSMLOWERUP:下层Up                                 *
*                      PPPFSMOPEN:Open事件                                  *
*                      PPPFSMCLOSE:Down事件                                 *
*                pPara:事件的参数,为NULL                                    *
* OUTPUT       ：                                                           *
* RETURN       ：NULL                                                       *
* CALLED BY    ：PPP_Core_ReceiveEventFromShell、PPP_Core_RejectProtocol    *
 修改历史      :
  1.日    期   : 2009年12月24日
    作    者   : zhaichao
    修改内容   : 针对ipv6cp进行修改
****************************************************************************/
VOID PPP_IPV6CP_ReceiveEventFromCore (VOID *pstIpcpInfo, VOS_UINT32 ulCmd, char *pPara)
{
    PPPFSM_S *pstFsm;
    PPPIPV6CPINFO_S *pstIpv6cpInfo = (PPPIPV6CPINFO_S *)pstIpcpInfo;
    PPPINFO_S *pstPppInfo = NULL;


    PPPC_INFO_LOG1("\r\n---Into PPP_IPV6CP_ReceiveEventFromCore ulCmd %d---\r\n", ulCmd);
    if (NULL == pstIpcpInfo)
    {
        return;
    }

    pstPppInfo = pstIpv6cpInfo->pstPppInfo;
    if ( NULL == pstPppInfo )
    {
        return;
    }
    if (PPP_EVENT_FSM_OPEN == ulCmd)
    {
        /* ipv6性能统计,IPv6CP协商尝试次数 */
        PPP_DBG_OK_CNT(PPP_PHOK_901);
        PPPC_INFO_LOG("\r\n PPP_IPV6CP_ReceiveEventFromCore,IPV6_PerfStatistic Attempt: enter!");

        A11_OM_PerfStatisticPCFUnit((VOS_UINT32)PERF_TYPE_PCF_PPPC_IPV6CP_NEGO_REQ_NUM, pstPppInfo->ulPcfIP);
    }

    pstFsm = &(((PPPIPV6CPINFO_S*)pstIpcpInfo)->stFsm);

    PPP_FSM_ReceiveEvent(pstFsm, ulCmd, pPara);

    return;
}

/****************************************************************************
* CREATE DATE  ：2000/04/05                                                 *
* CREATED BY   ：Deng Yi Ou                                                 *
* FUNCTION     ：IPCP接收报文                                               *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstIpcpInfo:IPCP控制块                                     *
*                pHead:存放报文内存的头指针,应负责释放这段内存              *
*                pPacket:报文头位置                                         *
*                ulLen:报文长度                                             *
* OUTPUT       ：                                                           *
* RETURN       ：0                                                          *
* CALLED BY    ：PPP_Core_ReceivePacketFromShell                            *
 修改历史      :
  1.日    期   : 2009年12月24日
    作    者   : zhaichao
    修改内容   : 针对ipv6cp进行修改
****************************************************************************/
VOID PPP_IPV6CP_ReceivePacket (VOID *pstIpV6cpInfo, UCHAR* pHead, UCHAR* pPacket, VOS_UINT32 ulLen)
{
    PPPFSM_S                           *pstFsm;
    PPPINFO_S                          *pstPppInfo;

    pstFsm = &(((PPPIPV6CPINFO_S*)pstIpV6cpInfo)->stFsm);

    /*入参需保证非空*/
    /*lint -e413*/
    pstPppInfo  = (PPPINFO_S *)PPPC_MEMBER2PARENT(PPPINFO_S, pstIpV6cpInfo);
    PPP_FSM_ReceivePacket(pstFsm, pHead, pPacket, ulLen, pstPppInfo->ulRPIndex);

    return;
}

/****************************************************************************
* CREATE DATE  ：                                                *
* CREATED BY   ：                                               *
* FUNCTION     ：确定IPv6CP需要协商那些参数,在IPv6CP初始化时进行                  *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstFsm    :状态机                                          *
* OUTPUT       ：                                                           *
* RETURN       ：0                                                          *
* CALLED BY    ：状态机中执行tls动作的宏PPP_FSM_tls                         *
 修改历史      :
  1.日    期   : 2009年12月24日
    作    者   : zhaichao
    修改内容   : 针对ipv6cp进行修改
****************************************************************************/
VOID PPP_IPV6CP_resetci(PPPFSM_S *pstFsm)
{
    PPPINFO_S           *pstPppInfo;
    PPPRENOGOINFO       *pstPppRenegoInfo;
    PPPIPV6CPINFO_S     *pstInfo;
    PPPCONFIGINFO_S     *pstConfig;
    PPP_IPV6CP_OPTION_S *pstAllowOptions, *pstWantOptions;
    PPP_IPV6CP_OPTION_S *pstGotOptions, *pstHisOptions;

    pstInfo = (PPPIPV6CPINFO_S *)pstFsm->pProtocolInfo;
    pstPppInfo = pstInfo->pstPppInfo;
    pstConfig = pstPppInfo->pstUsedConfigInfo;

    pstAllowOptions = &(pstInfo->stAllowOptions);
    pstWantOptions = &(pstInfo->stWantOptions);
    pstGotOptions = &(pstInfo->stGotOptions);
    pstHisOptions = &(pstInfo->stHisOptions);

    /* pstWantOptions中ouraddr和hisaddr在PPP_IPCP_Init中已经初始化 */

    /* 各参数的缺省值 */
    pstWantOptions->neg_addr  = 1;
    pstWantOptions->req_addr  = 1;
    pstWantOptions->old_addrs = 0;
    pstWantOptions->neg_vj = 0;
    pstWantOptions->vj_protocol  = PPP_VJ_COMP;
    pstWantOptions->maxslotindex = MAX_STATES - 1; /* really max index */
    pstWantOptions->cflag = 0;
    pstWantOptions->neg_dnsaddr0  = 0;
    pstWantOptions->req_dnsaddr0  = 0;
    pstWantOptions->neg_nbnsaddr0 = 0;
    pstWantOptions->req_nbnsaddr0 = 0;
    pstWantOptions->neg_dnsaddr1     = 0;
    pstWantOptions->req_dnsaddr1     = 0;
    pstWantOptions->neg_nbnsaddr1    = 0;
    pstWantOptions->req_nbnsaddr1    = 0;
    pstWantOptions->accept_dnsaddr0  = 0;
    pstWantOptions->accept_dnsaddr1  = 0;
    pstWantOptions->accept_nbnsaddr0 = 0;
    pstWantOptions->accept_nbnsaddr1 = 0;

    pstAllowOptions->req_addr = 1;
    pstAllowOptions->neg_dnsaddr0  = 0;
    pstAllowOptions->req_dnsaddr0  = 0;
    pstAllowOptions->neg_nbnsaddr0 = 0;
    pstAllowOptions->req_nbnsaddr0 = 0;
    pstAllowOptions->neg_dnsaddr1     = 0;
    pstAllowOptions->req_dnsaddr1     = 0;
    pstAllowOptions->neg_nbnsaddr1    = 0;
    pstAllowOptions->req_nbnsaddr1    = 0;
    pstAllowOptions->accept_dnsaddr0  = 0;  /* modified by gxf 20030414 不接受对方的DNS */
    pstAllowOptions->accept_dnsaddr1  = 0;  /* modified by gxf 20030414 不接受对方的DNS */
    pstAllowOptions->accept_nbnsaddr0 = 0;
    pstAllowOptions->accept_nbnsaddr1 = 0;

    *pstGotOptions = *pstWantOptions;

    /* pstHisOptions 清零 */
    PPP_MemSet((VOID*)pstHisOptions, 0, sizeof(PPP_IPV6CP_OPTION_S));

    pstFsm->ulTimeOutTime = pstConfig->ulNegTimeOut;

    pstPppRenegoInfo = pstPppInfo->pstPppRenegoInfo;
    if (pstPppRenegoInfo && pstPppRenegoInfo->ucIpV6cpFlag)
    {
        VOS_MemCpy((VOID*)pstGotOptions, (VOID*)&pstPppRenegoInfo->stIpcpV6Options, sizeof(PPP_IPV6CP_OPTION_S));
        *pstWantOptions = *pstGotOptions;
    }

    return;
}

/****************************************************************************
* CREATE DATE  ：2000/04/05                                                 *
* CREATED BY   ：Deng Yi Ou                                                 *
* FUNCTION     ：计算要发送的Config Request报文数据部分长度                 *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstFsm: 状态机                                             *
* OUTPUT       ：                                                           *
* RETURN       ：Config Request报文长度                                     *
* CALLED BY    ：PPP_FSM_SendConfigReq                                      *
 修改历史      :
  1.日    期   : 2009年12月24日
    作    者   : zhaichao
    修改内容   : 针对ipv6cp进行修改
****************************************************************************/
VOS_UINT16 PPP_IPV6CP_cilen(PPPFSM_S *pstFsm)
{
    PPP_IPV6CP_OPTION_S *pstGotOptions;

    pstGotOptions = &(((PPPIPV6CPINFO_S*)pstFsm->pProtocolInfo)->stGotOptions);

    /*
     * NB: we only ask for one of CHAP and UPAP, even if we will
     * accept either.
     */
    return (VOS_UINT16)(IPV6CP_LENCIADDR(pstGotOptions->neg_addr, pstGotOptions->old_addrs) +
                   IPV6CP_LENCIVJ(pstGotOptions->neg_vj));
}

/****************************************************************************
* CREATE DATE  ：2000/04/05                                                 *
* CREATED BY   ：Deng Yi Ou                                                 *
* FUNCTION     ：组织一个Config Request报文内容                             *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstFsm: 状态机                                             *
*                pPacket:报文头位置                                         *
* OUTPUT       ：                                                           *
*                pPacket:组装好的报文                                       *
* RETURN       ：                                                           *
* CALLED BY    ：PPP_FSM_SendConfigReq                                      *
 修改历史      :
  1.日    期   : 2009年12月24日
    作    者   : zhaichao
    修改内容   : 针对ipv6cp进行修改
****************************************************************************/
VOID PPP_IPV6CP_addci(PPPFSM_S *pstFsm, UCHAR *pPacket)
{
    PPP_IPV6CP_OPTION_S *pstGotOptions;

    pstGotOptions = &(((PPPIPV6CPINFO_S*)pstFsm->pProtocolInfo)->stGotOptions);

    ADDCIADDRV6(IPV6CP_CI_ADDR,
              pstGotOptions->neg_addr,
              pstGotOptions->old_addrs,
              pstGotOptions->OurV6InId,
              pstGotOptions->HisV6InId
    );
    (VOS_VOID)pPacket;
    return;
}

/****************************************************************************
* CREATE DATE  ：2000/04/05                                                 *
* CREATED BY   ：Deng Yi Ou                                                 *
* FUNCTION     ：处理收到的Config ACK报文                                   *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstFsm: 状态机                                             *
*                pPacket:报文头位置                                         *
*                ulLen:  报文长度                                           *
* OUTPUT       ：                                                           *
* RETURN       ：VOS_OK,合法的ACK报文;VOS_ERR:非法的ACK报文                 *
* CALLED BY    ：                                     *
 修改历史      :
  1.日    期   : 2009年12月25日
    作    者   : zhaichao
    修改内容   : 针对ipv6cp协议重新进行设计
****************************************************************************/
VOS_UINT16 PPP_IPV6CP_ackci(PPPFSM_S *pstFsm, UCHAR *pPacket, VOS_UINT32 ulLen)
{
    PPP_IPV6CP_OPTION_S *pstGotOptions;
    UCHAR cilen, citype;
    VOS_UINT16 ciusINid[4] = {0};
    VOS_UINT32 ulResult1 ,ulResult2;

    pstGotOptions = &(((PPPIPV6CPINFO_S*)pstFsm->pProtocolInfo)->stGotOptions);

    /*
     * CIs must be in exactly the same order that we sent...
     * Check packet length and CI length at each step.
     * If we find any deviations, then this packet is bad.
     */

    /* We allow the configuration length is 0. */
    if (ulLen == 0)
    {
        return VOS_OK;
    }

    /*lint -e63*/
    ACKCIADDRV6(IPV6CP_CI_ADDR,
              pstGotOptions->neg_addr,
              pstGotOptions->old_addrs,
              pstGotOptions->OurV6InId,
              pstGotOptions->HisV6InId
    );
    /*lint +e63*/

    ulResult1= PPP_ipv6_intfid_check(pstGotOptions->OurV6InId,IPV6_ADDR_LEN);
    ulResult2 = (VOS_UINT32)VOS_MemCmp((VOS_VOID *)ciusINid, (VOS_VOID *)pstGotOptions->OurV6InId, IPV6_ADDR_LEN);

    /*我们分配的pdsn接口id无效或者ack中的id同我们分配的接口id不一致*/
    /*lint -e801*/
    if ((ulResult2 != VOS_OK) || (ulResult1))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_220);
        goto bad;
    }

    /*
     * If there are any remaining CIs, then this packet is bad.
     */
    if (ulLen != 0)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_221);
        goto bad;
    }

    return VOS_OK;

bad:
    PPP_Debug_Error(pstFsm, PPP_LOG_WARNING, "Ipcp_ackci: received bad Ack!");
    return VOS_ERR;
    /*lint +e801*/
}

/****************************************************************************
* CREATE DATE  ：2000/04/05                                                 *
* CREATED BY   ：Deng Yi Ou                                                 *
* FUNCTION     ：处理收到的Config Nak报文                                   *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstFsm: 状态机                                             *
*                pPacket:报文头位置                                         *
*                ulLen:  报文长度                                           *
* OUTPUT       ：                                                           *
* RETURN       ：VOS_OK,合法的NAK报文;VOS_ERR:非法的NAK报文                 *
* CALLED BY    ：PPP_FSM_ReceiveConfNakRej                                  *
 修改历史      :
  1.日    期   : 2009年12月25日
    作    者   : zhaichao
    修改内容   : 针对ipv6cp在ipv4基础上进行修改
****************************************************************************/
VOS_UINT16 PPP_IPV6CP_nakci(PPPFSM_S *pstFsm, UCHAR *pPacket, VOS_UINT32 ulLen)
{
    PPP_IPV6CP_OPTION_S *pstGotOptions, *pstWantOptions;
    PPP_IPV6CP_OPTION_S stNoOption;  /* 被对方no掉的选项 */
    PPP_IPV6CP_OPTION_S stTryOption; /* 尝试与对方协商的选项 */

    UCHAR citype, cilen, *next;
    VOS_UINT16 ciaddr1[IPV6_ADDR_LEN_INTER], ciaddr2[IPV6_ADDR_LEN_INTER];
    VOS_UINT32 ulResult1 = VOS_ERR;
    VOS_UINT32 ulResult2 = VOS_ERR;

    pstGotOptions  = &(((PPPIPV6CPINFO_S*)pstFsm->pProtocolInfo)->stGotOptions);
    pstWantOptions = &(((PPPIPV6CPINFO_S*)pstFsm->pProtocolInfo)->stWantOptions);

    PPP_MemSet(ciaddr1, 0, sizeof(VOS_UINT16) * IPV6_ADDR_LEN_INTER);
    PPP_MemSet((VOID*)(&stNoOption), 0, sizeof(PPP_IPV6CP_OPTION_S));
    stTryOption = *pstGotOptions;

    /*
     * Any Nak'd CIs must be in exactly the same order that we sent.
     * Check packet length and CI length at each step.
     * If we find any deviations, then this packet is bad.
     */

    /*
     * Accept the peer's idea of {our,his} address, if different
     * from our idea, only if the accept_{local,remote} flag is set.
     */
    ulResult1 = PPP_ipv6_intfid_check(pstWantOptions->OurV6InId, IPV6_ADDR_LEN);
    NAKCIADDRV6(IPV6CP_CI_ADDR, neg_addr, pstGotOptions->old_addrs,
              if (VOS_OK == ulResult1)/*我们分配的id有效*/
              {
                  stTryOption.neg_addr = 0;
              }

              ulResult2 = PPP_ipv6_intfid_check(ciaddr1,IPV6_ADDR_LEN);

              if (ulResult1 && (!ulResult2)) /*我们分配的id无效并且nak中的id有效*/
              { /* Do we know our address? */
                  VOS_MemCpy((void*)(stTryOption.OurV6InId),(void *)ciaddr1,IPV6_ADDR_LEN);
              }
    );

    /*
     * Accept the peer's value of maxslotindex provided that it
     * is less than what we asked for.  Turn off slot-ID compression
     * if the peer wants.  Send old-style compress-type option if
     * the peer wants.
     */


    /*
     * There may be remaining CIs, if the peer is requesting negotiation
     * on an option that we didn't include in our request packet.
     * If they want to negotiate about IP addresses, we comply.
     * If they want us to ask for compression, we refuse.
     */
    /*lint -e801*/
    while (ulLen > IPCP_CILEN_VOID)
    {
        PPP_GETCHAR(citype, pPacket);
        PPP_GETCHAR(cilen, pPacket);
        if (cilen < 2)/*增加对非法报文配置项的处理*/
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_222);
            goto bad;
        }

        ulLen = (VOS_UINT32)(ulLen - cilen);
        if ((LONG)ulLen < 0)
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_223);
            goto bad;
        }

        next = pPacket + cilen - 2;

        switch (citype)
        {
            case IPCP_CI_COMPRESSTYPE:
                if (pstGotOptions->neg_vj || stNoOption.neg_vj
               || ((cilen != IPCP_CILEN_VJ) && (cilen != IPCP_CILEN_COMPRESS)))
                {
                    goto bad;
                }

                stNoOption.neg_vj = 1;
                break;
            case IPV6CP_CI_ADDR:
                if (pstGotOptions->neg_addr || stNoOption.neg_addr || (cilen != IPCP_CILEN_ADDR))
                {
                    PPP_DBG_ERR_CNT(PPP_PHERR_224);
                    goto bad;
                }

                PPP_GETCHARPTR(ciaddr1, pPacket,IPV6_ADDR_LEN);
                ulResult1 = PPP_ipv6_intfid_check(ciaddr1,IPV6_ADDR_LEN);
                ulResult2 = PPP_ipv6_intfid_check(pstWantOptions->OurV6InId, IPV6_ADDR_LEN);
                if ((!ulResult1) && (ulResult2))
                {
                    VOS_MemCpy((void*)(stTryOption.OurV6InId),(void *)ciaddr1,IPV6_ADDR_LEN);
                    stTryOption.neg_addr = 1;
                }

                stNoOption.neg_addr = 1;
                break;
            default:
                break;
        }

        pPacket = next;
    }

    /* If there is still anything left, this packet is bad. */
    if (ulLen != 0)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_225);
        goto bad;
    }

    /*
     * OK, the Nak is good.  Now we can update state.
     */
    if (pstFsm->ucState != (LONG)PPP_STATE_OPENED)
    {
        *pstGotOptions = stTryOption;
    }

    return VOS_OK;

bad:
    PPP_Debug_Error(pstFsm, PPP_LOG_WARNING, "Ipcp_nakci: received bad Nak!");
    return VOS_ERR;
    /*lint +e801*/
}

/****************************************************************************
* CREATE DATE  ：2000/04/05                                                 *
* CREATED BY   ：Deng Yi Ou                                                 *
* FUNCTION     ：处理收到的Config Reject报文                                *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstFsm: 状态机                                             *
*                pPacket:报文头位置                                         *
*                ulLen:  报文长度                                           *
* OUTPUT       ：                                                           *
* RETURN       ：VOS_OK,合法的reject报文;VOS_ERR:非法的reject报文           *
* CALLED BY    ：PPP_FSM_ReceiveConfNakRej                                  *
修改日期:2009-12-26
修改原因 ipv6cp特性做出适应性调整
修改人 z00129699
****************************************************************************/
VOS_UINT16 PPP_IPV6CP_rejci(PPPFSM_S *pstFsm, UCHAR *pPacket, VOS_UINT32 ulLen)
{
    PPP_IPV6CP_OPTION_S *pstGotOptions;
    VOS_UINT16 ciaddr[IPV6_ADDR_LEN_INTER];
    PPP_IPV6CP_OPTION_S stTryOption;      /* options to request next time */
    UCHAR cilen = 0;

    pstGotOptions = &(((PPPIPV6CPINFO_S*)pstFsm->pProtocolInfo)->stGotOptions);
    stTryOption = *pstGotOptions;

    /*lint -e821*/
    /*lint -e63*/
    REJCIADDRV6(IPV6CP_CI_ADDR,
                neg_addr,
                pstGotOptions->old_addrs,
                pstGotOptions->OurV6InId,
                pstGotOptions->HisV6InId
               );
    /*lint +e63*/
    /*lint +e821*/

    /*
     * If there are any remaining CIs, then this packet is bad.
     */
    /*lint -e801*/
    if (ulLen != 0)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_226);
        goto bad;
    }
    /*lint +e801*/

    /*
     * Now we can update state.
     */
    if (pstFsm->ucState != (LONG)PPP_STATE_OPENED)
    {
        *pstGotOptions = stTryOption;
    }

    return VOS_OK;

bad:
    PPP_Debug_Error(pstFsm, PPP_LOG_WARNING, "Ipcp_rejci: received bad Reject!");

    return VOS_ERR;
}

/*****************************************************************************
 函 数 名  : PPP_IPCP_IsSip
 功能描述  : 判断IPCP请求包中是否有IP选项：有，是SIP，否则是MIP
 输入参数  : UCHAR *pPacket
             VOS_UINT32 *pulLen
 输出参数  : 无
 返 回 值  : 1: SIP  0: MIP
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2003年4月15日
    作    者   : gxf
    修改内容   : 新生成函数
 修改历史      :
    日    期   : 2009年12月24日
    作    者   : ZHAICHAO
    修改内容   : 根据ipv6cp协议修改地址类型
*****************************************************************************/
UCHAR PPP_IPV6CP_IsSip(UCHAR *pPacket, VOS_UINT32 *pulLen)
{
    UCHAR *p;              /* Pointer to current and next CIs */
    VOS_UINT16 cilen, citype;   /* Parsed len, type */
    VOS_UINT32 l = *pulLen;      /* Length left */

    p = pPacket;

    while (l)
    {
        if ((l < 2)           /* Not enough data for CI header or */
           || (p[1] < 2)    /*  CI length too small or */
           || (p[1] > l))
        {
            /*  CI length too big? */
            PPP_DBG_OK_CNT(PPP_PHOK_902);
            return 0;
        }

        PPP_GETCHAR(citype, p);     /* Parse CI type */
        PPP_GETCHAR(cilen, p);      /* Parse CI length */
        l -= cilen;                 /* Adjust remaining length */
        p += (cilen - 2);           /* Step to next CI */

        if (citype == IPV6CP_CI_ADDR)
        {
            PPP_DBG_OK_CNT(PPP_PHOK_903);
            return 1;
        }
    }

    return 0;
}

/****************************************************************************
* CREATE DATE  ：2000/04/05                                                 *
* CREATED BY   ：Deng Yi Ou                                                 *
* FUNCTION     ：分析收到的config Request报文                               *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstFsm: 状态机                                             *
*                pPacket:报文头位置                                         *
*                pulLen: 报文长度                                           *
* OUTPUT       ：                                                           *
*                pPacket:要发给对方的报文(ACK或NAK或REJ)内容                *
*                pulLen: 要发给对方的报文的长度                             *
* RETURN       ：发给对方的报文类型:CONFACK、CONFNAK或者CONFREJ             *
* CALLED BY    ：
 修改历史      :
  1.日    期   : 2009年12月24日
    作    者   : zhaichao
    修改内容   : 针对ipv6cp在ipv4上进行修改
****************************************************************************/
UCHAR PPP_IPV6CP_reqci(PPPFSM_S *pstFsm, UCHAR *pPacket, VOS_UINT32 *pulLen)
{
    PPP_IPV6CP_OPTION_S *pstWantOptions;
    PPP_IPV6CP_OPTION_S *pstGotOptions;
    PPP_IPV6CP_OPTION_S *pstHisOptions;
    PPPINFO_S *pstPppInfo = NULL;

    UCHAR *cip, *next, *p;     /* Pointer to current and next CIs */
    VOS_UINT16 cilen, citype;   /* Parsed len, type */
    VOS_UINT16 ciaddr1[IPV6_ADDR_LEN_INTER]; /*interface id*/
    UCHAR rc = CONFACK;     /* Final packet return code */
    UCHAR orc;          /* Individual option return code */
    UCHAR *ucp = pPacket;       /* Pointer to current output char */
    long l = (long)*pulLen;       /* Length left */
    UCHAR ucresultaaa;
    UCHAR ucRetUsr;

    pstWantOptions  = &(((PPPIPV6CPINFO_S*)pstFsm->pProtocolInfo)->stWantOptions);
    pstGotOptions = &(((PPPIPV6CPINFO_S*)pstFsm->pProtocolInfo)->stGotOptions);
    pstHisOptions = &(((PPPIPV6CPINFO_S*)pstFsm->pProtocolInfo)->stHisOptions);

    /*
     * Reset all his options.
     */
    PPP_MemSet(ciaddr1, 0, sizeof(VOS_UINT16) * IPV6_ADDR_LEN_INTER);
    PPP_MemSet(pstHisOptions, 0, sizeof(PPP_IPV6CP_OPTION_S));

    /* 判断SIP/MIP */
    if (!PPP_IPV6CP_IsSip(pPacket, pulLen))
    {
    }

    /*
     * Process all his options.
     */
    if (l == 0)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_904);
        return rc;
    }

    next = pPacket;

    while (l)
    {
        orc = CONFACK;          /* Assume success */
        cip = p = next;         /* Remember begining of CI */
        if ((l < 2)               /* Not enough data for CI header or */
           || (p[1] < 2)    /*  CI length too small or */
           || (p[1] > l))
        /*lint -e801*/
        {
            /*  CI length too big? */
            orc   = CONFREJ;    /* Reject bad CI */
            cilen = (VOS_UINT16)l;          /* Reject till end of packet */
            l = 0;          /* Don't loop again */
            PPP_DBG_OK_CNT(PPP_PHOK_905);
            goto endswitch;
        }
        /*lint +e801*/

        PPP_GETCHAR(citype, p);     /* Parse CI type */
        PPP_GETCHAR(cilen, p);      /* Parse CI length */
        l    -= cilen;      /* Adjust remaining length */
        next += cilen;          /* Step to next CI */

        switch (citype)
        {
            case IPV6CP_CI_ADDR:

                if (!pstWantOptions->neg_addr
                     || (cilen != IPV6CP_CILEN_ADDR))
                {
                    /* Check CI length */
                    orc = CONFREJ;  /* Reject CI */
                    PPP_DBG_ERR_CNT(PPP_PHERR_227);
                    break;
                }

                PPP_GETCHARPTR(ciaddr1, p, IPV6_ADDR_LEN);/* Parse source address (his) */

                /*接口id获取规则
                1） AAA下发
                2） 终端IPCPV6协商请求中携带
                3） PDSN配置
                */
                ucresultaaa = (UCHAR)PPP_ipv6_intfid_check(pstWantOptions->HisV6InId, IPV6_ADDR_LEN);
                pstHisOptions->neg_addr = 1;
                if (VOS_OK == ucresultaaa)/*aaa下发了接口id*/
                {
                    /*收到接口id同aaa下发的接口id相同则回复ack，否则将aaa下发的接口id通过nak发送给对方*/
                    if ((ciaddr1[0] == pstWantOptions->HisV6InId[0])
                        &&(ciaddr1[1] == pstWantOptions->HisV6InId[1])
                        &&(ciaddr1[2] == pstWantOptions->HisV6InId[2])
                        &&(ciaddr1[3] == pstWantOptions->HisV6InId[3]))
                    {
                        pstGotOptions->neg_addr = 1;
                        VOS_MemCpy(pstHisOptions->HisV6InId, ciaddr1, IPV6_ADDR_LEN);
                        VOS_MemCpy(pstGotOptions->HisV6InId, ciaddr1, IPV6_ADDR_LEN);
                        pstPppInfo = (PPPINFO_S*)pstFsm->pPppInfo;
                        if ( NULL!= pstPppInfo )
                        {
                            VOS_MemCpy((void *)(pstPppInfo->usPeerIPv6Addr + 4), (void*)ciaddr1, IPV6_ADDR_LEN);
                        }
                    }
                    else
                    {
                        PPP_DBG_OK_CNT(PPP_PHOK_906);
                        orc = CONFNAK;
                        pstGotOptions->neg_addr = 1;
                        PPP_DECPTR(IPV6_ADDR_LEN, p);
                        PPP_PUTCHARPTR(pstWantOptions->HisV6InId, p,IPV6_ADDR_LEN);
                    }
                }
                else /*aaa 没有下发接口id 则使用本地配置*/
                {
                    /* 用户携带并且合法 */
                    ucRetUsr = (UCHAR)PPP_ipv6_intfid_check(ciaddr1, IPV6_ADDR_LEN);
                    if (VOS_OK == ucRetUsr)
                    {
                        pstGotOptions->neg_addr = 1;
                        VOS_MemCpy(pstHisOptions->HisV6InId, ciaddr1, IPV6_ADDR_LEN);
                        VOS_MemCpy(pstGotOptions->HisV6InId, ciaddr1, IPV6_ADDR_LEN);

                        VOS_MemCpy((void *)(pstWantOptions->HisV6InId), (void*)ciaddr1, IPV6_ADDR_LEN);
                        pstPppInfo = (PPPINFO_S*)pstFsm->pPppInfo;
                        if ( NULL!= pstPppInfo )
                        {
                            VOS_MemCpy((void *)(pstPppInfo->usPeerIPv6Addr + 4), (void*)ciaddr1, IPV6_ADDR_LEN);
                        }

                    }
                    else
                    {
                        PPP_DBG_OK_CNT(PPP_PHOK_907);
                        orc = CONFNAK;
                        pstGotOptions->neg_addr = 1;
                        PPP_DECPTR(IPV6_ADDR_LEN, p);
                        PPP_PUTCHARPTR(pstWantOptions->ConfigV6InId, p,IPV6_ADDR_LEN);

                        VOS_MemCpy((void *)(pstWantOptions->HisV6InId), (void*)pstWantOptions->ConfigV6InId, IPV6_ADDR_LEN);
                    }

                }
                break;
            default:
                PPP_DBG_ERR_CNT(PPP_PHERR_228);
                orc = CONFREJ;
                break;
        }

endswitch:
        PPPC_INFO_LOG3("\r\n PPP_IPV6CP_reqci: orc=%d , rc=%d, l = %d!",
                 orc, rc , l);

        if ((orc == CONFACK)          /* Good CI */
           && (rc != CONFACK))
        {
            /*  but prior CI wasnt? */
            continue;
        }                   /* Don't send this one */

        if (orc == CONFNAK)
        {
            /* Nak this CI? */
            if (rc == CONFREJ)
            {
                /* Rejecting prior CI? */
                continue;
            }                   /* Don't send this one */
            if (rc == CONFACK)
            {
                /* Ack'd all prior CIs? */
                rc  = CONFNAK;  /* Not anymore... */
                ucp = pPacket;      /* Backup */
            }
        }

        if ((orc == CONFREJ)          /* Reject this CI */
           && (rc != CONFREJ))
        {
            /*  but no prior ones? */
            rc  = CONFREJ;
            ucp = pPacket;          /* Backup */
        }

        /* Need to move CI? */
        if (ucp != cip)
        {
            (VOID)VOS_MemCpy(ucp, cip, (VOS_UINT32)cilen);
        }                                              /* Move it */

        /* Update output pointer */
        PPP_INCPTR(cilen, ucp);
    }

    *pulLen = (VOS_UINT32)(ucp - pPacket);           /* Compute output length */
    return (rc);            /* Return final code */
}

/****************************************************************************
* CREATE DATE  ：2000/04/05                                                 *
* CREATED BY   ：Deng Yi Ou                                                 *
* FUNCTION     ：状态机up的处理函数                                         *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstFsm:状态机                                              *
* OUTPUT       ：                                                           *
* RETURN       ：0                                                          *
* CALLED BY    ：是回调函数，由状态机tlu动作宏(PPP_FSM_tlu)调用             *
 修改历史      :
  1.日    期   : 2009年12月26日
    作    者   : zhaichao
    修改内容   : 针对ipv6cp在ipv4上进行修改而来
****************************************************************************/
VOID PPP_IPV6CP_up(PPPFSM_S *pstFsm)
{
    VOS_UINT32 ulAccept;

    /* IPCP协商结果是否可以接收 */
    ulAccept = PPP_IPV6CP_UpResetCi((PPPINFO_S *)pstFsm->pPppInfo);

    if (ulAccept == VOS_OK)
    {
        /* 协商结果可以接受,向内核发送Ipcp Up事件 */
        PPP_Core_ReceiveEventFromProtocol((PPPINFO_S *)pstFsm->pPppInfo,
                                          (LONG)PPP_EVENT_IPV6CPUP,
                                          NULL);
    }
    else
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_229);
        /* 协商结果不可接受,结束协商 */
        PPP_IPV6CP_NegotiationDown(pstFsm->pProtocolInfo);
    }
}

/****************************************************************************
* CREATE DATE  ：2000/04/05                                                 *
* CREATED BY   ：Deng Yi Ou                                                 *
* FUNCTION     ：状态机down的处理函数                                       *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstFsm:状态机                                              *
* OUTPUT       ：                                                           *
* RETURN       ：0                                                          *
* CALLED BY    ：是回调函数，由状态机tld动作宏(PPP_FSM_tld)调用             *
 修改历史      :
  1.日    期   : 2009年12月26日
    作    者   : zhaichao
    修改内容   : 针对ipv6cp在ipv4上进行修改而来

****************************************************************************/
VOID PPP_IPV6CP_down(PPPFSM_S *pstFsm)
{
    /* 重传定时器在PPP_FSM_tld中已经删除 */

    PPP_Core_ReceiveEventFromProtocol(((PPPINFO_S *)pstFsm->pPppInfo),
                                      (LONG)PPP_EVENT_IPV6CPDOWN,
                                      NULL);
}

/****************************************************************************
* CREATE DATE  ：2000/04/05                                                 *
* CREATED BY   ：Deng Yi Ou                                                 *
* FUNCTION     ：状态机finished的处理函数                                   *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstFsm:状态机                                              *
* OUTPUT       ：                                                           *
* RETURN       ：0                                                          *
* CALLED BY    ：是回调函数，由状态机tlf动作宏(PPP_FSM_tlf)调用             *
 修改历史      :
  1.日    期   : 2009年12月26日
    作    者   : zhaichao
    修改内容   : 针对ipv6cp在ipv4上进行修改而来

****************************************************************************/
VOID PPP_IPV6CP_finished(PPPFSM_S *pstFsm)
{
    PPP_Core_ReceiveEventFromProtocol(((PPPINFO_S *)pstFsm->pPppInfo),
                                      (LONG)PPP_EVENT_IPV6CPFINISHED,
                                      NULL);
}

/****************************************************************************
* CREATE DATE  ：2000/04/05                                                 *
* CREATED BY   ：Deng Yi Ou                                                 *
* FUNCTION     ：状态机starting的处理函数                                   *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstFsm:状态机                                              *
* OUTPUT       ：                                                           *
* RETURN       ：0                                                          *
* CALLED BY    ：是回调函数，由状态机tls动作宏(PPP_FSM_tls)调用             *
 修改历史      :
  1.日    期   : 2009年12月26日
    作    者   : zhaichao
    修改内容   : 针对ipv6cp在ipv4上进行修改而来

****************************************************************************/
VOID PPP_IPV6CP_starting(PPPFSM_S *pstFsm)
{
    PPP_Core_ReceiveEventFromProtocol(((PPPINFO_S *)pstFsm->pPppInfo),
                                      (LONG)PPP_EVENT_IPV6CPSTARTING,
                                      NULL);
}

/****************************************************************************
* CREATE DATE  ：2009/12/23                                                 *
* CREATED BY   ：zhaichao                                                 *
* FUNCTION     ：初始化IPv6CP控制块                                           *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstPppInfo:PPP控制块                                       *
*                ausMyIpAddr:我的IP地址                                      *
*                ausPeerIpAddr:分配给对方的IP地址                            *
* OUTPUT       ：                                                           *
* RETURN       ：0                                                          *
* CALLED BY    ：                                                           *
 修改历史      :
  1.日    期   : 2009年12月23日
    作    者   : zhaichao
    修改内容   : 针对ipv6cp在ipv4上进行修改而来

****************************************************************************/
VOID PPP_IPV6CP_Init(PPPINFO_S* pstPppInfo, VOS_UINT16 *ausMyIpAddr, VOS_UINT16 *ausPeerIpAddr)
{
    PPPFSM_S            *pstFsm;
    PPPIPV6CPINFO_S     *pstIpv6cpInfo;
    PPP_IPV6CP_OPTION_S *pstAllowOptions, *pstWantOptions;
    PPP_IPV6CP_OPTION_S *pstGotOptions, *pstHisOptions;


    if ((NULL == pstPppInfo) || (NULL == pstPppInfo->pstIpV6cpInfo))
    {
        return;
    }

    pstIpv6cpInfo = (PPPIPV6CPINFO_S *)pstPppInfo->pstIpV6cpInfo;
    pstFsm = &(pstIpv6cpInfo->stFsm);
    pstPppInfo->bPppStateFlgV6 = PPP_STATE_NEGOING;

    /* IPCP控制块初始化 */
    pstIpv6cpInfo->pstPppInfo = pstPppInfo;

    if (1 != pstIpv6cpInfo->ucUsedFlag)
    {
        pstIpv6cpInfo->ucUsedFlag = 1;
        PPP_DBG_OK_CNT(PPP_PHOK_908);

    }

    /* 状态机初始化 */
    pstFsm->usProtocol    = PPP_IPV6CP;
    pstFsm->pstCallBacks  = &g_stIpv6cpCallbacks;
    pstFsm->pProtocolInfo = (char*)pstIpv6cpInfo;
    pstFsm->pPppInfo = (char*)pstIpv6cpInfo->pstPppInfo;
    PPP_FSM_Init(pstFsm);

    /* 协商参数初始化 */
    pstAllowOptions = &(pstIpv6cpInfo->stAllowOptions);
    pstWantOptions = &(pstIpv6cpInfo->stWantOptions);
    pstGotOptions = &(pstIpv6cpInfo->stGotOptions);
    pstHisOptions = &(pstIpv6cpInfo->stHisOptions);

    if (0 == pstPppInfo->bPppClient)
    {
        /*这里需要协商的是接口id，而不是完全的ipv6地址,对端接口id初始值为fffffffffe*/
        VOS_MemCpy((void*)(pstWantOptions->OurV6InId),(void *)(&ausMyIpAddr[4]),IPV6_ADDR_LEN);

        /*aaa下发接口id则使用aaa的否则取本地配置*/
        if (VOS_OK == PPP_ipv6_intfid_check(ausPeerIpAddr + 4, IPV6_ADDR_LEN))
        {
            VOS_MemCpy((void*)(pstWantOptions->HisV6InId),(void *)(ausPeerIpAddr + 4),IPV6_ADDR_LEN);
            PPPC_INFO_LOG4("\r\n PPP_IPV6CP_Init: peer interface id = %x %x %x %x ",
                                                (ausPeerIpAddr + 4)[0],
                                                (ausPeerIpAddr + 4)[1],
                                                (ausPeerIpAddr + 4)[2],
                                                (ausPeerIpAddr + 4)[3]);
        }
        else
        {
            PPP_DBG_OK_CNT(PPP_PHOK_909);
            VOS_MemCpy((void*)(pstWantOptions->ConfigV6InId),(void *)g_pstApnByIndex[pstPppInfo->usCDBIndex].aucIterfaceID,IPV6_ADDR_LEN);
            PPPC_INFO_LOG4("\r\n wwwwwww PPP_IPV6CP_Init: local interface id = %x %x %x %x ",
                                                pstWantOptions->ConfigV6InId[0],
                                                pstWantOptions->ConfigV6InId[1],
                                                pstWantOptions->ConfigV6InId[2],
                                                pstWantOptions->ConfigV6InId[3]);
        }
    }
    else
    {
        PPP_MemSet((void*)(pstWantOptions->OurV6InId), 0, IPV6_ADDR_LEN);
        PPP_MemSet((void*)(pstWantOptions->HisV6InId), 0, IPV6_ADDR_LEN);
    }

    pstWantOptions->neg_addr  = 1;
    pstWantOptions->req_addr  = 1;
    pstWantOptions->old_addrs = 0;
    pstWantOptions->neg_vj = 0;
    pstWantOptions->vj_protocol  = PPP_VJ_COMP;
    pstWantOptions->maxslotindex = MAX_STATES - 1; /* really max index */
    pstWantOptions->cflag = 0;
    pstWantOptions->neg_dnsaddr0  = 0;
    pstWantOptions->req_dnsaddr0  = 0;
    pstWantOptions->neg_nbnsaddr0 = 0;
    pstWantOptions->req_nbnsaddr0 = 0;
    pstWantOptions->neg_dnsaddr1     = 0;
    pstWantOptions->req_dnsaddr1     = 0;
    pstWantOptions->neg_nbnsaddr1    = 0;
    pstWantOptions->req_nbnsaddr1    = 0;
    pstWantOptions->accept_dnsaddr0  = 0;
    pstWantOptions->accept_dnsaddr1  = 0;
    pstWantOptions->accept_nbnsaddr0 = 0;
    pstWantOptions->accept_nbnsaddr1 = 0;

    *pstGotOptions = *pstWantOptions;

    pstAllowOptions->req_addr = 1;
    pstAllowOptions->neg_dnsaddr0  = 0;
    pstAllowOptions->req_dnsaddr0  = 0;
    pstAllowOptions->neg_nbnsaddr0 = 0;
    pstAllowOptions->req_nbnsaddr0 = 0;
    pstAllowOptions->neg_dnsaddr1     = 0;
    pstAllowOptions->req_dnsaddr1     = 0;
    pstAllowOptions->neg_nbnsaddr1    = 0;
    pstAllowOptions->req_nbnsaddr1    = 0;
    pstAllowOptions->accept_dnsaddr0  = 0;
    pstAllowOptions->accept_dnsaddr1  = 0;
    pstAllowOptions->accept_nbnsaddr0 = 0;
    pstAllowOptions->accept_nbnsaddr1 = 0;

    /* pstHisOptions 清零 */
    PPP_MemSet((VOID*)pstHisOptions, 0, sizeof(PPP_IPV6CP_OPTION_S));
}

/****************************************************************************
* CREATE DATE  ：2000/04/05                                                 *
* CREATED BY   ：Deng Yi Ou                                                 *
* FUNCTION     ：IPCP up后对协商结果进行检查,主要是为了以后扩展留下的接口   *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstPppInfo:PPP控制块                                       *
* OUTPUT       ：                                                           *
* RETURN       ：VOS_ERR:协商结果不可接受,调用者应结束协商                  *
*                VOS_OK :协商结果可以接受,调用者应向上层协议报UP            *
* CALLED BY    ：PPP_IPCP_up                                                *
****************************************************************************/
VOS_UINT32 PPP_IPV6CP_UpResetCi(PPPINFO_S *pstPppInfo)
{
    /* success */
    return VOS_OK;
}

/*lint -e778*/
/*****************************************************************************
 Prototype    : PPP_IPv6_GetAddrType
 Description  : IPv6地址类型检查
 Input        : IN6ADDR_S *addr
 Output       : None
 Return Value :
 Calls        :
 Called By    :

*****************************************************************************/
VOS_UINT16 PPP_IPv6_GetAddrType( in6_addr *addr )
{
    VOS_UINT16  type;
    VOS_UINT32  st;

    st = addr->s6_addr32[0];

    if ( ( st & VOS_HTONL( 0xFF000000 ) ) == VOS_HTONL( 0xFF000000 ) )
    {
        type = IPV6_ADDR_MULTICAST;

        switch ( ( st & VOS_HTONL( 0x00FF0000 ) ) )
        {
            /*lint -e30*/
            case 0x00000100: /*VOS_HTONL( 0x00010000 ) */
                            type |= IPV6_ADDR_LOOPBACK;
                break;

            case 0x00000200: /*VOS_HTONL( 0x00020000 )*/
                            type |= IPV6_ADDR_LINKLOCAL;
                break;

            case 0x00000500: /*VOS_HTONL( 0x00050000 )*/
                            type |= IPV6_ADDR_SITELOCAL;
                break;
            /*lint +e30*/
            default:
                break;
        };
        return type;
    }

    type = IPV6_ADDR_UNICAST;

    /* Consider all addresses with the first three bits different of
       000 and 111 as finished.
     */
    if ( ( st & VOS_HTONL( 0xE0000000 ) ) != VOS_HTONL( 0x00000000 ) &&
         ( st & VOS_HTONL( 0xE0000000 ) ) != VOS_HTONL( 0xE0000000 ) )
{
        if ( ( st & VOS_HTONL( 0x20000000 ) ) == VOS_HTONL( 0x20000000 ) )
        {
            return ( IPV6_ADDR_GLOBAL | type ); /* global 0010 0000 0000 0000
                                                     global 0011 0000 0000 0000 */
        }
        return type;
    }

    if ( ( st & VOS_HTONL( 0xFFC00000 ) ) == VOS_HTONL( 0xFE800000 ) )
        return ( IPV6_ADDR_LINKLOCAL | type );/*link-local 1111 1110 10*/

    if ( ( st & VOS_HTONL( 0xFFC00000 ) ) == VOS_HTONL( 0xFEC00000 ) )
        return ( IPV6_ADDR_SITELOCAL | type );/*site-local 1111 1110 11*/

    if ( ( addr->s6_addr32[0] | addr->s6_addr32[1] ) == 0 )
    {
        if ( addr->s6_addr32[2] == 0 )
        {
            if ( addr->s6_addr32[3] == 0 )
                return IPV6_ADDR_ANY;/*all ::0*/

            if ( addr->s6_addr32[3] == VOS_HTONL( 0x00000001 ) )
                return ( IPV6_ADDR_LOOPBACK | type );/* ::0:1 */

            return ( IPV6_ADDR_COMPATv4 | type );
        }

        if ( addr->s6_addr32[2] == VOS_HTONL(0x0000ffff))
            return IPV6_ADDR_MAPPED;
    }

    st &= VOS_HTONL( 0xFF000000 );
    if ( st == 0 )
        return IPV6_ADDR_RESERVED; /*0000 0000 */
    st &= VOS_HTONL( 0xFE000000 );
    if ( st == VOS_HTONL( 0x02000000 ) )
        return IPV6_ADDR_RESERVED;    /* for NSAP */
    if ( st == VOS_HTONL( 0x04000000 ) )
        return IPV6_ADDR_RESERVED;    /* for IPX */

    return type;
}


/****************************************************************************
* CREATE DATE  ：2009/12/22                                                 *
* CREATED BY   ：T62595                                                  *
* FUNCTION     ：ipv6地址检查                                               *
* MODIFY DATE  ：                                                           *
* INPUT        ：                                                           *
* OUTPUT       ：                                                           *
* RETURN       ：
* CALLED BY    ：vos_ok:ip地址有效；vos_err:ip地址无效
****************************************************************************/
VOS_UINT32 PPP_ipv6_addr_check(VOS_UINT16 *pstIpv6addr)
{
    VOS_UINT16 ultype;
    VOS_UINT32 ulGlobalAddr = VOS_HTONL(0x20000000);   /* "可聚集全局单播地址"的二进制前缀为001 */
    VOS_UINT32 ulSiteLocalAddr = VOS_HTONL(0xFEC00000);/* "网点本地单播地址"的二进制前缀为1111 1111 11 */
    in6_addr *pstAddr = (in6_addr *)pstIpv6addr;
    VOS_UINT32 ulIpAddr = pstAddr->s6_addr32[0];

    ultype = PPP_IPv6_GetAddrType( pstAddr );

    /*暂时只支持SITE- local address，可以考虑以后再扩展*/
    if ( ( ultype & IPV6_ADDR_UNICAST )&&
         ( ( ultype & IPV6_ADDR_SITELOCAL )||( ultype & IPV6_ADDR_GLOBAL ) ) ) /* 支持 global */
    {
        /* 只有"可聚集全局单播地址"和"网点本地单播地址"可被分配 */
        if (((ulIpAddr & VOS_HTONL(0xE0000000)) != ulGlobalAddr)
            && ((ulIpAddr & VOS_HTONL(0xFFC00000)) != ulSiteLocalAddr))
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_230);
            return VOS_ERR;
        }
        /*  只有"可聚集全局单播地址"和"网点本地单播地址"可被分配*/
        return VOS_OK;
    }
    PPP_DBG_ERR_CNT(PPP_PHERR_231);
    return VOS_ERR;
}
/*lint +e778*/

/****************************************************************************
* CREATE DATE  ：2009/12/22                                                 *
* CREATED BY   ：z00129699                                                  *
* FUNCTION     ：ipv6 interface id 检查                                               *
* MODIFY DATE  ：                                                           *
* INPUT        ：                                                           *
* OUTPUT       ：                                                           *
* RETURN       ：
* CALLED BY    ：vos_ok:ip地址有效；vos_err:ip地址无效
****************************************************************************/
VOS_UINT32 PPP_ipv6_intfid_check(VOS_UINT16 *pstIpv6addr, VOS_UINT32 ullen)
{
    VOS_UINT32  ulReturn = 0;
    UCHAR  ucipv6Invalid[IPV6_ADDR_LEN*2] = {0};

    if (NULL == pstIpv6addr)
    {
        return VOS_ERR;
    }

    ulReturn = (VOS_UINT32)VOS_MemCmp((VOS_VOID *)pstIpv6addr, (VOS_VOID *)ucipv6Invalid, ullen);
    if (VOS_OK == ulReturn)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_910);
        PPPC_INFO_LOG("\r\n PPP_ipv6_intfid_check: ipv6 addr is zero!");
        return VOS_ERR;
    }

    return VOS_OK;
}


/****************************************************************************
* CREATE DATE  ：2009/12/22                                                 *
* CREATED BY   ：z00129699                                                  *
* FUNCTION     ：ipv6cp入口函数                                              *
* MODIFY DATE  ：                                                           *
* INPUT        ：                                                           *
* OUTPUT       ：                                                           *
* RETURN       ：
* CALLED BY    ：
****************************************************************************/
VOID PPP_Ipv6cp_Proc(PPPINFO_S *pstPppInfo)
{
    VOS_UINT32   ulResult   = VOS_ERR;

    PPPC_INFO_LOG("\r\n PPP_Ipv6cp_Proc: ENTER.");

    if (NULL == pstPppInfo)
    {
        PPPC_INFO_LOG("\r\n PPP_Ipv6cp_Proc: Invalid input parameter pstPppInfo!");
        return;
    }

    ulResult = PPP_ipv6_addr_check(pstPppInfo->usPeerIPv6Addr);

    /*地址有效未必申请地址成功，有可能是aaa下发的静态地址核查失败，此种情况地址是不能清空的*/
    if ((VOS_OK == ulResult)
        &&(pstPppInfo->pstIpV6cpInfo == NULL)
        &&( ( PPP_USERTYPE_SIP == pstPppInfo->bIPTech)))
    {
        PPPC_INFO_LOG("\r\n PPP_Ipv6cp_Proc: enter!");

        PPP_GETIPV6CPADDR(pstPppInfo->pstIpV6cpInfo, pstPppInfo->ulRPIndex);
        if (NULL == pstPppInfo->pstIpV6cpInfo)
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_232);
            PPP_Debug_CoreEvent(pstPppInfo, PPP_LOG_ERROR, "\r\nPPP_Ipv6cp_Proc Malloc IPv6CP CB Err!!");
            return;
        }

        PPP_MemSet((void *)pstPppInfo->pstIpV6cpInfo, 0, sizeof(PPPIPV6CPINFO_S));
        PPP_IPV6CP_Init(pstPppInfo, pstPppInfo->usIpv6Addr, pstPppInfo->usPeerIPv6Addr);

        /* 向IPCP发送消息,触发IPCP开始协商 */
        PPP_IPV6CP_ReceiveEventFromCore(pstPppInfo->pstIpV6cpInfo, (VOS_UINT32)PPP_EVENT_FSM_OPEN, NULL );
        PPP_IPV6CP_ReceiveEventFromCore(pstPppInfo->pstIpV6cpInfo, (VOS_UINT32)PPP_EVENT_FSM_UP, NULL );

    }
    else
    {
        PPP_DBG_OK_CNT(PPP_PHOK_911);
        PPPC_INFO_LOG1("\r\n PPP_Ipv6cp_Proc: don't nego ipv6 addr err ulResult %d, ",
                            ulResult);
    }

    return;
}


/****************************************************************************
* CREATE DATE  ：2009/12/23                                                 *
* CREATED BY   ：z00129699                                                  *
* FUNCTION     ：ipv6cp协商报文处理函数                                              *
* MODIFY DATE  ：                                                           *
* INPUT        ：                                                           *
* OUTPUT       ：                                                           *
* RETURN       ：
* CALLED BY    ：
****************************************************************************/

VOID PPP_IPV6CP_Pactket_Proc(PPPINFO_S *pstPppInfo,
                                         UCHAR*     pHead,
                                         UCHAR*     pPacket,
                                         VOS_UINT32      ulLen)
{
    /* 输出调试信息 */
    if (pstPppInfo->stPppDebugInfo.bDebug_Ipv6cp_Packet == VRP_YES)
    {
        PPP_Debug_FsmPacket(pstPppInfo,
                            pPacket,
                            ulLen,
                            PPP_IPV6CP,
                            (UCHAR)PPP_DEBUG_PACKET_IN);
    }

    /* 如果是因为协议未到Network阶段pstIpcpInfo才为0，
       则抛弃报文，但不发protocol reject。
       参见RFC1661。
     */
    if (pstPppInfo->usPhase != (VOS_UINT16)PPP_PHASE_NETWORK)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_233);
        return;
    }

    if (pstPppInfo->pstIpV6cpInfo)
    {
        PPP_IPV6CP_ReceivePacket(pstPppInfo->pstIpV6cpInfo, pHead, pPacket, ulLen);
        PPP_DBG_OK_CNT(PPP_PHOK_912);
        return;
    }
    return;
}
/*lint +e572*/
/*lint -restore */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
