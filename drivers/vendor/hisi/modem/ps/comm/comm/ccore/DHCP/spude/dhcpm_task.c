/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : dhcpm_task.c
  版 本 号   : 初稿
  作    者   : y00138047
  生成日期   : 2012年6月21日
  最近修改   :
  功能描述   : dhcpm DE板任务框架文件
  函数列表   :
*
*       1.                DHCPM_CreateQueue
*       2.                DHCPM_TaskEntry
*       3.                DHCPM_TaskInit
*       4.                DHCPM_TimerMsgProc
*

  修改历史   :
  1.日    期   : 2012年6月21日
    作    者   : y00138047
    修改内容   : 创建文件

******************************************************************************/

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

/*****************************************************************************
 函 数 名  : DHCPM_CreateQueue
 功能描述  : DHCPM在DE板上创建本地队列和共享队列
 输入参数  : 无
 输出参数  : 无
 返 回 值  : ULONG
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年5月15日
    作    者   : y00138047
    修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : DHCPM_TaskInit
 功能描述  : dhcpm任务初始化
 输入参数  : 无
 输出参数  : 无
 返 回 值  : ULONG
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月20日
    作    者   : y00138047
    修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : DHCPM_TimerMsgProc
 功能描述  : dhcpm处理定时器超时消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月20日
    作    者   : y00138047
    修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : DHCPM_TaskEntry
 功能描述  : dhcpm主任务入口函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月20日
    作    者   : y00138047
    修改内容   : 新生成函数

*****************************************************************************/
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
