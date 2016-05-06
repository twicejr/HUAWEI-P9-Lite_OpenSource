/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

******************************************************************************
  文   件  名: DhcpC.c
  版   本  号: 初稿
  作       者: j00142544
  生成日期   : 2009-07-27
  最近修改   :
  功能描述   : DHCP Client模块的处理函数，负责对dhcp控制块的管理，地址的续租，
               消息的接收以及发送处理
  函数列表   :
  修改历史   :
  1、日   期 : 2007-07-27
  作   者    : j00142544
    修改内容 : 创建文件
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
#if 0
#include "dhcpm_interface.h"
#endif
#include "dhcpv6c_fsm.h"

RELTMR_T g_ulDhcpcBoardStateChgDelayTimerId = 0;

#define DHCPM_MAX_REQUEST_TIMEOUT_NUM 5
extern DHCP_SERVER_STATUS_S *g_pstDhcpServerStatus;

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID          PS_FILE_ID_DHCPC_C
/*lint +e767*/

/*****************************************************************************
 函 数 名  : DHCPC_RenewTimeOut
 功能描述  : 地址续租定时器超时的处理函数，扫描所有dhcp控制块，完成地址的续租处理
 输入参数  : void
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年6月7日
    作    者   : heguangwei 65937
    修改内容   : 新生成函数

*****************************************************************************/
VOID DHCPC_RenewTimeOut( VOID )
{
    ULONG i = 0;
    ULONG ulRetTimeInSec = 0;
    ULONG ulIpUsedTime = 0;
    UCHAR ucReSendFlg = 0;
    DHCPC_CTRLBLK    *pstDhcpcCtlBlk = NULL;
    DHCPC_CTRLBLK    *pstDhcpNewcCtlBlk = NULL;
    ULONG ulDhcpCtlCount = 0;
    UCHAR ucSCID = 0;
    ULONG ulSendRlt = VOS_OK;
    UCHAR ucByte24Value = 0;
    ULONG ulSendNum = 0;
    ULONG ulDhcpRenewNum = 0;
    ULONG ulLease = 0;
    ULONG ulT1 = 0;
    ULONG ulT2 = 0;
    ULONG ulSndLAP2RelMsgCnt = 0;
    DHCPC_CTRLBLK_NODE stDhcpcTempCtlBlkNode = {0};
    DHCPC_TEMPCTRLBLK *pstDhcpcTempCtlBlk = NULL;
    ULONG ulOldCtrlblkXaxis = 0;

    /*24号软参控制DHCP每次发送续租消息个数M_SPM_AM_DHCP_RENEW_MESSAGE_NUM*/
    if (VOS_OK != SPM_GetByteValue(M_SPM_BYTE_024, &ucByte24Value))
    {
        ucByte24Value = 0;
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_243);
    }

    /*如果没有配置24号软参，则默认每次发送60个*/
    if(0 == ucByte24Value)
    {
        ulSendNum = 60;
    }
    else
    {
        ulSendNum = ucByte24Value;
    }

    ucSCID = (UCHAR)DHCPC_SELF_CMPIDX_INSG;

    /*遍历控制块HASH链*/
    for(i = g_ulCtrlblkXaxis; i < DHCPC_CTRLBLK_HASH_TABLE_SIZE; i++)
    {
        pstDhcpcCtlBlk = ( DHCPC_CTRLBLK * )g_pstDhcpcCtrlBlkRec[i];
        ulOldCtrlblkXaxis = i;
        g_ulCtrlblkXaxis++;

        /*如果遍历完，从第一个用户重新开始*/
        if (DHCPC_CTRLBLK_HASH_TABLE_SIZE == g_ulCtrlblkXaxis)
        {
            g_ulCtrlblkXaxis = 0;
        }

        while (g_ulCtrlblkYaxis != 0)
        {
            if (NULL == pstDhcpcCtlBlk)
            {
                g_ulCtrlblkYaxis = 0;
                break;
            }
            pstDhcpcCtlBlk = pstDhcpcCtlBlk->pstNextNode;
            g_ulCtrlblkYaxis--;
        }
        for (; ;)
        {
            if (NULL == pstDhcpcCtlBlk)
            {
                g_ulCtrlblkYaxis = 0;
                break;
            }
            else
            {
                pstDhcpNewcCtlBlk = pstDhcpcCtlBlk->pstNextNode;
                /*地址重用只对已经上线的用户*/
                /*modified by z00113478 ,有时会有莫名奇妙的状态进来*/
                if ( ( DHCPC_STATE_LEASE == pstDhcpcCtlBlk->usDhcpStatus )
                     ||( DHCPC_STATE_ReNewing == pstDhcpcCtlBlk->usDhcpStatus )
                     ||( DHCPC_STATE_PreReBinding == pstDhcpcCtlBlk->usDhcpStatus )
                     ||( DHCPC_STATE_ReBinding == pstDhcpcCtlBlk->usDhcpStatus )
                     ||( DHCPC_STATE_BOUND == pstDhcpcCtlBlk->usDhcpStatus ) )
                {
                    ucReSendFlg = VRP_NO;
                    ulLease     = pstDhcpcCtlBlk->ulLease;
                    ulT1 = DHCPC_GET_T1_BY_LEASE(ulLease);
                    ulT2 = DHCPC_GET_T2_BY_LEASE(ulLease);
                    /*取秒计数 modified by z00113478 at 20080703*/
                    ( VOS_VOID )PGP_TmNowInSec( &ulRetTimeInSec );
                    /*取秒计数 modified by z00113478 at 20080703*/
                    ulIpUsedTime = ulRetTimeInSec - pstDhcpcCtlBlk->ulTimeStamp;

                    if( ulIpUsedTime*2 >= ulT2 + ulLease ) /* 15/16 lease */
                    {
                        /* BEGIN: Modified for PN: DTS2012010500634  by guolixian 00171003, 2012/1/7  这里建议直接使用局部变量。*/
                        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPC_RenewTimeOut::Notify GTPC to delete context by Ip address!%u,%u,%d,%u,%u" ,
                        ulRetTimeInSec,pstDhcpcCtlBlk->ulTimeStamp,pstDhcpcCtlBlk->usDhcpStatus,i,pstDhcpcCtlBlk->ulDHCPCtxIdx );
                        pstDhcpcTempCtlBlk = &(stDhcpcTempCtlBlkNode.stDhcpcTmpCtlBlk );
                        pstDhcpcTempCtlBlk->ulUserIpAddr = pstDhcpcCtlBlk->aulUserIpAddr[0];
                        pstDhcpcTempCtlBlk->ucUserType = pstDhcpcCtlBlk->ucUserType;
                        pstDhcpcTempCtlBlk->usPoolIndex = pstDhcpcCtlBlk->usPoolIndex;
                        pstDhcpcTempCtlBlk->ulAgetIP = pstDhcpcCtlBlk->aulAgentIpAddr[0];
                        pstDhcpcTempCtlBlk->ulPdpIndex = pstDhcpcCtlBlk->ulPDPIndex;
                        pstDhcpcTempCtlBlk->ucAddressType = LAP_IPV4;
                        pstDhcpcTempCtlBlk->usDhcpGroupIndex = pstDhcpcCtlBlk->usServerGrpIndex;
                        pstDhcpcTempCtlBlk->ucSCID = ucSCID;
                        pstDhcpcTempCtlBlk->ulSrvIp = pstDhcpcCtlBlk->aulSrvIp[0];
                        pstDhcpcTempCtlBlk->ulDHCPCtlIdx = pstDhcpcCtlBlk->ulDHCPCtxIdx;
                        pstDhcpcTempCtlBlk->aulMSISDN[0] = pstDhcpcCtlBlk->aulMSISDN[0];
                        pstDhcpcTempCtlBlk->aulMSISDN[1] = pstDhcpcCtlBlk->aulMSISDN[1];
                        pstDhcpcTempCtlBlk->usVpnId = pstDhcpcCtlBlk->usVPNIndex;
                        pstDhcpcTempCtlBlk->aulIMSI[0] = pstDhcpcCtlBlk->aulIMSI[0];
                        pstDhcpcTempCtlBlk->aulIMSI[1] = pstDhcpcCtlBlk->aulIMSI[1];
                        /* BEGIN: Added by jixiaoming for  IMEI跟踪 at 2012-8-17 */
                        pstDhcpcTempCtlBlk->aulIMEI[0] = pstDhcpcCtlBlk->aulIMEI[0];
                        pstDhcpcTempCtlBlk->aulIMEI[1] = pstDhcpcCtlBlk->aulIMEI[1];
                        /* END: Added by jixiaoming for IMEI跟踪 at 2012-8-17 */
                        pstDhcpcTempCtlBlk->ucRole = pstDhcpcCtlBlk->ucRole;
                        /* 需要将用户类型和TEIDC赋值 */
                        pstDhcpcTempCtlBlk->ucUser = pstDhcpcCtlBlk->ucUser;
                        pstDhcpcTempCtlBlk->ulTEIDC = pstDhcpcCtlBlk->ulTEIDC;
                        pstDhcpcTempCtlBlk->ucLAPNo = pstDhcpcCtlBlk->ucLAPNo;
                        pstDhcpcTempCtlBlk->ucRandomNo = pstDhcpcCtlBlk->ucRandomNo; /* 随机跟踪 DTS2012091903437 y00170683 */

                        /* 给LAP2发送消息，通知删除用户  */
                        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPC_RenewTimeOutMsg to lap%u,%d,%u!",
                        pstDhcpcTempCtlBlk->ulUserIpAddr, pstDhcpcTempCtlBlk->usPoolIndex, pstDhcpcTempCtlBlk->ulAgetIP );
                        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_204);
                        ( VOID )DHCPC_SendMsgToLAP2(&stDhcpcTempCtlBlkNode, DHCPC_SND2_LAP2_ADDR_REL_MSG );
                        /* 发送release消息 */
                        ( VOID )DHCPC_Pkt_Send( DHCP_RELEASE, pstDhcpcTempCtlBlk );

                        /* 这里应该释放dhcp控制块,临时控制块 */
                        DHCPC_FreeDhcpCtrlBlk( pstDhcpcCtlBlk->ulDHCPCtxIdx, pstDhcpcCtlBlk->ulTEIDC, pstDhcpcCtlBlk->ucUser, pstDhcpcCtlBlk->ulPDPIndex);
                        PGP_MemZero(&stDhcpcTempCtlBlkNode, sizeof(DHCPC_CTRLBLK_NODE));
                        pstDhcpcTempCtlBlk = NULL;
                        /* z00175135 DTS2012011104522 防止大量续租失败时写共享队列失败 2012-02-02 start */
                        ulSndLAP2RelMsgCnt++;
                        if ( ulSndLAP2RelMsgCnt > 150 )
                        {
                            /* 回退g_ulCtrlblkXaxis，下次超时函数时，会重新扫描该未扫描完的hash链 10.0消除阻塞操作by y00138047 */
                            g_ulCtrlblkXaxis = ulOldCtrlblkXaxis;
                            g_ulCtrlblkYaxis = 0;
                            return;
                        }
                        /* z00175135 DTS2012011104522 防止大量续租失败时写共享队列失败 2012-02-02 end   */
                    }
                    else if ( ulIpUsedTime >=  ulT2 ) /* 7/8 lease */
                    {
                        /* 根据协议规定只在1/2和1/8时间发续租消息，但由于KPN的需要，可能后续需要新增软参控制是否不断发送 */
                        if (DHCPC_STATE_ReBinding != pstDhcpcCtlBlk->usDhcpStatus)
                        {
                            DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n Rebounding-<<<pstDhcpcCtlBlk->usDhcpStatus=%d!",pstDhcpcCtlBlk->usDhcpStatus );
                            DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n -<<<ulIpUsedTime Rebounding!" );
                            pstDhcpcCtlBlk->usDhcpStatus = DHCPC_STATE_ReBinding;
                            ucReSendFlg = VRP_YES;
                            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_229);
                        }
                    }
                    else if ( ulIpUsedTime >=  ulT1 ) /* 1/2 lease */
                    {
                        /* 根据协议规定只在1/2和1/8时间发续租消息，但由于KPN的需要，可能后续需要新增软参控制是否不断发送 */
                        if (DHCPC_STATE_ReNewing != pstDhcpcCtlBlk->usDhcpStatus)
                        {
                            DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n Renewing-<<<pstDhcpcCtlBlk->usDhcpStatus=%d!",pstDhcpcCtlBlk->usDhcpStatus );
                            DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n -<<<ulIpUsedTime Renewing!" );
                            pstDhcpcCtlBlk->usDhcpStatus = DHCPC_STATE_ReNewing;
                            ucReSendFlg = VRP_YES;
                            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_230);
                        }
                    }
                    /*是否重发REQ消息*/
                    if ( VRP_YES == ucReSendFlg )
                    {
                        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPC_RenewTimeOut::Renew Ip address for context %d !", g_ulCurrDHCPCCtlIndex );
                        ulSendRlt = DHCPC_RenewIpAddr( pstDhcpcCtlBlk );
                        if(VOS_OK != ulSendRlt)
                        {
                            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_239);
                        }

                        ulDhcpRenewNum ++; /*发送续租消息个数*/
                    }
                }

                g_ulCtrlblkYaxis++;

                ulDhcpCtlCount++;
            }
            pstDhcpcCtlBlk = pstDhcpNewcCtlBlk;
        }

        /*一次遍历200个控制块或者发送ulSendNum个续租消息*/
        if(  (ulDhcpCtlCount >= 300)
          ||(ulDhcpRenewNum >= ulSendNum))
        {
            break;
        }

        if (0 ==(g_ulCtrlblkXaxis %5000) )
        {
            break;
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : DHCPC_GetValidTestTime
 功能描述  : 获取dhcp server状态探测的时间间隔
 输入参数  : 无
 输出参数  : 无
 返 回 值  : ULONG
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月24日
    作    者   : m00221593
    修改内容   : 新生成函数

*****************************************************************************/
ULONG DHCPC_GetValidTestTime()
{
    ULONG ulPrimTesttime = 0;
    UCHAR ucSoftParaByte132 = 0;

    /* 获取byte132软参的值 */
    if (VOS_OK != SPM_GetByteValue(M_SPM_DHCP_SERVER_TEST_INTERVAL, &ucSoftParaByte132))
    {
        VOS_Assert( 0 );
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_300);
        ucSoftParaByte132 = 0;
    }

    /*默认10分钟*/
    ulPrimTesttime = ((0 == ucSoftParaByte132) ?
        DHCPC_SRV_TIMER_LENGTH : ((DHCPC_SRV_TIMER_LENGTH / 10) * ucSoftParaByte132));

    return ulPrimTesttime;
}

/*****************************************************************************
 函 数 名  : DHCPC_PriPrimarySrvStatusMaintenance
 功能描述  : 主server状态维护
 输入参数  : DHCP_SERVER_STATUS_S *pstDhcpServerStatus
             ULONG ulDhcpGroupIndex
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月24日
    作    者   : m00221593
    修改内容   : 新生成函数

*****************************************************************************/
VOID DHCPC_PriPrimarySrvStatusMaintenance(DHCP_SERVER_STATUS_S *pstDhcpServerStatus, ULONG ulDhcpGroupIndex)
{
    ULONG ulRet = 0;
    if ((NULL == pstDhcpServerStatus) || (ulDhcpGroupIndex >= DHCPGRP_MAX_NUM))
    {
        return;
    }

    if (pstDhcpServerStatus->ucPrimSrvTimerStatus == DHCP_PRISRV_TIMER_DOWN)
    {
        /* z00175135 DTS2012050400560 将定时器id清零 2012-07-03 start */
        if (0 != g_aulDhcpcSrvTimerId[ulDhcpGroupIndex])
        {
            (VOID)PGP_Timer_Delete(&(g_aulDhcpcSrvTimerId[ulDhcpGroupIndex]));
        }
        /* z00175135 DTS2012050400560 将定时器id清零 2012-07-03 end   */

        if ( PGP_Timer_Create( DHCPC_SELF_CSI,
                               DHCPC_MSG_TYPE_TIMER,
                               DHCPC_GetValidTestTime(),/*使用软参设置的值*/
                               ( VOID ( * )( VOID* ) )DHCPC_SeverTimeOut,/*pclint 该回调函数使用值传递 无问题*/
                               (VOID *)(ulDhcpGroupIndex),
                               &g_aulDhcpcSrvTimerId[ulDhcpGroupIndex],
                               VOS_TIMER_NOLOOP ) )
        {
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_007);
            VOS_Assert( 0 );
        }

        ulRet = DHCPM_SetPrimSrvTimerStatusByIndex(ulDhcpGroupIndex, DHCP_PRISRV_TIMER_ON);
        if (VOS_OK != ulRet)
        {
            g_ulCurrProcIndex++;
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_269);
        }

    }
    return;
}

/*****************************************************************************
 函 数 名  : DHCPC_RetransNodeTimerOutProc
 功能描述  : 重发节点超时时的处理
 输入参数  : DHCPC_CTRLBLK_NODE *pCurrNode
 输出参数  : 无
 返 回 值  : ULONG
 调用函数  :
 被调函数  : DHCPC_RetransTimeOut

 修改历史      :
  1.日    期   : 2012年11月24日
    作    者   : m00221593
    修改内容   : 新生成函数

*****************************************************************************/
ULONG DHCPC_RetransNodeTimerOutProc(DHCPC_CTRLBLK_NODE *pCurrNode)
{
    ULONG ulDhcpGroupIndex = 0;
    ULONG ulRet= VOS_OK;
    DHCP_SERVER_STATUS_S stDhcpServerStatus = {0};
    LAP_DHCP_CFG_S stDhcpServer = {0};

    if (NULL == pCurrNode)
    {
        return VOS_ERR;
    }

    ulDhcpGroupIndex = (ULONG)((pCurrNode->stDhcpcTmpCtlBlk ).usDhcpGroupIndex);
    ulRet = DHCPM_GetDhcpSrvCfgStatusByIndex(ulDhcpGroupIndex, &stDhcpServer, &stDhcpServerStatus);
    if ( VOS_OK != ulRet )
    {
        /*当前节点不再处理，直接退出*/
        return VOS_ERR;
    }

    if (pCurrNode->stDhcpcTmpCtlBlk.ulSrvIp == stDhcpServer.aulPrimaryServerIp[0])
    {
        /*上一次在主server上发送*/
        if (DHCPC_SNDSRVSEND <= (pCurrNode->stDhcpcTmpCtlBlk ).usAlreadySendFlg)
        {
            /*已经发送三次不再重发，直接回复失败，这种情况下主备server都不在位置*/
            return VOS_ERR;
        }
        else if ((DHCPC_ALREADYRESEND == (pCurrNode->stDhcpcTmpCtlBlk.usAlreadySendFlg))
                || ((DHCPC_FIRSTSEND == (pCurrNode->stDhcpcTmpCtlBlk.usAlreadySendFlg)
                    && (DHCP_SEVER_ABNORMAL == stDhcpServerStatus.ucPrimarySrvStatus))))
        {
            (VOID)DHCPM_SetPrimarySrvStatusByIndex(ulDhcpGroupIndex, DHCP_SEVER_ABNORMAL);
            DHCPC_PriPrimarySrvStatusMaintenance(&stDhcpServerStatus, ulDhcpGroupIndex);
            if (0 == stDhcpServer.aulSecondaryServerIp[0])
            {
                /*如果备server没有配置，直接按照失败处理，不再重发*/
                DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_218);
                return VOS_ERR;
            }

            /*需要向备server再发送一次*/
            pCurrNode->stDhcpcTmpCtlBlk.ulSrvIp = stDhcpServer.aulSecondaryServerIp[0];
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_273);
            return VOS_OK;
        }

        /*还没重发过,并且server状态为normal，继续发送*/
        return VOS_OK;
    }
    else if ((pCurrNode->stDhcpcTmpCtlBlk).ulSrvIp == stDhcpServer.aulSecondaryServerIp[0])
    {
        /*上一次在备server上发送*/
        if (DHCPC_SNDSRVSEND <= ( pCurrNode->stDhcpcTmpCtlBlk ).usAlreadySendFlg)
        {
            /*已经发送三次不再重发，直接回复失败*/
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_265);
            (VOID)DHCPM_SetSecondarySrvStatusByIndex(ulDhcpGroupIndex, DHCP_SEVER_ABNORMAL);
            return VOS_ERR;
        }
        else if ((DHCPC_ALREADYRESEND == (pCurrNode->stDhcpcTmpCtlBlk).usAlreadySendFlg)
                 || (( DHCPC_FIRSTSEND == (pCurrNode->stDhcpcTmpCtlBlk).usAlreadySendFlg)
                    && (DHCP_SEVER_ABNORMAL == stDhcpServerStatus.ucSecondarySrvStatus)))
        {
            (VOID)DHCPM_SetSecondarySrvStatusByIndex(ulDhcpGroupIndex, DHCP_SEVER_ABNORMAL);

            /*需要向主server再发送一次*/
            pCurrNode->stDhcpcTmpCtlBlk.ulSrvIp = stDhcpServer.aulPrimaryServerIp[0];
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_273);
            return VOS_OK;
        }

        /*还没重发过,并且server状态为normal，继续发送*/
        return VOS_OK;
    }

    return VOS_ERR;
}

/*****************************************************************************
 函 数 名  : DHCPC_RetransTimeOut
 功能描述  : 超时重发定时器回调处理函数
 输入参数  : VOID
 输出参数  : 无
 返 回 值  :VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年12月26日
    作    者   : caopu
    修改内容   : 增加主备服务器，判断是否换服务器发送

*****************************************************************************/
VOID DHCPC_RetransTimeOut( VOID )
{
    /*遍历重发定时器链表，
     *如果需要失败处理，则向申请模块返回失败，删临时控制块，释放内存
     *否则把该节点搬移到8s以后的定时器链表去。注意步长只有0.1s
     *所有对N(s)的定时器，应该查到N*10的链表中去
     *一次性处理该链表的所有节点，不作流控。
     */

    DHCPC_CTRLBLK_NODE *pCurrNode = NULL;
    DHCPC_CTRLBLK_NODE *pstNextNode = NULL;
    ULONG ulRet = VOS_OK;
    DLL_S* pstHeadTmrNode = NULL;

    if (g_ulCurrProcIndex >= DHCPC_TMR_CIRCLE_TIME)
    {
        g_ulCurrProcIndex = 0;
    }

    /*获取当前时间槽的头节点。*/
    pstHeadTmrNode = &(g_astTimerLink[g_ulCurrProcIndex]);
    pCurrNode = (DHCPC_CTRLBLK_NODE * )DLL_First( pstHeadTmrNode);
    while (NULL != pCurrNode)
    {
        /*根据接收到的消息内容，从DHCP模块的配置中得到配置信息*/
        pstNextNode = (DHCPC_CTRLBLK_NODE *)DLL_Next(pstHeadTmrNode,(DLL_NODE_S *)pCurrNode);

        /*判断是否重发，如需重发重新获取server的ip地址*/
        ulRet = DHCPC_RetransNodeTimerOutProc(pCurrNode);
        if (VOS_OK != ulRet)
        {
            /*不需要重发，做去活处理*/
            ( VOID )DHCPC_SendMsgToLAP2(pCurrNode,DHCPC_SND2_LAP2_NO_RSP_MSG);

            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_217);

            /*将当前节点从重发链表中删除*/
            DHCPC_DelNode(g_ulCurrProcIndex,pCurrNode);

            /* 释放控制块节点 */
            DHCPC_FreeDhcpCtrlBlk(pCurrNode->stDhcpcTmpCtlBlk.ulDHCPCtlIdx, pCurrNode->stDhcpcTmpCtlBlk.ulTEIDC,
                                   pCurrNode->stDhcpcTmpCtlBlk.ucUser, pCurrNode->stDhcpcTmpCtlBlk.ulPdpIndex);

            /* 释放临时控制块节点 */
            DHCPC_FreeDhcpTmpNode(pCurrNode);
        }
        else
        {
            /*需要重发，继续向外发送消息*/
            (VOID)DHCPC_ResendMSG(pCurrNode);
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_011);

            /*重新调整当前节点在重发链表中的位置*/
            DHCPC_DelNode(g_ulCurrProcIndex,pCurrNode);
            DHCPC_InSertNodeAfterSecs(DHCPC_8_SECONDS,pCurrNode);
            DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPC_RetransTimeOut: The first time retrans time out!");
        }
        pCurrNode = pstNextNode;
    }

    g_ulCurrProcIndex++;
    if (DHCPC_TMR_CIRCLE_TIME <= g_ulCurrProcIndex)
    {
        g_ulCurrProcIndex = 0;
    }

    return;
}

/*****************************************************************************
 函 数 名  : DHCPv4C_TimerCallBack
 功能描述  : V4 V6公用定时器的DHCPv4回调处理函数，目前只作V4续租消息超时处理
 输入参数  : UCHAR ucIpType
             ULONG ulTeidc
             UCHAR ucEvent
 输出参数  : VOID
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年1月24日
    作    者   : mengyuanhui 00221593
    修改内容   : 新生成函数

*****************************************************************************/
VOID DHCPv4C_TimerCallBack(UCHAR ucIpType, ULONG ulTeidc, UCHAR ucEvent)
{
    DHCP_SERVER_STATUS_S stDhcpServerStatus = {0};
    LAP_DHCP_CFG_S stDhcpServer = {0};
    DHCPC_CTRLBLK *pstDhcpcCtlBlk = NULL;
    ULONG ulRet = VOS_OK;

    DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_321);

    ulRet = DHCPC_QueryDhcpcContext(ucIpType, ulTeidc, &pstDhcpcCtlBlk);
    if  ((VOS_OK != ulRet) || (NULL == pstDhcpcCtlBlk))
    {
        return;
    }

    if ((DHCPC_STATE_LEASE == pstDhcpcCtlBlk->usDhcpStatus)
         ||(DHCPC_STATE_ReNewing == pstDhcpcCtlBlk->usDhcpStatus)
         ||(DHCPC_STATE_PreReBinding == pstDhcpcCtlBlk->usDhcpStatus)
         ||(DHCPC_STATE_ReBinding == pstDhcpcCtlBlk->usDhcpStatus))
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_322);

        ulRet = DHCPM_GetDhcpSrvCfgStatusByIndex(pstDhcpcCtlBlk->usServerGrpIndex, &stDhcpServer, &stDhcpServerStatus);
        if ( VOS_OK != ulRet )
        {
            /*当前节点不再处理，直接退出*/
            return;
        }

        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPv4C_TimerCallBack pstDhcpcCtlBlk->aulSrvIp[0] = %u", pstDhcpcCtlBlk->aulSrvIp[0]);

        if (pstDhcpcCtlBlk->aulSrvIp[0] == stDhcpServer.aulPrimaryServerIp[0])
        {
            /* 上一次给主server发送了消息 */
            if (DHCP_SEVER_NORMAL == stDhcpServerStatus.ucPrimarySrvStatus)
            {
                g_pstDhcpServerStatus[pstDhcpcCtlBlk->usServerGrpIndex].ucPrimRequestTimeout++;
                if (g_pstDhcpServerStatus[pstDhcpcCtlBlk->usServerGrpIndex].ucPrimRequestTimeout >= DHCPM_MAX_REQUEST_TIMEOUT_NUM)
                {
                    DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_323);
                    (VOID)DHCPM_SetPrimarySrvStatusByIndex(pstDhcpcCtlBlk->usServerGrpIndex, DHCP_SEVER_ABNORMAL);
                    DHCPC_PriPrimarySrvStatusMaintenance(&stDhcpServerStatus, pstDhcpcCtlBlk->usServerGrpIndex);
                }
            }
        }
        else if (pstDhcpcCtlBlk->aulSrvIp[0] == stDhcpServer.aulSecondaryServerIp[0])
        {
            /* 上一次给备server发送了消息 */
            if (DHCP_SEVER_NORMAL == stDhcpServerStatus.ucSecondarySrvStatus)
            {
                g_pstDhcpServerStatus[pstDhcpcCtlBlk->usServerGrpIndex].ucSecRequestTimeout++;
                if (g_pstDhcpServerStatus[pstDhcpcCtlBlk->usServerGrpIndex].ucSecRequestTimeout >= DHCPM_MAX_REQUEST_TIMEOUT_NUM)
                {
                    DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_324);
                    (VOID)DHCPM_SetSecondarySrvStatusByIndex(pstDhcpcCtlBlk->usServerGrpIndex, DHCP_SEVER_ABNORMAL);
                }
            }
        }
    }

    return;

}

/*****************************************************************************
 函 数 名  : DHCPC_TimerOut
 功能描述  : dhcp定时器超时函数
 输入参数  : VOID
 输出参数  : 无
 返 回 值  :VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年12月26日
    作    者   : caopu
    修改内容   : 增加主备服务器，判断是否换服务器发送

*****************************************************************************/
VOID DHCPC_TimerOut( VOID* pvArg )
{
    ULONG    ulTimerType = 0;
    UCHAR    ucLogicSlot = 0;

    if ( NULL == pvArg )
    {
        return ;
    }

    /* 任务初始化阶段,初始化性能统计,在这里重新初始化 */
    if (ulDhcpcPerfInitFinish != VOS_TRUE)
    {
        (VOID)DHCPC_OmInitial();
    }

    /*备板不处理*/
    ucLogicSlot = (UCHAR)CRM_GetSelfLogicSlotID();
    if (E_CRM_ACTIVE != CRM_GetSlotPrimaryInfoOfSelfGroup(ucLogicSlot))
    {
        return;
    }

    ulTimerType = *( ( ULONG* )pvArg );
    if ( g_ulTimerRenewType == ulTimerType )
    {
        /*重用定时器超时*/
        DHCPC_RenewTimeOut();
    }
    else if ( g_ulTimerRetransType == ulTimerType )
    {
        /*重发定时器超时*/
        DHCPC_RetransTimeOut();
    }

    return ;
}
/*****************************************************************************
 函 数 名  : DHCPC_SeverTimeOut
 功能描述  : 服务器状态探测定时器超时
 输入参数  : void
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年12月27日
    作    者   : caopu
    修改内容   : 新生成函数

*****************************************************************************/
VOID DHCPC_SeverTimeOut( ULONG pvArg )
{
    ULONG           ulServerIndex = 0;
    ULONG ulRet = VOS_OK;
    DHCP_SERVER_STATUS_S stDhcpServerStatus;
    LAP_DHCP_CFG_S stDhcpServer;

    if ( DHCPGRP_MAX_NUM <= pvArg )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_071);
        return ;
    }

    ulServerIndex = pvArg;

    /* z00175135 DTS2012050400560 将定时器id清零 2012-07-03 start */
    g_aulDhcpcSrvTimerId[ulServerIndex] = 0;
    /* z00175135 DTS2012050400560 将定时器id清零 2012-07-03 end   */

    ulRet = DHCPM_GetDhcpSrvCfgStatusByIndex(ulServerIndex, &stDhcpServer, &stDhcpServerStatus);
    if ( VOS_OK != ulRet )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_072);
        return ;
    }

    DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_073);

    // pstDhcpcSrvGrp->ucPrimarySrvTest = DHCP_PRISRV_TEST_ON;
    /* 修改定时器状态 使得主备切换时能够重新探测主服务器*/
    // pstDhcpcSrvGrp->ucPrimSrvTimerStatus = DHCP_PRISRV_TIMER_DOWN;

    /* z00175135 DTS2012050400560 在Server Down的情况下才启动探测 2012-07-03 start */
    /*linyufeng 001766669 DHCPv6特性 2012-07-14 start*/
    if(DHCP_SEVER_GROUP_IS_IPV6 == stDhcpServer.ucIsDHCPv6)
    {
        if ( DHCP_SEVER_ABNORMAL == stDhcpServerStatus.ucPrimarySrvStatus )
        {
            (VOID)DHCPM_SetPrimarySrvStatusByIndex(ulServerIndex, DHCP_SEVER_TRY);

        }
        if ( DHCP_SEVER_ABNORMAL == stDhcpServerStatus.ucSecondarySrvStatus )
        {
            (VOID)DHCPM_SetSecondarySrvStatusByIndex(ulServerIndex, DHCP_SEVER_TRY);
        }
    }
    else
    {
        if (DHCP_SEVER_ABNORMAL == stDhcpServerStatus.ucPrimarySrvStatus)
        {
            (VOID)DHCPM_SetPrimarySrvTestByIndex(ulServerIndex, DHCP_PRISRV_TEST_ON);

            (VOID)DHCPM_SetPrimSrvTimerStatusByIndex(ulServerIndex, DHCP_PRISRV_TIMER_DOWN);
        }
    }
    /*linyufeng 001766669 DHCPv6特性 2012-07-14 end*/
    /* z00175135 DTS2012050400560 在Server Down的情况下才启动探测 2012-07-03 end   */


    return ;
}

/*****************************************************************************
 函 数 名  : DHCPC_SetServerStatusToNormalByIndexAndIp
 功能描述  : 收到DHCP Server响应消息的时候把对应的server状态置成normal
 输入参数  : ULONG ulDhcpGroupIndex
             ULONG ulIP
 输出参数  : 无
 返 回 值  : ULONG
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年11月6日
    作    者   : m00221593
    修改内容   : 新生成函数

*****************************************************************************/
ULONG DHCPC_SetServerStatusToNormalByIndexAndIp(USHORT usDhcpGroupIndex, ULONG ulIP)
{
    DHCP_SERVER_STATUS_S stDhcpServerStatus = {0};
    LAP_DHCP_CFG_S stDhcpServer = {0};
    ULONG ulRet = VOS_OK;
    ULONG ulDhcpGroupIndex = (ULONG)usDhcpGroupIndex;

    ulRet = DHCPM_GetDhcpSrvCfgStatusByIndex(ulDhcpGroupIndex, &stDhcpServer, &stDhcpServerStatus);
    if ( VOS_OK != ulRet )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_119);
        return VOS_ERR;
    }

    if ( stDhcpServer.aulPrimaryServerIp[0] == ulIP )
    {
        ulRet = DHCPM_SetPrimarySrvStatusByIndex(ulDhcpGroupIndex, DHCP_SEVER_NORMAL);
        if ( VOS_OK != ulRet )
        {
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_263);
        }

        ulRet = DHCPM_SetPrimTimeoutNumByIndex(ulDhcpGroupIndex, 0);
        if ( VOS_OK != ulRet )
        {
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_264);
        }
    }
    else if ( stDhcpServer.aulSecondaryServerIp[0] == ulIP )
    {
        ulRet = DHCPM_SetSecondarySrvStatusByIndex(ulDhcpGroupIndex, DHCP_SEVER_NORMAL);
        if ( VOS_OK != ulRet )
        {
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_261);
        }

        ulRet = DHCPM_SetSecTimeoutNumByIndex(ulDhcpGroupIndex, 0);
        if ( VOS_OK != ulRet )
        {
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_262);
        }
    }
    else
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_120);
        return VOS_ERR;
    }

    return VOS_OK;
}
/*****************************************************************************
 函 数 名  : DHCPC_PrintLap2DhcpMsg
 功能描述  : 打印LAP消息的内容
 输入参数  : LAP2_DHCPC_MSG_S* pstLap2Msg
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年7月19日
    作    者   : jixiaoming 00180244
    修改内容   : 新生成函数

*****************************************************************************/
VOID DHCPC_PrintLap2DhcpMsg(LAP2_DHCPC_MSG_S* pstLap2Msg)
{
    if (NULL == pstLap2Msg)
    {
        VOS_Assert(0);
        return;
    }

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "msgtype=%u iptype=%u lapno=%u poolindex=%u sectionnum=%u dhcpgroupindex=%u",
            pstLap2Msg->ucMsgType, pstLap2Msg->ucAddressType, pstLap2Msg->ucLAPNo, pstLap2Msg->usPoolIndex,
            pstLap2Msg->ucSectionNum, pstLap2Msg->usDhcpGroupIndex);

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "agentip=0x%x %x %x %x  ip=0x%x %x %x %x",
            pstLap2Msg->aulAgentIP[0],pstLap2Msg->aulAgentIP[1], pstLap2Msg->aulAgentIP[2], pstLap2Msg->aulAgentIP[3],
            pstLap2Msg->aulPdpAddr[0],pstLap2Msg->aulPdpAddr[1], pstLap2Msg->aulPdpAddr[2], pstLap2Msg->aulPdpAddr[3]);

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "apnindex=%u  vpnid=%u  usertype=%u ucGtpVer=%u ulTeidc=0x%x ulIndex=%u ",
            pstLap2Msg->usApnIndex, pstLap2Msg->usVpnId, pstLap2Msg->ucUserType, pstLap2Msg->ucGtpVer,
            pstLap2Msg->ulTeidc, pstLap2Msg->ulIndex);

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "PrimaryDNS=0x%x %x %x %x  SecondaryDNS=0x%x %x %x %x",
            pstLap2Msg->aulPrimaryDNS[0], pstLap2Msg->aulPrimaryDNS[1], pstLap2Msg->aulPrimaryDNS[2], pstLap2Msg->aulPrimaryDNS[3],
            pstLap2Msg->aulSecondaryDNS[0], pstLap2Msg->aulSecondaryDNS[1], pstLap2Msg->aulSecondaryDNS[2], pstLap2Msg->aulSecondaryDNS[3]);

    return;
}

/*接收LAP地址分配请求和地址释放请求消息，促发DHCP*/
ULONG DHCPC_ReceiveLAP2Msg( VOID* pMsgBuf )
{
    UCHAR    ucMsgCode = 0;
    ULONG ulDHCPCtlIdx = 0;
    UCHAR ucLogicSlot = 0;
    LAP2_DHCPC_MSG_S* pstLap2DhcpCMsg = NULL;

    /*备板不处理*/
    ucLogicSlot = (UCHAR)CRM_GetSelfLogicSlotID();
    if (E_CRM_ACTIVE != CRM_GetSlotPrimaryInfoOfSelfGroup(ucLogicSlot))
    {
        return VOS_OK;
    }

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n-->DHCPC_ReceiveLAP2Msg()" );
    if ( NULL == pMsgBuf )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_013);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPC_ReceiveLAP2Msg NULL MsgBuf" );
        return VOS_ERR;
    }
    pstLap2DhcpCMsg = ( LAP2_DHCPC_MSG_S* )pMsgBuf;
    DHCPC_PRINT_LAP_MSG(pstLap2DhcpCMsg);
    ucMsgCode = pstLap2DhcpCMsg->ucMsgType;

    /* 根据用户类型填充当前DHCP控制块索引 */
    ulDHCPCtlIdx = pstLap2DhcpCMsg->ulTeidc;

    switch (ucMsgCode)
    {
            /* 收到地址申请消息 */
        case LAP2_SND2_DHCPC_ADDR_REQ_MSG:
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_014);
            DHCPC_MsgProc_Apply( pstLap2DhcpCMsg );
            break;

            /* 收到地址释放消息 */
        case LAP2_SND2_DHCPC_ADDR_REL_MSG:
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_015);
            DHCPC_MsgProc_Release( pstLap2DhcpCMsg);
            break;

            /* 收到地址更新/续租消息
               此处这个消息只是复用该共享队列,并非LAP2发送消息*/
        case LAP2_SND2_DHCPC_ADDR_REN_MSG:
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_016);
            DHCPC_MsgProc_Lease( ( LAP2_DHCPC_MSG_S * )pstLap2DhcpCMsg,ulDHCPCtlIdx );
            break;

            /* 收到地址强制回收消息 */
        case LAP2_SND2_DHCPC_ADDR_FORCE_REL_MSG:
            /* BEGIN: Deleted for PN:DTS2011120700783 by guolixian 00171003, 2012/1/6
            g_DHCPC_stHashTable没有初始化，这里调用可能导致单板异常复位*/
            break;

            /* 收到地址冲突消息 */
        case LAP2_SND2_DHCPC_ADDR_CONFLICT_MSG:
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_019);
            (VOID)DHCPC_MsgProc_Conflict( pstLap2DhcpCMsg);
            break;

        default:
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_020);
            VOS_Assert( 0 );
            DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPC_ReceiveSPUMsg Error MsgCode!" );
            return VOS_ERR;
    }
    return VOS_OK;
}

VOID DHCPC_ReceiveLap2MbufMsg(PMBUF_S *pstMBuf)
{
    UCHAR  *pucFwdMsg = NULL;

    if (NULL == pstMBuf)
    {
        VOS_Assert(0);
        return;
    }

    /*获取报文长度和地址*/
    pucFwdMsg = PMBUF_MTOD(pstMBuf, UCHAR*);
    if (NULL == pucFwdMsg)
    {
        return;
    }

    (VOID)DHCPC_ReceiveLAP2Msg((VOID *)pucFwdMsg);

    /* 外层释放Mbuf */
    return;
}

/*****************************************************************************
 函 数 名  : DHCPC_ReceiveServerMsg
 功能描述  : 接收sd上送的server返回的消息，解包后做相应处理
 输入参数  :  VOID* pstMsgBuf
 输出参数  : 无
 返 回 值  : ULONG
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年12月26日
    作    者   : caopu
    修改内容   : 新生成函数

*****************************************************************************/
ULONG DHCPC_ReceiveServerMbufMsg(PMBUF_S *pstMsgBuf)
{
    /*server回应，
     *1)遵循DHCP状态机
     *2)是REBIND状态还是初始状态回来的?STATUS为0则可从srv-ip取到临时控制块指针
     *3)xid是否一致?
     *4)删除临时控制块。
     */
    UDPS_PACKET_INFO_S stPktInf = {0};
    ULONG       ulRet = 0;
    ULONG       ulSrvIP = 0;
    UCHAR       ucLogicSlot = 0;
    ULONG       ulMsgLen = 0;
    UCHAR       *pucMsg = VOS_NULL;

    ucLogicSlot = (UCHAR)CRM_GetSelfLogicSlotID();
    if (E_CRM_ACTIVE != CRM_GetSlotPrimaryInfoOfSelfGroup(ucLogicSlot))
    {
        return VOS_OK;
    }

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "entry" );

    if ( NULL == pstMsgBuf )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_021);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n MBUF msg NULL!" );
        return VOS_ERR;
    }

    ulRet = (ULONG)UDPS_PickUpExt( &stPktInf, pstMsgBuf );
    if ( VOS_OK != ulRet )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_022);
        DHCPC_DebugPrint(PTM_LOG_ERR, " call UDPS_PickUp failed. [errcode=%u]", ulRet);
        return VOS_ERR;
    }

    ulMsgLen = PMBUF_GET_TOTAL_DATA_LENGTH(pstMsgBuf);
    if (ulMsgLen > DHCP_PKT_ASSUME_MAX_LEN)
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_113);
        DHCPC_DebugPrint(PTM_LOG_WARNING, " receive malformed Packet. length=%u", ulMsgLen);
        return VOS_ERR;
    }
    DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\nDHCPC_ReceiveServerMsg pkt length=%u", ulMsgLen );

    /* 检查Mbuf是否对消息进行了分片 */
    if (1 == PMBUF_GET_DATA_BLOCK_NUMBER(pstMsgBuf))
    {
        /* 没有分片 */
        pucMsg = PMBUF_MTOD(pstMsgBuf, UCHAR*);
    }
    else
    {
        /* 有分片，将MBUF内容复制到本地连续内存中 */
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\nDHCPC_ReceiveServerMsg pkt is sliced!" );
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_114);
        PGP_MemZero(g_pucDhcpPktBuf, sizeof(UCHAR) * DHCP_PKT_ASSUME_MAX_LEN);
        ulRet = PMBUF_CopyDataFromPMBufToBuffer(pstMsgBuf,
                                            0,
                                            ulMsgLen,
                                            g_pucDhcpPktBuf);
        if (VOS_OK != ulRet)
        {
            DHCPC_DebugPrint(PTM_LOG_WARNING, " call PMBUF_CopyDataFromPMBufToBuffer failed. [errcode=%u]", ulRet);
            VOS_Assert(0);
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_147);
            return VOS_ERR;
        }
        pucMsg = g_pucDhcpPktBuf;
    }

    ulSrvIP = stPktInf.uaddrSrc.stAddrSrc.sin_stAddr.s_ulAddr;
    if (ulMsgLen > DHCPC_PKT_FIXEDFIELD_LEN)
    {
        DHCPC_Dbg_PacketPrintReceive((DHCP_S*)pucMsg,  ulMsgLen - DHCPC_PKT_FIXEDFIELD_LEN);

        /* 处理DHCP消息 */
        (VOS_VOID)DHCPC_Pkt_ProcDHCP((DHCP_S*)pucMsg,  ulMsgLen - DHCPC_PKT_FIXEDFIELD_LEN, ulSrvIP);
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : DHCPC_ReceiveServerMsg
 功能描述  : 处理从sd发过来的dhcp server的响应消息
 输入参数  : UCHAR *pucMsg
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年5月18日
    作    者   : y00138047
    修改内容   : 新生成函数

*****************************************************************************/
VOID DHCPC_ReceiveServerMsg(UCHAR *pucMsg)
{
    PMBUF_S *pstMsgBuf = NULL;

    if ( NULL == pucMsg )
    {
        VOS_Assert(0);
        return;
    }

    pstMsgBuf = *((PMBUF_S **)pucMsg);

    if ( NULL == pstMsgBuf )
    {
        VOS_Assert(0);
        return;
    }

    (VOID)DHCPC_ReceiveServerMbufMsg(pstMsgBuf);

    ( VOS_VOID )PMBUF_Destroy(pstMsgBuf);
    *((PMBUF_S **)pucMsg) = NULL;

    return;
}

/*****************************************************************************
 函 数 名  : DHCPC_DelNode
 功能描述  : 从超时重发链表中删除一个节点
 输入参数  :  VOID* pstMsgBuf
 输出参数  : 无
 返 回 值  : ULONG
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年12月26日
    作    者   : caopu
    修改内容   : 新生成函数

*****************************************************************************/
VOID DHCPC_DelNode( ULONG ulTimerIndex, DHCPC_CTRLBLK_NODE* pstCurrNode )
{
    /*链表第一个节点*/
    ULONG    pTmrIndex = 0;

    if ( NULL == pstCurrNode )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_023);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\nDHCPC_DelNode para err!" );
        return;
    }

    if ( DHCPC_INVALID_INDEX == ulTimerIndex )
    {
        ULONG ulHeadNodeType = 0;
        DLL_NODE_S* pstTmpNode = ( DLL_NODE_S* )pstCurrNode;
        /*lint -e716*/
        while ( VOS_TRUE )
        /*lint +e716*/
        {
            ulHeadNodeType = DLL_GET_HANDLE( pstTmpNode );
            if ( DHCPC_HEADNODE_TYPE == ulHeadNodeType )
            {
                DLL_Delete( ( DLL_S* )pstTmpNode,( DLL_NODE_S* )pstCurrNode );
                break;
            }
            pstTmpNode = pstTmpNode->pPrev;
            if(NULL == pstTmpNode)
            {
                break;
            }
        }
    }
    else
    {
        pTmrIndex = ulTimerIndex % DHCPC_TMR_CIRCLE_TIME;
        DLL_Delete( &( g_astTimerLink[pTmrIndex] ), ( DLL_NODE_S * )pstCurrNode );
    }

    return;
}

/*ulSeconds:ulSeconds后的链表*/
/*****************************************************************************
 函 数 名  : DHCPC_InSertNodeAfterSecs
 功能描述  : 向重发链表中插入一个节点
 输入参数  :  VOID* pstMsgBuf
 输出参数  : 无
 返 回 值  : ULONG
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年12月26日
    作    者   : caopu
    修改内容   : 新生成函数

*****************************************************************************/
VOID DHCPC_InSertNodeAfterSecs( ULONG ulSeconds,DHCPC_CTRLBLK_NODE* pstCurrNode )
{
    ULONG pTmrIndex = 0;
    DLL_S *pstDhcpcTmrNode = NULL;

    if ( NULL == pstCurrNode )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_025);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\nDHCPC_InSertNodeAfterSecs para err!" );
        return;
    }

    /*从妙数转换到头结点索引*/
    pTmrIndex = ( g_ulCurrProcIndex + ulSeconds * DHCPC_RETRANS_STEPS_PERSEC )% DHCPC_TMR_CIRCLE_TIME;
    if ( pTmrIndex >= DHCPC_TMR_CIRCLE_TIME )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_026);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\nDHCPC_DelNode pTmrIndex error!" );
        return;
    }

    pstDhcpcTmrNode = &( g_astTimerLink[pTmrIndex] );
    DLL_Insert( pstDhcpcTmrNode,NULL,( DLL_NODE_S * )pstCurrNode );

    return;
}

/*****************************************************************************
 函 数 名  : DHCPC_GetDhcpTmpNode
 功能描述  : 获取一个空闲的临时控制块节点
 输入参数  :  VOID
 输出参数  : 无
 返 回 值  : ULONG
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年12月26日
    作    者   : caopu
    修改内容   : 新生成函数

*****************************************************************************/
DHCPC_CTRLBLK_NODE* DHCPC_GetDhcpTmpNode( VOID )
{
    ULONG i = 0;

    for ( i = 0; i < DHCPC_MAX_CTRLBLKNUM; i++ )
    {
        if ( DHCPC_CTRLBLK_IDLE == g_pstDhcpCtrlBlkNodeArr[i].ucOccupiedFlg )
        {
            /*置占用标志，返回指针*/
            g_pstDhcpCtrlBlkNodeArr[i].ucOccupiedFlg = DHCPC_CTRLBLK_OCCUPIED;
            return ( DHCPC_CTRLBLK_NODE* )&( g_pstDhcpCtrlBlkNodeArr[i] );
        }
    }
    DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_027);
    DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\nDHCPC_GetDhcpTmpNode:Dhcp temp control block used up!" );
    return NULL;
}

/*****************************************************************************
 函 数 名  : DHCPC_FreeDhcpTmpNode
 功能描述  : 释放临时控制块节点
 输入参数  :  VOID
 输出参数  : 无
 返 回 值  : ULONG
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年12月26日
    作    者   : caopu
    修改内容   : 新生成函数

*****************************************************************************/
VOID DHCPC_FreeDhcpTmpNode( DHCPC_CTRLBLK_NODE* pNode )
{

    if ( NULL == pNode )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_028);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n-->DHCPC_FreeDhcpTmpNode() pNode is null !" );
        return;
    }

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n-->DHCPC_FreeDhcpTmpNode()" );
    /*结构清0，占用标志恢复成IDLE状态*/
    PGP_MemZero( pNode, sizeof( DHCPC_CTRLBLK_NODE ) );
    return;
}

/*=======================================================================
 *  函数名称:              DHCPC_RenewIpAddr
 *  初稿完成:              2003/12/30
 *  作    者:             肖卫方
 *  函数功能:              向DHCPServer发送续租消息
 *  输入参数:              DHCPC_CTRLBLK *pstDhcpcCtlBlk
 *  输出参数:
 *  返回类型:              VOS_OK/VOS_ERR
 *  其他说明:              传入DHCP控制块，处理该消息时，需要根据用户类型来查找控制块
 *  调用函数:              VOS_MCWriteQue
 *  主调函数:              DHCPC_RenewTimeOut
 *  修改者  :              w00140934
 *  修改时间:              2010/08/05
 *=======================================================================*/
ULONG DHCPC_RenewIpAddr( DHCPC_CTRLBLK *pstDhcpcCtlBlk )
{
    LAP2_DHCPC_MSG_S stMsg = {0};
    ULONG ulRet = 0;


    DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n-->DHCPC_RenewIpAddr()" );
    DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_205);

    if ( NULL == pstDhcpcCtlBlk )
    {
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n-->DHCPC_RenewIpAddr:NULL == pstDhcpcCtlBlk" );
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_029);
        return VOS_ERR;
    }

    /* 填充消息体 */
    stMsg.ucMsgType = LAP2_SND2_DHCPC_ADDR_REN_MSG;
    stMsg.ulIndex = pstDhcpcCtlBlk->ulPDPIndex;
    stMsg.ulTeidc = pstDhcpcCtlBlk->ulTEIDC;
    stMsg.ucGtpVer = pstDhcpcCtlBlk->ucUser;
    stMsg.ucLAPNo = pstDhcpcCtlBlk->ucLAPNo;

    /* 后续该处需要优化, 给内部队列写消息 */
    if ( CRM_BOARD_TYPE_SPUD == g_ulDhcpcSpuType )
    {
        ulRet = DHCPC_SendRtMsg(DHCPC_SELF_CSI, DHCPC_MSG_TYPE_LAP, LAP2_SND2_DHCPC_ADDR_REN_MSG,
                                (UCHAR *)&stMsg, sizeof(LAP2_DHCPC_MSG_S));
    }
    else
    {
        ulRet = DHCPC_SendURTMsg(DHCPC_SELF_CSI, DHCPC_SELF_CSI, DHCPC_MSG_TYPE_FCM,
                                 LAP2_SND2_DHCPC_ADDR_REN_MSG, (UCHAR *)&stMsg, sizeof(LAP2_DHCPC_MSG_S));
    }

    return ulRet;
}

/*=======================================================================
 *  函数名称: DHCPC_SaveTmpDhcpCtrlBlkPtr
 *  初稿完成: 2010/08/05
 *  作    者: w00140934
 *  函数功能: 保存DHCP临时控制块
 *  输入参数: DHCPC_CTRLBLK_NODE* pDhcpCtrlBlkNodePtr
 *  返回类型: VOS_OK/VOS_ERR
 *  其他说明: 存储的是临时控制块节点的指针
 *=======================================================================*/
ULONG DHCPC_SaveTmpDhcpCtrlBlkPtr( ULONG ulDHCPCtlIdx, ULONG ulTEIDC, UCHAR ucUser, ULONG ulPdpIndex, DHCPC_CTRLBLK_NODE* pstDhcpCtrlBlkNodePtr )
{
    ULONG ulRet = VOS_ERR;
    DHCPC_CTRLBLK   * pstDhcpcCtlBlk = NULL;

    if ( NULL == pstDhcpCtrlBlkNodePtr )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_031);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPC_SaveTmpDhcpCtrlBlkPtr pDhcpCtrlBlkNodePtr is null!" );
        return ulRet;
    }

    /*获取控制块*/
    pstDhcpcCtlBlk = (DHCPC_CTRLBLK *)DHCPC_CalcCtlBlkHashValue(ulDHCPCtlIdx, ulTEIDC);
    if ( NULL != pstDhcpcCtlBlk )
    {
        /*用户获取IP地址之前，DHCP控制块是没用的，
         *使用ser-ip字段保存临时控制块的地址指针
         */
        if ( DHCPC_STATE_INITIAL == pstDhcpcCtlBlk->usDhcpStatus )
        {
            /*使用ulTmpVar字段保存指针*/
            pstDhcpcCtlBlk->pTmpDhcpCtrlBlkPtr = (VOID *)pstDhcpCtrlBlkNodePtr;
            DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPC_SaveTmpDhcpCtrlBlkPtr usDhcpStatus = INITIAL " );
            ulRet = VOS_OK;
        }
        else
        {
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_032);
            /*调试信息*/
            DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\nDhcp State err. when saving TmpCtrlBlk!" );
        }
    }
    else
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_033);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\nContexe not exist when saving TmpCtrlBlk!" );
    }

    return ulRet;
}

/*=======================================================================
 *  函数名称: DHCPC_GetTmpDhcpCtrlBlkPtr
 *  初稿完成: 2010/08/05
 *  作    者: w00140934
 *  函数功能: 获取DHCP临时控制块
 *  输入参数: DHCPC_CTRLBLK *pstDhcpCtrBlk
 *  返回类型: pstDhcpCtrlBlkNode/NULL
 *  其他说明: 获取控制块中保存的临时控制块指针
 *=======================================================================*/
DHCPC_CTRLBLK_NODE* DHCPC_GetTmpDhcpCtrlBlkPtr( DHCPC_CTRLBLK *pstDhcpCtrBlk )
{
    DHCPC_CTRLBLK_NODE*    pstDhcpCtrlBlkNode = NULL;

    if ( NULL == pstDhcpCtrBlk )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_034);
        VOS_DBGASSERT( 0 );
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPC_GetTmpDhcpCtrlBlkPtr ulCtrlBlkIndex call func failed!" );
        return NULL;
    }

    if ( ( DHCPC_STATE_INITIAL == pstDhcpCtrBlk->usDhcpStatus )
         && ( 0 != pstDhcpCtrBlk->pTmpDhcpCtrlBlkPtr ) )
    {
        pstDhcpCtrlBlkNode = (DHCPC_CTRLBLK_NODE *)pstDhcpCtrBlk->pTmpDhcpCtrlBlkPtr;
        if ( 0 == VOS_StrCmp( ( const CHAR* )( ( pstDhcpCtrlBlkNode->stDhcpcTmpCtlBlk ).ucCtrlBlkFlgStr ), DHCPC_TMPCTRLBLK_IDSTR ) )
            return pstDhcpCtrlBlkNode;
    }
    DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_035);
    return NULL;
}

/*=======================================================================
 *  函数名称: DHCPC_SaveSdbDhcpCtrlBlk
 *  初稿完成: 2010/08/05
 *  作    者: w00140934
 *  函数功能: 保存DHCP控制块
 *  输入参数: DHCPC_TEMPCTRLBLK* pstDhcpTmpCtrlBlk, VOS_BOOL bIsRenewState
 *  返回类型: VOS_OK/VOS_ERR
 *  其他说明: 仅在收到ACK，而且检查合格情况下调用，状态变为BOUND
 *=======================================================================*/
ULONG DHCPC_SaveSdbDhcpCtrlBlk( DHCPC_TEMPCTRLBLK* pstDhcpTmpCtrlBlk, VOS_BOOL bIsRenewState )
{
    DHCPC_CTRLBLK        *pstDhcpCtrlBlk = NULL;
    ULONG                        ulRetTimeInSec = 0;

    if ( ( NULL == pstDhcpTmpCtrlBlk ) || ( 0 == pstDhcpTmpCtrlBlk->usLease ) )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_036);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\nDHCPC_SaveSdbDhcpCtrlBlk para err!" );
        return VOS_ERR;
    }

    /*获取控制块*/
    pstDhcpCtrlBlk = (DHCPC_CTRLBLK *)DHCPC_CalcCtlBlkHashValue(pstDhcpTmpCtrlBlk->ulDHCPCtlIdx, pstDhcpTmpCtrlBlk->ulTEIDC);
    if ( NULL == pstDhcpCtrlBlk )
    {
        /*打印调试信息*/
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_039);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPC_SaveSdbDhcpCtrlBlk pstDhcpCtrlBlk not exist!" );
        return VOS_ERR;
    }
    else
    {
        pstDhcpCtrlBlk->ulDHCPCtxIdx = pstDhcpTmpCtrlBlk->ulDHCPCtlIdx;
        pstDhcpCtrlBlk->aulAgentIpAddr[0] = pstDhcpTmpCtrlBlk->ulAgetIP;/*暂时用来存agent ip*/
        pstDhcpCtrlBlk->usVPNIndex= pstDhcpTmpCtrlBlk->usVpnId;
        pstDhcpCtrlBlk->usServerGrpIndex = pstDhcpTmpCtrlBlk->usDhcpGroupIndex;
        pstDhcpCtrlBlk->ucUserType = pstDhcpTmpCtrlBlk->ucUserType;

        pstDhcpCtrlBlk->aulMSISDN[0] = pstDhcpTmpCtrlBlk->aulMSISDN[0];
        pstDhcpCtrlBlk->aulMSISDN[1] = pstDhcpTmpCtrlBlk->aulMSISDN[1];
        pstDhcpCtrlBlk->aulUserIpAddr[0] = pstDhcpTmpCtrlBlk->ulUserIpAddr;
        pstDhcpCtrlBlk->ulLease = pstDhcpTmpCtrlBlk->usLease;
        pstDhcpCtrlBlk->aulSrvIp[0] = pstDhcpTmpCtrlBlk->ulSrvIp;
        pstDhcpCtrlBlk->usPoolIndex = pstDhcpTmpCtrlBlk->usPoolIndex;

        pstDhcpCtrlBlk->aulIMSI[0] = pstDhcpTmpCtrlBlk->aulIMSI[0];
        pstDhcpCtrlBlk->aulIMSI[1] = pstDhcpTmpCtrlBlk->aulIMSI[1];
        /* BEGIN: Added by jixiaoming for  IMEI跟踪 at 2012-8-17 */
        pstDhcpCtrlBlk->aulIMEI[0] = pstDhcpTmpCtrlBlk->aulIMEI[0];
        pstDhcpCtrlBlk->aulIMEI[1] = pstDhcpTmpCtrlBlk->aulIMEI[1];
        /* END: Added by jixiaoming for IMEI跟踪 at 2012-8-17 */
        pstDhcpCtrlBlk->ucRole = pstDhcpTmpCtrlBlk->ucRole;
        /*需要将用户类型、TEIDC和上下文索引赋值*/
		pstDhcpCtrlBlk->ucUser = pstDhcpTmpCtrlBlk->ucUser;
        pstDhcpCtrlBlk->ulTEIDC = pstDhcpTmpCtrlBlk->ulTEIDC;
        pstDhcpCtrlBlk->ulPDPIndex = pstDhcpTmpCtrlBlk->ulPdpIndex;
        pstDhcpCtrlBlk->ucLAPNo = pstDhcpTmpCtrlBlk->ucLAPNo;
        pstDhcpCtrlBlk->ucRandomNo = pstDhcpTmpCtrlBlk->ucRandomNo; /* 随机跟踪 DTS2012091903437 y00170683 */

        (VOID)PGP_TmNowInSec( &ulRetTimeInSec);
        pstDhcpCtrlBlk->ulTimeStamp = ulRetTimeInSec;

        if ( VOS_TRUE == bIsRenewState )
        {
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_038);

            VOS_Assert( pstDhcpCtrlBlk->ulTmpVar == pstDhcpTmpCtrlBlk->ulTimeStamp );
        }
        else
        {
            pstDhcpCtrlBlk->ulTmpVar = 0;
        }

        pstDhcpCtrlBlk->usDhcpStatus = DHCPC_STATE_BOUND;

        return VOS_OK;
    }
}

/*****************************************************************************
 函 数 名  : DHCPC_ResendMSG
 功能描述  : 重发消息的处理函数
 输入参数  :  DHCPC_CTRLBLK_NODE* pstDhcpCtrlBlkNode
 输出参数  : 无
 返 回 值  : ULONG
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年12月26日
    作    者   : caopu
    修改内容   : 新生成函数

*****************************************************************************/
ULONG DHCPC_ResendMSG( DHCPC_CTRLBLK_NODE* pstDhcpCtrlBlkNode )
{
    /*只重发DISCOVER和REQUEST消息*/
    USHORT    usDhcpStatus = 0;
    ULONG    ulRet = VOS_ERR;
    DHCPC_TEMPCTRLBLK* pstDhcpTmpCtrlBlk = NULL;

    if ( NULL == pstDhcpCtrlBlkNode )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_040);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\nDHCPC_ResendMSG Null CtrlBlkNode!" );
        return VOS_ERR;
    }

    pstDhcpTmpCtrlBlk = &( pstDhcpCtrlBlkNode->stDhcpcTmpCtlBlk );
    usDhcpStatus = pstDhcpTmpCtrlBlk->usDhcpStatus;
    switch ( usDhcpStatus )
    {
        case DHCPC_STATE_DISCOVER:
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_041);
            ulRet = ( ULONG )DHCPC_Pkt_Send( DHCP_DISCOVER, pstDhcpTmpCtrlBlk );
            break;
        case DHCPC_STATE_REQUEST:
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_042);
            ulRet = ( ULONG )DHCPC_Pkt_Send( DHCP_REQUEST, pstDhcpTmpCtrlBlk );
            break;
        default:
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_043);
            VOS_Assert( 0 );
            ulRet = VOS_ERR;/*for UT*/
            DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\nDHCPC_ResendMSG error DHCP State!" );
            break;
    }
    if ( VOS_OK != ulRet )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_044);
        /*删控制块*/
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\nDHCPC_ResendMSG resend failed!" );
        /* 外层调用处对失败情况已经进行了释放处理，故注释掉此处的释放处理 */
        /*
        DHCPC_DelNode( g_ulCurrProcIndex,pstDhcpCtrlBlkNode );
        DHCPC_FreeDhcpCtrlBlk( pstDhcpCtrlBlkNode->stDhcpcTmpCtlBlk.ulDHCPCtlIdx, pstDhcpCtrlBlkNode->stDhcpcTmpCtlBlk.ulTEIDC, pstDhcpCtrlBlkNode->stDhcpcTmpCtlBlk.ucUser, pstDhcpCtrlBlkNode->stDhcpcTmpCtlBlk.ulPdpIndex );
        DHCPC_FreeDhcpTmpNode( pstDhcpCtrlBlkNode );
        */
        return ulRet;
    }
    /*重发时不更新timestamp*/
    VOS_Assert( NULL != pstDhcpTmpCtrlBlk->ulTimeStamp );

    /* 更改重发标志，每次重发状态向后迁移1 */
    pstDhcpTmpCtrlBlk->usAlreadySendFlg += 1;

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : DHCPC_SetReNewDhcpServerIp
 功能描述  : 获取bit218号软参值，并根据软参值选择发送续租的dhcp server服务器ip地址
 输入参数  : DHCPC_TEMPCTRLBLK *pstDhcpTmpCtrlBlk,
             DHCPC_SRV_GRP_S *pstDHCPCSrvGrp
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  : DHCPC_OutPut

 修改历史      :
  1.日    期   : 2011-12-01
    作    者   : zhangjinquan 00175135
    修改内容   : 新生成函数 DTS2011080902075 根据问题单同步bit218处理 001

*****************************************************************************/
VOID DHCPC_SetReNewDhcpServerIp(DHCPC_TEMPCTRLBLK *pstDhcpTmpCtrlBlk, LAP_DHCP_CFG_S *pstDhcpServer,
                                DHCP_SERVER_STATUS_S *pstDhcpServerStatus)
{
    UCHAR ucBit218Value = 0;

    if (VOS_OK != SPM_GetBitValue(M_SPM_BIT_218, &ucBit218Value))
    {
        ucBit218Value = 0;
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_281);
    }

    if (0 == ucBit218Value)
    {
        /* z00175135 根据bit218软参描述:bit218=0时只要主的ok就往主的发，否则往备发，没配置备的则往原server发 2012-04-12 start */
        if (DHCP_SEVER_NORMAL == pstDhcpServerStatus->ucPrimarySrvStatus)
        {
                pstDhcpTmpCtrlBlk->ulSrvIp = pstDhcpServer->aulPrimaryServerIp[0];
                DHCPC_DebugPrint(PTM_LOG_DEBUG,
                                "\r\n DHCPC_OutPut The Secondary DHCP Server has been down!Send Lease Message To The Secondary DHCP Server!" );
        }
        else if ((DHCP_SEVER_NORMAL == pstDhcpServerStatus->ucSecondarySrvStatus)
            && (0 != pstDhcpServer->aulSecondaryServerIp[0]))
        {
                pstDhcpTmpCtrlBlk->ulSrvIp = pstDhcpServer->aulSecondaryServerIp[0];
                DHCPC_DebugPrint(PTM_LOG_DEBUG,
                                "\r\n DHCPC_OutPut The Primary DHCP Server has been down!Send Lease Message To The Primary DHCP Server!" );

        }
        /* 处理续租消息: 如果都挂了就向原来的发送 */
        else
        {
             DHCPC_DebugPrint(PTM_LOG_DEBUG,
                            "\r\n DHCPC_OutPut The Primary and Secondary both down! Send Lease Message To The Original DHCP Server!" );
        }
        /* z00175135 根据bit218软参描述:bit218=0时只要主的ok就往主的发，否则往备发，没配置备的则往原server发 2012-04-12 end   */
    }

    return;
}

/*****************************************************************************
 函 数 名  : DHCPC_SetTmpCtrlBlkSrvIp
 功能描述  : 设置release/decline消息中临时控制块的server IP
 输入参数  : pstDhcpTmpCtrlBlk
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月29日
    作    者   : m00221593
    修改内容   : 新生成函数

*****************************************************************************/
void DHCPC_SetTmpCtrlBlkSrvIp(DHCPC_TEMPCTRLBLK *pstDhcpTmpCtrlBlk)
{
    ULONG ulRet = VOS_OK;
    DHCP_SERVER_STATUS_S stDhcpServerStatus = {0};
    LAP_DHCP_CFG_S stDhcpServer = {0};

    if (NULL == pstDhcpTmpCtrlBlk)
    {
        /*调试信息*/
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPC_SetDhcpSrvIp para error pstDhcpTmpCtrlBlk = NULL");
        return;
    }

    ulRet = DHCPM_GetDhcpSrvCfgStatusByIndex((ULONG)pstDhcpTmpCtrlBlk->usDhcpGroupIndex, &stDhcpServer, &stDhcpServerStatus);
    if ( VOS_OK != ulRet )
    {
        return;
    }

    DHCPC_SetReNewDhcpServerIp(pstDhcpTmpCtrlBlk, &stDhcpServer, &stDhcpServerStatus);

    return;
}

/*****************************************************************************
 函 数 名  : DHCPC_OutPut
 功能描述  : DHCP模块的udp发送函数
 输入参数  : UCHAR ucPktType, DHCPC_TEMPCTRLBLK* pstDhcpTmpCtrlBlk, PMBUF_S* pMBuf, LONG* plSecondReturnCode
 输出参数  : 无
 返 回 值  : ULONG
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年12月26日
    作    者   : caopu
    修改内容   : 新生成函数

*****************************************************************************/
LONG DHCPC_OutPut( UCHAR ucPktType, DHCPC_TEMPCTRLBLK* pstDhcpTmpCtrlBlk, PMBUF_S* pMBuf, LONG* plSecondReturnCode )
{
    LONG                    lRetCode = VOS_OK;
    FWD_TO_CTRL_HDR         stCtrlEncap = {0};
    UDPS_PACKET_INFO_S         stNodeTemp = {0};
    DHCP_SERVER_STATUS_S stDhcpServerStatus = {0};
    LAP_DHCP_CFG_S stDhcpServer = {0};
    ULONG ulDhcpGroupIndex = 0;
    ULONG ulRet = VOS_OK;

    /*参数合法性检查*/
    if ( NULL == plSecondReturnCode )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_045);
        /*调试信息*/
        DHCPC_DebugPrint(PTM_LOG_DEBUG,
                     "\r\n DHCPC_OutPut para error plSecondReturnCode = NULL");
        return VOS_ERR;
    }

    *plSecondReturnCode = VOS_ERR;

    if ( ( NULL == pstDhcpTmpCtrlBlk ) || ( NULL == pMBuf ) )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_046);
        /*调试信息*/
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPC_OutPut para error pstDhcpTmpCtrlBlk = NULL,pMBuf = NULL");
        return VOS_ERR;
    }

    /*判断要发送消息的类型是否合法*/
    if ( ( DHCP_DISCOVER != ucPktType )
         && ( DHCP_REQUEST != ucPktType )
         && ( DHCP_DECLINE != ucPktType )
         && ( DHCP_RELEASE != ucPktType ) )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_047);
        /*调试信息*/
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPC_OutPut Err DHCP packet type!" );
        return VOS_ERR;
    }

    /* 用于控制DHCP控制报文是否携带CheckSum */
    if (AM_IsNeedChecksum(AM_CHECKSUM_DHCP))
    {
        UDPS_SET_CHECK_SUM_ENABLE(&stNodeTemp);
    }

    ulDhcpGroupIndex = pstDhcpTmpCtrlBlk->usDhcpGroupIndex;
    if ( ulDhcpGroupIndex >= DHCPGRP_MAX_NUM )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_048);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPC_OutPut Err DHCP usDhcpGroupIndex!" );
        return VOS_ERR;
    }

    ulRet = DHCPM_GetDhcpSrvCfgStatusByIndex(ulDhcpGroupIndex, &stDhcpServer, &stDhcpServerStatus);
    if ( VOS_OK != ulRet )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_049);
        *plSecondReturnCode = VOS_ERR;
        return VOS_ERR;
    }

    /*发送Discover类型的消息时，如果配置了主备DHCP Server，要先向主DHCP Server发送
    在主DHCP Server不通的情况下，再向备DHCP Server发送消息*/

    stNodeTemp.ulFamily = AF_INET;/*add by cxf*/

    if ( DHCP_DISCOVER == ucPktType )
    {
        /* DHCP Server ip 为空则表明第一次发送discover消息 */
        if ( NULL == pstDhcpTmpCtrlBlk->ulSrvIp )
        {
            /*主备DHCP Server都没有配置*/
            if ( ( 0 == stDhcpServer.aulPrimaryServerIp[0] ) )
            {
                DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_051);
                /*调试信息*/
                DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPC_OutPut apn non't configure DHCP Server!" );
                *plSecondReturnCode = VOS_ERR;
                return VOS_ERR;
            }
            /*配置了主DHCP Server 且主服务器状态正常*/
            else if ( DHCP_SEVER_NORMAL == stDhcpServerStatus.ucPrimarySrvStatus )
            {
                /*构造UDP头参数*/
                stNodeTemp.uaddrSrc.stAddrSrc.sin_stAddr.s_ulAddr = pstDhcpTmpCtrlBlk->ulAgetIP;
                if (g_ucSoftParaDHCPKPN & ((UCHAR)0x02))
                {
                    stNodeTemp.uaddrSrc.stAddrSrc.sin_usPort = DHCPS_PKT_PORTNO;
                }
                else
                {
                    stNodeTemp.uaddrSrc.stAddrSrc.sin_usPort = DHCPC_PKT_PORTNO;
                }
                stNodeTemp.uaddrDst.stAddrDst.sin_stAddr.s_ulAddr = stDhcpServer.aulPrimaryServerIp[0];
                stNodeTemp.uaddrDst.stAddrDst.sin_usPort = DHCPS_PKT_PORTNO;
                stNodeTemp.ulVpnId = stDhcpServer.ulVpnIndex;
                stNodeTemp.pData = (CHAR*)&stCtrlEncap;
                stNodeTemp.ulDataLen = sizeof( FWD_TO_CTRL_HDR );

                /*调用函数发送报文*/
                PGP_MemZero( &stCtrlEncap,sizeof( FWD_TO_CTRL_HDR ) );

                fwd_set_ctrlhdr_vcpuid(&stCtrlEncap,0);
                fwd_set_ctrlhdr_vrfindex(&stCtrlEncap,stDhcpServer.ulVpnIndex);
                fwd_set_ctrlhdr_msgcode(&stCtrlEncap,(ULONG)ucPktType);
                fwd_set_ctrlhdr_moduleid(&stCtrlEncap,MID_DHCPC);

                pstDhcpTmpCtrlBlk->ulSrvIp = stDhcpServer.aulPrimaryServerIp[0];

                //GTPC_DumpMessage(pMBuf->stDataBlockDescriptor.pucData,pMBuf->ulTotalDataLength);
                DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPC_OutPut : 11 GTPC_DumpMessage %u ; %d ; %u ; %d ; %u ; %u ;" ,
                             stNodeTemp.uaddrSrc.stAddrSrc.sin_stAddr.s_ulAddr,stNodeTemp.uaddrSrc.stAddrSrc.sin_usPort,stNodeTemp.uaddrDst.stAddrDst.sin_stAddr.s_ulAddr,
                             stNodeTemp.uaddrDst.stAddrDst.sin_usPort,stNodeTemp.ulVpnId,stCtrlEncap.ulVcpuId );
                stNodeTemp.uaddrDst.stAddrDst.sin_chFamily = AF_INET;
                stNodeTemp.uaddrSrc.stAddrSrc.sin_chFamily = AF_INET;
                (VOID)UDPS_ConvertToSockAddr(&(stNodeTemp.uaddrSrc.stAddrSrc), sizeof(SOCKADDRIN_S));
                (VOID)UDPS_ConvertToSockAddr(&(stNodeTemp.uaddrDst.stAddrDst), sizeof(SOCKADDRIN_S));
                lRetCode = UDPS_DataHandle ( &stNodeTemp, pMBuf ); /*Deleted by hourufeng &stCtrlEncap,sizeof( FWD_TO_CTRL_HDR ) );*/


            }
            else if ( DHCP_PRISRV_TEST_ON == stDhcpServerStatus.ucPrimarySrvTest )
            {
                /*构造UDP头参数*/
                stNodeTemp.uaddrSrc.stAddrSrc.sin_stAddr.s_ulAddr = pstDhcpTmpCtrlBlk->ulAgetIP;
                if (g_ucSoftParaDHCPKPN & ((UCHAR)0x02))
                {
                    stNodeTemp.uaddrSrc.stAddrSrc.sin_usPort = DHCPS_PKT_PORTNO;
                }
                else
                {
                    stNodeTemp.uaddrSrc.stAddrSrc.sin_usPort = DHCPC_PKT_PORTNO;
                }
                stNodeTemp.uaddrDst.stAddrDst.sin_stAddr.s_ulAddr = stDhcpServer.aulPrimaryServerIp[0];
                stNodeTemp.uaddrDst.stAddrDst.sin_usPort = DHCPS_PKT_PORTNO;
                stNodeTemp.ulVpnId = stDhcpServer.ulVpnIndex;
                stNodeTemp.pData = (CHAR*)&stCtrlEncap;
                stNodeTemp.ulDataLen = sizeof( FWD_TO_CTRL_HDR );

                /*调用函数发送报文*/
                PGP_MemZero( &stCtrlEncap,sizeof( FWD_TO_CTRL_HDR ) );

                fwd_set_ctrlhdr_vcpuid(&stCtrlEncap,0);
                fwd_set_ctrlhdr_vrfindex(&stCtrlEncap,stDhcpServer.ulVpnIndex);
                fwd_set_ctrlhdr_msgcode(&stCtrlEncap,(ULONG)ucPktType);
                fwd_set_ctrlhdr_moduleid(&stCtrlEncap,MID_DHCPC);

                pstDhcpTmpCtrlBlk->ulSrvIp = stDhcpServer.aulPrimaryServerIp[0];

                //GTPC_DumpMessage(pMBuf->stDataBlockDescriptor.pucData,pMBuf->ulTotalDataLength);
                DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n 22 DHCPC_OutPut :  GTPC_DumpMessage %u ; %d ; %u ; %d ; %u ; %u ;" ,
                             stNodeTemp.uaddrSrc.stAddrSrc.sin_stAddr.s_ulAddr,stNodeTemp.uaddrSrc.stAddrSrc.sin_usPort,stNodeTemp.uaddrDst.stAddrDst.sin_stAddr.s_ulAddr,
                             stNodeTemp.uaddrDst.stAddrDst.sin_usPort,stNodeTemp.ulVpnId,stCtrlEncap.ulVcpuId );



                /* zhangjinquan z00175135 加写共享内存锁*/
                //pstDHCPCSrvGrp->ucPrimarySrvTest = DHCP_PRISRV_TEST_DOWN;
                ulRet = DHCPM_SetPrimarySrvTestByIndex(ulDhcpGroupIndex, DHCP_PRISRV_TEST_DOWN);
                if ( VOS_OK != ulRet )
                {
                    DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_279);
                    return VOS_ERR;
                }
                stNodeTemp.uaddrDst.stAddrDst.sin_chFamily = AF_INET;
                stNodeTemp.uaddrSrc.stAddrSrc.sin_chFamily = AF_INET;
                (VOID)UDPS_ConvertToSockAddr(&(stNodeTemp.uaddrSrc.stAddrSrc), sizeof(SOCKADDRIN_S));
                (VOID)UDPS_ConvertToSockAddr(&(stNodeTemp.uaddrDst.stAddrDst), sizeof(SOCKADDRIN_S));
                lRetCode = UDPS_DataHandle ( &stNodeTemp, pMBuf );
                /* 下面会根据ulRet的值进行处理，不可以return */
            }

            /*配置了备DHCP Server*/
            else if ( ( 0 != stDhcpServer.aulSecondaryServerIp[0] )&&( DHCP_SEVER_NORMAL == stDhcpServerStatus.ucSecondarySrvStatus ) )
            {
                /*构造UDP头参数*/
                stNodeTemp.uaddrSrc.stAddrSrc.sin_stAddr.s_ulAddr = pstDhcpTmpCtrlBlk->ulAgetIP;
                if (g_ucSoftParaDHCPKPN & ((UCHAR)0x02))
                {
                    stNodeTemp.uaddrSrc.stAddrSrc.sin_usPort = DHCPS_PKT_PORTNO;
                }
                else
                {
                    stNodeTemp.uaddrSrc.stAddrSrc.sin_usPort = DHCPC_PKT_PORTNO;
                }
                stNodeTemp.uaddrDst.stAddrDst.sin_stAddr.s_ulAddr = stDhcpServer.aulSecondaryServerIp[0];
                stNodeTemp.uaddrDst.stAddrDst.sin_usPort = DHCPS_PKT_PORTNO;
                stNodeTemp.ulVpnId = stDhcpServer.ulVpnIndex;
                stNodeTemp.pData = (CHAR*)&stCtrlEncap;
                stNodeTemp.ulDataLen = sizeof( FWD_TO_CTRL_HDR );

                /*调用函数发送报文*/
                PGP_MemZero( &stCtrlEncap,sizeof( FWD_TO_CTRL_HDR ) );

                fwd_set_ctrlhdr_vcpuid(&stCtrlEncap,0);
                fwd_set_ctrlhdr_vrfindex(&stCtrlEncap,stDhcpServer.ulVpnIndex);
                fwd_set_ctrlhdr_msgcode(&stCtrlEncap,(ULONG)ucPktType);
                fwd_set_ctrlhdr_moduleid(&stCtrlEncap,MID_DHCPC);

                pstDhcpTmpCtrlBlk->ulSrvIp = stDhcpServer.aulSecondaryServerIp[0];
                //GTPC_DumpMessage(pMBuf->stDataBlockDescriptor.pucData,pMBuf->ulTotalDataLength);
                DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n 33 DHCPC_OutPut :  GTPC_DumpMessage %u ; %d ; %u ; %d ; %u ; %u ;" ,
                             stNodeTemp.uaddrSrc.stAddrSrc.sin_stAddr.s_ulAddr,stNodeTemp.uaddrSrc.stAddrSrc.sin_usPort,stNodeTemp.uaddrDst.stAddrDst.sin_stAddr.s_ulAddr,
                             stNodeTemp.uaddrDst.stAddrDst.sin_usPort,stNodeTemp.ulVpnId,stCtrlEncap.ulVcpuId );
                stNodeTemp.uaddrDst.stAddrDst.sin_chFamily = AF_INET;
                stNodeTemp.uaddrSrc.stAddrSrc.sin_chFamily = AF_INET;
                (VOID)UDPS_ConvertToSockAddr(&(stNodeTemp.uaddrSrc.stAddrSrc), sizeof(SOCKADDRIN_S));
                (VOID)UDPS_ConvertToSockAddr(&(stNodeTemp.uaddrDst.stAddrDst), sizeof(SOCKADDRIN_S));
                lRetCode = UDPS_DataHandle ( &stNodeTemp, pMBuf );   /*Deleted by hourufeng &stCtrlEncap,sizeof( FWD_TO_CTRL_HDR ) );*/
            }
            /*主备服务器状态都不正常,或只配主服务器主服务器不正常*/
            else
            {
                /*构造UDP头参数*/
                stNodeTemp.uaddrSrc.stAddrSrc.sin_stAddr.s_ulAddr = pstDhcpTmpCtrlBlk->ulAgetIP;
                if (g_ucSoftParaDHCPKPN & ((UCHAR)0x02))
                {
                    stNodeTemp.uaddrSrc.stAddrSrc.sin_usPort = DHCPS_PKT_PORTNO;
                }
                else
                {
                    stNodeTemp.uaddrSrc.stAddrSrc.sin_usPort = DHCPC_PKT_PORTNO;
                }
                stNodeTemp.uaddrDst.stAddrDst.sin_stAddr.s_ulAddr = stDhcpServer.aulPrimaryServerIp[0];
                stNodeTemp.uaddrDst.stAddrDst.sin_usPort = DHCPS_PKT_PORTNO;
                stNodeTemp.ulVpnId = stDhcpServer.ulVpnIndex;
                stNodeTemp.pData = (CHAR*)&stCtrlEncap;
                stNodeTemp.ulDataLen = sizeof( FWD_TO_CTRL_HDR );

                /*调用函数发送报文*/
                PGP_MemZero( &stCtrlEncap,sizeof( FWD_TO_CTRL_HDR ) );

                fwd_set_ctrlhdr_vcpuid(&stCtrlEncap,0);
                fwd_set_ctrlhdr_vrfindex(&stCtrlEncap,stDhcpServer.ulVpnIndex);
                fwd_set_ctrlhdr_msgcode(&stCtrlEncap,(ULONG)ucPktType);
                fwd_set_ctrlhdr_moduleid(&stCtrlEncap,MID_DHCPC);

                pstDhcpTmpCtrlBlk->ulSrvIp = stDhcpServer.aulPrimaryServerIp[0];

                //GTPC_DumpMessage(pMBuf->stDataBlockDescriptor.pucData,pMBuf->ulTotalDataLength);
                DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPC_OutPut : 44 GTPC_DumpMessage %u ; %d ; %u ; %d ; %u ; %u ;" ,
                             stNodeTemp.uaddrSrc.stAddrSrc.sin_stAddr.s_ulAddr,stNodeTemp.uaddrSrc.stAddrSrc.sin_usPort,stNodeTemp.uaddrDst.stAddrDst.sin_stAddr.s_ulAddr,
                             stNodeTemp.uaddrDst.stAddrDst.sin_usPort,stNodeTemp.ulVpnId,stCtrlEncap.ulVcpuId );
                stNodeTemp.uaddrDst.stAddrDst.sin_chFamily = AF_INET;
                stNodeTemp.uaddrSrc.stAddrSrc.sin_chFamily = AF_INET;
                (VOID)UDPS_ConvertToSockAddr(&(stNodeTemp.uaddrSrc.stAddrSrc), sizeof(SOCKADDRIN_S));
                (VOID)UDPS_ConvertToSockAddr(&(stNodeTemp.uaddrDst.stAddrDst), sizeof(SOCKADDRIN_S));
                lRetCode = UDPS_DataHandle ( &stNodeTemp, pMBuf );  /* Deleted by hourufeng &stCtrlEncap,sizeof( FWD_TO_CTRL_HDR ) );*/

            }

        }
        /* 以前发送过discover消息此处为重发 */
        else
        {
            /*构造UDP头参数*/
            stNodeTemp.uaddrSrc.stAddrSrc.sin_stAddr.s_ulAddr = pstDhcpTmpCtrlBlk->ulAgetIP;
            if (g_ucSoftParaDHCPKPN & ((UCHAR)0x02))
            {
                stNodeTemp.uaddrSrc.stAddrSrc.sin_usPort = DHCPS_PKT_PORTNO;
            }
            else
            {
                stNodeTemp.uaddrSrc.stAddrSrc.sin_usPort = DHCPC_PKT_PORTNO;
            }
            stNodeTemp.uaddrDst.stAddrDst.sin_stAddr.s_ulAddr = pstDhcpTmpCtrlBlk->ulSrvIp;
            stNodeTemp.uaddrDst.stAddrDst.sin_usPort = DHCPS_PKT_PORTNO;
            stNodeTemp.ulVpnId = stDhcpServer.ulVpnIndex;
            stNodeTemp.pData =(CHAR*) &stCtrlEncap;
            stNodeTemp.ulDataLen = sizeof( FWD_TO_CTRL_HDR );

            /*调用函数发送报文*/
            PGP_MemZero( &stCtrlEncap,sizeof( FWD_TO_CTRL_HDR ) );

            fwd_set_ctrlhdr_vcpuid(&stCtrlEncap,0);
            fwd_set_ctrlhdr_vrfindex(&stCtrlEncap,stDhcpServer.ulVpnIndex);
            fwd_set_ctrlhdr_msgcode(&stCtrlEncap,(ULONG)ucPktType);
            fwd_set_ctrlhdr_moduleid(&stCtrlEncap,MID_DHCPC);

            //GTPC_DumpMessage(pMBuf->stDataBlockDescriptor.pucData,pMBuf->ulTotalDataLength);
            DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n 55 DHCPC_OutPut :  GTPC_DumpMessage %u ; %d ; %u ; %d ; %u ; %u ;" ,
                         stNodeTemp.uaddrSrc.stAddrSrc.sin_stAddr.s_ulAddr,stNodeTemp.uaddrSrc.stAddrSrc.sin_usPort,stNodeTemp.uaddrDst.stAddrDst.sin_stAddr.s_ulAddr,
                         stNodeTemp.uaddrDst.stAddrDst.sin_usPort,stNodeTemp.ulVpnId,stCtrlEncap.ulVcpuId );
            stNodeTemp.uaddrDst.stAddrDst.sin_chFamily = AF_INET;
            stNodeTemp.uaddrSrc.stAddrSrc.sin_chFamily = AF_INET;
            (VOID)UDPS_ConvertToSockAddr(&(stNodeTemp.uaddrSrc.stAddrSrc), sizeof(SOCKADDRIN_S));
            (VOID)UDPS_ConvertToSockAddr(&(stNodeTemp.uaddrDst.stAddrDst), sizeof(SOCKADDRIN_S));
            lRetCode = UDPS_DataHandle ( &stNodeTemp, pMBuf );  /* Deleted by hourufeng &stCtrlEncap,sizeof( FWD_TO_CTRL_HDR ) );*/
        }

    }
    /*发送非Discover报文*/
    else
    {
        /* 发送其他报文的情况,除了发送Discover报文,其他报文都已经确定了服务器的IP地址,
            这里再去判断有些画蛇添足,此处只判断临时控制块内是否正确就可以了 */
        /*配置了DHCP Server*/
        /*如果DHCP 临时控制块中的Server IP既不等于主DHCP Server的IP也不等于备DHCP Server的IP*/
        if ( ( pstDhcpTmpCtrlBlk->ulSrvIp != stDhcpServer.aulPrimaryServerIp[0] )
             && ( pstDhcpTmpCtrlBlk->ulSrvIp != stDhcpServer.aulSecondaryServerIp[0] ) )
        {
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_052);
            /*调试信息*/
            DHCPC_DebugPrint(PTM_LOG_DEBUG,
                         "\r\nDHCPC_OutPut not discover configure DHCP Server IP isn't DHCP Control block Server IP!" );
            *plSecondReturnCode = VOS_ERR;
            return VOS_ERR;
        }

        /* zhangjinquan DTS2011080902075 根据问题单同步bit218处理 001 2011-12-01 start */
        DHCPC_SetReNewDhcpServerIp(pstDhcpTmpCtrlBlk, &stDhcpServer, &stDhcpServerStatus);
        /* zhangjinquan DTS2011080902075 根据问题单同步bit218处理 001 2011-12-01 end   */

        /*构造发往DHCP Server消息的UDP头参数*/
        /* 这里的源地址有些疑问,为什么要填代理地址呢?dhcp server填的代理地址会转到ggsn吗?
           还需要配置路由?pf 基于什么把dhcp的报文送上来的呢?
        */
        stNodeTemp.uaddrSrc.stAddrSrc.sin_stAddr.s_ulAddr = pstDhcpTmpCtrlBlk->ulAgetIP;
        if (g_ucSoftParaDHCPKPN & ((UCHAR)0x02))
        {
            stNodeTemp.uaddrSrc.stAddrSrc.sin_usPort = DHCPS_PKT_PORTNO;
        }
        else
        {
            stNodeTemp.uaddrSrc.stAddrSrc.sin_usPort = DHCPC_PKT_PORTNO;
        }
        stNodeTemp.uaddrDst.stAddrDst.sin_stAddr.s_ulAddr = pstDhcpTmpCtrlBlk->ulSrvIp;
        stNodeTemp.uaddrDst.stAddrDst.sin_usPort = DHCPS_PKT_PORTNO;
        stNodeTemp.ulVpnId = stDhcpServer.ulVpnIndex;
        stNodeTemp.pData = (CHAR*)&stCtrlEncap;
        stNodeTemp.ulDataLen = sizeof( FWD_TO_CTRL_HDR );

        PGP_MemZero( &stCtrlEncap,sizeof( FWD_TO_CTRL_HDR ) );

        fwd_set_ctrlhdr_vcpuid(&stCtrlEncap,0);
        fwd_set_ctrlhdr_vrfindex(&stCtrlEncap,stDhcpServer.ulVpnIndex);
        fwd_set_ctrlhdr_msgcode(&stCtrlEncap,(ULONG)ucPktType);
        fwd_set_ctrlhdr_moduleid(&stCtrlEncap,MID_DHCPC);

        //GTPC_DumpMessage(pMBuf->stDataBlockDescriptor.pucData,pMBuf->ulTotalDataLength);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n 66 DHCPC_OutPut :  GTPC_DumpMessage %u ; %d ; %u ; %d ; %u ; %u ;" ,
                     stNodeTemp.uaddrSrc.stAddrSrc.sin_stAddr.s_ulAddr,stNodeTemp.uaddrSrc.stAddrSrc.sin_usPort,stNodeTemp.uaddrDst.stAddrDst.sin_stAddr.s_ulAddr,
                     stNodeTemp.uaddrDst.stAddrDst.sin_usPort,stNodeTemp.ulVpnId,stCtrlEncap.ulVcpuId );
        stNodeTemp.uaddrDst.stAddrDst.sin_chFamily = AF_INET;
        stNodeTemp.uaddrSrc.stAddrSrc.sin_chFamily = AF_INET;
        (VOID)UDPS_ConvertToSockAddr(&(stNodeTemp.uaddrSrc.stAddrSrc), sizeof(SOCKADDRIN_S));
        (VOID)UDPS_ConvertToSockAddr(&(stNodeTemp.uaddrDst.stAddrDst), sizeof(SOCKADDRIN_S));
        lRetCode = UDPS_DataHandle ( &stNodeTemp, pMBuf );  /* Deleted by hourufeng &stCtrlEncap,sizeof( FWD_TO_CTRL_HDR ) );*/
    }

    /*为输入参数plSecondReturnCode赋值，只要向一个DHCP Server消息成功，该参数的值就置为VOS_OK*/
    if ( ( VOS_OK != lRetCode ) && ( VOS_OK != *plSecondReturnCode ) )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_053);
        *plSecondReturnCode = VOS_ERR;
        return VOS_ERR ;
    }
    else
    {
        *plSecondReturnCode = VOS_OK;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : DHCPC_ConstructPhyAddr
 功能描述  : 构造发送到DHCPserver的物理地址
 输入参数  : DHCPC_TEMPCTRLBLK* pstTempCtrlBlk
             UCHAR* szChaddr
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年11月21日
    作    者   : caopu 110903
    修改内容   :39号软参第3个bit为1，v1用户:MAC地址保持现有实现，使用IMSI的后十二位设置
                            第3个bit位为0，v1用户:MAC地址的第一个字节使用槽位号填充，第二个字节使用vcpu号填充，其余的四个字节使用TEIDC填充

                            39号软参第3个bit为1，v0用户保持现有实现不变:MAC地址保持现有实现，使用IMSI的后十二位设置
                            第3个bit位为0，v0用户保持现有实现不变:MAC地址的第一个字节使用槽位号填充，第二个字节使用vcpu号填充，其余的四个字节使用上下文索引填充
                                 -------------------------------------------------------------
*****************************************************************************/
VOID DHCPC_ConstructPhyAddr( DHCPC_TEMPCTRLBLK* pstTempCtrlBlk, UCHAR* szChaddr )
{
    int ii = 0;
    USHORT usGroup = 0;
    GTP_IMSI_S stImsi;
    ULONG ulNetOrderDHCPCtlIdx = 0;

    if (NULL == pstTempCtrlBlk)
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_054);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\nDHCPC_ConstructPhyAddr index invalid!" );
        VOS_Assert( 0 );
        return ;
    }

    if ( NULL == szChaddr )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_055);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\nDHCPC_ConstructPhyAddr szChaddr is null!" );
        VOS_Assert( 0 );
        return ;
    }

    usGroup = (USHORT)CRM_GetSelfGroupId();
    if (0 == usGroup)
    {
        return;
    }

    usGroup = VOS_HTONS(usGroup);
    ulNetOrderDHCPCtlIdx = VOS_HTONL(pstTempCtrlBlk->ulDHCPCtlIdx);

    VOS_MemSet(&stImsi,0,sizeof(GTP_IMSI_S));
    VOS_MemCpy(&stImsi,pstTempCtrlBlk->aulIMSI, 2 * sizeof(ULONG));

    for ( ii = 0; ii < DHCP_ETHERNETHARDWARELEN; ii++ )
    {
        szChaddr[ii] = 0;
    }

    /* BEGIN: Modified for PN:DS.UGWV9R9C02.EMC.PTM.0005 UGW9811 V900R009C02紧急呼叫特性by guolixian 00171003, 2012/2/9 */
    if((VOS_NULL_DWORD == pstTempCtrlBlk->aulIMSI[0])
        &&(VOS_NULL_DWORD == pstTempCtrlBlk->aulIMSI[1]))
    {
         /*组号+teidc*/
        VOS_MemCpy((UCHAR*)( szChaddr ),&(usGroup),sizeof(USHORT));
        VOS_MemCpy( ( UCHAR* )( szChaddr+2 ),&(ulNetOrderDHCPCtlIdx),sizeof( ULONG ) );
    }
    else if (g_ucSoftParaDHCPKPN & ((UCHAR)0x04))
    {
        /*根据IMSI 的存储结构，将后12位拷入*/
        *(szChaddr) = ((stImsi.MNC2 << 4  ) | (stImsi.MNC1 ));
        *(szChaddr+1) = ((stImsi.MSIN2 << 4 ) | (stImsi.MSIN1 ));
        *(szChaddr+2) = ((stImsi.MSIN4 << 4 ) | (stImsi.MSIN3 ));
        *(szChaddr+3) = ((stImsi.MSIN6 << 4 ) | (stImsi.MSIN5 ));
        *(szChaddr+4) = ((stImsi.MSIN8 << 4 ) | (stImsi.MSIN7 ));
        *(szChaddr+5) = ((stImsi.MSIN10 << 4 ) | (stImsi.MSIN9 ));
    }
    else
    {
        /*组号+teidc*/
        VOS_MemCpy((UCHAR*)( szChaddr ),&(usGroup),sizeof(USHORT));
        VOS_MemCpy( ( UCHAR* )( szChaddr+2 ),&(ulNetOrderDHCPCtlIdx),sizeof( ULONG ) );
    }
    /* END:   Modified for PN:DS.UGWV9R9C02.EMC.PTM.0005 UGW9811 V900R009C02紧急呼叫特性 by guolixian 00171003, 2012/2/9 */
    return;
}
/*****************************************************************************
 函 数 名  : DHCPC_GetDhcpCtrlBlk
 功能描述  : 动态申请DHCP控制块结构
 输入参数  : DHCPC_CTRLBLK **ppstDhcp_CtrlBlk
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年11月21日
    作    者   : caopu
    修改内容   : 新生成函数

*****************************************************************************/
ULONG DHCPC_GetDhcpCtrlBlk( DHCPC_CTRLBLK **ppstDhcpCtrlBlk )
{
    if ( NULL == ppstDhcpCtrlBlk )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_056);
        return VOS_ERR;
    }

    *ppstDhcpCtrlBlk = DHCP_Malloc( DHCPC_HANDLE, sizeof( DHCPC_CTRLBLK ) );
    if ( NULL == ( *ppstDhcpCtrlBlk ) )
    {
        return VOS_ERR;
    }

    PGP_MemZero( *ppstDhcpCtrlBlk, sizeof( DHCPC_CTRLBLK ) );
    return VOS_OK;
}
/*****************************************************************************
 函 数 名  : DHCPC_FreeDhcpCtrlBlk
 功能描述  : 释放DHCP控制块结构
 输入参数  : ULONG ulCtrlBlkIndex, ULONG ulTEIDC, UCHAR ucUser, ULONG ulPDPIndex
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年11月21日
    作    者   : caopu
    修改内容   : 新生成函数
  2.日    期   : 2010年08月06日
    作    者   : w00140934
    修改内容   : 修改控制块结构

*****************************************************************************/
VOID DHCPC_FreeDhcpCtrlBlk( ULONG ulCtrlBlkIndex, ULONG ulTEIDC, UCHAR ucUser, ULONG ulPDPIndex )
{
    ULONG ulHashKey = 0;
    DHCPC_CTRLBLK * pstPreDhcpcCtlBlk = NULL;
    DHCPC_CTRLBLK * pstCurDhcpcCtlBlk = NULL;

    ulHashKey = DHCPC_GetCtlBlkHashKey( ulCtrlBlkIndex );

    if ( NULL == g_pstDhcpcCtrlBlkRec[ulHashKey] )
    {
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPC_FreeDhcpCtrlBlk g_pstDhcpcCtrlBlkRec[ulHashKey] is null!" );
        return;
    }

    /*如果要删除的是第一个结点*/
    pstCurDhcpcCtlBlk = g_pstDhcpcCtrlBlkRec[ulHashKey];
    if (pstCurDhcpcCtlBlk->ulTEIDC == ulTEIDC)
    {
        /* DHCP Lease backup  删除，在租约超时函数中处理--w00140934*/
        //DHCPC_Delete_BackupChain(ulCtrlBlkIndex);
        g_pstDhcpcCtrlBlkRec[ulHashKey] = pstCurDhcpcCtlBlk->pstNextNode;
        DHCP_Free( DHCPC_HANDLE, pstCurDhcpcCtlBlk );
        /* zhangjinquan DTS2011073004013 释放后置空 */
        pstCurDhcpcCtlBlk = NULL;
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n--> DHCPC_FreeDhcpCtrlBlk ulCtrlBlkIndex OK" );
        return;
    }

    pstPreDhcpcCtlBlk = pstCurDhcpcCtlBlk;
    pstCurDhcpcCtlBlk = pstCurDhcpcCtlBlk->pstNextNode;

    /* 遍历HASHKEY相等的控制块*/
    while ( NULL != pstCurDhcpcCtlBlk )
    {
        /* V1用户,如果TEIDC相等则找到了要删除的控制块*/
        if (pstCurDhcpcCtlBlk->ulTEIDC == ulTEIDC)
        {
            /* DHCP Lease backup  删除，在租约超时函数中处理--w00140934*/
            //DHCPC_Delete_BackupChain(ulCtrlBlkIndex);
            pstPreDhcpcCtlBlk->pstNextNode = pstCurDhcpcCtlBlk->pstNextNode;
            DHCP_Free( DHCPC_HANDLE, pstCurDhcpcCtlBlk );
            /* zhangjinquan DTS2011073004013 释放后置空 */
            pstCurDhcpcCtlBlk = NULL;
            DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n--> DHCPC_FreeDhcpCtrlBlk ulCtrlBlkIndex OK" );
            return;
        }

        pstPreDhcpcCtlBlk = pstCurDhcpcCtlBlk;
        pstCurDhcpcCtlBlk = pstCurDhcpcCtlBlk->pstNextNode;
    }

    /*没有找到要删除的结点*/
    DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPC_FreeDhcpCtrlBlk there is no DhcpcCtrlBlkRec!" );
    return;
}

/*****************************************************************************
 函 数 名  : DHCPC_EncapBackBlkByCtrlBlk
 功能描述  : 根据dhcp控制块封装dhcp备份块
 输入参数  : UCHAR ucIpType                   地址类型.IPV4、IPV6
             DHCPC_CTRLBLK *pstDhcpCtrlBlk    dhcp控制块
             DHCPC_BACK_BLK_S *pstDhcpBackBlk dhcp备份块
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月26日
    作    者   : jixiaoming 00180244
    修改内容   : 新生成函数

*****************************************************************************/
VOID DHCPC_EncapBackBlkByCtrlBlk(UCHAR ucIpType, DHCPC_CTRLBLK *pstDhcpCtrlBlk,
                                        DHCPC_BACK_BLK_S *pstDhcpBackBlk)
{
    pstDhcpBackBlk->aulMSISDN[0] = pstDhcpCtrlBlk->aulMSISDN[0];
    pstDhcpBackBlk->aulMSISDN[1] = pstDhcpCtrlBlk->aulMSISDN[1];

    pstDhcpBackBlk->aulIMSI[0] = pstDhcpCtrlBlk->aulIMSI[0];
    pstDhcpBackBlk->aulIMSI[1] = pstDhcpCtrlBlk->aulIMSI[1];

    pstDhcpBackBlk->aulIMEI[0] = pstDhcpCtrlBlk->aulIMEI[0];
    pstDhcpBackBlk->aulIMEI[1] = pstDhcpCtrlBlk->aulIMEI[1];

    pstDhcpBackBlk->ulLease = pstDhcpCtrlBlk->ulLease;
    pstDhcpBackBlk->ulTimeStamp = pstDhcpCtrlBlk->ulTimeStamp;
    pstDhcpBackBlk->ulTEIDC = pstDhcpCtrlBlk->ulTEIDC;
    pstDhcpBackBlk->ulPDPIndex = pstDhcpCtrlBlk->ulPDPIndex;
    pstDhcpBackBlk->usVPNIndex = pstDhcpCtrlBlk->usVPNIndex;
    pstDhcpBackBlk->usPoolIndex = pstDhcpCtrlBlk->usPoolIndex;
    pstDhcpBackBlk->usServerGrpIndex = pstDhcpCtrlBlk->usServerGrpIndex;
    pstDhcpBackBlk->usApnIndex = pstDhcpCtrlBlk->usApnIndex;
    pstDhcpBackBlk->ucLAPNo = pstDhcpCtrlBlk->ucLAPNo;
    pstDhcpBackBlk->ucRandomNo = pstDhcpCtrlBlk->ucRandomNo;
    pstDhcpBackBlk->ucRole = pstDhcpCtrlBlk->ucRole;
    pstDhcpBackBlk->usDhcpStatus = pstDhcpCtrlBlk->usDhcpStatus;

    if (LAP_IPV4 == ucIpType)
    {
        pstDhcpBackBlk->unBakInfo.stDhcpv4.ulAgentIpAddr = pstDhcpCtrlBlk->aulAgentIpAddr[0];
        pstDhcpBackBlk->unBakInfo.stDhcpv4.ulUserIpAddr = pstDhcpCtrlBlk->aulUserIpAddr[0];
        pstDhcpBackBlk->unBakInfo.stDhcpv4.ulServerIp = pstDhcpCtrlBlk->aulSrvIp[0];
    }
    else
    {
        pstDhcpBackBlk->unBakInfo.stDhcpv6.ulT1 = pstDhcpCtrlBlk->ulT1;
        pstDhcpBackBlk->unBakInfo.stDhcpv6.ulT2 = pstDhcpCtrlBlk->ulT2;
        pstDhcpBackBlk->unBakInfo.stDhcpv6.ucLeaseStatus = pstDhcpCtrlBlk->ucLeaseStatus;
        pstDhcpBackBlk->unBakInfo.stDhcpv6.ucResource = pstDhcpCtrlBlk->ucResource;
        pstDhcpBackBlk->unBakInfo.stDhcpv6.ucCurrentServer = pstDhcpCtrlBlk->ucCurrentServer;

        VOS_MemCpy(pstDhcpBackBlk->unBakInfo.stDhcpv6.aulAgentIpAddr, pstDhcpCtrlBlk->aulAgentIpAddr,
                    sizeof(ULONG) * LAP_IP_ULONG_NUM);
        VOS_MemCpy(pstDhcpBackBlk->unBakInfo.stDhcpv6.aulUserIpAddr, pstDhcpCtrlBlk->aulUserIpAddr,
                    sizeof(ULONG) * LAP_IP_ULONG_NUM);
        VOS_MemCpy(pstDhcpBackBlk->unBakInfo.stDhcpv6.aucSiDuid, pstDhcpCtrlBlk->aucSiDuid,
                    sizeof(UCHAR) * DHCPV6C_MAX_DUID_LEN);
    }

    return;
}

/*****************************************************************************
 函 数 名  : DHCPC_FillCtrlBlkByBackBlk
 功能描述  : 将dhcp备份块中的内容填入dhcp控制块
 输入参数  : UCHAR ucIpType
             DHCPC_CTRLBLK *pstDhcpCtrlBlk
             DHCPC_BACK_BLK_S *pstDhcpBackBlk
 输出参数  : 无
 返 回 值  : ULONG
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月26日
    作    者   : jixiaoming 00180244
    修改内容   : 新生成函数

*****************************************************************************/
VOID DHCPC_FillCtrlBlkByBackBlk(UCHAR ucIpType, DHCPC_CTRLBLK *pstDhcpCtrlBlk,
                                        DHCPC_BACK_BLK_S *pstDhcpBackBlk)
{
    pstDhcpCtrlBlk->aulMSISDN[0] = pstDhcpBackBlk->aulMSISDN[0];
    pstDhcpCtrlBlk->aulMSISDN[1] = pstDhcpBackBlk->aulMSISDN[1];

    pstDhcpCtrlBlk->aulIMSI[0] = pstDhcpBackBlk->aulIMSI[0];
    pstDhcpCtrlBlk->aulIMSI[1] = pstDhcpBackBlk->aulIMSI[1];

    pstDhcpCtrlBlk->aulIMEI[0] = pstDhcpBackBlk->aulIMEI[0];
    pstDhcpCtrlBlk->aulIMEI[1] = pstDhcpBackBlk->aulIMEI[1];

    pstDhcpCtrlBlk->ulTEIDC = pstDhcpBackBlk->ulTEIDC;
    pstDhcpCtrlBlk->ulLease = pstDhcpBackBlk->ulLease;
    pstDhcpCtrlBlk->ulTimeStamp = pstDhcpBackBlk->ulTimeStamp;
    pstDhcpCtrlBlk->ulPDPIndex = pstDhcpBackBlk->ulPDPIndex;
    pstDhcpCtrlBlk->usVPNIndex = pstDhcpBackBlk->usVPNIndex;
    pstDhcpCtrlBlk->usPoolIndex = pstDhcpBackBlk->usPoolIndex;
    pstDhcpCtrlBlk->usServerGrpIndex = pstDhcpBackBlk->usServerGrpIndex;
    pstDhcpCtrlBlk->usApnIndex = pstDhcpBackBlk->usApnIndex;
    pstDhcpCtrlBlk->ucLAPNo = pstDhcpBackBlk->ucLAPNo;
    pstDhcpCtrlBlk->ucRandomNo = pstDhcpBackBlk->ucRandomNo;
    pstDhcpCtrlBlk->ucRole = pstDhcpBackBlk->ucRole;
    pstDhcpCtrlBlk->ucIpType = ucIpType;

    if (LAP_IPV4 == ucIpType)
    {
        pstDhcpCtrlBlk->aulAgentIpAddr[0] = pstDhcpBackBlk->unBakInfo.stDhcpv4.ulAgentIpAddr;
        pstDhcpCtrlBlk->aulUserIpAddr[0] = pstDhcpBackBlk->unBakInfo.stDhcpv4.ulUserIpAddr;
        pstDhcpCtrlBlk->aulSrvIp[0] = pstDhcpBackBlk->unBakInfo.stDhcpv4.ulServerIp;
        pstDhcpCtrlBlk->usDhcpStatus = DHCPC_STATE_BOUND;    /* 备份重建的直接复制为稳态,目前因为时序的问题,可能会重建一些非稳态的控制块 */
    }
    else
    {
        pstDhcpCtrlBlk->ulT1 = pstDhcpBackBlk->unBakInfo.stDhcpv6.ulT1;
        pstDhcpCtrlBlk->ulT2 = pstDhcpBackBlk->unBakInfo.stDhcpv6.ulT2;
        pstDhcpCtrlBlk->ucLeaseStatus = pstDhcpBackBlk->unBakInfo.stDhcpv6.ucLeaseStatus;
        pstDhcpCtrlBlk->ucResource = pstDhcpBackBlk->unBakInfo.stDhcpv6.ucResource;
        pstDhcpCtrlBlk->ucCurrentServer = pstDhcpBackBlk->unBakInfo.stDhcpv6.ucCurrentServer;
        pstDhcpCtrlBlk->usDhcpStatus = DHCPV6C_STATE_BOUND;  /* 备份重建的直接复制为稳态,目前因为时序的问题,可能会重建一些非稳态的控制块 */

        VOS_MemCpy(pstDhcpCtrlBlk->aulAgentIpAddr, pstDhcpBackBlk->unBakInfo.stDhcpv6.aulAgentIpAddr,
                    sizeof(ULONG) * LAP_IP_ULONG_NUM);
        VOS_MemCpy(pstDhcpCtrlBlk->aulUserIpAddr, pstDhcpBackBlk->unBakInfo.stDhcpv6.aulUserIpAddr,
                    sizeof(ULONG) * LAP_IP_ULONG_NUM);
        VOS_MemCpy(pstDhcpCtrlBlk->aucSiDuid, pstDhcpBackBlk->unBakInfo.stDhcpv6.aucSiDuid,
                    sizeof(UCHAR) * DHCPV6C_MAX_DUID_LEN);
        DHCP_MemZero(pstDhcpCtrlBlk->aulMainDnsAddr, sizeof(ULONG) * 4);
        DHCP_MemZero(pstDhcpCtrlBlk->aulSecdDnsAddr, sizeof(ULONG) * 4);
    }

    /* 初始化剩余部分 */
    pstDhcpCtrlBlk->pTmpDhcpCtrlBlkPtr = NULL;
    pstDhcpCtrlBlk->ulDHCPCtxIdx = pstDhcpBackBlk->ulTEIDC;
    pstDhcpCtrlBlk->ulTmpVar = 0;
    pstDhcpCtrlBlk->usSeqNum = 0;
    pstDhcpCtrlBlk->ucUserType = 0;
    pstDhcpCtrlBlk->ucUser = 0;
    pstDhcpCtrlBlk->ucCurSvrSendCount = 0;
    pstDhcpCtrlBlk->ucTotalSendCount = 0;
    pstDhcpCtrlBlk->ucResendTimeout = 0;
    pstDhcpCtrlBlk->ucWaitRspTimeOutNum = 0;
    pstDhcpCtrlBlk->ucAgingFlag = 0;
    pstDhcpCtrlBlk->ucCause = DHCPV6C_CAUSE_DEFAULT;

    return ;
}

/*****************************************************************************
 函 数 名  : DHCPC_OutPut
 功能描述  : DHCPC模块控制块备份函数，从DHCP控制块数组中取出待备份的DHCP控制块，并将其放入备份结构中
 输入参数  : char **ppbuff, ULONG ulIndex, ULONG ulTEIDC, UCHAR ucUser, ULONG ulPDPIndex
 输出参数  : 无
 返 回 值  : ULONG
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年12月26日
    作    者   : caopu
    修改内容   : 新生成函数

  2.日    期   : 2012年07月27日
    作    者   : tianyang 00144555
    修改内容   : 增加DHCPV6特性

*****************************************************************************/
ULONG DHCPC_BackupProc( char **ppbuff, UCHAR ucIpType, ULONG ulTEIDC)
{
    ULONG ulRet = 0;
    DHCPC_CTRLBLK *pstDhcpCtrlBlk = NULL;

    /*入口参数检查*/
    if ( NULL == ppbuff || NULL == *ppbuff )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_059);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "master DhcpCtrlBlk backup err1!" );
        return VOS_ERR;
    }

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "iptype=%d teidc=0x%x!", ucIpType, ulTEIDC);

    if ( (LAP_IPV4 != ucIpType) && (LAP_IPV6 != ucIpType) )
    {
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_BAK_IPTYPEERR);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "In DHCPC_BackupProc input iptype err! iptype:%d", ucIpType);
        return VOS_ERR;
    }

    /* 获取dhcp控制块 */
    if ( LAP_IPV4 == ucIpType )
    {
        /*dhcp控制块索引:v0用户传入的是上下文索引;V1用户传入的是TEIDC*/
        pstDhcpCtrlBlk = (DHCPC_CTRLBLK *)DHCPC_CalcCtlBlkHashValue(ulTEIDC, ulTEIDC);
        if ( NULL == pstDhcpCtrlBlk )
        {
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_060);
            DHCPC_DebugPrint(PTM_LOG_DEBUG, "master DhcpCtrlBlk backup for Dhcpv4 err2!" );
            return VOS_ERR;
        }
    }
    else
    {
        pstDhcpCtrlBlk = NULL;

        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_BAK_IPV6);

        /*dhcp控制块索引:v0用户传入的是上下文索引;V1用户传入的是TEIDC*/
        ulRet = DHCPC_QueryDhcpcContext(LAP_IPV6, ulTEIDC, &pstDhcpCtrlBlk);
        if ( VOS_OK != ulRet )
        {
            DHCPC_DebugPrint(PTM_LOG_DEBUG, "master DhcpCtrlBlk backup for Dhcpv6 err2 ulTEIDC:%u!",ulTEIDC );
            return VOS_ERR;
        }
    }

    /* 封装备份块 */
    DHCPC_EncapBackBlkByCtrlBlk(ucIpType, pstDhcpCtrlBlk, (DHCPC_BACK_BLK_S *)(*ppbuff));
    *ppbuff += sizeof(DHCPC_BACK_BLK_S);

    /* 计数 */
    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : DHCPC_BkRestoreProcforV4
 功能描述  : 处理DHCPCV4备份函数，“封装老函数”
 输入参数  : char **ppbuff
             UCHAR ucIpType
             ULONG ulTEIDC
 输出参数  : 无
 返 回 值  : ULONG
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年7月30日
    作    者   : tianyang 00144555
    修改内容   : 新生成函数

*****************************************************************************/
ULONG DHCPC_BkRestoreProcforV4( char **ppbuff, UCHAR ucIpType, ULONG ulTEIDC )
{
    DHCPC_CTRLBLK *pstDhcpcCtlBlk = NULL;
    ULONG ulRetValue = 0;
    ULONG ulHashKey = 0;
    DHCPC_CTRLBLK *pstCtrlBlk = NULL;

    /*根据控制块索引计算HASHKEY*/
    ulHashKey = DHCPC_GetCtlBlkHashKey( ulTEIDC );
    /*dhcp控制块索引:v0用户传入的是上下文索引;V1用户传入的是TEIDC*/
    pstCtrlBlk = (DHCPC_CTRLBLK *)DHCPC_CalcCtlBlkHashValue(ulTEIDC, ulTEIDC);
    if ( NULL != pstCtrlBlk )
    {
        /*如果当前要备份的目标控制不为空，则先释放内存，后面再重新分配*/
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "slave DhcpCtrlBlk backup err3!" );
        DHCPC_FreeDhcpCtrlBlk( ulTEIDC, pstCtrlBlk->ulTEIDC, pstCtrlBlk->ucUser, pstCtrlBlk->ulPDPIndex);
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_317);
    }

    ulRetValue = DHCPC_GetDhcpCtrlBlk( &pstDhcpcCtlBlk );
    if ( VOS_OK != ulRetValue )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_062);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "get null DhcpCtrlBlk!" );
        return VOS_ERR;
    }

    DHCPC_FillCtrlBlkByBackBlk(LAP_IPV4, pstDhcpcCtlBlk, (DHCPC_BACK_BLK_S *)(*ppbuff));

    pstDhcpcCtlBlk->ulTmpVar = 0;

    /*将新结点插入到第一个位置*/
    pstDhcpcCtlBlk->pstNextNode = g_pstDhcpcCtrlBlkRec[ulHashKey];
    g_pstDhcpcCtrlBlkRec[ulHashKey] = pstDhcpcCtlBlk;

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "ok!" );
    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : DHCPC_BkRestoreProcforV6
 功能描述  : 处理DHCPCV6备份函数
 输入参数  : char **ppbuff
             UCHAR ucIpType
             ULONG ulTEIDC
 输出参数  : 无
 返 回 值  : ULONG
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年7月30日
    作    者   : tianyang 00144555
    修改内容   : 新生成函数

*****************************************************************************/
ULONG DHCPC_BkRestoreProcforV6( char **ppbuff, UCHAR ucIpType, ULONG ulTEIDC )
{
    ULONG ulRet = 0;
    DHCPC_CTRLBLK *pstCtrlBlk = NULL;
    DHCPV6C_PRE_RESULT_S stPreResult = {0};

    DHCPV6C_DBGCNT_ADD(E_DHCPV6C_BAKRESTORE);

    /* 状态不对,不进行备份 */
    /*BEGIN DTS2012101907734 判断条件修改为DHCPv6控制块状态 by mengyuanhui 00221593*/
    if (DHCPV6C_STATE_BOUND != ((DHCPC_BACK_BLK_S *)(*ppbuff))->usDhcpStatus)
    {
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_BAKRESTORE_STAT_ERR);
        DHCPC_DebugPrint(PTM_LOG_INFO, "\r\n state (%u) !", ((DHCPC_BACK_BLK_S *)(*ppbuff))->usDhcpStatus);
        //return VOS_ERR; 暂时删除
    }
    /*END DTS2012101907734 判断条件修改为DHCP控制块状态 by mengyuanhui 00221593*/

    (VOID)DHCPC_QueryDhcpcContext(LAP_IPV6, ulTEIDC, &pstCtrlBlk);
    if ( NULL != pstCtrlBlk )
    {
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_BAKRESTORE_RENEW);
        /*如果当前要备份的目标控制不为空，则先释放内存，后面再重新分配*/
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\npstCtrlBlk is not null ulTEDIC:%u!", ulTEIDC );

        /* 删除控制块定时器 */
        if ( CRM_GetSpuWorkModeOfSelfGroup() == CRM_BKUP_N_PLUS_1 )
        {
            ulRet = DHCPV6C_StopLeaseTimer(pstCtrlBlk);
            if ( VOS_OK != ulRet )
            {
                DHCPV6C_DBGCNT_ADD(E_DHCPV6C_BAKRESTORE_STOPTIMERR);
            }
        }


        ulRet = DHCPC_FreeDhcpcContext(LAP_IPV6, pstCtrlBlk->ulTEIDC);
        if ( VOS_OK != ulRet )
        {
            DHCPV6C_DBGCNT_ADD(E_DHCPV6C_BAKRESTORE_DELEERR);
            return VOS_ERR;
        }
    }

    ulRet = DHCPC_MallocDhcpcContext(LAP_IPV6, ((DHCPC_BACK_BLK_S *)(*ppbuff))->ulTEIDC, &pstCtrlBlk);
    if ( VOS_OK != ulRet )
    {
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_BAKRESTORE_CRTERR);
        return VOS_ERR;
    }

    DHCPC_FillCtrlBlkByBackBlk(LAP_IPV6, pstCtrlBlk, (DHCPC_BACK_BLK_S *)(*ppbuff));

    /* 定时器重建 */
    if (E_CRM_ACTIVE != CRM_GetSlotPrimaryInfoOfSelfGroup((UCHAR)CRM_GetSelfLogicSlotID()))
    {
        /* 如果是备板,不需要重建定时器 */
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "ok!" );
        return VOS_OK;
    }

    DHCPV6C_DBGCNT_ADD(E_DHCPV6C_CNT_TRC_1);

    /* 运行到此处有2种情况:
     * 1、N+1 Standby升为Active后。该单板所有的定时器都在此处重建。
     * 2、1+1 Standby升为Active后,需要处理部分在本板为Standby状态时接受的备份消息,
     *    因为此时已经变为主板,需要启动定时器。
     */
    ulRet = DHCPV6C_TimerRestoreProc(pstCtrlBlk);
    if ( VOS_OK != ulRet )
    {
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_BAKRESTORE_TIMERR);

        pstCtrlBlk->ucLeaseStatus = DHCPV6C_LEASE_STATE_BUTT;

        stPreResult.pstDhcpcContext = pstCtrlBlk;
        stPreResult.pMsg = NULL;
        stPreResult.enEvent = DHCPV6C_EV_IP_RELEASE;

        /* 运行状态机 */
        DHCPV6C_RunFsm(&stPreResult);
    }

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "ulRet=%u!", ulRet );
    return ulRet;
}
/*****************************************************************************
 函 数 名  : DHCPC_OutPut
 功能描述  : DHCPC模块控制块在备板的备份恢复重建函数，从备份结构中取出待备份
             的DHCP控制块内容，并将其放入DHCP控制块数组中
 输入参数  : char **ppbuff, ULONG ulIndex, ULONG ulTEIDC, UCHAR ucUser, ULONG ulPDPIndex
 输出参数  : 无
 返 回 值  : ULONG
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年12月26日
    作    者   : caopu
    修改内容   : 新生成函数

  2.日    期   : 2012年07月27日
    作    者   : tianyang 00144555
    修改内容   : 增加DHCPV6特性,封装老的DHCPV4处理功能

*****************************************************************************/
ULONG DHCPC_BKRestoreProc( char **ppbuff, UCHAR ucIpType, ULONG ulTEIDC )
{
    ULONG ulRetValue = 0;

    /*入口参数检查*/
    if ( NULL == ppbuff || NULL == *ppbuff )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_058);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n master DhcpCtrlBlk backup err1!" );
        return VOS_ERR;
    }

    if ( (LAP_IPV4 != ucIpType) && (LAP_IPV6 != ucIpType) )
    {
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_BAKRESTORE_IPTYPEERR);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n In DHCPC_BKRestoreProc input iptype err! iptype:%d", ucIpType);
        return VOS_ERR;
    }

    DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_315);

    if (LAP_IPV4 == ucIpType)
    {
        ulRetValue = DHCPC_BkRestoreProcforV4(ppbuff, ucIpType, ulTEIDC);
        if ( VOS_OK != ulRetValue )
        {
            /* 计数 */
        }
    }
    else
    {
        ulRetValue = DHCPC_BkRestoreProcforV6(ppbuff, ucIpType, ulTEIDC);
        if ( VOS_OK != ulRetValue )
        {
            /* 计数 */
        }
    }

    /* 不管成功失败都要进行偏移 */
    *ppbuff += sizeof(DHCPC_BACK_BLK_S);

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n slave DhcpCtrlBlk backup succ!" );

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : DHCPC_BKDeleteProc
 功能描述  : DHCPC模块控制块在备板的备份删除函数，从备份结构中取出待备份的DHCP
             控制块内容，并将其放入DHCP控制块数组中
 输入参数  : char **ppbuff, ULONG ulIndex, ULONG ulTEIDC, UCHAR ucUser, ULONG ulPDPIndex
 输出参数  : 无
 返 回 值  : ULONG
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年12月26日
    作    者   : caopu
    修改内容   : 新生成函数

  2.日    期   : 2012年07月31日
    作    者   : caopu
    修改内容   : 新生成函数

*****************************************************************************/
ULONG DHCPC_BKDeleteProc( UCHAR ucIpType, ULONG ulTEIDC, UCHAR ucUser, ULONG ulPDPIndex )
{
    ULONG ulRet = 0;
    DHCPC_CTRLBLK *pstDhcpcCtlBlk = NULL;

    /*dhcp控制块索引:v0用户传入的是上下文索引;V1用户传入的是TEIDC*/
    DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_318);

    if ( LAP_IPV4 == ucIpType )
    {
        pstDhcpcCtlBlk = (DHCPC_CTRLBLK *)DHCPC_CalcCtlBlkHashValue(ulTEIDC, ulTEIDC);
        if ( NULL == pstDhcpcCtlBlk )
        {
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_066);
            return VOS_ERR;
        }

        /*释放控制块内存，删除节点*/
        DHCPC_FreeDhcpCtrlBlk( ulTEIDC, ulTEIDC, ucUser, ulPDPIndex );
    }

    if ( LAP_IPV6 == ucIpType )
    {
        pstDhcpcCtlBlk = NULL;

        ulRet = DHCPC_QueryDhcpcContext(LAP_IPV6, ulTEIDC, &pstDhcpcCtlBlk);
        if ( VOS_OK != ulRet )
        {
            DHCPV6C_DBGCNT_ADD(E_DHCPV6C_BAKDEL_NOTFOUND);
            return VOS_ERR;
        }

        ulRet = DHCPC_FreeDhcpcContext(LAP_IPV6, pstDhcpcCtlBlk->ulTEIDC);
        if ( VOS_OK != ulRet )
        {
            DHCPV6C_DBGCNT_ADD(E_DHCPV6C_BAKDEL_FREEFAIL);
            return VOS_ERR;
        }
    }

    return VOS_OK;
}
/*****************************************************************************
 函 数 名  : DHCPC_Delete_BackupChain
 功能描述  : 从备份链表中删除节点
 输入参数  : DHCP控制块索引
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年07月30日
    作    者   : jiahuidong 00142544
    修改内容   : 新生成函数

*****************************************************************************/
VOID DHCPC_Delete_BackupChain(ULONG ulCtrlBlkIndex)
{
    return ;
}

/*****************************************************************************
 函 数 名  : DHCPC_NotifyBKUpdate
 功能描述  : 通知CKP更新备份的dhcp控制块
 输入参数  : DHCPC_CTRLBLK *
 输出参数  : 无
 返 回 值  : VOS_OK  正常结束
             VOS_ERR 通知备份失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年07月22日
    作    者   : jixiaoming
    修改内容   : 新生成函数

*****************************************************************************/
ULONG DHCPC_NotifyBKUpdate(ULONG ulTeidc)
{
    ULONG ulRet = 0;
    SDB_GSPU_CONTEXT_S * pstContext = NULL;

    /* 获取1个上下文 */
    pstContext = DHCPC_GetOneContextByteidc(ulTeidc);
    if (NULL == pstContext)
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_262);
        return VOS_ERR;
    }

    /* 调用接口通知ckp更新dhcp控制块备份 */
    ulRet = AM_USM_NotifyBackupByIndex(pstContext->ulGspuBdIndex, SDB_UPDATEVERNOTCHANGE_BACKUP);
    if (SDB_SUCCESS != ulRet)
    {
        DHCPC_DebugPrint(PTM_LOG_ERR, "DHCPC_NotifyBKUpdate: call AM_USM_NotifyBackupByIndex failed!! ulRet = %u", ulRet);
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_261);
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : DHCPC_GetDiffTimeToCur
 功能描述  : 获取从时间戳到当前时间的时间差
 输入参数  : ULONG ulStampTime
 输出参数  : 无
 返 回 值  : ULONG
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月25日
    作    者   : tianyang 00144555
    修改内容   : 新生成函数

*****************************************************************************/
ULONG DHCPC_GetDiffTimeToCur(ULONG ulStampTime)
{
    ULONG ulCurTimeInSec = 0;

    /* 获取当前时间 */
    (VOID)PGP_TmNowInSec(&ulCurTimeInSec);
    if ( ulCurTimeInSec < ulStampTime )
    {
        /* 时间翻转 */
        return ulCurTimeInSec + (0xFFFFFFFF - ulStampTime);
    }
    else
    {
        return ulCurTimeInSec - ulStampTime;
    }
}

/*****************************************************************************
 函 数 名  : DHCPV6C_TimerRestoreProc
 功能描述  : 1+1备板定时器重建，N+1备升主时定时器重建
 输入参数  : DHCPC_CTRLBLK *pstDhcpcCtlBlk
 输出参数  : 无
 返 回 值  : ULONG
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月3日
    作    者   : tianyang 00144555
    修改内容   : 新生成函数

*****************************************************************************/
ULONG DHCPV6C_TimerRestoreProc(DHCPC_CTRLBLK *pstDhcpcCtlBlk)
{
    ULONG ulRet = VOS_OK;
    ULONG ulT1 = 0;
    ULONG ulT2 = 0;
    ULONG ulDiffTime = 0;

    ulDiffTime = DHCPC_GetDiffTimeToCur(pstDhcpcCtlBlk->ulTimeStamp);

    ulT1 = DHCPV6C_GetT1(pstDhcpcCtlBlk);
    ulT2 = DHCPV6C_GetT2(pstDhcpcCtlBlk);

    if ( DHCPC_INFINITY_TIME == pstDhcpcCtlBlk->ulLease )
    {
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_TIMRES_NOTRESTORE);
        pstDhcpcCtlBlk->ucLeaseStatus = DHCPV6C_LEASE_STATE_BUTT;
        return VOS_OK;
    }

    /*首先根据T1来判断定时器类型*/
    /*T1>租期属于异常情况，应到期释放*/
    if (ulT1 >= pstDhcpcCtlBlk->ulLease)
    {
        /* 重建租约定时器 */
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_TIMRES_EXTIM);
        ulRet = DHCPV6C_LeaseExpireTimerRestoreProc(ulDiffTime, pstDhcpcCtlBlk);
    }
    else if (ulT1 > ulDiffTime)
    {
        /* 重建T1定时器 */
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_TIMRES_T1TIM);
        ulRet = DHCPV6C_T1TimerRestoreProc(ulT1, ulDiffTime, pstDhcpcCtlBlk);
    }
    /*过T1，根据T2判断定时器类型*/
    /*T2>租期属于异常情况，T2<租约时间*/
    else if ((ulT2 >= pstDhcpcCtlBlk->ulLease) || (ulT2 <= ulDiffTime))
    {
        /* 重建租约定时器 */
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_TIMRES_EXTIM);
        ulRet = DHCPV6C_LeaseExpireTimerRestoreProc(ulDiffTime, pstDhcpcCtlBlk);
    }
    else
    {
        /* 重建T2定时器 */
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_TIMRES_T2TIM);
        ulRet = DHCPV6C_T2TimerRestoreProc(ulDiffTime, pstDhcpcCtlBlk);
    }

    return ulRet;
}

/*****************************************************************************
 函 数 名  : DHCPV6C_T1TimerRestoreProc
 功能描述  : T1定时器重建
 输入参数  : ULONG ulT1
             ULONG ulDiffTime
             DHCPC_CTRLBLK *pstDhcpcCtlBlk
 输出参数  : 无
 返 回 值  : ULONG
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月3日
    作    者   : tianyang 00144555
    修改内容   : 新生成函数

*****************************************************************************/
ULONG DHCPV6C_T1TimerRestoreProc(ULONG ulT1, ULONG ulDiffTime, DHCPC_CTRLBLK *pstDhcpcCtlBlk)
{
    ULONG ulRet = 0;
    ULONG ulTimerInterval = 0;

    if ( NULL == pstDhcpcCtlBlk )
    {
        VOS_DBGASSERT(0);
        return VOS_ERR;
    }

    ulTimerInterval = ulT1 - ulDiffTime;
    pstDhcpcCtlBlk->ucLeaseStatus = DHCPV6C_LEASE_STATE_WAIT_T1;

    ulRet = DHCPC_StartTimer(pstDhcpcCtlBlk->ucIpType, pstDhcpcCtlBlk->ulTEIDC,
                                DHCPV6C_EV_TIMER_RENEW, ulTimerInterval, DHCPC_TimerCallBack);
    return ulRet;
}

/*****************************************************************************
 函 数 名  : DHCPV6C_T2TimerRestoreProc
 功能描述  : T2定时器重建
 输入参数  : ULONG ulT1
             ULONG ulDiffTime
             DHCPC_CTRLBLK *pstDhcpcCtlBlk
 输出参数  : 无
 返 回 值  : ULONG
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月3日
    作    者   : tianyang 00144555
    修改内容   : 新生成函数

*****************************************************************************/
ULONG DHCPV6C_T2TimerRestoreProc(ULONG ulDiffTime, DHCPC_CTRLBLK *pstDhcpcCtlBlk)
{
    ULONG ulT2 = 0;
    ULONG ulRet = 0;
    ULONG ulTimerInterval = 0;

    if ( NULL == pstDhcpcCtlBlk )
    {
        VOS_DBGASSERT(0);
        return VOS_ERR;
    }

    ulT2 = DHCPV6C_GetT2(pstDhcpcCtlBlk);

    if ( ulT2 <= ulDiffTime )
    {
        /* 如果当前时间到T1超时的时间差已经超过T2，则启动租约定时器 */
        ulRet = DHCPV6C_LeaseExpireTimerRestoreProc(ulDiffTime, pstDhcpcCtlBlk);

        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_TIMRES_T2EXTIM);

        return ulRet;
    }

    /* 重建T2定时器 */
    ulTimerInterval = ulT2 - ulDiffTime;

    pstDhcpcCtlBlk->ucLeaseStatus = DHCPV6C_LEASE_STATE_WAIT_T2;

    ulRet = DHCPC_StartTimer(pstDhcpcCtlBlk->ucIpType, pstDhcpcCtlBlk->ulTEIDC,
                                DHCPV6C_EV_TIMER_RENEW, ulTimerInterval, DHCPC_TimerCallBack);
    return ulRet;
}

/*****************************************************************************
 函 数 名  : DHCPV6C_LeaseExpireTimerRestoreProc
 功能描述  : 租约定时器重建
 输入参数  : ULONG ulDiffTime
             DHCPC_CTRLBLK *pstDhcpcCtlBlk
 输出参数  : 无
 返 回 值  : ULONG
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月3日
    作    者   : tianyang 00144555
    修改内容   : 新生成函数

*****************************************************************************/
ULONG DHCPV6C_LeaseExpireTimerRestoreProc(ULONG ulDiffTime, DHCPC_CTRLBLK *pstDhcpcCtlBlk)
{
    ULONG   ulRet = 0;
    ULONG   ulTimerInterval = 0;
    ULONG   ulLease = 0;

    if ( NULL == pstDhcpcCtlBlk )
    {
        VOS_DBGASSERT(0);
        return VOS_ERR;
    }

    ulLease = pstDhcpcCtlBlk->ulLease;

    if (ulLease <= ulDiffTime)
    {
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_TIMRES_EXTIM_ERR);

        /* 设置原因值 */
        pstDhcpcCtlBlk->ucCause = DHCPV6C_CAUSE_LEASE_EXPIRE;

        /* 租约到期,需要释放地址,此处返回错误,在外层处理 */
        return VOS_ERR;
    }

    ulTimerInterval = ulLease - ulDiffTime;
    pstDhcpcCtlBlk->ucLeaseStatus = DHCPV6C_LEASE_STATE_WAIT_LEASE;

    ulRet = DHCPC_StartTimer(pstDhcpcCtlBlk->ucIpType, pstDhcpcCtlBlk->ulTEIDC,
                                DHCPV6C_EV_TIMER_LEASE_EXPIRE, ulTimerInterval, DHCPC_TimerCallBack);

    return ulRet;
}

/*****************************************************************************
 函 数 名  : DHCPV6C_SendtoTimRestoreforSpud
 功能描述  : 1+1备份时启动定时器重建函数
 输入参数  : ULONG ulHashValue
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月10日
    作    者   : tianyang 00144555
    修改内容   : 新生成函数

*****************************************************************************/
VOID DHCPV6C_SendtoTimRestoreforSpud(ULONG ulHashValue)
{
    DHCPC_INNER_MSG_S stInnerMsg = {0};

    DHCPV6C_DBGCNT_ADD(E_DHCPV6C_SENDTIM_SPUDRESTORE);

    stInnerMsg.ulMsgCode = DHCPC_INNER_MSGCODE_TIM_RESTORE;
    stInnerMsg.ulCtlBlockHashValue = ulHashValue;

    (VOID)DHCPC_SendRtMsg(DHCPC_SELF_CSI, DHCPC_MSG_TYPE_SELF, DHCPC_INNER_MSGCODE_TIM_RESTORE,
                          (UCHAR *)&stInnerMsg, sizeof(DHCPC_INNER_MSG_S));

    return;
}

/*****************************************************************************
 函 数 名  : DHCPV6C_TimerRestoreForSpud
 功能描述  : 1+1spu板定时器重建流程
 输入参数  : DHCPC_INNER_MSG_S *pstInnerMsg
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月10日
    作    者   : tianyang 00144555
    修改内容   : 新生成函数

*****************************************************************************/
VOID DHCPV6C_TimerRestoreForSpud(DHCPC_INNER_MSG_S *pstInnerMsg)
{
    ULONG ulRet = 0;
    ULONG ulHashValue = 0;
    ULONG ulScanNum = 0;
    ULONG ulReleaseNum = 0;
    DHCPC_CTRLBLK *pstDhcpcCtlBlk = NULL;
    DHCPC_CTRLBLK *pstTmpDhcpcCtlBlk = NULL;
    DHCPV6C_PRE_RESULT_S stPreResult = {0};

    if ( NULL == pstInnerMsg )
    {
        VOS_DBGASSERT(0);
        return;
    }

    DHCPV6C_DBGCNT_ADD(E_DHCPV6C_TIME_SPUDRESTORE_ENTER);

    for ( ulHashValue = pstInnerMsg->ulCtlBlockHashValue; ulHashValue < DHCPC_CTRLBLK_HASH_TABLE_SIZE ; ulHashValue++ )
    {
        pstDhcpcCtlBlk = g_pstDhcpcIpv6CtrlBlkRec[ulHashValue];
        while ( NULL != pstDhcpcCtlBlk )
        {
            ulScanNum++;
            if ( ulScanNum % 5000 == 0 )/* 流控，无需用宏 */
            {
                DHCPV6C_SendtoTimRestoreforSpud(ulHashValue);
                return;
            }
            /* 查找定时器是否已经存在 */
            ulRet = DHCPC_IsTimNodeExist(LAP_IPV6, pstDhcpcCtlBlk->ulTEIDC);
            if ( VOS_OK == ulRet )
            {
                DHCPV6C_DBGCNT_ADD(E_DHCPV6C_TIME_HASEXIST);
                /* 定时器已存在则不需要再创建 */
                pstDhcpcCtlBlk = pstDhcpcCtlBlk->pstNextNode;

                continue;
            }

            /* 恢复定时器 */
            DHCPV6C_DBGCNT_ADD(E_DHCPV6C_TIME_SPUDRESTORE);

            pstTmpDhcpcCtlBlk = pstDhcpcCtlBlk;
            pstDhcpcCtlBlk = pstDhcpcCtlBlk->pstNextNode;
            ulRet = DHCPV6C_TimerRestoreProc(pstTmpDhcpcCtlBlk);
            if ( VOS_OK != ulRet )
            {
                DHCPV6C_DBGCNT_ADD(E_DHCPV6C_TIME_SPUDRESTORE_FAIL);

                pstTmpDhcpcCtlBlk->ucLeaseStatus = DHCPV6C_LEASE_STATE_BUTT;

                stPreResult.pstDhcpcContext = pstTmpDhcpcCtlBlk;
                stPreResult.pMsg = NULL;
                stPreResult.enEvent = DHCPV6C_EV_IP_RELEASE;

                /* 运行状态机 */
                DHCPV6C_RunFsm(&stPreResult);

                /* 此处流控一定要低!! */
                ulReleaseNum++;
                if (ulReleaseNum % 2 == 0)
                {
                    DHCPV6C_SendtoTimRestoreforSpud(ulHashValue);
                    return;
                }

                continue;
            }
        }
    }
}

/*****************************************************************************
 函 数 名  : DHCPC_BoardStatChgTimerOutCallBack
 功能描述  : 单板备升主定时器超时处理函数
 输入参数  : VOID *pArg
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月27日
    作    者   : jixiaoming 00180244
    修改内容   : 新生成函数

*****************************************************************************/
VOID DHCPC_BoardStatChgTimerOutCallBack(VOID *pArg)
{
    DHCPV6C_DBGCNT_ADD(E_DHCPV6C_CNT_TRC_2);
    g_ulDhcpcBoardStateChgDelayTimerId = 0;

    if (E_CRM_ACTIVE != CRM_GetSlotPrimaryInfoOfSelfGroup((UCHAR)CRM_GetSelfLogicSlotID()))
    {
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_CNT_TRC_4);

        /* 如果当前状态为备板，则继续启动定时器等待 */
        (VOID)DHCPC_StartLeaseRebuildWaitTimer();
        return;
    }

    /* 开始租约定时器重建 */
    DHCPV6C_SendtoTimRestoreforSpud(0);

    return;
}

/*****************************************************************************
 函 数 名  : DHCPC_StartLeaseRebuildWaitTimer
 功能描述  : 启动租约重建等待定时器
 输出参数  : 无
 返 回 值  : ULONG
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月1日
    作    者   : jixiaoming 00180244
    修改内容   : 新生成函数

*****************************************************************************/
ULONG DHCPC_StartLeaseRebuildWaitTimer()
{
    ULONG ulRet = VOS_ERR;

    if (g_ulDhcpcBoardStateChgDelayTimerId != 0)
    {
        VOS_Assert(0);
        return VOS_ERR;
    }

    /* 启动10s定时器,10s后开始处理s */
    ulRet = PGP_Timer_Create(DHCPC_SELF_CSI,
                               DHCPC_MSG_TYPE_TIMER,
                               10 * 1000,
                               DHCPC_BoardStatChgTimerOutCallBack,
                               NULL,
                               &g_ulDhcpcBoardStateChgDelayTimerId,
                               VOS_TIMER_NOLOOP);
    if (VOS_OK != ulRet)
    {
        VOS_DBGASSERT(0);
        DHCPC_DebugPrint(PTM_LOG_ERR, "call PGP_Timer_Create fail! ulRet=0x%x", ulRet);
        return ulRet;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : DHCPV6C_SendInnerMsgForBoardStateChange
 功能描述  : 发送内部队列，处理单板状态变化消息
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月16日
    作    者   : mengyuanhui 00221593
    修改内容   : 新生成函数

*****************************************************************************/
VOID DHCPV6C_SendInnerMsgForBoardStateChange()
{
    DHCPC_INNER_MSG_S stInnerMsg = {0};

    stInnerMsg.ulMsgCode = DHCPC_INNER_MSGCODE_BOARD_STATE_CHANGE;

    (VOID)DHCPC_SendRtMsg(DHCPC_SELF_CSI, DHCPC_MSG_TYPE_SELF, DHCPC_INNER_MSGCODE_BOARD_STATE_CHANGE,
                          (UCHAR *)&stInnerMsg, sizeof(DHCPC_INNER_MSG_S));

    return;
}

/*****************************************************************************
 函 数 名  : DHCPV6C_ProcBoardStateChangeMsg
 功能描述  : 单板状态变化消息处理函数。DTS2014011300825 10.1CRM回调中不能启动定时器
             修改成发内部队列，在内部队列中创建定时器
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月16日
    作    者   : mengyuanhui 00221593
    修改内容   : 新生成函数

*****************************************************************************/
VOID DHCPV6C_ProcBoardStateChangeMsg()
{
    ULONG ulRet = VOS_ERR;

    if (0 != g_ulDhcpcBoardStateChgDelayTimerId)
    {
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_CNT_TRC_3);
        return;
    }

    ulRet = DHCPC_StartLeaseRebuildWaitTimer();
    if (VOS_OK != ulRet)
    {
        DHCPC_DebugPrint(PTM_LOG_ERR, "call DHCPC_StartLeaseRebuildWaitTimer fail! ulRet=0x%x", ulRet);
    }
}


/*****************************************************************************
 函 数 名  : DHCPC_BoardStateChgProc
 功能描述  : 本板主备状态改变处理函数
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月27日
    作    者   : jixiaoming 00180244
    修改内容   : 新生成函数

*****************************************************************************/
VOID DHCPC_BoardStateChgProc()
{
    DHCPV6C_SendInnerMsgForBoardStateChange();

    return;
}
/*****************************************************************************
 函 数 名  : DHCPC_StateOfBoardChgCallback
 功能描述  : 单板状态改变处理函数
 输入参数  : CRM_SPUSTATE_CHG_ENUM enEvent
             UCHAR ucGroupID
             UCHAR ucSlotID
             UCHAR ucCpuID
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月10日
    作    者   : tianyang 00144555
    修改内容   : 新生成函数

*****************************************************************************/
VOID DHCPC_StateOfBoardChgCallback( CRM_SPUSTATE_CHG_ENUM enEvent, UCHAR ucGroupID, UCHAR ucSlotID, UCHAR ucCpuID, UCHAR ucSGIndex)
{
    if (ucGroupID != CRM_GetSelfGroupId())
    {
        return;
    }

    if (ucSlotID != CRM_GetSelfLogicSlotID())
    {
        return;
    }

    DHCPC_DebugPrint(PTM_LOG_INFO, "enEvent=%u ucGroupID=%d ucSlotID=%d ucCpuID=%d = %d!",
                enEvent, ucGroupID, ucSlotID, ucCpuID, ucSGIndex);

    switch (enEvent)
    {
        case CRM_BRDSTATE_CHG_STANDBY_TO_ACTIVE:
            DHCPC_BoardStateChgProc();
            break;

        default:
            break;
    }

    return;
}
