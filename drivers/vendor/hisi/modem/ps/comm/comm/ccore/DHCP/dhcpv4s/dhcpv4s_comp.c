
#include "dhcp_inc.h"
#include "dhcpc_def.h"
#include "dhcpv4s_def.h"
#include "dhcpv4s_type.h"
#include "dhcpv4s_var.h"
#include "dhcpv4s_fun.h"
#include "dhcpv4s_dbgcmd.h"
#include "dhcpv4s_comp.h"
//#include "dhcps_hsgw_public.h"

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID          PS_FILE_ID_DHCPV4S_COMP_C
/*lint +e767*/


ULONG ulDhcpv4sTaskStep = 0;

PTM_COMPONENT_INFO_S g_stDhcpv4sComInfo = { 0 };

VOS_UINT64 g_ullDhcpv4sUsmCsi = 0;

ULONG ulDhcpv4sPerfInitFinish = VOS_FALSE;

#define __INNER_MSG__

/*****************************************************************************
 函 数 名  : DHCPS_SendRtMsg
 功能描述  : dhcpv4 server发送RT消息
 输入参数  : VOS_UINT64 ullDstCsi
             ULONG ulMsgType
             ULONG ulMsgCode
             UCHAR *pucMsg
             ULONG ulMsgLen
 输出参数  : 无
 返 回 值  : ULONG
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年5月17日
    作    者   : y00138047
    修改内容   : 新生成函数

*****************************************************************************/
ULONG DHCPS_SendRtMsg(VOS_UINT64 ullDstCsi, ULONG ulMsgType, ULONG ulMsgCode, UCHAR *pucMsg, ULONG ulMsgLen )
{
    ULONG ulReturn = VOS_OK;
    UCHAR *pucRtMsg = VOS_NULL;

    if ((VOS_NULL == pucMsg) || (0 == ulMsgLen))
    {
        VOS_Assert(0);
        return VOS_ERR;
    }

    pucRtMsg = (UCHAR*)DHCP_RTDistributeAllocMsg(DHCPS_HANDLE, ulMsgLen);
    if (VOS_NULL == pucRtMsg)
    {
        DHCPS_DebugPrint(PTM_LOG_ERR, "DHCP_RTDistributeAllocMsg fail");
        return VOS_ERR;
    }

    VOS_MemCpy(pucRtMsg, pucMsg, ulMsgLen);

    RTD_SET_MSGCODE(pucRtMsg, (USHORT)ulMsgCode);
    ulReturn = DHCP_RTDistributeSend(DHCPS_SELF_CSI,
                           ullDstCsi,
                           pucRtMsg,
                           ulMsgLen,
                           ulMsgType);

    if (VOS_OK != ulReturn)
    {
        DHCPS_DebugPrint(PTM_LOG_ERR, "DHCP_RTDistributeSend fail, return = %x", ulReturn);
        DHCP_RTDistributeFreeMsg(pucRtMsg);
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : DHCPS_SendLeaseTimeOutInnerMsg
 功能描述  : dhcpv4s发送lease timeout消息
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
VOID DHCPS_SendLeaseTimeOutInnerMsg()
{
    ULONG ulReturn = 0;
    DHCPS_INNER_MSG_S stInnerMsg = {0};

    stInnerMsg.ulMsgCode = DHCPS_INNER_LEASE_TIMEOUT;

    ulReturn = DHCPS_SendRtMsg(DHCPS_SELF_CSI, DHCPS_MSG_TYPE_SELF,
                               DHCPS_INNER_LEASE_TIMEOUT, (UCHAR*)&stInnerMsg,
                               sizeof(DHCPS_INNER_MSG_S));
    if ( VOS_OK != ulReturn )
    {
        VOS_Assert(0);
        return;
    }

    return;
}

/*****************************************************************************
 函 数 名  : DHCPS_SendStateTimeOutInnerMsg
 功能描述  : dhcpv4s发送state timeout消息
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
VOID DHCPS_SendStateTimeOutInnerMsg()
{
    ULONG ulReturn = 0;
    DHCPS_INNER_MSG_S stInnerMsg = {0};

    stInnerMsg.ulMsgCode = DHCPS_INNER_STATE_TIMEOUT;

    ulReturn = DHCPS_SendRtMsg(DHCPS_SELF_CSI, DHCPS_MSG_TYPE_SELF,
                               DHCPS_INNER_STATE_TIMEOUT, (UCHAR*)&stInnerMsg,
                               sizeof(DHCPS_INNER_MSG_S));
    if ( VOS_OK != ulReturn )
    {
        VOS_Assert(0);
        return;
    }

    return;
}


/*==========================================================
 *  函数名称:              DHCPS_HA_BackupProc
 *  初稿完成:              2009/03/17
 *  作    者       :          dongmingzhou 42828
 *  函数功能:   从DHCP租约数组中取出待备份的DHCPS控制块，
                               并将其放入备份结构中
 *  输入参数:              主备倒换消息
 *  输出参数:
 *  返回类型:              无
 *  其他说明:              无
 *  调用函数:
 *  主调函数:              AM_USM_HA_EncapBackupMsgByContextRec
 *=========================================================*/
ULONG DHCPS_HA_BackupProc( char **ppbuff,  ULONG ulIndex )
{
    DHCPS_DebugPrint(PTM_LOG_DEBUG, " entry" );

    /*入口参数检查*/
    if ( NULL == ppbuff || NULL == *ppbuff )
    {
        VOS_Assert(0);
        return VOS_ERR;
    }

    /*前提: 上下文索引等于DHCPS控制块索引*/
    if ( ( 0 == ulIndex )
        || ( ulIndex > SDB_MAX_CONTEXT_NUM ) )
    {
        DHCPS_DebugPrint(PTM_LOG_ERR, " master the DHCPS lease index[%u] is error!", ulIndex);
        return VOS_ERR;
    }

    VOS_MemCpy( *ppbuff, &g_pstDhcpSLease[ulIndex], sizeof( DHCPS_LEASE_S ) );
    g_pstDhcpSLease[ulIndex].ucLeaseTimerOP = DHCPS_HA_LEASETIME_INVALID;

    *ppbuff += sizeof( DHCPS_LEASE_S );

    return VOS_OK;
}
/*==========================================================
 *  函数名称:              DHCPS_HA_SLAVE_RestoreProc
 *  初稿完成:              2009/03/17
 *  作    者       :          dongmingzhou 42828
 *  函数功能:   DHCPS模块控制块在备板的备份恢复重建函数
                               从备份结构中取出待备份的DHCP控制块内容，
                               并将其放入DHCP控制块数组中
 *  输入参数:              主备倒换消息
 *  输出参数:
 *  返回类型:              无
 *  其他说明:              无
 *  调用函数:
 *  主调函数:
 *=========================================================*/
ULONG DHCPS_HA_SLAVE_CreateProc( char **ppbuff,  ULONG ulIndex )
{
    DHCPS_LEASE_S *pstLease = NULL;
    ULONG ulTimerOutLength = 0;
    DHCPS_TIMER_TYPE_E enTimerType = E_DHCPS_INVALID_TIMER;

    DHCPS_DebugPrint(PTM_LOG_DEBUG, "entry" );


    /*入口参数检查*/
    if ( NULL == ppbuff || NULL == *ppbuff )
    {
        DHCPS_DebugPrint(PTM_LOG_ERR, "DHCPS_BackupRestoreProc : slave the point is NULL!" );
        DHCPS_InternalBranchCounter(DHCPS_INTERNAL_BRANCH_221);
        return VOS_ERR;
    }

    /*前提: 上下文索引等于DHCPS控制块索引*/
    if ( 0 == ulIndex || ulIndex > SDB_MAX_CONTEXT_NUM )
    {
        /*失败，指针也要偏移*/
        *ppbuff += sizeof( DHCPS_LEASE_S );
        DHCPS_DebugPrint(PTM_LOG_ERR, "DHCPS_BackupRestoreProc : slave DHCPS lease index[%u] error!", ulIndex);
        DHCPS_InternalBranchCounter(DHCPS_INTERNAL_BRANCH_222);
        return VOS_ERR;
    }

    pstLease = &g_pstDhcpSLease[ulIndex];

    if ((0 < pstLease->ulIndex) && (pstLease->ulIndex < SDB_MAX_CONTEXT_NUM))
    {
        if (VOS_TRUE == DHCPS_FSM_LeaseStateIsValid(ulIndex))
        {
            enTimerType = (DHCPS_TIMER_TYPE_E)g_stDHCPSStateMachine[pstLease->ucLeaseState].ulTimerType;
            if ((VOS_TRUE == DHCPS_IsTimerOn(pstLease->ulIndex, enTimerType)) && (pstLease->ucLeaseTimerOP != DHCPS_HA_LEASETIME_INVALID))
            {
                DHCPS_DebugPrint(PTM_LOG_DEBUG, " DHCPS_HA_SLAVE_CreateProc : Slave is timer on ");

                if (VOS_OK != DHCPS_TIMER_StopTimer(pstLease, (ULONG)enTimerType))
                {
                    DHCPS_DebugPrint(PTM_LOG_ERR, " DHCPS_HA_SLAVE_CreateProc : stop timer err ");
                    DHCPS_InternalBranchCounter(DHCPS_INTERNAL_BRANCH_327);
                }
            }
        }
    }

    VOS_MemCpy( pstLease,*ppbuff, sizeof( DHCPS_LEASE_S ) );
    pstLease->pstAnalyzedPacket = NULL;

    DHCPS_DebugPrint(PTM_LOG_DEBUG, " DHCPS_HA_SLAVE_CreateProc : ucUsed = %u, ucLeaseState = %u, ucLeaseTimerOP = %u",
                        pstLease->ucUsed,
                        pstLease->ucLeaseState,
                        pstLease->ucLeaseTimerOP);

    if (VOS_TRUE == DHCPS_FSM_LeaseStateIsValid(ulIndex))
    {
        ulTimerOutLength = g_stDHCPSStateMachine[pstLease->ucLeaseState].ulTimerOutLength;
        enTimerType = (DHCPS_TIMER_TYPE_E)g_stDHCPSStateMachine[pstLease->ucLeaseState].ulTimerType;

        /* 如果时长不为0，启动定时器 */
        if ((0 != ulTimerOutLength) && (pstLease->ucLeaseTimerOP & DHCPS_HA_LEASETIME_START))
        {
            if (VOS_OK != DHCPS_TIMER_StartTimer(pstLease, enTimerType, ulTimerOutLength))
            {
                DHCPS_DebugPrint(PTM_LOG_ERR, " DHCPS_HA_SLAVE_CreateProc : Lease Start Timer ERR ");
                DHCPS_InternalBranchCounter(DHCPS_INTERNAL_BRANCH_223);
            }
        }
    }

    pstLease->ucLeaseTimerOP = DHCPS_HA_LEASETIME_INVALID;

    *ppbuff += sizeof( DHCPS_LEASE_S );

    return VOS_OK;
}
/*==========================================================
 *  函数名称:              DHCPS_HA_SLAVE_UpdateProc
 *  初稿完成:              2009/03/17
 *  作    者       :          dongmingzhou 42828
 *  函数功能:   DHCPS模块控制块在备板的备份更新函数
                               从备份结构中取出待备份的DHCPS控制块内容，
                               并将其放入DHCP控制块数组中
 *  输入参数:              主备倒换消息
 *  输出参数:
 *  返回类型:              无
 *  其他说明:              无
 *  调用函数:
 *  主调函数:
 *=========================================================*/
ULONG DHCPS_HA_SLAVE_UpdateProc( char **ppbuff,  ULONG ulIndex )
{
    DHCPS_LEASE_S *pstLease = NULL;
    ULONG ulTimerOutLength = 0;
    DHCPS_TIMER_TYPE_E enTimerType = E_DHCPS_INVALID_TIMER;

    DHCPS_DebugPrint(PTM_LOG_DEBUG, " DHCPS_HA_SLAVE_UpdateProc : slave Enter. " );


    /*入口参数检查*/
    if ( NULL == ppbuff || NULL == *ppbuff )
    {
        DHCPS_DebugPrint(PTM_LOG_ERR, " DHCPS_HA_SLAVE_UpdateProc : slave the point is NULL!" );
        return VOS_ERR;
    }

    /*前提: 上下文索引等于dhcp控制块索引*/
    if ( (0 == ulIndex)
        || (ulIndex > SDB_MAX_CONTEXT_NUM) )
    {
        /*失败，指针也要偏移*/
        *ppbuff += sizeof( DHCPS_LEASE_S );
        DHCPS_DebugPrint(PTM_LOG_ERR, " DHCPS_HA_SLAVE_UpdateProc : slave the index[%u]  is error!", ulIndex);
        DHCPS_InternalBranchCounter(DHCPS_INTERNAL_BRANCH_224);
        return VOS_ERR;
    }

    pstLease = &g_pstDhcpSLease[ulIndex];

    if ((0 < pstLease->ulIndex) && (pstLease->ulIndex < SDB_MAX_CONTEXT_NUM))
    {
        if (VOS_TRUE == DHCPS_FSM_LeaseStateIsValid(ulIndex))
        {
            enTimerType = (DHCPS_TIMER_TYPE_E)g_stDHCPSStateMachine[pstLease->ucLeaseState].ulTimerType;
            if ((VOS_TRUE == DHCPS_IsTimerOn(pstLease->ulIndex, enTimerType)) && (pstLease->ucLeaseTimerOP != DHCPS_HA_LEASETIME_INVALID))
            {
                DHCPS_DebugPrint(PTM_LOG_DEBUG, " DHCPS_HA_SLAVE_UpdateProc : Slave is timer on ");

                if (VOS_OK != DHCPS_TIMER_StopTimer(pstLease, (ULONG)enTimerType))
                {
                    DHCPS_DebugPrint(PTM_LOG_ERR, " DHCPS_HA_SLAVE_UpdateProc : stop timer err ");
                    DHCPS_InternalBranchCounter(DHCPS_INTERNAL_BRANCH_328);
                }
            }
        }
    }

    VOS_MemCpy( pstLease ,*ppbuff, sizeof( DHCPS_LEASE_S ) );
    pstLease->pstAnalyzedPacket = NULL;

    if (VOS_TRUE == DHCPS_FSM_LeaseStateIsValid(ulIndex))
    {
        /* 定时器处理 */
        ulTimerOutLength = g_stDHCPSStateMachine[pstLease->ucLeaseState].ulTimerOutLength;
        enTimerType = (DHCPS_TIMER_TYPE_E)g_stDHCPSStateMachine[pstLease->ucLeaseState].ulTimerType;

        if ((0 != ulTimerOutLength) && (pstLease->ucLeaseTimerOP & DHCPS_HA_LEASETIME_START))
        {
            if (VOS_OK != DHCPS_TIMER_StartTimer(pstLease, enTimerType, ulTimerOutLength))
            {
                DHCPS_DebugPrint(PTM_LOG_ERR, " DHCPS_HA_SLAVE_UpdateProc : Lease Start Timer ERR ");
                DHCPS_InternalBranchCounter(DHCPS_INTERNAL_BRANCH_226);
            }
        }
    }

    pstLease->ucLeaseTimerOP = DHCPS_HA_LEASETIME_INVALID;

    *ppbuff += sizeof( DHCPS_LEASE_S );

    DHCPS_DebugPrint(PTM_LOG_DEBUG, " DHCPS_HA_SLAVE_UpdateProc : slave Exit. " );

    return VOS_OK;
}

/*==========================================================
 *  函数名称:              DHCPS_HA_SLAVE_DeleteProc
 *  初稿完成:              2009/03/17
 *  作    者       :          dongmingzhou 42828
 *  函数功能:   DHCPS模块控制块在备板的备份删除函数
 *  输入参数:              主备倒换消息
 *  输出参数:
 *  返回类型:              无
 *  其他说明:              无
 *  调用函数:
 *  主调函数:
 *=========================================================*/
ULONG DHCPS_HA_SLAVE_DeleteProc( ULONG ulIndex )
{
    DHCPS_TIMER_TYPE_E enTimerType = E_DHCPS_INVALID_TIMER;
    UCHAR ucLeaseState = 0;

    DHCPS_DebugPrint(PTM_LOG_DEBUG, " DHCPS_BackupDeleteProc : slave Enter. " );

    /*前提: 上下文索引等于DHCPS控制块索引*/
    if ( (0 == ulIndex)
        || (ulIndex > SDB_MAX_CONTEXT_NUM) )
    {
        DHCPS_DebugPrint(PTM_LOG_ERR, " DHCPS_BackupDeleteProc : slave the index[%u]  is error!", ulIndex);
        DHCPS_InternalBranchCounter(DHCPS_INTERNAL_BRANCH_227);
        return VOS_ERR;
    }

    if (VOS_TRUE != DHCPS_FSM_LeaseStateIsValid(ulIndex))
    {
        DHCPS_DebugPrint(PTM_LOG_ERR, " DHCPS_BackupDeleteProc : slave the ucLeaseState is error!" );
        DHCPS_InternalBranchCounter(DHCPS_INTERNAL_BRANCH_320);
        return VOS_ERR;
    }

    enTimerType = (DHCPS_TIMER_TYPE_E)g_stDHCPSStateMachine[ucLeaseState].ulTimerType;

    if (VOS_TRUE == DHCPS_IsTimerOn(ulIndex, enTimerType))
    {
        (VOID)DHCPS_TIMER_StopTimer(&g_pstDhcpSLease[ulIndex] , enTimerType);
    }

    PGP_MemZero(&g_pstDhcpSLease[ulIndex], sizeof(DHCPS_LEASE_S));

    DHCPS_DebugPrint(PTM_LOG_DEBUG, " DHCPS_BackupDeleteProc : slave Exit. " );

    return VOS_OK;
}

#define __DHCPS_COMP_INIT__

/*****************************************************************************
 函 数 名  : DHCPS_OmInitial
 功能描述  : DHCPC性能统计初始化
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
ULONG DHCPS_OmInitial()
{
    /* 注册性能统计 for pgw */
    if ((g_UEtoPGW_ulDHCPV4DiscoveryNumAddr = PerfGetFamPerfCounterAddress(
             PERF_TYPE_PGW_S5,
             PERF_TYPE_PGW_RCV_DHCPV4_DIS_FROM_UE_PKTS,
             VOS_NULL_PTR))
        == VOS_NULL_PTR)
    {
        /* 写日志 */
        DHCPS_DebugPrint(PTM_LOG_ERR, "DHCPS_OmInitial GetAddress of  PERF_TYPE_PGW_RCV_DHCPV4_DIS_FROM_UE_PKTS fail!");
        return VOS_ERR;
    }

    if ((g_UEtoPGW_ulDHCPV4RequestNumAddr = PerfGetFamPerfCounterAddress(
             PERF_TYPE_PGW_S5,
             PERF_TYPE_PGW_RCV_DHCPV4_REQ_FROM_UE_PKTS,
             VOS_NULL_PTR))
        == VOS_NULL_PTR)
    {
        /* 写日志 */
        DHCPS_DebugPrint(PTM_LOG_ERR, "DHCPS_OmInitial GetAddress of  PERF_TYPE_PGW_RCV_DHCPV4_REQ_FROM_UE_PKTS fail!");
        return VOS_ERR;
    }

    if ((g_UEtoPGW_ulDHCPV4DeclineNumAddr = PerfGetFamPerfCounterAddress(
             PERF_TYPE_PGW_S5,
             PERF_TYPE_PGW_RCV_DHCPV4_DEC_FROM_UE_PKTS,
             VOS_NULL_PTR))
        == VOS_NULL_PTR)
    {
        /* 写日志 */
        DHCPS_DebugPrint(PTM_LOG_ERR, "DHCPS_OmInitial GetAddress of  PERF_TYPE_PGW_RCV_DHCPV4_DEC_FROM_UE_PKTS fail!");
        return VOS_ERR;
    }

    if ((g_UEtoPGW_ulDHCPV4ReleaseNumAddr = PerfGetFamPerfCounterAddress(
             PERF_TYPE_PGW_S5,
             PERF_TYPE_PGW_RCV_DHCPV4_REL_FROM_UE_PKTS,
             VOS_NULL_PTR))
        == VOS_NULL_PTR)
    {
        /* 写日志 */
        DHCPS_DebugPrint(PTM_LOG_ERR, "DHCPS_OmInitial GetAddress of  PERF_TYPE_PGW_RCV_DHCPV4_REL_FROM_UE_PKTS fail!");
        return VOS_ERR;
    }

    if ((g_UEtoPGW_ulDHCPV4InformNumAddr = PerfGetFamPerfCounterAddress(
             PERF_TYPE_PGW_S5,
             PERF_TYPE_PGW_RCV_DHCPV4_INFORM_FROM_UE_PKTS,
             VOS_NULL_PTR))
        == VOS_NULL_PTR)
    {
        /* 写日志 */
        DHCPS_DebugPrint(PTM_LOG_ERR, "DHCPS_OmInitial GetAddress of  PERF_TYPE_PGW_RCV_DHCPV4_INFORM_FROM_UE_PKTS fail!");
        return VOS_ERR;
    }

    if ((g_PGWtoUE_ulDHCPV4OfferNumAddr = PerfGetFamPerfCounterAddress(
             PERF_TYPE_PGW_S5,
             PERF_TYPE_PGW_SEND_DHCPV4_OFFER_TO_UE_PKTS,
             VOS_NULL_PTR))
        == VOS_NULL_PTR)
    {
        /* 写日志 */
        DHCPS_DebugPrint(PTM_LOG_ERR, "DHCPS_OmInitial GetAddress of  PERF_TYPE_PGW_SEND_DHCPV4_OFFER_TO_UE_PKTS fail!");
        return VOS_ERR;
    }

    if ((g_PGWtoUE_ulDHCPV4AckNumAddr = PerfGetFamPerfCounterAddress(
             PERF_TYPE_PGW_S5,
             PERF_TYPE_PGW_SEND_DHCPV4_ACK_TO_UE_PKTS,
             VOS_NULL_PTR))
        == VOS_NULL_PTR)
    {
        /* 写日志 */
        DHCPS_DebugPrint(PTM_LOG_ERR, "DHCPS_OmInitial GetAddress of  PERF_TYPE_PGW_SEND_DHCPV4_ACK_TO_UE_PKTS fail!");
        return VOS_ERR;
    }

    if ((g_PGWtoUE_ulDHCPV4NakNumAddr = PerfGetFamPerfCounterAddress(
             PERF_TYPE_PGW_S5,
             PERF_TYPE_PGW_SEND_DHCPV4_NAK_TO_UE_PKTS,
             VOS_NULL_PTR))
        == VOS_NULL_PTR)
    {
        /* 写日志 */
        DHCPS_DebugPrint(PTM_LOG_ERR, "DHCPS_OmInitial GetAddress of  PERF_TYPE_PGW_SEND_DHCPV4_NAK_TO_UE_PKTS fail!");
        return VOS_ERR;
    }

    /*性能统计 for sgw*/
    if ((g_UEtoSGW_ulDHCPV4DiscoveryNumAddr = PerfGetFamPerfCounterAddress(
             PERF_TYPE_SGW_SM,
             PERF_TYPE_SGW_SM_RCV_DHCPV4_DIS_FROM_UE_PKTS,
             VOS_NULL_PTR))
        == VOS_NULL_PTR)
    {
        /* 写日志 */
        DHCPS_DebugPrint(PTM_LOG_ERR, "DHCPS_OmInitial GetAddress of  PERF_TYPE_SGW_SM_RCV_DHCPV4_DIS_FROM_UE_PKTS fail!");
        return VOS_ERR;
    }

    if ((g_UEtoSGW_ulDHCPV4RequestNumAddr = PerfGetFamPerfCounterAddress(
             PERF_TYPE_SGW_SM,
             PERF_TYPE_SGW_SM_RCV_DHCPV4_REQ_FROM_UE_PKTS,
             VOS_NULL_PTR))
        == VOS_NULL_PTR)
    {
        /* 写日志 */
        DHCPS_DebugPrint(PTM_LOG_ERR, "DHCPS_OmInitial GetAddress of  PERF_TYPE_SGW_SM_RCV_DHCPV4_REQ_FROM_UE_PKTS fail!");
        return VOS_ERR;
    }

    if ((g_UEtoSGW_ulDHCPV4DeclineNumAddr = PerfGetFamPerfCounterAddress(
             PERF_TYPE_SGW_SM,
             PERF_TYPE_SGW_SM_RCV_DHCPV4_DEC_FROM_UE_PKTS,
             VOS_NULL_PTR))
        == VOS_NULL_PTR)
    {
        /* 写日志 */
        DHCPS_DebugPrint(PTM_LOG_ERR, "DHCPS_OmInitial GetAddress of  PERF_TYPE_SGW_SM_RCV_DHCPV4_DEC_FROM_UE_PKTS fail!");
        return VOS_ERR;
    }

    if ((g_UEtoSGW_ulDHCPV4ReleaseNumAddr = PerfGetFamPerfCounterAddress(
             PERF_TYPE_SGW_SM,
             PERF_TYPE_SGW_SM_RCV_DHCPV4_REL_FROM_UE_PKTS,
             VOS_NULL_PTR))
        == VOS_NULL_PTR)
    {
        /* 写日志 */
        DHCPS_DebugPrint(PTM_LOG_ERR, "DHCPS_OmInitial GetAddress of  PERF_TYPE_SGW_SM_RCV_DHCPV4_REL_FROM_UE_PKTS fail!");
        return VOS_ERR;
    }

    if ((g_UEtoSGW_ulDHCPV4InformNumAddr = PerfGetFamPerfCounterAddress(
             PERF_TYPE_SGW_SM,
             PERF_TYPE_SGW_SM_RCV_DHCPV4_INFO_FROM_UE_PKTS,
             VOS_NULL_PTR))
        == VOS_NULL_PTR)
    {
        /* 写日志 */
        DHCPS_DebugPrint(PTM_LOG_ERR, "DHCPS_OmInitial GetAddress of  PERF_TYPE_SGW_SM_RCV_DHCPV4_INFO_FROM_UE_PKTS fail!");
        return VOS_ERR;
    }

    if ((g_SGWtoUE_ulDHCPV4OfferNumAddr = PerfGetFamPerfCounterAddress(
             PERF_TYPE_SGW_SM,
             PERF_TYPE_SGW_SM_SEND_DHCPV4_OFFER_TO_UE_PKTS,
             VOS_NULL_PTR))
        == VOS_NULL_PTR)
    {
        /* 写日志 */
        DHCPS_DebugPrint(PTM_LOG_ERR, "DHCPS_OmInitial GetAddress of  PERF_TYPE_SGW_SM_SEND_DHCPV4_OFFER_TO_UE_PKTS fail!");
        return VOS_ERR;
    }

    if ((g_SGWtoUE_ulDHCPV4AckNumAddr = PerfGetFamPerfCounterAddress(
             PERF_TYPE_SGW_SM,
             PERF_TYPE_SGW_SM_SEND_DHCPV4_ACK_TO_UE_PKTS,
             VOS_NULL_PTR))
        == VOS_NULL_PTR)
    {
        /* 写日志 */
        DHCPS_DebugPrint(PTM_LOG_ERR, "DHCPS_OmInitial GetAddress of  PERF_TYPE_SGW_SM_SEND_DHCPV4_ACK_TO_UE_PKTS fail!");
        return VOS_ERR;
    }

    if ((g_SGWtoUE_ulDHCPV4NakNumAddr = PerfGetFamPerfCounterAddress(
             PERF_TYPE_SGW_SM,
             PERF_TYPE_SGW_SM_SEND_DHCPV4_NAK_TO_UE_PKTS,
             VOS_NULL_PTR))
        == VOS_NULL_PTR)
    {
        /* 写日志 */
        DHCPS_DebugPrint(PTM_LOG_ERR, "DHCPS_OmInitial GetAddress of  PERF_TYPE_SGW_SM_SEND_DHCPV4_NAK_TO_UE_PKTS fail!");
        return VOS_ERR;
    }

    ulDhcpv4sPerfInitFinish = VOS_TRUE;

    return VOS_OK;
}

/*==========================================================
 *  函数名称: DHCPS_OM_QueryIpinuseProc
 *  初稿完成:
 *  作    者:
 *  函数功能: dhcpserver查询使用的IP处理流程

 *  输入参数:
 *  输出参数:
 *  返回类型: 无
 *  其他说明: 无
 *  调用函数:
 *  主调函数:
 *=========================================================*/
VOID DHCPS_OM_QueryIpinuseProc( UCHAR * pucMsg,
                                                                   ULONG ulMsgLen ,
                                                                   VOS_VOID ** ppSendData,
                                                                   ULONG *pulSendDataLen)
{
    DHCPS_IPINUSE_MSG_S *pstReplyMsg = NULL;

    ULONG ulReqMsgLen = sizeof(DHCPS_IPINUSE_MSG_S);
    ULONG ulReplyMsgLen = sizeof(DHCPS_IPINUSE_MSG_S);

    if ((VOS_NULL_PTR == pucMsg)
        ||(VOS_NULL_PTR == ppSendData)
        || (ulReqMsgLen != ulMsgLen))
    {
        VOS_DBGASSERT(VOS_FALSE);
        return;
    }

    DHCPS_DebugPrint(PTM_LOG_DEBUG, "entry");

    /* 分配消息发送所需的内存 */
    pstReplyMsg = (DHCPS_IPINUSE_MSG_S *)IPC_RPC_AllocMsg(ulReplyMsgLen, MID_DHCPS);
    if (NULL == pstReplyMsg)
    {
        DHCPS_DebugPrint(PTM_LOG_ERR, " IPC_RPC_AllocMsg fail !");
        return;
    }

    (VOID)VOS_MemSet((VOID *)(pstReplyMsg), 0, sizeof(DHCPS_IPINUSE_MSG_S));

    pstReplyMsg->usMsgType = VOS_HTONS(MSG_ACK);
    pstReplyMsg->ucResult = VOS_OK;
    pstReplyMsg->ucScId = (UCHAR)DHCPS_SELF_CMPIDX_INSG;
    pstReplyMsg->ulIpNum = VOS_HTONL(g_ulDHCPSIpnum);

    *ppSendData = (VOS_VOID *)pstReplyMsg;
    *pulSendDataLen = ulReplyMsgLen;

    return;
}

/*==========================================================
 *  函数名称: DHCPS_IpcCallback
 *  初稿完成:
 *  作    者:
 *  函数功能: dhcpserverIPC回调处理函数

 *  输入参数:
 *  输出参数:
 *  返回类型: 无
 *  其他说明: 无
 *  调用函数:
 *  主调函数:
 *=========================================================*/
VOID DHCPS_IpcCallback( ULONG ulSrcNode, ULONG ulSrcModuleID,
                        VOID *pReceiveData, ULONG ulReceiveDataLen,
                        VOID **ppSendData, ULONG *pulSendDataLen )
{
    USHORT usMsgCode = 0;
    UCHAR * pucMsg = NULL;
    ULONG ulMsgLen = NULL;

    /* 参数检查 */
   if((NULL == pReceiveData) || (NULL == ppSendData) || (NULL == pulSendDataLen))
   {
       VOS_Assert(VOS_FALSE);
       return;
   }
   /*数据长度的判断*/
   if( sizeof(MSG_HDR_S) >= ulReceiveDataLen)
   {
       VOS_Assert(VOS_FALSE);

       return;
   }

   usMsgCode = VOS_HTONS(((MSG_HDR_S *)pReceiveData)->usMsgCode);

   pucMsg = (UCHAR *)pReceiveData;
   ulMsgLen = ulReceiveDataLen;

   switch(usMsgCode)
   {
        case DHCPS_IPNUM_REQ :
            DHCPS_OM_QueryIpinuseProc(pucMsg , ulMsgLen , ppSendData, pulSendDataLen);

            break;

        default:
            DHCPS_DebugPrint(PTM_LOG_DEBUG, " DHCPS_IpcCallback: Exceptional IPC-RPC Msg!ucMsgCode = %d\n",usMsgCode);

        break;
   }
   return;
}

/*****************************************************************************
 函 数 名  : DHCPS_MallocNode
 功能描述  : 申请指定大小的内存
 输入参数  : 无
 输出参数  : 无
 返 回 值  : ULONG
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月25日
    作    者   : guolixian 00171003
    修改内容   : 新生成函数
*****************************************************************************/
ULONG DHCPS_MallocNode(UCHAR **ppucNode,ULONG ulLength)
{

    /* 申请发送消息的缓冲区空间*/
    *ppucNode = (UCHAR *) DHCP_Malloc(DHCPS_HANDLE, ulLength);
    if( NULL == *ppucNode )
    {
        VOS_Assert(0);
        return VOS_ERR;
    }
    DHCP_MemZero(*ppucNode , ulLength);
    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : DHCPS_FreeNode
 功能描述  :释放 指定内存
 输入参数  : 无
 输出参数  : 无
 返 回 值  : ULONG
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月25日
    作    者   : guolixian 00171003
    修改内容   : 新生成函数
*****************************************************************************/
VOID DHCPS_FreeNode(UCHAR **ppucNode)
{

    if(NULL != *ppucNode)
    {
        DHCP_Free(DHCPS_HANDLE, *ppucNode);
        *ppucNode = NULL;
    }
    return;
}


/*****************************************************************************
 函 数 名  : DHCPS_InitRecvBuff
 功能描述  : dhcps初始化接收消息缓存，避免频繁申请释放内存
 输入参数  : 无
 输出参数  : 无
 返 回 值  : ULONG
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月28日
    作    者   : guolixian 00171003
    修改内容   : 新生成函数
*****************************************************************************/
ULONG DHCPS_InitRecvBuff()
{
    UCHAR *pucBuf = NULL;

    /* 申请发送消息的缓冲区空间*/
    pucBuf = (UCHAR *) DHCP_Malloc(DHCPS_HANDLE, DHCPS_RECV_MSG_MAXLEN);
    if( NULL == pucBuf)
    {
        VOS_Assert(0);
        return VOS_ERR;
    }
    DHCP_MemZero(pucBuf, DHCPS_RECV_MSG_MAXLEN);
    g_pucDHCPSRecvMsgBuff = pucBuf;
    return VOS_OK;
}



/*****************************************************************************
 函 数 名  : DHCPS_InitDHCPMsgDelayBuff
 功能描述  : 消息缓存起来，delay用
 输入参数  : 无
 输出参数  : 无
 返 回 值  : ULONG
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月28日
    作    者   : guolixian 00171003
    修改内容   : 新生成函数
*****************************************************************************/
ULONG DHCPS_InitDHCPMsgDelayBuff()
{
    g_pstDHCPMsgBuffList = (DHCPS_MSG_BUFFLIST_HEAD *) DHCP_Malloc(DHCPS_HANDLE, sizeof(DHCPS_MSG_BUFFLIST_HEAD));
    if( NULL == g_pstDHCPMsgBuffList)
    {
        VOS_Assert(0);
        return VOS_ERR;
    }
    DHCP_MemZero(g_pstDHCPMsgBuffList, sizeof(DHCPS_MSG_BUFFLIST_HEAD));

    g_pstDHCPMsgBuffList->ulNodeNum = 0;
    g_pstDHCPMsgBuffList->stFistNode.pPre = NULL;
    g_pstDHCPMsgBuffList->stFistNode.pNext = &(g_pstDHCPMsgBuffList->stEndNode);
    g_pstDHCPMsgBuffList->stFistNode.pucMsgData = NULL;
    g_pstDHCPMsgBuffList->stFistNode.ulMsgLen = 0;
    g_pstDHCPMsgBuffList->stFistNode.ulPdnIndex = VOS_NULL_DWORD;
    g_pstDHCPMsgBuffList->stEndNode.pNext = NULL;
    g_pstDHCPMsgBuffList->stEndNode.pPre = &(g_pstDHCPMsgBuffList->stFistNode);
    g_pstDHCPMsgBuffList->stEndNode.pucMsgData = NULL;
    g_pstDHCPMsgBuffList->stEndNode.ulMsgLen = 0;
    g_pstDHCPMsgBuffList->stEndNode.ulPdnIndex = VOS_NULL_DWORD;

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : DHCPS_GetMbufData
 功能描述  : dhcps从mbuf中获取数据
 输入参数  : VOID
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月28日
    作    者   : g00171003
    修改内容   : 新生成函数
*****************************************************************************/
ULONG DHCPS_GetMbufData(PMBUF_S* pstMsgBuf, UCHAR **ppMsg, ULONG *pulMsgLen)
{
    ULONG ulMsgLen = 0;

    if (NULL == pstMsgBuf)
    {
        return VOS_ERR;
    }


    /*获取报文长度和地址*/
    ulMsgLen = PMBUF_GET_TOTAL_DATA_LENGTH(pstMsgBuf);
    if (DHCPS_RECV_MSG_MAXLEN < ulMsgLen)
    {
        return VOS_ERR;
    }

    *pulMsgLen = ulMsgLen;
    DHCP_MemZero(g_pucDHCPSRecvMsgBuff, DHCPS_RECV_MSG_MAXLEN);

    /* 没有分片 BLOCK_NUMBER为 1 */
    if (1 == PMBUF_GET_DATA_BLOCK_NUMBER(pstMsgBuf))
    {
        *ppMsg = PMBUF_MTOD(pstMsgBuf, UCHAR*);
    }
    else
    {
        /* 有分片，需要复制到连续内存 , 将MBUF内容复制到本地连续内存中 */
        if (VOS_OK != PMBUF_CopyDataFromPMBufToBuffer(pstMsgBuf, 0, ulMsgLen, g_pucDHCPSRecvMsgBuff))
        {
            return VOS_ERR;
        }
        *ppMsg = g_pucDHCPSRecvMsgBuff;
    }

    return VOS_OK;
}



/*****************************************************************************
 函 数 名  : DHCPS_ProcPfMsg
 功能描述  : 处理PF上送的dhcp信令
 输入参数  : VOID* pMsg
 输出参数  : 无
 返 回 值  : ULONG
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月23日
    作    者   : guolixian 00171003
    修改内容   : 新生成函数

*****************************************************************************/
VOID DHCPS_ProcPfMsg(PMBUF_S *pstMsgBuf)
{
    ULONG ulMsgLen = 0;
    ULONG ulRet = VOS_OK;
    UCHAR *pucMsg = NULL;

    if ( NULL == pstMsgBuf )
    {
        VOS_Assert(0);
        return;
    }

    /*获取数据地址和长度*/
    ulRet = DHCPS_GetMbufData(pstMsgBuf, &pucMsg, &ulMsgLen);
    if (VOS_OK != ulRet)
    {
        return;
    }

    ulRet = DHCPS_DPEDhcpMsgProc(pucMsg, ulMsgLen);
    if (VOS_OK != ulRet)
    {
        DHCPS_InternalBranchCounter(DHCPS_INTERNAL_BRANCH_319);
    }

    return;
}




/*****************************************************************************
 函 数 名  : DHCPS_LocalMemInit
 功能描述  : dhcpc本地内存初始化
 输入参数  : 无
 输出参数  : 无
 返 回 值  : ULONG
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年5月14日
    作    者   : y00138047
    修改内容   : 新生成函数

*****************************************************************************/
ULONG DHCPS_LocalMemInit()
{
    USHORT i = 0;
    ULONG ulRet = VOS_OK;

    g_ulDhcpStatisc = DHCP_Malloc(DHCPS_HANDLE, sizeof(ULONG) * DHCPS_MAX_STATISC);
    if(NULL == g_ulDhcpStatisc )
    {
        return VOS_ERR;
    }
    PGP_MemZero(g_ulDhcpStatisc,  sizeof(ULONG) * DHCPS_MAX_STATISC);

    g_pstDhcpSLease = (DHCPS_LEASE_S *)DHCP_Malloc(DHCPS_HANDLE, sizeof(DHCPS_LEASE_S)*(SDB_MAX_CONTEXT_NUM+1));
    if(NULL == g_pstDhcpSLease)
    {
        return VOS_ERR;
    }
    PGP_MemZero(g_pstDhcpSLease, sizeof(DHCPS_LEASE_S)*(SDB_MAX_CONTEXT_NUM+1));

    g_pstOption = (DHCPS_CFG_OPTION_S *)DHCP_Malloc(DHCPS_HANDLE, sizeof(DHCPS_CFG_OPTION_S) * 256);
    if(NULL == g_pstOption)
    {
        return VOS_ERR;
    }
    PGP_MemZero(g_pstOption, sizeof(DHCPS_CFG_OPTION_S)*256);

    /*调试数据初始化*/
    VOS_MemSet((VOID *)g_aulDHCPSDbgCnt,0,
                           (sizeof(ULONG) * DHCPS_MAX_FAILURE_COUNTER));

    g_pstExpiredInfor = ( DHCPS_EXPIRED_REC_S * )DHCP_Malloc(DHCPS_HANDLE, sizeof( DHCPS_EXPIRED_REC_S )*( MAX_APN_NUM+1 ) );
    if ( NULL == g_pstExpiredInfor )
    {
        DHCPS_DebugPrint(PTM_LOG_INFO, " DHCPS_InitCDBConfig: g_astExpiredInfor Error" );
        return VOS_ERR;
    }

    PGP_MemZero( g_pstExpiredInfor, sizeof( DHCPS_EXPIRED_REC_S )*( MAX_APN_NUM+1 ) );

    for ( i = 0;i <= MAX_APN_NUM;i++)
    {
        g_pstExpiredInfor[i].usApnIndex = i;
        g_pstExpiredInfor[i].usDay  = 1;
        g_pstExpiredInfor[i].ucHour = 0;
        g_pstExpiredInfor[i].ucMinute = 0;
        g_pstExpiredInfor[i].usUnlimited = 0;
    }

    g_ppstStateTimerList = (DHCPS_TIMER_LINKLIST_S**)DHCP_Malloc(DHCPS_HANDLE, sizeof(DHCPS_TIMER_LINKLIST_S*) * DHCPS_MAX_STATE_TIMER_LINKLIST);
    if (NULL == g_ppstStateTimerList)
    {
        return VOS_ERR;
    }
    PGP_MemZero((VOID*)g_ppstStateTimerList, sizeof(DHCPS_TIMER_LINKLIST_S*) * DHCPS_MAX_STATE_TIMER_LINKLIST);

    g_ppstLeaseTimerList = (DHCPS_TIMER_LINKLIST_S**)DHCP_Malloc(DHCPS_HANDLE, sizeof(DHCPS_TIMER_LINKLIST_S*) * DHCPS_MAX_LEASE_TIMER_LINKLIST);
    if (NULL == g_ppstLeaseTimerList)
    {
        return VOS_ERR;
    }
    PGP_MemZero((VOID*)g_ppstLeaseTimerList, sizeof(DHCPS_TIMER_LINKLIST_S*) * DHCPS_MAX_LEASE_TIMER_LINKLIST);

    g_pstLeaseTimer = DHCP_Malloc(DHCPS_HANDLE, sizeof(DHCPS_TIMER_LINKLIST_S)*(SDB_MAX_CONTEXT_NUM+1));
    if(NULL == g_pstLeaseTimer)
    {
        return VOS_ERR;
    }
    PGP_MemZero(g_pstLeaseTimer, sizeof(DHCPS_TIMER_LINKLIST_S)*(SDB_MAX_CONTEXT_NUM+1));

    g_pstStateTimer = DHCP_Malloc(DHCPS_HANDLE, sizeof(DHCPS_TIMER_LINKLIST_S)*(SDB_MAX_CONTEXT_NUM+1));
    if(NULL == g_pstStateTimer)
    {
        return VOS_ERR;
    }
    PGP_MemZero(g_pstStateTimer, sizeof(DHCPS_TIMER_LINKLIST_S)*(SDB_MAX_CONTEXT_NUM+1));


    ulRet = DHCPS_InitRecvBuff();
    if(VOS_OK != ulRet)
    {
        return ulRet;
    }

    ulRet = DHCPS_InitDHCPMsgDelayBuff();
    if(VOS_OK != ulRet)
    {
        return ulRet;
    }
    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : DHCPS_GetOtherCompInfo
 功能描述  : DHCPV4S获取其它组件的CSI
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年7月3日
    作    者   : y00138047
    修改内容   : 新生成函数

*****************************************************************************/
VOID DHCPS_GetOtherCompInfo()
{
    g_ullDhcpv4sUsmCsi = PSM_Inf_GetCSIBySGIDCmpTypeAndCmpInstId(DHCPS_SELF_SGID,
                                                                 E_COMP_TYPE_USM,
                                                                 DHCPS_SELF_CMPIDX_INSG);
    return;
}

/*****************************************************************************
 函 数 名  : DHCPS_CommInit1
 功能描述  : 第二阶段公共初始化
 输入参数  :
 输出参数  : 无
 返 回 值  : ULONG
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年5月14日
    作    者   : y00138047
    修改内容   : 新生成函数

*****************************************************************************/
ULONG DHCPS_CommInit1(  )
{
    ULONG ulReturn = VOS_OK;

    DBG_LogRecordReg(M_PTM_SYSTEM_NAME, "DHCP", "DHCPV4S", &g_ulDhcpv4sLogRecordRegId);

    PTM_Dbg_RegMemoryPrint(DHCPS_SELF_CSI);

    ulDhcpv4sTaskStep = 200;

    DHCPS_GetOtherCompInfo();

    ulDhcpv4sTaskStep = 300;

    /* 创建私有内存 */
    ulReturn = DHCPS_LocalMemInit();
    if (VOS_OK != ulReturn)
    {
        DHCPS_DebugPrint(PTM_LOG_ERR, " DHCPS_LocalMemInit fail" );
        return ulReturn;
    }

    ulDhcpv4sTaskStep = 400;

    ulReturn = IPC_RPC_Register(MID_DHCPS, DHCPS_IpcCallback);
    if ( VOS_OK != ulReturn )
    {
        DHCPS_DebugPrint(PTM_LOG_ERR, " DHCPS_Init: IPC_Create Failed!~!!" );
        return ulReturn;
    }

    ulDhcpv4sTaskStep = 500;

    DHCPV4S_DebugCmdInit(DHCPS_SELF_CSI);

    DHCPS_FSM_Register();

    ulDhcpv4sTaskStep = 1800;

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : DHCPS_CommInit2
 功能描述  : 第二阶段公共初始化
 输入参数  :
 输出参数  : 无
 返 回 值  : ULONG
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年5月14日
    作    者   : y00138047
    修改内容   : 新生成函数

*****************************************************************************/
ULONG DHCPS_CommInit2(  )
{
    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : DHCPS_CommInit3
 功能描述  : 第三阶段公共初始化
 输入参数  :
 输出参数  : 无
 返 回 值  : ULONG
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年5月14日
    作    者   : y00138047
    修改内容   : 新生成函数

*****************************************************************************/
ULONG DHCPS_CommInit3( )
{
    ULONG ulReturn = 0;

    ulDhcpv4sTaskStep = 4100;

#ifndef PRODUCT_TYPE_HSGW

    DHCPS_V4_CallBackReg();

    /* 配置初始化 */
    DHCPS_GetConfig();

    ulDhcpv4sTaskStep = 4200;

    /* 初始化性能统计 */
    ulReturn = DHCPS_OmInitial();
    if (VOS_OK != ulReturn)
    {
        DHCPS_DebugPrint(PTM_LOG_ERR, "DHCPS_OmInitial fail" );
        /* 不可返回失败 */
    }
#endif
    ulDhcpv4sTaskStep = 6100;

    return VOS_OK;
}


#define __DHCPS_COMP_MSG_PROC___________

ULONG DHCPS_StartWorkProc( )
{
    ULONG ulReturn = VOS_OK;

    ulReturn = DHCPS_Tmr_Init();
    if ( VOS_OK != ulReturn )
    {
        return ulReturn;
    }

    ulReturn = DHCPS_RegLogCnt();
    if (VOS_OK != ulReturn)
    {
        DHCPS_DebugPrint(PTM_LOG_ERR, "call DHCPS_RegLogCnt fail! ulReturn=%u", ulReturn);
    }

    ulDhcpv4sTaskStep = 6200;

    return VOS_OK;
}


VOID DHCPS_ProcSelfMsg(VOID* pMsg)
{
    DHCPS_INNER_MSG_S *pstInnerMsg = NULL;

    if ( NULL == pMsg )
    {
        VOS_Assert(0);
        return;
    }

    pstInnerMsg = (DHCPS_INNER_MSG_S *)pMsg;

    switch ( pstInnerMsg->ulMsgCode )
    {
        case DHCPS_INNER_LEASE_TIMEOUT :
            DHCPS_LeaseTimerMsgProc();
            break;

        case DHCPS_INNER_STATE_TIMEOUT :
            DHCPS_StateTimerMsgProc();
            break;

        default:
            VOS_Assert(0);
            break;
    }

    return;
}

#ifdef __LINUX_PLATFORM__

/*****************************************************************************
 函 数 名  : DHCPS_GetSelfCompInfo
 功能描述  : 获取本组件相关信息
 输入参数  : DMS_COMMID_T myCSI
 输出参数  : 无
 返 回 值  : ULONG
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年5月14日
    作    者   : y00138047
    修改内容   : 新生成函数

*****************************************************************************/
ULONG DHCPS_GetSelfCompInfo(DMS_COMMID_T myCSI )
{
    g_stDhcpv4sComInfo.ullSelfCsi = PSM_Inf_GetSelfCSI(E_COMP_TYPE_DSV4);
    g_stDhcpv4sComInfo.ullSelfSgId = PSM_Inf_GetSelfSGID();

    g_stDhcpv4sComInfo.ulSelfCmpIdx = PSM_Inf_GetCmpIndexInOSByCSI(g_stDhcpv4sComInfo.ullSelfCsi);
    g_stDhcpv4sComInfo.ulSelfCmpIdxInSG = PSM_Inf_GetCmpSameTIndexInSGByCSI(g_stDhcpv4sComInfo.ullSelfCsi);

    (VOID)VOS_HandleInitialize("mid_dhcps", &g_stDhcpv4sComInfo.ulHandle);

    return VOS_OK;
}


VOID DHCPS_ScheduleInit( DMS_COMMID_T ullCpi )
{
    ULONG i = 0;
    ULONG ulReturn = VOS_OK;
    COMP_MSGSTM_ATTR_S astMsgQueAttr[DHCPS_MSG_TYPE_BULT] = {0};
    ULONG aulScheduleTlb[DHCPS_MSG_TYPE_BULT] = { 0 };
    ULONG ulNum = 0;

    /* 初始化每个队列的流控深度 */
    aulScheduleTlb[DHCPS_MSG_TYPE_PF]        = 50;
    aulScheduleTlb[DHCPS_MSG_TYPE_USM]         = 50;
    aulScheduleTlb[DHCPS_MSG_TYPE_TIMER]         = 50;
    aulScheduleTlb[DHCPS_MSG_TYPE_SELF]         = 2;

    for (i = DHCPS_MSG_TYPE_PF; i < DHCPS_MSG_TYPE_BULT; i++)
    {
        if ( 0 == aulScheduleTlb[i] )
        {
            continue;
        }

        astMsgQueAttr[ulNum].uiMsgNum = aulScheduleTlb[i];
        astMsgQueAttr[ulNum].uiStreamId = i;
        astMsgQueAttr[ulNum].uiFcmQue = 0;
        astMsgQueAttr[ulNum].uiMaxAppMsgNum = DHCPV4S_DEFAULT_MAX_APP_MSG_NUM;
        ulNum++;
    }

    ulReturn = (ULONG)PGP_ScmCompMsgStmAttribSet(ullCpi, ulNum, astMsgQueAttr);
    if (VOS_OK != ulReturn)
    {
        DHCPS_DebugPrint(PTM_LOG_ERR, "\r\n PGP_ScmCompMsgStmAttribSet fail, Ret = %u", ulReturn);
    }

    return;
}


/*****************************************************************************
 函 数 名  : DHCPS_CompInitPhase1
 功能描述  : 组件第一阶段初始化
 输入参数  : DMS_COMMID_T myCSI
 输出参数  : 无
 返 回 值  : ULONG
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年5月14日
    作    者   : y00138047
    修改内容   : 新生成函数

*****************************************************************************/
ULONG DHCPS_CompInitPhase1(DMS_COMMID_T myCSI)
{
    ULONG ulRet = VOS_OK;

    /* 初始化组件参数 */
    ulRet = DHCPS_GetSelfCompInfo(myCSI);
    if (VOS_OK != ulRet)
    {
        return VOS_ERR;
    }

    ulRet = DHCPS_CommInit1();
    if (VOS_OK != ulRet)
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : DHCPS_CompInitPhase2
 功能描述  : 组件第二阶段初始化
 输入参数  : 无
 输出参数  : 无
 返 回 值  : ULONG
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年5月14日
    作    者   : y00138047
    修改内容   : 新生成函数

*****************************************************************************/
ULONG DHCPS_CompInitPhase2()
{
    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : DHCPS_CompInitPhase3
 功能描述  : 组件第三阶段初始化
 输入参数  : 无
 输出参数  : 无
 返 回 值  : ULONG
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年5月14日
    作    者   : y00138047
    修改内容   : 新生成函数

*****************************************************************************/
ULONG DHCPS_CompInitPhase3(DMS_COMMID_T myCPI)
{
    ULONG ulRet = VOS_OK;

    ulRet = DHCPS_CommInit3();
    if (VOS_OK != ulRet)
    {
        return VOS_ERR;
    }

    /* 注册流控初始化函数*/
    DHCPS_ScheduleInit(myCPI);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : DHCPS_CompMsgDistribute
 功能描述  : 组件消息分发函数
 输入参数  : VOID* pMsg
 输出参数  : 无
 返 回 值  : ULONG
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年5月14日
    作    者   : y00138047
    修改内容   : 新生成函数

*****************************************************************************/
ULONG DHCPS_CompMsgDistribute(ULONG ulMsgType, VOID* pMsg )
{
    switch(ulMsgType)
    {
        case DHCPS_MSG_TYPE_PF:
        {
            DHCPS_ProcPfMsg(pMsg);

            /* MBUF需要组件自己释放 */
            (VOID)PMBUF_Destroy((PMBUF_S *)pMsg);
            break;
        }
        case DHCPS_MSG_TYPE_USM:
        {
            DHCPS_FSM_PreMsgFromUSM(pMsg);

            break;
        }
        case DHCPS_MSG_TYPE_SELF:
        {
            DHCPS_ProcSelfMsg(pMsg);

            break;
        }
        default:
        {
            break;
        }
    }

    return VOS_OK;
}

#define __DHCPS_COMP_FRAME____________
/*****************************************************************************
 函 数 名  : DHCPS_CompConstruct
 功能描述  : DHCPC组件构造函数
 输入参数  : RTF_COMP_CONSTRUCT_STAGE_E eConstructStage
             DMS_COMMID_T myCSI
             DMS_COMMID_T myCPI
             VOID* pThis
 输出参数  : 无
 返 回 值  : ULONG
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年5月14日
    作    者   : y00138047
    修改内容   : 新生成函数

*****************************************************************************/
ULONG DHCPS_CompConstruct( RTF_COMP_CONSTRUCT_STAGE_E eConstructStage,
                            DMS_COMMID_T myCSI, DMS_COMMID_T myCPI, VOID* pThis )
{
    ULONG ulRet = 0;

    switch (eConstructStage)
    {
        case RTF_COMP_CONSTRUCT_STAGE1:
            /* 第一阶段*/
            /* 初始化组件信息(self csi, handle) */
            /* 本地内存初始化 */
            /* 共享内存/共享锁初始化, 包括SG内和SG间 */
            /* 队列初始化 */
            /* 调试命令/调试相关内存初始化 */
            /* CRM /INST/ HAA /DVM /RMM回调函数注册 */

            /* 先创建组件LOCAL区 */
            ulRet = PGP_CompConstruct(myCSI, myCPI, &pThis);
            if (VOS_OK != ulRet)
            {
                return ulRet;
            }

            ulRet = DHCPS_CompInitPhase1( myCSI );
            break;

        case RTF_COMP_CONSTRUCT_STAGE2:
            /* 第二阶段 PGPReady*/
            /* CDB配置、License、软参 */
            /* RDB 相关的业务初始化（包括内存，IFA 接口获取，逻辑部署） */
            ulRet = DHCPS_CompInitPhase2( );
            break;

        case RTF_COMP_CONSTRUCT_STAGE3:
            /* 第三阶段: 组件enable, 向平台回Confirm */
            /* Timer初始化 */
            ulRet = DHCPS_CompInitPhase3( myCPI);
            break;

        default:
            /*错误处理*/
            ulRet = VOS_ERR;
            break;
    }

    vos_printf("DHCPS_CompConstruct stage %u, ret %u", eConstructStage, ulRet);

    return ulRet;
}

/*****************************************************************************
 函 数 名  : DHCPS_CompDestruct
 功能描述  : DHCPC组件析构函数
 输入参数  : DMS_COMMID_T myPid
             VOID* pThis
 输出参数  : 无
 返 回 值  : ULONG
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年5月14日
    作    者   : y00138047
    修改内容   : 新生成函数

*****************************************************************************/
ULONG DHCPS_CompDestruct( DMS_COMMID_T myPid, VOID* pThis )
{
    vos_printf("Destruct Component DHCPS\r\n");
    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : DHCPS_CompMsgProc
 功能描述  : DHCPC组件消息处理函数
 输入参数  : VOID* pMsg
             VOID* pThis
 输出参数  : 无
 返 回 值  : ULONG
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年5月14日
    作    者   : y00138047
    修改内容   : 新生成函数

*****************************************************************************/
ULONG DHCPS_CompMsgProc(VOID* pMsg, VOID* pThis)
{
    DMS_IID_T recvIId;
    ULONG ulRet = VOS_OK;
    VOID *pMsgBody = NULL;
    ULONG ulMsgType = 0;

    if( NULL == pMsg )
    {
        return VOS_ERR;
    }

    /* 开工消息处理 */
    if ((INTF_SSP == VRP_MSG_GET_INTF_ID(pMsg))
        && (SSP_SUB_INTF_HA == VRP_MSG_GET_SUBINTF_ID(pMsg))
        && (MSG_HA_START_WORK == VRP_MSG_GET_TYPE(pMsg)))
    {
         ulRet = DHCPS_StartWorkProc();
         if (VOS_OK == ulRet)
         {
            (VOID)HAF_SendStartWorkRsp(((COMP_LOCAL_COMMON_S*)pThis)->selfDopraCpi, VOS_OK);
         }

         return VOS_OK;
    }

    /* 定时器消息处理*/
    recvIId = DMS_MSG_RECV_IID_GET(pMsg);
    if( VOS_IID_TMR_TIMEOUT == recvIId )
    {
        /* 调用平台封装的定时器处理函数，里面会调业务注册的回调函数 */
        PGP_CompRelTimeoutProc((VOS_MSG_TMR_RELTMR_S*)pMsg);
        return VOS_OK;
    }

    /* 获取DMSQ消息体 */
    pMsgBody = PGP_CompGetMsgBody(pMsg) ;

    ulMsgType = DMS_MSG_STREAMID_GET(pMsg);
    if ( ulMsgType < M_PS_MSG_TYPE_BASE ) /*队列是PGP队列*/
    {
        /* 平台消息处理*/
        (VOID)PGP_CompMsgProc(pMsgBody);
    }
    else
    {
        ulDhcpv4sTaskStep= 7000;
        /* 其它队列消息分发处理 */
        ulRet = DHCPS_CompMsgDistribute(ulMsgType, pMsgBody);
    }

    /* 平台消息释放处理*/
    PGP_CompMsgRelease();

    return ulRet;
}

#endif

