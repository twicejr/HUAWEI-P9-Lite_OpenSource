#ifndef _DHCPV6C_FSM_H_

#define _DHCPV6C_FSM_H_

/* 状态机状态. 增加状态时需要注意:
 * 1. 状态机动作注册
 * 2. 状态机状态字符串数组维护(g_ucDhcpv6FsmStateStr)
 */
typedef enum tagDHCPV6C_STATE_E
{
    DHCPV6C_STATE_INITIAL,
    DHCPV6C_STATE_SOLICIT,
    DHCPV6C_STATE_REQUEST,
    DHCPV6C_STATE_BOUND,
    DHCPV6C_STATE_RENEW,
    DHCPV6C_STATE_RELEASE,
    DHCPV6C_STATE_DECLINE,
    DHCPV6C_STATE_END,
    DHCPV6C_STATE_BUTT
} DHCPV6C_STATE_E;

typedef enum tagDHCPV6C_LEASE_STATE_E
{
    DHCPV6C_LEASE_STATE_WAIT_T1,
    DHCPV6C_LEASE_STATE_WAIT_T2,
    DHCPV6C_LEASE_STATE_WAIT_LEASE,
    DHCPV6C_LEASE_STATE_BUTT
} DHCPV6C_LEASE_STATE_E;

/* 状态机驱动事件.增加事件时需要注意:
 * 1.各状态的事件处理动作注册.
 * 2.状态机事件字符串数组维护(g_ucDhcpv6FsmEventStr).
 */
typedef enum tagDHCPV6C_EVENT_E
{
    DHCPV6C_EV_IP_REQUEST,
    DHCPV6C_EV_IP_RELEASE,
    DHCPV6C_EV_IP_DECLINE,
    DHCPV6C_EV_INNER_IP_RELEASE,
    DHCPV6C_EV_DHPCS_ADVERTISE,
    DHCPV6C_EV_DHPCS_REPLY,
    DHCPV6C_EV_DHPCS_MSG_CHECK_ERR,
    DHCPV6C_EV_TIMER_RENEW,
    DHCPV6C_EV_TIMER_RESEND,
    DHCPV6C_EV_TIMER_LEASE_EXPIRE,
    DHCPV6C_EV_NOTIFY_LAP_ALLOC_FAIL,
    DHCPV6C_EV_RELEASE_RESOURCE,
    DHCPV6C_EV_BUTT
} DHCPV6C_EVENT_E;

typedef enum tagDHCPV6C_FSM_RESULT_E
{
    DHCPV6C_FSM_FINISH,
    DHCPV6C_FSM_CONTINUE
}DHCPV6C_FSM_RERULT_E;

/* 预处理结果 */
typedef struct tagDHCPV6C_PRE_RESULT_S
{
    DHCPC_CTRLBLK *pstDhcpcContext;
    VOID* pMsg;
    DHCPV6C_EVENT_E enEvent;
    UCHAR ucDhcpServerMsg;
} DHCPV6C_PRE_RESULT_S;

typedef ULONG (* DHCPV6C_FSM_ACTION)(DHCPV6C_PRE_RESULT_S *);

typedef struct
{
    DHCPV6C_FSM_ACTION pFuncFsmAcion[DHCPV6C_EV_BUTT];
    ULONG   aulEventCounter[DHCPV6C_EV_BUTT];
    ULONG   aulTrack[DHCPV6C_EV_BUTT][DHCPV6C_STATE_BUTT];
} DHCPV6C_FSM_NODE;

#define DHCPV6C_FSM_MAX_STEP    10

#define DHCPV6C_SET_FSM_ACTION(state, event, pFuncAction)   {g_stDhcpv6cStateMachine[(state)].pFuncFsmAcion[(event)] = pFuncAction; }
#define DHCPV6C_GET_FSM_ACTION(state, event, pFuncAction) \
{ \
    pFuncAction = g_stDhcpv6cStateMachine[(state)].pFuncFsmAcion[(event)]; \
    (g_stDhcpv6cStateMachine[(state)].aulEventCounter[event])++; \
}

#define DHCPV6C_FSM_TRACK(oldStat, event, NewStat) {g_stDhcpv6cStateMachine[(oldStat)].aulTrack[(event)][(NewStat)]++;}

#define DHCPV6_TRANSER_SERVER_MSG_TO_EVENT(enEvent, msgtype)  \
{ \
    switch ((msgtype))    \
    {   \
        case DHCPV6_MSG_TYPE_ADVERTISE: \
            (enEvent) = DHCPV6C_EV_DHPCS_ADVERTISE; \
            break;  \
        case DHCPV6_MSG_TYPE_REPLY: \
            (enEvent) = DHCPV6C_EV_DHPCS_REPLY; \
            break;  \
        default:    \
            break;  \
    }   \
}

#define DHCPC_LAP_RESOURCE     1

#define DHCPC_SET_RESOURCE(resource, bit)     {(resource) |= (bit);}
#define DHCPC_GET_RESOURCE(resource, bit)     ((resource) & (bit))
#define DHCPC_CLR_RESOURCE(resource, bit)     {(resource) &= ~(bit);}

#define DHCPC_CLR_ALL_RESOURCE(resource)      {(resource) = 0;}

#define DHCPC_INFINITY_TIME     0xffffffff

/*----------------------------------------------------------------------
                              接口函数声明
------------------------------------------------------------------------*/
extern UCHAR *g_ucDhcpv6FsmStateStr[DHCPV6C_STATE_BUTT];
extern UCHAR *g_ucDhcpv6FsmEventStr[DHCPV6C_EV_BUTT];
extern DHCPV6C_FSM_NODE g_stDhcpv6cStateMachine[DHCPV6C_STATE_BUTT];

extern VOID DHCPV6C_RunFsm(DHCPV6C_PRE_RESULT_S *pstPreResult);
extern ULONG DHCPC_TimerCallBack(UCHAR ucIpType, ULONG ulTeidc, UCHAR ucEvent);
/*m00221573 全文件pclint 2012-10-15 start*/
extern ULONG DHCPV6C_StopLeaseTimer(DHCPC_CTRLBLK *pstDhcpcContext);
extern ULONG DHCPV6C_GetT1(DHCPC_CTRLBLK *pstDhcpcContext);
extern ULONG DHCPV6C_GetT2(DHCPC_CTRLBLK *pstDhcpcContext);
extern VOID DHCPV6C_FSM_Register(VOID);
extern ULONG DHCPV6C_FSM_PreProc_ServerMsg(DHCPV6C_PRE_RESULT_S *pstPreResult);
extern inline ULONG  DHCPM_GetRetransmitTimeOutByIndex(ULONG ulDhcpIndex, UCHAR *pucRetransmitTimeOut);
extern ULONG DHCPC_SendMsgToLAP2ByContext(DHCPC_CTRLBLK *pstDhcpcContext, UCHAR MsgType);
extern VOID DHCPC_EmsReportAndCleanCause(DHCPC_CTRLBLK *pstDhcpcContext);
extern ULONG DHCPC_NotifyLapFail(DHCPC_CTRLBLK *pstDhcpcContext);
/*m00221573 全文件pclint 2012-10-15 end*/
extern VOID DHCPv4C_TimerCallBack(UCHAR ucIpType, ULONG ulTeidc, UCHAR ucEvent);

#endif /* _DHCPV6C_FSM_H_ */

