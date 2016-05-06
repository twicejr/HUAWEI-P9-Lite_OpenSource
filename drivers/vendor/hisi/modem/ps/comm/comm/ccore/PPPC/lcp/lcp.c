/************************************************************************
*                                                                      *
*                             lcp.c                                    *
*                                                                      *
*  Project Code:       VRP3.0                                          *
*  Create Date:        2000/04/04                                      *
*  Author:             Deng Yi Ou                                      *
*  Modify Date:                                                        *
*  Document:                                                           *
*  Function:           PPP的LCP协议模块                                *
*  Others:                                                             *
*----------------------------------------------------------------------*
*                                                                      *
*  Copyright 2000-2002 VRP3.0 Team Beijing Institute HuaWei Tech, Inc. *
*                      ALL RIGHTS RESERVED                             *
*                                                                      *
*----------------------------------------------------------------------*
*                                                                      *
*   这个文件定义了LCP协议模块的全部接口函数和内部处理函数              *
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
#define         THIS_FILE_ID            PS_FILE_ID_PPPC_LCP_C


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
/* LCP回调函数数据结构 */
PPPFSMCALLBACK_S g_stLcpCallbacks =
{
    /* 动作：协商报文处理 */
    PPP_LCP_resetci,   /* 根据配置信息设置协商初始值 */
    PPP_LCP_cilen,     /* 我要发送的request报文长度 */
    PPP_LCP_addci,     /* 组织协商报文 */
    PPP_LCP_ackci,     /* 处理对方的ack报文 */
    PPP_LCP_nakci,     /* 处理对方的nak报文 */
    PPP_LCP_rejci,     /* 处理对方的reject报文 */
    PPP_LCP_reqci,     /* 处理对方的request报文 */
    PPP_LCP_extcode,   /* 处理协议特有的报文，如protocol reject等 */

    /* 事件：协议转入了终止状态 */
    PPP_LCP_up,        /* 协议up */
    PPP_LCP_down,       /* 协议暂时down,马上要重新协商.
                           与finished的区别是:对于PPPOE、DDR等的情况，
                           不用通知下层拆除链路 */
    PPP_LCP_finished,   /* 协议结束，通知底层:拆除链路.对于LCP,只要不是
                           PPPOE、DDR等的情况,则会设置reset定时器,
                           超时后重新启动协商 */
    PPP_LCP_starting,   /* tls(This-Layer-Started)动作中，通知下层:我准
                           备好了重新协商,如可能,请发一个up事件.
                           协议对这个动作没有具体规定,可以不实现*/

    /* 子协议信息 */
    "LCP"               /* 子协议名 */
};

/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*lint -save -e958 */
/*lint -e{572,778}*/

/****************************************************************************
* CREATE DATE  ：2000/04/04                                                 *
* CREATED BY   ：Deng Yi Ou                                                 *
* FUNCTION     ：LCP接收外部事件.事件包括：Up、Down、Open、Close            *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstLcpInfo:LCP控制块指针                                   *
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
VOID PPP_LCP_ReceiveEventFromCore (VOID *pstLcpInfo, VOS_UINT32 ulCmd, char *pPara)
{
    PPPFSM_S *pstFsm;
    PPPINFO_S *pstPppInfo = NULL;

    PPPC_INFO_LOG1("\r\n---Into PPP_LCP_ReceiveEventFromCore ulCmd: %d---\r\n", ulCmd);

    if (NULL == pstLcpInfo)
    {
        return;
    }

    pstFsm = &(((PPPLCPINFO_S*)pstLcpInfo)->stFsm);
    pstPppInfo = (PPPINFO_S *)pstFsm->pPppInfo;

    /* 性能统计:LCP协商尝试次数 */
    if (PPP_EVENT_FSM_OPEN == ulCmd)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_913);
        PPP_PerfInc(&g_stPppPerfStatistic.ulLcpTotal, PERF_TYPE_PPPC_LCP_NEGO_REQ_NUM, pstPppInfo->bEhrpdUser);
        PPPC_INFO_LOG1("****LcpTotal: %d****", g_stPppPerfStatistic.ulLcpTotal);
    }



    PPP_FSM_ReceiveEvent(pstFsm, ulCmd, pPara);

    return;
}

/****************************************************************************
* CREATE DATE  ：2000/04/05                                                 *
* CREATED BY   ：Deng Yi Ou                                                 *
* FUNCTION     ：LCP接收报文                                                *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstLcpInfo:LCP控制块                                       *
*                pHead:存放报文内存的头指针,应负责释放这段内存              *
*                pPacket:报文头位置                                         *
*                ulLen:报文长度                                             *
* OUTPUT       ：                                                           *
* RETURN       ：0                                                          *
* CALLED BY    ：PPP_Core_ReceivePacketFromShell                            *
****************************************************************************/
VOID PPP_LCP_ReceivePacket (VOID *pstLcpInfo, UCHAR* pHead, UCHAR* pPacket, VOS_UINT32 ulLen)
{
    PPPFSM_S *pstFsm = NULL;
    PPPINFO_S *pstPppInfo = NULL;


        if ((NULL == pstLcpInfo) || (NULL == pPacket))
    {
        return;
    }

    pstFsm = &(((PPPLCPINFO_S*)pstLcpInfo)->stFsm);

    pstPppInfo = (((PPPLCPINFO_S*)pstLcpInfo)->pstPppInfo);

    /*Added by y00125257 DTS2011051206336: 设置标志位表示收到过消息，如果未收到消息
    则不统计失败*/
    if (pstPppInfo != NULL)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_914);
        pstPppInfo->bRecvLcpMsgFlag = VOS_TRUE;
    }

    /* PPP ID参数只有在支持CCP压缩时在CCP模块有效,其他模带参是为了接口统一 */
    PPP_FSM_ReceivePacket(pstFsm, pHead, pPacket, ulLen, 1);/* Modified by liutao 38563 at 2004-09-22 V800R002 for PPP压缩移植 */
    return;

}

/****************************************************************************
* CREATE DATE  ：2000/04/04                                                 *
* CREATED BY   ：Deng Yi Ou                                                 *
* FUNCTION     ：确定LCP需要协商那些参数,在LCP初始化时进行                  *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstFsm    :状态机                                          *
* OUTPUT       ：                                                           *
* RETURN       ：0                                                          *
* CALLED BY    ：状态机中执行tls动作的宏PPP_FSM_tls                         *
****************************************************************************/
VOID PPP_LCP_resetci(PPPFSM_S *pstFsm)
{
    PPPLCPINFO_S *pstInfo;
    PPPCONFIGINFO_S *pstConfig;
    PPPINFO_S *pstPppInfo;
    PPP_LCP_OPTION_S *pstAllowOptions, *pstWantOptions;
    PPP_LCP_OPTION_S *pstGotOptions, *pstHisOptions;
    PPP_LCP_OPTION_S stRenegoOptions;
    VOS_UINT32 ulDefaultMruLen = 1500;

    if ( VOS_TRUE == g_ulHsgwA10TestDbgFlg )
    {
         PPPC_WARNING_LOG("SHOULD NEVER HAPPEN");
         return;
    }

    PPPC_INFO_LOG("\r\n---Into PPP_LCP_resetci---\r\n");

    pstInfo = (PPPLCPINFO_S *)pstFsm->pProtocolInfo;
    pstPppInfo = pstInfo->pstPppInfo;
    pstConfig = pstPppInfo->pstUsedConfigInfo;

    pstAllowOptions = &(pstInfo->stAllowOptions);
    pstWantOptions = &(pstInfo->stWantOptions);
    pstGotOptions = &(pstInfo->stGotOptions);
    pstHisOptions = &(pstInfo->stHisOptions);

    /* 各参数的缺省值 */

    /* pstHisOptions 清零 */
    PPP_MemSet((VOID*)pstHisOptions, 0, sizeof(PPP_LCP_OPTION_S));

    PPP_MemSet((VOID*)&stRenegoOptions, 0, sizeof(stRenegoOptions));

    if ((pstPppInfo->bReNego) ||(pstPppInfo->bReNegoV6))
    {
        VOS_MemCpy((VOID*)&stRenegoOptions, (VOID*)pstGotOptions, sizeof(PPP_LCP_OPTION_S));
    }

    /* 希望协商的选项 */
    pstWantOptions->neg_mru = ((ulDefaultMruLen == pstConfig->usMru) ? 0 : 1); /* Mru取默认值，不进行协商 */
    pstWantOptions->neg_asyncmap = 0;
    pstWantOptions->neg_upap = 0;
    pstWantOptions->neg_eap = 0;

    /* Added start by ZhangJun HT04406 at 2005-09-21 for PPP鉴权 */
    pstWantOptions->neg_chap = 0;
    /* Added end by ZhangJun HT04406 at 2005-09-21 for PPP鉴权 */
    pstWantOptions->neg_magicnumber = 1;

    pstWantOptions->neg_pcompression  = g_ulPCompressOnoff;
    pstWantOptions->neg_accompression = g_ulACompressOnoff;
    pstWantOptions->neg_lqr   = 0;
    pstWantOptions->neg_mrru  = 0;
    pstWantOptions->neg_ssnhf = 0;
    pstWantOptions->neg_discr = 0;
    pstWantOptions->neg_callback = 0;

    /*VA的MTU取至于VT   2002/4/28
    pstWantOptions->mru               = (VOS_UINT16)IF_GetConfigMTU(IF_GetIfByIndex(pstPppInfo->ulIfIndex));*/

    /*pstWantOptions->mru               = (VOS_UINT16)IF_GetConfigMTU(IF_GETTOPIF(IF_GetIfByIndex(pstPppInfo->ulIfIndex)));*/
    pstWantOptions->mru = pstConfig->usMru;

    /* 允许协商的选项 */
    *pstAllowOptions = *pstWantOptions;
    pstAllowOptions->neg_mru  = 1;
    pstAllowOptions->neg_upap = g_ulAuthPapOnoff;
    pstAllowOptions->neg_chap = g_ulAuthChapOnoff;
    pstAllowOptions->neg_eap = 1;

    pstAllowOptions->neg_pcompression  = g_ulPCompressOnoff;
    pstAllowOptions->neg_accompression = g_ulACompressOnoff;

    /* 按配置设置参数值 */

    if (pstPppInfo->bIsAsync)  /* 异步方式,协商ACCMAP */
    {
        pstWantOptions->neg_asyncmap  = 1;
        pstAllowOptions->neg_asyncmap = 1;

        pstWantOptions->asyncmap = pstPppInfo->ulLocalAccm;
    }

    if (pstConfig->bAuthRmtPap)
    {
        pstWantOptions->neg_upap = 1;
    }

    if (pstConfig->bAuthRmtChap)
    {
        pstWantOptions->neg_chap = 1;
    }

    if (pstConfig->bAuthRmtEap)
    {
        pstWantOptions->neg_eap = 1;
    }

    /* 最后得到的我的选项 */
    *pstGotOptions = *pstWantOptions;

    /* 修改其他参数修改其他参数 */
    pstGotOptions->numloops = 0;
    pstPppInfo->bLoopBacked = 0;

    pstFsm->ulTimeOutTime = pstConfig->ulNegTimeOut;

    /* modified by gxf for GGSN80 20030224  ulEchoTimeOutTime=0不启动发送Echo
       Request的定时器*/
    pstFsm->ulEchoTimeOutTime = 0 /*IF_GetIfByIndex(pstPppInfo->ulIfIndex)->if_ulKeepAlive*/;

    if ((pstPppInfo->bReNego) ||(pstPppInfo->bReNegoV6))
    {
        VOS_MemCpy((VOID*)pstGotOptions, (VOID*)&stRenegoOptions, sizeof(PPP_LCP_OPTION_S));
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
VOS_UINT16 PPP_LCP_cilen(PPPFSM_S *pstFsm)
{
    PPP_LCP_OPTION_S *pstGotOptions;

    pstGotOptions = &(((PPPLCPINFO_S*)pstFsm->pProtocolInfo)->stGotOptions);

    /*
     * NB: we only ask for one of CHAP and UPAP, even if we will
     * accept either.
     */


    /* CHAP优先 */
    return (VOS_UINT16)(PPP_LENCISHORT(pstGotOptions->neg_mru) +
                   PPP_LENCILONG(pstGotOptions->neg_asyncmap) +
                   PPP_LENCICHAP(pstGotOptions->neg_chap) +
                   PPP_LENCISHORT((!pstGotOptions->neg_chap && pstGotOptions->neg_upap)) +
                   PPP_LENCISHORT(pstGotOptions->neg_eap) +
                   PPP_LENCILQR(pstGotOptions->neg_lqr) +
                   PPP_LENCILONG(pstGotOptions->neg_magicnumber) +
                   PPP_LENCIVOID(pstGotOptions->neg_pcompression) +
                   PPP_LENCIVOID(pstGotOptions->neg_accompression) +
                   PPP_LENCISHORT(pstGotOptions->neg_mrru) +
                   PPP_LENCIVOID(pstGotOptions->neg_ssnhf) +
                   PPP_LENCIDISCR(pstGotOptions->neg_discr) +
                   PPP_LENCALLBACK(pstGotOptions->neg_callback)
    );


    /*End of liushuang*/
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
VOID PPP_LCP_addci(PPPFSM_S *pstFsm, UCHAR *pPacket)
{
    PPP_LCP_OPTION_S *pstGotOptions;

    pstGotOptions = &(((PPPLCPINFO_S*)pstFsm->pProtocolInfo)->stGotOptions);
    pstGotOptions->magicnumber = PPP_GetMagicNumber();

    ADDCISHORT(LCP_CI_MRU,
               pstGotOptions->neg_mru,
               pstGotOptions->mru
    );

    ADDCILONG(LCP_CI_ASYNCMAP,
              pstGotOptions->neg_asyncmap,
              pstGotOptions->asyncmap
    );

    /* CHAP优先 */
    ADDCICHAP(LCP_CI_AUTHTYPE,
              pstGotOptions->neg_chap,
              (VOS_UINT16)PPP_CHAP,
              pstGotOptions->chap_mdtype
    );

    ADDCISHORT(LCP_CI_AUTHTYPE,
               !pstGotOptions->neg_chap && pstGotOptions->neg_upap,
               (VOS_UINT16)PPP_PAP
    );
      /*End of liushuang*/

    ADDCISHORT(LCP_CI_AUTHTYPE,
             pstGotOptions->neg_eap,
             (VOS_UINT16)PPP_EAP
    );

    ADDCILQR(LCP_CI_QUALITY,
             pstGotOptions->neg_lqr,
             pstGotOptions->lqr_period
    );

    ADDCILONG(LCP_CI_MAGICNUMBER,
              pstGotOptions->neg_magicnumber,
              pstGotOptions->magicnumber);

    ADDCIVOID(LCP_CI_PCOMPRESSION,
              pstGotOptions->neg_pcompression
    );

    ADDCIVOID(LCP_CI_ACCOMPRESSION,
              pstGotOptions->neg_accompression
    );

    ADDCISHORT(LCP_CI_MRRU,
               pstGotOptions->neg_mrru,
               pstGotOptions->mrru
    );

    ADDCIVOID(LCP_CI_SSNHF,
              pstGotOptions->neg_ssnhf
    );

    ADDCIDISCR(LCP_CI_DISCR,
               pstGotOptions->neg_discr,
               pstGotOptions->discr_class,
               pstGotOptions->discr_len,
               pstGotOptions->discr_addr
    );

    ADDCICALLBACK(LCP_CI_CALLBACK,
                  pstGotOptions->neg_callback,
                  pstGotOptions->callbackopr,
                  pstGotOptions->callbackinfo,
                  (VOS_UINT32)(pstGotOptions->callbacklen)
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
VOS_UINT16 PPP_LCP_ackci(PPPFSM_S *pstFsm, UCHAR *pPacket, VOS_UINT32 ulLen)
{
    PPP_LCP_OPTION_S *pstGotOptions;
    UCHAR cilen, citype, cichar;
    VOS_UINT16 cishort;
    VOS_UINT32 cilong;


    pstGotOptions = &(((PPPLCPINFO_S*)pstFsm->pProtocolInfo)->stGotOptions);

    if (ulLen == 0)
    {
        return VOS_OK;
    }
    PPPC_INFO_LOG("\r\n c00265046:PPP_LCP_ackci 1. \r\n");

    /* L2TP需要的参数 */
#if (VRP_MODULE_SEC_L2TP == VRP_YES)
    /* 说明:根据VRP1.2的程序修改而来.
            协议上说应记录最后一个发送的报文,实际VRP1.2
            中记录的却是接收的最后一个ACK报文,不知有没有什么问题 */
    {
        PPPINFO_S *pstPppInfo = (PPPINFO_S*)(pstFsm->pPppInfo);
        if (pstPppInfo->pL2tpPara != NULL)
        {
            L2TP_SESSIONPARA_S *pstOptionalPara = (L2TP_SESSIONPARA_S*)pstPppInfo->pL2tpPara;

            /* 记下最后一个接收的ACK报文 */
            pstOptionalPara->ulLastSentLen = ulLen;
            VOS_MemCpy(pstOptionalPara->szLastSent, pPacket, ulLen);
        }
    }
#endif

    ACKCISHORT(LCP_CI_MRU, pstGotOptions->neg_mru, pstGotOptions->mru);
    PPPC_INFO_LOG("\r\n c00265046:PPP_LCP_ackci 2. \r\n");

    ACKCILONG(LCP_CI_ASYNCMAP,
              pstGotOptions->neg_asyncmap,
              pstGotOptions->asyncmap
    );
    PPPC_INFO_LOG("\r\n c00265046:PPP_LCP_ackci 3. \r\n");

    /* CHAP优先 */
    ACKCICHAP(LCP_CI_AUTHTYPE,
              pstGotOptions->neg_chap,
              PPP_CHAP,
              pstGotOptions->chap_mdtype
    );

    PPPC_INFO_LOG("\r\n c00265046:PPP_LCP_ackci 4. \r\n");

    ACKCISHORT(LCP_CI_AUTHTYPE,
               !pstGotOptions->neg_chap && pstGotOptions->neg_upap,
               PPP_PAP
    );

    PPPC_INFO_LOG("\r\n c00265046:PPP_LCP_ackci 5. \r\n");
    /*End of liushuang*/

    ACKCISHORT(LCP_CI_AUTHTYPE,
               pstGotOptions->neg_eap,
               PPP_EAP
    );

    PPPC_INFO_LOG("\r\n c00265046:PPP_LCP_ackci 8. \r\n");

    ACKCILQR(LCP_CI_QUALITY,
             pstGotOptions->neg_lqr,
             pstGotOptions->lqr_period
    );

    PPPC_INFO_LOG("\r\n c00265046:PPP_LCP_ackci 9. \r\n");

    ACKCILONG(LCP_CI_MAGICNUMBER,
              pstGotOptions->neg_magicnumber,
              pstGotOptions->magicnumber
    );

    PPPC_INFO_LOG("\r\n c00265046:PPP_LCP_ackci 10. \r\n");

    ACKCIVOID(LCP_CI_PCOMPRESSION,
              pstGotOptions->neg_pcompression
    );

    PPPC_INFO_LOG("\r\n c00265046:PPP_LCP_ackci 11. \r\n");

    ACKCIVOID(LCP_CI_ACCOMPRESSION,
              pstGotOptions->neg_accompression
    );

    PPPC_INFO_LOG("\r\n c00265046:PPP_LCP_ackci 12. \r\n");

    ACKCISHORT(LCP_CI_MRRU,
               pstGotOptions->neg_mrru,
               pstGotOptions->mrru
    );

    PPPC_INFO_LOG("\r\n c00265046:PPP_LCP_ackci 13. \r\n");

    ACKCIVOID(LCP_CI_SSNHF,
              pstGotOptions->neg_ssnhf
    );

    PPPC_INFO_LOG("\r\n c00265046:PPP_LCP_ackci 14. \r\n");

    ACKCIDISCR(LCP_CI_DISCR,
               pstGotOptions->neg_discr,
               pstGotOptions->discr_class,
               pstGotOptions->discr_len,
               pstGotOptions->discr_addr
    );

    PPPC_INFO_LOG("\r\n c00265046:PPP_LCP_ackci 15. \r\n");

    ACKCALLBACK(LCP_CI_CALLBACK,
                pstGotOptions->neg_callback,
                pstGotOptions->callbackopr,
                pstGotOptions->callbackinfo,
                (VOS_UINT32)(pstGotOptions->callbacklen)
    );

    PPPC_INFO_LOG1("\r\n c00265046_1:  PPP_LCP_ackci ulLen. \r\n", ulLen);

    /*lint -e801*/
    if (ulLen != 0)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_234);
        PPPC_WARNING_LOG("\r\n c00265046_1:  PPP_LCP_ackci bad. \r\n");
        goto bad;
    }
    /*lint +e801*/

    return VOS_OK;

bad:
    PPP_Debug_Error(pstFsm, PPP_LOG_WARNING, "lcp_ackci: received bad Ack!");
    PPP_DBG_ERR_CNT(PPP_PHERR_235);
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
VOS_UINT16 PPP_LCP_nakci(PPPFSM_S *pstFsm, UCHAR *pPacket, VOS_UINT32 ulLen)
{
    PPP_LCP_OPTION_S *pstGotOptions, *pstWantOptions;
    PPP_LCP_OPTION_S stNoOption;  /* 被对方no掉的选项 */
    PPP_LCP_OPTION_S stTryOption; /* 尝试与对方协商的选项 */
    PPPINFO_S *pstPppInfo;
    UCHAR citype, cichar, *next;
    VOS_UINT16 cishort      = 0;
    VOS_UINT32 cilong       = 0;
    VOS_UINT32 looped_back  = 0;
    SHORT cilen;

    pstGotOptions  = &(((PPPLCPINFO_S*)pstFsm->pProtocolInfo)->stGotOptions);
    pstWantOptions = &(((PPPLCPINFO_S*)pstFsm->pProtocolInfo)->stWantOptions);

    pstPppInfo = (PPPINFO_S*)pstFsm->pPppInfo;

    PPP_MemSet((VOID*)(&stNoOption), 0, sizeof(PPP_LCP_OPTION_S));
    stTryOption = *pstGotOptions;

    /*
     * Any Nak'd CIs must be in exactly the same order that we sent.
     * Check packet length and CI length at each step.
     * If we find any deviations, then this packet is bad.
     */

    /******************************************************************
     * no nak comp packets;
     *******************************************************************/

    /*
     * We don't care if they want to send us smaller packets than
     * we want.  Therefore, accept any MRU less than what we asked for,
     * but then ignore the new value when setting the MRU in the kernel.
     * If they send us a bigger MRU than what we asked, accept it, up to
     * the limit of the default MRU we'd get if we didn't negotiate.
     */
    NAKCISHORT(LCP_CI_MRU, neg_mru,
               if ((cishort <= pstWantOptions->mru) || (cishort <= PPP_DEFMRU))
               {
                   stTryOption.mru = cishort;
               }

    );

    /*
     * Add any characters they want to our (receive-side) asyncmap.
     */
    NAKCILONG(LCP_CI_ASYNCMAP, neg_asyncmap,
              stTryOption.asyncmap = pstGotOptions->asyncmap | cilong;
    );

    /*
     * If they've nak'd our authentication-protocol, check whether
     * they are proposing a different protocol, or a different
     * hash algorithm for CHAP.
     */
    /*lint -e801*/
    if ((pstGotOptions->neg_chap || pstGotOptions->neg_upap)
        && (ulLen >= PPP_CILEN_SHORT)
        && (pPacket[0] == LCP_CI_AUTHTYPE) && (pPacket[1] >= PPP_CILEN_SHORT))
    {
        cilen = pPacket[1];
        PPP_INCPTR(2, pPacket);
        PPP_GETSHORT(cishort, pPacket);
        ulLen -= 4;
        if ((cishort == PPP_PAP) && (cilen == PPP_CILEN_SHORT))
        {
            /*
             * If they are asking for PAP, then they don't want to do CHAP.
             * If we weren't asking for CHAP, then we were asking for PAP,
             * in which case this Nak is bad.
             */
            if (!pstGotOptions->neg_chap)
            {
                PPP_DBG_ERR_CNT(PPP_PHERR_236);
                goto bad;
            }

            stTryOption.neg_chap = 0;
        }
        else
        {
            if ((cishort == PPP_CHAP) && (cilen == PPP_CILEN_CHAP))
            {
                PPP_GETCHAR(cichar, pPacket);
                ulLen -= 1;
                if (pstGotOptions->neg_chap)
                {
                    /*
                     * We were asking for CHAP/MD5; they must want a different
                     * algorithm.  If they can't do MD5, we'll have to stop
                     * asking for CHAP.
                     */
                    if (cichar != pstGotOptions->chap_mdtype)
                    {
                        stTryOption.neg_chap = 0;
                    }
                    
                    /*End of liushuang*/
                }
                else
                {
                    /*
                     * Stop asking for PAP if we were asking for it.
                     */
                    stTryOption.neg_upap = 0;
                }
            }
            else
            {
                /*
                 * We don't recognize what they're suggesting.
                 * Stop asking for what we were asking for.
                 */
                if (pstGotOptions->neg_chap)
                {
                    stTryOption.neg_chap = 0;
                }
                else
                {
                    stTryOption.neg_upap = 0;
                }

                pPacket += cilen - PPP_CILEN_SHORT;
                ulLen -= cilen - PPP_CILEN_SHORT;
            }
        }
    }

    /*
     * Peer shouldn't send Nak for protocol compression or
     * address/control compression requests; they should send
     * a Reject instead.  If they send a Nak, treat it as a Reject.
     */
    if (!pstGotOptions->neg_chap)
    {
        NAKCISHORT(LCP_CI_AUTHTYPE, neg_upap,
                   stTryOption.neg_upap = 0;
        );
    }

    NAKCISHORT(LCP_CI_AUTHTYPE, neg_eap,
               stTryOption.neg_eap = 0;
    );

    /*
     * If they can't cope with our link quality protocol, we'll have
     * to stop asking for LQR.  We haven't got any other protocol.
     * If they Nak the reporting period, take their value XXX ?
     */
    NAKCILQR(LCP_CI_QUALITY, neg_lqr,
             if (cishort != PPP_LQR)
             {
                 stTryOption.neg_lqr = 0;
             }
             else
             {
                 stTryOption.lqr_period = cilong;
             }

    );

    /*
     * Check for a looped-back line.
     */
    NAKCILONG(LCP_CI_MAGICNUMBER, neg_magicnumber,
              stTryOption.magicnumber = PPP_GetMagicNumber();
              looped_back = 1;
    );

    NAKCIVOID(LCP_CI_PCOMPRESSION, neg_pcompression,
              stTryOption.neg_pcompression = 0;
    );
    NAKCIVOID(LCP_CI_ACCOMPRESSION, neg_accompression,
              stTryOption.neg_accompression = 0;
    );


    /*
    NAKCISHORT(LCP_CI_MRRU, neg_mrru,
       if (cishort <= pstWantOptions->mrru || cishort < PPP_DEFMRRU)
            stTryOption.mrru = cishort;
       );
     */
    NAKCISHORT(LCP_CI_MRRU, neg_mrru,
               if ((cishort <= pstWantOptions->mrru) || (cishort <= PPP_DEFMRRU))
               {
                   stTryOption.mrru = cishort;
               }

    );
    NAKCIVOID(LCP_CI_SSNHF, neg_ssnhf,
              stTryOption.neg_ssnhf = 0;
    );

    NAKCIDISCR(LCP_CI_DISCR, neg_discr,
               stTryOption.neg_discr = 0;
    );

    NAKCICALLBACK(LCP_CI_CALLBACK, neg_callback);

    while (ulLen > PPP_CILEN_VOID)
    {
        PPP_GETCHAR(citype, pPacket);
        PPP_GETCHAR(cilen, pPacket);

        if (cilen < 2)/*增加对非法报文配置项的处理*/
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_237);
            goto bad;
        }

        ulLen = (VOS_UINT32)(ulLen - cilen);
        if ((LONG)ulLen < 0)
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_238);
            goto bad;
        }

        next = pPacket + cilen - 2;

        switch (citype)
        {
            case LCP_CI_MRU:
                if (pstGotOptions->neg_mru
               || stNoOption.neg_mru
               || (cilen != PPP_CILEN_SHORT))
                {
                    PPP_DBG_ERR_CNT(PPP_PHERR_239);
                    goto bad;
                }

                break;

            case LCP_CI_ASYNCMAP:
                if (pstGotOptions->neg_asyncmap
               || stNoOption.neg_asyncmap
               || (cilen != PPP_CILEN_LONG))
                {
                    PPP_DBG_ERR_CNT(PPP_PHERR_240);
                    goto bad;
                }

                break;

            case LCP_CI_AUTHTYPE:
                if (pstGotOptions->neg_chap
               || stNoOption.neg_chap
               || pstGotOptions->neg_upap
               || stNoOption.neg_upap)
                {
                    PPP_DBG_ERR_CNT(PPP_PHERR_241);
                    goto bad;
                }

                break;

            case LCP_CI_MAGICNUMBER:
                if (pstGotOptions->neg_magicnumber
               || stNoOption.neg_magicnumber
               || (cilen != PPP_CILEN_LONG))
                {
                    PPP_DBG_ERR_CNT(PPP_PHERR_242);
                    goto bad;
                }

                break;

            case LCP_CI_PCOMPRESSION:
                if (pstGotOptions->neg_pcompression
               || stNoOption.neg_pcompression
               || (cilen != PPP_CILEN_VOID))
                {
                    PPP_DBG_ERR_CNT(PPP_PHERR_243);
                    goto bad;
                }

                break;

            case LCP_CI_ACCOMPRESSION:
                if (pstGotOptions->neg_accompression
               || stNoOption.neg_accompression
               || (cilen != PPP_CILEN_VOID))
                {
                    PPP_DBG_ERR_CNT(PPP_PHERR_244);
                    goto bad;
                }

                break;

            case LCP_CI_QUALITY:
                if (pstGotOptions->neg_lqr
               || stNoOption.neg_lqr
               || (cilen != PPP_CILEN_LQR))
                {
                    PPP_DBG_ERR_CNT(PPP_PHERR_245);
                    goto bad;
                }

                break;
            case LCP_CI_CALLBACK:
                if (pstGotOptions->neg_callback
               || stNoOption.neg_callback
               || (cilen < 3))
                {
                    PPP_DBG_ERR_CNT(PPP_PHERR_246);
                    goto bad;
                }

                break;
            default:
                break;
        }

        pPacket = next;
    }

    /* If there is still anything left, this packet is bad. */
    if (ulLen != 0)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_247);
        goto bad;
    }
    /*lint +e801*/

    /*
     * OK, the Nak is good.  Now we can update state.
     */
    if (pstFsm->ucState != (UCHAR)PPP_STATE_OPENED)
    {
        if (looped_back)
        {
            if (++stTryOption.numloops >= PPP_MAXLOOPSBACK)
            {
                PPP_Debug_Error(pstFsm, PPP_LOG_NOTICE, "Serial line is looped back.");
                pstPppInfo->bLoopBacked = 1;
                PPP_SET_REL_CODE(pstPppInfo, AM_RELCODE_PPP_LCP_LOOPBACK);
                PPP_LCP_NegotiationDown(pstFsm->pProtocolInfo);
            }
        }
        else
        {
            stTryOption.numloops = 0;
        }

        *pstGotOptions = stTryOption;
    }

    return VOS_OK;

bad:
    PPP_Debug_Error(pstFsm, PPP_LOG_WARNING, "lcp_nakci: received bad Nak!");
    return VOS_ERR;
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
VOS_UINT16 PPP_LCP_rejci(PPPFSM_S *pstFsm, UCHAR *pPacket, VOS_UINT32 ulLen)
{
    PPP_LCP_OPTION_S *pstGotOptions;
    UCHAR cichar   = 0;
    VOS_UINT16 cishort = 0;
    VOS_UINT32 cilong;
    PPP_LCP_OPTION_S stTryOption;        /* options to request next time */

    pstGotOptions = &(((PPPLCPINFO_S*)pstFsm->pProtocolInfo)->stGotOptions);
    stTryOption = *pstGotOptions;

    REJCISHORT(LCP_CI_MRU,
               neg_mru,
               pstGotOptions->mru
    );

    REJCILONG(LCP_CI_ASYNCMAP,
              neg_asyncmap,
              pstGotOptions->asyncmap
    );

    /* 早期PPP协议RFC1661中LCP配置选项无ACCM选项，网侧有可能会拒绝该选项，
       所以如果LCP协商不支持异步映射选项，那么异步映射默认值设定为0 */
    if (0 == stTryOption.neg_asyncmap)
    {
        stTryOption.asyncmap = 0;
    }


    /* CHAP优先 */
    REJCICHAP(LCP_CI_AUTHTYPE,
              neg_chap,
              PPP_CHAP,
              pstGotOptions->chap_mdtype
    );

    if (!pstGotOptions->neg_chap)
    {
        REJCISHORT(LCP_CI_AUTHTYPE,
                   neg_upap,
                   PPP_PAP
        );
    }

    REJCISHORT(LCP_CI_AUTHTYPE,
               neg_eap,
               PPP_EAP
    );

    REJCILQR(LCP_CI_QUALITY,
             neg_lqr,
             pstGotOptions->lqr_period
    );

    REJCILONG(LCP_CI_MAGICNUMBER,
              neg_magicnumber,
              pstGotOptions->magicnumber
    );

    REJCIVOID(LCP_CI_PCOMPRESSION,
              neg_pcompression
    );

    REJCIVOID(LCP_CI_ACCOMPRESSION,
              neg_accompression
    );

    REJCISHORT(LCP_CI_MRRU,
               neg_mrru,
               pstGotOptions->mrru
    );

    REJCIVOID(LCP_CI_SSNHF,
              neg_ssnhf
    );

    REJCIDISCR(LCP_CI_DISCR,
               neg_discr,
               pstGotOptions->discr_class,
               pstGotOptions->discr_len,
               pstGotOptions->discr_addr
    );

    REJCICALLBACK(LCP_CI_CALLBACK,
                  neg_callback,
                  (VOS_UINT32)(pstGotOptions->callbacklen),
                  pstGotOptions->callbackopr,
                  pstGotOptions->callbackinfo
    );

    /*
     * If there are any remaining CIs, then this packet is bad.
     */

    PPPC_INFO_LOG("\r\n c00265046_1: PPP_LCP_rejci. \r\n");

    /*lint -e801*/
    if (ulLen != 0)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_248);
        PPPC_WARNING_LOG("\r\n c00265046_1: PPP_LCP_rejci bad. \r\n");
        goto bad;
    }
    /*lint +e801*/

    /*
     * Now we can update state.
     */
    if (pstFsm->ucState != (UCHAR)PPP_STATE_OPENED)
    {
        *pstGotOptions = stTryOption;
    }

    return VOS_OK;

bad:
    PPP_Debug_Error(pstFsm, PPP_LOG_WARNING, "lcp_rejci: received bad Reject!");

    return VOS_ERR;
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
UCHAR PPP_LCP_reqci(PPPFSM_S *pstFsm, UCHAR *pPacket, VOS_UINT32 *pulLen)
{
    PPP_LCP_OPTION_S *pstAllowOptions;
    PPP_LCP_OPTION_S *pstGotOptions;
    PPP_LCP_OPTION_S *pstHisOptions;

    UCHAR *cip, *next, *currentpos;      /* Pointer to current and next CIs */

    UCHAR cilen, citype, cichar;/* Parsed len, type, char value */
    VOS_UINT16 cishort;         /* Parsed short value */
    VOS_UINT32 cilong;           /* Parse long value */
    UCHAR rc = CONFACK;        /* Final packet return code */
    SHORT orc;                /* Individual option return code */

    UCHAR *rejp;            /* Pointer to next char in reject frame */
    UCHAR *nakp;            /* Pointer to next char in Nak frame */
    LONG l = (LONG)*pulLen;        /* Length left */
    /*lint -e813*/
    UCHAR nak_buffer[PPP_DEFAULT_NEGO_PACKET_LEN];
    VOS_UINT16      usMru;

    /*lint +e813*/
    /* L2TP需要的参数 */
 /*#if (VRP_MODULE_SEC_L2TP == VRP_YES)*/
#if 1
    PPPINFO_S *pstPppInfo = (PPPINFO_S*)(pstFsm->pPppInfo);
    if (pstPppInfo->pL2tpPara != NULL)
    {
        L2TP_SESSIONPARA_S *pstOptionalPara = (L2TP_SESSIONPARA_S*)pstPppInfo->pL2tpPara;

        /* 记下第一个接收的LCP Conf-Req报文先 */
        if (pstOptionalPara->ulInitialRcvLen == 0)
        {
            pstOptionalPara->ulInitialRcvLen = *pulLen;
            VOS_MemCpy(pstOptionalPara->szInitialRcv, (CHAR*)pPacket, *pulLen);
        }

        /* 记下最后一个接收的LCP Conf-Req报文 */
        pstOptionalPara->ulLastRcvLen = *pulLen;
        VOS_MemCpy(pstOptionalPara->szLastRcv, (CHAR*)pPacket, *pulLen);
    }
 #endif

    pstAllowOptions = &(((PPPLCPINFO_S*)pstFsm->pProtocolInfo)->stAllowOptions);
    pstGotOptions = &(((PPPLCPINFO_S*)pstFsm->pProtocolInfo)->stGotOptions);
    pstHisOptions = &(((PPPLCPINFO_S*)pstFsm->pProtocolInfo)->stHisOptions);

    /*
     * Reset all his options.
     */
    (VOID)VOS_MemSet(pstHisOptions, 0, sizeof(PPP_LCP_OPTION_S));
    if (1 == pstAllowOptions->neg_asyncmap)
    {
        pstHisOptions->asyncmap = 0xffffffff;
    }

    /*
     * Process all his options.
     */
    next = pPacket;
    nakp = nak_buffer;
    rejp = pPacket;

    rc = CONFACK;            /* Assume success */

    if (l == 0)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_915);
        return rc;
    }

    while (l)
    {
        orc = CONFACK;           /* Assume success */
        currentpos = next;            /* Remember begining of CI */
        cip = next;
        /*lint -e801*/
        if ((l < 2)               /* Not enough data for CI header or */
           || (currentpos[1] < 2)           /*  CI length too small or */
           || (currentpos[1] > l))
        {
            /*  CI length too big? */
            PPP_Debug_Error(pstFsm, PPP_LOG_WARNING, "lcp_reqci: bad CI length!");
            orc   = CONFREJ;      /* Reject bad CI */
            cilen = (UCHAR)l;            /* Reject till end of packet */
            l = 0;            /* Don't loop again */
            PPP_DBG_OK_CNT(PPP_PHOK_916);
            goto endswitch;
        }
        /*lint +e801*/

        PPP_GETCHAR(citype, currentpos);        /* Parse CI type */
        PPP_GETCHAR(cilen, currentpos);        /* Parse CI length */
        l -= cilen;                /* Adjust remaining length */

        next += cilen;            /* Step to next CI */

        switch (citype)
        {
            /* Check CI type */
            case LCP_CI_MRU:
                if (!pstAllowOptions->neg_mru       /* Allow option? */
               || (cilen != PPP_CILEN_SHORT))
                {
                    /* Check CI length */
                    orc = CONFREJ;    /* Reject CI */
                    PPP_DBG_ERR_CNT(PPP_PHERR_249);
                    break;
                }

                PPP_GETSHORT(cishort, currentpos);/* Parse MRU */

                /*
                 * He must be able to receive at least our minimum.
                 * No need to check a maximum.  If he sends a large number,
                 * we'll just ignore it.
                 */
                if ((cishort < PPP_MINMRU) && (rc != CONFREJ))
                {
                    orc = CONFNAK;    /* Nak CI */
                    PPP_PUTCHAR(LCP_CI_MRU, nakp);
                    PPP_PUTCHAR(PPP_CILEN_SHORT, nakp);

                    usMru = PPP_GetDefaultMru();    /* 使用默认的MRU，从NV项中读取 */
                    PPP_PUTSHORT(usMru, nakp);/* Give him a hint */
                    PPP_DBG_OK_CNT(PPP_PHOK_917);
                    break;
                }

                pstHisOptions->neg_mru = 1;    /* Remember he sent MRU */
                pstHisOptions->mru = cishort;    /* And remember value */
                break;

            case LCP_CI_ASYNCMAP:
                if (!pstAllowOptions->neg_asyncmap
               || (cilen != PPP_CILEN_LONG))
                {
                    orc = CONFREJ;
                    PPP_DBG_ERR_CNT(PPP_PHERR_250);
                    break;
                }

                PPP_GETLONG(cilong, currentpos);

                /*
                 * Asyncmap must have set at least the bits
                 * which are set in lcp_allowoptions[unit].asyncmap.
                 */
                if (((pstAllowOptions->asyncmap & ~cilong) != 0) && (rc != CONFREJ))
                {
                    orc = CONFNAK;
                    PPP_PUTCHAR(LCP_CI_ASYNCMAP, nakp);
                    PPP_PUTCHAR(PPP_CILEN_LONG, nakp);
                    PPP_PUTLONG((pstAllowOptions->asyncmap | cilong), nakp);
                    PPP_DBG_OK_CNT(PPP_PHOK_918);
                    break;
                }

                pstHisOptions->neg_asyncmap = 1;
                pstHisOptions->asyncmap = cilong;
                break;

            case LCP_CI_AUTHTYPE:
                if ((cilen < PPP_CILEN_SHORT)
               || !(pstAllowOptions->neg_upap || pstAllowOptions->neg_chap || pstAllowOptions->neg_eap))
                {
                    /*
                     * Reject the option if we're not willing to authenticate.
                     */
                    orc = CONFREJ;
                    PPP_DBG_ERR_CNT(PPP_PHERR_251);
                    break;
                }

                PPP_GETSHORT(cishort, currentpos);

                /*
                 * Authtype must be UPAP or CHAP.
                 *
                 * Note: if both pstAllowOptions->neg_upap and pstAllowOptions->neg_chap are set,
                 * and the peer sends a Configure-Request with two
                 * authenticate-protocol requests, one for CHAP and one
                 * for UPAP, then we will reject the second request.
                 * Whether we end up doing CHAP or UPAP depends then on
                 * the ordering of the CIs in the peer's Configure-Request.
                 */
/* L2TP需要的参数 */
/*#if (VRP_MODULE_SEC_L2TP == VRP_YES)*/
#if 1

                if (pstPppInfo->bEhrpdUser)
                {
                    if (cishort == PPP_EAP)
                    {
                        /* 只判断长度就可以了mode by z00129699 for DTS2013102109070 */
                        if (cilen != PPP_CILEN_SHORT)
                        {
                            orc = CONFREJ;
                            PPP_DBG_ERR_CNT(PPP_PHERR_252);
                            break;
                        }

                        pstHisOptions->neg_eap = 1;
                        break;
                    }
                    else
                    {
                        orc = CONFREJ;
                        break;
                    }
                }
                else
                {
#endif
                    if (cishort == PPP_PAP)
                    {
                        if (pstHisOptions->neg_chap   /* we've already accepted CHAP */
                       || (cilen != PPP_CILEN_SHORT))
                        {
                            orc = CONFREJ;
                            PPP_DBG_ERR_CNT(PPP_PHERR_253);
                            break;
                        }

                        if (!pstAllowOptions->neg_upap && (rc != CONFREJ))
                        {
                            /* we don't want to do PAP */
                            orc = CONFNAK;/* NAK it and suggest CHAP */
                            PPP_PUTCHAR(LCP_CI_AUTHTYPE, nakp);
                            PPP_PUTCHAR(PPP_CILEN_CHAP, nakp);
                            PPP_PUTSHORT(PPP_CHAP, nakp);
                            PPP_PUTCHAR(pstAllowOptions->chap_mdtype, nakp);
                            PPP_DBG_OK_CNT(PPP_PHOK_919);
                            break;
                        }

                        pstHisOptions->neg_upap = 1;
                        break;
                    }

                    if (cishort == PPP_CHAP)
                    {
                        if (pstHisOptions->neg_upap   /* we've already accepted PAP */
                       || (cilen != PPP_CILEN_CHAP))
                        {
                            PPP_DBG_ERR_CNT(PPP_PHERR_254);
                            orc = CONFREJ;
                            break;
                        }

                        if (!pstAllowOptions->neg_chap && (rc != CONFREJ))
                        {
                            PPP_DBG_OK_CNT(PPP_PHOK_920);
                            /* we don't want to do CHAP */
                            orc = CONFNAK;/* NAK it and suggest PAP */
                            PPP_PUTCHAR(LCP_CI_AUTHTYPE, nakp);
                            PPP_PUTCHAR(PPP_CILEN_SHORT, nakp);
                            PPP_PUTSHORT(PPP_PAP, nakp);
                            break;
                        }

                        PPP_GETCHAR(cichar, currentpos);/* get digest type*/
                        if ((cichar != pstAllowOptions->chap_mdtype) && (rc != CONFREJ))
                        {
                            PPP_DBG_OK_CNT(PPP_PHOK_921);
                            orc = CONFNAK;
                            PPP_PUTCHAR(LCP_CI_AUTHTYPE, nakp);
                            PPP_PUTCHAR(PPP_CILEN_CHAP, nakp);
                            PPP_PUTSHORT(PPP_CHAP, nakp);
                            PPP_PUTCHAR(pstAllowOptions->chap_mdtype, nakp);
                            break;
                        }

                        pstHisOptions->chap_mdtype = cichar;/* save md type */
                        pstHisOptions->neg_chap = 1;
                        break;
                    }


                    if (cishort == PPP_EAP)
                    {
                        orc = CONFREJ;
                        break;
                    }
/* L2TP需要的参数 */
#if (VRP_MODULE_SEC_L2TP == VRP_YES)

                }
#endif
                /*
                 * We don't recognize the protocol they're asking for.
                 * Nak it with something we're willing to do.
                 * (At this point we know pstAllowOptions->neg_upap || pstAllowOptions->neg_chap.)
                 */
                if (rc == CONFREJ)
                {
                    PPP_DBG_ERR_CNT(PPP_PHERR_255);
                    break;
                }

                orc = CONFNAK;
                PPP_PUTCHAR(LCP_CI_AUTHTYPE, nakp);

/* L2TP需要的参数 */
#if (VRP_MODULE_SEC_L2TP == VRP_YES)

                if (pstPppInfo->bEhrpdUser)
                {
                    PPP_PUTCHAR(PPP_CILEN_SHORT, nakp);
                    PPP_PUTSHORT(PPP_EAP, nakp);
                }
                else
                {
#endif
                    if (pstAllowOptions->neg_chap)
                    {
                        PPP_PUTCHAR(PPP_CILEN_CHAP, nakp);
                        PPP_PUTSHORT(PPP_CHAP, nakp);
                        PPP_PUTCHAR(pstAllowOptions->chap_mdtype, nakp);
                    }
                    else
                    {
                        PPP_PUTCHAR(PPP_CILEN_SHORT, nakp);
                        PPP_PUTSHORT(PPP_PAP, nakp);
                    }
/* L2TP需要的参数 */
/*#if (VRP_MODULE_SEC_L2TP == VRP_YES)*/
#if 1
                }
#endif
                break;

            case LCP_CI_QUALITY:
                if (!pstAllowOptions->neg_lqr
               || (cilen != PPP_CILEN_LQR))
                {
                    PPP_DBG_ERR_CNT(PPP_PHERR_256);
                    orc = CONFREJ;
                    break;
                }

                PPP_GETSHORT(cishort, currentpos);
                PPP_GETLONG(cilong, currentpos);

                /*
                 * Check the protocol and the reporting period.
                 * XXX When should we Nak this, and what with?
                 */
                if ((cishort != PPP_LQR) && (rc != CONFREJ))
                {
                    PPP_DBG_OK_CNT(PPP_PHOK_922);
                    orc = CONFNAK;
                    PPP_PUTCHAR(LCP_CI_QUALITY, nakp);
                    PPP_PUTCHAR(PPP_CILEN_LQR, nakp);
                    PPP_PUTSHORT(PPP_LQR, nakp);
                    PPP_PUTLONG(pstAllowOptions->lqr_period, nakp);
                    break;
                }

                pstHisOptions->lqr_period = VOS_NTOHL(cilong);
                break;

            case LCP_CI_MAGICNUMBER:

                /* we should check if this link is loopbacked */
                if (!(pstAllowOptions->neg_magicnumber || pstGotOptions->neg_magicnumber)
               || (cilen != PPP_CILEN_LONG))
                {
                    PPP_DBG_ERR_CNT(PPP_PHERR_257);
                    orc = CONFREJ;
                    break;
                }

                PPP_GETLONG(cilong, currentpos);

                /*
                 * He must have a different magic number.
                 */
                if ((pstGotOptions->neg_magicnumber && (cilong == pstGotOptions->magicnumber))
                    || ((cilong == 0) && (rc != CONFREJ)))
                {
                    PPP_DBG_OK_CNT(PPP_PHOK_923);
                    cilong = PPP_GetMagicNumber();
                    orc = CONFNAK;
                    PPP_PUTCHAR(LCP_CI_MAGICNUMBER, nakp);
                    PPP_PUTCHAR(PPP_CILEN_LONG, nakp);
                    PPP_PUTLONG(cilong, nakp);
                    break;
                }

                pstHisOptions->neg_magicnumber = 1;
                pstHisOptions->magicnumber = cilong;
                break;

            case LCP_CI_PCOMPRESSION:
                if (!pstAllowOptions->neg_pcompression
               || (cilen != PPP_CILEN_VOID))
                {
                    PPP_DBG_ERR_CNT(PPP_PHERR_258);
                    orc = CONFREJ;
                    break;
                }

                pstHisOptions->neg_pcompression = 1;
                break;

            case LCP_CI_ACCOMPRESSION:
                if (!pstAllowOptions->neg_accompression
               || (cilen != PPP_CILEN_VOID))
                {
                    PPP_DBG_ERR_CNT(PPP_PHERR_259);
                    orc = CONFREJ;
                    break;
                }

                pstHisOptions->neg_accompression = 1;
                break;
            case LCP_CI_MRRU:
                if (!pstAllowOptions->neg_mrru || (cilen != PPP_CILEN_SHORT))
                {
                    PPP_DBG_ERR_CNT(PPP_PHERR_260);
                    orc = CONFREJ;
                    break;
                }

                PPP_GETSHORT(cishort, currentpos);/* Parse MRU */

                /*
                 * He must be able to receive at least our minimum.
                 * No need to check a maximum.  If he sends a large number,
                 * we'll just ignore it.
                 */
                if ((cishort < PPP_MINMRRU) && (rc != CONFREJ))
                {
                    PPP_DBG_OK_CNT(PPP_PHOK_924);
                    orc = CONFNAK;    /* Nak CI */
                    PPP_PUTCHAR(LCP_CI_MRRU, nakp);
                    PPP_PUTCHAR(PPP_CILEN_SHORT, nakp);
                    PPP_PUTSHORT((VOS_UINT16)PPP_MINMRRU, nakp);/* Give him a hint */
                    break;
                }

                pstHisOptions->mrru = cishort;    /* And remember value */
                pstHisOptions->neg_mrru = 1;    /* Remember he sent MRRU */
                break;

            case LCP_CI_SSNHF:
                if (!pstAllowOptions->neg_ssnhf
               || (cilen != PPP_CILEN_VOID))
                {
                    PPP_DBG_ERR_CNT(PPP_PHERR_261);
                    orc = CONFREJ;
                    break;
                }

                pstHisOptions->neg_ssnhf = 1;
                break;

            case LCP_CI_DISCR:
                if (!pstAllowOptions->neg_discr || (cilen < 3))
                {
                    PPP_DBG_ERR_CNT(PPP_PHERR_262);
                    orc = CONFREJ;
                    break;
                }

                PPP_GETCHAR(cichar, currentpos);/* Parse class */
                switch (cichar)
                {
                    case LCP_DISCR_NULL:
                        if (cilen != PPP_CILEN_DISCR)
                        {
                            PPP_DBG_ERR_CNT(PPP_PHERR_263);
                            orc = CONFREJ;
                            break;
                        }

                    /* following case without break */
                    /*lint -e825*/
                    case LCP_DISCR_IPADDR:
                    case LCP_DISCR_LOCASSIGN:
                    case LCP_DISCR_MACADDR:
                    case LCP_DISCR_MAGICNUM:
                    /*lint +e825*/
                        pstHisOptions->discr_len = cilen;
                        (VOID)VOS_MemCpy(pstHisOptions->discr_addr, (CHAR*)currentpos,
                                           (VOS_UINT32)(pstHisOptions->discr_len - PPP_CILEN_DISCR));
                        PPP_INCPTR( pstHisOptions->discr_len - PPP_CILEN_DISCR, currentpos);
                        break;
                    default:
                        PPP_DBG_ERR_CNT(PPP_PHERR_264);
                        orc = CONFREJ;
                        break;
                }

                pstHisOptions->discr_class = cichar;/* And remember value */
                pstHisOptions->neg_discr = 1;      /* Remember he sent MRRU */
                break;
            case LCP_CI_CALLBACK:

                /* if she negitiate callback she must neg the auth protocol */
                if (!pstAllowOptions->neg_callback || (cilen < 3))
                {
                    PPP_DBG_ERR_CNT(PPP_PHERR_265);
                    orc = CONFREJ;
                    break;
                }

                PPP_GETCHAR(pstHisOptions->callbackopr, currentpos);
                (VOID)VOS_MemCpy((char *)(pstHisOptions->callbackinfo), (char *)currentpos, (VOS_UINT32)(cilen - 3));
                currentpos += cilen - 3;
                pstHisOptions->neg_callback = 1;
                break;

            default:
                PPP_DBG_ERR_CNT(PPP_PHERR_266);
                orc = CONFREJ;
                break;
        }

endswitch:

        /* according protocol, we first send rej, then send nak and finally send ack */
        if (orc == CONFREJ)
        {
            (VOID)VOS_MemCpy((char *)rejp, (char *)cip, (VOS_UINT32)cilen); /* Move it */
            PPP_INCPTR(cilen, rejp);    /* Update output pointer */
            rc = CONFREJ;
            continue;
        }

        if (rc == CONFREJ)
        {
            continue;
        }

        if (orc == CONFNAK)
        {
            rc = CONFNAK;
            continue;
        }
    }

    /*
     * If we wanted to send additional NAKs (for unsent CIs), the
     * code would go here.  The extra NAKs would go at *nakp.
     * At present there are no cases where we want to ask the
     * peer to negotiate an option.
     */

    switch (rc)
    {
        case CONFACK:
            *pulLen = (VOS_UINT32)(next - pPacket);
            break;
        case CONFNAK:
            *pulLen = (VOS_UINT32)(nakp - nak_buffer);
            (VOID)VOS_MemCpy((char *)pPacket, (char *)nak_buffer, *pulLen);
            break;
        case CONFREJ:
            *pulLen = (VOS_UINT32)(rejp - pPacket);
            break;
        default:
            break;
    }

    return (rc);            /* Return final code */
}

/****************************************************************************
* CREATE DATE  ：2000/04/05                                                 *
* CREATED BY   ：Deng Yi Ou                                                 *
* FUNCTION     ：处理子协议私有的报文私有的报文类型                         *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstFsm: 状态机                                             *
*                ucCode: 报文类型                                           *
*                ucId:   报文ID                                             *
*                pHead:  存放报文内存的头指针,应负责释放这段内存            *
*                pPacket:报文头位置                                         *
*                ulLen:  报文长度                                           *
* OUTPUT       ：                                                           *
* RETURN       ：VOS_OK :合法报文                                           *
*                VOS_ERR:不能识别的报文                                     *
* CALLED BY    ：PPP_FSM_ReceivePacket                                      *
****************************************************************************/
/*lint -e529*/
VOS_UINT16 PPP_LCP_extcode(PPPFSM_S *pstFsm, UCHAR ucCode, UCHAR ucId, UCHAR *pHead, UCHAR *pPacket, VOS_UINT32
                       ulLen, VOS_UINT32 ulUserIndex)/* Added by liutao 38563 at 2004-10-08 V800R002 for PPP压缩移植 */
{
    PPP_LCP_OPTION_S *pstGotOptions;
    VOS_UINT32 ulMagicNumber;

    pstGotOptions = &(((PPPLCPINFO_S*)(pstFsm->pProtocolInfo))->stGotOptions);
    ulMagicNumber = pstGotOptions->magicnumber;

    switch (ucCode)
    {
        case ECHOREQ:

            /* 输出debug信息 */
            PPP_Debug_FsmEvent(pstFsm, (VOS_UINT32)PPP_EVENT_FSM_RXR);

            if (pstFsm->ucState == (UCHAR)PPP_STATE_OPENED)
            {
                /* ser action */
                /*lint -e438*/
                PPP_FSM_ser(pstFsm, ucId, pHead, pPacket, ulLen, ulMagicNumber);
                /*lint +e438*/
            }
            else
            {
                if ((pstFsm->ucState == (UCHAR)PPP_STATE_INITIAL)
               || (pstFsm->ucState == (UCHAR)PPP_STATE_STARTING))
                {
                    /* Illegal Event */
                    PPP_Debug_FsmIllegalEvent(pstFsm, PPP_EVENT_FSM_RXR);
                }

            }

            /* state not changed */
            break;

        case ECHOREP:

            /* 输出debug信息 */
            PPP_Debug_FsmEvent(pstFsm, (VOS_UINT32)PPP_EVENT_FSM_RXR);

            PPP_LCP_ReceiveEchoReply(pstFsm, ucId, pPacket, ulLen);
            break;

        case DISCREQ:

            /* 输出debug信息 */
            PPP_Debug_FsmEvent(pstFsm, (VOS_UINT32)PPP_EVENT_FSM_RXR);

            break;

        case IDENTIFIC:
            PPP_GETLONG(ulMagicNumber, pPacket);

            break;

        case TIMEREMAIN:
            break;

        default:
            PPP_DBG_ERR_CNT(PPP_PHERR_267);

            /* RUC event */
            PPP_FSM_ReceiveUnknownCode(pstFsm, ucId, pHead, pPacket, ulLen);
            return VOS_ERR;
    }

    (VOS_VOID)ulMagicNumber;
    (VOS_VOID)pPacket;
    return VOS_OK;
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
****************************************************************************/
VOID PPP_LCP_up(PPPFSM_S *pstFsm)
{
    VOS_UINT32 ulAccept = 0;


    PPPC_WARNING_LOG("enter:PPP_LCP_up\r\n");

    /* 根据LCP协商结果初始化其他协议的协商参数 */
    ulAccept = PPP_LCP_UpResetCi((PPPINFO_S *)pstFsm->pPppInfo);

    if (ulAccept == VOS_OK)
    {
        /* 协商结果可以接受,向内核发送Lcp Up事件 */
        PPP_Core_ReceiveEventFromProtocol((PPPINFO_S *)pstFsm->pPppInfo,
                                          (VOS_UINT32)PPP_EVENT_LCPUP,
                                          NULL);

        if (pstFsm->ucState == (UCHAR)PPP_STATE_OPENED)
        {
            if (pstFsm->ulEchoTimeOutTime > 0)
            {
                if (pstFsm->ulEchoTimeoutID == 0)
                {
                    /* 启动Echo Request定时器(循环定时器!!!) */
                    (VOS_VOID)VOS_StartRelTimer((HTIMER *)&(pstFsm->ulEchoTimeoutID), MID_PPPC,
                           pstFsm->ulEchoTimeOutTime, (VOS_UINT32)pstFsm, PPPC_LCP_SEND_ECHO_REQ_TIMER,
                           VOS_TIMER_NOLOOP, VOS_TIMER_PRECISION_0);
                }
                else
                {
                    PPP_DBG_ERR_CNT(PPP_PHERR_268);
                }
            }
        }

        /* 发送echo Req */
    }
    else
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_269);
        /* 协商结果不可接受,结束协商 */
        PPP_SET_REL_CODE(((PPPINFO_S *)pstFsm->pPppInfo), AM_RELCODE_PPP_LCP_NEGONAK);
        PPP_LCP_NegotiationDown(pstFsm->pProtocolInfo);
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
****************************************************************************/
VOID PPP_LCP_down(PPPFSM_S *pstFsm)
{
    PPPINFO_S *pstPppInfo = NULL;

    /* 重传定时器在PPP_FSM_tld中已经删除 */

    /* 删除Echo Request定时器先 */
    if (pstFsm->ulEchoTimeoutID)
    {
        (VOID)VOS_StopRelTimer(&(pstFsm->ulEchoTimeoutID));
        pstFsm->ulEchoTimeoutID = 0;
    }

    pstPppInfo = (PPPINFO_S *)(pstFsm->pPppInfo);
    if (NULL == pstPppInfo)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_270);
        return;
    }

    PPPC_EAP_Init((PPPINFO_S *)pstFsm->pPppInfo);



    PPP_Core_ReceiveEventFromProtocol(((PPPINFO_S *)pstFsm->pPppInfo),
                                      (VOS_UINT32)PPP_EVENT_LCPDOWN,
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
VOID PPP_LCP_finished(PPPFSM_S *pstFsm)
{
    PPPINFO_S                          *pstPppInfo = NULL;

    pstPppInfo = (PPPINFO_S *)(pstFsm->pPppInfo);
    if (NULL == pstPppInfo)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_270);
        return;
    }

    /* 接入鉴权失败通知RPA */
    if (PPPC_PPP_ID_FOR_ACCESS_AUTH == pstPppInfo->ulRPIndex)
    {
        /* 通知RPA接入鉴权结束 */
        if (AM_RELCODE_PPP_CHAP_RSPTIMEOUT == pstPppInfo->ucPppRleaseCode)
        {
            PPPC_HRPD_SendRpaAccessAuthRsp(CTTF_HRPD_PPP_ACCESS_AUTH_RETRAN_CHAP_TIMEOUT);

            /* 不拦截用户的拨号请求 */
            /* 如果没有收到CHAP鉴权的结果则按接入鉴权成功处理 */
            PPPC_AccessAuthSuccProc();
        }
        else if (AM_RELCODE_PPP_LCP_NEGOTIMEOUT == pstPppInfo->ucPppRleaseCode)
        {
            PPPC_HRPD_SendRpaAccessAuthRsp(CTTF_HRPD_PPP_ACCESS_AUTH_RETRAN_LCP_TIMEOUT);

            /* 如果接入鉴权LCP阶段已经失败则不需要在做业务 */
            PPPC_StopAllAccessAuthDelayProcTimer();
        }
        else
        {
            PPPC_WARNING_LOG1("Illegal RleaseCode When Fail to Access Auth", pstPppInfo->ucPppRleaseCode);
        }

        /* 如果正在进行接入鉴权,清除标志位 */
        PPPC_ChangeAccessAuthState(PS_FALSE, (VOS_UINT8)(pstPppInfo->ulRPIndex));
    }


    PPP_Core_ReceiveEventFromProtocol(((PPPINFO_S *)pstFsm->pPppInfo),
                                      (VOS_UINT32)PPP_EVENT_LCPFINISHED,
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
VOID PPP_LCP_starting(PPPFSM_S *pstFsm)
{
    PPP_Core_ReceiveEventFromProtocol(((PPPINFO_S *)pstFsm->pPppInfo),
                                      (VOS_UINT32)PPP_EVENT_LCPSTARTING,
                                      NULL);
}

/****************************************************************************
* CREATE DATE  ：2000/04/05                                                 *
* CREATED BY   ：Deng Yi Ou                                                 *
* FUNCTION     ：初始化LCP控制块                                            *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstPppInfo:PPP控制块                                       *
* OUTPUT       ：                                                           *
* RETURN       ：0                                                          *
* CALLED BY    ：封装函数                                                   *
****************************************************************************/
VOID PPP_LCP_Init(PPPINFO_S* pstPppInfo)
{
    PPPLCPINFO_S *pstLcpInfo;
    PPPFSM_S *pstFsm;
    PPP_LCP_OPTION_S *pstWantOptions;
    PPP_LCP_OPTION_S *pstAllowOptions;

    pstLcpInfo = (PPPLCPINFO_S*)pstPppInfo->pstLcpInfo;
    pstFsm = &(pstLcpInfo->stFsm);

    pstPppInfo->bPppClient = 1;

    pstWantOptions  = &(pstLcpInfo->stWantOptions);
    pstAllowOptions = &(pstLcpInfo->stAllowOptions);

    /* LCP控制块初始化 */
    pstLcpInfo->pstPppInfo = pstPppInfo;
    pstLcpInfo->ucUsedFlag = 1;
    /* 状态机初始化 */
    pstFsm->usProtocol    = PPP_LCP;
    pstFsm->pstCallBacks  = &g_stLcpCallbacks;
    pstFsm->pProtocolInfo = (char*)pstLcpInfo;
    pstFsm->pPppInfo = (char*)pstLcpInfo->pstPppInfo;
    PPP_FSM_Init(pstFsm);
    pstFsm->ucEchoId = 0;
    pstFsm->ulEchoTimeoutID = 0;

    /* modified by gxf for GGSN80 20030224  ulEchoTimeOutTime=0不启动发送Echo
       Request的定时器*/
    pstFsm->ulEchoTimeOutTime = 0 /*IF_GetIfByIndex(pstPppInfo->ulIfIndex)->if_ulKeepAlive*/;

    /*luofeng37050notify  协商参数值初始化,是否协商某个参数则在resetci函数中初始化 */
    /* 协商参数值初始化,是否协商某个参数则在resetci函数中初始化 */

    /* mru */
    /* 用一个假的先,以后替换掉 */
    pstWantOptions->mru  = 1500;
    pstWantOptions->mrru = pstWantOptions->mru;

    pstWantOptions->chap_mdtype  = CHAP_DIGEST_MD5;
    pstAllowOptions->chap_mdtype = CHAP_DIGEST_MD5;
}

/****************************************************************************
* CREATE DATE  ：2000/04/05                                                 *
* CREATED BY   ：Deng Yi Ou                                                 *
* FUNCTION     ：处理收到的Echo Reply报文                                   *
* MODIFY DATE  ： q34846 2004/06/17                                                                   *
* INPUT        ：pstFsm: 状态机                                             *
*                ucId:   报文ID                                             *
*                pPacket:报文头位置                                         *
*                ulLen:  报文长度                                           *
* OUTPUT       ：                                                           *
* RETURN       ：0                                                          *
* CALLED BY    ：PPP_LCP_extcode                                            *
****************************************************************************/

/*r002*/
VOID PPP_LCP_ReceiveEchoReply(PPPFSM_S *pstFsm, UCHAR ucId, UCHAR *pPacket, VOS_UINT32 ulLen)
{
    PPPINFO_S *pstPppInfo;
    PPPLCPINFO_S *pstLcpInfo;
    PPP_LCP_OPTION_S *pstGotOptions;
    VOS_UINT32 ulMagic;
    VOS_UINT32 ulReturn = VOS_OK;
    CHAR cDebug[200];
    CHAR *pBuf = cDebug;

    pstPppInfo = (PPPINFO_S *)pstFsm->pPppInfo;
    pstLcpInfo = (PPPLCPINFO_S *)pstFsm->pProtocolInfo;
    pstGotOptions = &(pstLcpInfo->stGotOptions);

    pstFsm->sRetransmits = PPP_DEFMAXCONFREQS;

    /* del the echo timer first */
    if (pstFsm->ulEchoTimeoutID != 0)
    {
        /* 删除Echo Request定时器先 */
        (VOID)VOS_StopRelTimer(&(pstFsm->ulEchoTimeoutID));
        pstFsm->ulEchoTimeoutID = 0;
    }

    /*lint -e801*/
    if (pstFsm->ulEchoTimeOutTime == 0) /*if someone have del the time first,we just return directly */
    {
        pBuf += VOS_sprintf(pBuf, "PPP_LCP_ReceiveEchoReply Error pstFsm->ulEchoTimeOutTime == 0");

        PPP_Debug_CoreEvent((PPPINFO_S*)pstFsm->pPppInfo, PPP_LOG_WARNING, cDebug);
        PPP_DBG_OK_CNT(PPP_PHOK_925);

        goto A11PROC;
    }

    pstFsm->ulEchoTimeOutTime = 0;

    if ((pstFsm->ucEchoId & 0xFF) != ucId)
    {
        /* wrong ID */
        pBuf += VOS_sprintf(pBuf, "PPP_LCP_ReceiveEchoReply Error (pstFsm->ucEchoId & 0xFF):%lu != ucId:%lu",
                            (VOS_UINT32)(pstFsm->ucEchoId & 0xFF), (VOS_UINT32)ucId );

        PPP_Debug_CoreEvent((PPPINFO_S*)pstFsm->pPppInfo, PPP_LOG_WARNING, cDebug);
        PPP_DBG_OK_CNT(PPP_PHOK_926);

        goto A11PROC;
    }

    /* Check the magic number - don't count replies from ourselves. */
    if (ulLen < 4)
    {
        /* no magic number */
        ulReturn = VOS_ERR;

        pBuf += VOS_sprintf(pBuf, "PPP_LCP_ReceiveEchoReply Error ulLen is %lu", ulLen);

        PPP_Debug_CoreEvent((PPPINFO_S*)pstFsm->pPppInfo, PPP_LOG_WARNING, cDebug);
        PPP_DBG_ERR_CNT(PPP_PHERR_271);

        goto A11PROC;
    }
    /*lint +e801*/

    PPP_GETLONG(ulMagic, pPacket);
    if (pstGotOptions->neg_magicnumber
        && (ulMagic == pstGotOptions->magicnumber))
    {
        /* 与自己的magic number一样,可能发生了自环 */
        if (++pstGotOptions->numloops >= PPP_MAXLOOPSBACK)
        {
            pstPppInfo->bLoopBacked = 1;

            /* 发生自环,结束协商 */
            PPP_SET_REL_CODE(pstPppInfo, AM_RELCODE_PPP_LCP_LOOPBACK);
            PPP_LCP_NegotiationDown(pstFsm->pProtocolInfo);
        }
    }
    else
    {
        pstGotOptions->numloops = 0;
        pstPppInfo->bLoopBacked = 0;
    }

    /* notify a11 to start dormant timer */
A11PROC:

    /*  需要加上编译宏，GGSN不处理 */
 #ifdef    __PRODUCT_TYPE_PDSN80
    if (VOS_ERR == ulReturn)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_272);
        (VOID)USM_NotifyReleaseUserMsg(pstPppInfo->ulRPIndex,  AM_RELCODE_PPP_ECHORRP_MAGIC_ERR);
    }
    pstFsm->ucEchoState = 0;
 #endif

    (VOS_VOID)ulReturn;
     (VOS_VOID)pPacket;
    return;
}

/****************************************************************************
* CREATE DATE  ：2000/04/05                                                 *
* CREATED BY   ：Deng Yi Ou                                                 *
* FUNCTION     ：发送Echo Request报文,并设置定时器准备下次发送              *
* MODIFY DATE  ：q34846 2004/06/17                                                           *
* INPUT        ：pFsm:状态机                                                *
* OUTPUT       ：                                                           *
* RETURN       ：0                                                          *
* CALLED BY    ：是定时器的回调函数,定时器超时时调用                        *
****************************************************************************/
VOID PPP_LCP_EchoTimeOut(VOID *pFsm)
{
    PPPFSM_S *pstFsm = (PPPFSM_S*)pFsm;

    pstFsm->ulEchoTimeoutID = 0;/* NOLOOP的定时器不需要删除了，直接置位 */
    PPP_DBG_OK_CNT(PPP_PHOK_927);

    /* 只有OPENED状态才发送Echo Request报文 */
    if (pstFsm->ucState == (UCHAR)PPP_STATE_OPENED)
    {
        CHAR cDebug[200];
        CHAR *pBuf = cDebug;

        /* 重传计数器减1 */
        pstFsm->sRetransmits--;

        pBuf += VOS_sprintf(pBuf, "Echo Timer Expired ,Retransmit = %d ", pstFsm->sRetransmits);

        PPP_Debug_CoreEvent((PPPINFO_S*)pstFsm->pPppInfo, PPP_LOG_WARNING, cDebug);

        /* 检查是否已超过最大重传次数 */
        if (pstFsm->sRetransmits <= 0)
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_273);
            pstFsm->sRetransmits = PPP_DEFMAXCONFREQS;
            pstFsm->ucEchoState = 0;

            /* 重传次数过多，结束协商 */
            PPP_SET_REL_CODE(((PPPINFO_S *)(pstFsm->pPppInfo)), AM_RELCODE_PPP_LCP_ECHOTIMEOUT);
            PPP_LCP_NegotiationDown(pstFsm->pProtocolInfo);

            return;
        }
        PPP_DBG_OK_CNT(PPP_PHOK_928);

        /* 发送报文 */
        PPP_LCP_SendEchoRequest(pstFsm);
    }

    return;
}

/****************************************************************************
* CREATE DATE  ：2000/04/05                                                 *
* CREATED BY   ：Deng Yi Ou                                                 *
* FUNCTION     ：发送Echo Request报文                                       *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstFsm:状态机                                              *
* OUTPUT       ：                                                           *
* RETURN       ：0                                                          *
* CALLED BY    ：PPP_LCP_EchoTimeOut                                        *
****************************************************************************/
/*lint -e529*/
VOID PPP_LCP_SendEchoRequest(PPPFSM_S *pstFsm)
{
    UCHAR *pHead, *pPacket;
    VOS_UINT32 ulLen = 0;
    VOS_UINT32 ulOffset;
    VOS_UINT32 ulMagic;
    PPP_LCP_OPTION_S *pstGotOptions;

    PPP_DBG_OK_CNT(PPP_PHOK_929);

    /* 得到magic number */
    pstGotOptions = &(((PPPLCPINFO_S*)pstFsm->pProtocolInfo)->stGotOptions);
    ulMagic = pstGotOptions->neg_magicnumber ? pstGotOptions->magicnumber : 0L;

    /* 预留出打PPP报文头的空间 */
    ulOffset = PPP_RESERVED_PACKET_HEADER;

    /* 申请内存 */
    pHead = g_ucPppSendPacketHead;

    pPacket = pHead + ulOffset;

    /* 报文情况(bytes) */

    /*
                                      1   2   3   4
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |            ...                |   |   |   |   |
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |--------- ulOffset ------------|
    pHead                           pPacket
     */

    PPP_PUTLONG(ulMagic, pPacket);
    pPacket -= 4;
    ulLen = 4;

    /* 报文情况 */

    /*
                                      1   2   3   4
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |            ...                |  Magic Number |
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |--------- ulOffset ------------|---- ulLen ----|
    pHead                           pPacket
     */
    pstFsm->ucEchoId++;
    PPP_FSM_SendPacket(pstFsm, ECHOREQ, pstFsm->ucEchoId, pHead, pPacket, ulLen);

    if (pstFsm->ulEchoTimeoutID)
    {
        /* 删除Echo Request定时器先 */
        (VOID)VOS_StopRelTimer(&(pstFsm->ulEchoTimeoutID));
        pstFsm->ulEchoTimeoutID = 0;
    }

    if (pstFsm->ulEchoTimeoutID == 0)
    {
        /* 重新启动Echo Request定时器 */
        (VOS_VOID)VOS_StartRelTimer((HTIMER *)&(pstFsm->ulEchoTimeoutID),
                                    MID_PPPC,
                                    pstFsm->ulEchoTimeOutTime,
                                    (VOS_UINT32)pstFsm,
                                    PPPC_LCP_SEND_ECHO_REQ_TIMER,
                                    VOS_TIMER_NOLOOP,
                                    VOS_TIMER_PRECISION_0);
    }
    else
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_275);
    }

    return;
}

/*r002 end*/

/****************************************************************************
* CREATE DATE  ：2000/04/05                                                 *
* CREATED BY   ：Deng Yi Ou                                                 *
* FUNCTION     ：LCP up后对协商结果进行检查,并确定以后的协商参数            *
* MODIFY DATE  ：modified by gxf 20030414                                   *
* INPUT        ：pstPppInfo:PPP控制块                                       *
* OUTPUT       ：                                                           *
* RETURN       ：VOS_ERR:协商结果不可接受,调用者应结束协商                  *
*                VOS_OK :协商结果可以接受,调用者应向上层协议报UP            *
* CALLED BY    ：PPP_LCP_up                                                 *
mode by zhaichao 00129699 2012.11.21
****************************************************************************/
VOS_UINT32 PPP_LCP_UpResetCi(PPPINFO_S *pstPppInfo)
{
    PPPLCPINFO_S *pstLcpInfo;
    PPP_LCP_OPTION_S *pstGotOptions;
    PPP_LCP_OPTION_S *pstHisOptions;

    pstLcpInfo = (PPPLCPINFO_S *)pstPppInfo->pstLcpInfo;
    pstGotOptions = &(pstLcpInfo->stGotOptions);
    pstHisOptions = &(pstLcpInfo->stHisOptions);

    /* 检查协商结果 */
    if (!pstGotOptions->neg_magicnumber)
    {
        pstGotOptions->magicnumber = 0;
    }

    if (!pstHisOptions->neg_magicnumber)
    {
        pstHisOptions->magicnumber = 0;
    }

    /*注意:pstGotOptions->neg_chap和pstGotOptions->neg_upap可能
       同时为1,在使用中chap优先级高,在此要先保证只有一个标志为1 */
    /* CHAP优先 */
    if (pstGotOptions->neg_chap == 1)
    {
        pstGotOptions->neg_upap = 0;
    }

    if (pstHisOptions->neg_chap == 1)
    {
        pstHisOptions->neg_upap = 0;
    }
    /*手机是客户端Add by chenmin 00265046*/
    pstPppInfo->bPppClient = 1;

    /*-------------------------------------------------------*/
#if 0
    /* eHRPD用户必须进行EAP认证 */
    if ((pstPppInfo->bEhrpdUser) && (0 == pstGotOptions->neg_eap))
    {
        return VOS_ERR;
    }
#endif
    /*设置Server端验证还未通过*/
    if ((pstGotOptions->neg_upap == 1) || (pstGotOptions->neg_chap == 1) || (pstGotOptions->neg_eap == 1))
    {
        pstPppInfo->bAuthServer = VRP_YES;
    }
    else
    {
        pstPppInfo->bAuthServer = VRP_NO;
    }

    /*设置Client端验证还未通过*/
    if ((pstHisOptions->neg_upap == 1) || (pstHisOptions->neg_chap == 1) || (pstHisOptions->neg_eap == 1))
    {
        pstPppInfo->bAuthClient = VRP_YES;
    }
    else
    {
        pstPppInfo->bAuthClient = VRP_NO;
    }

    /* 设置底层ACCMAP */
    pstPppInfo->ulRemoteAccm = pstHisOptions->asyncmap;
    pstPppInfo->ulLocalAccm = pstGotOptions->asyncmap;

    /* 设置MTU */
    if (pstHisOptions->neg_mru)
    {
        pstPppInfo->usMtu = pstHisOptions->mru > pstGotOptions->mru ? pstGotOptions->mru : pstHisOptions->mru;
    }
    else
    {
        pstPppInfo->usMtu =  pstGotOptions->mru;
    }

    if (pstPppInfo->usMtu > PPP_DEFMRRU)
    {
        pstPppInfo->usMtu = PPP_DEFMRRU;
    }

    return VOS_OK;
}

 #ifdef __PRODUCT_TYPE_PDSN80

/****************************************************************************
* CREATE DATE  ：2004/06/17                                                 *
* CREATED BY   ：QQ                                                     *
* FUNCTION     ：TDORMANT定时器超时调用该函数发送echo消息       *
* MODIFY DATE  ：                               *
* INPUT        ：ucFlag ucFlag为1，标识通知PPPC发送Echo消息，ucFlag为0，标识终止和Echo相关的处理。 *
* OUTPUT       ：                                                           *
* RETURN       ：VOS_ERR:协商结果不可接受,调用者应结束协商                  *
*                VOS_OK :协商结果可以接受,调用者应向上层协议报UP            *
* CALLED BY    ：A11_ActiveStateMachProc                                                *
****************************************************************************/
VOS_UINT32 A11_PPPC_EchoSet(A11_ECHO_E ucFlag, VOS_UINT32 ulRPIndex)
{
    PPPINFO_S *pstPppInfo;
    PPPFSM_S *pstFsm;
    PPPLCPINFO_S *pstLcpInfo;

    if (ulRPIndex > PPP_MAX_USER_NUM)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_276);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n PPP A11_PPPC_EchoSet : rpindex %d isn't exist!", ulRPIndex);
        return VOS_ERR;
    }

    if (PPP_CB_STATE_FREE == g_astPppPool[ulRPIndex].usState)    /* 用户已删除 */
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_277);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n PPP A11_PPPC_EchoSet : User %d isn't exist!", ulRPIndex);
        return VOS_ERR;
    }

    GETPPPINFOPTRBYRP(pstPppInfo, ulRPIndex);

    if (NULL == pstPppInfo)
    {
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n PPP A11_PPPC_EchoSet : pstPppInfo is NULL!");
        return VOS_OK;
    }


    pstLcpInfo = (PPPLCPINFO_S*)pstPppInfo->pstLcpInfo;

    if (pstLcpInfo == NULL)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_278);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n PPP A11_PPPC_EchoSet : User %d isn't exist!", ulRPIndex);
        return VOS_OK;
    }

    pstFsm = &(pstLcpInfo->stFsm);

    /* DTS2012030802073 修改echo超时取配置，次数默认还是5次 */
    if (A11_SEND_ECHO == ucFlag)
    {
        pstFsm->ulEchoTimeOutTime = pstPppInfo->pstUsedConfigInfo->ulNegTimeOut;
        pstFsm->sRetransmits = (SHORT)g_ulPppEchoRetransmit;
        pstFsm->ucEchoState = 1;
        PPP_DBG_OK_CNT(PPP_PHOK_930);

        if (pstFsm->ucState == (UCHAR)PPP_STATE_OPENED)
        {
            /* 发送echo Req */
            PPP_LCP_SendEchoRequest(pstFsm);
        }
    }
    else /* if during waiting the reply ,we get the traffic then delete all resource */
    {
        PPP_DBG_OK_CNT(PPP_PHOK_931);
        if (pstFsm->ulEchoTimeoutID != 0)
        {
            /* 删除Echo Request定时器先 */
            (VOID)VOS_StopRelTimer(&(pstFsm->ulEchoTimeoutID));
            pstFsm->ulEchoTimeoutID   = 0;
            pstFsm->ulEchoTimeOutTime = 0;
            pstFsm->sRetransmits = PPP_DEFMAXCONFREQS;
        }
    }

    return VOS_OK;
}

 #endif

/*lint +e572*/
/*lint -restore */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
