
#include "dhcp_inc.h"
#include "dhcpc_def.h"
#include "dhcpv4s_def.h"
#include "dhcpv4s_type.h"
#include "dhcpv4s_var.h"
#include "dhcpv4s_fun.h"
#include "dhcpv4s_comp.h"
#include "dhcpv4s_dbgcmd.h"


/*****************************************************************************
 函 数 名      : DHCPS_FSM_Run
 功能描述   : DHCPS的状态机入口函数
 输入参数   : 无
 输出参数   : 无
 返 回 值      : 无
 调用函数   :
 被调函数   :

 修改历史   :
  1.日    期      : 2008年11月27日
    作    者       : dongmingzhou 42828
    修改内容: 新生成函数

*****************************************************************************/
VOID DHCPS_FSM_Run(DHCPS_PRE_RESULT_S *pstPreResult)
{
    UCHAR                    ucMsgType             = 0xff;
    UCHAR                    ucStateMachine       = 0xff;
    DHCPS_STATE_RET    stStateChangeRet;
    DHCPS_LEASE_S        *pstLease               = NULL;
    PF_DHCPS_FSM         pFuncStateMachine  = NULL;
    ULONG                    ulRet                       = VOS_OK;
    ULONG                    ulCount                    =0;
    ULONG                    ulPDPContextIndex   = 0;
    ULONG ulTimerOutLength = 0;
    DHCPS_TIMER_TYPE_E enTimerType = E_DHCPS_INVALID_TIMER;

    DHCPS_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPS_FSM_Run : Enter");

    if (NULL == pstPreResult)
    {
        DHCPS_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPS_FSM_Run : ERROR parameter is NULL");
        DHCPS_InternalBranchCounter(DHCPS_INTERNAL_BRANCH_000);
        VOS_Assert(0);
        return;
    }

    DHCPV4S_ShowCode((UCHAR*)pstPreResult, sizeof(DHCPS_PRE_RESULT_S));

    PGP_MemZero((VOID *)&stStateChangeRet, sizeof(DHCPS_STATE_RET));

    /*取出相关数据*/
    ucMsgType = pstPreResult->ucMsgType;
    ulPDPContextIndex   = pstPreResult->ulPdpIndex;
    if ( (0 == ulPDPContextIndex)
        ||(ulPDPContextIndex > SDB_MAX_CONTEXT_NUM))
    {
        DHCPS_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPS_FSM_Run : ERROR ulPDPContextIndex is %d",
                                    ulPDPContextIndex);
        /* 按顺序修改计数，下同*/
        DHCPS_InternalBranchCounter(DHCPS_INTERNAL_BRANCH_001);
        VOS_Assert(0);
        return;
    }

    /*临时的租约 = 全局变量的租约，此时应该是为NULL的*/
    pstLease = &g_pstDhcpSLease[ulPDPContextIndex];

    pstPreResult->pstLease = pstLease;

    ucStateMachine = pstLease->ucLeaseState;

    /*判断消息和状态的有效性*/
    if ((ucMsgType >= DHCPS_MSG_MAX ) || (ucStateMachine >= DHCPS_STATE_MAX))
    {
        DHCPS_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPS_FSM_Run : ERROR ! ucMsgType = %d , ucStateMachine = %d",ucMsgType,ucStateMachine);
        DHCPS_InternalBranchCounter(DHCPS_INTERNAL_BRANCH_002);
        return;
    }

    /*取出特定消息下的回调函数*/
    pFuncStateMachine = g_stDHCPSStateMachine[ucStateMachine].pFuncStateMachine[ucMsgType];
    if(NULL == pFuncStateMachine)
    {
        /*某状态收到了没有注册的消息，直接返回*/
        g_stDHCPSStateMachine[ucStateMachine].ErrMsgCount[ucMsgType]++;
        DHCPS_InternalBranchCounter(DHCPS_INTERNAL_BRANCH_003);
        return;
    }

    /*取得时长和定时器类型*/
    enTimerType = (DHCPS_TIMER_TYPE_E)g_stDHCPSStateMachine[ucStateMachine].ulTimerType;

    /*只要消息类型和回调函数不为空，继续执行*/
    /*lint -e716*/
    while (1)
    /*lint +e716*/
    {
        /*如果超过最大可循环次数，
        可能是发生了异常，直接跳出，避免死循环*/
        ulCount ++;
        if(ulCount > DHCPS_FSM_MAX_STEP)
        {
            DHCPS_DebugPrint(PTM_LOG_INFO, " DHCPS_FSM_Run : Finite State Machine Run times = %u",ulCount);
            DHCPS_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPS_FSM_Run : Finite State Machine Run times = %u",ulCount);
            /* z00175135 DTS2012031905269 删除无用断言 2012-03-19 start */
            //VOS_Assert(0);
            /* z00175135 DTS2012031905269 删除无用断言 2012-03-19 end   */
            DHCPS_InternalBranchCounter(DHCPS_INTERNAL_BRANCH_004);
            return;
        }

        /*停止状态机定时器*/
        if (1 == g_pstStateTimer[ulPDPContextIndex].ucState)
        {
            if (VOS_OK != DHCPS_TIMER_StopTimer(pstLease, enTimerType))
            {
                DHCPS_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPS_FSM_Run : DHCPS_TIMER_StopTimer g_pstStateTimer Err : "
                                             "ulPDPContextIndex= %u, enTimerType %u",
                                             ulPDPContextIndex,
                                             enTimerType);
                DHCPS_InternalBranchCounter(DHCPS_INTERNAL_BRANCH_005);
            }
        }

        /*Todo:除INFORM消息外其他消息都要删除租约定时器*/
        if ((1 == g_pstLeaseTimer[ulPDPContextIndex].ucState)
            && ( DHCPS_MSG_RECIVE_INFORM != ucMsgType))
        {
            if (VOS_OK != DHCPS_TIMER_StopTimer(pstLease, enTimerType))
            {
                DHCPS_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPS_FSM_Run : DHCPS_TIMER_StopTimer g_pstLeaseTimer Err : "
                                             "ulPDPContextIndex= %u, enTimerType %u",
                                             ulPDPContextIndex,
                                             enTimerType);
                DHCPS_InternalBranchCounter(DHCPS_INTERNAL_BRANCH_006);
            }
        }

        /*调用状态机函数*/
        ulRet = (*pFuncStateMachine)(pstPreResult, &stStateChangeRet);
        if(ulRet != VOS_OK)
        {
            DHCPS_InternalBranchCounter(DHCPS_INTERNAL_BRANCH_007);
        }

        DHCPS_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPS_FSM_Run : Change Result = %d, ulNewState = %d, ulMessageType %d",
                                    stStateChangeRet.ulResult,
                                    stStateChangeRet.ulNewState,
                                    stStateChangeRet.ulMessageType);

        switch (stStateChangeRet.ulResult)
        {
            /*状态迁移成功，迁移到新的状态*/
            case DHCPS_STATE_CHANGE_OK:
            {
                if (stStateChangeRet.ulNewState >= DHCPS_STATE_MAX)
                {
                    DHCPS_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPS_FSM_Run : Finite State Machine : ucStateMachine = %u, ulNewState = %u",
                                                    ucStateMachine,
                                                    stStateChangeRet.ulNewState);
                    DHCPS_DebugPrint(PTM_LOG_INFO, " DHCPS_FSM_Run : Finite State Machine : ucStateMachine = %u, ulNewState = %u",
                                                            ucStateMachine,
                                                            stStateChangeRet.ulNewState);
                    DHCPS_InternalBranchCounter(DHCPS_INTERNAL_BRANCH_008);
                    return;
                }

                /*统计信息*/
                g_stDHCPSStateMachine[ucStateMachine].StateChangeOKCount[ucMsgType][stStateChangeRet.ulNewState]++;

                /*切换状态*/
                pstLease->ucLeaseState = (UCHAR)stStateChangeRet.ulNewState;

                ulTimerOutLength = g_stDHCPSStateMachine[stStateChangeRet.ulNewState].ulTimerOutLength;
                enTimerType = (DHCPS_TIMER_TYPE_E)g_stDHCPSStateMachine[stStateChangeRet.ulNewState].ulTimerType;

                /*状态转换成功，如果注册了定时器，则启动定时器*/
                if ((0 != g_stDHCPSStateMachine[pstLease->ucLeaseState].ulTimerOutLength)
                    && (DHCPS_MSG_RECIVE_INFORM != ucMsgType))
                {
                    /*增加定时器类型*/
                    if (VOS_OK != DHCPS_TIMER_StartTimer(pstLease, enTimerType, ulTimerOutLength))
                    {
                        DHCPS_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPS_FSM_Run : Lease Start Timer ERR ");
                    }

                    DHCPS_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPS_FSM_Run : Lease Start Timer OK");
                }


                DHCPS_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPS_FSM_Run : Change OK From %u To  %u",
                                                ucStateMachine,
                                                stStateChangeRet.ulNewState);
                return;
            }

            /*状态机没有迁移，继续后续处理，可能后面没有处理
            也有可能继续后续的处理，根据消息新返回的内部消息码
            判断*/
            case DHCPS_STATE_NO_CHANGE:
            {
                g_stDHCPSStateMachine[ucStateMachine].MsgNOChangeCount[ucMsgType]++;
                ucMsgType = (UCHAR)stStateChangeRet.ulMessageType;
                if (ucMsgType >= DHCPS_MSG_MAX)
                {
                    DHCPS_DebugPrint(PTM_LOG_INFO, " DHCPS_FSM_Run : Finite State Machine : ucStateMachine = %u, NO_CHANGE ucMsgType = %u",
                    ucStateMachine, ucMsgType);
                    DHCPS_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPS_FSM_Run : Finite State Machine : ucStateMachine = %u, NO_CHANGE ucMsgType = %u",
                    ucStateMachine, ucMsgType);
                    DHCPS_InternalBranchCounter(DHCPS_INTERNAL_BRANCH_009);
                    return;
                }

                /*获取新的处理函数*/
                pFuncStateMachine = g_stDHCPSStateMachine[ucStateMachine].pFuncStateMachine[ucMsgType];
                if(NULL != pFuncStateMachine)
                {
                    continue;
                }

                /*某状态收到了没有注册的消息，直接返回*/
                g_stDHCPSStateMachine[ucStateMachine].ErrMsgCount[ucMsgType]++;

                return;
            }

            /*状态机迁移发生错误，记录错误，
            如果生成错误消息码，继续处理*/
            case DHCPS_STATE_CHANGE_ERR:
            {
                g_stDHCPSStateMachine[ucStateMachine].MsgChangeERRCount[ucMsgType]++;

                ucMsgType = (UCHAR)stStateChangeRet.ulMessageType;

                if (ucMsgType >= DHCPS_MSG_MAX)
                {
                    DHCPS_DebugPrint(PTM_LOG_INFO, " DHCPS_FSM_Run : Finite State Machine : ucStateMachine = %u, CHANGE_ERR ucMsgType = %u",
                    ucStateMachine, ucMsgType);
                    DHCPS_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPS_FSM_Run : Finite State Machine : ucStateMachine = %u, CHANGE_ERR ucMsgType = %u",
                    ucStateMachine, ucMsgType);
                    DHCPS_InternalBranchCounter(DHCPS_INTERNAL_BRANCH_010);
                    return;
                }

                /*获取新的处理函数，进行失败处理*/
                pFuncStateMachine = g_stDHCPSStateMachine[ucStateMachine].pFuncStateMachine[ucMsgType];
                g_stDHCPSStateMachine[ucStateMachine].MsgNOChangeCount[ucMsgType]++;
                if(NULL != pFuncStateMachine)
                {
                    continue;
                }

                /*某状态收到了没有注册的消息，直接返回*/
                g_stDHCPSStateMachine[ucStateMachine].ErrMsgCount[ucMsgType]++;
                return;
            }

            /*对于指针为空等系统错误，返回该消息码，
            直接跳出状态机函数*/
            case DHCPS_STATE_SYSTEM_ERR:
            {
                g_stDHCPSStateMachine[ucStateMachine].MsgSysERRCount[ucMsgType]++;
                DHCPS_DebugPrint(PTM_LOG_INFO, " DHCPS_FSM_Run : Finite State Machine : SYSTEM ERROR ucStateMachine = %u",
                ucStateMachine);
                DHCPS_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPS_FSM_Run : Finite State Machine : SYSTEM ERROR ucStateMachine = %u",
                ucStateMachine);
                DHCPS_InternalBranchCounter(DHCPS_INTERNAL_BRANCH_011);
                return;
            }

            /*异常的返回结果，记录错误*/
            default:
            {
                g_stDHCPSStateMachine[ucStateMachine].StateChangeUNKNOWCount[ucMsgType]++;
                DHCPS_DebugPrint(PTM_LOG_INFO, " DHCPS_FSM_Run : Finite State Machine : UNKNOW result ucStateMachine = %u",
                ucStateMachine);
                DHCPS_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPS_FSM_Run : Finite State Machine: UNKNOW result ucStateMachine = %u",
                ucStateMachine);
                DHCPS_InternalBranchCounter(DHCPS_INTERNAL_BRANCH_012);
                return;
            }
        }
    }
}

/*****************************************************************************
 函 数 名      : DHCPS_FSM_Register
 功能描述   : 注册DHCPS状态机的处理函数
 输入参数   : 无
 输出参数   : 无
 返 回 值      : 无
 调用函数   :
 被调函数   :

 修改历史   :
  1.日    期      : 2008年11月27日
    作    者       : dongmingzhou 42828
    修改内容: 新生成函数

*****************************************************************************/
VOID DHCPS_FSM_Register()
{

    /*初始化为0*/
    PGP_MemZero(g_stDHCPSStateMachine, (DHCPS_STATE_MAX + 1) * sizeof(DHCPS_STATE_MACHINE_NODE));
    PGP_MemZero(g_stDHCPSMsgNode, DHCPS_MSG_MAX*sizeof(DHCPS_STATE_MESSAGE_NODE));

    /*注册各个状态定时器的时长*/
    g_stDHCPSStateMachine[DHCPS_STATE_IDEL].ulTimerOutLength            = 0;
    g_stDHCPSStateMachine[DHCPS_STATE_REQUESTIP].ulTimerOutLength   = DHCPS_TIMER_LENGTH_WAITUSM;
    g_stDHCPSStateMachine[DHCPS_STATE_OFFERED].ulTimerOutLength      = DHCPS_TIMER_LENGTH_WAITREAUESTMSG;
    g_stDHCPSStateMachine[DHCPS_STATE_COMMITED].ulTimerOutLength   = 0XFFFFFFFF;

    /*注册各个状态定时器超时后的消息,此消息发给状态机的处理函数为超时处理!!!*/
    g_stDHCPSStateMachine[DHCPS_STATE_IDEL].ulTimerOutMsg          = 0XFFFFFFFF;
    g_stDHCPSStateMachine[DHCPS_STATE_REQUESTIP].ulTimerOutMsg = DHCPS_MSG_TIMER;
    g_stDHCPSStateMachine[DHCPS_STATE_OFFERED].ulTimerOutMsg    = DHCPS_MSG_TIMER;
    g_stDHCPSStateMachine[DHCPS_STATE_COMMITED].ulTimerOutMsg = DHCPS_MSG_TIMER;

    /*注册各个状态定时器的类型*/
    g_stDHCPSStateMachine[DHCPS_STATE_IDEL].ulTimerType            = E_DHCPS_INVALID_TIMER;
    g_stDHCPSStateMachine[DHCPS_STATE_REQUESTIP].ulTimerType   = E_DHCPS_FSM_TIMER;
    g_stDHCPSStateMachine[DHCPS_STATE_OFFERED].ulTimerType      = E_DHCPS_FSM_TIMER;
    g_stDHCPSStateMachine[DHCPS_STATE_COMMITED].ulTimerType   = E_DHCPS_LEASE_TIMER;


    /*注册为NULL表示不需要进行处理*/

    /*idel态的状态机处理函数注册*/
    g_stDHCPSStateMachine[DHCPS_STATE_IDEL].pFuncStateMachine[DHCPS_MSG_RECIVE_DISCOVER]                   = DHCPS_FSM_IDLE_ReceiveDiscover;
    g_stDHCPSStateMachine[DHCPS_STATE_IDEL].pFuncStateMachine[DHCPS_MSG_RECIVE_REQUEST]                    = DHCPS_FSM_IDEL_ReceiveRequest;
    g_stDHCPSStateMachine[DHCPS_STATE_IDEL].pFuncStateMachine[DHCPS_MSG_RECIVE_DECLINE]                     = NULL;
    g_stDHCPSStateMachine[DHCPS_STATE_IDEL].pFuncStateMachine[DHCPS_MSG_RECIVE_RELEASE]                     = DHCPS_FSM_IDLE_ReceiveRelease;
    g_stDHCPSStateMachine[DHCPS_STATE_IDEL].pFuncStateMachine[DHCPS_MSG_RECIVE_INFORM]                      = NULL;
    g_stDHCPSStateMachine[DHCPS_STATE_IDEL].pFuncStateMachine[DHCPS_MSG_USM_ADDRESS_SUCCESS]          = NULL;
    g_stDHCPSStateMachine[DHCPS_STATE_IDEL].pFuncStateMachine[DHCPS_MSG_USM_ADDRESS_FAILURE]           = NULL;
    g_stDHCPSStateMachine[DHCPS_STATE_IDEL].pFuncStateMachine[DHCPS_MSG_USM_DEACTIVE]                       = NULL;
    g_stDHCPSStateMachine[DHCPS_STATE_IDEL].pFuncStateMachine[DHCPS_MSG_TIMER]                                    = NULL;
    g_stDHCPSStateMachine[DHCPS_STATE_IDEL].pFuncStateMachine[DHCPS_MSG_RELAY_SERVER_NAK]                     = NULL;


    /*申请地址态的状态机处理函数注册*/
    g_stDHCPSStateMachine[DHCPS_STATE_REQUESTIP].pFuncStateMachine[DHCPS_MSG_RECIVE_DISCOVER]          = NULL;
    g_stDHCPSStateMachine[DHCPS_STATE_REQUESTIP].pFuncStateMachine[DHCPS_MSG_RECIVE_REQUEST]           = NULL;
    g_stDHCPSStateMachine[DHCPS_STATE_REQUESTIP].pFuncStateMachine[DHCPS_MSG_RECIVE_DECLINE]            = NULL;
    g_stDHCPSStateMachine[DHCPS_STATE_REQUESTIP].pFuncStateMachine[DHCPS_MSG_RECIVE_RELEASE]            = DHCPS_FSM_REQUESTIP_ReceiveRelease;
    g_stDHCPSStateMachine[DHCPS_STATE_REQUESTIP].pFuncStateMachine[DHCPS_MSG_RECIVE_INFORM]             = NULL;
    g_stDHCPSStateMachine[DHCPS_STATE_REQUESTIP].pFuncStateMachine[DHCPS_MSG_USM_ADDRESS_SUCCESS] = DHCPS_FSM_REQUESTIP_AddressAllocateSuccess;
    g_stDHCPSStateMachine[DHCPS_STATE_REQUESTIP].pFuncStateMachine[DHCPS_MSG_USM_ADDRESS_FAILURE]  = DHCPS_FSM_REQUESTIP_AddressAllocateFailed;
    g_stDHCPSStateMachine[DHCPS_STATE_REQUESTIP].pFuncStateMachine[DHCPS_MSG_USM_DEACTIVE]              = DHCPS_FSM_REQUESTIP_Deactive;
    g_stDHCPSStateMachine[DHCPS_STATE_REQUESTIP].pFuncStateMachine[DHCPS_MSG_TIMER]                           = DHCPS_FSM_REQUESTIP_USMTimerOut;
    g_stDHCPSStateMachine[DHCPS_STATE_REQUESTIP].pFuncStateMachine[DHCPS_MSG_RELAY_SERVER_NAK]                     = NULL;

    /*offer态的状态机处理函数注册*/
    g_stDHCPSStateMachine[DHCPS_STATE_OFFERED].pFuncStateMachine[DHCPS_MSG_RECIVE_DISCOVER]             = DHCPS_FSM_OFFERED_ReceiveDiscover;
    g_stDHCPSStateMachine[DHCPS_STATE_OFFERED].pFuncStateMachine[DHCPS_MSG_RECIVE_REQUEST]              = DHCPS_FSM_OFFERED_ReceiveRequest;
    g_stDHCPSStateMachine[DHCPS_STATE_OFFERED].pFuncStateMachine[DHCPS_MSG_RECIVE_DECLINE]               = DHCPS_FSM_OFFERED_ReceiveDecline;
    g_stDHCPSStateMachine[DHCPS_STATE_OFFERED].pFuncStateMachine[DHCPS_MSG_RECIVE_RELEASE]               = DHCPS_FSM_OFFERED_ReceiveRelease;
    g_stDHCPSStateMachine[DHCPS_STATE_OFFERED].pFuncStateMachine[DHCPS_MSG_RECIVE_INFORM]                = NULL;
    g_stDHCPSStateMachine[DHCPS_STATE_OFFERED].pFuncStateMachine[DHCPS_MSG_USM_ADDRESS_SUCCESS]    = NULL;
    g_stDHCPSStateMachine[DHCPS_STATE_OFFERED].pFuncStateMachine[DHCPS_MSG_USM_ADDRESS_FAILURE]     = NULL;
    g_stDHCPSStateMachine[DHCPS_STATE_OFFERED].pFuncStateMachine[DHCPS_MSG_USM_DEACTIVE]                 = DHCPS_FSM_OFFERED_Deactive;
    g_stDHCPSStateMachine[DHCPS_STATE_OFFERED].pFuncStateMachine[DHCPS_MSG_TIMER]                              = DHCPS_FSM_OFFERED_ClientTimerOut;
    g_stDHCPSStateMachine[DHCPS_STATE_OFFERED].pFuncStateMachine[DHCPS_MSG_RELAY_SERVER_NAK]                     = NULL;


    /*commit态的状态机处理函数注册*/
    g_stDHCPSStateMachine[DHCPS_STATE_COMMITED].pFuncStateMachine[DHCPS_MSG_RECIVE_DISCOVER]          = DHCPS_FSM_COMMITED_ReceiveDiscover;
    g_stDHCPSStateMachine[DHCPS_STATE_COMMITED].pFuncStateMachine[DHCPS_MSG_RECIVE_REQUEST]            = DHCPS_FSM_COMMITED_ReceiveRequest;
    g_stDHCPSStateMachine[DHCPS_STATE_COMMITED].pFuncStateMachine[DHCPS_MSG_RECIVE_DECLINE]             = DHCPS_FSM_COMMITED_ReceiveDecline;
    g_stDHCPSStateMachine[DHCPS_STATE_COMMITED].pFuncStateMachine[DHCPS_MSG_RECIVE_RELEASE]             = DHCPS_FSM_COMMITED_ReceiveRelease;
    g_stDHCPSStateMachine[DHCPS_STATE_COMMITED].pFuncStateMachine[DHCPS_MSG_RECIVE_INFORM]              = DHCPS_FSM_COMMITED_ReceiveInform;
    g_stDHCPSStateMachine[DHCPS_STATE_COMMITED].pFuncStateMachine[DHCPS_MSG_USM_ADDRESS_SUCCESS]  = NULL;
    g_stDHCPSStateMachine[DHCPS_STATE_COMMITED].pFuncStateMachine[DHCPS_MSG_USM_ADDRESS_FAILURE]   = NULL;
    g_stDHCPSStateMachine[DHCPS_STATE_COMMITED].pFuncStateMachine[DHCPS_MSG_USM_DEACTIVE]               = DHCPS_FSM_COMMITED_ReceiveDeactive;
    g_stDHCPSStateMachine[DHCPS_STATE_COMMITED].pFuncStateMachine[DHCPS_MSG_TIMER]                            = DHCPS_FSM_COMMITED_LeaseTimerOut;
    g_stDHCPSStateMachine[DHCPS_STATE_COMMITED].pFuncStateMachine[DHCPS_MSG_RELAY_SERVER_NAK]                     = NULL;

    /* Added start by ZhangYang  z00142225 at 2008-12-29 UGWV900R001C001 for 地址分配功能 */
    /*relay态的状态机处理函数注册*/
    g_stDHCPSStateMachine[DHCPS_STATE_RELAY].pFuncStateMachine[DHCPS_MSG_RECIVE_DISCOVER]          = NULL;
    g_stDHCPSStateMachine[DHCPS_STATE_RELAY].pFuncStateMachine[DHCPS_MSG_RECIVE_REQUEST]            = NULL;
    g_stDHCPSStateMachine[DHCPS_STATE_RELAY].pFuncStateMachine[DHCPS_MSG_RECIVE_DECLINE]             = DHCPS_FSM_RELAY_ReceiveDecline;
    g_stDHCPSStateMachine[DHCPS_STATE_RELAY].pFuncStateMachine[DHCPS_MSG_RECIVE_RELEASE]             = DHCPS_FSM_RELAY_ReceiveRelease;
    g_stDHCPSStateMachine[DHCPS_STATE_RELAY].pFuncStateMachine[DHCPS_MSG_RECIVE_INFORM]              = NULL;
    g_stDHCPSStateMachine[DHCPS_STATE_RELAY].pFuncStateMachine[DHCPS_MSG_USM_ADDRESS_SUCCESS]  = NULL;
    g_stDHCPSStateMachine[DHCPS_STATE_RELAY].pFuncStateMachine[DHCPS_MSG_USM_ADDRESS_FAILURE]   = NULL;
    g_stDHCPSStateMachine[DHCPS_STATE_RELAY].pFuncStateMachine[DHCPS_MSG_USM_DEACTIVE]               = DHCPS_FSM_RELAY_ReceiveDeactive;
    g_stDHCPSStateMachine[DHCPS_STATE_RELAY].pFuncStateMachine[DHCPS_MSG_TIMER]                     = NULL;
    g_stDHCPSStateMachine[DHCPS_STATE_RELAY].pFuncStateMachine[DHCPS_MSG_RELAY_SERVER_NAK]           = DHCPS_FSM_RELAY_ReceiveDecline;
    /* Added end by ZhangYang  z00142225 at 2008-12-29 UGWV900R001C001 for 地址分配功能 */
}

/*****************************************************************************
 函 数 名      : DHCPS_FSM_ReleaseResource
 功能描述   : 释放租约相关的所有资源
                            1.释放报文内存。
                            2.停定时器。
                            3.释放IP地址。
                            不设置状态。
                            不设置使用标志。
 输入参数   : 无
 输出参数   : 无
 返 回 值      : VOS_OK    成功; VOS_ERR    失败
 调用函数   :
 被调函数   :

 修改历史   :
  1.日    期      : 2008年12月2日
    作    者       : dongmingzhou 42828
    修改内容: 新生成函数

*****************************************************************************/
ULONG   DHCPS_FSM_ReleaseResource(DHCPS_LEASE_S *pstLease)
{
    /*入参判断*/
    DHCPS_CHECKLEASEPOINT(pstLease,DHCPS_INTERNAL_BRANCH_124)

    /*释放报文内存*/
    if ((pstLease->pstAnalyzedPacket != NULL)
        && (pstLease->pstAnalyzedPacket != &g_stAnalyzPacket))
    {
        DHCP_Free(DHCPS_HANDLE, pstLease->pstAnalyzedPacket);
    }

    pstLease->pstAnalyzedPacket = NULL;

    /*Todo:停止所有定时器*/
    (VOID)DHCPS_TIMER_StopTimer(pstLease , E_DHCPS_FSM_TIMER);

    (VOID)DHCPS_TIMER_StopTimer(pstLease , E_DHCPS_LEASE_TIMER);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名      : DHCPS_FSM_InitLease
 功能描述   : 初始化租约数据。
 输入参数   : 无
 输出参数   : 无
 返 回 值      : VOS_OK    成功; VOS_ERR    失败
 调用函数   :
 被调函数   :

 修改历史   :
  1.日    期      : 2008年12月2日
    作    者       : dongmingzhou 42828
    修改内容: 新生成函数

*****************************************************************************/
ULONG   DHCPS_FSM_InitLease(DHCPS_LEASE_S *pstLease)
{

    /*入参判断*/
    DHCPS_CHECKLEASEPOINT(pstLease,DHCPS_INTERNAL_BRANCH_125)

    if(1 == pstLease->ucUserNumFlag)
    {
        if (g_ulDHCPSIpnum >0)
        {
            g_ulDHCPSIpnum--;
        }
    }

    pstLease->ucUsed                = DHCPS_LEASE_NOTUSED;
    pstLease->ucLeaseState        = DHCPS_STATE_IDEL;
    pstLease->ucUserNumFlag = 0;
    pstLease->ucRole = DHCPS_GET_ROLE_INVALID;
    pstLease->ucPmipFlag              = 0;
    pstLease->ulAddr                  = 0;
    pstLease->ulIndex                = 0;
    pstLease->pstAnalyzedPacket = NULL;
    pstLease->ucFirstRequestMsgFlag = 0;

    return VOS_OK;
}


ULONG DHCPS_FSM_LeaseStateIsValid(ULONG ulIndex)
{
    if ( (0 == ulIndex)
        || (ulIndex > SDB_MAX_CONTEXT_NUM) )
    {
        DHCPS_DebugPrint(PTM_LOG_ERR, " DHCPS_FSM_LeaseStateIsValid : ulIndex = %u is error!", ulIndex);
        return VOS_FALSE;
    }

    if(DHCPS_STATE_MAX <= g_pstDhcpSLease[ulIndex].ucLeaseState)
    {
        DHCPS_DebugPrint(PTM_LOG_ERR, " DHCPS_BackupDeleteProc : slave the ucLeaseState = %u is error!", g_pstDhcpSLease[ulIndex].ucLeaseState);
        return VOS_FALSE;
    }

    return VOS_TRUE;
}
