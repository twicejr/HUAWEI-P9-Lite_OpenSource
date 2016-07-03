



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
#define         THIS_FILE_ID            PS_FILE_ID_PPPC_TASK_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*lint -save -e958 */


VOS_UINT32 PPP_QueueInit(  )
{
    VOS_UINT32                      ulResult = VOS_OK;
    PTM_QUEUE_INFO_S                stQueInfo = { 0 };

    stQueInfo.ullSelfCsi    = PPP_SELF_CSI;
    stQueInfo.ulTaskId      = g_ulPPPTaskId;


    g_ulPppTaskTrace = 10;

    /* 创建定时器消息队列 */
    stQueInfo.ulQueType     = MSG_QUETYPE_VOSQ;
    stQueInfo.ulMsgType     = PPP_MSG_TYPE_TIMER;
    stQueInfo.ulQueLen      = PPP_MAXQUELEN * 4;
    stQueInfo.ulEvent       = VOS_TIMER_EVENT;
    VOS_sprintf(stQueInfo.szQueName, "3PTM");

    ulResult = PTM_CreateQueue(&stQueInfo, &g_ulPppTimeQueID);
    if (VOS_OK != ulResult)
    {
        PPPC_WARNING_LOG1("PPP_QueueInit: Create TIMER Que error 0x%x!", ulResult);
        return VOS_ERR;
    }

    /* 创建内部队列 */
    stQueInfo.ulQueType     = MSG_QUETYPE_VOSQ;
    stQueInfo.ulMsgType     = PPP_MSG_TYPE_INNER;
    stQueInfo.ulQueLen      = PPP_MAXQUELEN;
    stQueInfo.ulEvent       = PPP_INNERMSG_NOTIFY_PPP_EVENTBIT;
    VOS_sprintf(stQueInfo.szQueName, "PPPIN");

    ulResult = PTM_CreateQueue(&stQueInfo, &g_ulPppInnerMsgQueID);
    if (VOS_OK != ulResult)
    {
        PPPC_WARNING_LOG2("PTM_CreateQueue %s fail, return = 0x%x", stQueInfo.szQueName, ulResult);
        return ulResult;
    }

    /*================以下为PPP接收的共享队列====================*/
    /* 创建接收LAP的消息队列 */
    stQueInfo.ulQueType     = MSG_QUETYPE_MCQ;
    stQueInfo.ulMsgType     = PPP_MSG_TYPE_LAP;
    stQueInfo.ulQueLen      = PPP_MAXQUELEN;
    stQueInfo.ulEvent       = PPP_LAP_NOTIFY_PPP_EVENTBIT;
    VOS_sprintf(stQueInfo.szQueName, "SC%02lu_PPP_QUE", PPP_SELF_CMPIDX);

    ulResult = PTM_CreateQueue(&stQueInfo, (VOS_UINT32 *)&g_pstPppLAPNotifyQueID);
    if (VOS_OK != ulResult)
    {
        return VOS_ERR;
    }

     /* 创建接收DDU的消息队列 */
    stQueInfo.ulQueType     = MSG_QUETYPE_MCQ;
    stQueInfo.ulMsgType     = PPP_MSG_TYPE_DDU;
    stQueInfo.ulQueLen      = PPP_MAXQUELEN ;
    stQueInfo.ulEvent       = 0;                /* 不用写事件 */
    VOS_sprintf(stQueInfo.szQueName, "S%luPP", PPP_SELF_CMPIDX);

    ulResult = PTM_CreateQueue(&stQueInfo, (VOS_UINT32 *)&g_pstPppNegoQueID);
    if (VOS_OK != ulResult)
    {
        PPPC_WARNING_LOG1("[ppp]PPP_QueueInit: Create DDU Que error 0x%x!",ulResult);
        return VOS_ERR;
    }

    return VOS_OK;
}


VOS_UINT32 PPP_TaskInit(  )
{
    VOS_UINT32                      ulRet = VOS_OK;

    /* 初始化组件参数 */
    g_stPppCompInfo.ullSelfCsi   = PSM_Inf_GetSelfCSI(E_COMP_TYPE_PPPT);
    g_stPppCompInfo.ullSelfSgId  = PSM_Inf_GetSelfSGID();
    g_stPppCompInfo.ulSelfCmpIdx = PSM_Inf_GetCmpIndexInOSByCSI(PPP_SELF_CSI);
    g_stPppCompInfo.ulSelfCmpIdxInSG = PSM_Inf_GetCmpSameTIndexInSGByCSI(PPP_SELF_CSI);
    g_stPppCompInfo.ulHandle     = MID_PPPC;



    /* 第一阶段初始化 */
    /*lint -e746*/
    ulRet = PPP_CompInit1();
    /*lint +e746*/
    if (VOS_OK != ulRet)
    {

        PPPC_WARNING_LOG1("[ppp]PPP_TaskInit: PPP_CompInit1 error %lu!",ulRet);
        return VOS_ERR;
    }

    PPP_ClearCnt();

    return VOS_OK;
}




VOS_UINT32 PPP_TaskEntry(VOID)
{
    VOS_UINT32                  ulRet = VOS_OK;


    /* 创建队列*/
    ulRet = PPP_QueueInit();
    if (VOS_OK != ulRet)
    {
        PPPC_WARNING_LOG1("[ppp]PPP_TaskEntry: PPP_QueueInit error %lu!",ulRet);
        return VOS_ERR;
    }

    /* 第二阶段初始化 */
    /*lint -e746*/
    ulRet = PPP_CompInit2();
    if (VOS_OK != ulRet)
    {
        PPPC_WARNING_LOG1("[ppp]PPP_TaskEntry: PPP_CompInit2 error %lu!",ulRet);
        return VOS_ERR;
    }

    /* 第三阶段初始化 */
    ulRet = PPP_CompInit3();
    if (VOS_OK != ulRet)
    {
        PPPC_WARNING_LOG1("[ppp]PPP_TaskEntry: PPP_CompInit3 error %lu!",ulRet);
        return VOS_ERR;
    }

    PPP_SubBoardInit();




    /* 任务处理 */
    /* 屏蔽coverity报错，队列死读，无需跳出 */
#if 0
    // coverity[no_escape][loop_top][loop_bottom]
    for(;;)
    {
        ulEvRcv = 0x0;

        /* 读事件信息 */
        if (VOS_OK == VOS_Ev_Read(VOS_TIMER_EVENT
                                   | PPP_AAA_EVENTBIT
                                   | PPP_COMPRESS_MSG_EVENTBIT
                                   | PPP_A11_NOTIFY_PPP_EVENTBIT
                                   | PPP_LAP_NOTIFY_PPP_EVENTBIT
                                   | PPP_L2TP_NOTIFY_PPP_EVENTBIT
                                   | DIAM_AUTH_PPP_EVENT
                                   | PPP_INNERMSG_NOTIFY_PPP_EVENTBIT,
                                   &ulEvRcv,
                                   (VOS_EV_ANY | VOS_NO_WAIT), 0))/*添加事件位*/
        {

            /* 处理定时器事件 */
            if (ulEvRcv & VOS_TIMER_EVENT)
            {
                PPP_TIMERTaskProc();
            }

            /* 处理A11事件 */
            if (ulEvRcv & PPP_A11_NOTIFY_PPP_EVENTBIT)
            {
                PPP_A11TaskProc();
            }
             ///TODO:luofang处理压缩事件

            /* 处理AAA事件 */
            if (ulEvRcv & PPP_AAA_EVENTBIT)
            {
                PPP_AAATaskProc();
            }

            /* 处理DIAM AAA事件 */
            if (ulEvRcv & DIAM_AUTH_PPP_EVENT)
            {
                PPP_DiamAAATaskProc();
            }

            /* 处理LAP事件 */
            if (ulEvRcv & PPP_LAP_NOTIFY_PPP_EVENTBIT)
            {
                PPP_LAPTaskProc();
            }

             /* 处理L2TP事件 */
            if (ulEvRcv & PPP_L2TP_NOTIFY_PPP_EVENTBIT)
            {
                PPP_L2TPTaskProc();
            }

            if (ulEvRcv & PPP_INNERMSG_NOTIFY_PPP_EVENTBIT)
            {
               /* 处理内部消息 */
                PPP_InnerMsgProc();
            }
        }

        /* 处理协商事件 */
        PPP_NEGOTaskProc();
        /*lint +e746*/
        VOS_T_Delay(10); /* 释放CPU */
    }
#endif
    return VOS_OK;
}
#if 0

VOID PPP_InnerMsgProc()
{
    VOS_UINT32 aulMsg[4] = {0};
    UCHAR *pucMsg = VOS_NULL_PTR;
    VOS_UINT32 ulFlowControl = 0;

    while (VOS_OK == VOS_Que_Read(g_ulPppInnerMsgQueID, aulMsg, VOS_NO_WAIT, 0))
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1366);
        pucMsg = (UCHAR*)aulMsg[1];

        if ( VOS_NULL_PTR != pucMsg )
        {
            /*分发内部消息*/
            PPP_DispatchInnerMsg(pucMsg);
            PGP_RTDistributeFreeMsg(pucMsg);
        }

        PPP_DBG_OK_CNT(PPP_PHOK_1367);

        ulFlowControl++;
        if(PPP_FLOWCONTROL_MAX < ulFlowControl)
        {
            (VOID)VOS_Ev_Write(g_ulPPPTaskId, PPP_INNERMSG_NOTIFY_PPP_EVENTBIT);
            break;
        }
    }

    return;
}



VOID PPP_DispatchInnerMsg(UCHAR *pucMsg)
{
    if ( VOS_NULL_PTR == pucMsg )
    {
        return;
    }
#if 0
    switch (RTD_GET_MSGCODE(pucMsg))
    {
        case PPP_INNER_MSG_CODE_RENEGO :
             PPP_InnerRengeoMsgProc(pucMsg);
             break;

        default:
            break;
    }
#endif
    return;
}



VOID PPP_InnerRengeoMsgProc(UCHAR *pucMsg)
{
    VOS_UINT32  ulSelfCpuId = DVM_SELF_CPUID;

    PPP_DBG_OK_CNT(PPP_PHOK_1368);
    if ( VOS_NULL_PTR == pucMsg )
    {
        return;
    }

    if ((PPP_CPU_ONLINE == g_ulPppSubBordStat[0])
        && (PPP_CPU_ONLINE == g_ulPppSubBordStat[1]))
    {
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
            "\r\n [ppp]PPP_ReNegoCompressTask: Subboard is restored! SelfCpuId = [%d]"
            ,ulSelfCpuId);
         g_ulReNegoTaskId = 0;
         return;
    }

    PPP_DBG_OK_CNT(PPP_PHOK_1369);
    PPP_ReNegoCompressTask(pucMsg);

    return;
}


VOID PPP_TIMERTaskProc()
{
    VOS_UINT32 ulFlowControl = 0; /* 定义并初始化流控变量 */
    VOS_UINT32 ulRetMsg[4] = {0};

    while (VOS_OK == VOS_Que_Read(g_ulPppTimeQueID, ulRetMsg, VOS_NO_WAIT, 0))
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1370);
        if (ulRetMsg[2] != VOS_NULL_PTR)
        {
            ((VOID (*) (VOID *))(ulRetMsg[2]))((VOID*)(ulRetMsg[3]));
        }

        if (++ulFlowControl >= g_ulPPPTimerFlowctrl)
        {
            PPP_DBG_OK_CNT(PPP_PHOK_1371);
            (VOID)VOS_Ev_Write(g_ulPPPTaskId, VOS_TIMER_EVENT);
            break;
        }
    }
    return;
}



VOID PPP_A11TaskProc()
{
    VOS_UINT32 ulFlowControl = 0; /* 定义并初始化流控变量  */
    VOID *pMsg = VOS_NULL_PTR;
    VOS_UINT32 ulRetMsg[4] = {0};

    while (VOS_OK == VOS_Que_Read(g_ulPppA11NotifyQueID, ulRetMsg, VOS_NO_WAIT, 0))
    {
       pMsg = (VOID *)ulRetMsg[1];
       if (VOS_NULL_PTR == pMsg)
       {
           VOS_DBGASSERT(0);
           continue;
       }

       PPP_A11MsgProc(pMsg);
       PGP_RTDistributeFreeMsg(pMsg);

       if (++ulFlowControl >= g_ulPPPA11Flowctrl)
       {
           (VOID)VOS_Ev_Write(g_ulPPPTaskId, PPP_A11_NOTIFY_PPP_EVENTBIT);
           break;
       }
    }
   return;
}


VOID PPP_DiamAAATaskProc()
{
    VOS_UINT32 ulFlowControl = 0; /* 定义并初始化流控变量 */
    VOS_UINT32 ulRetMsg[4] = {0};
    VOID *pMsg = VOS_NULL_PTR;

    while (VOS_OK == VOS_Que_Read(g_ulPppDiamAaaQueID, ulRetMsg, VOS_NO_WAIT, 0))
    {
        pMsg = (DIAM_AUTHRSP_S *)ulRetMsg[1];
        PPP_DBG_OK_CNT(PPP_PHOK_1372);

        if (VOS_NULL_PTR == pMsg)
        {
            VOS_DBGASSERT(0);
            continue;
        }

#if (VRP_MODULE_LINK_PPP_EAP == VRP_YES)
        PPP_EAP_ReceiveDiamAAAResult((DIAM_AUTHRSP_S *)pMsg);
#endif
        PGP_RTDistributeFreeMsg(pMsg);

        if (++ulFlowControl >= g_ulPPPAAAFlowctrl)
        {
            (VOID)VOS_Ev_Write(g_ulPPPTaskId, DIAM_AUTH_PPP_EVENT);
            break;
        }
    }
    return;
}


VOID PPP_AAATaskProc()
{
    VOS_UINT32 ulFlowControl = 0; /* 定义并初始化流控变量 */
    VOS_UINT32 ulRetMsg[4] = {0};
    VOID *pMsg = VOS_NULL_PTR;

    while (VOS_OK == VOS_Que_Read(g_ulPppAaaQueID, ulRetMsg, VOS_NO_WAIT, 0))
    {
        pMsg = (AAA_AUTHRSP_S *)ulRetMsg[1];
        PPP_DBG_OK_CNT(PPP_PHOK_1373);

        if (VOS_NULL_PTR == pMsg)
        {
            VOS_DBGASSERT(0);
            continue;
        }

        PPP_AAAMsgProc((AAA_AUTHRSP_S *)pMsg);
        PGP_RTDistributeFreeMsg(pMsg);

        if (++ulFlowControl >= g_ulPPPAAAFlowctrl)
        {
            (VOID)VOS_Ev_Write(g_ulPPPTaskId, PPP_AAA_EVENTBIT);
            break;
        }
    }
    return;
}
#endif
#if 0

VOID PPP_NEGOTaskProc()
{
    VOS_UINT32 ulFlowControl = 0; /* 定义并初始化流控变量 */
    VOID *pMsg = VOS_NULL_PTR;
    VOS_UINT32 ulMsgCode = 0;
    VOS_UINT32 ulRet = VOS_OK;

     while (VOS_OK == VOS_MCReadQue(g_pstPppNegoQueID,
                                    &pMsg,
                                    &ulMsgCode,
                                    VOS_MCQUEUE_NO_WAIT,
                                    0))
     {
         if (VOS_NULL_PTR == pMsg)
         {
             VOS_DBGASSERT(0);
             continue;
         }

         PPP_DBG_OK_CNT(PPP_PHOK_1374);
         ulRet = PPP_NegoMsgProc((UCHAR *)pMsg);
         if (VOS_OK != ulRet)
         {
             PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n [ppp]PPP_NegoMsgProc error: %lu!",ulRet);
             continue;
         }

         if (++ulFlowControl >= g_ulPPPNegoFlowctrl)
         {
             (VOID)VOS_Ev_Write(g_ulPPPTaskId, PPP_NEGO_EVENTBIT);
             break;
         }
     }
     return;
}
#endif

#if 0

VOID PPP_L2TPTaskProc()
{
    VOS_UINT32 ulFlowControl = 0; /* 定义并初始化流控变量  */
    VOS_VOID *pMsg = VOS_NULL_PTR;
    VOS_UINT32 ulMsgCode = 0;

    PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n [ppp]PPP_L2TPTaskProc: enter!");

    while (VOS_OK == VOS_MCReadQue(g_pstL2TPPppNotifyQueID,
                                   &pMsg,
                                   &ulMsgCode,
                                   VOS_MCQUEUE_NO_WAIT,
                                   0))
    {

        if (VOS_NULL_PTR == pMsg)
        {
            VOS_DBGASSERT(0);
            continue;
        }

        PPP_DBG_OK_CNT(PPP_PHOK_1375);
        /* PPP_L2tpMsgProc(pMsg, RTD_GET_MSGCODE(pMsg)); */

        PGP_RTDistributeFreeMsg(pMsg);

        if (++ulFlowControl >= 25)
        {
            (VOID)VOS_Ev_Write(g_ulPPPTaskId, PPP_L2TP_NOTIFY_PPP_EVENTBIT);
            break;
        }
    }
    return;
}
#endif
#if 0

VOID PPP_LAPTaskProc()
{
      VOS_UINT32 ulFlowControl = 0; /* 定义并初始化流控变量  */
      VOID *pMsg = VOS_NULL_PTR;
      VOS_UINT32 ulMsgCode = 0;

      while (VOS_OK == VOS_MCReadQue(g_pstPppLAPNotifyQueID,
                                   &pMsg,
                                   &ulMsgCode,
                                   VOS_MCQUEUE_NO_WAIT,
                                   0))
      {
          if (VOS_NULL_PTR == pMsg)
          {
              VOS_DBGASSERT(0);
              continue;
          }

          PPP_DBG_OK_CNT(PPP_PHOK_1376);

          /* (VOID)PDN_LapMsgProc((USM_LAP2_MSG_S *)pMsg); */

          PGP_RTDistributeFreeMsg(pMsg);

          if (++ulFlowControl >= g_ulPPPLapFlowctrl)
          {
              (VOID)VOS_Ev_Write(g_ulPPPTaskId, PPP_LAP_NOTIFY_PPP_EVENTBIT);
              break;
          }
      }

    return;
}
#endif

VOS_VOID PPP_SubBoardInit(VOS_VOID)
{

    return;
}

#if 0

VOS_VOID  PPP_ReNegoCompressTask(UCHAR *pucMsg)
{
    VOS_UINT32 ulFlowCtr1 = 0;
    VOS_UINT32 ulFlowCtr2 = 0;
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;
    PPPIPCPINFO_S* pstIpcpInfo = VOS_NULL_PTR;
    PPP_CCP_INFO_S* pstCcpInfo = VOS_NULL_PTR;
    PPPRENOGOINFO* pstPppRenegoInfo = VOS_NULL_PTR;
    PPP_INNER_MSG_S *pstPppInnerMsg = VOS_NULL_PTR;
    VOS_UINT32 ulMemSize = 0;
    VOS_UINT32 ulRenegoIndex = 0;

    pstPppInnerMsg = (PPP_INNER_MSG_S *)pucMsg;
    ulRenegoIndex = pstPppInnerMsg->ulCurRenegoIndex ;

    for(; ulRenegoIndex <= PPP_MAX_USER_NUM; ulRenegoIndex++ )
    {
        /* 进行流控 */
        ulFlowCtr1++;
        if ((1000 <= ulFlowCtr1) || (3 <= ulFlowCtr2))
        {
            ulFlowCtr1 = 0;
            ulFlowCtr2 = 0;
            PPP_DBG_OK_CNT(PPP_PHOK_1377);
            PPP_SendInnerMsg(ulRenegoIndex);
            break;
        }

        pstPppInfo = &g_astPppPool[ulRenegoIndex];
        if(PPP_CB_STATE_USED != pstPppInfo->usState)
        {
            continue;
        }

        /* 如果是压缩用户，且压缩子卡状态不在位，则进行重协商 */
        if (((MAX_DMPU_NUM > pstPppInfo->ucDmpuId)
                && (PPP_CPU_ONLINE != g_ulPppSubBordStat[pstPppInfo->ucDmpuId]))
            &&((VOS_NULL_PTR != pstPppInfo->pstCcpInfo)
                || ((VOS_NULL_PTR != pstPppInfo->pstIpcpInfo)
                &&(((PPPIPCPINFO_S*)pstPppInfo->pstIpcpInfo)->stGotOptions.neg_vj))))
        {
                pstIpcpInfo = (PPPIPCPINFO_S*)pstPppInfo->pstIpcpInfo;
                pstCcpInfo = (PPP_CCP_INFO_S*)pstPppInfo->pstCcpInfo;
                PPP_DBG_OK_CNT(PPP_PHOK_1378);

                /*lint -e746*/
                if ((VOS_NULL_PTR != pstPppInfo->pstIpcpInfo)
                    &&(((PPPIPCPINFO_S*)pstPppInfo->pstIpcpInfo)->stGotOptions.neg_vj)
                    && (VOS_OK != PPP_CheckVjLimit()))
                /*lint +e746*/
                {
                     PPP_ERROR_COUNTER(PPP_ERROR_COUNTER024);
                     PPP_SET_REL_CODE(pstPppInfo, AM_RELCODE_PPP_CMPRESS_RENEGO_FAIL);
                     PPP_LCP_NegotiationDown(pstPppInfo->pstLcpInfo);

                     PPP_DBG_ERR_CNT(PPP_PHERR_668);
                     ulFlowCtr2++;
                     continue;
                }

                //(VOID)PPP_NodeDelete(ulRenegoIndex);
                (VOID)PPP_NodeAdd(ulRenegoIndex, 0, PPP_NEGO_LIST_NODE_LCP_START);

                pstPppInfo->bReNego = 1;
                if (VOS_NULL_PTR == pstPppInfo->pstPppRenegoInfo)
                {

                    ulMemSize = sizeof(PPPRENOGOINFO);
                    pstPppInfo->pstPppRenegoInfo = (PPPRENOGOINFO *)PPP_Malloc(ulMemSize);

                }

                if (VOS_NULL_PTR == pstPppInfo->pstPppRenegoInfo)
                {
                     PPP_DBG_OK_CNT(PPP_PHOK_1379);
                     continue;
                }

                pstPppRenegoInfo = pstPppInfo->pstPppRenegoInfo;
                PPP_MemSet((VOID*)pstPppRenegoInfo, 0, sizeof(PPPRENOGOINFO));
                if (VOS_NULL_PTR != pstIpcpInfo )
                {
                    pstPppRenegoInfo->ucIpcpFlag = 1;
                    (VOID)VOS_MemCpy((VOID*)&(pstPppRenegoInfo->stIpcpOptions),
                                (VOID*)&(pstIpcpInfo->stGotOptions),
                                sizeof(PPP_IPCP_OPTION_S));
                }

                if ((VOS_NULL_PTR != pstCcpInfo) && (PPP_STATE_OPENED == pstCcpInfo->stFsm.ucState))
                {
                    pstPppRenegoInfo->ucCcpFlag = 1;
                    (VOID)VOS_MemCpy((VOID*)&(pstPppRenegoInfo->stCcpOptions),
                                (VOID*)&(pstCcpInfo->stGotOptions),
                                sizeof(PPP_CCP_options_S));
                }

                PPP_INNER_COUNTER(PPP_INNER_COUTNER_019);
                PPP_Core_ReceiveEventFromShell(pstPppInfo, PPPISLRENEGO, VOS_NULL_PTR);

                /* 将子卡及DPEID设为无效，后续重协商时会重选 */
                pstPppInfo->ucDmpuId = 0xFF;
                pstPppInfo->ucDpeId = 0xFF;

                ulFlowCtr2++;
        }
    }

    g_ulReNegoTaskId = 0;
    return;
}
#endif


VOS_VOID PPP_SubBoardDown(VOS_VOID)
{
    if (CRM_BOARD_TYPE_SPUD != g_enPppBoardType)
    {
        return;
    }

    /* 及时刷新压缩资源信息 */
    /*lint -e746*/
    PPP_CompRescSyn();
    /*lint +e746*/

    if (0 != g_ulReNegoTaskId)
    {
        PPPC_INFO_LOG1("[ppp]PPP_SubBoardDown: task is already running, g_ulReNegoTaskId = [%d]", g_ulReNegoTaskId);
        return;
    }

    PPP_SendInnerMsg(1);

    return;
}


/*lint -restore */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
