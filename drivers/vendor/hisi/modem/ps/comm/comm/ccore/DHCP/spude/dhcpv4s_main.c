
#include "dhcp_inc.h"
#include "dhcpc_def.h"
#include "dhcpv4s_def.h"
#include "dhcpv4s_type.h"
#include "dhcpv4s_var.h"
#include "dhcpv4s_fun.h"
#include "dhcpv4s_dbgcmd.h"
#include "dhcpv4s_comp.h"

extern VOID DHCPS_ProcPfMsg(PMBUF_S *pstMsgBuf);

#define __INIT__



ULONG DHCPS_CreateQueue()
{
    ULONG ulResult = VOS_OK;
    PTM_QUEUE_INFO_S stQueInfo = { 0 };

    stQueInfo.ullSelfCsi    = DHCPS_SELF_CSI;
    stQueInfo.ulTaskId      = g_ulDhcpServerTaskId;

    /* 接受USM消息队列 */
    stQueInfo.ulQueType     = MSG_QUETYPE_VOSQ;
    stQueInfo.ulMsgType     = DHCPS_MSG_TYPE_USM;
    stQueInfo.ulQueLen      = DHCPS_QUEUE_LENGTH;
    stQueInfo.ulEvent       = DHCPS_USM_EV;
    VOS_sprintf(stQueInfo.szQueName, "DHCPS_USM");

    ulResult = PTM_CreateQueue(&stQueInfo, &g_ulDHCPSUSMQueId);
    if (VOS_OK != ulResult)
    {
        return VOS_ERR;
    }

    /* 定时器队列 */
    stQueInfo.ulQueType     = MSG_QUETYPE_VOSQ;
    stQueInfo.ulMsgType     = DHCPS_MSG_TYPE_TIMER;
    stQueInfo.ulQueLen      = 1024;
    stQueInfo.ulEvent       = VOS_TIMER_EVENT;
    VOS_sprintf(stQueInfo.szQueName, "DST");

    ulResult = PTM_CreateQueue(&stQueInfo, &g_ulDhcpsTimerQueId);
    if (VOS_OK != ulResult)
    {
        return VOS_ERR;
    }

    /* 创建内部队列 */
    stQueInfo.ulQueType     = MSG_QUETYPE_VOSQ;
    stQueInfo.ulMsgType     = DHCPS_MSG_TYPE_SELF;
    stQueInfo.ulQueLen      = 256;
    stQueInfo.ulEvent       = DHCPS_INNER_EVENT;
    VOS_sprintf(stQueInfo.szQueName, "DHCI");

    ulResult = PTM_CreateQueue(&stQueInfo, &g_ulDhcpsInnerQueId);
    if (VOS_OK != ulResult)
    {
        return VOS_ERR;
    }

    /* 接收信令消息 */
    stQueInfo.ulQueType     = MSG_QUETYPE_MCQ;
    stQueInfo.ulMsgType     = DHCPS_MSG_TYPE_PF;
    stQueInfo.ulQueLen      = DHCPS_DFT_QUEUE_LENGTH;
    stQueInfo.ulEvent       = DHCPS_PF_EV;
    VOS_sprintf(stQueInfo.szQueName, "S%luDHCPv4S", DHCPS_SELF_CMPIDX);

    ulResult = PTM_CreateQueue(&stQueInfo, (ULONG *)&g_pDHCPSRcvDhcpMsgQueId);
    if (VOS_OK != ulResult)
    {
        return VOS_ERR;
    }

    return VOS_OK;
}


ULONG DHCPS_Init()
{
    ULONG ulReturn = 0;

    /* 初始化组件参数 */
    g_stDhcpv4sComInfo.ullSelfCsi   = PSM_Inf_GetSelfCSI(E_COMP_TYPE_DSV4);
    g_stDhcpv4sComInfo.ullSelfSgId = PSM_Inf_GetSelfSGID();
    g_stDhcpv4sComInfo.ulSelfCmpIdx = PSM_Inf_GetCmpIndexInOSByCSI(g_stDhcpv4sComInfo.ullSelfCsi);
    g_stDhcpv4sComInfo.ulSelfCmpIdxInSG = PSM_Inf_GetCmpSameTIndexInSGByCSI(g_stDhcpv4sComInfo.ullSelfCsi);
    g_stDhcpv4sComInfo.ulHandle     = MID_DHCPS;

    ulDhcpv4sTaskStep = 100;

    /* 第一阶段初始化 */
    ulReturn = DHCPS_CommInit1();
    if (VOS_OK != ulReturn)
    {
        return VOS_ERR;
    }

    ulDhcpv4sTaskStep = 200;

#ifndef __WIN32_PLATFORM__
    ulReturn = CLAP_TaskInit(g_stDhcpv4sComInfo.ullSelfCsi, g_stDhcpv4sComInfo.ulHandle);
    if (VOS_OK != ulReturn)
    {
        return ulReturn;
    }
#endif

    ulDhcpv4sTaskStep = 2000;

    return VOS_OK;
}

#define __TASK__

VOID DHCPS_RecvMsgFromUSM()
{
    ULONG aulMsgBuf[4];            /* 消息队列元素 */
    ULONG ulFlowCounter = 0;
    UCHAR *pucMsg = NULL;

    for (;;)
    {
        aulMsgBuf[1] = 0;

        if (VOS_OK == VOS_Que_Read( g_ulDHCPSUSMQueId,
                                    aulMsgBuf,
                                    VOS_NO_WAIT,
                                    0 ))
        {
            if (NULL != aulMsgBuf[1])
            {
                pucMsg = (UCHAR*)aulMsgBuf[1];
                g_ulDhcpStatisc[DHCPS_RECEIVE_USM]++;

                DHCPS_FSM_PreMsgFromUSM(pucMsg);
                DHCP_RTDistributeFreeMsg(pucMsg);
            }
        }
        else
        {
            break;
        }

        ulFlowCounter++;
        if (ulFlowCounter >= 50)
        {
            /* 还有未处理的消息,写事件位,下次继续处理 */
            (VOID)VOS_Ev_Write(g_ulDhcpServerTaskId, DHCPS_USM_EV);
            break;
        }
    }

}




VOS_VOID DHCPS_InnerMsgProc()
{
    ULONG ulFlowControl = 0;
    ULONG ulMsg[4] = {0};
    UCHAR *pucMsg = NULL;

    while (VOS_OK == VOS_Que_Read(g_ulDhcpsInnerQueId, ulMsg, VOS_NO_WAIT, 0))
    {
        pucMsg = (UCHAR*)ulMsg[1];
        if ( NULL == pucMsg )
        {
            VOS_Assert(0);
            continue;
        }

        DHCPS_ProcSelfMsg(pucMsg);

        DHCP_RTDistributeFreeMsg(pucMsg);
        ulFlowControl++;
        if (ulFlowControl >= 2)
        {
            (VOID)VOS_Ev_Write(g_ulDhcpServerTaskId, DHCPS_INNER_EVENT);
            break;
        }
    }

    return;
}



VOS_VOID  DHCPS_RecvMsgHandle(VOID)
{
    PMBUF_S * pstMsgBuf = VOS_NULL_PTR;
    ULONG   ulMsgLen = 0;
    ULONG   ulLoopi = 0;

    for(ulLoopi = 0; ulLoopi < DHCPS_FLOWCONTROL_MAX; ulLoopi++)
    {
        ulMsgLen = 0;

        /*注意: 这是共享对列的读取方式*/
        if( VOS_OK != VOS_MCReadQue(g_pDHCPSRcvDhcpMsgQueId,
                                    &pstMsgBuf,
                                    &ulMsgLen,
                                    VOS_MCQUEUE_NO_WAIT,
                                    0))
        {
            /* 读取失败直接返回 */
            return;
        }

        /* 判断消息合法性 */
        if( VOS_NULL_PTR == pstMsgBuf)
        {
            /* 记录异常信息 */
            DHCPS_DebugPrint(PTM_LOG_INFO, " DHCPS_RecvMsgHandle: Null Msg!\n");
            continue;
        }

        g_ulDhcpStatisc[DHCPS_RECEIVE_DPE]++;

        DHCPS_ProcPfMsg(pstMsgBuf);


        (VOID)PMBUF_Destroy(pstMsgBuf);
    }

    /* 队列中还有消息, 写时间位,下面继续处理 */
    (VOID)VOS_Ev_Write(g_ulDhcpServerTaskId, DHCPS_PF_EV);

    return;
}


VOID  DHCPS_TimerOut(VOID)
{
    ULONG aulMsgBuf[4];            /* 消息队列元素 */
    ULONG ulFlowCounter = 0;

    /* 循环读内部消息超时队列 */
    for (;;)
    {
        /* 初始化  */
        aulMsgBuf[2] = 0;
        aulMsgBuf[3] = 0;

        if (VOS_OK == VOS_Que_Read( g_ulDhcpsTimerQueId,
                                    aulMsgBuf,
                                    VOS_NO_WAIT,
                                    0 ))
        {
            if (NULL != aulMsgBuf[2])
            {
                /* 状态机定时器处理 */
                /*lint -e{746}*/
                ((VOID(*) ())(aulMsgBuf[2]))((VOID *)(aulMsgBuf[3]));
            }
        }
        else
        {
            break;
        }

        ulFlowCounter++;
        if (ulFlowCounter >= 50)
        {
            /* 还未处理完,写时间位,下次继续处理 */
            (VOID)VOS_Ev_Write(g_ulDhcpServerTaskId, VOS_TIMER_EVENT);
            break;
        }
    }

    return;
}


VOID DHCPS_MainEntry()
{
    ULONG ulRet = 0;
    ULONG ulEvent = 0;

    ulDhcpv4sTaskStep = 2100;

    /* 创建队列 */
    ulRet = DHCPS_CreateQueue();
    if (VOS_OK != ulRet)
    {
        return;
    }

    ulDhcpv4sTaskStep = 3000;

    /*等待PGP ready*/
    PGP_Ready();

    ulDhcpv4sTaskStep = 4000;

    ulRet = DHCPS_CommInit3();
    if (VOS_OK != ulRet)
    {
        return;
    }

    ulDhcpv4sTaskStep = 6200;

    ulRet = DHCPS_StartWorkProc();
    if (VOS_OK != ulRet)
    {
        return;
    }

    ulDhcpv4sTaskStep = 6400;

#ifndef __WIN32_PLATFORM__
    ulRet = CLAP_TaskConfirm(g_ulDhcpServerTaskId);
    if (VOS_OK != ulRet)
    {
        return;
    }
#endif

    ulDhcpv4sTaskStep = 6600;

    (VOID)PGP_SetTaskRunConfirm();

    ulDhcpv4sTaskStep = 7000;

    for(;;)
    {
        /* 从转发收消息的队列必须死读,转发目前没有写事件位 */
        DHCPS_RecvMsgHandle();

        /*读事件位*/
        if (VOS_OK == VOS_Ev_Read( VOS_TIMER_EVENT
                                 | DHCPS_INNER_EVENT
                                 | DHCPS_PF_EV
                                 | DHCPS_USM_EV,
                                 &ulEvent, VOS_EV_ANY|VOS_WAIT, 100 ) )
        {
            /*处理定时器事件*/
            if (VOS_TIMER_EVENT & ulEvent)
            {
                DHCPS_TimerOut();
            }

            /* 读事件位方式修改为WAIT,防止处理能力不足,此处继续处理 */
            if (DHCPS_PF_EV & ulEvent)
            {
                /* 从转发读队列 */
                DHCPS_RecvMsgHandle();
            }

            /*处理USM发送的消息*/
            if (DHCPS_USM_EV & ulEvent)
            {
                DHCPS_RecvMsgFromUSM();
            }

            /* 处理内部消息 */
            if (DHCPS_INNER_EVENT & ulEvent)
            {
                DHCPS_InnerMsgProc();
            }
        }

#ifndef __WIN32_PLATFORM__
        CLAP_TaskProcess();
#endif

        VOS_T_Delay(1);
        ulDhcpv4sTaskStep = 8888;
    }
}


