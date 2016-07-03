
#include "dhcp_inc.h"
#include "dhcpc_def.h"
#include "dhcpv6_def.h"
#include "dhcpc.h"
#include "dhcpc_dbg.h"
#include "dhcpv6c_pkt.h"
#include "dhcpv6c_fsm.h"

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID          PS_FILE_ID_DHCPV6C_FSM_C
/*lint +e767*/

DHCPV6C_FSM_NODE g_stDhcpv6cStateMachine[DHCPV6C_STATE_BUTT] = {0};

UCHAR *g_ucDhcpv6FsmStateStr[DHCPV6C_STATE_BUTT] =
{
    DHCPC_GET_STR(DHCPV6C_STATE_INITIAL),
    DHCPC_GET_STR(DHCPV6C_STATE_SOLICIT),
    DHCPC_GET_STR(DHCPV6C_STATE_REQUEST),
    DHCPC_GET_STR(DHCPV6C_STATE_BOUND),
    DHCPC_GET_STR(DHCPV6C_STATE_RENEW),
    DHCPC_GET_STR(DHCPV6C_STATE_RELEASE),
    DHCPC_GET_STR(DHCPV6C_STATE_DECLINE),
    DHCPC_GET_STR(DHCPV6C_STATE_END)
};

UCHAR *g_ucDhcpv6FsmEventStr[DHCPV6C_EV_BUTT] =
{
    DHCPC_GET_STR(DHCPV6C_EV_IP_REQUEST),
    DHCPC_GET_STR(DHCPV6C_EV_IP_RELEASE),
    DHCPC_GET_STR(DHCPV6C_EV_IP_DECLINE),
    DHCPC_GET_STR(DHCPV6C_EV_INNER_IP_RELEASE),
    DHCPC_GET_STR(DHCPV6C_EV_DHPCS_ADVERTISE),
    DHCPC_GET_STR(DHCPV6C_EV_DHPCS_REPLY),
    DHCPC_GET_STR(DHCPV6C_EV_DHPCS_MSG_CHECK_ERR),
    DHCPC_GET_STR(DHCPV6C_EV_TIMER_RENEW),
    DHCPC_GET_STR(DHCPV6C_EV_TIMER_RESEND),
    DHCPC_GET_STR(DHCPV6C_EV_TIMER_LEASE_EXPIRE),
    DHCPC_GET_STR(DHCPV6C_EV_NOTIFY_LAP_ALLOC_FAIL),
    DHCPC_GET_STR(DHCPV6C_EV_RELEASE_RESOURCE)
};


ULONG DHCPV6C_TimerCallBack(UCHAR ucIpType, ULONG ulTeidc, UCHAR ucEvent)
{
    //UCHAR ucLogicSlot = 0;
    //ULONG ulSelftSlotState = 0;
    ULONG ulReturn = VOS_ERR;
    DHCPV6C_PRE_RESULT_S stPreResult = {0};

    /* 查找ip控制块 */
    ulReturn = DHCPC_QueryDhcpcContext(ucIpType, ulTeidc, &(stPreResult.pstDhcpcContext));
    if  ( VOS_OK !=  ulReturn)
    {
        return ulReturn;
    }

    if (DHCPV6C_EV_TIMER_RESEND == ucEvent)
    {
        (stPreResult.pstDhcpcContext->ucWaitRspTimeOutNum)++;
    }

    stPreResult.enEvent = (DHCPV6C_EVENT_E)ucEvent;
    DHCPV6C_RunFsm(&stPreResult);

    return VOS_OK;
}


ULONG DHCPC_TimerCallBack(UCHAR ucIpType, ULONG ulTeidc, UCHAR ucEvent)
{
    ULONG ulReturn = VOS_ERR;

    if (LAP_IPV4 == ucIpType)
    {
        /* Dhcpv4c处理 */
        DHCPv4C_TimerCallBack(ucIpType, ulTeidc, ucEvent);
    }
    else
    {
        ulReturn = DHCPV6C_TimerCallBack(ucIpType, ulTeidc, ucEvent);
    }

    return ulReturn;
}

#define ___DHCPV6C_SERVER_MSG_PRE_PROC___

ULONG DHCPV6C_FSM_Solicit_Request_CheckStatusCode(USHORT usStautsCode,
                                        ULONG *pulEvent, UCHAR *pucCause)
{
    *pulEvent = DHCPV6C_EV_DHPCS_MSG_CHECK_ERR;
    *pucCause = DHCPV6C_CAUSE_SERVER_MSG_EXCEPTION;
    switch(usStautsCode)
    {
        case DHCPV6C_STATUS_CODE_NOADDRESS:
            DHCPV6C_DBGCNT_ADD(E_DHCPV6C_STATUSCODE_NOADDR);
            *pucCause = DHCPV6C_CAUSE_SERVER_NO_ADDR;
            break;

        case DHCPV6C_STATUS_CODE_UNSPECFAIL:
            DHCPV6C_DBGCNT_ADD(E_DHCPV6C_STATUSCODE_UNSPECFAIL);
            break;

        case DHCPV6C_STATUS_CODE_USEMULTICAST:
            DHCPV6C_DBGCNT_ADD(E_DHCPV6C_STATUSCODE_USEMULTICAST);
            return VOS_ERR;

        default:
            *pucCause = DHCPV6C_CAUSE_DEFAULT;
            return VOS_OK;
    }

    return VOS_ERR;
}


ULONG DHCPV6C_FSM_Renew_CheckStatusCode(USHORT usStautsCode, ULONG *pulEvent,
                                                        UCHAR *pucCause)
{
    *pulEvent = DHCPV6C_EV_DHPCS_MSG_CHECK_ERR;
    *pucCause = DHCPV6C_CAUSE_SERVER_MSG_EXCEPTION;
    switch(usStautsCode)
    {
        case DHCPV6C_STATUS_CODE_UNSPECFAIL:
            DHCPV6C_DBGCNT_ADD(E_DHCPV6C_STATUSCODE_UNSPECFAIL_2);
            break;

        case DHCPV6C_STATUS_CODE_NOBIND:
            DHCPV6C_DBGCNT_ADD(E_DHCPV6C_STATUSCODE_NOBIND);
            *pulEvent = DHCPV6C_EV_IP_RELEASE;
            break;

        default:
            *pucCause = DHCPV6C_CAUSE_DEFAULT;
            return VOS_OK;
    }

    return VOS_ERR;
}


ULONG DHCPV6C_FSM_StatusCodeCheck(DHCPV6C_STATE_E enState, DHCPV6C_STATUS_CODE_OPTION_S *pstStatusCode,
                                            ULONG *pulEvent, UCHAR *pucCuase)
{
    ULONG ulReturn = VOS_ERR;

    *pulEvent = DHCPV6C_EV_DHPCS_MSG_CHECK_ERR;
    if (NULL == pstStatusCode)
    {
        /* 未携带默认为OK */
        return VOS_OK;
    }

    /* 长度检查 */
    if (pstStatusCode->usLen < sizeof(pstStatusCode->usCode))
    {
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_STATUSCODE_LEN_ERR);
        *pucCuase = DHCPV6C_CAUSE_SERVER_MSG_EXCEPTION;
        return VOS_ERR;
    }

    if (pstStatusCode->usCode > DHCPV6C_STATUS_CODE_USEMULTICAST)
    {
        /* 不在协议规定的范围内,按照OK处理 */
        return VOS_OK;
    }

    switch(enState)
    {
        case DHCPV6C_STATE_SOLICIT:
        case DHCPV6C_STATE_REQUEST:
            ulReturn = DHCPV6C_FSM_Solicit_Request_CheckStatusCode(pstStatusCode->usCode,
                                                                pulEvent, pucCuase);
            break;

        case DHCPV6C_STATE_RENEW:
            ulReturn = DHCPV6C_FSM_Renew_CheckStatusCode(pstStatusCode->usCode,
                                                        pulEvent, pucCuase);
            break;

        default:
            *pucCuase = DHCPV6C_CAUSE_DEFAULT;
            ulReturn = VOS_ERR;
            break;
    }

    return ulReturn;
}


ULONG DHCPV6C_FSM_CheckAllStatusCodeInOption(DHCPV6C_STATE_E enState,
                                        DHCPV6C_OPTION_INFO_S *pstDhcpv6cOptionInfo,
                                        ULONG *pulEvent, UCHAR *pucCause)
{
    ULONG ulReturn = VOS_ERR;

    DHCPC_FUNC_ENTRY();

    ulReturn = DHCPV6C_FSM_StatusCodeCheck(enState,
        pstDhcpv6cOptionInfo->pstMsgStatusCodeOption, pulEvent, pucCause);
    if (VOS_OK != ulReturn)
    {
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "check MsgStatusCode err!");
        return VOS_ERR;
    }

    ulReturn = DHCPV6C_FSM_StatusCodeCheck(enState,
        pstDhcpv6cOptionInfo->pstIaNaStatusCodeOption, pulEvent, pucCause);
    if (VOS_OK != ulReturn)
    {
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "check StatusCode err!");
        return VOS_ERR;
    }

    ulReturn = DHCPV6C_FSM_StatusCodeCheck(enState,
        pstDhcpv6cOptionInfo->pstIaAddrStatusCodeOption, pulEvent, pucCause);
    if (VOS_OK != ulReturn)
    {
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "check IaAddrStatusCode err!");
        return VOS_ERR;
    }

    DHCPC_FUNC_EXIT(VOS_OK);
    return VOS_OK;
}


ULONG DHCPV6C_FSM_Slocit_PreProc_ServerMsg(DHCPV6C_PRE_RESULT_S *pstPreResult)
{
    DHCPV6C_OPTION_INFO_S *pstDhcpv6cOptionInfo = (DHCPV6C_OPTION_INFO_S *)(pstPreResult->pMsg);

    DHCPC_FUNC_ENTRY();

    pstPreResult->enEvent = DHCPV6C_EV_DHPCS_MSG_CHECK_ERR;
#if 0
    if (0 == pstDhcpv6cOptionInfo->pstIaAddrOption->ulValidTime)
    {
        return VOS_ERR;
    }
#endif

    DHCPC_FUNC_EXIT(VOS_OK);
    return VOS_OK;
}


ULONG DHCPV6C_FSM_Request_PreProc_ServerMsg(DHCPV6C_PRE_RESULT_S *pstPreResult)
{
    LONG lIpCmpRet = 0;
    DHCPV6C_OPTION_INFO_S *pstDhcpv6cOptionInfo = (DHCPV6C_OPTION_INFO_S *)(pstPreResult->pMsg);
    DHCPV6C_IAADDR_OPTION_S *pstIaAddrOption = pstDhcpv6cOptionInfo->pstIaAddrOption;
    DHCPV6C_IANA_OPTION_S *pstIaNaOption = pstDhcpv6cOptionInfo->pstIaNaOption;
    DHCPC_CTRLBLK *pstDhcpcContext = pstPreResult->pstDhcpcContext;

    DHCPC_FUNC_ENTRY();

    pstPreResult->enEvent = DHCPV6C_EV_DHPCS_MSG_CHECK_ERR;
    if (DHCPV6_MSG_TYPE_REPLY != pstPreResult->ucDhcpServerMsg)
    {
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_REQUEST_RCV_UNEXCEPT_MSG);
        return DHCPC_RET_DROP_MSG;
    }

#if 0
    lIpCmpRet = VOS_MemCmp(pstDhcpcContext->aulUserIpAddr, &(pstIaAddrOption->stIpv6Addr), sizeof(in6_addr));
    if (0 != lIpCmpRet)
    {
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_REQUEST_ADDR_NOT_EQUAL);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "check addr err! [old: 0x%x %x %x %x] [new: 0x%x %x %x %x]",
                    pstDhcpcContext->aulUserIpAddr[0], pstDhcpcContext->aulUserIpAddr[1],
                    pstDhcpcContext->aulUserIpAddr[2], pstDhcpcContext->aulUserIpAddr[3],
                    pstIaAddrOption->stIpv6Addr.s6_addr32[0], pstIaAddrOption->stIpv6Addr.s6_addr32[1],
                    pstIaAddrOption->stIpv6Addr.s6_addr32[2], pstIaAddrOption->stIpv6Addr.s6_addr32[3]);
        return VOS_ERR;
    }

    if (pstDhcpcContext->ulLease != pstIaAddrOption->ulValidTime)
    {
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_REQUEST_LEASE_NOT_EQUAL);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "check Lease err! [old: %u] [new: %u]",
                        pstDhcpcContext->ulLease, pstIaAddrOption->ulValidTime);
        return VOS_ERR;
    }

    if  ((pstDhcpcContext->ulT1 != pstIaNaOption->ulT1)
        || (pstDhcpcContext->ulT2 != pstIaNaOption->ulT2))
    {
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_REQUEST_T1T2_NOT_EQUAL);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "check T1 T2 err! [old: T1=%u T2=%u] [new: T1=%u T2=%u]", pstDhcpcContext->ulT1,
                    pstDhcpcContext->ulT2, pstIaNaOption->ulT1, pstIaNaOption->ulT2);
        return VOS_ERR;
    }
#endif

    DHCPC_FUNC_EXIT(VOS_OK);
    return VOS_OK;
}


ULONG DHCPV6C_FSM_Renew_PreProc_ServerMsg(DHCPV6C_PRE_RESULT_S *pstPreResult)
{
    LONG lIpCmpRet = 0;
    DHCPV6C_OPTION_INFO_S *pstDhcpv6cOptionInfo = (DHCPV6C_OPTION_INFO_S *)(pstPreResult->pMsg);
    DHCPV6C_IAADDR_OPTION_S *pstIaAddrOption = pstDhcpv6cOptionInfo->pstIaAddrOption;
    DHCPC_CTRLBLK *pstDhcpcContext = pstPreResult->pstDhcpcContext;

    DHCPC_FUNC_ENTRY();

    pstPreResult->enEvent = DHCPV6C_EV_DHPCS_MSG_CHECK_ERR;
    if (DHCPV6_MSG_TYPE_REPLY != pstPreResult->ucDhcpServerMsg)
    {
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_RENEW_RCV_UNEXCEPT_MSG);
        return DHCPC_RET_DROP_MSG;
    }

    lIpCmpRet = VOS_MemCmp(pstDhcpcContext->aulUserIpAddr, &(pstIaAddrOption->stIpv6Addr), sizeof(in6_addr));
    if (0 != lIpCmpRet)
    {
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_RENEW_ADDR_NOT_EQUAL);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "check addr err! [old: 0x%x %x %x %x] [new: 0x%x %x %x %x]",
                    pstDhcpcContext->aulUserIpAddr[0], pstDhcpcContext->aulUserIpAddr[1],
                    pstDhcpcContext->aulUserIpAddr[2], pstDhcpcContext->aulUserIpAddr[3],
                    pstIaAddrOption->stIpv6Addr.s6_addr32[0], pstIaAddrOption->stIpv6Addr.s6_addr32[1],
                    pstIaAddrOption->stIpv6Addr.s6_addr32[2], pstIaAddrOption->stIpv6Addr.s6_addr32[3]);
        return VOS_ERR;
    }

    if (0 == pstIaAddrOption->ulValidTime)
    {
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_RENEW_VALID_TIME_IS_0);
        pstPreResult->enEvent = DHCPV6C_EV_IP_RELEASE;
        DHCPC_DebugPrint(PTM_LOG_ERR, "[dhcpv6c-err]: ulValidTime is 0");
        return VOS_ERR;
    }

    DHCPC_FUNC_EXIT(VOS_OK);
    return VOS_OK;
}


ULONG DHCPV6C_FSM_Release_Decline_PreProc_ServerMsg(DHCPV6C_PRE_RESULT_S *pstPreResult)
{
    ULONG ulReturn = VOS_OK;

    DHCPC_FUNC_ENTRY();

    pstPreResult->enEvent = DHCPV6C_EV_DHPCS_MSG_CHECK_ERR;
    if (DHCPV6_MSG_TYPE_REPLY != pstPreResult->ucDhcpServerMsg)
    {
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_REL_DEC_RCV_UNEXCEPT_MSG);
        ulReturn = DHCPC_RET_DROP_MSG;
    }

    DHCPC_FUNC_EXIT(ulReturn);
    return ulReturn;
}


ULONG DHCPV6C_FSM_Com_PreProc_ServerMsg(DHCPV6C_PRE_RESULT_S *pstPreResult)
{
    ULONG ulReturn = VOS_OK;
    ULONG ulT1 = 0;
    ULONG ulT2 = 0;
    ULONG ulEvent = 0;
    UCHAR ucCause = DHCPV6C_CAUSE_DEFAULT;

    /* 以下为必选信元,如果消息中未携带,在消息解析中就会检查出错.所以此处不会为NULL */
    DHCPV6C_OPTION_INFO_S *pstDhcpv6cOptionInfo = (DHCPV6C_OPTION_INFO_S *)(pstPreResult->pMsg);
    DHCPV6C_IAADDR_OPTION_S *pstIaAddrOption = pstDhcpv6cOptionInfo->pstIaAddrOption;
    DHCPV6C_IANA_OPTION_S *pstIaNaOption = pstDhcpv6cOptionInfo->pstIaNaOption;
    DHCPC_CTRLBLK *pstDhcpcContext = pstPreResult->pstDhcpcContext;

    DHCPC_FUNC_ENTRY();

    /* 先将Cause值、Event初始化 */
    pstDhcpcContext->ucCause = DHCPV6C_CAUSE_SERVER_MSG_EXCEPTION;
    pstPreResult->enEvent = DHCPV6C_EV_DHPCS_MSG_CHECK_ERR;

#if 0
    if (pstIaAddrOption->ulPreTime > pstIaAddrOption->ulValidTime)
    {
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_IAADDR_TIME_ERR);
        DHCPC_DebugPrint(PTM_LOG_ERR, "[dhcpv6c-err]:ulPreTime(%u) > ulValidTime(%u)",
            pstIaAddrOption->ulPreTime, pstIaAddrOption->ulValidTime);
        return VOS_ERR;
    }

    /* 如果租约时间为无限长,不再检查T1、T2的合法性 */
    if (DHCPC_INFINITY_TIME != pstIaAddrOption->ulValidTime)
    {
        /* T1、T2合法性检查 */
        ulT1 = (0 != pstIaNaOption->ulT1)
                ? pstIaNaOption->ulT1 : DHCPC_GET_T1_BY_LEASE(pstIaAddrOption->ulValidTime);
        ulT2 = (0 != pstIaNaOption->ulT2)
                ? pstIaNaOption->ulT2 : DHCPC_GET_T2_BY_LEASE(pstIaAddrOption->ulValidTime);
        if (ulT1 > ulT2)
        {
            DHCPV6C_DBGCNT_ADD(E_DHCPV6C_IANA_T1T2_ERR_2);
            return VOS_ERR;
        }
    }
#endif

    ulReturn = DHCPV6C_FSM_CheckAllStatusCodeInOption((DHCPV6C_STATE_E)(pstDhcpcContext->usDhcpStatus),
                                            pstDhcpv6cOptionInfo, &ulEvent, &ucCause);
    if (VOS_OK != ulReturn)
    {
        pstPreResult->enEvent = ulEvent;
        pstDhcpcContext->ucCause = ucCause;
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "call DHCPV6C_FSM_CheckAllStatusCodeInOption fail! ");
        return VOS_ERR;
    }

    DHCPC_FUNC_EXIT(VOS_OK);
    return VOS_OK;
}


ULONG DHCPV6C_FSM_PreProc_ServerMsg(DHCPV6C_PRE_RESULT_S *pstPreResult)
{
    ULONG ulReturn = VOS_ERR;
    DHCPC_CTRLBLK *pstDhcpcContext = pstPreResult->pstDhcpcContext;

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "state = %u! msg=%u",
                pstDhcpcContext->usDhcpStatus, pstPreResult->ucDhcpServerMsg);

    DHCPV6C_DBGCNT_ADD(E_DHCPV6C_FSM_PRE_PROC_ENTER);

    pstPreResult->enEvent = DHCPV6C_EV_DHPCS_MSG_CHECK_ERR;
    if (NULL == pstPreResult->pMsg)
    {
        VOS_Assert(0);
        return DHCPC_RET_DROP_MSG;
    }

    switch(pstDhcpcContext->usDhcpStatus)
    {
        case DHCPV6C_STATE_SOLICIT:
            ulReturn = DHCPV6C_FSM_Slocit_PreProc_ServerMsg(pstPreResult);
            break;

        case DHCPV6C_STATE_REQUEST:
            ulReturn = DHCPV6C_FSM_Request_PreProc_ServerMsg(pstPreResult);
            break;

        case DHCPV6C_STATE_RENEW:
            ulReturn = DHCPV6C_FSM_Renew_PreProc_ServerMsg(pstPreResult);
            break;

        case DHCPV6C_STATE_RELEASE:
        case DHCPV6C_STATE_DECLINE:
            ulReturn = DHCPV6C_FSM_Release_Decline_PreProc_ServerMsg(pstPreResult);
            return ulReturn;

        default:
            DHCPV6C_DBGCNT_ADD(E_DHCPV6C_FSM_RCV_UNEXCEPT_MSG);
            ulReturn = DHCPC_RET_DROP_MSG;;
    }

    if (VOS_OK != ulReturn)
    {
        pstDhcpcContext->ucCause = DHCPV6C_CAUSE_SERVER_MSG_EXCEPTION;
        return ulReturn;
    }

    ulReturn = DHCPV6C_FSM_Com_PreProc_ServerMsg(pstPreResult);
    if (VOS_OK != ulReturn)
    {
        return ulReturn;
    }

    DHCPV6_TRANSER_SERVER_MSG_TO_EVENT(pstPreResult->enEvent, pstPreResult->ucDhcpServerMsg);

    DHCPV6C_DBGCNT_ADD(E_DHCPV6C_FSM_PRE_PROC_OK);

    pstDhcpcContext->ucCause = DHCPV6C_CAUSE_DEFAULT;
    DHCPC_FUNC_EXIT(VOS_OK);
    return VOS_OK;
}

#define ___DHCPV6C_COMOM_PROC___


ULONG DHCPV6C_SendPacketWithResend(DHCPC_CTRLBLK *pstDhcpcContext, ULONG ulDhpcv6MsgType)
{
    ULONG ulReturn = VOS_ERR;

    DHCPC_FUNC_ENTRY();

    /* 发送消息 */
    ulReturn = DHCPV6C_SendPacket(pstDhcpcContext, ulDhpcv6MsgType);
    if (VOS_OK != ulReturn)
    {
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "[dhcpv6c-err]:call DHCPV6C_SendPacket fail! ulReturn=%u", ulReturn);
        return VOS_ERR;
    }

    /* 启动重发定时器 */
    ulReturn = DHCPC_StartTimer(pstDhcpcContext->ucIpType, pstDhcpcContext->ulTEIDC, DHCPV6C_EV_TIMER_RESEND,
                                pstDhcpcContext->ucResendTimeout, DHCPC_TimerCallBack);
    if (VOS_OK != ulReturn)
    {
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_FSM_START_RESEND_TM_FAIL);
        DHCPC_DebugPrint(PTM_LOG_ERR, "[dhcpv6c-err]:call DHCPC_StartTimer fail! ulReturn=%u", ulReturn);
        return VOS_ERR;
    }

    DHCPC_FUNC_EXIT(VOS_OK);
    return VOS_OK;
}


ULONG DHCPV6C_GetT1(DHCPC_CTRLBLK *pstDhcpcContext)
{
    if (0 == pstDhcpcContext->ulT1)
    {
        return DHCPC_GET_T1_BY_LEASE(pstDhcpcContext->ulLease);
    }

    return pstDhcpcContext->ulT1;
}


ULONG DHCPV6C_GetT2(DHCPC_CTRLBLK *pstDhcpcContext)
{
    if (0 == pstDhcpcContext->ulT2)
    {
        return DHCPC_GET_T2_BY_LEASE(pstDhcpcContext->ulLease);
    }

    return pstDhcpcContext->ulT2;
}


ULONG DHCPV6C_StartT1Timer(DHCPC_CTRLBLK *pstDhcpcContext)
{
    ULONG   ulReturn = VOS_ERR;
    ULONG   ulTimerInterval = 0;
    DHCPV6C_EVENT_E enEvent = DHCPV6C_EV_TIMER_RENEW;
    ULONG   ulLease = pstDhcpcContext->ulLease;

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "T1=%u lease=%u", pstDhcpcContext->ulT1, ulLease);

    ulTimerInterval = DHCPV6C_GetT1(pstDhcpcContext);
    if (ulTimerInterval >= ulLease)
    {
        /* 如果T1的时间比租约时间长,则不再启动Renew定时器,直接启动租约到期定时器 */
        ulTimerInterval = ulLease;
        enEvent = DHCPV6C_EV_TIMER_LEASE_EXPIRE;
        pstDhcpcContext->ucLeaseStatus = DHCPV6C_LEASE_STATE_WAIT_LEASE;
    }

    ulReturn = DHCPC_StartTimer(pstDhcpcContext->ucIpType, pstDhcpcContext->ulTEIDC,
                                enEvent, ulTimerInterval, DHCPC_TimerCallBack);
    if (VOS_OK != ulReturn)
    {
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_FSM_START_T1_FAIL);
    }

    DHCPC_FUNC_EXIT(ulReturn);
    return ulReturn;
}


ULONG DHCPV6C_StartT2Timer(DHCPC_CTRLBLK *pstDhcpcContext)
{
    ULONG   ulReturn = VOS_ERR;
    ULONG   ulT2 = 0;
    ULONG   ulTimerInterval = 0;
    ULONG   ulElapseTime = 0;
    ULONG   ulLease = pstDhcpcContext->ulLease;
    DHCPV6C_EVENT_E enEvent = DHCPV6C_EV_TIMER_RENEW;

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "T1=%u T2=%u lease=%u", pstDhcpcContext->ulT1,
                        pstDhcpcContext->ulT2, ulLease);

    ulElapseTime = DHCPV6C_GetT1(pstDhcpcContext)
                    + (pstDhcpcContext->ucWaitRspTimeOutNum * pstDhcpcContext->ucResendTimeout);

    ulT2 = DHCPV6C_GetT2(pstDhcpcContext);
    if ((ulT2 <= ulElapseTime) || (ulT2 >= ulLease))
    {
        /* 已经过了T2 Renew的时间,或T2时间比租约时间长,则启动租约定时器 */
        if (ulLease <= ulElapseTime)
        {
            /* 租约到期,不再需要启动定时器 */
            pstDhcpcContext->ucCause = DHCPV6C_CAUSE_LEASE_EXPIRE;
            pstDhcpcContext->ucLeaseStatus = DHCPV6C_LEASE_STATE_BUTT;
            return VOS_ERR;
        }

        ulTimerInterval = ulLease - ulElapseTime;
        enEvent = DHCPV6C_EV_TIMER_LEASE_EXPIRE;
        pstDhcpcContext->ucLeaseStatus = DHCPV6C_LEASE_STATE_WAIT_LEASE;
    }
    else
    {
        /* 还未到T2 Renew的时间,则启动Renew定时器 */
        ulTimerInterval = ulT2 - ulElapseTime;
    }

    ulReturn = DHCPC_StartTimer(pstDhcpcContext->ucIpType, pstDhcpcContext->ulTEIDC,
                                enEvent, ulTimerInterval, DHCPC_TimerCallBack);
    if (VOS_OK != ulReturn)
    {
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_FSM_START_T2_FAIL);
    }

    DHCPC_FUNC_EXIT(ulReturn);
    return ulReturn;
}


ULONG DHCPV6C_StartLeaseExpireTimer(DHCPC_CTRLBLK *pstDhcpcContext)
{
    ULONG   ulReturn = VOS_ERR;
    ULONG   ulTimerInterval = 0;
    ULONG   ulElapseTime = 0;
    ULONG   ulLease = pstDhcpcContext->ulLease;

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "T2=%u lease=%u", pstDhcpcContext->ulT2, ulLease);

    ulElapseTime = DHCPV6C_GetT2(pstDhcpcContext)
                    + (pstDhcpcContext->ucWaitRspTimeOutNum * pstDhcpcContext->ucResendTimeout);

    if (ulLease <= ulElapseTime)
    {
        /* 租约已经到期,不再需要启动定时器 */
        pstDhcpcContext->ucCause = DHCPV6C_CAUSE_LEASE_EXPIRE;
        pstDhcpcContext->ucLeaseStatus = DHCPV6C_LEASE_STATE_BUTT;
        return VOS_ERR;
    }

    ulTimerInterval = ulLease - ulElapseTime;

    ulReturn = DHCPC_StartTimer(pstDhcpcContext->ucIpType, pstDhcpcContext->ulTEIDC,
                                DHCPV6C_EV_TIMER_LEASE_EXPIRE, ulTimerInterval, DHCPC_TimerCallBack);
    if (VOS_OK != ulReturn)
    {
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_FSM_START_LEASE_TM_FAIL);
    }

    DHCPC_FUNC_EXIT(ulReturn);
    return ulReturn;
}


ULONG DHCPV6C_StartLeaseTimer(DHCPC_CTRLBLK *pstDhcpcContext)
{
    ULONG   ulReturn = VOS_ERR;
    DHCPV6C_LEASE_STATE_E enLeaseState = (DHCPV6C_LEASE_STATE_E)(pstDhcpcContext->ucLeaseStatus);
    ULONG   ulLease = pstDhcpcContext->ulLease;

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "LeaseState=%u T1=%u T2=%u lease=%u",
                    enLeaseState, pstDhcpcContext->ulT1, pstDhcpcContext->ulT2, ulLease);

    if (DHCPC_INFINITY_TIME == ulLease)
    {
        /* 租约为无限期时,不需要启动RENEW定时器 */
        pstDhcpcContext->ucLeaseStatus = DHCPV6C_LEASE_STATE_BUTT;
        return VOS_OK;
    }

    if (DHCPV6C_LEASE_STATE_WAIT_T1 == enLeaseState)
    {
        ulReturn = DHCPV6C_StartT1Timer(pstDhcpcContext);
    }
    else if (DHCPV6C_LEASE_STATE_WAIT_T2 == enLeaseState)
    {
        ulReturn = DHCPV6C_StartT2Timer(pstDhcpcContext);
    }
    else
    {
        ulReturn = DHCPV6C_StartLeaseExpireTimer(pstDhcpcContext);
    }

    if (VOS_OK != ulReturn)
    {
        /* 启动定时器失败,将租约状态设置为非法值,防止释放地址时重复删除定时器 */
        DHCPC_DebugPrint(PTM_LOG_ERR, "Teidc=0x%x LeaseState=%u",
                        pstDhcpcContext->ulTEIDC,enLeaseState);
        pstDhcpcContext->ucLeaseStatus = DHCPV6C_LEASE_STATE_BUTT;
    }

    DHCPC_FUNC_EXIT(ulReturn);
    return ulReturn;
}


ULONG DHCPV6C_StopLeaseTimer(DHCPC_CTRLBLK *pstDhcpcContext)
{
    ULONG ulReturn = VOS_ERR;
    DHCPV6C_EVENT_E enEvent = DHCPV6C_EV_BUTT;

    DHCPC_FUNC_ENTRY();

    if (pstDhcpcContext->ucLeaseStatus <=  DHCPV6C_LEASE_STATE_WAIT_T2)
    {
        enEvent = DHCPV6C_EV_TIMER_RENEW;
    }
    else if (DHCPV6C_LEASE_STATE_WAIT_LEASE == pstDhcpcContext->ucLeaseStatus)
    {
        enEvent = DHCPV6C_EV_TIMER_LEASE_EXPIRE;
    }
    else
    {
        return VOS_OK;
    }

    ulReturn = DHCPC_StopTimer(pstDhcpcContext->ucIpType, pstDhcpcContext->ulTEIDC, enEvent);

    DHCPC_FUNC_EXIT(ulReturn);
    return ulReturn;
}


ULONG DHCPV6C_FSM_ResendEventComProc(DHCPC_CTRLBLK *pstDhcpcContext, ULONG ulMsgType)
{
    ULONG ulReturn = VOS_ERR;

    DHCPC_FUNC_ENTRY();

    /* 重发消息不再获取重发时间间隔 */

    /* 发送消息并启动重发定时器 */
    ulReturn = DHCPV6C_SendPacketWithResend(pstDhcpcContext, ulMsgType);
    if (VOS_OK != ulReturn)
    {
        DHCPV6C_FreeSeqNum(pstDhcpcContext->usSeqNum);
    }

    DHCPC_FUNC_EXIT(ulReturn);
    return ulReturn;
}


ULONG DHCPV6C_FSM_SendMsgComProc(DHCPV6C_PRE_RESULT_S *pstPreResult, ULONG ulMsgType)
{
    ULONG ulReturn = VOS_ERR;
    DHCPC_CTRLBLK *pstDhcpcContext = pstPreResult->pstDhcpcContext;

    /* 将等待Server响应超时消息次数清0 */
    pstDhcpcContext->ucWaitRspTimeOutNum = 0;

    /* 将记录向server发送消息次数的变量清0 */
    pstDhcpcContext->ucCurSvrSendCount = 0;
    pstDhcpcContext->ucTotalSendCount = 0;

    /* 获取seqno */
    ulReturn = DHCPV6C_AllocSeqNum(&(pstDhcpcContext->usSeqNum), pstDhcpcContext->ulTEIDC, pstDhcpcContext->ucIpType);
    if (VOS_OK != ulReturn)
    {
        pstDhcpcContext->ucCause = DHCPV6C_CAUSE_TID_EXHAUST;
        return VOS_ERR;
    }

    /* 获取重发时间间隔 */
    ulReturn = DHCPM_GetRetransmitTimeOutByIndex(pstDhcpcContext->usServerGrpIndex, &(pstDhcpcContext->ucResendTimeout));
    if (VOS_OK != ulReturn)
    {
        DHCPV6C_FreeSeqNum(pstDhcpcContext->usSeqNum);
        DHCPC_DebugPrint(PTM_LOG_ERR, "[dhcpv6c-err]:call DHCPM_GetRetransmitTimeOutByIndex failed! return=%u", ulReturn);
        return VOS_ERR;
    }

    /* 发送消息并启动重发定时器 */
    ulReturn = DHCPV6C_SendPacketWithResend(pstDhcpcContext, ulMsgType);
    if (VOS_OK != ulReturn)
    {
        DHCPV6C_FreeSeqNum(pstDhcpcContext->usSeqNum);
        return VOS_ERR;
    }

    return VOS_OK;
}


VOID DHCPV6C_FSM_StopMsgSend(DHCPC_CTRLBLK *pstDhcpcContext)
{
    (VOID)DHCPC_StopTimer(pstDhcpcContext->ucIpType, pstDhcpcContext->ulTEIDC, DHCPV6C_EV_TIMER_RESEND);

    /* 释放seqno */
    DHCPV6C_FreeSeqNum(pstDhcpcContext->usSeqNum);

    return;
}


ULONG DHCPV6C_FSM_BoundIp(DHCPV6C_PRE_RESULT_S *pstPreResult)
{
    ULONG   ulReturn = VOS_ERR;
    ULONG   ulRetTimeInSec = 0;
    DHCPC_CTRLBLK *pstDhcpcContext = pstPreResult->pstDhcpcContext;
    DHCPV6C_OPTION_INFO_S *pstDhcpv6Option = (DHCPV6C_OPTION_INFO_S *)(pstPreResult->pMsg);

    DHCPC_FUNC_ENTRY();

    DHCPV6C_FSM_StopMsgSend(pstDhcpcContext);

    /* 迁移到BOUND态 */
    pstDhcpcContext->usDhcpStatus = DHCPV6C_STATE_BOUND;
    pstDhcpcContext->ucLeaseStatus = DHCPV6C_LEASE_STATE_WAIT_T1;

    if ( NULL == pstDhcpv6Option )
    {
        VOS_Assert(0);
        return VOS_ERR;
    }

    /* 保存地址信息到控制块中 */
    DHCPV6C_SaveOptionToContext(pstDhcpcContext, pstDhcpv6Option);

    /* 启动租约定时器 */
    ulReturn = DHCPV6C_StartLeaseTimer(pstDhcpcContext);
    if (VOS_OK != ulReturn)
    {
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_FSM_BOUNDIP_START_TM_FAIL);
        return VOS_ERR;
    }

    ( VOID )PGP_TmNowInSec( &ulRetTimeInSec );
    pstDhcpcContext->ulTimeStamp = ulRetTimeInSec;

    DHCPV6C_DBGCNT_ADD(E_DHCPV6C_FSM_BOUNDIP_SUCC);

    DHCPC_FUNC_EXIT(VOS_OK);
    return VOS_OK;
}


ULONG DHCPV6C_FSM_FirstBoundIp(DHCPV6C_PRE_RESULT_S *pstPreResult)
{
    ULONG ulReturn = 0;
    DHCPC_CTRLBLK *pstDhcpcContext = pstPreResult->pstDhcpcContext;

    DHCPC_FUNC_ENTRY();

    ulReturn = DHCPV6C_FSM_BoundIp(pstPreResult);
    if (VOS_OK != ulReturn)
    {
        /* 绑定IP失败,通知LAP分配地址失败 */
        pstPreResult->enEvent = DHCPV6C_EV_NOTIFY_LAP_ALLOC_FAIL;
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_FSM_1ST_BOUNDIP_FAIL);
        return DHCPV6C_FSM_CONTINUE;
    }

    ulReturn = DHCPC_SendMsgToLAP2ByContext(pstDhcpcContext, DHCPC_SND2_LAP2_ADDR_SUCCESS_MSG);
    if (VOS_OK != ulReturn)
    {
        /* 发消息失败,释放资源,此处不再通知LAP分配失败 */
        pstPreResult->enEvent = DHCPV6C_EV_IP_RELEASE;
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_FSM_SND_LAP_SUCC_FAIL);
        return DHCPV6C_FSM_CONTINUE;
    }

    DHCPC_SET_RESOURCE(pstDhcpcContext->ucResource, DHCPC_LAP_RESOURCE);

    DHCPV6C_DBGCNT_ADD(E_DHCPV6C_FSM_REQ_IP_SUCC);

    DHCPC_FUNC_EXIT(DHCPV6C_FSM_FINISH);
    return DHCPV6C_FSM_FINISH;
}


ULONG DHCPV6C_FSM_IpRelease(DHCPV6C_PRE_RESULT_S *pstPreResult)
{
    ULONG ulReturn = VOS_ERR;
    DHCPC_CTRLBLK *pstDhcpcContext = pstPreResult->pstDhcpcContext;

    DHCPC_FUNC_ENTRY();

    DHCPC_EmsReportAndCleanCause(pstDhcpcContext);

    /* 首先通知lap释放地址 */
    if (0 != DHCPC_GET_RESOURCE(pstDhcpcContext->ucResource, DHCPC_LAP_RESOURCE))
    {
        ulReturn = DHCPC_SendMsgToLAP2ByContext(pstDhcpcContext, DHCPC_SND2_LAP2_ADDR_REL_MSG);
        if (VOS_OK != ulReturn)
        {
            DHCPC_DebugPrint(PTM_LOG_ERR, "\r\n DHCPV6C_FSM_ReleaseResource fail! ucState=%u ulReturn=%u",
                pstDhcpcContext->usDhcpStatus, ulReturn);
        }
    }

    ulReturn = DHCPV6C_FSM_SendMsgComProc(pstPreResult, DHCPV6_MSG_TYPE_RELEASE);
    if (VOS_OK != ulReturn)
    {
        pstPreResult->enEvent = DHCPV6C_EV_RELEASE_RESOURCE;
        return DHCPV6C_FSM_CONTINUE;
    }

    pstDhcpcContext->usDhcpStatus = DHCPV6C_STATE_RELEASE;

    DHCPC_FUNC_EXIT(DHCPV6C_FSM_FINISH);
    return DHCPV6C_FSM_FINISH;
}

#define ___DHCPV6C_EVENT_PROC___

ULONG DHCPV6C_FSM_Init_Rcv_IpReq(DHCPV6C_PRE_RESULT_S *pstPreResult)
{
    ULONG   ulReturn = VOS_ERR;
    DHCPC_CTRLBLK *pstDhcpcContext = pstPreResult->pstDhcpcContext;

    DHCPC_FUNC_ENTRY();

    ulReturn = DHCPV6C_FSM_SendMsgComProc(pstPreResult, DHCPV6_MSG_TYPE_SOLICIT);
    if (VOS_OK != ulReturn)
    {
        pstPreResult->enEvent = DHCPV6C_EV_NOTIFY_LAP_ALLOC_FAIL;
        return DHCPV6C_FSM_CONTINUE;
    }

    /* 迁移到SOLICIT态 */
    pstDhcpcContext->usDhcpStatus = DHCPV6C_STATE_SOLICIT;

    DHCPC_FUNC_EXIT(DHCPV6C_FSM_FINISH);
    return DHCPV6C_FSM_FINISH;
}


ULONG DHCPV6C_FSM_Solicit_Rcv_Advertise(DHCPV6C_PRE_RESULT_S *pstPreResult)
{
    ULONG   ulReturn = VOS_ERR;
    DHCPC_CTRLBLK *pstDhcpcContext = pstPreResult->pstDhcpcContext;
    DHCPV6C_OPTION_INFO_S *pstDhcpv6Option = (DHCPV6C_OPTION_INFO_S *)(pstPreResult->pMsg);

    DHCPC_FUNC_ENTRY();

    /* 将等待dhcp server消息超时次数清0 */
    pstDhcpcContext->ucWaitRspTimeOutNum = 0;

    (VOID)DHCPC_StopTimer(pstDhcpcContext->ucIpType, pstDhcpcContext->ulTEIDC, DHCPV6C_EV_TIMER_RESEND);

    do
    {
        if (NULL == pstDhcpv6Option)
        {
            VOS_Assert(0);
            break;
        }

        DHCPV6C_SaveOptionToContext(pstDhcpcContext, pstDhcpv6Option);

        /* 获取重发时间间隔 */
        ulReturn = DHCPM_GetRetransmitTimeOutByIndex(pstDhcpcContext->usServerGrpIndex, &(pstDhcpcContext->ucResendTimeout));
        if (VOS_OK != ulReturn)
        {
            DHCPC_DebugPrint(PTM_LOG_ERR, "[dhcpv6c-err]:call DHCPM_GetRetransmitTimeOutByIndex failed! return=%u", ulReturn);
            break;
        }

        /* 发送Request消息,并启动重发定时器 */
        ulReturn = DHCPV6C_SendPacketWithResend(pstDhcpcContext, DHCPV6_MSG_TYPE_REQUEST);
        if (VOS_OK != ulReturn)
        {
            break;
        }

        /* 迁移到REQUEST态 */
        pstDhcpcContext->usDhcpStatus = DHCPV6C_STATE_REQUEST;
        return DHCPV6C_FSM_FINISH;
    }
    while(0);

    DHCPV6C_FreeSeqNum(pstDhcpcContext->usSeqNum);
    pstPreResult->enEvent = DHCPV6C_EV_NOTIFY_LAP_ALLOC_FAIL;

    DHCPC_FUNC_EXIT(DHCPV6C_FSM_CONTINUE);
    return DHCPV6C_FSM_CONTINUE;
}


ULONG DHCPV6C_FSM_Solicit_Rcv_Reply(DHCPV6C_PRE_RESULT_S *pstPreResult)
{
    ULONG ulReturn = 0;

    DHCPC_FUNC_ENTRY();

    ulReturn = DHCPV6C_FSM_FirstBoundIp(pstPreResult);

    DHCPC_FUNC_EXIT(ulReturn);
    return ulReturn;
}


ULONG DHCPV6C_FSM_Solicit_Rcv_Resend(DHCPV6C_PRE_RESULT_S *pstPreResult)
{
    ULONG ulReturn = VOS_ERR;
    DHCPV6C_FSM_RERULT_E enRunResult = DHCPV6C_FSM_FINISH;

    DHCPC_FUNC_ENTRY();

    ulReturn = DHCPV6C_FSM_ResendEventComProc(pstPreResult->pstDhcpcContext, DHCPV6_MSG_TYPE_SOLICIT);
    if (VOS_OK != ulReturn)
    {
        enRunResult = DHCPV6C_FSM_CONTINUE;
        pstPreResult->enEvent = DHCPV6C_EV_NOTIFY_LAP_ALLOC_FAIL;
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "call DHCPV6C_FSM_ResendEventComProc fail!");
    }

    DHCPC_FUNC_EXIT(enRunResult);
    return enRunResult;
}


ULONG DHCPV6C_FSM_Solicit_Rcv_MsgCheckErr(DHCPV6C_PRE_RESULT_S *pstPreResult)
{
    DHCPC_FUNC_ENTRY();

    DHCPV6C_FSM_StopMsgSend(pstPreResult->pstDhcpcContext);

    pstPreResult->enEvent = DHCPV6C_EV_NOTIFY_LAP_ALLOC_FAIL;

    DHCPC_FUNC_EXIT(DHCPV6C_FSM_CONTINUE);
    return DHCPV6C_FSM_CONTINUE;
}


ULONG DHCPV6C_FSM_Request_Rcv_Reply(DHCPV6C_PRE_RESULT_S *pstPreResult)
{
    ULONG   ulReturn = VOS_ERR;

    DHCPC_FUNC_ENTRY();

    ulReturn = DHCPV6C_FSM_FirstBoundIp(pstPreResult);

    DHCPC_FUNC_EXIT(ulReturn);
    return ulReturn;
}


ULONG DHCPV6C_FSM_Request_Rcv_Resend(DHCPV6C_PRE_RESULT_S *pstPreResult)
{
    ULONG ulReturn = VOS_ERR;
    DHCPV6C_FSM_RERULT_E enRunResult = DHCPV6C_FSM_FINISH;

    DHCPC_FUNC_ENTRY();

    ulReturn = DHCPV6C_FSM_ResendEventComProc(pstPreResult->pstDhcpcContext, DHCPV6_MSG_TYPE_REQUEST);
    if (VOS_OK != ulReturn)
    {
        enRunResult = DHCPV6C_FSM_CONTINUE;
        pstPreResult->enEvent = DHCPV6C_EV_NOTIFY_LAP_ALLOC_FAIL;
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "call DHCPV6C_FSM_ResendEventComProc fail!");
    }

    DHCPC_FUNC_EXIT(enRunResult);
    return enRunResult;
}


ULONG DHCPV6C_FSM_Request_Rcv_MsgCheckErr(DHCPV6C_PRE_RESULT_S *pstPreResult)
{
    DHCPC_CTRLBLK *pstDhcpcContext = pstPreResult->pstDhcpcContext;
    DHCPV6C_OPTION_INFO_S *pstDhcpv6cOption = (DHCPV6C_OPTION_INFO_S *)(pstPreResult->pMsg);

    DHCPC_FUNC_ENTRY();

    DHCPV6C_FSM_StopMsgSend(pstDhcpcContext);

    (VOID)DHCPC_NotifyLapFail(pstPreResult->pstDhcpcContext);

    pstPreResult->enEvent = DHCPV6C_EV_RELEASE_RESOURCE;
    if (NULL != pstDhcpv6cOption->pstIaAddrOption)
    {
        /* 如果消息中携带了地址,要向dhcp server发送release消息 */
        VOS_MemCpy(pstDhcpcContext->aulUserIpAddr,
            &(pstDhcpv6cOption->pstIaAddrOption->stIpv6Addr), sizeof(in6_addr));
        pstPreResult->enEvent = DHCPV6C_EV_INNER_IP_RELEASE;    /* 使用内部IP释放事件 */
    }

    DHCPC_FUNC_EXIT(DHCPV6C_FSM_CONTINUE);
    return DHCPV6C_FSM_CONTINUE;
}


ULONG DHCPV6C_FSM_Bound_Rcv_Renew(DHCPV6C_PRE_RESULT_S *pstPreResult)
{
    ULONG   ulReturn = VOS_ERR;
    DHCPC_CTRLBLK *pstDhcpcContext = pstPreResult->pstDhcpcContext;
    SDB_GSPU_CONTEXT_S *pstContext = VOS_NULL_PTR;

    DHCPC_FUNC_ENTRY();

    /* 首先查看dhcp控制块对应的上下文是否存在,如果存在再进行renew */
    pstContext = DHCPC_GetOneContextByteidc(pstDhcpcContext->ulTEIDC);
    if (NULL == pstContext)
    {
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_FSM_RNEW_QUERY_PDP_FAIL);
        pstPreResult->enEvent = DHCPV6C_EV_IP_RELEASE;
        return DHCPV6C_FSM_CONTINUE;
    }

    /* 改变租约状态 */
    (pstDhcpcContext->ucLeaseStatus)++;

    ulReturn = DHCPV6C_FSM_SendMsgComProc(pstPreResult, DHCPV6_MSG_TYPE_RENEW);
    if (VOS_OK != ulReturn)
    {
        /* 发送renew消息失败, 则启动下一阶段定时器 */
        ulReturn = DHCPV6C_StartLeaseTimer(pstDhcpcContext);
        if (VOS_OK != ulReturn)
        {
            pstPreResult->enEvent = DHCPV6C_EV_IP_RELEASE;
            return DHCPV6C_FSM_CONTINUE;
        }
        return DHCPV6C_FSM_FINISH;
    }

    pstDhcpcContext->usDhcpStatus = DHCPV6C_STATE_RENEW;
    DHCPC_FUNC_EXIT(DHCPV6C_FSM_FINISH);
    return DHCPV6C_FSM_FINISH;
}


ULONG DHCPV6C_FSM_Bound_Rcv_IpRelease(DHCPV6C_PRE_RESULT_S *pstPreResult)
{
    ULONG ulReturn = VOS_ERR;

    DHCPC_FUNC_ENTRY();

    (VOID)DHCPV6C_StopLeaseTimer(pstPreResult->pstDhcpcContext);

    ulReturn = DHCPV6C_FSM_IpRelease(pstPreResult);

    DHCPC_FUNC_EXIT(ulReturn);
    return ulReturn;
}


ULONG DHCPV6C_FSM_Bound_Rcv_IpDecline(DHCPV6C_PRE_RESULT_S *pstPreResult)
{
    ULONG ulReturn = VOS_ERR;
    DHCPC_CTRLBLK *pstDhcpcContext = pstPreResult->pstDhcpcContext;

    DHCPC_FUNC_ENTRY();

    DHCPC_EmsReportAndCleanCause(pstDhcpcContext);

    (VOID)DHCPV6C_StopLeaseTimer(pstPreResult->pstDhcpcContext);

    ulReturn = DHCPV6C_FSM_SendMsgComProc(pstPreResult, DHCPV6_MSG_TYPE_DECLINE);
    if (VOS_OK != ulReturn)
    {
        pstPreResult->enEvent = DHCPV6C_EV_RELEASE_RESOURCE;
        return DHCPV6C_FSM_CONTINUE;
    }

    pstDhcpcContext->usDhcpStatus = DHCPV6C_STATE_DECLINE;

    DHCPC_FUNC_EXIT(DHCPV6C_FSM_FINISH);
    return DHCPV6C_FSM_FINISH;
}


ULONG DHCPV6C_FSM_Bound_Rcv_LeaseExpire(DHCPV6C_PRE_RESULT_S *pstPreResult)
{
    DHCPC_FUNC_ENTRY();

    pstPreResult->pstDhcpcContext->ucCause = DHCPV6C_CAUSE_LEASE_EXPIRE;

    /* 将租约状态设置为未启动定时器状态,防止以后重复删除定时器 */
    pstPreResult->pstDhcpcContext->ucLeaseStatus = DHCPV6C_LEASE_STATE_BUTT;

    pstPreResult->enEvent = DHCPV6C_EV_IP_RELEASE;

    DHCPC_FUNC_EXIT(DHCPV6C_FSM_CONTINUE);
    return DHCPV6C_FSM_CONTINUE;
}


ULONG DHCPV6C_FSM_Renew_Rcv_Reply(DHCPV6C_PRE_RESULT_S *pstPreResult)
{
    ULONG ulReturn = VOS_ERR;

    DHCPC_FUNC_ENTRY();

    ulReturn = DHCPV6C_FSM_BoundIp(pstPreResult);
    if (VOS_OK != ulReturn)
    {
        pstPreResult->enEvent = DHCPV6C_EV_IP_RELEASE;
        return DHCPV6C_FSM_CONTINUE;
    }

    DHCPV6C_DBGCNT_ADD(E_DHCPV6C_FSM_RENEW_IP_SUCC);

    ulReturn = DHCPC_NotifyBKUpdate(pstPreResult->pstDhcpcContext->ulTEIDC);
    if ( VOS_OK != ulReturn )
    {
         DHCPV6C_DBGCNT_ADD(E_DHCPV6C_RENEW_RCVREPLYBK);
    }

    DHCPC_FUNC_EXIT(DHCPV6C_FSM_FINISH);
    return DHCPV6C_FSM_FINISH;
}


ULONG DHCPV6C_IsLeaseExpireInRenewResend(DHCPC_CTRLBLK *pstDhcpcContext)
{
    ULONG ulElapseTime = 0;
    ULONG ulLease = pstDhcpcContext->ulLease;
    DHCPV6C_LEASE_STATE_E enLeaseState = (DHCPV6C_LEASE_STATE_E)(pstDhcpcContext->ucLeaseStatus);

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "LeaseState=%u T1=%u T2=%u lease=%u resendtime=%u", enLeaseState,
                pstDhcpcContext->ulT1, pstDhcpcContext->ulT2, ulLease, pstDhcpcContext->ucWaitRspTimeOutNum);

    if (DHCPV6C_LEASE_STATE_WAIT_T2 == enLeaseState)
    {
        ulElapseTime = DHCPV6C_GetT1(pstDhcpcContext)
                + (pstDhcpcContext->ucWaitRspTimeOutNum * pstDhcpcContext->ucResendTimeout);

    }
    else if (DHCPV6C_LEASE_STATE_WAIT_LEASE == enLeaseState)
    {
        ulElapseTime = DHCPV6C_GetT2(pstDhcpcContext)
                + (pstDhcpcContext->ucWaitRspTimeOutNum * pstDhcpcContext->ucResendTimeout);
    }
    else
    {
        return VOS_FALSE;
    }

    if (ulElapseTime < ulLease)
    {
        return VOS_FALSE;
    }

    DHCPC_FUNC_EXIT(VOS_TRUE);
    return VOS_TRUE;
}


ULONG DHCPV6C_FSM_Renew_Rcv_Resend(DHCPV6C_PRE_RESULT_S *pstPreResult)
{
    ULONG ulReturn = VOS_ERR;
    DHCPC_CTRLBLK *pstDhcpcContext = pstPreResult->pstDhcpcContext;

    DHCPC_FUNC_ENTRY();

    /* 判断租约是否到期 */
    ulReturn = DHCPV6C_IsLeaseExpireInRenewResend(pstDhcpcContext);
    if (VOS_TRUE == ulReturn)
    {
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "lease expire!");

        /* 释放seqno */
        DHCPV6C_FreeSeqNum(pstDhcpcContext->usSeqNum);

        /* 先迁移回BOUND态 */
        pstDhcpcContext->usDhcpStatus = DHCPV6C_STATE_BOUND;

        pstDhcpcContext->ucCause = DHCPV6C_CAUSE_LEASE_EXPIRE;
        pstDhcpcContext->ucLeaseStatus = DHCPV6C_LEASE_STATE_BUTT;
        pstPreResult->enEvent = DHCPV6C_EV_IP_RELEASE;
        return DHCPV6C_FSM_CONTINUE;
    }

    ulReturn = DHCPV6C_FSM_ResendEventComProc(pstDhcpcContext, DHCPV6_MSG_TYPE_RENEW);
    if (VOS_OK != ulReturn)
    {
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "call DHCPV6C_FSM_ResendEventComProc fail!");

        /* 先迁移回BOUND态 */
        pstDhcpcContext->usDhcpStatus = DHCPV6C_STATE_BOUND;

        /* 启动下一阶段定时器 */
        ulReturn = DHCPV6C_StartLeaseTimer(pstDhcpcContext);
        if (VOS_OK != ulReturn)
        {
            pstPreResult->enEvent = DHCPV6C_EV_IP_RELEASE;
            return DHCPV6C_FSM_CONTINUE;
        }
        return DHCPV6C_FSM_FINISH;
    }

    DHCPC_FUNC_EXIT(DHCPV6C_FSM_FINISH);
    return DHCPV6C_FSM_FINISH;
}


ULONG DHCPV6C_FSM_Renew_Rcv_MsgCheckErr(DHCPV6C_PRE_RESULT_S *pstPreResult)
{
    ULONG   ulReturn = VOS_ERR;
    DHCPC_CTRLBLK *pstDhcpcContext = pstPreResult->pstDhcpcContext;

    DHCPC_FUNC_ENTRY();

    DHCPV6C_FSM_StopMsgSend(pstDhcpcContext);

    /* 迁移回BOUND态 */
    pstDhcpcContext->usDhcpStatus = DHCPV6C_STATE_BOUND;

    ulReturn = DHCPV6C_StartLeaseTimer(pstDhcpcContext);
    if (VOS_OK != ulReturn)
    {
        pstPreResult->enEvent = DHCPV6C_EV_IP_RELEASE;
        return DHCPV6C_FSM_CONTINUE;
    }

    DHCPC_FUNC_EXIT(DHCPV6C_FSM_FINISH);
    return DHCPV6C_FSM_FINISH;
}


ULONG DHCPV6C_FSM_Renew_Rcv_IpRelease(DHCPV6C_PRE_RESULT_S *pstPreResult)
{
    ULONG   ulReturn = VOS_ERR;
    DHCPC_CTRLBLK *pstDhcpcContext = pstPreResult->pstDhcpcContext;

    DHCPC_FUNC_ENTRY();

    DHCPV6C_FSM_StopMsgSend(pstDhcpcContext);

    ulReturn = DHCPV6C_FSM_IpRelease(pstPreResult);

    DHCPC_FUNC_EXIT(ulReturn);
    return ulReturn;
}


ULONG DHCPV6C_FSM_Release_Rcv_Reply(DHCPV6C_PRE_RESULT_S *pstPreResult)
{
    DHCPC_FUNC_ENTRY();

    DHCPV6C_FSM_StopMsgSend(pstPreResult->pstDhcpcContext);

    /* 释放资源 */
    pstPreResult->enEvent = DHCPV6C_EV_RELEASE_RESOURCE;

    DHCPC_FUNC_EXIT(DHCPV6C_FSM_CONTINUE);
    return DHCPV6C_FSM_CONTINUE;
}


ULONG DHCPV6C_FSM_Release_Rcv_Resend(DHCPV6C_PRE_RESULT_S *pstPreResult)
{
    ULONG ulReturn = VOS_ERR;
    DHCPV6C_FSM_RERULT_E enRunResult = DHCPV6C_FSM_FINISH;

    DHCPC_FUNC_ENTRY();

    ulReturn = DHCPV6C_FSM_ResendEventComProc(pstPreResult->pstDhcpcContext, DHCPV6_MSG_TYPE_RELEASE);
    if (VOS_OK != ulReturn)
    {
        pstPreResult->enEvent = DHCPV6C_EV_RELEASE_RESOURCE;
        enRunResult = DHCPV6C_FSM_CONTINUE;
    }

    DHCPC_FUNC_EXIT(enRunResult);
    return enRunResult;
}


ULONG DHCPV6C_FSM_Decline_Rcv_Reply(DHCPV6C_PRE_RESULT_S *pstPreResult)
{
    DHCPC_FUNC_ENTRY();

    DHCPV6C_FSM_StopMsgSend(pstPreResult->pstDhcpcContext);

    /* 释放资源 */
    pstPreResult->enEvent = DHCPV6C_EV_RELEASE_RESOURCE;

    DHCPC_FUNC_EXIT(DHCPV6C_FSM_CONTINUE);
    return DHCPV6C_FSM_CONTINUE;
}


ULONG DHCPV6C_FSM_Decline_Rcv_Resend(DHCPV6C_PRE_RESULT_S *pstPreResult)
{
    ULONG ulReturn = VOS_ERR;
    DHCPV6C_FSM_RERULT_E enRunResult = DHCPV6C_FSM_FINISH;

    DHCPC_FUNC_ENTRY();

    ulReturn = DHCPV6C_FSM_ResendEventComProc(pstPreResult->pstDhcpcContext, DHCPV6_MSG_TYPE_DECLINE);
    if (VOS_OK != ulReturn)
    {
        pstPreResult->enEvent = DHCPV6C_EV_RELEASE_RESOURCE;
        enRunResult = DHCPV6C_FSM_CONTINUE;
    }

    DHCPC_FUNC_EXIT(enRunResult);
    return enRunResult;
}


ULONG DHCPV6C_FSM_ReleaseResource(DHCPV6C_PRE_RESULT_S *pstPreResult)
{
    ULONG   ulReturn = VOS_ERR;
    DHCPC_CTRLBLK *pstDhcpcContext = pstPreResult->pstDhcpcContext;

    DHCPC_FUNC_ENTRY();

    ulReturn = DHCPC_FreeDhcpcContext(LAP_IPV6, pstDhcpcContext->ulTEIDC);
    if (VOS_OK != ulReturn)
    {
        DHCPC_DebugPrint(PTM_LOG_ERR, "\r\n DHCPV6C_FSM_ReleaseResource call DHCPC_FreeDhcpcContext fail! ucState=%u",
            pstDhcpcContext->usDhcpStatus);
    }

    pstPreResult->pstDhcpcContext = NULL;

    DHCPC_FUNC_EXIT(DHCPV6C_FSM_FINISH);
    return DHCPV6C_FSM_FINISH;
}


ULONG DHCPV6C_FSM_NotifyLapAllocFail(DHCPV6C_PRE_RESULT_S *pstPreResult)
{
    DHCPC_FUNC_ENTRY();

    (VOID)DHCPC_NotifyLapFail(pstPreResult->pstDhcpcContext);

    pstPreResult->enEvent = DHCPV6C_EV_RELEASE_RESOURCE;

    DHCPC_FUNC_EXIT(DHCPV6C_FSM_CONTINUE);
    return DHCPV6C_FSM_CONTINUE;
}


VOID DHCPV6C_FSM_Register()
{
    DHCPV6C_STATE_E enState = 0;

    for (enState = DHCPV6C_STATE_INITIAL; enState < DHCPV6C_STATE_BUTT; enState++)
    {
        DHCPV6C_SET_FSM_ACTION(enState, DHCPV6C_EV_RELEASE_RESOURCE, DHCPV6C_FSM_ReleaseResource);
    }

    /* 注册INITIAL态的事件处理函数 */
    DHCPV6C_SET_FSM_ACTION(DHCPV6C_STATE_INITIAL, DHCPV6C_EV_IP_REQUEST,            DHCPV6C_FSM_Init_Rcv_IpReq);
    DHCPV6C_SET_FSM_ACTION(DHCPV6C_STATE_INITIAL, DHCPV6C_EV_NOTIFY_LAP_ALLOC_FAIL, DHCPV6C_FSM_NotifyLapAllocFail);

    /* 注册SOLICIT态的事件处理函数 */
    DHCPV6C_SET_FSM_ACTION(DHCPV6C_STATE_SOLICIT, DHCPV6C_EV_DHPCS_ADVERTISE,       DHCPV6C_FSM_Solicit_Rcv_Advertise);
    DHCPV6C_SET_FSM_ACTION(DHCPV6C_STATE_SOLICIT, DHCPV6C_EV_DHPCS_REPLY,           DHCPV6C_FSM_Solicit_Rcv_Reply);
    DHCPV6C_SET_FSM_ACTION(DHCPV6C_STATE_SOLICIT, DHCPV6C_EV_TIMER_RESEND,          DHCPV6C_FSM_Solicit_Rcv_Resend);
    DHCPV6C_SET_FSM_ACTION(DHCPV6C_STATE_SOLICIT, DHCPV6C_EV_DHPCS_MSG_CHECK_ERR,   DHCPV6C_FSM_Solicit_Rcv_MsgCheckErr);
    DHCPV6C_SET_FSM_ACTION(DHCPV6C_STATE_SOLICIT, DHCPV6C_EV_NOTIFY_LAP_ALLOC_FAIL, DHCPV6C_FSM_NotifyLapAllocFail);
    DHCPV6C_SET_FSM_ACTION(DHCPV6C_STATE_SOLICIT, DHCPV6C_EV_INNER_IP_RELEASE,      DHCPV6C_FSM_IpRelease);

    /* 注册REQUEST态的事件处理函数 */
    DHCPV6C_SET_FSM_ACTION(DHCPV6C_STATE_REQUEST, DHCPV6C_EV_DHPCS_REPLY,           DHCPV6C_FSM_Request_Rcv_Reply);
    DHCPV6C_SET_FSM_ACTION(DHCPV6C_STATE_REQUEST, DHCPV6C_EV_TIMER_RESEND,          DHCPV6C_FSM_Request_Rcv_Resend);
    DHCPV6C_SET_FSM_ACTION(DHCPV6C_STATE_REQUEST, DHCPV6C_EV_DHPCS_MSG_CHECK_ERR,   DHCPV6C_FSM_Request_Rcv_MsgCheckErr);
    DHCPV6C_SET_FSM_ACTION(DHCPV6C_STATE_REQUEST, DHCPV6C_EV_NOTIFY_LAP_ALLOC_FAIL, DHCPV6C_FSM_NotifyLapAllocFail);
    DHCPV6C_SET_FSM_ACTION(DHCPV6C_STATE_REQUEST, DHCPV6C_EV_INNER_IP_RELEASE,      DHCPV6C_FSM_IpRelease);

    /* 注册BOUND态的事件处理函数 */
    DHCPV6C_SET_FSM_ACTION(DHCPV6C_STATE_BOUND, DHCPV6C_EV_TIMER_RENEW,             DHCPV6C_FSM_Bound_Rcv_Renew);
    DHCPV6C_SET_FSM_ACTION(DHCPV6C_STATE_BOUND, DHCPV6C_EV_IP_RELEASE,              DHCPV6C_FSM_Bound_Rcv_IpRelease);
    DHCPV6C_SET_FSM_ACTION(DHCPV6C_STATE_BOUND, DHCPV6C_EV_IP_DECLINE,              DHCPV6C_FSM_Bound_Rcv_IpDecline);
    DHCPV6C_SET_FSM_ACTION(DHCPV6C_STATE_BOUND, DHCPV6C_EV_TIMER_LEASE_EXPIRE,      DHCPV6C_FSM_Bound_Rcv_LeaseExpire);

    /* 注册Renew态的事件处理函数 */
    DHCPV6C_SET_FSM_ACTION(DHCPV6C_STATE_RENEW, DHCPV6C_EV_DHPCS_REPLY,             DHCPV6C_FSM_Renew_Rcv_Reply);
    DHCPV6C_SET_FSM_ACTION(DHCPV6C_STATE_RENEW, DHCPV6C_EV_TIMER_RESEND,            DHCPV6C_FSM_Renew_Rcv_Resend);
    DHCPV6C_SET_FSM_ACTION(DHCPV6C_STATE_RENEW, DHCPV6C_EV_IP_RELEASE,              DHCPV6C_FSM_Renew_Rcv_IpRelease);
    DHCPV6C_SET_FSM_ACTION(DHCPV6C_STATE_RENEW, DHCPV6C_EV_DHPCS_MSG_CHECK_ERR,     DHCPV6C_FSM_Renew_Rcv_MsgCheckErr);

    /* 注册RELEASE态的事件处理函数 */
    DHCPV6C_SET_FSM_ACTION(DHCPV6C_STATE_RELEASE, DHCPV6C_EV_DHPCS_REPLY,           DHCPV6C_FSM_Release_Rcv_Reply);
    DHCPV6C_SET_FSM_ACTION(DHCPV6C_STATE_RELEASE, DHCPV6C_EV_DHPCS_MSG_CHECK_ERR,   DHCPV6C_FSM_Release_Rcv_Reply); /* 与reply事件的处理方式相同 */
    DHCPV6C_SET_FSM_ACTION(DHCPV6C_STATE_RELEASE, DHCPV6C_EV_TIMER_RESEND,          DHCPV6C_FSM_Release_Rcv_Resend);

    /* 注册DECLINE态的事件处理函数 */
    DHCPV6C_SET_FSM_ACTION(DHCPV6C_STATE_DECLINE, DHCPV6C_EV_DHPCS_REPLY,           DHCPV6C_FSM_Decline_Rcv_Reply);
    DHCPV6C_SET_FSM_ACTION(DHCPV6C_STATE_DECLINE, DHCPV6C_EV_DHPCS_MSG_CHECK_ERR,   DHCPV6C_FSM_Decline_Rcv_Reply);  /* 与reply事件的处理方式相同 */
    DHCPV6C_SET_FSM_ACTION(DHCPV6C_STATE_DECLINE, DHCPV6C_EV_TIMER_RESEND,          DHCPV6C_FSM_Decline_Rcv_Resend);

    return;
}


ULONG DHCPV6C_DecideNextStep(DHCPV6C_FSM_RERULT_E enFsmRunResult)
{
    ULONG ulContinueRun = VOS_FALSE;

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "Fsm run result %u", enFsmRunResult);

    switch(enFsmRunResult)
    {
        case DHCPV6C_FSM_FINISH:
            ulContinueRun= VOS_FALSE;
            break;

        case DHCPV6C_FSM_CONTINUE:
            ulContinueRun= VOS_TRUE;
            break;

        default:
            VOS_Assert(0);
            ulContinueRun= VOS_FALSE;
            break;
    }

    return ulContinueRun;
}


VOID DHCPV6C_RunFsm(DHCPV6C_PRE_RESULT_S *pstPreResult)
{
    ULONG   ulLoopNum = 0;
    ULONG   ulFsmRunReturn = VOS_ERR;
    ULONG   ulContinueRun = VOS_FALSE;
    DHCPV6C_STATE_E enState = 0;
    DHCPV6C_EVENT_E enEvent = 0;

    DHCPC_CTRLBLK       *pstDhcpcContext = NULL;
    DHCPV6C_FSM_ACTION  pstFsmAction = NULL;

    DHCPC_FUNC_ENTRY();

    if ((NULL == pstPreResult) || (NULL == pstPreResult->pstDhcpcContext))
    {
        VOS_Assert(0);
        return;
    }

    pstDhcpcContext = pstPreResult->pstDhcpcContext;

    do
    {
        ulLoopNum++;
        if (ulLoopNum >= DHCPV6C_FSM_MAX_STEP)
        {
            VOS_Assert(0);
            break;
        }

        enState = (DHCPV6C_STATE_E) (pstDhcpcContext->usDhcpStatus);
        if (enState >= DHCPV6C_STATE_BUTT)
        {
            VOS_Assert(0);
            break;
        }

        enEvent = pstPreResult->enEvent;
        if (enEvent >= DHCPV6C_EV_BUTT)
        {
            VOS_Assert(0);
            break;
        }

        DHCPC_DebugPrint(PTM_LOG_DEBUG, "[teidc : 0x%x] [state : %s] [event : %s]", pstDhcpcContext->ulTEIDC,
                                g_ucDhcpv6FsmStateStr[enState],g_ucDhcpv6FsmEventStr[enEvent]);
        DHCPV6C_GET_FSM_ACTION(enState, enEvent, pstFsmAction);
        if (NULL == pstFsmAction)
        {
            break;
        }

        ulFsmRunReturn = pstFsmAction(pstPreResult);

        DHCPV6C_FSM_TRACK(enState, enEvent,
            pstPreResult->pstDhcpcContext != NULL ? pstPreResult->pstDhcpcContext->usDhcpStatus : DHCPV6C_STATE_END);

        ulContinueRun = DHCPV6C_DecideNextStep(ulFsmRunReturn);
    } while(ulContinueRun);

    DHCPC_FUNC_EXIT(VOS_OK);
    return;
}

