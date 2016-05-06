
#include "dhcp_inc.h"
#include "dhcpc_def.h"
#include "dhcpc.h"
#include "dhcpc_cdb.h"
#include "dhcpc_func.h"
#include "dhcpc_table.h"
#include "dhcpc_var.h"
#include "dhcpc_comp.h"
#include "dhcpc_dbg.h"
#if 0
#include "dhcpm_interface.h"
#endif

extern ULONG ulDhcpcTaskStep;

/*m00221573 全文件pclint 2012-10-19 start*/
extern VOS_UINT32 LAP2_McQue_IsEmpty( VOS_VOID *pvMCQueId );
/*m00221573 全文件pclint 2012-10-19 end*/

#define __INIT__

/*****************************************************************************
 函 数 名  : DHCPC_CreateQueue
 功能描述  : dhcpc在DE板上创建本地队列和共享队列
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
ULONG DHCPC_CreateQueue()
{
    ULONG ulResult = VOS_OK;
    PTM_QUEUE_INFO_S stQueInfo = { 0 };

    stQueInfo.ullSelfCsi    = DHCPC_SELF_CSI;
    stQueInfo.ulTaskId      = g_ulDhcpcTaskId;

    /* 定时器队列 */
    stQueInfo.ulQueType     = MSG_QUETYPE_VOSQ;
    stQueInfo.ulMsgType     = DHCPC_MSG_TYPE_TIMER;
    stQueInfo.ulQueLen      = 1024;
    stQueInfo.ulEvent       = VOS_TIMER_EVENT;
    VOS_sprintf(stQueInfo.szQueName, "DTMR");

    ulResult = PTM_CreateQueue(&stQueInfo, &g_ulDhcpcTimerQid);
    if (VOS_OK != ulResult)
    {
        DHCPC_DebugPrint(PTM_LOG_ERR, "PTM_CreateQueue %s fail, return = %x",
                            stQueInfo.szQueName, ulResult);
        return VOS_ERR;
    }

    /* 创建内部队列 */
    stQueInfo.ulQueType     = MSG_QUETYPE_VOSQ;
    stQueInfo.ulMsgType     = DHCPC_MSG_TYPE_SELF;
    stQueInfo.ulQueLen      = 256;
    stQueInfo.ulEvent       = DHCPC_INNER_EVENT;
    VOS_sprintf(stQueInfo.szQueName, "DHCI");

    ulResult = PTM_CreateQueue(&stQueInfo, &g_ulDhcpcInnerQid);
    if (VOS_OK != ulResult)
    {
        DHCPC_DebugPrint(PTM_LOG_ERR, "PTM_CreateQueue %s fail, return = %x",
                            stQueInfo.szQueName, ulResult);
        return VOS_ERR;
    }

    /*接收LAP的请求消息*/
    stQueInfo.ulQueType     = MSG_QUETYPE_MCQ;
    stQueInfo.ulMsgType     = DHCPC_MSG_TYPE_LAP;
    stQueInfo.ulQueLen      = 1024;
    stQueInfo.ulEvent       = DHCPC_LAP_MSG_EV;
    VOS_sprintf(stQueInfo.szQueName, "SC%02u_DHCPC_QUE", DHCPC_SELF_CMPIDX);

    ulResult = PTM_CreateQueue(&stQueInfo, (ULONG *)&g_pulDHCP_LAP2_REQQueID);
    if (VOS_OK != ulResult)
    {
        DHCPC_DebugPrint(PTM_LOG_ERR, "PTM_CreateQueue %s fail, return = %x",
                            stQueInfo.szQueName, ulResult);

        return VOS_ERR;
    }

    /*挂接给lap发送消息的队列*/
    ulResult = DHCPC_AttachLapQueue();
    if (VOS_OK != ulResult)
    {
        DHCPC_DebugPrint(PTM_LOG_ERR, "PTM_CreateQueue call DHCPC_AttachLapQueue, return = %x",
                            ulResult);
        return VOS_ERR;
    }

    /*接收SD发过来的Server响应消息*/
    stQueInfo.ulQueType     = MSG_QUETYPE_MCQ;
    stQueInfo.ulMsgType     = DHCPC_MSG_TYPE_SERVER;
    stQueInfo.ulQueLen      = 512;
    stQueInfo.ulEvent       = DHCPC_V4_SVR_EV;
    VOS_sprintf(stQueInfo.szQueName, "DHCPSC%02u", DHCPC_SELF_CMPIDX );

    ulResult = PTM_CreateQueue(&stQueInfo, (ULONG *)&g_pulSDDhcpMCQueID);
    if (VOS_OK != ulResult)
    {
        DHCPC_DebugPrint(PTM_LOG_ERR, "PTM_CreateQueue %s fail, return = %x",
                            stQueInfo.szQueName, ulResult);

        return VOS_ERR;
    }

    stQueInfo.ulQueType     = MSG_QUETYPE_MCQ;
    stQueInfo.ulMsgType     = DHCPC_MSG_TYPE_DHCPV6_SERVER;
    stQueInfo.ulQueLen      = 1024;
    stQueInfo.ulEvent       = DHCPC_V6_SVR_EV;
    VOS_sprintf(stQueInfo.szQueName, "DHCPV6SC%02u", DHCPC_SELF_CMPIDX );

    ulResult = PTM_CreateQueue(&stQueInfo, (ULONG *)&g_pulSDDhcpv6cMcQueId);
    if (VOS_OK != ulResult)
    {
        DHCPC_DebugPrint(PTM_LOG_ERR, "PTM_CreateQueue %s fail, return = %x",
                            stQueInfo.szQueName, ulResult);

        return VOS_ERR;
    }

#if 0
    /*注册FCM通道*/
    ulResult = FCM_CreateFwdChannel(E_COMP_TYPE_DHCPC,
                                    DHCPC_MSG_TYPE_FCM,
                                    DHCPC_SELF_CMPIDX);
#endif
    if (VOS_OK != ulResult)
    {
        DHCPC_DebugPrint(PTM_LOG_ERR, "FCM_CreateFwdChannel fail, return = %x", ulResult);

        return VOS_ERR;
    }

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : DHCPC_AttachLapQueue
 功能描述  : 创建dhcp给lap发送消息的队列
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月1日
    作    者   : j00142544
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 DHCPC_AttachLapQueue()
{
    MC_QUE_ID pstQueId = NULL;
    PTM_QUEUE_INFO_S stQueInfo = { 0 };
    ULONG ulRet = 0;

    stQueInfo.ulQueType = MSG_QUETYPE_MCQ;
    stQueInfo.ulMsgType = E_AM_USM_QUE_SC_LAP_MSG;
    stQueInfo.ulQueLen = 1024;
    stQueInfo.ulEvent = M_AM_USM_EV_LAP2_MSG;

    VOS_StrNCpy(stQueInfo.szQueName, "LAP2_DHCPC_QUE", M_PTM_QUE_NAME_LEN);
    ulRet = PTM_CreateMcQueue(&stQueInfo, (ULONG *)&pstQueId);

    return ulRet;
}



/*****************************************************************************
 函 数 名  : DHCPC_TaskInit
 功能描述  : DHCPC任务初始化函数
 输入参数  : VOID
 输出参数  : 无
 返 回 值  : ULONG
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年5月15日
    作    者   : y00138047
    修改内容   : 新生成函数

*****************************************************************************/
ULONG DHCPC_TaskInit(VOID)
{
    ULONG ulReturn = 0;

    ulDhcpcTaskStep = 100;

    /* 初始化组件参数 */
    g_stDhcpcComInfo.ullSelfCsi   = PSM_Inf_GetSelfCSI(E_COMP_TYPE_DHCPC);
    g_stDhcpcComInfo.ullSelfSgId = PSM_Inf_GetSelfSGID();
    g_stDhcpcComInfo.ulSelfCmpIdx = PSM_Inf_GetCmpIndexInOSByCSI(g_stDhcpcComInfo.ullSelfCsi);
    g_stDhcpcComInfo.ulSelfCmpIdxInSG = PSM_Inf_GetCmpSameTIndexInSGByCSI(g_stDhcpcComInfo.ullSelfCsi);
    g_stDhcpcComInfo.ulHandle     = MID_DHCPC;

    /* 第一阶段初始化 */
    ulReturn = DHCPC_CommInit1();
    if (VOS_OK != ulReturn)
    {
        return VOS_ERR;
    }

    ulDhcpcTaskStep = 1000;

    return VOS_OK;
}

#define __TASK__

/*****************************************************************************
 函 数 名  : DHCPC_TimerMsgQuePro
 功能描述  :dhcpc模块处理定时器消息。
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :
 修改历史       :
  1.日      期   : 2011年01月05日
    作      者   : jiahuidong00142544
    修改内容   : 新生成函数
*****************************************************************************/
VOID DHCPC_TimerMsgQuePro()
{
    ULONG ulFlowControl = 0;            /* 定义并初始化流控变量   */
    ULONG ulMsgBuf[4] = {0};              /* 定义消息缓存区         */

    while ( VOS_OK ==( VOS_Que_Read( g_ulDhcpcTimerQid,
                                     ulMsgBuf,VOS_NO_WAIT,0 ) ) )
    {
        /*定时器超时处理*/
        if ( ulMsgBuf[2] == NULL )
        {
            continue;
        }
        /*lint -e{746}*/
        ( ( VOID( * )() )( ulMsgBuf[2] ) )( ( VOID * )( ulMsgBuf[3] ) );

        /* 流控*/
        ulFlowControl++;
        if ( DHCPC_MAXMSGS_PEREVENT < ulFlowControl )
        {
            ( VOID )VOS_Ev_Write( g_ulDhcpcTaskId, VOS_TIMER_EVENT );
            break;
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : DHCPC_InnerMsgQuePro
 功能描述  : dhcpc内部消息处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年5月17日
    作    者   : y00138047
    修改内容   : 新生成函数

*****************************************************************************/
VOID DHCPC_InnerMsgQuePro()
{
    ULONG ulFlowControl = 0;            /* 定义并初始化流控变量   */
    ULONG aulMsgBuf[4] = {0};              /* 定义消息缓存区         */
    UCHAR *pucMsg = NULL;

    while ( VOS_OK == ( VOS_Que_Read( g_ulDhcpcInnerQid,
                                     aulMsgBuf,VOS_NO_WAIT,0 ) ) )
    {
        pucMsg = (UCHAR *)aulMsgBuf[1];
        if ( NULL == pucMsg )
        {
            continue;
        }

        DHCPC_SelfMsgProc(pucMsg);

        DHCP_RTDistributeFreeMsg(pucMsg);

        /* 流控*/
        ulFlowControl++;
        if ( 2 < ulFlowControl )
        {
            ( VOID )VOS_Ev_Write( g_ulDhcpcTaskId, DHCPC_INNER_EVENT);
            break;
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : DHCPC_LAPMsgQuePro
 功能描述  :dhcpc模块处理lap消息的函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :
 修改历史       :
  1.日      期   : 2011年01月05日
    作      者   : jiahuidong00142544
    修改内容   : 新生成函数
*****************************************************************************/
VOID DHCPC_LAPMsgQuePro()
{
    ULONG ulFlowControl = 0;
    UCHAR *pucMsg = NULL;
    ULONG ulMsgCode = 0;

    if (VOS_OK != LAP2_McQue_IsEmpty(g_pulDHCP_LAP2_REQQueID))
    {
        return;
    }

    while ( VOS_OK == ( VOS_MCReadQue( g_pulDHCP_LAP2_REQQueID,
                                       &pucMsg, &ulMsgCode, VOS_MCQUEUE_NO_WAIT, 0 ) ) )
    {
        /*注意释放消息体*/
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_000);

        if ( NULL == pucMsg )
        {
            VOS_DBGASSERT( 0 );
            continue;
        }

        ( VOID )DHCPC_ReceiveLAP2Msg (pucMsg);

        DHCP_RTDistributeFreeMsg(pucMsg);

        /* 流控*/
        ulFlowControl++;
        if ( DHCPC_MAXMSGS_PEREVENT < ulFlowControl )
        {
            (VOID)VOS_Ev_Write( g_ulDhcpcTaskId, DHCPC_LAP_MSG_EV);
            break;
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : DHCPC_SDMsgQuePro
 功能描述  :dhcpc模块处理dhcp server返回的消息。
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :
 修改历史       :
  1.日      期   : 2011年01月05日
    作      者   : jiahuidong00142544
    修改内容   : 新生成函数
*****************************************************************************/
VOID DHCPC_SDMsgQuePro()
{
    ULONG ulFlowControl = 0;
    ULONG ulMsfCode = 0;
    UCHAR *pucMsg = NULL;

    if (VOS_OK != LAP2_McQue_IsEmpty(g_pulSDDhcpMCQueID))
    {
        return;
    }

    /* 此处读取与SD之间的共享队列 */
    while (VOS_OK == (VOS_MCReadQue (g_pulSDDhcpMCQueID, &pucMsg, &ulMsfCode, VOS_MCQUEUE_NO_WAIT,0)))
    {
        /* 从SD收到DHCP报文 */
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_002);
        if (NULL == pucMsg)
        {
            VOS_DBGASSERT(0);
            continue;
        }

        DHCPC_ReceiveServerMsg(pucMsg);

        DHCP_RTDistributeFreeMsg(pucMsg);

        /* 流控*/
        ulFlowControl++;
        if (DHCPC_MAXMSGS_PEREVENT < ulFlowControl)
        {
            (VOID)VOS_Ev_Write( g_ulDhcpcTaskId, DHCPC_V4_SVR_EV);
            break;
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : DHCPC_SDDhcpv6MsgQueProc
 功能描述  : 处理SD分发的dhcpv6信令消息
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年7月11日
    作    者   : jixiaoming 00180244
    修改内容   : 新生成函数

*****************************************************************************/
VOID DHCPC_SDDhcpv6MsgQueProc()
{
    UCHAR *pucMsg = NULL;
    ULONG ulMsfCode = 0;
    ULONG ulCounter = 0;

    if (VOS_OK != LAP2_McQue_IsEmpty(g_pulSDDhcpv6cMcQueId))
    {
        return;
    }

    while (VOS_OK == (VOS_MCReadQue (g_pulSDDhcpv6cMcQueId, &pucMsg, &ulMsfCode, VOS_MCQUEUE_NO_WAIT,0)))
    {
        if (NULL == pucMsg)
        {
            VOS_Assert(0);
            continue;
        }

        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPC_SDDhcpv6MsgQueProc get dhcpv6 msg!");

        DHCPV6C_ProcSDMsg(pucMsg);

        DHCP_RTDistributeFreeMsg(pucMsg);

        ulCounter++;
        if (ulCounter > DHCPC_MAXMSGS_PEREVENT)
        {
            (VOID)VOS_Ev_Write( g_ulDhcpcTaskId, DHCPC_V6_SVR_EV);
            break;
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : DHCPC_ProFcmMsg
 功能描述  :dhcpc模块处理fcm通道消息的函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :
 修改历史       :
  1.日      期   : 2011年01月05日
    作      者   : jiahuidong00142544
    修改内容   : 新生成函数
*****************************************************************************/
VOID DHCPC_ProFcmMsg()
{
    PMBUF_S * pMBuf = NULL;
    ULONG  ulTemp = 0;

    while (VOS_OK == FCM_ReadMCQue(E_COMP_TYPE_DHCPC, DHCPC_MSG_TYPE_FCM, DHCPC_SELF_CMPIDX, &pMBuf))
    {
        /*获取报文长度和地址*/
        if (NULL == pMBuf)
        {
            return;
        }

        DHCPC_ReceiveLap2MbufMsg(pMBuf);

        (VOID)PMBUF_Destroy(pMBuf);

        /* 每次处理256个消息 */
        ulTemp++;
        if (ulTemp >= DHCPC_MAXMSGS_PEREVENT)
        {
            break;
        }
    }
    return;
}

/*****************************************************************************
 函 数 名  : DHCPC_TaskEntry
 功能描述  : dhcpc主任务入口函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年5月17日
    作    者   : y00138047
    修改内容   : 新生成函数

*****************************************************************************/
VOID DHCPC_TaskEntry()
{
    ULONG ulRet = 0;
    ULONG ulEvent = 0;

    ulDhcpcTaskStep = 2000;

    /* 创建队列 */
    ulRet = DHCPC_CreateQueue();
    if (VOS_OK != ulRet)
    {
        return;
    }

    ulDhcpcTaskStep = 2100;

    /*等待PGP ready*/
    PGP_Ready();

    ulDhcpcTaskStep = 2200;

    ulRet = DHCPC_CommInit3();
    if (VOS_OK != ulRet)
    {
        return;
    }

    ulDhcpcTaskStep = 2400;

    ulRet = DHCPC_StartWorkProc();
    if (VOS_OK != ulRet)
    {
        return;
    }

    ulDhcpcTaskStep = 2600;

    (VOID)PGP_SetTaskRunConfirm();

    ulDhcpcTaskStep = 2800;

    for (;;)
    {
        if (CRM_BOARD_TYPE_SPUE == g_ulDhcpcSpuType)
        {
            /*读取数据通道的消息*/
            DHCPC_ProFcmMsg();
        }

        if (VOS_OK == VOS_Ev_Read(DHCPC_INNER_EVENT
                                | VOS_TIMER_EVENT
                                | DHCPC_LAP_MSG_EV
                                | DHCPC_V4_SVR_EV
                                | DHCPC_V6_SVR_EV,
                                 &ulEvent, (VOS_EV_ANY | VOS_WAIT), 50))
        {
            if (ulEvent & DHCPC_LAP_MSG_EV)
            {
                /*LAP上送的消息处理*/
                DHCPC_LAPMsgQuePro();
            }

            if (ulEvent & DHCPC_V4_SVR_EV)
            {
                /*DHCPV4 Server返回的消息处理*/
                DHCPC_SDMsgQuePro();
            }

            if (ulEvent & DHCPC_V6_SVR_EV)
            {
               /*DHCPV6 Server返回的消息处理*/
               DHCPC_SDDhcpv6MsgQueProc();
            }

            if (ulEvent & VOS_TIMER_EVENT)
            {
                /*定时器消息处理*/
                DHCPC_TimerMsgQuePro();
            }

            if (ulEvent & DHCPC_INNER_EVENT)
            {
                /*定时器消息处理*/
                DHCPC_InnerMsgQuePro();
            }
        }

        /*真正释放CPU*/
        VOS_T_Delay(10);

        ulDhcpcTaskStep = 8888;
    }

    //return;
}


