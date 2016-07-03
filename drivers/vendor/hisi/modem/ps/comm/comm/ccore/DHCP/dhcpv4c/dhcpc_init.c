
#include "dhcp_inc.h"
#include "dhcpc_def.h"
#include "dhcpc.h"
#include "dhcpc_cdb.h"
#include "dhcpc_func.h"
#include "dhcpc_table.h"
#include "dhcpc_var.h"
#include "dhcpc_comp.h"
#include "dhcpc_dbg.h"

RELTMR_T g_ulDhcpcDftTimerID = 0;
RELTMR_T g_ulFreeDhcpcCtrlBlkMemTimerId = 0;



VOID DHCPC_CtrlBlockAgingTimerOut( VOID* pvArg )
{
    DHCPC_SendSelfPdpCheckMsg(1);
    return;
}




VOID DHCPC_DftSendCtrlBlockTimerOut()
{
    ULONG    i = 0;
    ULONG ulNum = 0;

    for ( i = 0; i < DHCPC_MAX_CTRLBLKNUM; i++ )
    {
        if ( DHCPC_CTRLBLK_IDLE == g_pstDhcpCtrlBlkNodeArr[i].ucOccupiedFlg )
        {
            ulNum++;
        }
    }

    *g_DFT_pulDHCPSendCBNum = ulNum;
    return;
}


ULONG DHCPC_Tmr_Init( VOID )
{
    if ( PGP_Timer_Create( DHCPC_SELF_CSI,
                           DHCPC_MSG_TYPE_TIMER,
                           DHCPC_RENEW_TIMER_LENGTH,/*10s*/
                           ( VOID ( * )( VOID * ) )DHCPC_TimerOut,
                           &g_ulTimerRenewType,
                           &g_ulDhcpcRenewTimerID,
                           VOS_TIMER_LOOP ) )
    {
        VOS_Assert( 0 );
        return VOS_ERR;
    }

    if ( PGP_Timer_Create( DHCPC_SELF_CSI,
                           DHCPC_MSG_TYPE_TIMER,
                           DHCPC_RETRANS_TIMER_LENGTH,/*0.1s*/
                           ( VOID ( * )( VOID * ) )DHCPC_TimerOut,
                           &g_ulTimerRetransType,
                           &g_ulDhcpcRetransTimerID,
                           VOS_TIMER_LOOP ) )
    {
        VOS_Assert( 0 );
        return VOS_ERR;
    }

    /*创建dhcp控制块老化定时器*/
    if ( PGP_Timer_Create( DHCPC_SELF_CSI,
                           DHCPC_MSG_TYPE_TIMER,
                           DHCPC_CTRL_BLOCK_AGING_TIMER_INTERVAL,
                           ( VOID ( * )( VOID * ) )DHCPC_CtrlBlockAgingTimerOut,
                           NULL,
                           &g_ulDhcpcCtrlBlockAgingTimerID,
                           VOS_TIMER_LOOP ) )
    {
        VOS_Assert( 0 );
        return VOS_ERR;
    }

    /*创建dft 上报 dhcp发送控制块定时器*/
    if ( PGP_Timer_Create( DHCPC_SELF_CSI,
                           DHCPC_MSG_TYPE_TIMER,
                           DHCPC_DFTCB_TIMER_INTERVAL,
                           ( VOID ( * )( VOID * ) )DHCPC_DftSendCtrlBlockTimerOut,
                           NULL,
                           &g_ulDhcpcDftTimerID,
                           VOS_TIMER_LOOP ) )
    {
        VOS_Assert( 0 );
        return VOS_ERR;
    }

    if ( PGP_Timer_Create( DHCPC_SELF_CSI,
                           DHCPC_MSG_TYPE_TIMER,
                           DHCPC_FREE_SCAN_TIMER_LENGTH,
                           ( VOID ( * )( VOID * ) )DHCPC_FreeDhcpcCtrlBlkMem,
                           NULL,
                           &g_ulFreeDhcpcCtrlBlkMemTimerId,
                           VOS_TIMER_LOOP ) )
    {
        VOS_Assert( 0 );
        return VOS_ERR;
    }

    /* 启动小时链表扫描处理定时器 */
    if (PGP_Timer_Create(DHCPC_SELF_CSI,
                            DHCPC_MSG_TYPE_TIMER,
                            DHCPC_MILLSECONDS_PER_SECOND, /* 1秒 */
                            (VOID (*)(VOID *))DHCPC_HourListTimerOut,
                            NULL,
                            &g_ulDHCPCHourTimerId,
                            VOS_TIMER_LOOP))
    {
        VOS_Assert( 0 );
        return VOS_ERR;
    }

    /* 启动秒级链表扫描处理定时器 */
    if (PGP_Timer_Create(DHCPC_SELF_CSI,
                            DHCPC_MSG_TYPE_TIMER,
                            DHCPC_SECOND_TIMER_INTERVAL, /* 200毫秒 */
                            (VOID (*)(VOID *))DHCPC_SecondListTimerOut,
                            NULL,
                            &g_ulDHCPCSecondTimerId,
                            VOS_TIMER_LOOP))
    {
        VOS_Assert( 0 );
        return VOS_ERR;
    }

    if (PGP_Timer_Create(DHCPC_SELF_CSI,
                           DHCPC_MSG_TYPE_TIMER,
                           DHCPC_AGEING_SEQNUM_TIMER_LENGTH,
                           (VOID (*)(VOID *))DHCPV6C_AgeingSeqNum,
                           NULL,
                           &g_ulDhcpcSeqnumAgingTimerID,
                           VOS_TIMER_LOOP))
    {
        VOS_Assert(0);
        return VOS_ERR;
    }

    return VOS_OK;
}

