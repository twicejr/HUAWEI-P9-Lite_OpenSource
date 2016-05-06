/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : dhcpc_pkt.c
  版 本 号   : 初稿
  作    者   : yuqingping(25027)
  生成日期   : 2002年11月21日
  最近修改   :
  功能描述   : dhcpc模块的报文处理
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
#if 0
#include "dhcpm_interface.h"
#endif

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID          PS_FILE_ID_DHCPC_PKT_C
/*lint +e767*/



/*****************************************************************************
 函 数 名  : DHCPC_GetOneContextByteidc
 功能描述  : 根据Teidc获取1个上下文。上下文存在则返回指向上下文的指针，不存在
             则返回NULL。获取到的指针不需要释放。
 输入参数  : ULONG ulTeidc,
 输出参数  : 无
 返 回 值  : SDB_GSPU_CONTEXT_S * 上下文的指针
 调用函数  : SDB_GTPC_GetRelatedContextsByTeidc
 被调函数  : DHCPC_Pkt_ProcDHCP

 日    期   : 2011-07-20
 作    者   : jixiaoming

*****************************************************************************/
SDB_GSPU_CONTEXT_S * DHCPC_GetOneContextByteidc(ULONG ulTeidc)
{
    ULONG ulRet = 0;
    ULONG ulContextsNum = 0;
    SDB_GSPU_CONTEXT_S *pstRelContexts[M_MNT_MAX_PDP_NUM] = {NULL};

    ulRet = (ULONG)SDB_GTPC_GetRelatedContextsByTeidc(ulTeidc, &ulContextsNum, (UCHAR **)pstRelContexts);
    if ((SDB_SUCCESS == ulRet) && (NULL != pstRelContexts[0]))
    {
        return pstRelContexts[0];
    }

    return NULL;
}

/*****************************************************************************
 函 数 名  : DHCPC_PGWPerfStat
 功能描述  : PGW性能统计
 输入参数  : UCHAR ucMsgType
 输出参数  : 无
 返 回 值  : ULONG
 调用函数  :
 被调函数  :

 日    期   : 2011-06-22
 作    者   : 纪晓明

*****************************************************************************/
VOID DHCPC_PGWPerfStat(UCHAR ucMsgType)
{
    switch(ucMsgType)
    {
        case DHCP_DISCOVER:
            if (VOS_NULL_PTR != g_PGWtoServer_ulDHCPV4DiscoveryNumAddr)
            {
                (VOID)PerfSetFamPerfCounterByAddress(g_PGWtoServer_ulDHCPV4DiscoveryNumAddr, E_PERF_OBJECT_ADD, 1);
            }
            break;

        case DHCP_REQUEST:
            if (VOS_NULL_PTR != g_PGWtoServer_ulDHCPV4RequestNumAddr)
            {
                (VOID)PerfSetFamPerfCounterByAddress(g_PGWtoServer_ulDHCPV4RequestNumAddr, E_PERF_OBJECT_ADD, 1);
            }
            break;

        case DHCP_DECLINE:
            if (VOS_NULL_PTR != g_PGWtoServer_ulDHCPV4DeclineNumAddr)
            {
                (VOID)PerfSetFamPerfCounterByAddress(g_PGWtoServer_ulDHCPV4DeclineNumAddr, E_PERF_OBJECT_ADD, 1);
            }
            break;

        case DHCP_RELEASE:
            if (VOS_NULL_PTR != g_PGWtoServer_ulDHCPV4ReleaseNumAddr)
            {
                (VOID)PerfSetFamPerfCounterByAddress(g_PGWtoServer_ulDHCPV4ReleaseNumAddr, E_PERF_OBJECT_ADD, 1);
            }
            break;

        case DHCP_OFFER:
            if (VOS_NULL_PTR != g_ServertoPGW_ulDHCPV4OfferNumAddr)
            {
                (VOID)PerfSetFamPerfCounterByAddress(g_ServertoPGW_ulDHCPV4OfferNumAddr, E_PERF_OBJECT_ADD, 1);
            }
            break;

        case DHCP_ACK:
            if (VOS_NULL_PTR != g_ServertoPGW_ulDHCPV4AckNumAddr)
            {
                (VOID)PerfSetFamPerfCounterByAddress(g_ServertoPGW_ulDHCPV4AckNumAddr, E_PERF_OBJECT_ADD, 1);
            }
            break;

        case DHCP_NAK:
            if (VOS_NULL_PTR != g_ServertoPGW_ulDHCPV4akNumAddr)
            {
                (VOID)PerfSetFamPerfCounterByAddress(g_ServertoPGW_ulDHCPV4akNumAddr, E_PERF_OBJECT_ADD, 1);
            }
            break;

        default :
            break;
    }
}

/*****************************************************************************
 函 数 名  : DHCPC_Pkt_CheckPkt
 功能描述  : 处理收到的DHCP的报文，进行地址合法性检查
 输入参数  : DHCP_S  *pstDHCPPkt
 输出参数  : 无
 返 回 值  : ULONG
 调用函数  :
 被调函数  :

 日    期   : 2010-09-10
 作    者   : w00140934

*****************************************************************************/
ULONG DHCPC_Pkt_CheckPkt(DHCP_S  *pstDHCPPkt)
{
    ULONG ulHostOrderAddress = 0;

    /*----------------DHPC报文合法性检查----------------------*/
    if ( ( ( VOS_HTONL( pstDHCPPkt->ulYiaddr )&( ULONG )0xE0000000 )==( ULONG )0xE0000000 )
         ||( ( VOS_HTONL( pstDHCPPkt->ulSiaddr )&( ULONG )0xE0000000 )==( ULONG )0xE0000000 ) )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_105);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\nDHCPC_Pkt_ProcDHCP Failed to process server packet(invalid IP )" );
        return VOS_ERR;
    }
    ulHostOrderAddress = VOS_HTONL( pstDHCPPkt->ulYiaddr );
    if (  0 ==  ulHostOrderAddress )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_106);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\nDHCPC_Pkt_ProcDHCP Failed to process server packet(invalid IP )" );
        return VOS_ERR;
    }

    if (VOS_OK != GTPC_RadiusHlrIPValidCheck(pstDHCPPkt->ulYiaddr))
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_107);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\nDHCPC_Pkt_ProcDHCP Failed to process server packet(invalid IP = %u )",VOS_HTONL( pstDHCPPkt->ulYiaddr ) );
        return VOS_ERR;
    }

    if( (ulHostOrderAddress  ==  0x7FFFFFFF)
        || (ulHostOrderAddress == 0x80000000) || (ulHostOrderAddress == 0xBFFFFFFF)
        || (ulHostOrderAddress == 0xC0000000) || (ulHostOrderAddress == 0xDFFFFFFF) )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_108);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\nDHCPC_Pkt_ProcDHCP Failed to process server packet(invalid IP = %u )",ulHostOrderAddress );
        return VOS_ERR;
    }
    return VOS_OK;

}

/*****************************************************************************
 函 数 名  : DHCPC_TransMsisdnToCallFromID
 功能描述  : MSISDN BCD->ASSIC
 输入参数  : UCHAR *pucMsisdn
             UCHAR *pucCallFromId
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年12月27日
    作    者   : caopu
    修改内容   : 移植from gtpc

*****************************************************************************/
UCHAR DHCPC_TransMsisdnToCallFromID ( UCHAR *pucMsisdn, UCHAR *pucCallFromId )
{
    int   i = 0;
    UCHAR ucCallFromIdLen = 0;      /*主叫号码长度*/

    if ( ( pucMsisdn == NULL ) || ( pucCallFromId == NULL ) )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_098);
        return ucCallFromIdLen;
    }

    for ( i=0; i<DHCP_MAX_MSISDN_LEN; i++ )
    {
        if ( 0X0F != ( ( *( pucMsisdn+i ) )&0X0F ) )
        {
            /*转换成字符串形式*/
            *( pucCallFromId+ucCallFromIdLen ) = ( ( *( pucMsisdn+i ) )&0X0F ) + 48;
            ucCallFromIdLen++;
        }
        if ( 0XF0 != ( ( *( pucMsisdn+i ) )&0XF0 ) )
        {
            /*转换成字符串形式*/
            *( pucCallFromId+ucCallFromIdLen ) = ( ( ( *( pucMsisdn+i ) )&0XF0 )>>4 ) + 48;
            ucCallFromIdLen++;
        }
    }

    return ucCallFromIdLen;
}

/*****************************************************************************
 函 数 名  : DHCPC_FillClientIdOption
 功能描述  : 封装dhcp clientid信元
 输入参数  : UCHAR *pucOption
             ULONG aulMsisdn[]
 输出参数  : 无
 返 回 值  : ULONG
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月9日
    作    者   : mengyuanhui 00221593
    修改内容   : 新生成函数

*****************************************************************************/
ULONG DHCPC_FillClientIdOption(UCHAR *pucOption, ULONG aulMsisdn[])
{
    UCHAR   szMSISDN[DHCP_MAX_MSISDN_STRING_LEN + 1] = {0};
    ULONG   ulMsisdnLen = 0;

    if ((NULL == pucOption) || (NULL == aulMsisdn))
    {
        VOS_Assert(0);
        return 0;
    }

    (VOID)DHCPC_TransMsisdnToCallFromID((UCHAR *)aulMsisdn, szMSISDN);
    ulMsisdnLen = VOS_StrLen(szMSISDN);
    if (0 == ulMsisdnLen)
    {
        return 0;
    }
    else
    {
        *pucOption++ = DHCP_CLIENTID_CODE;
        *pucOption++ = (UCHAR)(ulMsisdnLen + 1);   /*7;选项长度 现在为 17*/
        *pucOption++ = 0;                    /*使用MSISDN作为ID是否需要改变Type值*/
        VOS_MemCpy(pucOption, szMSISDN, ulMsisdnLen);
    }

    return ulMsisdnLen + 3;
}

/*****************************************************************************
 函 数 名  : DHCPC_Pkt_ProcDHCPRELEASE
 功能描述  : 处理Release报文
 输入参数  :
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2002年11月23日
    作    者   : yuqingping(25027)
    修改内容   : 新生成函数

*****************************************************************************/

ULONG DHCPC_Pkt_ProcDHCPRELEASE ( DHCPC_CTRLBLK_NODE* pstDhcpCtrlBlkNode )
{
    DHCPC_TEMPCTRLBLK    *pItemInfo = NULL;
	DHCPC_CTRLBLK        *pstDhcpCtrlBlk = NULL;

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n-->DHCPC_Pkt_ProcDHCPNACK()" );
    DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_099);
    if (NULL == pstDhcpCtrlBlkNode)
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_100);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\nDHCPC_MsgProc_Release pstDhcpCtrlBlkNode is NULL!" );
        return VOS_ERR;
    }
    pItemInfo = &( pstDhcpCtrlBlkNode->stDhcpcTmpCtlBlk );

    /*获取DHCP控制块*/
    pstDhcpCtrlBlk = (DHCPC_CTRLBLK *)DHCPC_CalcCtlBlkHashValue(pItemInfo->ulDHCPCtlIdx, pItemInfo->ulTEIDC);
    if ( NULL == pstDhcpCtrlBlk )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_101);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\nDHCPC_MsgProc_Release enter error!" );
        VOS_Assert( 0 );
        return VOS_ERR;
    }

    if ( ( DHCPC_STATE_BOUND        != pstDhcpCtrlBlk->usDhcpStatus )
         && ( DHCPC_STATE_LEASE        != pstDhcpCtrlBlk->usDhcpStatus )
         && ( DHCPC_STATE_ReNewing        != pstDhcpCtrlBlk->usDhcpStatus )
         && ( DHCPC_STATE_PreReBinding    != pstDhcpCtrlBlk->usDhcpStatus )
         && ( DHCPC_STATE_ReBinding        != pstDhcpCtrlBlk->usDhcpStatus ) )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_102);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\nDHCPC_Pkt_ProcDHCPRelease state err!" );
        return VOS_ERR;
    }

    (VOID)DHCPC_StopTimer(pstDhcpCtrlBlk->ucIpType, pstDhcpCtrlBlk->ulTEIDC, 0);
    ( VOID )DHCPC_SendMsgToLAP2( pstDhcpCtrlBlkNode,DHCPC_SND2_LAP2_ADDR_REL_MSG );
    DHCPC_FreeDhcpCtrlBlk( pstDhcpCtrlBlk->ulDHCPCtxIdx, pstDhcpCtrlBlk->ulTEIDC, pstDhcpCtrlBlk->ucUser, pstDhcpCtrlBlk->ulPDPIndex);
    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : DHCPC_PktProc_RcvDHCP
 功能描述  : 处理收到的DHCP的报文，进行分类
 输入参数  : DHCP_S  *pstDHCPPkt
             ULONG       ulOptionLen
 输出参数  : 无
 返 回 值  : ULONG
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2002年11月22日
    作    者   : yuqingping(25027)
    修改内容   : 新生成函数

*****************************************************************************/
ULONG  DHCPC_Pkt_ProcDHCP( DHCP_S  *pstDHCPPkt, ULONG ulOptionLen,ULONG ulSrvIpAddr )
{
    DHCPC_TEMPCTRLBLK   *pstHashItem = NULL;
    DHCPC_CTRLBLK_NODE  *pstDhcpCtrlBlkNode = NULL;
    DHCPC_CTRLBLK       *pstDhcpCtrBlk = NULL;
    DHCP_OPTION_S       stDhcpOption;
    ULONG               ulUserIpAddr = 0;
    ULONG               ulDHCPCtxIdx = 0;        /*DHCP控制块索引*/
    ULONG               ulRet = 0;
    UCHAR               ucSCID = 0;
    UCHAR               ucRenewFlg = VRP_NO;

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n-->DHCPC_Pkt_ProcDHCP()" );
    DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_206);

    if ( NULL == pstDHCPPkt )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_103);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\nDHCPC_Pkt_ProcDHCP NULL packet!" );
        return NULL;
    }

    /*判断报文类型是否确实是DHCPREPLY*/
    if ( pstDHCPPkt->ucOp != DHCP_OP_REPLY )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_104);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\nDHCPC_Pkt_ProcDHCP receive a request packet!" );
        return VOS_ERR;
    }

    /*取报文中的OPTION*/
    PGP_MemZero( ( CHAR * )&stDhcpOption,  sizeof( DHCP_OPTION_S ) );
    if ( VOS_OK != DHCPR_RecordAllOption( &stDhcpOption,pstDHCPPkt,ulOptionLen ) )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_109);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\nDHCPC_Pkt_ProcDHCP dhcp options error!" );
        return VOS_ERR;
    }

    if ( NULL == stDhcpOption.pucDHCPMsgType )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_110);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\nDHCPC_Pkt_ProcDHCP DHCP type error!" );
        return VOS_ERR;
    }

    /*获取DHCP控制块*/
    pstDhcpCtrBlk = (DHCPC_CTRLBLK *)DHCPC_LookupCtlBlkNodeIntoHashTable( pstDHCPPkt );
    if( NULL == pstDhcpCtrBlk )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_115);
        /* zhangjinquan DTS2011072204836  对于spud板需要能够抓到异常的ack包 2012-01-09 start */
        if (VOS_TRUE == TrcGetTraceFlag(TRC_TYPE_V))
        {
            /* z00175135 DTS2011120504839 全pclint修改 2012-02-18 start */

            DHCPC_OmVIfMsgTrc((ULONG)*(stDhcpOption.pucDHCPMsgType),
                                TRC_DIRECTION_RIGHT_IN_UGW_ERR,
                                (UCHAR*)pstDHCPPkt,
                                (USHORT)(DHCPC_PKT_FIXEDFIELD_LEN + ulOptionLen),
                                LAP_IPV4,
                                &ulSrvIpAddr);
            /* z00175135 DTS2011120504839 全pclint修改 2012-02-18 end   */
        }
        /* zhangjinquan DTS2011072204836  对于spud板需要能够抓到异常的ack包 2012-01-09 end   */
        DHCPC_DebugPrint(PTM_LOG_DEBUG,
                                "\r\nDHCPC_Pkt_ProcDHCP get DhcpCtrlBlk error ulDHCPCtxIdx = %u!",ulDHCPCtxIdx );
        /*当前用户没有创建dhcp控制块，或者当前用户索引不正确*/
        return VOS_ERR;
    }

    /*获取本SC的id*/
    ucSCID = (UCHAR)DHCPC_SELF_CMPIDX_INSG;

    /* 如果当前控制块不为初始状态 (非第一次激活流程) */
    if ( DHCPC_STATE_INITIAL != pstDhcpCtrBlk->usDhcpStatus )
    {
        ulRet = DHCPC_SetServerStatusToNormalByIndexAndIp(pstDhcpCtrBlk->usServerGrpIndex, ulSrvIpAddr);
        if (VOS_OK != ulRet)
        {
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_248);
            return ulRet;
        }

        /* V9 DHCP 返回的地址不放入SDB上下文中，将地址放入控制块保存，如
        果此时控制块不为初始状态，则IP地址必定不为0或0xFFFFFFFF，此时地
        址根据控制块中的判断 comment by caopu */
        ulUserIpAddr = pstDhcpCtrBlk->aulUserIpAddr[0];
        if ( ( 0 == ulUserIpAddr ) || ( 0xffffffff == ulUserIpAddr ) )
        {
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_116);
            DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\nDHCPC_Pkt_ProcDHCP get user ip fail when renew ip!" );
            /* 此时DHCP状态不正常 */
            return VOS_ERR;
        }
        /*续申请用户,自己构造一个控制块节点*/
        pstDhcpCtrlBlkNode = ( DHCPC_CTRLBLK_NODE* )DHCP_Malloc( DHCPC_HANDLE, sizeof( DHCPC_CTRLBLK_NODE ) );
        if ( NULL == pstDhcpCtrlBlkNode )
        {
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_117);
            DHCPC_DebugPrint(PTM_LOG_DEBUG,  "\r\nDHCPC_Pkt_ProcDHCP memory alloc failed!" );
            return VOS_ERR;
        }
        /* 增加必要的清零操作 */
        PGP_MemZero(pstDhcpCtrlBlkNode, sizeof(DHCPC_CTRLBLK_NODE));
        /* pstHashItem为临时控制块 */
        pstHashItem = &( pstDhcpCtrlBlkNode->stDhcpcTmpCtlBlk );
        DHCPC_INIT_ITEM( pstHashItem );
        pstHashItem->usLease = pstDhcpCtrBlk->ulLease;
        pstHashItem->ulSrvIp= pstDhcpCtrBlk->aulSrvIp[0];
        pstHashItem->ulTimeStamp= pstDhcpCtrBlk->ulTmpVar;    /*发送REQ的时间保存在ulTmpVar*/
        pstHashItem->usDhcpStatus= pstDhcpCtrBlk->usDhcpStatus;
        pstHashItem->ulUserIpAddr = ulUserIpAddr;
        pstHashItem->ulPdpIndex = pstDhcpCtrBlk->ulPDPIndex;    /*ST*/
        /*added start by z00113478 把值都赋完整*/
        pstHashItem->ulDHCPCtlIdx = pstDhcpCtrBlk->ulDHCPCtxIdx;
        pstHashItem->ucUserType = pstDhcpCtrBlk->ucUserType;
        pstHashItem->aulMSISDN[0] = pstDhcpCtrBlk->aulMSISDN[0];
        pstHashItem->aulMSISDN[1] = pstDhcpCtrBlk->aulMSISDN[1];
        pstHashItem->aulIMSI[0] = pstDhcpCtrBlk->aulIMSI[0];
        pstHashItem->aulIMSI[1] = pstDhcpCtrBlk->aulIMSI[1];
        /* BEGIN: Added by jixiaoming for  IMEI跟踪 at 2012-8-17 */
        pstHashItem->aulIMEI[0] = pstDhcpCtrBlk->aulIMEI[0];
        pstHashItem->aulIMEI[1] = pstDhcpCtrBlk->aulIMEI[1];
        /* END: Added by jixiaoming for IMEI跟踪 at 2012-8-17 */

        pstHashItem->ulAgetIP = pstDhcpCtrBlk->aulAgentIpAddr[0];
        pstHashItem->usPoolIndex = pstDhcpCtrBlk->usPoolIndex;
        pstHashItem->usDhcpGroupIndex = pstDhcpCtrBlk->usServerGrpIndex;
        pstHashItem->usVpnId= pstDhcpCtrBlk->usVPNIndex;
        pstHashItem->ucRole = pstDhcpCtrBlk->ucRole;
        /*usApnIndex是否需要?可以考虑从Server回来的报文中提取*/
        pstHashItem->ucUser= pstDhcpCtrBlk->ucUser;
        pstHashItem->ulTEIDC = pstDhcpCtrBlk->ulTEIDC;
        ucRenewFlg = VRP_YES;
        pstHashItem->ucSCID = ucSCID;
        /* 进行地址类型配置，当前指定为IPv4 */
        pstHashItem->ucAddressType = LAP_IPV4;
        pstHashItem->ucLAPNo = pstDhcpCtrBlk->ucLAPNo;
        pstHashItem->ucRandomNo = pstDhcpCtrBlk->ucRandomNo;

    }
    /* 如果当前控制块第一次申请流程中的状态 */
    else
    {
        /*取临时控制块指针，并判断该内存区是否临时控制块?*/
        pstDhcpCtrlBlkNode = DHCPC_GetTmpDhcpCtrlBlkPtr( pstDhcpCtrBlk );
        if ( NULL == pstDhcpCtrlBlkNode )
        {
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_118);
            DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPC_Pkt_ProcDHCP find no DHCP temp control block!" );
            return VOS_ERR;
        }
        pstHashItem = &( pstDhcpCtrlBlkNode->stDhcpcTmpCtlBlk );

        ulRet = DHCPC_SetServerStatusToNormalByIndexAndIp(pstHashItem->usDhcpGroupIndex, ulSrvIpAddr);
        if (VOS_OK != ulRet)
        {
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_250);
            return ulRet;
        }

        /*用户表项中的ulXid与报文中是否相符*/
        if ( VOS_HTONL(pstDHCPPkt->ulXid) != pstHashItem->ulXid )
        {
            /* zhangjinquan DTS2011072204836  对于spud板需要能够抓到异常的ack包 2012-01-09 start */
            if (VOS_TRUE == TrcGetTraceFlag(TRC_TYPE_V))
            {
                /* z00175135 DTS2011120504839 全pclint修改 2012-02-18 start */

                DHCPC_OmVIfMsgTrc((ULONG)*(stDhcpOption.pucDHCPMsgType),
                                    TRC_DIRECTION_RIGHT_IN_UGW_ERR,
                                    (UCHAR*)pstDHCPPkt,
                                    (USHORT)(DHCPC_PKT_FIXEDFIELD_LEN + ulOptionLen),
                                    LAP_IPV4,
                                    &ulSrvIpAddr);
                /* z00175135 DTS2011120504839 全pclint修改 2012-02-18 end   */
            }
            /* zhangjinquan DTS2011072204836  对于spud板需要能够抓到异常的ack包 2012-01-09 end   */
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_121);
            DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPC_Pkt_ProcDHCP Xid different!" );
            return VOS_ERR;
        }
    }

{
//        ULONG ulRet = 0;
        SDB_GSPU_CONTEXT_S *pstContext = VOS_NULL_PTR;
        /* BEGIN: Added for PN:全网跟踪  by LiHairong, 2010/4/8 */
        RM_SOCKET_PATH_S stPath = {0};
        S_OM_EMS_TRC_PARA stTrcPara = {0};
        /* END:   Added for PN:全网跟踪  by LiHairong, 2010/4/8 */
        ULONG ulDirection = TRC_DIRECTION_RIGHT_IN_PGW;

        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPC_Pkt_ProcDHCP Trace !" );

        /*根据Teidc, 获取1个上下文*/
        pstContext = DHCPC_GetOneContextByteidc(pstDhcpCtrBlk->ulTEIDC);
        if (NULL == pstContext)
        {
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_114);
            if ( VRP_YES == ucRenewFlg )
            {
                DHCP_Free( DHCPC_HANDLE, pstDhcpCtrlBlkNode);
                pstDhcpCtrlBlkNode = NULL;
            }
            DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPC_Pkt_ProcDHCP : SDB_GetContextByIndex return ERR.!" );
            return VOS_ERR;
        }
        if(( E_NET_ELEMENT_ROLE_GGSN == pstContext->ucUgwRole )||( E_NET_ELEMENT_ROLE_PGW_AND_SGW == pstContext->ucUgwRole ))
        {
            ulDirection = TRC_DIRECTION_RIGHT_IN_UGW;
        }

        UGW_OmUsrMsgTrace((UCHAR *)pstDHCPPkt,
                         GUSER_MSGTYPE_DHCPV4,
                         (ULONG)*( stDhcpOption.pucDHCPMsgType ) + ulDirection,
                         (USHORT)(DHCPC_PKT_FIXEDFIELD_LEN + ulOptionLen),
                         (UCHAR *)&(pstContext->stImsi),
                         (UCHAR *)&(pstContext->stIMEI),
                         pstContext->szMsisdn,
                         pstContext->ucRandomNo);

        /* DHCP信令消息V接口跟踪 */ /* 将TrcGetTraceFlag()调用放在跟踪函数之外,提升效率 */
        if (VOS_TRUE == TrcGetTraceFlag(TRC_TYPE_V))
        {
            /* z00175135 DTS2011120504839 全pclint修改 2012-02-18 start */

            DHCPC_OmVIfMsgTrc((ULONG)*(stDhcpOption.pucDHCPMsgType),
                                ulDirection,
                                (UCHAR*)pstDHCPPkt,
                                (USHORT)(DHCPC_PKT_FIXEDFIELD_LEN + ulOptionLen),
                                LAP_IPV4,
                                &ulSrvIpAddr);
            /* z00175135 DTS2011120504839 全pclint修改 2012-02-18 end   */
        }

        /* BEGIN: Added for PN:全网跟踪  by LiHairong, 2010/4/10 */
        stPath.ulLocalAddr = pstHashItem->ulAgetIP;
        stPath.ulPeerAddr = ulSrvIpAddr;
        if (g_ucSoftParaDHCPKPN & ((UCHAR)0x02))
        {
            stPath.usLocalPort = DHCPS_PKT_PORTNO;
        }
        else
        {
            stPath.usLocalPort = DHCPC_PKT_PORTNO;
        }
        stPath.usPeerPort = DHCPS_PKT_PORTNO;

        stTrcPara.pucTrcMsg = (UCHAR *)pstDHCPPkt;
        stTrcPara.ucMsgType = (UCHAR)*( stDhcpOption.pucDHCPMsgType );
        stTrcPara.ucUgwRole = pstContext->ucUgwRole;
        stTrcPara.usMsgLen = (USHORT)(DHCPC_PKT_FIXEDFIELD_LEN + ulOptionLen);
        stTrcPara.ulEmsTrcDir = M_EMS_TRC_RECV_MSG;
        stTrcPara.ulUsrTrcDir = TRC_DIRECTION_RIGHT_IN_PGW;
        stTrcPara.usTraceId = pstContext->usTraceId;
        stTrcPara.ucSgwTrcFlg = pstContext->ucSgwIsTraceFlag;
        stTrcPara.ucPgwTrcFlg = pstContext->ucPgwIsTraceFlag;
        stTrcPara.ucSgwTrcIf = pstContext->ucSgwListOfInterfaces;
        stTrcPara.ucPgwTrcIf = pstContext->ucPgwListOfInterfaces;
        stTrcPara.ucProType = GTPC_GUSER_MSGTYPE_DHCPV4;
        stTrcPara.ucMsgIntf = VOS_NULL_BYTE;
        stTrcPara.ucMsgSndFlg = 0;
        if((1 == stTrcPara.ucSgwTrcFlg)
            || (1 == stTrcPara.ucPgwTrcFlg))
        {
            UGW_OmEmsTrcMsgTrc(&stTrcPara,&stPath);
        }
        /* END:   Added for PN:全网跟踪  by LiHairong, 2010/4/10 */

        /* PGW性能统计 */
        if ((E_NET_ELEMENT_ROLE_PGW == pstContext->ucUgwRole) || (E_NET_ELEMENT_ROLE_PGW_AND_SGW == pstContext->ucUgwRole))
        {
            DHCPC_PGWPerfStat(*(stDhcpOption.pucDHCPMsgType));
        }
}

    /* 移动到消息跟踪之后. Modified by jixiaoming at 2011-10-15 for DTS2011071801195 */
    /* Added start by w00140934 at 2010-09-10 for 地址判断后移，续租时如果Server回复nak，地址无法释放 */
    if( DHCP_NAK != *( stDhcpOption.pucDHCPMsgType ) )
    {
        ulRet = DHCPC_Pkt_CheckPkt(pstDHCPPkt);
        if(VOS_ERR == ulRet)
        {
            if ( VRP_YES == ucRenewFlg )
            {
                DHCP_Free( DHCPC_HANDLE, pstDhcpCtrlBlkNode );
                /* zhangjinquan DTS2011073004013 释放后置空 */
                pstDhcpCtrlBlkNode = NULL;
            }
            return VOS_ERR;
        }
    }
    /* Added start by w00140934 at 2010-09-10 for 地址判断后移，续租时如果Server回复nak，地址无法释放 */

    switch ( *( stDhcpOption.pucDHCPMsgType ) )
    {
        case DHCP_OFFER:
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_207);

            VOS_Assert( VRP_NO == ucRenewFlg );
            ( VOID )DHCPC_Pkt_ProcDHCPOFFER( pstDHCPPkt, &stDhcpOption, pstDhcpCtrlBlkNode );
            break;

        case DHCP_ACK:
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_208);
            ( VOID )DHCPC_Pkt_ProcDHCPACK( pstDHCPPkt, &stDhcpOption, pstDhcpCtrlBlkNode );
            break;

        case DHCP_NAK:
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_209);
            ( VOID )DHCPC_Pkt_ProcDHCPNACK( pstDhcpCtrlBlkNode );
            break;
        case DHCP_RELEASE:
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_210);
            ( VOID )DHCPC_Pkt_ProcDHCPRELEASE ( pstDhcpCtrlBlkNode );
            break;
        default:
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_122);
            VOS_Assert( 0 );
            DHCPC_DebugPrint(PTM_LOG_DEBUG,  "\r\n DHCPC_Pkt_ProcDHCP unknown dhcp packet type!" );
            break;
    }

    if ( VRP_YES == ucRenewFlg )
    {
        DHCP_Free( DHCPC_HANDLE, pstDhcpCtrlBlkNode );
        /* zhangjinquan DTS2011073004013 释放后置空 */
        pstDhcpCtrlBlkNode = NULL;
    }
    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : DHCPC_PktProc_OFFER
 功能描述  : 处理offer报文
 输入参数  : DHCP_S  *pstDHCPPkt
             DHCPC_INFO_S* pItemInfo
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2002年11月23日
    作    者   : yuqingping(25027)
    修改内容   : 新生成函数

*****************************************************************************/
ULONG DHCPC_Pkt_ProcDHCPOFFER ( DHCP_S *pstDHCPPkt, DHCP_OPTION_S *pstDhcpOption, DHCPC_CTRLBLK_NODE* pstDhcpCtrlBlkNode )
{
    ULONG               ulRet = 0;
    DHCPC_TEMPCTRLBLK   *pItemInfo = NULL;
    ULONG               ulDnsNum = 0;

    if((NULL == pstDHCPPkt) || (NULL == pstDhcpOption) || (NULL == pstDhcpCtrlBlkNode))
    {
        VOS_Assert(0);
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_123);
        return VOS_ERR;
    }

    DHCPC_FUNC_ENTRY();

    pItemInfo = &( pstDhcpCtrlBlkNode->stDhcpcTmpCtlBlk );

    /*--------------------------报文检查--------------------------*/
    if ( DHCPC_STATE_DISCOVER != pItemInfo->usDhcpStatus )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_124);
        DHCPC_DebugPrint(PTM_LOG_DEBUG,  "Dhcp State error!" );
        return VOS_ERR;
    }

    /*报文中的内容保存到item中*/
    pItemInfo->ulUserIpAddr        = pstDHCPPkt->ulYiaddr;
    /* z00175135 DTS2012051105936 dhcp分配地址和agent-ip相同时发送Decline 2012-07-03 start */
    if (pItemInfo->ulAgetIP == pstDHCPPkt->ulYiaddr)
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_225);
        (VOID)DHCPC_Pkt_Send(DHCP_DECLINE, pItemInfo);
        return VOS_ERR;
    }
    /* z00175135 DTS2012051105936 dhcp分配地址和agent-ip相同时发送Decline 2012-07-03 end   */

    if ( NULL != pstDhcpOption->pulLeaseTime )
    {
        pItemInfo->usLease = VOS_HTONL(*pstDhcpOption->pulLeaseTime);
    }
    else
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_125);
        /*DHCPOFFER MUST carry IP address lease time*/
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\nDHCPC_Pkt_ProcDHCPOFFER OFFER carry no IP address lease time!" );
        return VOS_ERR;
    }

    /*记录server-ip*/
    if ( NULL != pstDhcpOption->pulDHCPServerIp )
    {
        pItemInfo->ulSrvIp = *pstDhcpOption->pulDHCPServerIp;
    }
    else
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_126);
        /*DHCPOFFER MUST carry Server identifier*/
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\nDHCPC_Pkt_ProcDHCPOFFER OFFER carry no server ip!" );
        return VOS_ERR;
    }

    /*记录DNS IP*/
    if ( ( NULL != pstDhcpOption->pulDNSIp )&&( 0 == ( pstDhcpOption->ucDNSIpLen%4 ) ) && ( 0 != ( pstDhcpOption->ucDNSIpLen/4 ) ) )
    {
        ulDnsNum = pstDhcpOption->ucDNSIpLen/4;
        if ( ulDnsNum >= 2 )
        {
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_127);
            /*对于返回多个DNS Server,只处理前两个DNS,赋给主备DNS IP*/
            pItemInfo->ulPriDNSIP = *pstDhcpOption->pulDNSIp;
            DHCPC_DebugPrint(PTM_LOG_DEBUG,  "ulDnsNum=%u,pItemInfo->ulPriDNSIP=%u!",ulDnsNum,pItemInfo->ulPriDNSIP );
            VOS_MemCpy( ( VOID* )&pItemInfo->ulSecDNSIP,( VOID* )( pstDhcpOption->pulDNSIp + 1 ),4 );

            pItemInfo->ulSecDNSIP = *(pstDhcpOption->pulDNSIp + 1) ;
            /* Added start by y00170683 at 2012-08-27 UGW10.0 for DTS2012082700731,主备相同时只携带主 */
            if (pItemInfo->ulPriDNSIP == pItemInfo->ulSecDNSIP)
            {
                pItemInfo->ulSecDNSIP = 0;
            }
            DHCPC_DebugPrint(PTM_LOG_DEBUG,  "ulPriDNSIP=%x ulSecDNSIP=%x",pItemInfo->ulPriDNSIP,pItemInfo->ulSecDNSIP );
        }
        else
        {
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_128);

            /*只返回一个DNS Server*/
            pItemInfo->ulPriDNSIP = *pstDhcpOption->pulDNSIp;

            DHCPC_DebugPrint(PTM_LOG_DEBUG,  "ulPriDNSIP=%x", pItemInfo->ulPriDNSIP);
        }
    }

    /* 设置状态为DHCPC_STATE_REQUEST */
    DHCPC_ITEM_SETSATE( pItemInfo, DHCPC_STATE_REQUEST );

    /*报文发送*/
    ulRet = DHCPC_Pkt_Send( DHCP_REQUEST, pItemInfo );
    if ( VOS_OK != ulRet )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_129);
        /*删定时器节点*/
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\nDHCPC_Pkt_ProcDHCPOFFER send REQUEST error!" );

        /* zhangjinquan 通知lap2处理失败 */
        ulRet = DHCPC_SendMsgToLAP2(pstDhcpCtrlBlkNode, DHCPC_SND2_LAP2_ADDR_FAILED_MSG);
        if (VOS_OK != ulRet)
        {
            DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPC_Pkt_ProcDHCPOFFER inform LAP2 error!" );
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_050);
        }
        DHCPC_FreeDhcpCtrlBlk( pstDhcpCtrlBlkNode->stDhcpcTmpCtlBlk.ulDHCPCtlIdx,
        pstDhcpCtrlBlkNode->stDhcpcTmpCtlBlk.ulTEIDC,
        pstDhcpCtrlBlkNode->stDhcpcTmpCtlBlk.ucUser,
        pstDhcpCtrlBlkNode->stDhcpcTmpCtlBlk.ulPdpIndex);
        DHCPC_DelNode( DHCPC_INVALID_INDEX, pstDhcpCtrlBlkNode );
        DHCPC_FreeDhcpTmpNode( pstDhcpCtrlBlkNode );
        return VOS_ERR;
    }
    /*重置发送标志*/
    pItemInfo->usAlreadySendFlg = DHCPC_FIRSTSEND;
    DHCPC_DelNode( DHCPC_INVALID_INDEX, pstDhcpCtrlBlkNode );
    DHCPC_InSertNodeAfterSecs( DHCPC_4_SECONDS, pstDhcpCtrlBlkNode );

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : DHCPC_PktProc_ACK
 功能描述  : 处理ack报文
 输入参数  : DHCP_S  *pstDHCPPkt
             DHCPC_INFO_S* pItemInfo
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2002年11月23日
    作    者   : yuqingping(25027)
    修改内容   : 新生成函数

*****************************************************************************/
ULONG DHCPC_Pkt_ProcDHCPACK ( DHCP_S  *pstDHCPPkt, DHCP_OPTION_S *pstDhcpOption, DHCPC_CTRLBLK_NODE* pstDhcpCtrlBlkNode )
{
    /*
    *1、对于续申请用户(ucModId = null)，直接写SDB，
    *修改lease和time-stamp，status。注意写备份标志
    *2、对于申请用户，修改sdb，写入DHCP控制块，备份标志
    *通知GTPC/PPPC，删临时控制块；g_ulDhcpTotalCtrlBlkNum--;
    *3、检查IP地址的有效性，有效则通知GTPC/PPPC，
    *无效则往SERVER发DECLINE。同时通知GTPC/PPPC不成功;
    *4、检查IP地址是否已经被重复使用，
    *如果是，则往SERVER发DECLINE。同时通知GTPC/PPPC不成功;
    *5、对于ACK 报文，在续申请用户发送倒换后，
    *只要还能找到该上下文，仍然有效
    *6、如果在IP地址申请成功，通知GTPC/PPPC模块时，返回不成功
    *则往server发送Release报文
    */
    DHCPC_TEMPCTRLBLK   *pItemInfo = NULL;
    ULONG               ulDnsNum = 0;
    ULONG               ulRet = VOS_OK;
    DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n-->DHCPC_Pkt_ProcDHCPACK()" );

    if((NULL == pstDHCPPkt) || (NULL == pstDhcpOption) || (NULL == pstDhcpCtrlBlkNode))
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_130);
        DHCPC_DebugPrint(PTM_LOG_DEBUG,  "\r\nDHCPC_Pkt_ProcDHCPOFFER NULL error!" );
        return VOS_ERR;
    }

    pItemInfo = &( pstDhcpCtrlBlkNode->stDhcpcTmpCtlBlk );


    if ( ( DHCPC_STATE_REQUEST        != pItemInfo->usDhcpStatus )
         && ( DHCPC_STATE_LEASE           != pItemInfo->usDhcpStatus )
         && ( DHCPC_STATE_ReNewing        != pItemInfo->usDhcpStatus )
         && ( DHCPC_STATE_PreReBinding    != pItemInfo->usDhcpStatus )
         && ( DHCPC_STATE_ReBinding       != pItemInfo->usDhcpStatus ) )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_131);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\nDHCPC_Pkt_ProcDHCPACK state err!" );
        return VOS_ERR;
    }

    if ( NULL != pstDhcpOption->pulLeaseTime )
    {
        pItemInfo->usLease = VOS_HTONL(*pstDhcpOption->pulLeaseTime);
    }
    else
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_132);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\nDHCPC_Pkt_ProcDHCPACK ACK carry no lease time!" );
        return VOS_ERR;
    }

    /*记录DNS IP*/
    if ( ( NULL != pstDhcpOption->pulDNSIp )&&( 0 == ( pstDhcpOption->ucDNSIpLen%4 ) ) && ( 0 != ( pstDhcpOption->ucDNSIpLen/4 ) ) )
    {
        ulDnsNum = pstDhcpOption->ucDNSIpLen/4;
        if ( ulDnsNum >= 2 )
        {
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_133);
            /*对于返回多个DNS Server,只处理前两个DNS,赋给主备DNS IP*/
            pItemInfo->ulPriDNSIP = *pstDhcpOption->pulDNSIp;
            DHCPC_DebugPrint(PTM_LOG_DEBUG,  "ulDnsNum=%u,pItemInfo->ulPriDNSIP=%u!",ulDnsNum,pItemInfo->ulPriDNSIP );
            VOS_MemCpy( ( VOID* )&pItemInfo->ulSecDNSIP,( VOID* )( pstDhcpOption->pulDNSIp + 1 ),4 );

            pItemInfo->ulSecDNSIP = * ( pstDhcpOption->pulDNSIp + 1) ;
            /* Added start by y00170683 at 2012-08-27 UGW10.0 for DTS2012082700731,主备相同时只携带主 */
            if (pItemInfo->ulPriDNSIP == pItemInfo->ulSecDNSIP)
            {
                pItemInfo->ulSecDNSIP = 0;
            }
            DHCPC_DebugPrint(PTM_LOG_DEBUG,  "ulPriDNSIP=%x ulSecDNSIP=%x",pItemInfo->ulPriDNSIP,pItemInfo->ulSecDNSIP );
        }
        else
        {
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_134);

            /*只返回一个DNS Server*/
            pItemInfo->ulPriDNSIP = *pstDhcpOption->pulDNSIp;

            DHCPC_DebugPrint(PTM_LOG_DEBUG,  "ulPriDNSIP=%x",pItemInfo->ulPriDNSIP);
        }
    }

    switch ( pItemInfo->usDhcpStatus )
    {
        case DHCPC_STATE_REQUEST:
        {
             /* 地址不一致释放当前IP */
            if ( pstDHCPPkt->ulYiaddr != pItemInfo->ulUserIpAddr )
            {
                DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_200);
                ( VOID )DHCPC_Pkt_Send( DHCP_RELEASE, pItemInfo );

                /* zhangjinquan 通知lap2处理失败 */
                ulRet = DHCPC_SendMsgToLAP2(pstDhcpCtrlBlkNode, DHCPC_SND2_LAP2_ADDR_FAILED_MSG);
                if (VOS_OK != ulRet)
                {
                    DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPC_Pkt_ProcDHCPACK inform LAP2 error 1!" );
                    DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_057);
                }

                DHCPC_DelNode( DHCPC_INVALID_INDEX, pstDhcpCtrlBlkNode );
                DHCPC_FreeDhcpCtrlBlk( pItemInfo->ulDHCPCtlIdx, pItemInfo->ulTEIDC, pItemInfo->ucUser, pItemInfo->ulPdpIndex );
                DHCPC_FreeDhcpTmpNode( pstDhcpCtrlBlkNode );
                return VOS_ERR;
            }
            if ( VOS_ERR == DHCPC_SaveSdbDhcpCtrlBlk( pItemInfo, VOS_FALSE ) )
            {
                DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_135);
                /*请求IP用户:
                  *控制块内容已经改变，此时最好删除节点
                  *删除控制块节点，释放内存
                  */
                /* zhangjinquan 通知lap2处理失败 */
                ulRet = DHCPC_SendMsgToLAP2(pstDhcpCtrlBlkNode, DHCPC_SND2_LAP2_ADDR_FAILED_MSG);
                if (VOS_OK != ulRet)
                {
                    DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPC_Pkt_ProcDHCPACK inform LAP2 error 2!" );
                    DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_061);
                }

                /* 发送release消息 */
                ( VOID )DHCPC_Pkt_Send( DHCP_RELEASE, pItemInfo );

                DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\nDHCPC_Pkt_ProcDHCPACK save SDB err!" );
                DHCPC_DelNode( DHCPC_INVALID_INDEX, pstDhcpCtrlBlkNode );

                DHCPC_FreeDhcpCtrlBlk( pItemInfo->ulDHCPCtlIdx, pItemInfo->ulTEIDC, pItemInfo->ucUser, pItemInfo->ulPdpIndex );

                DHCPC_FreeDhcpTmpNode( pstDhcpCtrlBlkNode );
                return VOS_ERR;
            }

            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_219);
            ( VOID )DHCPC_SendMsgToLAP2( pstDhcpCtrlBlkNode ,DHCPC_SND2_LAP2_ADDR_SUCCESS_MSG );

            /*删除控制块节点，释放内存*/
            DHCPC_DelNode( DHCPC_INVALID_INDEX, pstDhcpCtrlBlkNode );
            DHCPC_FreeDhcpTmpNode( pstDhcpCtrlBlkNode );
            break;
        }

        case DHCPC_STATE_LEASE :
        case DHCPC_STATE_ReNewing:
        case DHCPC_STATE_PreReBinding:
        case DHCPC_STATE_ReBinding:
        {

            (VOID)DHCPC_StopTimer(pItemInfo->ucAddressType, pItemInfo->ulTEIDC, 0);
            /* 此处判断DHCP Server 返回的IP是否和当前的一致,应该不会返回不一致的情况吧??????? by caopu*/
            if ( pstDHCPPkt->ulYiaddr == pItemInfo->ulUserIpAddr )
            {
                DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPC_Pkt_ProcDHCPACK For Lease!" );
                if ( VOS_ERR == DHCPC_SaveSdbDhcpCtrlBlk( pItemInfo, VOS_TRUE ) )
                {
                    DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_136);
                    DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPC_Pkt_ProcDHCPACK save SDB after renew err!" );
                    /*add by z00113478 此时错误应把控制块删除*/
                    DHCPC_FreeDhcpCtrlBlk( pItemInfo->ulDHCPCtlIdx, pItemInfo->ulTEIDC, pItemInfo->ucUser, pItemInfo->ulPdpIndex );
                    return VOS_ERR;
                }

                if (VOS_OK != DHCPC_NotifyBKUpdate(pItemInfo->ulTEIDC))
                {
                    /* 只添加打点计数 */
                    DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_262);
                }

            }
            else
            {
                DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_216);
                /* 地址不一致释放当前IP */
                if ( VOS_ERR == DHCPC_SendMsgToLAP2( pstDhcpCtrlBlkNode, DHCPC_SND2_LAP2_ADDR_REL_MSG ) )
                {
                    DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_137);
                    DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPC_Pkt_ProcDHCPACK delete user !" );
                    return VOS_ERR;
                }

                /* 发送release消息 */
                ( VOID )DHCPC_Pkt_Send( DHCP_RELEASE, pItemInfo );
                DHCPC_FreeDhcpCtrlBlk( pItemInfo->ulDHCPCtlIdx, pItemInfo->ulTEIDC, pItemInfo->ucUser, pItemInfo->ulPdpIndex );

            }
            break;
        }
        default:
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_138);
            VOS_DBGASSERT( 0 );
            break;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : DHCPC_PktProc_NACK
 功能描述  : 处理nack报文
 输入参数  : DHCP_S  *pstDHCPPkt
             DHCPC_INFO_S* pItemInfo
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2002年11月23日
    作    者   : yuqingping(25027)
    修改内容   : 新生成函数

*****************************************************************************/
ULONG DHCPC_Pkt_ProcDHCPNACK ( DHCPC_CTRLBLK_NODE* pstDhcpCtrlBlkNode )
{
    /*
    *1、对于初始申请用户，通知GTPC/PPPC不成功，删临时控制块
    *2、对于续申请用户，通知GTPC删IP上下文
    */
    DHCPC_TEMPCTRLBLK    *pItemInfo = NULL;

    if(NULL == pstDhcpCtrlBlkNode)
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_139);
        DHCPC_DebugPrint(PTM_LOG_DEBUG,  "\r\nDHCPC_Pkt_ProcDHCPNACK NULL error!" );
        return VOS_ERR;
    }

    pItemInfo = &( pstDhcpCtrlBlkNode->stDhcpcTmpCtlBlk );

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n-->DHCPC_Pkt_ProcDHCPNACK()" );

    if ( ( DHCPC_STATE_REQUEST        != pItemInfo->usDhcpStatus )
         && ( DHCPC_STATE_LEASE        != pItemInfo->usDhcpStatus )
         && ( DHCPC_STATE_ReNewing        != pItemInfo->usDhcpStatus )
         && ( DHCPC_STATE_PreReBinding    != pItemInfo->usDhcpStatus )
         && ( DHCPC_STATE_ReBinding        != pItemInfo->usDhcpStatus ) )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_140);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\nDHCPC_Pkt_ProcDHCPNACK state err!" );
        return VOS_ERR;
    }

    switch ( pItemInfo->usDhcpStatus )
    {
        case DHCPC_STATE_REQUEST  :
            DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\nReceive NAK msg from server when renew IP!" );

            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_220);
            ( VOID )DHCPC_SendMsgToLAP2( pstDhcpCtrlBlkNode ,DHCPC_SND2_LAP2_ADDR_FAILED_MSG );
            /*删除临时控制块节点，释放内存*/
            DHCPC_FreeDhcpCtrlBlk( pstDhcpCtrlBlkNode->stDhcpcTmpCtlBlk.ulDHCPCtlIdx, pstDhcpCtrlBlkNode->stDhcpcTmpCtlBlk.ulTEIDC, pstDhcpCtrlBlkNode->stDhcpcTmpCtlBlk.ucUser, pstDhcpCtrlBlkNode->stDhcpcTmpCtlBlk.ulPdpIndex);
            DHCPC_DelNode( DHCPC_INVALID_INDEX, pstDhcpCtrlBlkNode );
            DHCPC_FreeDhcpTmpNode( pstDhcpCtrlBlkNode );
            break;

        case DHCPC_STATE_LEASE :
        case DHCPC_STATE_ReNewing:
        case DHCPC_STATE_PreReBinding:
        case DHCPC_STATE_ReBinding:
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_141);
            DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\nReceive NAK msg from server when renew IP!" );

            (VOID)DHCPC_StopTimer(pItemInfo->ucAddressType, pItemInfo->ulTEIDC, 0);
            ( VOID )DHCPC_SendMsgToLAP2( pstDhcpCtrlBlkNode,DHCPC_SND2_LAP2_ADDR_REL_MSG );
            DHCPC_FreeDhcpCtrlBlk( pstDhcpCtrlBlkNode->stDhcpcTmpCtlBlk.ulDHCPCtlIdx, pstDhcpCtrlBlkNode->stDhcpcTmpCtlBlk.ulTEIDC, pstDhcpCtrlBlkNode->stDhcpcTmpCtlBlk.ucUser, pstDhcpCtrlBlkNode->stDhcpcTmpCtlBlk.ulPdpIndex);

            break;

        default:
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_142);
            VOS_DBGASSERT( 0 );
            break;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : DHCPC_SendMsgToLAP2
 功能描述  : DHCPC向LAP2发送消息函数，根据单板类型选择不同的发送方式
 输入参数  : DHCPC_CTRLBLK_NODE* pstDhcpCtrlBlkNode, UCHAR MsgType
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年11月25日
    作    者   : zhangyang 00142225
    修改内容   : 新生成函数
*****************************************************************************/
ULONG DHCPC_SendMsgToLAP2 ( DHCPC_CTRLBLK_NODE* pstDhcpCtrlBlkNode, UCHAR MsgType )
{
    ULONG ulRetValue = 0;
    LAP2_DHCPC_MSG_S stLapDhcpcMsg = {0};
    DHCPC_TEMPCTRLBLK *pItemInfo = NULL;
    DHCPC_CTRLBLK *pstDhcpcCtlBlk = NULL;

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n-->DHCPC_SendMsgToLAP2()" );
    DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_231);

    if (NULL == pstDhcpCtrlBlkNode)
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_232);
        DHCPC_DebugPrint(PTM_LOG_DEBUG,  "\r\n DHCPC_SendMsgToLAP2-pstDhcpCtrlBlkNode=null!");
        return VOS_ERR;
    }

    pItemInfo = &( pstDhcpCtrlBlkNode->stDhcpcTmpCtlBlk );

    /*获取DHCP控制块*/
    pstDhcpcCtlBlk = (DHCPC_CTRLBLK *)DHCPC_CalcCtlBlkHashValue(pItemInfo->ulDHCPCtlIdx, pItemInfo->ulTEIDC);
    if (NULL == pstDhcpcCtlBlk)
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_245);
        DHCPC_DebugPrint(PTM_LOG_DEBUG,
            "\r\n DHCPC_Pkt_SendMsgtoLAP2 DHCPCTRL Index is wrong= %u!", pItemInfo->ulDHCPCtlIdx);
        return VOS_ERR;
    }

    /* 填充消息内容 */
    stLapDhcpcMsg.usVpnId = pItemInfo->usVpnId;
    stLapDhcpcMsg.aulPdpAddr[0] = pItemInfo->ulUserIpAddr;
    stLapDhcpcMsg.aulPdpAddr[1] = 0xFFFFFFFF;
    stLapDhcpcMsg.aulPdpAddr[2] = 0xFFFFFFFF;
    stLapDhcpcMsg.aulPdpAddr[3] = 0xFFFFFFFF;
    stLapDhcpcMsg.ucAddressType = pItemInfo->ucAddressType;
    stLapDhcpcMsg.usPoolIndex = pItemInfo->usPoolIndex;
    stLapDhcpcMsg.ucSCID = DHCPC_SELF_CMPIDX_INSG;
    stLapDhcpcMsg.aulAgentIP[0] = pItemInfo->ulAgetIP;
    /* zhangjinquan 00175135 DHCPv6特性 2012-07-14 start */
    /* 对于V4的发消息接口，直接将第二个ULONG置全F */
    stLapDhcpcMsg.aulAgentIP[1] = VOS_NULL_LONG;
    /* zhangjinquan 00175135 DHCPv6特性 2012-07-14 end   */
    stLapDhcpcMsg.ulIndex = pItemInfo->ulPdpIndex;
    stLapDhcpcMsg.usDhcpGroupIndex = pItemInfo->usDhcpGroupIndex;
    stLapDhcpcMsg.ucMsgType = MsgType;
    stLapDhcpcMsg.usApnIndex = pstDhcpcCtlBlk->usApnIndex;
    stLapDhcpcMsg.aulPrimaryDNS[0] = pItemInfo->ulPriDNSIP;
    stLapDhcpcMsg.aulSecondaryDNS[0] = pItemInfo->ulSecDNSIP;
    stLapDhcpcMsg.ucUserType = pItemInfo->ucUserType;
    stLapDhcpcMsg.ucGtpVer = pItemInfo->ucUser;
    stLapDhcpcMsg.ulTeidc = pItemInfo->ulTEIDC;
    stLapDhcpcMsg.ucStaticIpRouteType = 0;
    stLapDhcpcMsg.aulMSISDN[0] = pItemInfo->aulMSISDN[0];
    stLapDhcpcMsg.aulMSISDN[1] = pItemInfo->aulMSISDN[1];
    stLapDhcpcMsg.ucLAPNo = pItemInfo->ucLAPNo;

    DHCPC_DebugPrint(PTM_LOG_DEBUG,
        "\r\n DHCPC_SendMsgToLAP2ByFCM lapNo = %u!", pItemInfo->ucLAPNo);

    ulRetValue = DHCPC_SendAddrMsgToLAP(&stLapDhcpcMsg,
                                           sizeof(LAP2_DHCPC_MSG_S),
                                           pItemInfo->ulUserIpAddr,
                                           pItemInfo->ucLAPNo);
    if (VOS_OK != ulRetValue)
    {
        return ulRetValue;
    }

    return ulRetValue;
}


/*****************************************************************************
 函 数 名  : DHCPC_SendMsgToLAP2_WithOriginalMsg
 功能描述  : DHCPC向LAP2发送消息函数，直接通过LAP2发送过来的消息构造消息内容，根据单板类型选择不同的发送方式
 输入参数  : LAP2_DHCPC_MSG_S *pstLapDhcpcMsg, UCHAR ucMsgType
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年01月25日
    作    者   : zhangjinquan z00175135
    修改内容   : 新生成函数
  2.日    期   : 2012年02月15日
    作    者   : z00175135
    修改内容   : 修改函数 删除无实际使用的变量
*****************************************************************************/
ULONG DHCPC_SendMsgToLAP2_WithOriginalMsg(LAP2_DHCPC_MSG_S *pstLapDhcpcMsg, UCHAR ucMsgType)
{
    ULONG ulRet = 0;
    LAP2_DHCPC_MSG_S stLapDhcpcMsgOut = {0};
    LAP2_DHCPC_MSG_S *pstLapDhcpcMsgOut = &stLapDhcpcMsgOut;

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n-->DHCPC_SendMsgToLAP2_WithOriginalMsg()" );
    DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_246);

    if (NULL == pstLapDhcpcMsg)
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_247);
        DHCPC_DebugPrint(PTM_LOG_DEBUG,  "\r\n DHCPC_SendMsgToLAP2_WithOriginalMsg-pstLapDhcpcMsg=null!");
        return VOS_ERR;
    }

    switch(ucMsgType)
    {
        case DHCPC_SND2_LAP2_ADDR_REL_MSG:
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_249);
            break;
        case DHCPC_SND2_LAP2_NO_RSP_MSG:
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_251);
            break;
        case DHCPC_SND2_LAP2_ADDR_FAILED_MSG:
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_252);
            break;
        case DHCPC_SND2_LAP2_ADDR_SUCCESS_MSG:
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_253);
            break;
        case DHCPC_SND2_LAP2_LEASE_REL:
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_254);
            break;
        default:
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_255);
            break;
    }

    DHCPC_DebugPrint(PTM_LOG_DEBUG,
                    "\r\n DHCPC_SendMsgToLAP2_WithOriginalMsg aulPdpAddr=%x,ulAgentIP=%x,usPoolIndex=%d",pstLapDhcpcMsg->aulPdpAddr[0],
                    pstLapDhcpcMsg->aulAgentIP[0],pstLapDhcpcMsg->usPoolIndex);


    /* 填充消息内容 */
    pstLapDhcpcMsgOut->usVpnId = pstLapDhcpcMsg->usVpnId;
    pstLapDhcpcMsgOut->aulPdpAddr[0] = pstLapDhcpcMsg->aulPdpAddr[0];
    pstLapDhcpcMsgOut->aulPdpAddr[1] = IPV4_NOT_USE_ADDULONG;
    pstLapDhcpcMsgOut->aulPdpAddr[2] = IPV4_NOT_USE_ADDULONG;
    pstLapDhcpcMsgOut->aulPdpAddr[3] = IPV4_NOT_USE_ADDULONG;
    pstLapDhcpcMsgOut->ucAddressType = pstLapDhcpcMsg->ucAddressType;
    pstLapDhcpcMsgOut->usPoolIndex = pstLapDhcpcMsg->usPoolIndex;
    pstLapDhcpcMsgOut->ucSCID = DHCPC_SELF_CMPIDX_INSG;
    /* zhangjinquan 00175135 DHCPv6特性 2012-07-14 start */
    pstLapDhcpcMsgOut->aulAgentIP[0] = pstLapDhcpcMsg->aulAgentIP[0];
    pstLapDhcpcMsgOut->aulAgentIP[1] = pstLapDhcpcMsg->aulAgentIP[1];
    /* zhangjinquan 00175135 DHCPv6特性 2012-07-14 end   */
    pstLapDhcpcMsgOut->ulIndex = pstLapDhcpcMsg->ulIndex;
    pstLapDhcpcMsgOut->usDhcpGroupIndex = pstLapDhcpcMsg->usDhcpGroupIndex;
    /* 修改消息类型 */
    pstLapDhcpcMsgOut->ucMsgType = ucMsgType;
    pstLapDhcpcMsgOut->usApnIndex = pstLapDhcpcMsg->usApnIndex;
    pstLapDhcpcMsgOut->aulPrimaryDNS[0] = pstLapDhcpcMsg->aulPrimaryDNS[0];
    pstLapDhcpcMsgOut->aulSecondaryDNS[0] = pstLapDhcpcMsg->aulSecondaryDNS[0];
    pstLapDhcpcMsgOut->ucUserType = pstLapDhcpcMsg->ucUserType;
    pstLapDhcpcMsgOut->ulTeidc= pstLapDhcpcMsg->ulTeidc;
    pstLapDhcpcMsgOut->ucStaticIpRouteType = pstLapDhcpcMsg->ucStaticIpRouteType;
    pstLapDhcpcMsgOut->aulMSISDN[0] = pstLapDhcpcMsg->aulMSISDN[0];
    pstLapDhcpcMsgOut->aulMSISDN[1] = pstLapDhcpcMsg->aulMSISDN[1];
    pstLapDhcpcMsgOut->ucLAPNo = pstLapDhcpcMsg->ucLAPNo;

    ulRet = DHCPC_SendAddrMsgToLAP((VOID *)pstLapDhcpcMsgOut,
                                      sizeof(LAP2_DHCPC_MSG_S),
                                      pstLapDhcpcMsg->aulPdpAddr[0],
                                      pstLapDhcpcMsg->ucLAPNo);
    return ulRet;
}

/*****************************************************************************
 函 数 名  : DHCPC_Pkt_Send
 功能描述  : 发送DHCP报文
 输入参数  : UCHAR ucPktType
             DHCPC_INFO_S* pItemInfo
 输出参数  : 无
 返 回 值  : ULONG
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2002年11月22日
    作    者   : yuqingping(25027)
    修改内容   : 新生成函数
    ---------------------------------
  2.VOS_ERR:发送失败，需要调用函数删临时控制块
    ---------------------------------

  3. 2007年11月21日 caopu 110903

  发送失败，需要调用函数释放控制块结构内存

*****************************************************************************/
ULONG DHCPC_Pkt_Send( UCHAR ucPktType, DHCPC_TEMPCTRLBLK* pItemInfo )
{
    LONG        lRet  = -1;
    PMBUF_S      *pMBuf = NULL;
    DHCP_S      *pstDhcpPkt = NULL;
    LONG        lSecondReturnCode = -1;
    SDB_GSPU_CONTEXT_S *pstContext = VOS_NULL_PTR;
    RM_SOCKET_PATH_S stPath = {0};
    S_OM_EMS_TRC_PARA stTrcPara = {0};
    ULONG ulRet = 0;

    if (NULL == pItemInfo)
    {
        VOS_Assert(0);
        return VOS_ERR;
    }

    /* 申请MBUF */
#if 0
    pMBuf = PMBUF_CreateForControlPacket( 0, 1500, PMBUF_TYPE_DATA, MID_DHCPC );
#endif
    pMBuf = PMBUF_GetPMbuf(MID_DHCPC, 1500);

    if ( pMBuf == NULL )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_150);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\nDHCPC_Pkt_ProcDHCP MBUF memory alloc failed!" );
        return VOS_ERR;
    }

    pstDhcpPkt = PMBUF_MTOD( pMBuf, DHCP_S * );
    PGP_MemZero( pstDhcpPkt, sizeof( DHCP_S ) );

    switch ( ucPktType )
    {
        case DHCP_DISCOVER:
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_211);

            /*填充discovery报文*/
            DHCPC_Pkt_EncapDiscovry( pstDhcpPkt, pItemInfo );
            break;

        case DHCP_REQUEST:
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_212);
            /*填充request报文*/
            DHCPC_Pkt_EncapRequest( pstDhcpPkt, pItemInfo );
            break;

        case DHCP_DECLINE:
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_213);
            /*填充decline报文*/
            DHCPC_Pkt_EncapDecline( pstDhcpPkt, pItemInfo );
            break;

        case DHCP_RELEASE:
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_214);
            /*填充release报文*/
            DHCPC_Pkt_EncapRelease( pstDhcpPkt, pItemInfo );
            break;

        default:
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_151);
            DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\nDHCPC_Pkt_Send invalid DHCP packet type!" );
            ( VOID )PMBUF_Destroy( pMBuf );    /*X34710 Add*/
            pMBuf = NULL;
            return VOS_ERR;
    }

    /*MBuf中报文长度设置*/
    pMBuf->ulTotalDataLength = DHCPC_PKT_LEN;/*需确定长度，没有IP UDP头的长度*/
    pMBuf->stDataBlockDescriptor.ulDataLength = DHCPC_PKT_LEN;
    /*------------------------------------debug show packet----------------------*/
    DHCPC_Dbg_PacketPrintSend( pMBuf );

    lRet = DHCPC_OutPut( ucPktType, pItemInfo, pMBuf, &lSecondReturnCode );
    if ( VOS_OK != lRet )
    {
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\nDHCPC_Pkt_Send send packet 1st direction failed!" );
        ( VOID )PMBUF_Destroy( pMBuf );
        pMBuf = NULL;
        /*此时不删控制块,由调用函数删*/
        if ( VOS_ERR == lSecondReturnCode )
        {
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_152);
            /*所有方向上的发送都失败，返回失败，删除临时控制快，否则认为发送成功*/
            DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\nDHCPC_Pkt_Send send packet 2nd direction failed!" );
            return VOS_ERR;
        }
    }
    else
    {
        ULONG ulDirection = TRC_DIRECTION_RIGHT_OUT_PGW;

        if(( E_NET_ELEMENT_ROLE_GGSN == pItemInfo->ucRole )||( E_NET_ELEMENT_ROLE_PGW_AND_SGW == pItemInfo->ucRole ))
        {
            ulDirection = TRC_DIRECTION_RIGHT_OUT_UGW;
        }
        UGW_OmUsrMsgTrace((UCHAR *)pstDhcpPkt,
                     GUSER_MSGTYPE_DHCPV4,
                     (ULONG)ucPktType + ulDirection,
                     (USHORT)DHCPC_PKT_LEN,
                     (UCHAR *)(pItemInfo->aulIMSI),
                     (UCHAR *)(pItemInfo->aulIMEI),
                     (UCHAR *)(pItemInfo->aulMSISDN),
                     pItemInfo->ucRandomNo);

        /* DHCP信令消息V接口跟踪 */ /* 将TrcGetTraceFlag()调用放在跟踪函数之外,提升效率 */
        if (VOS_TRUE == TrcGetTraceFlag(TRC_TYPE_V))
        {
            DHCPC_OmVIfMsgTrc((ULONG)(ucPktType),
                                ulDirection,
                                (UCHAR*)pstDhcpPkt,
                                DHCPC_PKT_LEN,
                                LAP_IPV4,
                                &(pItemInfo->ulSrvIp));
        }

        /* BEGIN: Added for PN:全网跟踪  by LiHairong, 2010/4/10 */
        stPath.ulLocalAddr = pItemInfo->ulAgetIP;
        stPath.ulPeerAddr  = pItemInfo->ulSrvIp;
        if (g_ucSoftParaDHCPKPN & ((UCHAR)0x02))
        {
            stPath.usLocalPort = DHCPS_PKT_PORTNO;
        }
        else
        {
            stPath.usLocalPort = DHCPC_PKT_PORTNO;
        }
        stPath.usPeerPort = DHCPS_PKT_PORTNO;

        /*根据PDP INDEX, 获取上下文*/
        ulRet = (ULONG)SDB_GetContextByIndex(pItemInfo->ulPdpIndex, (UCHAR**)&pstContext );
        if ( ( ulRet == VOS_OK ) && ( NULL != pstContext ) )
        {
            stTrcPara.pucTrcMsg = (UCHAR *)pstDhcpPkt;
            stTrcPara.ucMsgType = ucPktType;
            stTrcPara.ucUgwRole = pstContext->ucUgwRole;
            stTrcPara.usMsgLen = DHCPC_PKT_LEN;
            stTrcPara.ulEmsTrcDir = M_EMS_TRC_SEND_MSG;
            stTrcPara.ulUsrTrcDir = TRC_DIRECTION_RIGHT_OUT_PGW;
            stTrcPara.usTraceId = pstContext->usTraceId;
            stTrcPara.ucSgwTrcFlg = pstContext->ucSgwIsTraceFlag;
            stTrcPara.ucPgwTrcFlg = pstContext->ucPgwIsTraceFlag;
            stTrcPara.ucSgwTrcIf = pstContext->ucSgwListOfInterfaces;
            stTrcPara.ucPgwTrcIf = pstContext->ucPgwListOfInterfaces;
            stTrcPara.ucProType = GTPC_GUSER_MSGTYPE_DHCPV4;
            stTrcPara.ucMsgIntf = VOS_NULL_BYTE;
            stTrcPara.ucMsgSndFlg = 0;
            if((1 == stTrcPara.ucSgwTrcFlg)
                || (1 == stTrcPara.ucPgwTrcFlg))
            {
                UGW_OmEmsTrcMsgTrc(&stTrcPara,&stPath);
            }
        }
        /* END:   Added for PN:全网跟踪  by LiHairong, 2010/4/10 */

        /* PGW性能统计*/
        if ((E_NET_ELEMENT_ROLE_PGW == pItemInfo->ucRole) || (E_NET_ELEMENT_ROLE_PGW_AND_SGW == pItemInfo->ucRole))
        {
            DHCPC_PGWPerfStat(ucPktType);
        }

    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : DHCPC_Pkt_EncapDiscovry
 功能描述  : 封装discovery报文
 输入参数  : IP_S *pstIpPkt
             DHCPC_INFO_S* pItemInfo
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2002年11月22日
    作    者   : yuqingping(25027)
    修改内容   : 新生成函数
  ---------------------------------------------------------------------------
  2. 2007年11月21日 caopu 110903
    修改内容   : client identifier 字段改为携带 MSISDN
      ---------------------------------------------------------------------------
  3. 2010年08月07日 w00140934
    修改内容   : 修改控制块索引与Xid的封装方式
*****************************************************************************/
VOID DHCPC_Pkt_EncapDiscovry ( DHCP_S * pstDhcpPkt, DHCPC_TEMPCTRLBLK* pItemInfo )
{
    /*增加lease time选项的发送*/
    DHCP_S  *pDhcp = NULL;
    ULONG   *pulMagicCookie = NULL;
    UCHAR   *pucDhcpOption = NULL;
    UCHAR   szChaddrr[6] = {0};
    ULONG   ulClientIdLen = 0;

    if((NULL == pstDhcpPkt)||(NULL == pItemInfo))
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_153);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\nDHCPC_Pkt_EncapDiscovry pstDhcpPkt = NULL");
        return;
    }

    /* zhangjinquan DTS2011122601821 review问题-去掉多余的初始化处理 2012-01-02 */
    //PGP_MemZero(szChaddrr, sizeof(UCHAR)*6);
    //PGP_MemZero(szMSISDN, sizeof(UCHAR)*16);
    DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n-->DHCPC_Pkt_EncapDiscovry()" );
    /*----------------- 填充DHCP固定字段内容-----------------  */
    pDhcp    = pstDhcpPkt;

    /*获取物理地址*/
    DHCPC_ConstructPhyAddr(pItemInfo, szChaddrr);

    /*获取xid*/
    pItemInfo->ulXid = DHCPC_Pkt_GetTransId(pItemInfo);

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPC_Pkt_EncapDiscovry: pItemInfo->ulXid = %x,pItemInfo->ulDHCPCtlIdx = %x",
                                pItemInfo->ulXid, pItemInfo->ulDHCPCtlIdx );
    DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n pItemInfo->ucSCID = %x,g_ulDHCPCTransId = %x",
                            pItemInfo->ucSCID, g_ulDHCPCTransId );

    DHCP_FILLFIXEDFIELD(    DHCP_OP_REQUEST, pDhcp,
                            pItemInfo->ulXid, 0,
                            0, pItemInfo->ulUserIpAddr,
                            pItemInfo->ulAgetIP, 0, szChaddrr );

    pDhcp->ulSiaddr=0;      /*此参数在REQUEST报文中有用*/
    pDhcp->szSname[0] = 0;
    pDhcp->szFile[0] = 0;

    /*----------------- 填充DHCP的可选字段 ------------------*/
    /*填充MAGICCOOKIE*/
    pulMagicCookie  = ( ULONG * )( ( VOID * )( pDhcp + 1 ) );
    DHCP_FILLMAGICCODE( pulMagicCookie );

    /*"DHCP message type" */
    pucDhcpOption    = ( UCHAR * )( pulMagicCookie + 1 );
    DHCP_FILLMESSAGETYPEOPTION( pucDhcpOption, DHCP_DISCOVER );

    if((0 ==(g_ucSoftParaDHCPKPN & ((UCHAR)0x20)))
        &&((VOS_NULL_DWORD != pItemInfo->aulMSISDN[0])
        || (VOS_NULL_DWORD != pItemInfo->aulMSISDN[1])))
    {
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n-->pItemInfo->aulMSISDN(0) = %x,pItemInfo->aulMSISDN[1] = %x",
                                pItemInfo->aulMSISDN[0],pItemInfo->aulMSISDN[1] );
        ulClientIdLen = DHCPC_FillClientIdOption(pucDhcpOption, pItemInfo->aulMSISDN);
        if (0 != ulClientIdLen)
        {
            pucDhcpOption += ulClientIdLen;
        }
    }

    /*"server identifier" */
    /*"IP Address Lease Time" x34710 add*/
    if ( 0 != pItemInfo->usLease )
    {
        DHCP_FILLULONGOPTION( pucDhcpOption, DHCP_IPLEASETIME_CODE, pItemInfo->usLease );
    }

    /*
     *只为了填充多余信息，补齐长度
     *UCHAR *pucHName;
     *pucHName="HuaWei MA5200 dhcp client inbed";
     *DHCP_FILLHOSTNAME(pucDhcpOption,pucHName,31);
     */
    if((g_ucSoftParaDHCPKPN & ((UCHAR)0x40)) || (g_ucSoftParaDHCPKPN & ((UCHAR)0x80)))
    {
        if((g_ucSoftParaDHCPKPN & ((UCHAR)0x40)) && (0 == (g_ucSoftParaDHCPKPN & ((UCHAR)0x80))))
        {
            *pucDhcpOption++ = DHCP_REQPARAM_CODE;
            *pucDhcpOption++ = 0x01;
            *pucDhcpOption++ = DHCP_DNSIP_CODE;
        }
        if ((0 == (g_ucSoftParaDHCPKPN & ((UCHAR)0x40))) && (g_ucSoftParaDHCPKPN & ((UCHAR)0x80)))
        {
            *pucDhcpOption++ = DHCP_REQPARAM_CODE;
            *pucDhcpOption++ = 0x03;
            *pucDhcpOption++ = DHCP_SUBNETMASK_CODE;
            *pucDhcpOption++ = DHCP_DNSIP_CODE;
            *pucDhcpOption++ = DHCP_NBNS_CODE;
        }
        if ((g_ucSoftParaDHCPKPN & ((UCHAR)0x40)) && (g_ucSoftParaDHCPKPN & ((UCHAR)0x80)))
        {
            *pucDhcpOption++ = DHCP_REQPARAM_CODE;
            *pucDhcpOption++ = 0x02;
            *pucDhcpOption++ = DHCP_DNSIP_CODE;
            *pucDhcpOption++ = DHCP_NBNS_CODE;
        }
    }
    else
    {
        DHCP_FILLPARALISTOPTION( pucDhcpOption );   /*lfb 问题单D01785*/
    }

    /*填充ENDOPTION*/
    DHCP_FILLENDOPTION( pucDhcpOption );

    DHCP_LENGTHTO300( pulMagicCookie,pucDhcpOption ); /*长度达到308   且清0*/

    return ;
}

/*****************************************************************************
 函 数 名  : DHCPC_Pkt_EncapRequest
 功能描述  : 封装request报文
 输入参数  : IP_S *pstIpPkt
             DHCPC_INFO_S* pItemInfo
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2002年11月22日
    作    者   : yuqingping(25027)
    修改内容   : 新生成函数

*****************************************************************************/
VOID DHCPC_Pkt_EncapRequest ( DHCP_S * pstDhcpPkt, DHCPC_TEMPCTRLBLK* pItemInfo )
{
    DHCP_S        *pDhcp = NULL;
    ULONG        *pulMagicCookie = NULL;
    UCHAR        *pucDhcpOption = NULL;
    /* zhangjinquan DTS2011122601821 review问题-去掉多余的初始化处理 2012-01-02 */
    UCHAR        szChaddrr[6] = {0};
    ULONG        ulClientIdLen = 0;

    if((NULL == pstDhcpPkt)||(NULL == pItemInfo))
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_154);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\nDHCPC_Pkt_EncapRequest pstDhcpPkt = NULL");
        return;
    }

    pDhcp = pstDhcpPkt;
    pDhcp->ulSiaddr=0;  /* (ULONG)VOS_HTONL(pItemInfo->ulDhcpSvrAddr); lfb 此参数在REQUEST报文中有用*/
    pDhcp->szSname[0] = 0;   /*问题单： D01622*/
    pDhcp->szFile[0] = 0;

    DHCPC_ConstructPhyAddr( pItemInfo, szChaddrr );
    /*----------------- 填充DHCP的可选字段 ------------------*/
    /*填充MAGICCOOKIE*/
    pulMagicCookie  = ( ULONG * )( ( VOID * )( pDhcp + 1 ) );
    DHCP_FILLMAGICCODE( pulMagicCookie );

    /*"DHCP message type" */
    pucDhcpOption    = ( UCHAR * )( pulMagicCookie + 1 );
    DHCP_FILLMESSAGETYPEOPTION( pucDhcpOption, DHCP_REQUEST );

    /*"client identifier" */
    /* z00175135 DTS2012041905330 无msisdn的情况不携带 2012-04-20 start */
    if((!(g_ucSoftParaDHCPKPN & ((UCHAR)0x20)))
        && ((VOS_NULL_DWORD != pItemInfo->aulMSISDN[0])
            || (VOS_NULL_DWORD != pItemInfo->aulMSISDN[1])))
    {
        ulClientIdLen = DHCPC_FillClientIdOption(pucDhcpOption, pItemInfo->aulMSISDN);
        if (0 != ulClientIdLen)
        {
            pucDhcpOption += ulClientIdLen;
        }
    }
    /* z00175135 DTS2012041905330 无msisdn的情况不携带 2012-04-20 end   */

    switch ( pItemInfo->usDhcpStatus )
    {
        case DHCPC_STATE_REQUEST :

            DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n-->DHCPC_Pkt_EncapRequest()" );

            /*----------------- 填充DHCP固定字段内容-----------------  */
            DHCP_FILLFIXEDFIELD( DHCP_OP_REQUEST, pDhcp,
                                 pItemInfo->ulXid, 0,
                                 0, 0/*pItemInfo->ulUserIpAddr*/, /*X34710 modify*/
                                 pItemInfo->ulAgetIP,0, szChaddrr );

            /*填充REQUEST IP*/
            if ( pItemInfo->ulUserIpAddr!=NULL )
            {
                DHCP_FILLIPOPTION( pucDhcpOption, ( ULONG )DHCP_REQUESTEDIP_CODE, pItemInfo->ulUserIpAddr );
            }

            /*"server identifier" */
            /*??协议说MUST 携带"server identifier"的??*/
            if ( pItemInfo->ulSrvIp!=NULL )
            {
                DHCP_FILLIPOPTION(pucDhcpOption,(ULONG)DHCP_SERVERIP_CODE,pItemInfo->ulSrvIp);/*???问题单号:D01030*/
            }

            /*MAY* "release time" REQUEST报文必带选项   (DHCPDISCOVER or DHCPREQUEST)*/
            if ( 0 != pItemInfo->usLease )
            {
                DHCP_FILLULONGOPTION( pucDhcpOption, ( ULONG )DHCP_IPLEASETIME_CODE, ( ULONG )( pItemInfo->usLease ) );
            }

            break;

        case DHCPC_STATE_LEASE :
        case DHCPC_STATE_ReNewing:
        case DHCPC_STATE_PreReBinding:
        case DHCPC_STATE_ReBinding:

            DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n-->DHCPC_Pkt_EncapRenew()" );

            /*重新获取xid*/
            pItemInfo->ulXid = DHCPC_Pkt_GetTransId(pItemInfo);

            DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPC_Pkt_EncapRequest: pItemInfo->ulXid = %x,pItemInfo->ulDHCPCtlIdx = %x",
                                pItemInfo->ulXid, pItemInfo->ulDHCPCtlIdx );
            DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n pItemInfo->ucSCID = %x,g_ulDHCPCTransId = %x",
                                pItemInfo->ucSCID, g_ulDHCPCTransId );

            /*----------------- 填充DHCP固定字段内容-----------------  */
            DHCP_FILLFIXEDFIELD( DHCP_OP_REQUEST, pDhcp,
                                 pItemInfo->ulXid, 0, /*modified by z00113478lease时的xid又需要重新填充*/
                                 0, 0/*pItemInfo->ulUserIpAddr*/,  /*X34710 modify*/
                                 pItemInfo->ulAgetIP,
                                 pItemInfo->ulUserIpAddr, szChaddrr );/* Modifyed by niutao 60002996 at 2006-08-25 V800R002C05B010 for KPN Project*/
            /*MAY  lease time */
            if ( 0 != pItemInfo->usLease )
            {
                DHCP_FILLULONGOPTION( pucDhcpOption, DHCP_IPLEASETIME_CODE, pItemInfo->usLease );
            }

            break;

        default:
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_155);
            VOS_DBGASSERT( 1 == 0 );
            return;
    };
    if((g_ucSoftParaDHCPKPN & ((UCHAR)0x40)) || (g_ucSoftParaDHCPKPN & ((UCHAR)0x80)))
    {
        if((g_ucSoftParaDHCPKPN & ((UCHAR)0x40)) && (0 == (g_ucSoftParaDHCPKPN & ((UCHAR)0x80))))
        {
            *pucDhcpOption++ = DHCP_REQPARAM_CODE;
            *pucDhcpOption++ = 0x01;
            *pucDhcpOption++ = DHCP_DNSIP_CODE;
        }
        if ((0 == (g_ucSoftParaDHCPKPN & ((UCHAR)0x40))) && (g_ucSoftParaDHCPKPN & ((UCHAR)0x80)))
        {
            *pucDhcpOption++ = DHCP_REQPARAM_CODE;
            *pucDhcpOption++ = 0x03;
            *pucDhcpOption++ = DHCP_SUBNETMASK_CODE;
            *pucDhcpOption++ = DHCP_DNSIP_CODE;
            *pucDhcpOption++ = DHCP_NBNS_CODE;
        }
        if ((g_ucSoftParaDHCPKPN & ((UCHAR)0x40)) && (g_ucSoftParaDHCPKPN & ((UCHAR)0x80)))
        {
            *pucDhcpOption++ = DHCP_REQPARAM_CODE;
            *pucDhcpOption++ = 0x02;
            *pucDhcpOption++ = DHCP_DNSIP_CODE;
            *pucDhcpOption++ = DHCP_NBNS_CODE;
        }
    }
    else
    {
        DHCP_FILLPARALISTOPTION( pucDhcpOption ); /* 问题单D01785 // lease时可能要更新选项*/
    }
    /*填充ENDOPTION*/
    DHCP_FILLENDOPTION( pucDhcpOption );
    DHCP_LENGTHTO300( pulMagicCookie,pucDhcpOption ); /*长度达到308   且清0*/

    return ;
}


/*****************************************************************************
 函 数 名  : DHCPC_Pkt_EncapDecline
 功能描述  : 封装decline报文
 输入参数  : IP_S *pstIpPkt
             DHCPC_INFO_S* pItemInfo
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2002年11月22日
    作    者   : yuqingping(25027)
    修改内容   : 新生成函数

*****************************************************************************/
VOID DHCPC_Pkt_EncapDecline( DHCP_S * pstDhcpPkt, DHCPC_TEMPCTRLBLK* pItemInfo )
{
    DHCP_S        *pDhcp = NULL;
    ULONG         *pulMagicCookie = NULL;
    ULONG         ulXid = 0;
    UCHAR         *pucDhcpOption = NULL;
    UCHAR        szChaddrr[6] = {0};
    ULONG        ulClientIdLen = 0;

    if((NULL == pstDhcpPkt)||(NULL == pItemInfo))
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_156);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\nDHCPC_Pkt_EncapDeclinepstDhcpPkt = NULL");
        return;
    }

    ulXid = DHCPC_Pkt_GetTransId(pItemInfo);

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPC_Pkt_EncapDecline: pItemInfo->ulXid = %x,pItemInfo->ulDHCPCtlIdx = %x",
                                pItemInfo->ulXid, pItemInfo->ulDHCPCtlIdx );
    DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n pItemInfo->ucSCID = %x,g_ulDHCPCTransId = %x",
                            pItemInfo->ucSCID, g_ulDHCPCTransId );
    /*----------------- 填充DHCP固定字段内容-----------------  */
    pDhcp = pstDhcpPkt;
    DHCPC_ConstructPhyAddr( pItemInfo, szChaddrr );
    DHCP_FILLFIXEDFIELD( DHCP_OP_REQUEST, pDhcp,
                         ulXid, 0,
                         0, 0,
                         pItemInfo->ulAgetIP,
                         0, szChaddrr );
    pDhcp->szSname[0] = 0;
    pDhcp->szFile[0] = 0;

    /*----------------- 填充DHCP的可选字段 ------------------*/
    /*填充MAGICCOOKIE*/
    pulMagicCookie  = ( ULONG * )( ( VOID * )( pDhcp + 1 ) );
    DHCP_FILLMAGICCODE( pulMagicCookie );

    /*"DHCP message type" */
    pucDhcpOption    = ( UCHAR * )( pulMagicCookie + 1 );
    DHCP_FILLMESSAGETYPEOPTION( pucDhcpOption, DHCP_DECLINE );


    /*"client identifier" */
    /* z00175135 DTS2012041905330 无msisdn的情况不携带 2012-04-20 start */
    if ((!(g_ucSoftParaDHCPKPN & ((UCHAR)0x20)))
        && ((VOS_NULL_DWORD != pItemInfo->aulMSISDN[0])
            || (VOS_NULL_DWORD != pItemInfo->aulMSISDN[1])))
    {
        ulClientIdLen = DHCPC_FillClientIdOption(pucDhcpOption, pItemInfo->aulMSISDN);
        if (0 != ulClientIdLen)
        {
            pucDhcpOption += ulClientIdLen;
        }
    }
    /* z00175135 DTS2012041905330 无msisdn的情况不携带 2012-04-20 end   */

    DHCPC_SetTmpCtrlBlkSrvIp(pItemInfo);

    DHCP_FILLIPOPTION(pucDhcpOption,(ULONG)DHCP_SERVERIP_CODE,pItemInfo->ulSrvIp);


    /*填充REQUEST IP X34710 Add*/
    DHCP_FILLIPOPTION( pucDhcpOption, DHCP_REQUESTEDIP_CODE, pItemInfo->ulUserIpAddr );

    /*填充ENDOPTION*/
    DHCP_FILLENDOPTION( pucDhcpOption );
    DHCP_LENGTHTO300( pulMagicCookie,pucDhcpOption ); /*长度达到308   且清0*/

    return ;
}


/*****************************************************************************
 函 数 名  : DHCPC_Pkt_EncapRelease
 功能描述  : 封装release报文
 输入参数  : IP_S *pstIpPkt
             DHCPC_INFO_S* pItemInfo
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2002年11月22日
    作    者   : yuqingping(25027)
    修改内容   : 新生成函数

*****************************************************************************/
VOID DHCPC_Pkt_EncapRelease ( DHCP_S * pstDhcpPkt, DHCPC_TEMPCTRLBLK* pItemInfo )
{
    DHCP_S       *pDhcp = NULL;
    ULONG        *pulMagicCookie = NULL;
    ULONG        ulXid = 0;
    UCHAR        *pucDhcpOption = NULL;
    /* zhangjinquan DTS2011122601821 review问题-增加初始化处理 2012-01-02 */
    UCHAR        szChaddrr[6] = {0};
    ULONG        ulClientIdLen = 0;

    if((NULL == pstDhcpPkt)||(NULL == pItemInfo))
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_157);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\nDHCPC_Pkt_EncapRelease pstDhcpPkt = NULL");
        return;
    }

    /*----------------- 填充DHCP固定字段内容-----------------  */
    pDhcp = pstDhcpPkt;
    DHCPC_ConstructPhyAddr( pItemInfo, szChaddrr );

    ulXid = DHCPC_Pkt_GetTransId(pItemInfo);

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPC_Pkt_EncapRelease: ulXid = %x,pItemInfo->ulDHCPCtlIdx = %x",
                                ulXid, pItemInfo->ulDHCPCtlIdx );
    DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n pItemInfo->ucSCID = %x,g_ulDHCPCTransId = %x",
                            pItemInfo->ucSCID, g_ulDHCPCTransId );

    DHCP_FILLFIXEDFIELD( DHCP_OP_REQUEST, pDhcp,
                         ulXid, 0,
                         0, 0,
                         pItemInfo->ulAgetIP,pItemInfo->ulUserIpAddr, szChaddrr );
    pDhcp->szSname[0] = 0;
    pDhcp->szFile[0] = 0;

    /*----------------- 填充DHCP的可选字段 ------------------*/
    /*填充MAGICCOOKIE*/
    pulMagicCookie  = ( ULONG * )( ( VOID * )( pDhcp + 1 ) );
    DHCP_FILLMAGICCODE( pulMagicCookie );

    /*"DHCP message type" */
    pucDhcpOption    = ( UCHAR * )( pulMagicCookie + 1 );
    DHCP_FILLMESSAGETYPEOPTION( pucDhcpOption, DHCP_RELEASE );

    /*"client identifier" */
    /* z00175135 DTS2012041905330 无msisdn的情况不携带 2012-04-20 start */
    if((!(g_ucSoftParaDHCPKPN & ((UCHAR)0x20)))
        && ((VOS_NULL_DWORD != pItemInfo->aulMSISDN[0])
            || (VOS_NULL_DWORD != pItemInfo->aulMSISDN[1])))
    {
        ulClientIdLen = DHCPC_FillClientIdOption(pucDhcpOption, pItemInfo->aulMSISDN);
        if (0 != ulClientIdLen)
        {
            pucDhcpOption += ulClientIdLen;
        }
    }
    /* z00175135 DTS2012041905330 无msisdn的情况不携带 2012-04-20 end   */

    DHCPC_SetTmpCtrlBlkSrvIp(pItemInfo);

    DHCP_FILLIPOPTION(pucDhcpOption,(ULONG)DHCP_SERVERIP_CODE,pItemInfo->ulSrvIp);

    /*填充ENDOPTION*/
    DHCP_FILLENDOPTION( pucDhcpOption );
    DHCP_LENGTHTO300( pulMagicCookie,pucDhcpOption ); /*长度达到308   且清0*/

    return;
}

/*****************************************************************************
 函 数 名  : DHCPC_Pkt_GetTransId
 功能描述  : 获取报文的Xid，
 输入参数  : 无
 输出参数  : 报文的xid
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2002年11月24日
    作    者   : yuqingping(25027)
    修改内容   : 新生成函数
  ---------------------------------------------------------------------------
  2. 2007年11月21日 caopu 110903
    修改内容   : Xid 修改为 SCID(4 bit)+PDPIndex(24 bit)+DHCPTransID(4 bit)
*****************************************************************************/
ULONG  DHCPC_Pkt_GetTransId( DHCPC_TEMPCTRLBLK* pItemInfo )
{
    ULONG ulXid = 0;
    ULONG ulSCID = 0;

    /*获取本SC的id*/
    ulSCID = DHCPC_SELF_CMPIDX_INSG;

    if (NULL == pItemInfo)
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_158);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\nDHCPC_Pkt_GetTransId pItemInfo = NULL");
        return VOS_ERR;
    }

	/*39号软参第5个bit为1，XID直接使用TEIDC设置。*/
	/*39号软参第5个bit位为0，v1用户: DE板: token(13bit)+sc id(3bit)+Sequence（16bit）
                                     F板:token(14bit)+reserve(2bit)+Sequence（16bit）*/
    if(g_ucSoftParaDHCPKPN & ((UCHAR)0x10))
    {
        ulXid =  pItemInfo->ulDHCPCtlIdx;
    }
    else
    {
        if ( CRM_BOARD_TYPE_SPUF != g_ulDhcpcSpuType )
        {
            ulXid = (( ULONG )(pItemInfo->ulDHCPCtlIdx) & 0xFFF80000 )
                           | ((ulSCID << 16 ) & 0x70000)
                           | ((g_ulDHCPCTransId++) & 0xffff);
        }
        else
        {
            ulXid = (( ULONG )(pItemInfo->ulDHCPCtlIdx) & 0xFFFC0000 )
                           | ((g_ulDHCPCTransId++) & 0xffff);
        }

    }

    return ulXid;
}

/*****************************************************************************
 函 数 名  : DHCPR_RecordAllOption
 功能描述  : 记录DHCP OPTION的指针
 输入参数  : DHCPOPTION_S stDhcpOption
             DHCP_S *pstDhcp
             ULONG ulOptionLen
 输出参数  : 无
 返 回 值  : ULONG
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2002年11月23日
    作    者   : 马洪波
    修改内容   : 新生成函数

*****************************************************************************/
ULONG  DHCPR_RecordAllOption( DHCP_OPTION_S *pstDhcpOpt, DHCP_S *pstDhcp, ULONG ulOptionLen )
{
    ULONG  ulMagicCookie = NULL;
    UCHAR  *pucOpt = NULL;
    LONG   lDhcpOptionLen = NULL;
    UCHAR  *pucOptions = NULL;
    ULONG  i = 0;
    UCHAR  a_ucCount[DHCP_OPTION_COUNT] = {0};

    /*判断入参的合法性*/
    if ( ( pstDhcp == NULL )||( pstDhcpOpt == NULL ) )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_159);
        return VOS_ERR;
    }

    /*得到OPTION的头指针pucOption*/
    pucOptions     = ( UCHAR * )( pstDhcp+1 );
    lDhcpOptionLen = ( LONG )ulOptionLen;

    pucOpt = pucOptions;


    /*判断MAGICCODE是否为所需要的*/
    ulMagicCookie = *( ULONG * )pucOpt;
    if ( ulMagicCookie != ( ULONG )VOS_HTONL( DCHP_MAGICCOOKIE ) )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_160);
        return VOS_ERR;
    }

    /*为每个属性初始化计数*/
    for ( i = 0; i < DHCP_OPTION_COUNT; a_ucCount[i] = 0, i++ ) ;

    /*pucOption指针加4，长度减4*/
    pucOptions     += 4;
    lDhcpOptionLen -= 4;

    while ( *pucOptions!= DHCP_ENDOFOPTIONS/* *pucOption != 0xFF*/ )
    {
        /*定义变量记录option类型和option长度*/
        UCHAR ucOptionCode = VOS_NULL;
        UCHAR ucOptionLen = VOS_NULL;

        /*判断ulOptionLen大于2，2为最小的option长度*/

        /*取得option类型*/
        ucOptionCode    = *pucOptions++;

        if ( ucOptionCode == 0 )
        {
            ucOptionLen     = 0;
            lDhcpOptionLen --;
        }
        else
        {
            ucOptionLen     = *pucOptions++;
            lDhcpOptionLen -= 2;
        }

        /*取得option长度*/

        /*判断后面的变长字段的长度是否还足够,绝对保证不能
          读到当前DHCP报文的变长字段的长度域之外去*/
        if ( lDhcpOptionLen <= ( LONG )ucOptionLen )
        {
            /*当没有"DHCP message type"选项时，就是BOOTP报文    */
            if ( pstDhcpOpt->pucDHCPMsgType == NULL )
            {
                /*lint -e801*/
                goto optionnumchk;
                /*lint +e801*/
            }
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_161);

            return VOS_ERR;
        }

        switch ( ucOptionCode/*option类型*/ )
        {
                /*1.是"Subnet mask"选项，code = 0x01*/
            case DHCP_SUBNETMASK_CODE :
                if ( ucOptionLen != 4 )
                {
                    DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_162);
                    return VOS_ERR;
                }

                a_ucCount[0]++;
                pstDhcpOpt->pulSubnetMask = ( ULONG * )pucOptions;
                pstDhcpOpt->ucNetMaskLen = ucOptionLen;
                break;

                /*2.是"Router"选项，code = 0x03*/
            case DHCP_ROUTERIP_CODE :
                /*判断长度是否是4的倍数*/
                if ( ( ucOptionLen & 0x03 )!= NULL )
                {
                    DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_163);
                    return VOS_ERR;
                }

                a_ucCount[1]++;
                pstDhcpOpt->pulRouterIp   = ( ULONG * )pucOptions;
                pstDhcpOpt->ucRouterIpLen = ucOptionLen;
                break;

                /*3.是"DNS 服务器"选项，code = 0x06*/
            case DHCP_DNSIP_CODE :
                DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n-->DHCPR_RecordAllOption(),have DNS option" );
                /*判断长度是否是4的倍数*/
                if ( ( ucOptionLen & 0x03 )!= NULL )
                {
                    DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_164);
                    return VOS_ERR;
                }

                a_ucCount[2]++;
                pstDhcpOpt->pulDNSIp   = ( ULONG * )pucOptions;
                pstDhcpOpt->ucDNSIpLen = ucOptionLen;
                break;

                /*4.是"Host name"选项，code = 0x0b*/
            case DHCP_HOSTNAME_CODE :
                if ( ucOptionLen < 1 )
                {
                    DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_165);
                    return VOS_ERR;
                }

                a_ucCount[3]++;
                pstDhcpOpt->pucHostName   = pucOptions;
                pstDhcpOpt->ucHostNameLen = ucOptionLen;
                break;

                /*5.是"Domain name"选项，code = 0x0f*/
            case DHCP_DOMAINNAME_CODE :
                if ( ucOptionLen < 1 )
                {
                    DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_166);
                    return VOS_ERR;
                }

                a_ucCount[4]++;
                pstDhcpOpt->pucDomainName   = pucOptions;
                pstDhcpOpt->ucDomainNameLen = ucOptionLen;
                break;

                /*6.是"Netbios name server"选项，code = 0x2c*/
            case DHCP_NBNS_CODE :
                /*判断长度是否是4的倍数*/
                if ( ( ucOptionLen & 0x03 )!= NULL )
                {
                    DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_167);
                    return VOS_ERR;
                }

                a_ucCount[5]++;
                pstDhcpOpt->pulNBNSIp   = ( ULONG * )pucOptions;
                pstDhcpOpt->ucNBNSIpLen = ucOptionLen;
                break;

                /*7.是"Netbios data distribute server"选项，code = 0x2d*/
            case DHCP_NBDS_CODE :
                /*判断长度是否是4的倍数*/
                if ( ( ucOptionLen & 0x03 )!= NULL )
                {
                    DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_168);
                    return VOS_ERR;
                }

                a_ucCount[6]++;
                pstDhcpOpt->pulNBDSIp   = ( ULONG * )pucOptions;
                pstDhcpOpt->ucNBDSIpLen = ucOptionLen;
                break;

                /*8.是"Netbios node type"选项，code = 0x2e*/
            case DHCP_NBNT_CODE :
                if ( ucOptionLen != 1 )
                {
                    DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_169);
                    return VOS_ERR;
                }

                a_ucCount[7]++;
                pstDhcpOpt->pucNBNodeType   = pucOptions;
                break;

                /*9.是"Netbios scope"选项，code = 0x2f*/
            case DHCP_NBSCOPE_CODE :
                if ( ucOptionLen < 1 )
                {
                    DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_170);
                    return VOS_ERR;
                }

                a_ucCount[8]++;
                pstDhcpOpt->pucNBScope   = pucOptions;
                pstDhcpOpt->ucNBScopeLen = ucOptionLen;
                break;

                /*10.是"Requested Ip"选项，code = 0x32*/
            case DHCP_REQUESTEDIP_CODE :
                if ( ucOptionLen != 4 )
                {
                    DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_171);
                    return VOS_ERR;
                }

                a_ucCount[9]++;
                pstDhcpOpt->pulReqIp = ( ULONG * )pucOptions;
                break;

                /*11.是"Ip address lease time"选项，code=0x33*/
            case DHCP_IPLEASETIME_CODE:
                if ( ucOptionLen != 4 )
                {
                    DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_172);
                    return VOS_ERR;
                }

                a_ucCount[10]++;
                pstDhcpOpt->pulLeaseTime = ( ULONG * )pucOptions;/*以秒为单位的IP使用期限*/
                break;

                /*12.是"DHCP message type"选项，code=0x35*/
                /*当没有这个选项时,会在调用此函数的函数中进行出错处理*/
            case DHCP_MESSAGETYPE_CODE:
                /*"DHCP Message Type"选项的长度是否为1*/
                if ( ucOptionLen != 1 )
                {
                    DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_173);
                    return VOS_ERR;
                }

                a_ucCount[11]++;
                pstDhcpOpt->pucDHCPMsgType = pucOptions;
                break;

                /*13.是"Server Identifier"选项，code=0x36*/
            case DHCP_SERVERIP_CODE:
                if ( ucOptionLen != 4 )/*仔细考虑，需不需要进一步处理(ZQ0805)*/
                {
                    DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_174);
                    return VOS_ERR;
                }

                a_ucCount[12]++;
                pstDhcpOpt->pulDHCPServerIp = ( ULONG * )pucOptions;
                break;

                /*14.是"Requested parameter list"选项，code = 0x37*/
            case DHCP_REQPARAM_CODE :
                if ( ucOptionLen < 1 )
                {
                    DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_175);
                    return VOS_ERR;
                }

                a_ucCount[13]++;
                pstDhcpOpt->pucReqParamList   = pucOptions;
                pstDhcpOpt->ucReqParamListLen = ucOptionLen;
                break;

                /*15.是"Renew time"选项，code = 0x3a*/
            case DHCP_RENEWTIME_CODE :
                if ( ucOptionLen != 4 )
                {
                    DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_176);
                    return VOS_ERR;
                }

                a_ucCount[14]++;
                pstDhcpOpt->pulRenewTime = ( ULONG * )pucOptions;/*以秒为单位*/
                break;

                /*16.是"Rebind time"选项，code = 0x3b*/
            case DHCP_REBINDTIME_CODE :
                if ( ucOptionLen != 4 )
                {
                    DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_177);
                    return VOS_ERR;
                }

                a_ucCount[15]++;
                pstDhcpOpt->pulRebindTime = ( ULONG * )pucOptions;/*以秒为单位*/
                break;

                /*17.是"Client Id"选项，code = 0x3d*/
            case DHCP_CLIENTID_CODE :
                if ( ucOptionLen < 2 )
                {
                    DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_178);
                    return VOS_ERR;
                }

                a_ucCount[16]++;
                pstDhcpOpt->pucClientId   = pucOptions;
                pstDhcpOpt->ucClientIdLen = ucOptionLen;
                break;

                /*18.是"Vendor information"选项，code = 0x29*/
            case DHCP_VENDORINFO_CODE :
                if ( ucOptionLen < 1 )
                {
                    DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_179);
                    return VOS_ERR;
                }

                a_ucCount[17]++;
                pstDhcpOpt->pucVendorOption   = pucOptions;
                pstDhcpOpt->ucVendorOptinLen  = ucOptionLen;
                break;

            case DHCP_OPT82_CODE :
                if ( ucOptionLen < 2 )
                {
                    DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_180);
                    return VOS_ERR;
                }

                a_ucCount[18]++;
                pstDhcpOpt->pucOpt82   = pucOptions;
                pstDhcpOpt->ucOpt82Len  = ucOptionLen;
                break;

            case DHCP_OPTION60 :
                if ( ucOptionLen < 1 )
                {
                    DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_181);
                    return VOS_ERR;
                }

                a_ucCount[19]++;
                pstDhcpOpt->pucOption60= pucOptions;
                pstDhcpOpt->ucOpt60Len  = ucOptionLen;
                break;

                /*对其他的选项不做任何操作*/
            default:
                DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_182);
                break;
        }

        /*跳过ucOptionLen长度的字节，得到下一个code字节*/
        pucOptions     += ucOptionLen;
        if(lDhcpOptionLen < ucOptionLen )
        {
            break;
        }
        lDhcpOptionLen -= ( long )ucOptionLen;

    }
    DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n-->DHCPR_RecordAllOption(),a_ucCount[2]=%d",a_ucCount[2] );

    if ( *pucOptions == DHCP_ENDOFOPTIONS/*结尾属性为END OPTION*/ )
    {
        /*赋值*/
        pstDhcpOpt->pucEndOfOption = pucOptions;
    }
    else if ( pstDhcpOpt->pucDHCPMsgType == VOS_NULL_PTR/*消息类型为空为BOOTP报文*/ )
    {
        /*打印*/

    }
    else
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_183);
        /*打印错误直接返回*/
        return VOS_ERR;
    }

    /*goto语句*/
optionnumchk:
    /*根据属性计数，判断有属性出现过两次，如果出现两次，出错*/
    for ( i = 0; ( i < DHCP_OPTION_COUNT ) && ( a_ucCount[i] <= 1 ); i++ ) ;

    /* Deleted for DTS2014040204742 PS11.0 裁决合入 TR5 */
    /*
    if ( i < DHCP_OPTION_COUNT )
    {
        return VOS_ERR;
    }
    */

    /*返回成功*/
    return VOS_OK;

}

