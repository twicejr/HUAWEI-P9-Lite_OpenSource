/************************************************************************
*                                                                      *
*                             ipcp.c                                   *
*                                                                      *
*  Project Code:       VRP3.0                                          *
*  Create Date:        2000/04/04                                      *
*  Author:             Deng Yi Ou                                      *
*  Modify Date:                                                        *
*  Document:                                                           *
*  Function:           PPP的IPCP协议模块                               *
*  Others:                                                             *
*----------------------------------------------------------------------*
*                                                                      *
*  Copyright 2000-2002 VRP3.0 Team Beijing Institute HuaWei Tech, Inc. *
*                      ALL RIGHTS RESERVED                             *
*                                                                      *
*----------------------------------------------------------------------*
*                                                                      *
*   这个文件定义了IPCP协议模块的全部接口函数和内部处理函数             *
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
#define         THIS_FILE_ID            PS_FILE_ID_PPPC_IPCP_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
/* IPCP回调函数数据结构 */
PPPFSMCALLBACK_S g_stIpcpCallbacks =
{
    /* 动作：协商报文处理 */
    PPP_IPCP_resetci,   /* 根据配置信息设置协商初始值 */
    PPP_IPCP_cilen,     /* 我要发送的request报文长度 */
    PPP_IPCP_addci,     /* 组织协商报文 */
    PPP_IPCP_ackci,     /* 处理对方的ack报文 */
    PPP_IPCP_nakci,     /* 处理对方的nak报文 */
    PPP_IPCP_rejci,     /* 处理对方的reject报文 */
    PPP_IPCP_reqci,     /* 处理对方的request报文 */
    NULL,                /* extcode函数,处理协议特有的报文.
                            IPCP没有特殊类型报文,因此不提供这个函数*/

    /* 事件：协议转入了终止状态 */
    PPP_IPCP_up,        /* 协议up */
    PPP_IPCP_down,       /* 协议暂时down,马上要重新协商.
                           与finished的区别是:对于PPPOE、DDR等的情况，
                           不用通知下层拆除链路 */
    PPP_IPCP_finished,   /* 协议结束，通知下层:拆除链路.对于IPCP,则是通知
                            LCP:如果没有其他网络层协议,则LCP可以down掉*/
    PPP_IPCP_starting,   /* tls(This-Layer-Started)动作中，通知下层:我准
                           备好了重新协商,如可能,请发一个up事件.
                           协议对这个动作没有具体规定,可以不实现*/

    /* 子协议信息 */
    "IPCP"               /* 子协议名 */
};

/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*lint -save -e958 */

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
****************************************************************************/
VOID PPP_IPCP_ReceiveEventFromCore (VOID *pstIpcpInfo, VOS_UINT32 ulCmd, char *pPara)
{
    PPPFSM_S *pstFsm;


    PPPC_INFO_LOG1("\r\n---Into PPP_IPCP_ReceiveEventFromCore ulCmd %d---\r\n", ulCmd);
    if (NULL == pstIpcpInfo)
    {
        return;
    }

    /* 性能统计:IPCP协商尝试次数 */
    if (PPP_EVENT_FSM_OPEN == ulCmd)
    {
        PPP_PerfInc(&g_stPppPerfStatistic.ulIpcpTotal, PERF_TYPE_PPPC_IPCP_NEGO_REQ_NUM, 0);
        PPPC_INFO_LOG1("****pulIpcpTotal: %d****", g_stPppPerfStatistic.ulIpcpTotal);
        PPP_DBG_OK_CNT(PPP_PHOK_885);
    }


    pstFsm = &(((PPPIPCPINFO_S*)pstIpcpInfo)->stFsm);

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
****************************************************************************/
VOID PPP_IPCP_ReceivePacket (VOID *pstIpcpInfo, UCHAR* pHead, UCHAR* pPacket, VOS_UINT32 ulLen)
{
    PPPFSM_S                           *pstFsm;
    PPPINFO_S                          *pstPppInfo;


    if(NULL == pstIpcpInfo)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_193);
        return;
    }
    /* 已保证pstIpcpInfo非空*/
    /*lint -e413*/
    pstFsm = &(((PPPIPCPINFO_S*)pstIpcpInfo)->stFsm);
    pstPppInfo  = (PPPINFO_S*)PPPC_MEMBER2PARENT(PPPINFO_S, pstIpcpInfo);
    /*lint +e413*/
    PPP_FSM_ReceivePacket(pstFsm, pHead, pPacket, ulLen, pstPppInfo->ulRPIndex);/* Modified by liutao 38563 at 2004-09-22 V800R002 for PPP压缩移植 */

    return;
}

/****************************************************************************
* CREATE DATE  ：2000/04/04                                                 *
* CREATED BY   ：Deng Yi Ou                                                 *
* FUNCTION     ：确定IPCP需要协商那些参数,在IPCP初始化时进行                  *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstFsm    :状态机                                          *
* OUTPUT       ：                                                           *
* RETURN       ：0                                                          *
* CALLED BY    ：状态机中执行tls动作的宏PPP_FSM_tls                         *
****************************************************************************/
VOID PPP_IPCP_resetci(PPPFSM_S *pstFsm)
{
    PPPIPCPINFO_S *pstInfo;
    PPPCONFIGINFO_S *pstConfig;
    PPPINFO_S *pstPppInfo;
    PPP_IPCP_OPTION_S *pstAllowOptions, *pstWantOptions;
    PPP_IPCP_OPTION_S *pstGotOptions, *pstHisOptions;
    PPPRENOGOINFO *pstPppRenegoInfo;

    pstInfo = (PPPIPCPINFO_S *)pstFsm->pProtocolInfo;
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
    pstWantOptions->neg_dnsaddr0  = 1;
    pstWantOptions->req_dnsaddr0  = 1;
    pstWantOptions->neg_nbnsaddr0 = 0;
    pstWantOptions->req_nbnsaddr0 = 0;
    pstWantOptions->neg_dnsaddr1     = 1;
    pstWantOptions->req_dnsaddr1     = 1;
    pstWantOptions->neg_nbnsaddr1    = 0;
    pstWantOptions->req_nbnsaddr1    = 0;
    pstWantOptions->accept_dnsaddr0  = 1;/* modified by chenmin00265046 接受对方的DNS,会影响到收到IPCP NAK后再次发送ConfigReq选项 */
    pstWantOptions->accept_dnsaddr1  = 1;/* modified by chenmin00265046 接受对方的DNS,会影响到收到IPCP NAK后再次发送ConfigReq选项*/
    pstWantOptions->accept_nbnsaddr0 = 0;
    pstWantOptions->accept_nbnsaddr1 = 0;

    pstAllowOptions->req_addr = 1;
    pstAllowOptions->neg_dnsaddr0  = 1;
    pstAllowOptions->req_dnsaddr0  = 1;
    pstAllowOptions->neg_nbnsaddr0 = 0;
    pstAllowOptions->req_nbnsaddr0 = 0;
    pstAllowOptions->neg_dnsaddr1     = 1;
    pstAllowOptions->req_dnsaddr1     = 1;
    pstAllowOptions->neg_nbnsaddr1    = 0;
    pstAllowOptions->req_nbnsaddr1    = 0;
    pstAllowOptions->accept_dnsaddr0  = 0;  /* modified by gxf 20030414 不接受对方的DNS */
    pstAllowOptions->accept_dnsaddr1  = 0;  /* modified by gxf 20030414 不接受对方的DNS */
    pstAllowOptions->accept_nbnsaddr0 = 0;
    pstAllowOptions->accept_nbnsaddr1 = 0;

    /* 按配置信息设置协商参数 */
    if (pstConfig->bEnableVJComp)
    {
        if (1 == pstPppInfo->bPppClient)
        {
            pstWantOptions->neg_vj = 0;
        }
        else
        {
            pstWantOptions->neg_vj = 1;
        }
    }

    if (pstAllowOptions->dnsaddr0 == 0)
    {
        pstAllowOptions->accept_dnsaddr0 = 0;
    }

    if (pstAllowOptions->dnsaddr1 == 0)
    {
        pstAllowOptions->accept_dnsaddr1 = 0;
    }

    *pstGotOptions = *pstWantOptions;

    /* pstHisOptions 清零 */
    PPP_MemSet((VOID*)pstHisOptions, 0, sizeof(PPP_IPCP_OPTION_S));

    pstFsm->ulTimeOutTime = pstConfig->ulNegTimeOut;

    pstPppRenegoInfo = pstPppInfo->pstPppRenegoInfo;
    if (pstPppRenegoInfo && pstPppRenegoInfo->ucIpcpFlag)
    {
        VOS_MemCpy((VOID*)pstGotOptions, (VOID*)&pstPppRenegoInfo->stIpcpOptions, sizeof(PPP_IPCP_OPTION_S));
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
****************************************************************************/
VOS_UINT16 PPP_IPCP_cilen(PPPFSM_S *pstFsm)
{
    PPP_IPCP_OPTION_S *pstGotOptions;

    pstGotOptions = &(((PPPIPCPINFO_S*)pstFsm->pProtocolInfo)->stGotOptions);

    /*
     * NB: we only ask for one of CHAP and UPAP, even if we will
     * accept either.
     */
    return (VOS_UINT16)(IPCP_LENCIADDR(pstGotOptions->neg_addr, pstGotOptions->old_addrs) +
                   IPCP_LENCIVJ(pstGotOptions->neg_vj) +
                   IPCP_LENCIDNSADDR(pstGotOptions->neg_dnsaddr0) +
                   IPCP_LENCIDNSADDR(pstGotOptions->neg_nbnsaddr0) +
                   IPCP_LENCIDNSADDR(pstGotOptions->neg_dnsaddr1) +
                   IPCP_LENCIDNSADDR(pstGotOptions->neg_nbnsaddr1)
    );
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
****************************************************************************/
VOID PPP_IPCP_addci(PPPFSM_S *pstFsm, UCHAR *pPacket)
{
    PPP_IPCP_OPTION_S *pstGotOptions;

    pstGotOptions = &(((PPPIPCPINFO_S*)pstFsm->pProtocolInfo)->stGotOptions);

    ADDCIADDR((pstGotOptions->old_addrs ? IPCP_CI_ADDRS : IPCP_CI_ADDR),
              pstGotOptions->neg_addr,
              pstGotOptions->old_addrs,
              pstGotOptions->ouraddr,
              pstGotOptions->hisaddr
    );

    ADDCIVJ(IPCP_CI_COMPRESSTYPE,
            pstGotOptions->neg_vj,
            pstGotOptions->vj_protocol,
            pstGotOptions->maxslotindex,
            pstGotOptions->cflag
    );

    ADDCIDNSADDR(IPCP_CI_DNSADDR0,
                 pstGotOptions->neg_dnsaddr0,
                 pstGotOptions->dnsaddr0
    );

    ADDCIDNSADDR(IPCP_CI_NBNSADDR0,
                 pstGotOptions->neg_nbnsaddr0,
                 pstGotOptions->nbnsaddr0
    );

    ADDCIDNSADDR(IPCP_CI_DNSADDR1,
                 pstGotOptions->neg_dnsaddr1,
                 pstGotOptions->dnsaddr1
    );

    ADDCIDNSADDR(IPCP_CI_NBNSADDR1,
                 pstGotOptions->neg_nbnsaddr1,
                 pstGotOptions->nbnsaddr1
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
* CALLED BY    ：PPP_FSM_ReceiveConfAck                                     *
****************************************************************************/
VOS_UINT16 PPP_IPCP_ackci(PPPFSM_S *pstFsm, UCHAR *pPacket, VOS_UINT32 ulLen)
{
    PPP_IPCP_OPTION_S *pstGotOptions;
    UCHAR cilen, citype;
    VOS_UINT16 cishort;
    VOS_UINT32 cilong = 0;
    UCHAR cimaxslotindex, cicflag;

    pstGotOptions = &(((PPPIPCPINFO_S*)pstFsm->pProtocolInfo)->stGotOptions);

    /*
     * CIs must be in exactly the same order that we sent...
     * Check packet length and CI length at each step.
     * If we find any deviations, then this packet is bad.
     */

    /* We allow the configuration length is 0. */
    if (ulLen == 0)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_886);
        return VOS_OK;
    }

    ACKCIADDR((pstGotOptions->old_addrs ? IPCP_CI_ADDRS : IPCP_CI_ADDR),
              pstGotOptions->neg_addr,
              pstGotOptions->old_addrs,
              pstGotOptions->ouraddr,
              pstGotOptions->hisaddr
    );

    ACKCIVJ(IPCP_CI_COMPRESSTYPE,
            pstGotOptions->neg_vj,
            pstGotOptions->vj_protocol,
            pstGotOptions->maxslotindex,
            pstGotOptions->cflag
    );

    ACKCIDNSADDR(IPCP_CI_DNSADDR0,
                 pstGotOptions->neg_dnsaddr0,
                 pstGotOptions->dnsaddr0
    );

    ACKCIDNSADDR(IPCP_CI_NBNSADDR0,
                 pstGotOptions->neg_nbnsaddr0,
                 pstGotOptions->nbnsaddr0
    );

    ACKCIDNSADDR(IPCP_CI_DNSADDR1,
                 pstGotOptions->neg_dnsaddr1,
                 pstGotOptions->dnsaddr1
    );

    ACKCIDNSADDR(IPCP_CI_NBNSADDR1,
                 pstGotOptions->neg_nbnsaddr1,
                 pstGotOptions->nbnsaddr1
    );

    /*
     * If there are any remaining CIs, then this packet is bad.
     */
    /*lint -e801*/
    if (ulLen != 0)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_194);
        goto bad;
    }
    /*lint +e801*/

    return VOS_OK;

bad:
    PPP_Debug_Error(pstFsm, PPP_LOG_WARNING, "Ipcp_ackci: received bad Ack!");
    return VOS_ERR;
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
****************************************************************************/
VOS_UINT16 PPP_IPCP_nakci(PPPFSM_S *pstFsm, UCHAR *pPacket, VOS_UINT32 ulLen)
{
    PPP_IPCP_OPTION_S *pstGotOptions, *pstWantOptions;
    PPP_IPCP_OPTION_S stNoOption;  /* 被对方no掉的选项 */
    PPP_IPCP_OPTION_S stTryOption; /* 尝试与对方协商的选项 */

    UCHAR cimaxslotindex, cicflag;
    UCHAR citype, cilen, *next;
    VOS_UINT16 cishort;
    VOS_UINT32 ciaddr1 = 0;
    VOS_UINT32 ciaddr2 = 0;

    pstGotOptions  = &(((PPPIPCPINFO_S*)pstFsm->pProtocolInfo)->stGotOptions);
    pstWantOptions = &(((PPPIPCPINFO_S*)pstFsm->pProtocolInfo)->stWantOptions);

    PPP_MemSet((VOID*)(&stNoOption), 0, sizeof(PPP_IPCP_OPTION_S));
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
    NAKCIADDR((pstGotOptions->old_addrs ? IPCP_CI_ADDRS : IPCP_CI_ADDR), neg_addr, pstGotOptions->old_addrs,
            if (ciaddr1)
            {
                stTryOption.ouraddr = ciaddr1;
            }

              if (ciaddr2)
              { /* Does he know his? */
                  stTryOption.hisaddr = ciaddr2;
              }

    );

    /*
     * Accept the peer's value of maxslotindex provided that it
     * is less than what we asked for.  Turn off slot-ID compression
     * if the peer wants.  Send old-style compress-type option if
     * the peer wants.
     */
    NAKCIVJ(IPCP_CI_COMPRESSTYPE, neg_vj,
            if (cilen == IPCP_CILEN_VJ)
            {
                PPP_GETCHAR(cimaxslotindex, pPacket);
                PPP_GETCHAR(cicflag, pPacket);
                if (cishort == PPP_VJ_COMP)
                {
                    if (cimaxslotindex < pstGotOptions->maxslotindex)
                    {
                        stTryOption.maxslotindex = cimaxslotindex;
                    }

                    if (!cicflag)
                    {
                        stTryOption.cflag = 0;
                    }
                }
                else
                {
                    stTryOption.neg_vj = 0;
                }
            }

    );

    NAKCIDNSADDR( IPCP_CI_DNSADDR0, neg_dnsaddr0,
                  if ((pstGotOptions->accept_dnsaddr0 != 0) && (ciaddr1 != 0))
                  {
                      stTryOption.dnsaddr0 = ciaddr1;
                  }

                  if ((pstGotOptions->accept_dnsaddr0 == 0) && (ciaddr1 != 0))
                  {
                      stTryOption.neg_dnsaddr0 = 0;
                  }

    );

    NAKCIDNSADDR( IPCP_CI_NBNSADDR0, neg_nbnsaddr0,
                  if ((pstGotOptions->accept_nbnsaddr0 != 0) && (ciaddr1 != 0))
                  {
                      stTryOption.nbnsaddr0 = ciaddr1;
                  }

                  if ((pstGotOptions->accept_nbnsaddr0 == 0) && (ciaddr1 != 0))
                  {
                      stTryOption.neg_nbnsaddr0 = 0;
                  }

    );
    NAKCIDNSADDR( IPCP_CI_DNSADDR1, neg_dnsaddr1,
                  if ((pstGotOptions->accept_dnsaddr1 != 0) && (ciaddr1 != 0))
                  {
                      stTryOption.dnsaddr1 = ciaddr1;
                  }

                  if ((pstGotOptions->accept_dnsaddr1 == 0) && (ciaddr1 != 0))
                  {
                      stTryOption.neg_dnsaddr1 = 0;
                  }

    );
    NAKCIDNSADDR( IPCP_CI_NBNSADDR1, neg_nbnsaddr1,
                  if ((pstGotOptions->accept_nbnsaddr1 != 0) && (ciaddr1 != 0))
                  {
                      stTryOption.nbnsaddr1 = ciaddr1;
                  }

                  if ((pstGotOptions->accept_nbnsaddr1 == 0) && (ciaddr1 != 0))
                  {
                      stTryOption.neg_nbnsaddr1 = 0;
                  }

    );

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
            PPP_DBG_ERR_CNT(PPP_PHERR_195);
            goto bad;
        }

        ulLen = (VOS_UINT32)(ulLen - cilen);
        if ((LONG)ulLen < 0)
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_196);
            goto bad;
        }

        next = pPacket + cilen - 2;

        switch (citype)
        {
            case IPCP_CI_COMPRESSTYPE:
                if (pstGotOptions->neg_vj || stNoOption.neg_vj
               || ((cilen != IPCP_CILEN_VJ) && (cilen != IPCP_CILEN_COMPRESS)))
                {
                    PPP_DBG_ERR_CNT(PPP_PHERR_197);
                    goto bad;
                }

                stNoOption.neg_vj = 1;
                break;

            case IPCP_CI_ADDRS:
                if ((pstGotOptions->neg_addr && pstGotOptions->old_addrs) || stNoOption.old_addrs
                    || (cilen != IPCP_CILEN_ADDRS))
                {
                    PPP_DBG_ERR_CNT(PPP_PHERR_198);
                    goto bad;
                }

                stTryOption.neg_addr  = 1;
                stTryOption.old_addrs = 1;
                PPP_GETADDR(ciaddr1, pPacket);
                if (ciaddr1 && (pstWantOptions->ouraddr == 0L))
                {
                    stTryOption.ouraddr = ciaddr1;
                }

                PPP_GETADDR(ciaddr2, pPacket);
                if (ciaddr2)
                {
                    stTryOption.hisaddr = ciaddr2;
                }

                stNoOption.old_addrs = 1;
                break;

            case IPCP_CI_ADDR:
                if (pstGotOptions->neg_addr || stNoOption.neg_addr || (cilen != IPCP_CILEN_ADDR))
                {
                    PPP_DBG_ERR_CNT(PPP_PHERR_199);
                    goto bad;
                }

                PPP_GETADDR(ciaddr1, pPacket);
                if (ciaddr1 && (pstWantOptions->ouraddr == 0L))
                {
                    stTryOption.ouraddr  = ciaddr1;
                    stTryOption.neg_addr = 1;
                }

                stNoOption.neg_addr = 1;
                break;
            case IPCP_CI_DNSADDR0:
                NONEGDNSADDR( neg_dnsaddr0, accept_dnsaddr0, dnsaddr0 );
                break;
            case IPCP_CI_NBNSADDR0:
                NONEGDNSADDR( neg_nbnsaddr0, accept_nbnsaddr0, nbnsaddr0 );
                break;
            case IPCP_CI_DNSADDR1:
                NONEGDNSADDR( neg_dnsaddr1, accept_dnsaddr1, dnsaddr1 );
                break;
            case IPCP_CI_NBNSADDR1:
                NONEGDNSADDR( neg_nbnsaddr1, accept_nbnsaddr1, nbnsaddr1 );
                break;
            default:
                break;
        }

        pPacket = next;
    }

    /* If there is still anything left, this packet is bad. */
    /*lint -e801*/
    if (ulLen != 0)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_200);
        goto bad;
    }
    /*lint +e801*/

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
****************************************************************************/
/*lint -e529*/
VOS_UINT16 PPP_IPCP_rejci(PPPFSM_S *pstFsm, UCHAR *pPacket, VOS_UINT32 ulLen)
{
    PPP_IPCP_OPTION_S *pstGotOptions;
    UCHAR cimaxslotindex, ciflag, cilen = 0;
    VOS_UINT16 cishort;
    VOS_UINT32 cilong = 0;
    PPP_IPCP_OPTION_S stTryOption;      /* options to request next time */

    pstGotOptions = &(((PPPIPCPINFO_S*)pstFsm->pProtocolInfo)->stGotOptions);
    stTryOption = *pstGotOptions;

    /*lint -e821*/
    REJCIADDR((pstGotOptions->old_addrs ? IPCP_CI_ADDRS : IPCP_CI_ADDR),
               neg_addr,
               pstGotOptions->old_addrs,
               pstGotOptions->ouraddr,
               pstGotOptions->hisaddr
             );
    /*lint +e821*/

    REJCIVJ(IPCP_CI_COMPRESSTYPE,
            neg_vj,
            pstGotOptions->vj_protocol,
            pstGotOptions->maxslotindex,
            pstGotOptions->cflag
           );

    REJCIDNSADDR(IPCP_CI_DNSADDR0,
                 neg_dnsaddr0,
                 dnsaddr0
                );

    REJCIDNSADDR(IPCP_CI_NBNSADDR0,
                 neg_nbnsaddr0,
                 nbnsaddr0
                );

    REJCIDNSADDR(IPCP_CI_DNSADDR1,
                 neg_dnsaddr1,
                 dnsaddr1
                );

    REJCIDNSADDR(IPCP_CI_NBNSADDR1,
                 neg_nbnsaddr1,
                 nbnsaddr1
                );

    /*
     * If there are any remaining CIs, then this packet is bad.
     */
    /*lint -e801*/
    if (ulLen != 0)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_201);
        goto bad;
    }

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
    /*lint +e801*/
}
/*lint +e529*/

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

*****************************************************************************/
UCHAR PPP_IPCP_IsSip(UCHAR *pPacket, VOS_UINT32 *pulLen)
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
            PPP_DBG_OK_CNT(PPP_PHOK_887);
            return 0;
        }

        PPP_GETCHAR(citype, p);     /* Parse CI type */
        PPP_GETCHAR(cilen, p);      /* Parse CI length */
        l -= cilen;                 /* Adjust remaining length */
        p += (cilen - 2);           /* Step to next CI */

        if (citype == IPCP_CI_ADDR)
        {
            PPP_DBG_OK_CNT(PPP_PHOK_888);
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
* CALLED BY    ：PPP_FSM_ReceiveConfReq函数中由PPP_FSM_reqci宏调用          *
****************************************************************************/
UCHAR PPP_IPCP_reqci(PPPFSM_S *pstFsm, UCHAR *pPacket, VOS_UINT32 *pulLen)
{
    PPP_IPCP_OPTION_S *pstWantOptions;
    PPP_IPCP_OPTION_S *pstAllowOptions;
    PPP_IPCP_OPTION_S *pstGotOptions;
    PPP_IPCP_OPTION_S *pstHisOptions;
    PPPINFO_S* pstPppInfo = NULL;

    UCHAR *cip, *next, *p;     /* Pointer to current and next CIs */
    VOS_UINT16 cilen, citype;   /* Parsed len, type */
    VOS_UINT16 cishort;     /* Parsed short value */
    VOS_UINT32 ciaddr1 = 0; /* Parsed address values */
    VOS_UINT32 ciaddr2 = 0; /* Parsed address values */
    UCHAR rc = CONFACK;     /* Final packet return code */
    UCHAR orc;          /* Individual option return code */
    UCHAR *ucp = pPacket;       /* Pointer to current output char */
    long l = (long)*pulLen;       /* Length left */
    UCHAR maxslotindex, cflag;

    pstWantOptions  = &(((PPPIPCPINFO_S*)pstFsm->pProtocolInfo)->stWantOptions);
    pstAllowOptions = &(((PPPIPCPINFO_S*)pstFsm->pProtocolInfo)->stAllowOptions);
    pstGotOptions = &(((PPPIPCPINFO_S*)pstFsm->pProtocolInfo)->stGotOptions);
    pstHisOptions = &(((PPPIPCPINFO_S*)pstFsm->pProtocolInfo)->stHisOptions);
    pstPppInfo = (PPPINFO_S *)pstFsm->pPppInfo;

    /*
     * Reset all his options.
     */
    (VOID)VOS_MemSet(pstHisOptions, 0, sizeof(PPP_IPCP_OPTION_S));

    /*luofeng37050notify */
    /* added by gxf 20030415    判断SIP/MIP */
    if (!PPP_IPCP_IsSip(pPacket, pulLen))
    {
    }

    /*
     * Process all his options.
     */
    if (l == 0)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_889);
        return rc;
    }

    next = pPacket;

    /*lint -e801*/
    while (l)
    {
        orc = CONFACK;          /* Assume success */
        cip = p = next;         /* Remember begining of CI */
        if ((l < 2)               /* Not enough data for CI header or */
           || (p[1] < 2)    /*  CI length too small or */
           || (p[1] > l))
        {
            /*  CI length too big? */
            orc   = CONFREJ;    /* Reject bad CI */
            cilen = (VOS_UINT16)l;          /* Reject till end of packet */
            l = 0;          /* Don't loop again */
            PPP_DBG_OK_CNT(PPP_PHOK_890);
            goto endswitch;
        }

        PPP_GETCHAR(citype, p);     /* Parse CI type */
        PPP_GETCHAR(cilen, p);      /* Parse CI length */
        l    -= cilen;      /* Adjust remaining length */
        next += cilen;          /* Step to next CI */

        switch (citype)
        {
            /* Check CI type */
            case IPCP_CI_ADDRS:
                if (!pstWantOptions->neg_addr
               || (cilen != IPCP_CILEN_ADDRS))
                {
                    /* Check CI length */
                    PPP_DBG_ERR_CNT(PPP_PHERR_202);
                    orc = CONFREJ;  /* Reject CI */
                    PPPC_INFO_LOG("\r\n PPP_IPCP_reqci: IPCP_CI_ADDRS is not compatible(neg_addr)! ");
                    break;
                }

                /*
                 * If he has no address, or if we both have his address but
                 * disagree about it, then NAK it with our idea.
                 * In particular, if we don't know his address, but he does,
                 * then accept it.
                 */

                /* make sure GetRmtIP return value is net byte */
                /* make sure GetLocIP return value is net byte */

                PPP_GETADDR(ciaddr1, p); /* Parse source address (his) */
                PPP_GETADDR(ciaddr2, p); /* Parse desination address (ours) */

                if ((!pstGotOptions->hisaddr && (!ciaddr1)) || ((!pstGotOptions->ouraddr) && (!ciaddr2)))
                {
                    /* we can't dispatch each other's address so have to say bye */
                    orc = CONFREJ;
                    PPP_DBG_ERR_CNT(PPP_PHERR_203);
                    PPPC_INFO_LOG("\r\n PPP_IPCP_reqci: IPCP_CI_ADDRS is not compatible(ciaddr1,ciaddr2)! ");
                    break;
                }

                if ((pstGotOptions->hisaddr == ciaddr1) && (pstGotOptions->ouraddr == ciaddr2))
                {
                    break;
                }
                else
                {
                    if (ciaddr1)
                    {
                        pstGotOptions->hisaddr = ciaddr1;
                        pstHisOptions->hisaddr = ciaddr1;
                    }

                    if (!pstGotOptions->ouraddr)
                    {
                        pstGotOptions->ouraddr = ciaddr2;
                        pstHisOptions->ouraddr = ciaddr2;
                        break;
                    }

                    if (pstGotOptions->ouraddr != ciaddr2)
                    {
                        orc = CONFNAK;
                        PPP_DECPTR(sizeof(VOS_UINT32) << 1, p);
                        PPP_PUTADDR(pstGotOptions->hisaddr, p);
                        PPP_PUTADDR(pstGotOptions->ouraddr, p);
                    }

                    pstGotOptions->old_addrs = 1;
                    pstHisOptions->old_addrs = 1;
                }

                /* this is occurce when she wants us to dispatch her a ip address */
                break;

            case IPCP_CI_ADDR:

                /* BEGIN: Modified for PN:aaa分配ip无效或不下发 by wangyong 00138171, 2012/8/3 */
                if (!pstWantOptions->neg_addr
                   || (cilen != IPCP_CILEN_ADDR)
                   || (0xffffffff == pstPppInfo->ulPeerIPAddr))
                /* END:   Modified for PN:aaa分配ip无效或不下发 by wangyong 00138171, 2012/8/3 */
                {
                    /* Check CI length */
                    orc = CONFREJ;  /* Reject CI */
                    PPP_DBG_ERR_CNT(PPP_PHERR_204);
                    PPPC_INFO_LOG("\r\n PPP_IPCP_reqci: IPCP_CI_ADDR is not compatible(neg_addr)! ");
                    break;
                }

                PPP_GETADDR(ciaddr1, p);/* Parse source address (his) */

                if (ciaddr1 != 0L)
                {
                    pstHisOptions->neg_addr = 1;

                    /* save his address, no whether his address is changed */
                    pstGotOptions->neg_addr = 1;
                    pstHisOptions->hisaddr = ciaddr1;
                    pstGotOptions->hisaddr = ciaddr1;
                }
                else
                {
                    /*
                     * If he has no address, or if we both have his address but
                     * disagree about it, then NAK it with our idea.
                     * In particular, if we don't know his address, but he does,
                     * then accept it.
                     */
                    if (pstWantOptions->hisaddr == 0L)
                    {
                        orc = CONFREJ;
                        PPP_DBG_ERR_CNT(PPP_PHERR_205);
                        PPPC_INFO_LOG("\r\n PPP_IPCP_reqci: IPCP_CI_ADDR is not compatible(hisaddr)! ");
                        pstWantOptions->req_addr = 0;/* don't NAK with 0.0.0.0 later */
                    }
                    else
                    {
                        pstHisOptions->neg_addr = 1;
                        orc = CONFNAK;
                        pstGotOptions->neg_addr = 1;
                        PPP_DECPTR(sizeof(VOS_UINT32), p);
                        PPP_PUTADDR(pstGotOptions->hisaddr, p);
                    }
                }

                break;

            case IPCP_CI_COMPRESSTYPE:
                if (!pstWantOptions->neg_vj || (cilen != IPCP_CILEN_VJ))
                {
                    orc = CONFREJ;
                    PPP_DBG_ERR_CNT(PPP_PHERR_206);
                    PPPC_INFO_LOG("\r\n PPP_IPCP_reqci: IPCP_CI_COMPRESSTYPE is not compatible(neg_vj)! ");
                    break;
                }

                PPP_GETSHORT(cishort, p);

                if (cishort != PPP_VJ_COMP)
                {
                    PPP_DBG_ERR_CNT(PPP_PHERR_207);
                    orc = CONFREJ;
                    PPPC_INFO_LOG("\r\n PPP_IPCP_reqci: IPCP_CI_COMPRESSTYPE is not compatible(cishort)! ");
                    break;
                }

                pstHisOptions->neg_vj = 1;
                pstHisOptions->vj_protocol = cishort;

                PPP_GETCHAR(maxslotindex, p);
                if (maxslotindex > pstWantOptions->maxslotindex)
                {
                    PPP_DBG_OK_CNT(PPP_PHOK_891);
                    orc = CONFNAK;
                    PPP_DECPTR(1, p);
                    PPP_PUTCHAR(pstWantOptions->maxslotindex, p);
                    break;
                }

                PPP_GETCHAR(cflag, p);
                if (cflag && !pstWantOptions->cflag)
                {
                    PPP_DBG_OK_CNT(PPP_PHOK_892);
                    orc = CONFNAK;
                    PPP_DECPTR(1, p);
                    PPP_PUTCHAR(pstWantOptions->cflag, p);
                    break;
                }

                pstHisOptions->maxslotindex = maxslotindex;
                pstHisOptions->cflag = cflag;
                break;
            case IPCP_CI_DNSADDR0:
                if ((pstAllowOptions->neg_dnsaddr0 == 0)
               || (cilen != IPCP_CILEN_ADDR))
                {
                    PPP_DBG_ERR_CNT(PPP_PHERR_208);
                    orc = CONFREJ;
                    PPPC_INFO_LOG("\r\n PPP_IPCP_reqci: IPCP_CI_DNSADDR0 is not compatible(neg_dnsaddr0)! ");
                    break;
                }

                if (0 == pstAllowOptions->dnsaddr0)
                {
                    PPP_DBG_ERR_CNT(PPP_PHERR_209);
                    orc = CONFREJ;
                    PPPC_INFO_LOG("\r\n PPP_IPCP_reqci: IPCP_CI_DNSADDR0 is not compatible(dnsaddr0)! ");
                    break;
                }

                PPP_GETADDR( ciaddr1, p );
                pstHisOptions->neg_dnsaddr0 = 1;
                if ((ciaddr1 != pstAllowOptions->dnsaddr0) && ((0 == pstAllowOptions->accept_dnsaddr0)
                   || (ciaddr1 == 0)))
                {
                    PPP_DBG_OK_CNT(PPP_PHOK_893);
                    orc = CONFNAK;
                    PPP_DECPTR(sizeof(VOS_UINT32), p);
                    ciaddr1 = pstAllowOptions->dnsaddr0;
                    PPP_PUTADDR( ciaddr1, p );
                }
                else
                {
                    pstHisOptions->dnsaddr0 = ciaddr1;
                }

                break;
            case IPCP_CI_DNSADDR1:
                if ((pstAllowOptions->neg_dnsaddr1 == 0)
               || (cilen != IPCP_CILEN_ADDR))
                {
                    PPP_DBG_ERR_CNT(PPP_PHERR_210);
                    orc = CONFREJ;
                    PPPC_INFO_LOG("\r\n PPP_IPCP_reqci: IPCP_CI_DNSADDR1 is not compatible(neg_dnsaddr1)! ");
                    break;
                }

                if (0 == pstAllowOptions->dnsaddr1)
                {
                    PPP_DBG_ERR_CNT(PPP_PHERR_211);
                    orc = CONFREJ;
                    PPPC_INFO_LOG("\r\n PPP_IPCP_reqci: IPCP_CI_DNSADDR1 is not compatible(dnsaddr1)! ");
                    break;
                }

                PPP_GETADDR( ciaddr1, p );
                pstHisOptions->neg_dnsaddr1 = 1;
                if ((ciaddr1 == 0)
               || ((ciaddr1 != pstAllowOptions->dnsaddr1) && (0 == pstAllowOptions->accept_dnsaddr1)))
                {
                    PPP_DBG_OK_CNT(PPP_PHOK_894);
                    orc = CONFNAK;
                    PPP_DECPTR(sizeof(VOS_UINT32), p);
                    ciaddr1 = pstAllowOptions->dnsaddr1;
                    PPP_PUTADDR( ciaddr1, p );
                }
                else
                {
                    pstHisOptions->dnsaddr1 = ciaddr1;
                }

                break;
            case IPCP_CI_NBNSADDR0:
                if ((pstAllowOptions->neg_nbnsaddr0 == 0)
               || (cilen != IPCP_CILEN_ADDR))
                {
                    PPP_DBG_ERR_CNT(PPP_PHERR_212);
                    orc = CONFREJ;
                    PPPC_INFO_LOG("\r\n PPP_IPCP_reqci: IPCP_CI_NBNSADDR0 is not compatible(neg_nbnsaddr0)! ");
                    break;
                }

                if (0 == pstAllowOptions->nbnsaddr0)
                {
                    PPP_DBG_ERR_CNT(PPP_PHERR_213);
                    orc = CONFREJ;
                    PPPC_INFO_LOG("\r\n PPP_IPCP_reqci: IPCP_CI_NBNSADDR0 is not compatible(nbnsaddr0)! ");
                    break;
                }

                PPP_GETADDR( ciaddr1, p );
                pstHisOptions->neg_nbnsaddr0 = 1;
                if ((ciaddr1 == 0)
               || ((ciaddr1 != pstAllowOptions->nbnsaddr0) && (0 == pstAllowOptions->accept_nbnsaddr0)))
                {
                    PPP_DBG_OK_CNT(PPP_PHOK_895);
                    orc = CONFNAK;
                    PPP_DECPTR(sizeof(VOS_UINT32), p);
                    ciaddr1 = pstAllowOptions->nbnsaddr0;
                    PPP_PUTADDR( ciaddr1, p );
                }
                else
                {
                    pstHisOptions->nbnsaddr0 = ciaddr1;
                }

                break;
            case IPCP_CI_NBNSADDR1:
                if ((pstAllowOptions->neg_nbnsaddr1 == 0)
               || (cilen != IPCP_CILEN_ADDR))
                {
                    PPP_DBG_ERR_CNT(PPP_PHERR_214);
                    orc = CONFREJ;
                    PPPC_INFO_LOG("\r\n PPP_IPCP_reqci: IPCP_CI_NBNSADDR1 is not compatible(neg_nbnsaddr1)! ");
                    break;
                }

                if (0 == pstAllowOptions->nbnsaddr1)
                {
                    PPP_DBG_ERR_CNT(PPP_PHERR_215);
                    orc = CONFREJ;
                    PPPC_INFO_LOG("\r\n PPP_IPCP_reqci: IPCP_CI_NBNSADDR1 is not compatible(nbnsaddr1)! ");
                    break;
                }

                PPP_GETADDR( ciaddr1, p );
                pstHisOptions->neg_nbnsaddr1 = 1;
                if ((ciaddr1 == 0)
               || ((ciaddr1 != pstAllowOptions->nbnsaddr1) && (0 == pstAllowOptions->accept_nbnsaddr1)))
                {
                    PPP_DBG_OK_CNT(PPP_PHOK_896);
                    orc = CONFNAK;
                    PPP_DECPTR(sizeof(VOS_UINT32), p);
                    ciaddr1 = pstAllowOptions->nbnsaddr1;
                    PPP_PUTADDR( ciaddr1, p );
                }
                else
                {
                    pstHisOptions->nbnsaddr1 = ciaddr1;
                }

                break;
            default:
                PPP_DBG_ERR_CNT(PPP_PHERR_216);
                orc = CONFREJ;
                break;
        }

endswitch:
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
    /*lint +e801*/
}
/*lint +e529*/

/****************************************************************************
* CREATE DATE  ：2000/04/05                                                 *
* CREATED BY   ：Deng Yi Ou                                                 *
* FUNCTION     ：状态机up的处理函数                                         *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstFsm:状态机                                              *
* OUTPUT       ：                                                           *
* RETURN       ：0                                                          *
* CALLED BY    ：是回调函数，由状态机tlu动作宏(PPP_FSM_tlu)调用             *
****************************************************************************/
VOID PPP_IPCP_up(PPPFSM_S *pstFsm)
{
    VOS_UINT32 ulAccept = 0;
    PPPINFO_S* pstPppInfo = (PPPINFO_S*)pstFsm->pPppInfo;

    PPPC_WARNING_LOG("enter PPP_IPCP_up\r\n");

    /* IPCP协商结果是否可以接收 */
    ulAccept = PPP_IPCP_UpResetCi(pstPppInfo);
    if (VOS_OK != ulAccept)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_217);
        /* 协商结果不可接受,结束协商 */
        return;
    }

    /* 协商结果可以接受,向内核发送Ipcp Up事件 */
    PPP_Core_ReceiveEventFromProtocol(pstPppInfo,
                                      (LONG)PPP_EVENT_IPCPUP,
                                      NULL);
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
****************************************************************************/
VOID PPP_IPCP_down(PPPFSM_S *pstFsm)
{
    /* 重传定时器在PPP_FSM_tld中已经删除 */
    PPPIPCPINFO_S *pstIpcpInfo = (PPPIPCPINFO_S*)pstFsm->pProtocolInfo;

    if ((pstIpcpInfo->pstPppInfo)
        && (pstIpcpInfo->pstPppInfo->bVjFlag))
    {
        PPP_DBG_OK_CNT(PPP_PHOK_897);
        PPP_CompUserNumDel(pstIpcpInfo->pstPppInfo, PPP_USERSTAT_VJ);
    }

    PPP_Core_ReceiveEventFromProtocol(((PPPINFO_S *)pstFsm->pPppInfo),
                                      (LONG)PPP_EVENT_IPCPDOWN,
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
****************************************************************************/
VOID PPP_IPCP_finished(PPPFSM_S *pstFsm)
{
    PPP_Core_ReceiveEventFromProtocol(((PPPINFO_S *)pstFsm->pPppInfo),
                                      (LONG)PPP_EVENT_IPCPFINISHED,
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
****************************************************************************/
VOID PPP_IPCP_starting(PPPFSM_S *pstFsm)
{
    PPP_Core_ReceiveEventFromProtocol(((PPPINFO_S *)pstFsm->pPppInfo),
                                      (LONG)PPP_EVENT_IPCPSTARTING,
                                      NULL);
}

/****************************************************************************
* CREATE DATE  ：2000/04/05                                                 *
* CREATED BY   ：Deng Yi Ou                                                 *
* FUNCTION     ：初始化IPCP控制块                                           *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstPppInfo:PPP控制块                                       *
*                ulMyIpAddr:我的IP地址                                      *
*                ulPeerIpAddr:分配给对方的IP地址                            *
* OUTPUT       ：                                                           *
* RETURN       ：0                                                          *
* CALLED BY    ：                                                           *
****************************************************************************/
VOID PPP_IPCP_Init(PPPINFO_S* pstPppInfo, VOS_UINT32 ulMyIpAddr, VOS_UINT32 ulPeerIpAddr)
{
    PPPIPCPINFO_S *pstIpcpInfo;
    PPPFSM_S *pstFsm;
    PPP_IPCP_OPTION_S *pstAllowOptions, *pstWantOptions;
    PPP_IPCP_OPTION_S *pstGotOptions, *pstHisOptions;

    if ((NULL == pstPppInfo) || (NULL == pstPppInfo->pstIpcpInfo))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_218);
        return;
    }

    pstIpcpInfo = (PPPIPCPINFO_S*)pstPppInfo->pstIpcpInfo;
    pstFsm = &(pstIpcpInfo->stFsm);
    pstPppInfo->bPppStateFlg = PPP_STATE_NEGOING;

    /* IPCP控制块初始化 */
    pstIpcpInfo->pstPppInfo = pstPppInfo;
    pstIpcpInfo->ucUsedFlag = 1;

    /* 状态机初始化 */
    pstFsm->usProtocol    = PPP_IPCP;
    pstFsm->pstCallBacks  = &g_stIpcpCallbacks;
    pstFsm->pProtocolInfo = (char*)pstIpcpInfo;
    pstFsm->pPppInfo = (char*)pstIpcpInfo->pstPppInfo;
    PPP_FSM_Init(pstFsm);

    /* 协商参数初始化 */
    pstAllowOptions = &(pstIpcpInfo->stAllowOptions);
    pstWantOptions = &(pstIpcpInfo->stWantOptions);
    pstGotOptions = &(pstIpcpInfo->stGotOptions);
    pstHisOptions = &(pstIpcpInfo->stHisOptions);

    if (0 == pstPppInfo->bPppClient)
    {
        pstWantOptions->ouraddr = ulMyIpAddr;
        pstWantOptions->hisaddr = ulPeerIpAddr;
    }
    else
    {
        pstWantOptions->ouraddr = 0;
        pstWantOptions->hisaddr = 0;
    }

    pstWantOptions->neg_addr  = 1;
    pstWantOptions->req_addr  = 1;
    pstWantOptions->old_addrs = 0;
    pstWantOptions->neg_vj = 0;
    pstWantOptions->vj_protocol  = PPP_VJ_COMP;
    pstWantOptions->maxslotindex = MAX_STATES - 1; /* really max index */
    pstWantOptions->cflag = 0;
    pstWantOptions->neg_dnsaddr0  = 1;
    pstWantOptions->req_dnsaddr0  = 1;
    pstWantOptions->neg_nbnsaddr0 = 0;
    pstWantOptions->req_nbnsaddr0 = 0;
    pstWantOptions->neg_dnsaddr1     = 1;
    pstWantOptions->req_dnsaddr1     = 1;
    pstWantOptions->neg_nbnsaddr1    = 0;
    pstWantOptions->req_nbnsaddr1    = 0;
    pstWantOptions->accept_dnsaddr0  = 0;
    pstWantOptions->accept_dnsaddr1  = 0;
    pstWantOptions->accept_nbnsaddr0 = 0;
    pstWantOptions->accept_nbnsaddr1 = 0;

    *pstGotOptions = *pstWantOptions;

    pstAllowOptions->req_addr = 1;
    pstAllowOptions->neg_dnsaddr0  = 1;
    pstAllowOptions->req_dnsaddr0  = 1;
    pstAllowOptions->neg_nbnsaddr0 = 0;
    pstAllowOptions->req_nbnsaddr0 = 0;
    pstAllowOptions->neg_dnsaddr1     = 1;
    pstAllowOptions->req_dnsaddr1     = 1;
    pstAllowOptions->neg_nbnsaddr1    = 0;
    pstAllowOptions->req_nbnsaddr1    = 0;
    pstAllowOptions->accept_dnsaddr0  = 1;
    pstAllowOptions->accept_dnsaddr1  = 1;
    pstAllowOptions->accept_nbnsaddr0 = 0;
    pstAllowOptions->accept_nbnsaddr1 = 0;

    /* added by gxf 20030414    初始化dns */
    pstAllowOptions->dnsaddr0 = pstPppInfo->ulDNSAddr1;
    pstAllowOptions->dnsaddr1 = pstPppInfo->ulDNSAddr2;

    /* pstHisOptions 清零 */
    PPP_MemSet((VOID*)pstHisOptions, 0, sizeof(PPP_IPCP_OPTION_S));
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
VOS_UINT32 PPP_IPCP_UpResetCi(PPPINFO_S *pstPppInfo)
{
    PPPIPCPINFO_S * pstIpcpInfo = NULL;
    //UCHAR szTempImsi[M_IMSI_LEN] = {0};
    //UCHAR szTranImsi[M_IMSI_LEN] = {0};

    /* 协商成不同类型的用户 (包括重协商) */
    pstIpcpInfo = pstPppInfo->pstIpcpInfo;

    if (PPP_USERTYPE_MIP_RENEGO_TYPECHANGE(pstPppInfo,pstIpcpInfo))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_218);
        PPPC_INFO_LOG("\r\n PPP_IPCP_UpResetCi:Nego result isn't accepted!");

        HSGW_EmsTraceByRpIndex(pstPppInfo->ulRPIndex, HSGW_EMS_MODULE_PPP, EMS_PPP_33);
        if (0 == g_ulPppDBGStatisc[PPP_PHERR_218]%50)
        {
            //ImsiToString(pstPppInfo->stIMSI, szTempImsi);
            //AM_EncryptPrivacyData(szTempImsi,(M_IMSI_LEN - 1) , szTranImsi);
            PPPC_WARNING_LOG("\r\nPPP_Shell_IpcpUpNegotiateIp:cmip->sip");
        }
        PPP_SET_REL_CODE(pstPppInfo, AM_RELCODE_PPP_IPCP_NEGONAK);
        PPP_LCP_NegotiationDown(pstPppInfo->pstLcpInfo);  /*释放链路*/
        PPPC_INFO_LOG2("\r\n [ppp]PPP_Shell_IpcpUpNegotiateIp: mip -> sip pstPppInfo->bReNego = %u pstPppInfo->bIPTech = %u  ",
                      pstPppInfo->bReNego, pstPppInfo->bIPTech);

        return VOS_ERR;
    }

    /* success */
    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPP_Ipv4cp_Proc
 功能描述  : 获取ipv4地址后的ipcp流程处理函数
 输入参数  : PPPINFO_S *pstPppInfo
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年1月12日
    作    者   : T62595
    修改内容   : 新生成函数

*****************************************************************************/
VOID PPP_Ipv4cp_Proc( PPPINFO_S *pstPppInfo )
{
    /* 获取IPCP控制块 */
    if (NULL == pstPppInfo->pstIpcpInfo)
    {
        PPP_GETIPCPADDR(pstPppInfo->pstIpcpInfo, pstPppInfo->ulRPIndex);
        if (NULL == pstPppInfo->pstIpcpInfo)
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_219);
            /* Malloc Error */
            PPP_Debug_CoreEvent(pstPppInfo, PPP_LOG_ERROR, "Malloc IPCP CB Err!!");
            return;
        }
    }
    PPP_MemSet((void *)pstPppInfo->pstIpcpInfo, 0, sizeof(PPPIPCPINFO_S));

    /* 判断是否需要协商VJ压缩 */
    /*lint -e746*/
    if(VOS_OK == PPP_CheckVjLimit())
    /*lint +e746*/
    {
        /* 当重协商前就不支持VJ压缩，则仍然协商为不支持，否则支持VJ压缩 */
        if ((0 != pstPppInfo->bReNego)
            && (NULL != pstPppInfo->pstPppRenegoInfo)
            && (0 != ((PPPRENOGOINFO*)pstPppInfo->pstPppRenegoInfo)->ucIpcpFlag)
            && (0 == ((PPPRENOGOINFO*)pstPppInfo->pstPppRenegoInfo)->stIpcpOptions.neg_vj))
        {
             ((PPPCONFIGINFO_S*)pstPppInfo->pstConfigInfo)->bEnableVJComp = 0;
             PPP_DBG_OK_CNT(PPP_PHOK_898);

        }
        else
        {
            ((PPPCONFIGINFO_S*)pstPppInfo->pstConfigInfo)->bEnableVJComp = 1;
            PPP_DBG_OK_CNT(PPP_PHOK_899);
        }
    }
    else
    {
        ((PPPCONFIGINFO_S*)pstPppInfo->pstConfigInfo)->bEnableVJComp = 0;

        if ((NULL != pstPppInfo->pstPppRenegoInfo)
            && (0 != pstPppInfo->pstPppRenegoInfo->stIpcpOptions.neg_vj))
        {

             /* 重协商时不限制VJ压缩 y00125257 DTS2011111102645*/
             ((PPPCONFIGINFO_S*)pstPppInfo->pstConfigInfo)->bEnableVJComp = 1;
             PPP_DBG_OK_CNT(PPP_PHOK_900);
        }

    }

    PPP_IPCP_Init(pstPppInfo, pstPppInfo->ulIPAddr, pstPppInfo->ulPeerIPAddr);

    /* 向IPCP发送消息,触发IPCP开始协商 */
    PPP_IPCP_ReceiveEventFromCore(pstPppInfo->pstIpcpInfo, (VOS_UINT32)PPP_EVENT_FSM_OPEN, NULL );
    PPP_IPCP_ReceiveEventFromCore(pstPppInfo->pstIpcpInfo, (VOS_UINT32)PPP_EVENT_FSM_UP, NULL );

    return;
}


/*lint -restore */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
