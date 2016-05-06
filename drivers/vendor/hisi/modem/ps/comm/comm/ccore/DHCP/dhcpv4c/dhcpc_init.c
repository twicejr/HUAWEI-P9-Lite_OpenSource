/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : dhcpc_init.c
  版 本 号   : 初稿
  作    者   : yuqingping(25027)
  生成日期   : 2002年11月21日
  最近修改   :
  功能描述   : dhcpc模块的任务初始化处理
  函数列表   :
  修改历史   :
  1.日    期   : 2002年11月21日
    作    者   : yuqingping(25027)
    修改内容   : 创建文件

******************************************************************************/
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


/*****************************************************************************
 函 数 名  : DHCPC_CtrlBlockAgingTimerOut
 功能描述  : dhcp控制块老化定时器超时处理
 输入参数  : VOID
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年02月08日
    作    者   : jiahuidong
    修改内容   : 新生成函数

*****************************************************************************/
VOID DHCPC_CtrlBlockAgingTimerOut( VOID* pvArg )
{
    DHCPC_SendSelfPdpCheckMsg(1);
    return;
}



/*****************************************************************************
 函 数 名  : DHCPC_DftSendCtrlBlockTimerOut
 功能描述  : dhcp dft上报发送控制块定时器
 输入参数  : VOID
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年02月08日
    作    者   : jiahuidong
    修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : DHCPC_Tmr_Init
 功能描述  :DHCPC模块创建定时器
 输入参数  :
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :
 修改历史       :
  1.日      期   : 2009年07月04日
    作      者   : jiahuidong00142544
    修改内容   : 新生成函数
*****************************************************************************/
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

    /* BEGIN: Added for PN:DHCPv6特性 by tianyang 00144555, 2012/7/23 */
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
    /* END:   Added for PN:DHCPv6特性 by tianyang 00144555, 2012/7/23 */

    /* zhangjinquan 00175135 DHCPv6特性 2012-07-23 start */
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
    /* zhangjinquan 00175135 DHCPv6特性 2012-07-23 end   */

    /* Added start by y00170683 at 2012-09-10 UGW10.0---SEQNUM老化处理---DS.UGWV9R10C0.DHCPv6.DHCP.0024支持TID使用情况的维护 */
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
    /* Added end by y00170683 at 2012-09-10 UGW10.0---SEQNUM老化处理---DS.UGWV9R10C0.DHCPv6.DHCP.0024支持TID使用情况的维护 */

    return VOS_OK;
}

