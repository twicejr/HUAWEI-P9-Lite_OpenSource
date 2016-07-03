

#include "dhcp_inc.h"
#include "dhcpc_def.h"
#include "dhcpc.h"
#include "dhcpc_cdb.h"
#include "dhcpc_dbg.h"
#include "dhcpm_interface.h"
#include "dhcpm_comp.h"
#include "dhcpm_task.h"
#include "dhcpm_dbg.h"



ULONG g_ulDhcpMTaskId = 0;

ULONG g_ulDhcpMTimerMsgQueID = 0;

VOID    *g_pulDhcpmDbgCmdMcRecvQueId      = 0;


ULONG DHCPM_CreateQueue()
{
    ULONG ulResult = VOS_OK;
    PTM_QUEUE_INFO_S stQueInfo = { 0 };

    stQueInfo.ullSelfCsi    = DHCPM_SELF_CSI;
    stQueInfo.ulTaskId      = g_ulDhcpMTaskId;

    /* 定时器队列 */
    stQueInfo.ulQueType     = MSG_QUETYPE_VOSQ;
    stQueInfo.ulMsgType     = DHCPM_MSG_TYPE_TIMER;
    stQueInfo.ulQueLen      = DHCPM_TIMER_QUE_LEN;
    stQueInfo.ulEvent       = VOS_TIMER_EVENT;
    VOS_sprintf(stQueInfo.szQueName, "DHMT");

    ulResult = PTM_CreateQueue(&stQueInfo, &g_ulDhcpMTimerMsgQueID);
    if (VOS_OK != ulResult)
    {
        DHCPM_DebugPrint(PTM_LOG_ERR, "PTM_CreateQueue %s fail, return = %x",
                        stQueInfo.szQueName, ulResult);
        return VOS_ERR;
    }

    return VOS_OK;
}


ULONG DHCPM_TaskInit()
{
    ULONG ulReturn = 0;

    /* 初始化组件参数 */
    g_stDhcpMCompInfo.ullSelfCsi   = PSM_Inf_GetSelfCSI(E_COMP_TYPE_DHCPCGM);
    g_stDhcpMCompInfo.ulSelfCmpIdx = PSM_Inf_GetCmpIndexInOSByCSI(g_stDhcpMCompInfo.ullSelfCsi);
    g_stDhcpMCompInfo.ulHandle     = MID_DHCPM;

    /* 第一阶段初始化 */
    ulReturn = DHCPM_CommInit1();
    if (VOS_OK != ulReturn)
    {
        return VOS_ERR;
    }

    return VOS_OK;
}


VOS_VOID DHCPM_TimerMsgProc()
{
    ULONG ulFlowControl = 0;
    ULONG ulMsg[4] = {0};

    while (VOS_OK == VOS_Que_Read(g_ulDhcpMTimerMsgQueID, ulMsg, VOS_NO_WAIT, 0))
    {
        if (ulMsg[2] != NULL)
        {
            /*lint -e{746}*/
            ( ( VOID( * )() )( ulMsg[2] ) )( ( VOID * )( ulMsg[3] ) , ( VOID * )( ulMsg[0] ));
        }

        ulFlowControl++;
        if (ulFlowControl >= 20)
        {
            (VOID)VOS_Ev_Write(g_ulDhcpMTaskId, VOS_TIMER_EVENT);
            break;
        }
    }

    return;
}

VOID DHCPM_ProcessBatchCmdRspMsg()
{
    ULONG ulTemp = 0;
    ULONG ulMsgCode = 0;
    VOS_VOID *pMsg = NULL;

    if (NULL == g_pulDhcpmDbgCmdMcRecvQueId)
    {
        return;
    }

    for (;;)
    {
        if (VOS_OK != VOS_MCReadQue(g_pulDhcpmDbgCmdMcRecvQueId, &pMsg, &ulMsgCode, VOS_QUEUE_NO_WAIT, 0))
        {
            break;
        }

        if (NULL == pMsg)
        {
            VOS_Assert(0);
            return ;
        }

        (VOID)PTM_DebugBatchSProcDebugCmdRspMsg((UCHAR *)pMsg);

        PGP_RTDistributeFreeMsg(pMsg);

        ulTemp++;
        if (ulTemp > 20)
        {
            break;
        }
    }

    return;
}


VOID DHCPM_TaskEntry()
{
    ULONG ulRet = 0;
    ULONG ulEvent = 0;

    ulRet = DHCPM_CreateQueue();
    if ( VOS_OK != ulRet )
    {
        return;
    }

    /*等待PGP ready*/
    PGP_Ready();

    ulRet = DHCPM_CommInit3();
    if ( VOS_OK != ulRet )
    {
        return;
    }

    ulRet = DHCPM_StartWorkProc();
    if ( VOS_OK != ulRet )
    {
        return;
    }

    (VOID)PGP_SetTaskRunConfirm();

    for (;;)
    {
        /* 读消息信息 */
        if (VOS_OK == VOS_Ev_Read (VOS_TIMER_EVENT, &ulEvent,
                                   (VOS_EV_ANY | VOS_NO_WAIT), 0))
        {
            /* 有定时器事件 */
            if (ulEvent & VOS_TIMER_EVENT)
            {
                DHCPM_TimerMsgProc();
            }
        }

        DHCPM_ProcessBatchCmdRspMsg();

        VOS_T_Delay(10);
    }
}
