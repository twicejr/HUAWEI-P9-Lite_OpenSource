/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : dhcpc_msg.c
  版 本 号   : 初稿
  作    者   : yuqingping(25027)
  生成日期   : 2002年11月21日
  最近修改   :
  功能描述   : dhcpc模块的消息处理
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
#include "dhcpv6c_pkt.h"
#include "dhcpv6c_fsm.h"

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID          PS_FILE_ID_DHCPC_MSG_C
/*lint +e767*/


extern VOS_UINT32 g_ulPtmHashGene;
#define M_PTM_HASH_GENE (g_ulPtmHashGene)

/*m00221573 全文件pclint 2012-10-19 start*/
extern ULONG DHCPM_GetDhcpSrvCfgByIndex(ULONG ulDhcpIndex, LAP_DHCP_CFG_S *pstDhcpServer);
/*m00221573 全文件pclint 2012-10-19 end*/

/*****************************************************************************
 函 数 名  : DHCPC_QueryContextByteidc
 功能描述  :
 输入参数  : ULONG ulTeidc
 输出参数  : 无
 返 回 值  : VOS_OK    找到了上下文
             VOS_ERR   未找到上下文
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年07月08日
    作    者   : jixiaoming
    修改内容   : 新生成函数

*****************************************************************************/
ULONG DHCPC_QueryContextByteidc(ULONG ulTeidc)
{
    ULONG ulRet = 0;
    ULONG ulContextsNum = 0;
    SDB_GSPU_CONTEXT_S *pstRelContexts[M_MNT_MAX_PDP_NUM] = {NULL};

    ulRet = (ULONG)SDB_GTPC_GetRelatedContextsByTeidc(ulTeidc, &ulContextsNum, (UCHAR **)pstRelContexts);
    if (SDB_SUCCESS == ulRet)
    {
        return VOS_OK;
    }

    return VOS_ERR;
}

/*****************************************************************************
 函 数 名  : DHCPC_GetCtlBlkHashKey
 功能描述  : 获取HashKey
 输入参数  : ULONG ulDHCPCtlIdx
 输出参数  : ulHashKey
 返 回 值  : ulHashKey
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年08月14日
    作    者   : w00140934
    修改内容   : 新生成函数

*****************************************************************************/
ULONG DHCPC_GetCtlBlkHashKey( ULONG ulDHCPCtlIdx )
{
    ULONG ulHashKey = 0;

    /* 根据控制块索引的后16位计算HASHKEY */
    ulHashKey = (ulDHCPCtlIdx & 0x0000ffff) % DHCPC_CTRLBLK_HASH_TABLE_SIZE;

    DHCPC_DebugPrint(PTM_LOG_DEBUG,
                "\r\n DHCPC_GetCtlBlkHashKey:ulHashKey = %d",ulHashKey );
    return ulHashKey;
}


/*****************************************************************************
 函 数 名  : DHCPC_CalcCtlBlkHashValue
 功能描述  : 计算HashValue
 输入参数  : ULONG ulDHCPCtlIdx, ULONG ulTEIDC, UCHAR ucUser, ULONG ulContextIdx
 输出参数  : 无
 返 回 值  : pstDhcpcCtlBlk 成功，NULL 失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年08月04日
    作    者   : w00140934
    修改内容   : 新生成函数

*****************************************************************************/
DHCPC_CTRLBLK * DHCPC_CalcCtlBlkHashValue( ULONG ulDHCPCtlIdx, ULONG ulTEIDC)
{
    ULONG ulHashKey = 0;
    DHCPC_CTRLBLK * pstDhcpcCtlBlk = NULL;

    /* 根据控制块索引计算HASHKEY */
    ulHashKey = DHCPC_GetCtlBlkHashKey( ulDHCPCtlIdx );
    pstDhcpcCtlBlk = g_pstDhcpcCtrlBlkRec[ulHashKey];

    /* 遍历所有HASHKEY相等的控制块 */
    while ( NULL != pstDhcpcCtlBlk )
    {
        /* V1用户如果TEIDC相等则找到相应控制块 */
        if ( pstDhcpcCtlBlk->ulTEIDC == ulTEIDC)
        {
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_237);
            DHCPC_DebugPrint(PTM_LOG_DEBUG,
                                "\r\n DHCPC_CalcCtlBlkHashValue:ulTEIDC = %d",pstDhcpcCtlBlk->ulTEIDC );
            return pstDhcpcCtlBlk;
        }

        pstDhcpcCtlBlk = pstDhcpcCtlBlk->pstNextNode;
        if (NULL == pstDhcpcCtlBlk)
        {
            break;
        }

    }

    DHCPC_DebugPrint(PTM_LOG_DEBUG,
                "\r\n DHCPC_CalcCtlBlkHashValue: there is no DHCP CtlBlk! " );
    return NULL;
}

/*****************************************************************************
 函 数 名  : DHCPC_LookupCtlBlkNodeIntoHashTable
 功能描述  : 查找控制块节点
 输入参数  : DHCP_S  *pstDHCPPkt
 输出参数  : 无
 返 回 值  : pstDhcpcCtlBlk 成功，NULL 失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年08月05日
    作    者   : w00140934
    修改内容   : 新生成函数

*****************************************************************************/
DHCPC_CTRLBLK * DHCPC_LookupCtlBlkNodeIntoHashTable( DHCP_S  *pstDHCPPkt)
{
    ULONG ulHashKey = 0;
    ULONG ulIndex = 0;
    DHCPC_CTRLBLK *pstDhcpcCtlBlk = NULL;

    /* 入参检查 */
    if ( NULL == pstDHCPPkt)
    {
        DHCPC_DebugPrint(PTM_LOG_DEBUG,
                "\r\n DHCPC_LookupCtlBlkNodeIntoHashTable:pstDHCPPkt is null!" );
        return NULL;
    }

    /* 根据39号软参的第5位获取控制块索引 */
    if(g_ucSoftParaDHCPKPN & ((UCHAR)0x10))
    {
        ulIndex = VOS_HTONL(pstDHCPPkt->ulXid);
    }
    else
    {
        VOS_MemCpy( ( CHAR* )&ulIndex,( CHAR* )&( pstDHCPPkt->szChaddr[2] ),4 );
        ulIndex = VOS_HTONL(ulIndex);
    }

    /* 根据控制块索引的后16位计算HASHKEY */
    ulHashKey = (ulIndex & 0x0000ffff) % DHCPC_CTRLBLK_HASH_TABLE_SIZE;

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n ulXid = 0X%x, ulHashKey = %d",
                     pstDHCPPkt->ulXid, ulHashKey);

    pstDhcpcCtlBlk = g_pstDhcpcCtrlBlkRec[ulHashKey];

    /* 遍历HASHKEY相等的控制块，根据用户类型得到相应控制块 */
    while ( NULL != pstDhcpcCtlBlk )
    {
        if ( pstDhcpcCtlBlk->ulDHCPCtxIdx == ulIndex)
        {
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_238);
            return pstDhcpcCtlBlk;
        }

        pstDhcpcCtlBlk = pstDhcpcCtlBlk->pstNextNode;
    }

    /*没有找到相应控制块*/
    DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_241);
    DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n there is no pstDhcpcCtlBlk!" );
    return NULL;
}

/*****************************************************************************
 函 数 名  : DHCPC_InsertCtlBlkNodeIntoHashTable
 功能描述  : 插入控制块节点
 输入参数  : LAP2_DHCPC_MSG_S *pstReqMsg，ULONG ulIndex(控制块索引)
 输出参数  : 无
 返 回 值  : VOS_OK 成功，VOS_ERR 失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年08月04日
    作    者   : w00140934
    修改内容   : 新生成函数

*****************************************************************************/
ULONG DHCPC_InsertCtlBlkNodeIntoHashTable( LAP2_DHCPC_MSG_S *pstReqMsg, ULONG ulIndex)
{
    ULONG ulHashKey = 0;
    ULONG ulRetCode = 0;
    DHCPC_CTRLBLK* pstDhcpcCtlBlk = NULL; /*DHCP 控制块指针*/

    if ( NULL == pstReqMsg )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_235);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPC_InsertCtlBlkNodeIntoHashTableget: pstReqMsg is null!");
        return VOS_ERR;
    }

    /*根据控制块索引计算HASHKEY*/
    ulHashKey = DHCPC_GetCtlBlkHashKey( ulIndex );

    /*计算HashKey判断DHCP控制块是否已经存在*/
    pstDhcpcCtlBlk = DHCPC_CalcCtlBlkHashValue(ulIndex, pstReqMsg->ulTeidc);
    if (NULL != pstDhcpcCtlBlk)
    {
        /*DHCP控制块已经存在*/
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_236);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPC_InsertCtlBlkNodeIntoHashTableget: pstDhcpcCtlBlk is already exist!");
        return DHCP_CTRLBLK_EXIST;
    }

    /*初始化新结点*/
    ulRetCode = (ULONG)DHCPC_GetDhcpCtrlBlk(&pstDhcpcCtlBlk);
    if ( VOS_OK != ulRetCode )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_070);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPC_InsertCtlBlkNodeIntoHashTableget null DhcpCtrlBlk!");
        return VOS_ERR;
    }

    pstDhcpcCtlBlk->usApnIndex = pstReqMsg->usApnIndex;
    pstDhcpcCtlBlk->ulPDPIndex = pstReqMsg->ulIndex;
    pstDhcpcCtlBlk->ucUser= pstReqMsg->ucGtpVer;
    pstDhcpcCtlBlk->ulTEIDC= pstReqMsg->ulTeidc;
    pstDhcpcCtlBlk->ulDHCPCtxIdx= ulIndex;
    pstDhcpcCtlBlk->ucLAPNo = pstReqMsg->ucLAPNo;

    /*将新结点插入到第一个位置*/
    pstDhcpcCtlBlk->pstNextNode = g_pstDhcpcCtrlBlkRec[ulHashKey];
    g_pstDhcpcCtrlBlkRec[ulHashKey] = pstDhcpcCtlBlk;

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPC_InsertCtlBlkNodeIntoHashTableget success!");
    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : DHCPC_ProcIpv4Apply
 功能描述  : 处理地址申请，续租的消息
 输入参数  : LAP2_DHCPC_MSG_S* pstReqMsg
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2002年11月21日
    作    者   : yuqingping(25027)
    修改内容   : 新生成函数
  2.日    期   : 2010年08月07日
    作    者   : w00140934
    修改内容   : 修改DHCP控制块结构

*****************************************************************************/
VOID DHCPC_ProcIpv4Apply(LAP2_DHCPC_MSG_S* pstReqMsg)
{
    /*变量定义*/
    ULONG                   ulRet = 0;       /*函数调用返回值*/
    ULONG                   ulIpLease = 0;
    ULONG                   ulRetTimeInSec = 0;
    DHCPC_CTRLBLK_NODE*     pstDhcpCtrlNode = NULL;
    DHCPC_TEMPCTRLBLK*      pstTempItem = NULL;
    SDB_GSPU_CONTEXT_S *pstContext = VOS_NULL_PTR;
    ULONG ulDhcpGroupIndex = 0;
    LAP_DHCP_CFG_S stDhcpServer = {0};

    /* 得到DHCP临时控制块节点 */
    pstDhcpCtrlNode = (DHCPC_CTRLBLK_NODE *)DHCPC_GetDhcpTmpNode();
    if ( NULL == pstDhcpCtrlNode )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_068);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPC_MsgProc_Apply get null DhcpTmpNode!");
        (VOID)DHCPC_SendMsgToLAP2_WithOriginalMsg(pstReqMsg, DHCPC_SND2_LAP2_ADDR_FAILED_MSG);
        return;
    }
    pstTempItem = &(pstDhcpCtrlNode->stDhcpcTmpCtlBlk);

    DHCPC_INIT_ITEM(pstTempItem );

    DHCPC_MSG2ITEM(pstReqMsg, pstTempItem);

    /* 根据用户类型填充当前DHCP控制块索引 */
    pstTempItem->ulDHCPCtlIdx = pstReqMsg->ulTeidc;
    pstTempItem->ulAgetIP = pstReqMsg->aulAgentIP[0];
    pstTempItem->usPoolIndex = pstReqMsg->usPoolIndex;
    pstTempItem->aulMSISDN[0] = pstReqMsg->aulMSISDN[0];
    pstTempItem->aulMSISDN[1] = pstReqMsg->aulMSISDN[1];
    pstTempItem->ucUserType = pstReqMsg->ucUserType;
    pstTempItem->usVpnId = pstReqMsg->usVpnId;
    pstTempItem->ulPdpIndex = pstReqMsg->ulIndex;
    pstTempItem->ucUser = pstReqMsg->ucGtpVer;
    pstTempItem->ulTEIDC = pstReqMsg->ulTeidc;
    pstTempItem->ucLAPNo = pstReqMsg->ucLAPNo;

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPC_MsgProc_Apply:ucUser = 0X%x, ulTEIDC = 0X%x, ulIndex = 0X%x, ucLAPNo = %d",
                          pstReqMsg->ucGtpVer, pstReqMsg->ulTeidc, pstReqMsg->ulIndex, pstReqMsg->ucLAPNo);

#if 0
    /*根据PDP INDEX, 获取上下文*/
    ulRet = (ULONG)SDB_GetContextByIndex(pstReqMsg->ulIndex, (UCHAR**)&pstContext );
    if ( ( ulRet != VOS_OK ) || ( NULL == pstContext ) )
    {
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPC_MsgProc_Apply : SDB_GetContextByIndex return ERR.!" );

        /* BEGIN: Added for PN:DTS2011120700783 by guolixian 00171003, 2012/1/6 pstDhcpCtrlNode没有释放，资源泄漏*/
        (VOID)DHCPC_SendMsgToLAP2_WithOriginalMsg(pstReqMsg, DHCPC_SND2_LAP2_ADDR_FAILED_MSG);
        DHCPC_FreeDhcpTmpNode(pstDhcpCtrlNode);
        return;
    }

    VOS_MemCpy(pstTempItem->aulIMSI,&(pstContext->stImsi),sizeof(ULONG)*2);
    VOS_MemCpy(pstTempItem->aulMSISDN,pstContext->szMsisdn,sizeof(ULONG)*2);
    VOS_MemCpy(pstTempItem->aulIMEI,&(pstContext->stIMEI),sizeof(ULONG)*2); /* Added by jixiaoming for  IMEI跟踪 at 2012-8-17 */
    pstTempItem->ucRole = pstContext->ucUgwRole;
    pstTempItem->ucRandomNo = pstContext->ucRandomNo;
#endif

    /* 根据用户类型创建DHCP控制块的HASH表*/
    ulRet = DHCPC_InsertCtlBlkNodeIntoHashTable(pstReqMsg, pstTempItem->ulDHCPCtlIdx);
    if ( ulRet != VOS_OK )
    {
        if(DHCP_CTRLBLK_EXIST == ulRet)
        {
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_069);
            /* 通知LAP退网---ADDR_REL消息码*/
            (VOID)DHCPC_SendMsgToLAP2(pstDhcpCtrlNode, DHCPC_SND2_LAP2_ADDR_REL_MSG);

            /* 通知DHCPServer释放IP*/
            (VOID)DHCPC_Pkt_Send(DHCP_RELEASE, pstTempItem);
        }

        (VOID)DHCPC_SendMsgToLAP2_WithOriginalMsg(pstReqMsg, DHCPC_SND2_LAP2_ADDR_FAILED_MSG);

        /*删除临时控制块节点，释放内存*/
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_242);
        DHCPC_FreeDhcpTmpNode(pstDhcpCtrlNode);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPC_MsgProc_Apply : DHCPC_InsertCtlBlkNodeIntoHashTable return ERR.!" );
        return;
    }

    /* 创建DHCP控制块结构并记录到相应的全局数组中，当前版本的SDB已经不再保存控制
    块结构，所以现在动态申请控制块结构空间，并将控制块结构指针放入全局数组中保存
    。该数组以PDP上下文索引，相当于原来的SDB*/

    ulDhcpGroupIndex = pstTempItem->usDhcpGroupIndex;
    ulRet = DHCPM_GetDhcpSrvCfgByIndex(ulDhcpGroupIndex, &stDhcpServer);
    if ( VOS_OK != ulRet )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_080);
        VOS_DBGASSERT(0);
        (VOID)DHCPC_SendMsgToLAP2_WithOriginalMsg(pstReqMsg, DHCPC_SND2_LAP2_ADDR_FAILED_MSG);
        DHCPC_FreeDhcpCtrlBlk(pstTempItem->ulDHCPCtlIdx, pstTempItem->ulTEIDC, pstTempItem->ucUser, pstTempItem->ulPdpIndex );
        DHCPC_FreeDhcpTmpNode(pstDhcpCtrlNode);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "DHCPM_GetDhcpSrvCfgByIndex fail, ulDhcpGroupIndex=%u", ulDhcpGroupIndex);
        return;
    }

    ulIpLease = stDhcpServer.ucLeaseTime* 3600 ;/* 将小时转换成秒 */

    if(0 != ulIpLease)
    {
        pstTempItem->usLease = ulIpLease;
    }

    /*----------------------------------------------------
    *              报文发送
    ----------------------------------------------------*/

    /*切换状态，启动定时器*/
    DHCPC_ITEM_SETSATE(pstTempItem, DHCPC_STATE_DISCOVER);

    /*发送discovery报文*/
    ulRet = DHCPC_Pkt_Send(DHCP_DISCOVER , pstTempItem);
    if(VOS_OK != ulRet)
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_081);
        (VOID)DHCPC_SendMsgToLAP2_WithOriginalMsg(pstReqMsg, DHCPC_SND2_LAP2_ADDR_FAILED_MSG);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\nDHCPC_MsgProc_Apply send DHCP_DISCOVER packet failed!");

        /*不插入重发定时器链表，删除节点，释放内存*/

        /* 释放控制块 */
        DHCPC_FreeDhcpCtrlBlk(pstTempItem->ulDHCPCtlIdx, pstTempItem->ulTEIDC, pstTempItem->ucUser, pstTempItem->ulPdpIndex );
        DHCPC_FreeDhcpTmpNode(pstDhcpCtrlNode);
        return;
    }

    /*记录发送Discovery的时间*/

    /*取秒计数*/
    (VOID)PGP_TmNowInSec( &ulRetTimeInSec);
    pstTempItem->ulTimeStamp = ulRetTimeInSec;

    /*置重发标志插入到重发定时器链表,以便在适当时机重发该报文*/
    DHCPC_InSertNodeAfterSecs(DHCPC_4_SECONDS, pstDhcpCtrlNode);

    /*临时控制块指针保存到DHCP控制块的ulTmpVar字段操作失败不作处理*/
    if (VOS_OK != DHCPC_SaveTmpDhcpCtrlBlkPtr(pstTempItem->ulDHCPCtlIdx, pstTempItem->ulTEIDC, pstTempItem->ucUser, pstTempItem->ulPdpIndex, (VOID *)pstDhcpCtrlNode) )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_082);
        (VOID)DHCPC_SendMsgToLAP2_WithOriginalMsg(pstReqMsg, DHCPC_SND2_LAP2_ADDR_FAILED_MSG);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPC_MsgProc_Apply save TmpCtrlBlk pointer failed!");
        /* 释放控制块 */
        DHCPC_FreeDhcpCtrlBlk(pstTempItem->ulDHCPCtlIdx, pstTempItem->ulTEIDC, pstTempItem->ucUser, pstTempItem->ulPdpIndex );
        DHCPC_DelNode(DHCPC_INVALID_INDEX, pstDhcpCtrlNode);
        DHCPC_FreeDhcpTmpNode(pstDhcpCtrlNode);
    }

}

/*****************************************************************************
 函 数 名  : DHCPC_InitDhcpContextByLapMsg
 功能描述  : 根据LAP的消息填充dhcpc控制块
 输入参数  : DHCPC_CTRLBLK *pstDhcpcContext
             LAP2_DHCPC_MSG_S* pstReqMsg
 输出参数  : 无
 返 回 值  : ULONG
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年7月10日
    作    者   : jixiaoming 00180244
    修改内容   : 新生成函数

*****************************************************************************/
ULONG DHCPC_InitDhcpContextByLapMsg(DHCPC_CTRLBLK *pstDhcpcContext, LAP2_DHCPC_MSG_S* pstReqMsg)
{
    ULONG ulReturn = VOS_ERR;
    SDB_GSPU_CONTEXT_S *pstContext = VOS_NULL_PTR;

    DHCPC_FUNC_ENTRY();

    pstDhcpcContext->aulMSISDN[0] = pstReqMsg->aulMSISDN[0];
    pstDhcpcContext->aulMSISDN[1] = pstReqMsg->aulMSISDN[1];
    VOS_MemCpy(pstDhcpcContext->aulAgentIpAddr, pstReqMsg->aulAgentIP, sizeof(ULONG) * LAP_IP_ULONG_NUM);
    pstDhcpcContext->usVPNIndex = pstReqMsg->usVpnId;
    pstDhcpcContext->usServerGrpIndex = pstReqMsg->usDhcpGroupIndex;
    pstDhcpcContext->ucUserType = pstReqMsg->ucUserType;
    pstDhcpcContext->usPoolIndex = pstReqMsg->usPoolIndex;
    pstDhcpcContext->usApnIndex = pstReqMsg->usApnIndex;
    pstDhcpcContext->ucLAPNo = pstReqMsg->ucLAPNo;
    pstDhcpcContext->ucIpType = pstReqMsg->ucAddressType;
    pstDhcpcContext->ucUser = pstReqMsg->ucGtpVer;
    //pstDhcpcContext->ulTEIDC = pstReqMsg->ulTeidc;
    pstDhcpcContext->ulPDPIndex = pstReqMsg->ulIndex;
    pstDhcpcContext->ucAgingFlag = 0;
    pstDhcpcContext->ucLeaseStatus = DHCPV6C_LEASE_STATE_BUTT;
    DHCPV6C_SET_V6ADDR_NULL(pstDhcpcContext->aulMainDnsAddr);
    DHCPV6C_SET_V6ADDR_NULL(pstDhcpcContext->aulSecdDnsAddr);
    DHCPC_CLR_ALL_RESOURCE(pstDhcpcContext->ucResource);
    pstDhcpcContext->ucRabId   = pstReqMsg->ucRabId;
    pstDhcpcContext->enModemId = pstReqMsg->enModemId;

    ulReturn = DHCPM_GetRetransmitTimeOutByIndex(pstReqMsg->usDhcpGroupIndex, &(pstDhcpcContext->ucResendTimeout));
    if (VOS_OK != ulReturn)
    {
        DHCPC_DebugPrint(PTM_LOG_ERR, "call DHCPM_GetRetransmitTimeOutByIndex failed! return=%u", ulReturn);
        return VOS_ERR;
    }

#if 0
    ulReturn = (ULONG)SDB_GetContextByIndex(pstReqMsg->ulIndex, (UCHAR**)&pstContext);
    if (VOS_OK != ulReturn)
    {
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_FIND_SDB_FAIL);
        DHCPC_DebugPrint(PTM_LOG_INFO, "call SDB_GetContextByIndex failed! return=%u", ulReturn);
        return VOS_ERR;
    }
    pstDhcpcContext->ucRandomNo = pstContext->ucRandomNo;
    pstDhcpcContext->ucRole = pstContext->ucUgwRole;
    VOS_MemCpy(pstDhcpcContext->aulIMSI, &(pstContext->stImsi),sizeof(ULONG) * 2);
    VOS_MemCpy(pstDhcpcContext->aulIMEI, &(pstContext->stIMEI),sizeof(ULONG) * 2);
#endif

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "MSISDN : 0x%x %x", pstDhcpcContext->aulMSISDN[0], pstDhcpcContext->aulMSISDN[1]);
    DHCPC_DebugPrint(PTM_LOG_DEBUG, "IMSI   : 0x%x %x", pstDhcpcContext->aulIMSI[0], pstDhcpcContext->aulIMSI[1]);
    DHCPC_DebugPrint(PTM_LOG_DEBUG, "IMEI   : 0x%x %x", pstDhcpcContext->aulIMEI[0], pstDhcpcContext->aulIMEI[1]);

    DHCPC_FUNC_EXIT(VOS_OK);
    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : DHCPC_ProcIpv6Apply
 功能描述  : 处理LAP的Ipv6地址请求消息
 输入参数  : LAP2_DHCPC_MSG_S* pstReqMsg
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年7月10日
    作    者   : jixiaoming 00180244
    修改内容   : 新生成函数

*****************************************************************************/
ULONG DHCPC_ProcIpv6Apply(LAP2_DHCPC_MSG_S* pstReqMsg)
{
    ULONG ulReturn = VOS_ERR;
    DHCPC_CTRLBLK *pstDhcpcContext = NULL;
    DHCPV6C_PRE_RESULT_S stPreResult = {0};

    DHCPC_FUNC_ENTRY();

    DHCPV6C_DBGCNT_ADD(E_DHCPV6C_REV_LAP_REQ_MSG);

    ulReturn = DHCPC_QueryDhcpcContext(pstReqMsg->ucAddressType, pstReqMsg->ulTeidc, &pstDhcpcContext);
    if (VOS_OK != ulReturn)
    {
        ulReturn = DHCPC_MallocDhcpcContext(LAP_IPV6, pstReqMsg->ulTeidc, &pstDhcpcContext);
        if (VOS_OK != ulReturn)
        {
            DHCPV6C_DBGCNT_ADD(E_DHCPV6C_CREAT_CONTEXT_FAIL);
            return VOS_ERR;
        }
        pstDhcpcContext->usDhcpStatus = DHCPV6C_STATE_INITIAL;
        ulReturn = DHCPC_InitDhcpContextByLapMsg(pstDhcpcContext, pstReqMsg);
        if (VOS_OK != ulReturn)
        {
            DHCPV6C_DBGCNT_ADD(E_DHCPV6C_INIT_CONTEXT_FAIL);

            ulReturn = DHCPC_FreeDhcpcContext(LAP_IPV6, pstDhcpcContext->ulTEIDC);
            if (ulReturn != VOS_OK)
            {
                DHCPV6C_DBGCNT_ADD(E_DHCPV6C_CNT_ERR_2);
            }

            return VOS_ERR;
        }

    }
    else
    {
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_CONTEXT_EXIST_FAIL);

        /* 释放该地址 */
        stPreResult.pstDhcpcContext = pstDhcpcContext;
        stPreResult.enEvent = DHCPV6C_EV_IP_RELEASE;
        stPreResult.pMsg = NULL;

        DHCPV6C_RunFsm(&stPreResult);
        return VOS_ERR;
    }

    stPreResult.pstDhcpcContext = pstDhcpcContext;
    stPreResult.enEvent = DHCPV6C_EV_IP_REQUEST;
    stPreResult.pMsg = NULL;

    /* 运行状态机 */
    DHCPV6C_RunFsm(&stPreResult);

    DHCPC_FUNC_EXIT(VOS_OK);
    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : DHCPC_MsgProc_Apply
 功能描述  : 处理地址申请，续租的消息
 输入参数  : LAP2_DHCPC_MSG_S* pstReqMsg
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2002年11月21日
    作    者   : yuqingping(25027)
    修改内容   : 新生成函数
  2.日    期   : 2010年08月07日
    作    者   : w00140934
    修改内容   : 修改DHCP控制块结构

*****************************************************************************/
VOID DHCPC_MsgProc_Apply(LAP2_DHCPC_MSG_S* pstReqMsg )
{
    ULONG   ulReturn = VOS_ERR;

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n-->DHCPC_MsgProc_Apply()");

    if (NULL == pstReqMsg)
    {
        VOS_Assert(0);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPC_MsgProc_Apply get null pstReqMsg!");
        return;
    }

    if (M_AM_USM_ADDRTYPE_IPV4 == pstReqMsg->ucAddressType)
    {
        DHCPC_ProcIpv4Apply(pstReqMsg);
    }
    else
    {
        ulReturn = DHCPC_ProcIpv6Apply(pstReqMsg);
        if (VOS_OK != ulReturn)
        {
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_067);
            (VOID)DHCPC_SendMsgToLAP2_WithOriginalMsg(pstReqMsg, DHCPC_SND2_LAP2_ADDR_FAILED_MSG);
        }
    }

    return ;
}


/*****************************************************************************
 函 数 名  : DHCPC_MsgProc_Req
 功能描述  : 处理地址申请，续租的消息
 输入参数  : UCHAR ucMsgType
             DHCPC_AMREQMSG_S   *pstReqMsg
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2002年11月21日
    作    者   : yuqingping(25027)
    修改内容   : 新生成函数
  2.日    期   : 2010年08月07日
    作    者   : w00140934
    修改内容   : 修改DHCP控制块结构

*****************************************************************************/
VOID DHCPC_MsgProc_Lease( LAP2_DHCPC_MSG_S *pstReqMsg, ULONG ulDHCPCtlIdx )
{
    /*变量定义*/
    ULONG                ulRet = 0;       /*函数调用返回值*/
    ULONG                ulIndex = 0;
    ULONG                ulRetTimeInSec = 0;
    DHCPC_CTRLBLK        *pstDhcpCtrlBlk = NULL;
    DHCPC_TEMPCTRLBLK    *pstHashItem = NULL;

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n-->DHCPC_MsgProc_Lease()" );
    if( NULL == pstReqMsg)
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_083);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\nDHCPC_MsgProc_Lease() pstReqMsg =null!" );
        return;
    }
    ulIndex        =  pstReqMsg->ulIndex;

    /*获取DHCP控制块*/
    pstDhcpCtrlBlk = DHCPC_CalcCtlBlkHashValue(ulDHCPCtlIdx, pstReqMsg->ulTeidc);
    if ( NULL == pstDhcpCtrlBlk )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_084);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\nDHCPC_MsgProc_Release there is no DHCPCTRLBLK REC!" );
        return;
    }

    if ( DHCPC_STATE_INITIAL == pstDhcpCtrlBlk->usDhcpStatus )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_085);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPC_MsgProc_Lease get null SdbDhcpCtrlBlk!" );
        return;
    }

    /* BEGIN: Added for DHCP 控制块残留 DTS2011051702815 by z00175135, 2011/5/23 */
    /*发送续租消息如果找不到对应的上下文，就释放控制块，给server发送release 消息释放地址*/
    if (VOS_OK != DHCPC_QueryContextByteidc(pstReqMsg->ulTeidc))
    {
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPC_MsgProc_Lease: get null PDPContext!!IMSI=0x%x, 0x%x, PDPIndex = %u, IP=0x%x, agent-ip=0x%x",
                 pstDhcpCtrlBlk->aulIMSI[0], pstDhcpCtrlBlk->aulIMSI[1], ulIndex, pstDhcpCtrlBlk->aulUserIpAddr[0], pstDhcpCtrlBlk->aulAgentIpAddr[0]);

        /* 释放资源 */
        (VOID)DHCPC_ReleaseDhcpCtrlBlock(pstDhcpCtrlBlk);
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_800);
        return;
    }
    /* END:   Added for DHCP 控制块残留 DTS2011051702815  by z00175135, 2011/5/23 */

    pstHashItem = ( DHCPC_TEMPCTRLBLK * )DHCP_Malloc( DHCPC_HANDLE, sizeof( DHCPC_TEMPCTRLBLK ) );
    if ( NULL == pstHashItem )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_086);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPC_MsgProc_Lease alloc null memory!" );
        return;
    }
    /*lint -save -e530*/
    DHCPC_INIT_ITEM( pstHashItem );
    pstHashItem->ulPdpIndex     = ulIndex;
    //pstHashItem->ulUserIpAddr     = ulUserIpAddr; delete by z00113478,ulUserIpAddr没有赋值
    pstHashItem->ulSrvIp = pstDhcpCtrlBlk->aulSrvIp[0];

    /*add by z00113478 由于Lease消息中需要DHCPGroupIndex,AgentIP,ulUserIpAddr,Client Identifier*/
    pstHashItem->ulDHCPCtlIdx = pstDhcpCtrlBlk->ulDHCPCtxIdx;
    pstHashItem->ulAgetIP = pstDhcpCtrlBlk->aulAgentIpAddr[0];
    pstHashItem->ulUserIpAddr = pstDhcpCtrlBlk->aulUserIpAddr[0];
    pstHashItem->aulMSISDN[0] = pstDhcpCtrlBlk->aulMSISDN[0];
    pstHashItem->aulMSISDN[1] = pstDhcpCtrlBlk->aulMSISDN[1];
    pstHashItem->usDhcpGroupIndex = pstDhcpCtrlBlk->usServerGrpIndex;
    pstHashItem->ucSCID = (UCHAR)DHCPC_SELF_CMPIDX_INSG;


    pstHashItem->aulIMSI[0] = pstDhcpCtrlBlk->aulIMSI[0];
    pstHashItem->aulIMSI[1] = pstDhcpCtrlBlk->aulIMSI[1];
    /* BEGIN: Added by jixiaoming for  IMEI跟踪 at 2012-8-17 */
    pstHashItem->aulIMEI[0] = pstDhcpCtrlBlk->aulIMEI[0];
    pstHashItem->aulIMEI[1] = pstDhcpCtrlBlk->aulIMEI[1];
    /* END: Added by jixiaoming for IMEI跟踪 at 2012-8-17 */
    pstHashItem->usVpnId= pstDhcpCtrlBlk->usVPNIndex;
    pstHashItem->usPoolIndex = pstDhcpCtrlBlk->usPoolIndex;
    pstHashItem->ucUserType = pstDhcpCtrlBlk->ucUserType;
    pstHashItem->usDhcpStatus = pstDhcpCtrlBlk->usDhcpStatus;
    pstHashItem->ulTimeStamp = pstDhcpCtrlBlk->ulTimeStamp;
    pstHashItem->usLease = pstDhcpCtrlBlk->ulLease;/*MAY*/
    pstHashItem->ucRole = pstDhcpCtrlBlk->ucRole;
    pstHashItem->ucUser= pstDhcpCtrlBlk->ucUser;
    pstHashItem->ulTEIDC = pstDhcpCtrlBlk->ulTEIDC;
    pstHashItem->ucLAPNo = pstDhcpCtrlBlk->ucLAPNo;
    pstHashItem->ucRandomNo = pstDhcpCtrlBlk->ucRandomNo;

    /*改变状态*/
    DHCPC_ITEM_SETSATE( pstHashItem , DHCPC_STATE_LEASE );

    /*发送request报文*/
    ulRet = DHCPC_Pkt_Send( DHCP_REQUEST, pstHashItem );
    if ( VOS_OK != ulRet )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_087);
        /*删控制块*/
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\nDHCPC_MsgProc_Lease send DHCP_REQUEST packet failed!" );
        DHCP_Free( DHCPC_HANDLE, pstHashItem );
        return;
    }
    /*记录发送REQ的时间*/
    /*问题:时间点保存不合理，如果服务器没有响应
      *下一次发送续约申请的时间将被改
      */
    /*取秒计数 modified by z00113478 at 20080703*/
    //ulRetTimeInSec = BSP_getTimeByTicksInMisc();
    ( VOID )PGP_TmNowInSec( &ulRetTimeInSec );
    /*取秒计数 modified by z00113478 at 20080703*/
    pstDhcpCtrlBlk->ulTmpVar = ulRetTimeInSec;
    pstDhcpCtrlBlk->aulSrvIp[0] = pstHashItem->ulSrvIp;

    /* 启动续租消息超时定时器 */
    (VOID)DHCPC_StartTimer(pstDhcpCtrlBlk->ucIpType, pstDhcpCtrlBlk->ulTEIDC, 0,
                                DHCPC_4_SECONDS, DHCPC_TimerCallBack);

    DHCP_Free( DHCPC_HANDLE, pstHashItem );

    return ;
}

/*****************************************************************************
 函 数 名  : DHCPC_ProcIpv4Release
 功能描述  : 处理LAP发送的IPV4地址释放消息
 输入参数  : LAP2_DHCPC_MSG_S* pstReqMsg
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年7月10日
    作    者   : jixiaoming 00180244
    修改内容   : 新生成函数

*****************************************************************************/
VOID DHCPC_ProcIpv4Release(LAP2_DHCPC_MSG_S* pstReqMsg)
{
    DHCPC_TEMPCTRLBLK*    pstTempItem = NULL;
    DHCPC_CTRLBLK*           pstDhcpcCtlBlk = NULL;


    /*获取DHCP控制块*/
    pstDhcpcCtlBlk = DHCPC_CalcCtlBlkHashValue( pstReqMsg->ulTeidc, pstReqMsg->ulTeidc);
    if ( NULL == pstDhcpcCtlBlk )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_089);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPC_ProcIpv4Release there is no DHCPCTRLBLK REC!" );
        return;
    }

    /*初始化stTempItem */
    pstTempItem = ( DHCPC_TEMPCTRLBLK * )DHCP_Malloc( DHCPC_HANDLE, sizeof( DHCPC_TEMPCTRLBLK ) );
    if ( NULL == pstTempItem )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_090);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPC_ProcIpv4Release alloc null memory!" );
        VOS_Assert( 0 );
        return;
    }

    PGP_MemZero( pstTempItem, sizeof( DHCPC_TEMPCTRLBLK ) );

    DHCPC_INIT_ITEM( pstTempItem );
    /*把pReqMsg中内容填充到stTempItem 中*/
    DHCPC_RELEASEMSG2ITEM( pstReqMsg, pstTempItem );

    pstTempItem->ulSrvIp = pstDhcpcCtlBlk->aulSrvIp[0];
    pstTempItem->ulDHCPCtlIdx = pstDhcpcCtlBlk->ulDHCPCtxIdx;
    pstTempItem->ulPdpIndex= pstDhcpcCtlBlk->ulPDPIndex;
    pstTempItem->ulAgetIP = pstDhcpcCtlBlk->aulAgentIpAddr[0];
    pstTempItem->aulMSISDN[0] = pstDhcpcCtlBlk->aulMSISDN[0];
    pstTempItem->aulMSISDN[1] = pstDhcpcCtlBlk->aulMSISDN[1];
    pstTempItem->aulIMSI[0]= pstDhcpcCtlBlk->aulIMSI[0];
    pstTempItem->aulIMSI[1]= pstDhcpcCtlBlk->aulIMSI[1];
    /* BEGIN: Added by jixiaoming for  IMEI跟踪 at 2012-8-17 */
    pstTempItem->aulIMEI[0]= pstDhcpcCtlBlk->aulIMEI[0];
    pstTempItem->aulIMEI[1]= pstDhcpcCtlBlk->aulIMEI[1];
    /* END: Added by jixiaoming for IMEI跟踪 at 2012-8-17 */
    pstTempItem->ucUser= pstDhcpcCtlBlk->ucUser;
    pstTempItem->ulTEIDC = pstDhcpcCtlBlk->ulTEIDC;
    pstTempItem->ucRole = pstDhcpcCtlBlk->ucRole;
    pstTempItem->ucLAPNo = pstDhcpcCtlBlk->ucLAPNo;
    pstTempItem->ucRandomNo = pstDhcpcCtlBlk->ucRandomNo;

    DHCPC_DebugPrint(PTM_LOG_DEBUG,
                "\r\n DHCPC_ProcIpv4Release:pstTempItem->ucUser = %d, pstTempItem->ulTEIDC = 0X%x",
                 pstTempItem->ucUser, pstTempItem->ulTEIDC);

    /*发送消息*/
    ( VOID )DHCPC_Pkt_Send( DHCP_RELEASE, pstTempItem );
    DHCP_Free( DHCPC_HANDLE, pstTempItem );
    /* 这里应该释放dhcp控制块 */

    DHCPC_FreeDhcpCtrlBlk( pstReqMsg->ulTeidc, pstDhcpcCtlBlk->ulTEIDC, pstDhcpcCtlBlk->ucUser, pstDhcpcCtlBlk->ulPDPIndex);

    return;
}

/*****************************************************************************
 函 数 名  : DHCPC_ProcIpv6Release
 功能描述  : 处理LAP发送的IPV6地址释放消息
 输入参数  : LAP2_DHCPC_MSG_S* pstReqMsg
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年7月10日
    作    者   : jixiaoming 00180244
    修改内容   : 新生成函数

*****************************************************************************/
VOID DHCPC_ProcIpv6Release(LAP2_DHCPC_MSG_S* pstReqMsg)
{
    ULONG ulReturn = VOS_ERR;
    DHCPC_CTRLBLK *pstDhcpcContext = NULL;
    DHCPV6C_PRE_RESULT_S stPreResult = {0};

    DHCPV6C_DBGCNT_ADD(E_DHCPV6C_REV_LAP_RELEASE_MSG);

    ulReturn = DHCPC_QueryDhcpcContext(pstReqMsg->ucAddressType, pstReqMsg->ulTeidc, &pstDhcpcContext);
    if (VOS_OK != ulReturn)
    {
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_LAPREL_QRY_CONTEXT_FAIL);
        return;
    }

    stPreResult.pstDhcpcContext = pstDhcpcContext;
    stPreResult.pMsg = NULL;
    stPreResult.enEvent = DHCPV6C_EV_IP_RELEASE;

    /* 清除lap的资源位 */
    DHCPC_CLR_RESOURCE(pstDhcpcContext->ucResource, DHCPC_LAP_RESOURCE);

    /* 设置原因值为缺省 */
    pstDhcpcContext->ucCause = DHCPV6C_CAUSE_DEFAULT;

    /* 运行状态机 */
    DHCPV6C_RunFsm(&stPreResult);

    return;
}
/*****************************************************************************
 函 数 名  : DHCPC_MsgProc_Release
 功能描述  : 处理地址释放，冲突的消息
 输入参数  : DHCPC_AMREQMSG_S   *pstReqMsg
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年11月26日
    作    者   : zhangyang 00142225
    修改内容   : 新生成函数
*****************************************************************************/
VOID DHCPC_MsgProc_Release( LAP2_DHCPC_MSG_S* pstReqMsg)
{
    DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n-->DHCPC_MsgProc_Release()" );

    if( NULL == pstReqMsg)
    {
        VOS_Assert(0);
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_088);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\nDHCPC_MsgProc_Lease() pstReqMsg =null!" );
        return;
    }

    if (M_AM_USM_ADDRTYPE_IPV4 == pstReqMsg->ucAddressType)
    {
        DHCPC_ProcIpv4Release(pstReqMsg);
    }
    else
    {
        DHCPC_ProcIpv6Release(pstReqMsg);
    }

    return;
}

/*****************************************************************************
 函 数 名  : DHCPC_MsgProcIpv4Conflict
 功能描述  : 处理lap发送的ipv4地址冲突消息
 输入参数  : LAP2_DHCPC_MSG_S* pstReqMsg
 输出参数  : 无
 返 回 值  : ULONG
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年7月18日
    作    者   : jixiaoming 00180244
    修改内容   : 封装函数

*****************************************************************************/
ULONG DHCPC_MsgProcIpv4Conflict(LAP2_DHCPC_MSG_S* pstReqMsg)
{
    DHCPC_TEMPCTRLBLK*    pstTempItem = NULL;
    DHCPC_CTRLBLK        *pstDhcpCtrlBlk = NULL;

    DHCPC_FUNC_ENTRY();

    /*获取DHCP控制块*/
    pstDhcpCtrlBlk = DHCPC_CalcCtlBlkHashValue( pstReqMsg->ulTeidc, pstReqMsg->ulTeidc);
    if ( NULL == pstDhcpCtrlBlk )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_096);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n there is no DHCPCTRLBLK REC!" );
        VOS_Assert( 0 );
        return VOS_ERR;
    }

    /*初始化stTempItem */
    pstTempItem = ( DHCPC_TEMPCTRLBLK * )DHCP_Malloc( DHCPC_HANDLE, sizeof( DHCPC_TEMPCTRLBLK ) );
    if ( NULL == pstTempItem )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_097);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n alloc null memory!" );
        VOS_Assert( 0 );
        return VOS_ERR;
    }

    PGP_MemZero( pstTempItem, sizeof( DHCPC_TEMPCTRLBLK ) );

    DHCPC_INIT_ITEM( pstTempItem );
    /*把pReqMsg中内容填充到stTempItem 中*/
    DHCPC_RELEASEMSG2ITEM( pstReqMsg, pstTempItem );
    pstTempItem->ulSrvIp = pstDhcpCtrlBlk->aulSrvIp[0];
    pstTempItem->ulDHCPCtlIdx = pstDhcpCtrlBlk->ulDHCPCtxIdx;
    pstTempItem->ulPdpIndex = pstDhcpCtrlBlk->ulPDPIndex;
    pstTempItem->ulAgetIP = pstDhcpCtrlBlk->aulAgentIpAddr[0];
    pstTempItem->ulUserIpAddr = pstDhcpCtrlBlk->aulUserIpAddr[0];
    pstTempItem->usDhcpGroupIndex = pstDhcpCtrlBlk->usServerGrpIndex;
    pstTempItem->aulMSISDN[0]= pstDhcpCtrlBlk->aulMSISDN[0];
    pstTempItem->aulMSISDN[1]= pstDhcpCtrlBlk->aulMSISDN[1];

    pstTempItem->aulIMSI[0]= pstDhcpCtrlBlk->aulIMSI[0];
    pstTempItem->aulIMSI[1]= pstDhcpCtrlBlk->aulIMSI[1];
    /* BEGIN: Added by jixiaoming for  IMEI跟踪 at 2012-8-17 */
    pstTempItem->aulIMEI[0]= pstDhcpCtrlBlk->aulIMEI[0];
    pstTempItem->aulIMEI[1]= pstDhcpCtrlBlk->aulIMEI[1];
    /* END: Added by jixiaoming for IMEI跟踪 at 2012-8-17 */

    pstTempItem->ucRole = pstDhcpCtrlBlk->ucRole;
    pstTempItem->ucUser= pstDhcpCtrlBlk->ucUser;
    pstTempItem->ulTEIDC = pstDhcpCtrlBlk->ulTEIDC;
    pstTempItem->ucLAPNo = pstDhcpCtrlBlk->ucLAPNo;

    pstTempItem->ucRandomNo = pstDhcpCtrlBlk->ucRandomNo;

    /*发送消息*/
    ( VOID )DHCPC_Pkt_Send( DHCP_DECLINE, pstTempItem );
    DHCP_Free( DHCPC_HANDLE, pstTempItem );
    /* 这里应该释放dhcp控制块 */

    DHCPC_FreeDhcpCtrlBlk( pstReqMsg->ulTeidc, pstDhcpCtrlBlk->ulTEIDC, pstDhcpCtrlBlk->ucUser, pstDhcpCtrlBlk->ulPDPIndex);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : DHCPC_MsgProcIpv6Conflict
 功能描述  : 处理lap发送的ipv6地址冲突消息
 输入参数  : LAP2_DHCPC_MSG_S* pstReqMsg
 输出参数  : 无
 返 回 值  : ULONG
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年7月18日
    作    者   : jixiaoming 00180244
    修改内容   : 新生成函数

*****************************************************************************/
ULONG DHCPC_MsgProcIpv6Conflict(LAP2_DHCPC_MSG_S* pstReqMsg)
{
    ULONG ulReturn = VOS_ERR;
    DHCPC_CTRLBLK *pstDhcpcContext = NULL;
    DHCPV6C_PRE_RESULT_S stPreResult = {0};

    DHCPV6C_DBGCNT_ADD(E_DHCPV6C_REV_LAP_CONFLICT_MSG);

    DHCPC_FUNC_ENTRY();

    ulReturn = DHCPC_QueryDhcpcContext(pstReqMsg->ucAddressType, pstReqMsg->ulTeidc, &pstDhcpcContext);
    if (VOS_OK != ulReturn)
    {
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_REV_LAP_CONFLICT_FAIL);
        return VOS_ERR;
    }

    stPreResult.pstDhcpcContext = pstDhcpcContext;
    stPreResult.pMsg = NULL;
    stPreResult.enEvent = DHCPV6C_EV_IP_DECLINE;

    /* 清除lap的资源位 */
    DHCPC_CLR_RESOURCE(pstDhcpcContext->ucResource, DHCPC_LAP_RESOURCE);

    /* 设置原因值为缺省 */
    pstDhcpcContext->ucCause = DHCPV6C_CAUSE_DEFAULT;

    /* 运行状态机 */
    DHCPV6C_RunFsm(&stPreResult);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : DHCPC_MsgProc_Conflict
 功能描述  : 处理LAP返回的地址冲突消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年12月31日
    作    者   : caopu
    修改内容   : 新生成函数
  2.日    期   : 2010年08月07日
    作    者   : w00140934
    修改内容   : 修改DHCP控制块结构

*****************************************************************************/
ULONG DHCPC_MsgProc_Conflict( LAP2_DHCPC_MSG_S* pstReqMsg)
{
    ULONG ulReturn = VOS_ERR;

    DHCPC_FUNC_ENTRY();

    if (M_AM_USM_ADDRTYPE_IPV4 == pstReqMsg->ucAddressType)
    {
        ulReturn = DHCPC_MsgProcIpv4Conflict(pstReqMsg);
    }
    else
    {
        ulReturn = DHCPC_MsgProcIpv6Conflict(pstReqMsg);
    }

    DHCPC_FUNC_EXIT(ulReturn);
    return ulReturn;
}

#define __CHECK__

/*****************************************************************************
 函 数 名  : DHCPC_PdpContextCheck
 功能描述  : 筛选出需要做SDB核查的上下文
 输入参数  : VOID
 输出参数  : 无
 返 回 值  : VOS_OK:需要做SDB核查，VOS_ERR:不需要做SDB核查
 调用函数  :
 被调函数  : DHCPC_SetAgingFlagBySDBContext

 修改历史      :
  1.日    期   : 2011年05月27日
    作    者   : j00142544
    修改内容   : 新生成函数

*****************************************************************************/
ULONG DHCPC_JudgePdpContextCheck(SDB_GSPU_CONTEXT_S *pstContext)
{
    if (NULL == pstContext)
    {
        /*异常情况，放弃该上下文，记录日志。*/
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_304);
        return VOS_ERR;
    }

    if (0 == pstContext->ulGspuBdIndex)
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_305);
        return VOS_ERR;
    }

    /* l2tp用户的上下文不作为SDB核查对象 */
    if (0 != pstContext->ucL2TPFlag)
    {
        return VOS_ERR;
    }


    if ( E_NET_ELEMENT_ROLE_GGSN == pstContext->ucUgwRole )
    {
        if ((USM_PCRFC_DELETE == pstContext->ucMachineState) || (USM_CM_DELETE == pstContext->ucMachineState) || (USM_WAIT_SGSN_DELETE == pstContext->ucMachineState))
        {
            /*表明上下文正处于去活*/
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_346);
            return VOS_ERR;
        }
    }
    else
    {
        if (E_AM_USM_L1_STATE_DELETE == pstContext->ucMachineState)
        {
            /*表明上下文正处于去活*/
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_347);
            return VOS_ERR;
        }
    }


    if (E_NET_ELEMENT_ROLE_GGSN == pstContext->ucUgwRole)
    {
        if (pstContext->ucMachineState <= USM_IP_APPLY)
        {
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_306);
            return VOS_ERR;
        }
    }
    else if ((E_NET_ELEMENT_ROLE_PGW == pstContext->ucUgwRole)
              || (E_NET_ELEMENT_ROLE_PGW_AND_SGW == pstContext->ucUgwRole))
    {
        if (E_AM_USM_L1_STATE_CREATE > pstContext->ucMachineState)
        {
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_307);
            return VOS_ERR;
        }

        if ((E_AM_USM_L1_STATE_CREATE == pstContext->ucMachineState)
                &&( E_AM_USM_L2_STATE_LAP >= pstContext->ucMachineL2State))
        {
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_308);
            return VOS_ERR;
        }
    }
    else
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_309);
        return VOS_ERR;
    }

    /* BEGIN: Modified for PN:DHCPv6特性 by tianyang 00144555, 2012/7/24 */
    if ((GTP_DHCP_ALLOC_ADDR != pstContext->ucIPv4AllocType)
        && (GTP_DHCP_ALLOC_ADDR != pstContext->ucIPv6AllocType))
    /* END:   Modified for PN:DHCPv6特性 by tianyang 00144555, 2012/7/24 */
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_315);
        return VOS_ERR;
    }

    DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_310);
    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : DHCPC_NotifyLAPRelContext
 功能描述  : DHCPC根据上下文信息通知lap去活上下文。
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :DHCPC_SetAgingFlagBySDBContext
 修改历史       :
  1.日      期   : 2011年08月10日
    作      者   : jiahuidong00142544
    修改内容   : 新生成函数

  2.日      期   : 2012年07月25日
    作      者   : tianyang 00144555
    修改内容   : 增加IPV6相关处理
*****************************************************************************/
ULONG DHCPC_NotifyLAPRelContext(UCHAR ucIPType, SDB_GSPU_CONTEXT_S *pstContext)
{
    ULONG ulRet = VOS_OK;
    LAP2_DHCPC_MSG_S stSendMessage = {0};

    if (NULL == pstContext)
    {
        return VOS_OK;
    }

    /*封装地址消息*/
    stSendMessage.ulTeidc = DHCPC_GetTedicByUgwRole(pstContext->ucUgwRole, pstContext->ulSgwLeftLocTeidc, pstContext->ulS5_Gn_LocTeidc);

    stSendMessage.usApnIndex  =  pstContext->usApnIndex;
    stSendMessage.usVpnId =  pstContext->usVpnId;
    stSendMessage.ulIndex  =  pstContext->ulGspuBdIndex;
    stSendMessage.ucStaticIpRouteType = pstContext->ucStaticIpRouteType;
    stSendMessage.ucMsgType  = DHCPC_SND2_LAP2_REL_CONTEXT;
    stSendMessage.ucSCID = (UCHAR)DHCPC_SELF_CMPIDX_INSG;

    if ( LAP_IPV4 == ucIPType )
    {
        stSendMessage.ucAddressType = M_AM_USM_ADDRTYPE_IPV4;
        stSendMessage.aulPdpAddr[0] = pstContext->ulIPv4Addr;
        stSendMessage.ucSectionNum = pstContext->ucLapSectionV4Num;
        stSendMessage.ucLAPNo = pstContext->ucipv4LAPSequence;
        stSendMessage.usPoolIndex = pstContext->usPoolIndex;

        /*发送消息给lap，由lap通知usm去活用户。*/
        ulRet = DHCPC_SendAddrMsgToLAP((VOID *)(&stSendMessage),
                                          sizeof(LAP2_DHCPC_MSG_S),
                                          pstContext->ulIPv4Addr,
                                          pstContext->ucipv4LAPSequence);
    }
    else
    {
        stSendMessage.ucAddressType = M_AM_USM_ADDRTYPE_IPV6;
        stSendMessage.aulPdpAddr[0] = pstContext->stIPv6Addr.s6_addr32[0];
        stSendMessage.aulPdpAddr[1] = pstContext->stIPv6Addr.s6_addr32[1];
        stSendMessage.aulPdpAddr[2] = pstContext->stIPv6Addr.s6_addr32[2];
        stSendMessage.aulPdpAddr[3] = pstContext->stIPv6Addr.s6_addr32[3];
        stSendMessage.ucSectionNum = pstContext->ucLapSectionV6Num;
        stSendMessage.ucLAPNo = pstContext->ucipv6LAPSequence;
        stSendMessage.usPoolIndex = pstContext->usPoolIPV6Index;

        /*发送消息给lap，由lap通知usm去活用户。*/
        ulRet = DHCPC_SendAddrMsgToLAP((VOID *)(&stSendMessage),
                                          sizeof(LAP2_DHCPC_MSG_S),
                                          pstContext->stIPv6Addr.s6_addr32[1],
                                          pstContext->ucipv6LAPSequence);
    }

    if (VOS_OK != ulRet)
    {
        return ulRet;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : DHCPC_ReleaseDhcpCtrlBlock
 功能描述  :根据dhcp控制块释放dhcp控制块资源
 输入参数  : DHCPC_CTRLBLK *pstDhcpcCtlBlk
 输出参数  : 无
 返 回 值  : ULONG
 调用函数  :
 被调函数  :
 修改历史       :
  1.日      期   : 2011年04月26日
    作      者   : jiahuidong 00142544
    修改内容   : 新生成函数

*****************************************************************************/
ULONG DHCPC_ReleaseDhcpCtrlBlock(DHCPC_CTRLBLK *pstDhcpcCtlBlk)
{
    DHCPC_CTRLBLK_NODE *pstDhcpcTempCtlBlkNode = NULL;
    DHCPC_TEMPCTRLBLK *pstDhcpcTempCtlBlk = NULL;

    if (NULL == pstDhcpcCtlBlk)
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_301);
        return VOS_ERR;
    }

    /*获取临时控制块节点*/
    pstDhcpcTempCtlBlkNode = ( DHCPC_CTRLBLK_NODE* )DHCP_Malloc( DHCPC_HANDLE, sizeof( DHCPC_CTRLBLK_NODE ) );
    if ( NULL == pstDhcpcTempCtlBlkNode )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_302);
        VOS_DBGASSERT( 0 );
        return VOS_ERR;
    }

    PGP_MemZero( pstDhcpcTempCtlBlkNode,sizeof( DHCPC_CTRLBLK_NODE ) );
    pstDhcpcTempCtlBlk = &( pstDhcpcTempCtlBlkNode->stDhcpcTmpCtlBlk );

    pstDhcpcTempCtlBlk->ulUserIpAddr = pstDhcpcCtlBlk->aulUserIpAddr[0];
    pstDhcpcTempCtlBlk->ucUserType = pstDhcpcCtlBlk->ucUserType;
    pstDhcpcTempCtlBlk->usPoolIndex = pstDhcpcCtlBlk->usPoolIndex;
    pstDhcpcTempCtlBlk->ulAgetIP = pstDhcpcCtlBlk->aulAgentIpAddr[0];
    pstDhcpcTempCtlBlk->ulPdpIndex = pstDhcpcCtlBlk->ulPDPIndex;
    pstDhcpcTempCtlBlk->ucAddressType = LAP_IPV4;
    pstDhcpcTempCtlBlk->usDhcpGroupIndex = pstDhcpcCtlBlk->usServerGrpIndex;
    pstDhcpcTempCtlBlk->ucSCID = (UCHAR)DHCPC_SELF_CMPIDX_INSG;
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

    pstDhcpcTempCtlBlk->ucRandomNo = pstDhcpcCtlBlk->ucRandomNo;

    /* 给LAP2发送消息，通知删除用户  */
    DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPC_RenewTimeOutMsg to lap,ulUserIpAddr = %u,usPoolIndex = %d,ulAgetIP = %u!",
    pstDhcpcTempCtlBlk->ulUserIpAddr, pstDhcpcTempCtlBlk->usPoolIndex, pstDhcpcTempCtlBlk->ulAgetIP );
    DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_201);

    (VOID)DHCPC_SendMsgToLAP2( pstDhcpcTempCtlBlkNode, DHCPC_SND2_LAP2_ADDR_REL_MSG );

    /* 发送release消息 */
    (VOID)DHCPC_Pkt_Send(DHCP_RELEASE, pstDhcpcTempCtlBlk);

    /* 这里应该释放dhcp控制块,临时控制块 */
    DHCPC_FreeDhcpCtrlBlk( pstDhcpcCtlBlk->ulDHCPCtxIdx, pstDhcpcCtlBlk->ulTEIDC, pstDhcpcCtlBlk->ucUser, pstDhcpcCtlBlk->ulPDPIndex);
    DHCP_Free( DHCPC_HANDLE, pstDhcpcTempCtlBlkNode );
    pstDhcpcTempCtlBlkNode = NULL;
    pstDhcpcTempCtlBlk = NULL;

    DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_303);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : DHCPC_SendRtMsg
 功能描述  :
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
ULONG DHCPC_SendRtMsg(VOS_UINT64 ullDstCsi, ULONG ulMsgType, ULONG ulMsgCode, UCHAR *pucMsg, ULONG ulMsgLen )
{
    ULONG ulReturn = VOS_OK;
    UCHAR *pucRtMsg = VOS_NULL;

    if ((VOS_NULL == pucMsg) || (0 == ulMsgLen))
    {
        return VOS_ERR;
    }

    pucRtMsg = (UCHAR*)DHCP_RTDistributeAllocMsg(DHCPC_HANDLE, ulMsgLen);
    if (VOS_NULL == pucRtMsg)
    {
        return VOS_ERR;
    }

    VOS_MemCpy(pucRtMsg, pucMsg, ulMsgLen);

    RTD_SET_MSGCODE(pucRtMsg, (USHORT)ulMsgCode);
    ulReturn = DHCP_RTDistributeSend(DHCPC_SELF_CSI,
                           ullDstCsi,
                           pucRtMsg,
                           ulMsgLen,
                           ulMsgType);

    if (VOS_OK != ulReturn)
    {
        DHCP_RTDistributeFreeMsg(pucRtMsg);
        return VOS_ERR;
    }

    return VOS_OK;
}



ULONG DHCPC_SendURTMsg(VOS_UINT64 ullSrcCsi, VOS_UINT64 ullDstCsi, ULONG ulMsgType,
                      ULONG ulMsgCode, UCHAR *pucMsg, ULONG ulMsgLen )
{
    PMBUF_S *pstMbuf   = VOS_NULL;
    ULONG ulRet = 0;
    ULONG ulMode = 0;

    /* 检查接收方CSI是否正常 */
    if ( !PSM_Inf_GetStatByCSI(ullDstCsi))
    {
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "Dst CPU is not registered!");
        return VOS_ERR;
    }

#if 0
    pstMbuf = PMBUF_CreateByCopyBuffer(0, ulMsgLen, pucMsg, PMBUF_TYPE_DATA, MID_PAPI);
#endif
    pstMbuf = PMBUF_GetPMbuf(MID_DHCPC, ulMsgLen);

    if (VOS_NULL == pstMbuf)
    {
        DHCPC_DebugPrint(PTM_LOG_ERR, "PMBUF_CreateByCopyBuffer fail");
        return VOS_ERR;
    }

    URTD_SET_MSGCODE(pstMbuf, (UCHAR)ulMsgCode);

    if ( CRM_BOARD_TYPE_SPUD == g_ulDhcpcSpuType )
    {
        ulMode = URTD_PRIORITY_LOW;
    }
    else
    {
        ulMode = URTD_PRIORITY_HIGH;
    }

    /* 调用URT接口发送 */
    ulRet = PGP_URTDistributeSend(ullSrcCsi,
                                 ullDstCsi,
                                 pstMbuf,
                                 ulMode,
                                 ulMsgType,
                                 M_PTM_HASH_GENE);
    if (VOS_OK != ulRet)
    {
        /* 发送失败，需要释放PMBUF */
        (VOID)PMBUF_Destroy(pstMbuf);

        DHCPC_DebugPrint(PTM_LOG_ERR, "PGP_URTDistributeSend fail, ulRet = %x", ulRet);
        return ulRet;
    }

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : DHCPC_SendSelfPdpCheckMsg
 功能描述  : DHCPC向自身发送上下文核查消息
 输入参数  : ULONG ulPdpIndex
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年5月17日
    作    者   : y00138047
    修改内容   : 新生成函数

*****************************************************************************/
VOID DHCPC_SendSelfPdpCheckMsg(ULONG ulPdpIndex)
{
    DHCPC_INNER_MSG_S stInnerMsg = {0};

    stInnerMsg.ulMsgCode = DHCPC_INNER_MSGCODE_CHECK_PDP;
    stInnerMsg.ulPdpIndex = ulPdpIndex;

    (VOID)DHCPC_SendRtMsg(DHCPC_SELF_CSI, DHCPC_MSG_TYPE_SELF, DHCPC_INNER_MSGCODE_CHECK_PDP,
                          (UCHAR *)&stInnerMsg, sizeof(DHCPC_INNER_MSG_S));

    return;
}

/*****************************************************************************
 函 数 名  : DHCPC_SendSelfCtlBlockCheckMsg
 功能描述  : DHCPC向自身发送控制块核查消息
 输入参数  : ULONG ulHashValue
 输出参数  : 无
 返 回 值  : ULONG
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年5月17日
    作    者   : y00138047
    修改内容   : 新生成函数

*****************************************************************************/
ULONG DHCPC_SendSelfCtlBlockCheckMsg(ULONG ulHashValue)
{
    DHCPC_INNER_MSG_S stInnerMsg = {0};

    stInnerMsg.ulMsgCode = DHCPC_INNER_MSGCODE_CHECK_CNTRL_BLCK;
    stInnerMsg.ulCtlBlockHashValue = ulHashValue;

    (VOID)DHCPC_SendRtMsg(DHCPC_SELF_CSI, DHCPC_MSG_TYPE_SELF, DHCPC_INNER_MSGCODE_CHECK_CNTRL_BLCK,
                          (UCHAR *)&stInnerMsg, sizeof(DHCPC_INNER_MSG_S));

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : DHCPC_CheckPdpByCrtBlk
 功能描述  : 根据DHCP控制块核查上下文信息
 输入参数  : DHCPC_CTRLBLK *pstDhcpcCtlBlk
             SDB_GSPU_CONTEXT_S *pstContext
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年7月24日
    作    者   : tianyang 00144555
    修改内容   : 新生成函数

*****************************************************************************/
VOID DHCPC_CheckPdpByCrtBlk(UCHAR ucIpType, DHCPC_CTRLBLK *pstDhcpcCtlBlk, SDB_GSPU_CONTEXT_S *pstContext)
{
    UCHAR ucLogicSlot = 0;

    if (NULL != pstDhcpcCtlBlk)
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_311);

        if ((LAP_IPV4 == ucIpType) && ((DHCPC_STATE_LEASE == pstDhcpcCtlBlk->usDhcpStatus)
             ||( DHCPC_STATE_ReNewing == pstDhcpcCtlBlk->usDhcpStatus)
             ||( DHCPC_STATE_PreReBinding == pstDhcpcCtlBlk->usDhcpStatus)
             ||( DHCPC_STATE_ReBinding == pstDhcpcCtlBlk->usDhcpStatus)
             ||( DHCPC_STATE_BOUND == pstDhcpcCtlBlk->usDhcpStatus)))
        {
            /*控制块中的老化标记清为0*/
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_312);
            pstDhcpcCtlBlk->ucAgingFlag = 0;
        }

        if ((LAP_IPV6 == ucIpType)
            && ((DHCPV6C_STATE_BOUND == pstDhcpcCtlBlk->usDhcpStatus)
            || (DHCPV6C_STATE_RENEW == pstDhcpcCtlBlk->usDhcpStatus)))
        {
            /*控制块中的老化标记清为0*/
            /* 计数 */
            pstDhcpcCtlBlk->ucAgingFlag = 0;
        }

        return;
    }

    ucLogicSlot = (UCHAR)CRM_GetSelfLogicSlotID();
    if (E_CRM_ACTIVE != CRM_GetSlotPrimaryInfoOfSelfGroup(ucLogicSlot))
    {
        return;
    }
    DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_316);
    /*上下文存在，而dhcp控制块不存在，说明上下文已经残留，此时通知LAP去活*/

    if ( NULL == pstContext )
    {
        VOS_DBGASSERT(0);
        return;
    }

    (VOID)DHCPC_NotifyLAPRelContext(ucIpType, pstContext);

    return;
}

/*****************************************************************************
 函 数 名  : DHCPC_GetTedicByUgwRole
 功能描述  : 根据UGW角色选择所用的Tedic，当角色为SGW时选择ulSgwLeftLocTeidc
 输入参数  : UCHAR ucUgwRole
             ULONG ulSgwLeftLocTeidc
             ULONG ulS5_Gn_LocTeidc
 输出参数  : 无
 返 回 值  : ULONG
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年7月24日
    作    者   : tianyang 00144555
    修改内容   : 新生成函数

*****************************************************************************/
ULONG DHCPC_GetTedicByUgwRole(UCHAR ucUgwRole, ULONG ulSgwLeftLocTeidc, ULONG ulS5_Gn_LocTeidc)
{
    if (E_NET_ELEMENT_ROLE_SGW == ucUgwRole)
    {
        return ulSgwLeftLocTeidc;
    }

    return ulS5_Gn_LocTeidc;
}

/*****************************************************************************
 函 数 名  : DHCPC_CheckPdpProcForIpv4
 功能描述  : DHCPV4核查上下文处理函数
 输入参数  : SDB_GSPU_CONTEXT_S *pstContext
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年7月24日
    作    者   : tianyang 00144555
    修改内容   : 新生成函数

*****************************************************************************/
VOID DHCPC_CheckPdpProcForIpv4(SDB_GSPU_CONTEXT_S *pstContext)
{
    ULONG ulTeidc = 0;
    DHCPC_CTRLBLK *pstDhcpcCtlBlk = NULL;

    if ( NULL == pstContext )
    {
        VOS_DBGASSERT(0);
        return;
    }

    if ( GTP_DHCP_ALLOC_ADDR != pstContext->ucIPv4AllocType )
    {
        /* 计数 */
        return;
    }

    /*根据上下文中记录的teidc查找dhcp控制块*/
    ulTeidc = DHCPC_GetTedicByUgwRole(pstContext->ucUgwRole, pstContext->ulSgwLeftLocTeidc, pstContext->ulS5_Gn_LocTeidc);

    pstDhcpcCtlBlk = (DHCPC_CTRLBLK *)DHCPC_CalcCtlBlkHashValue(ulTeidc, ulTeidc);

    DHCPC_CheckPdpByCrtBlk(LAP_IPV4, pstDhcpcCtlBlk, pstContext);

    return;
}

/*****************************************************************************
 函 数 名  : DHCPC_CheckPdpProcForIpv6
 功能描述  : DHCPV6核查上下文处理函数
 输入参数  : SDB_GSPU_CONTEXT_S *pstContext
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年7月24日
    作    者   : tianyang 00144555
    修改内容   : 新生成函数

*****************************************************************************/
VOID DHCPC_CheckPdpProcForIpv6(SDB_GSPU_CONTEXT_S *pstContext)
{
    ULONG ulTeidc = 0;
    DHCPC_CTRLBLK *pstDhcpcCtlBlk = NULL;

    if ( NULL == pstContext )
    {
        VOS_DBGASSERT(0);
        return;
    }

    if ( GTP_DHCP_ALLOC_ADDR != pstContext->ucIPv6AllocType )
    {
        /* 计数 */
        return;
    }

    /*根据上下文中记录的teidc查找dhcp控制块*/
    ulTeidc = DHCPC_GetTedicByUgwRole(pstContext->ucUgwRole, pstContext->ulSgwLeftLocTeidc, pstContext->ulS5_Gn_LocTeidc);

    (VOID)DHCPC_QueryDhcpcContext(LAP_IPV6, ulTeidc, &pstDhcpcCtlBlk);

    DHCPC_CheckPdpByCrtBlk(LAP_IPV6, pstDhcpcCtlBlk, pstContext);

    return;
}

/*****************************************************************************
 函 数 名  : DHCPC_CheckPdpContext
 功能描述  : DHCPC核查PDP上下文
 输入参数  : DHCPC_INNER_MSG_S *pstInnerMsg
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年5月17日
    作    者   : y00138047
    修改内容   : 新生成函数

  2.日    期   : 2012年7月24日
    作    者   : tianyang 00144555
    修改内容   : 增加DHCPV6特性老化功能

*****************************************************************************/
VOID DHCPC_CheckPdpContext(DHCPC_INNER_MSG_S *pstInnerMsg)
{
    ULONG ulRet = VOS_OK;
    ULONG ulScanPdpNum = 0;
    SDB_GSPU_CONTEXT_S *pstContext = VOS_NULL_PTR;
    ULONG ulPdpIndex = 0;

    if ( NULL == pstInnerMsg )
    {
        return;
    }

    ulPdpIndex = pstInnerMsg->ulPdpIndex;

    for (; ulPdpIndex <= SDB_MAX_CONTEXT_NUM; ulPdpIndex++)
    {
        ulScanPdpNum++;
        if (0 == (ulScanPdpNum % 10))
        {
            DHCPC_SendSelfPdpCheckMsg(ulPdpIndex);
            return;
        }

        /*根据PDP INDEX, 获取上下文*/
        ulRet = (ULONG)SDB_GetContextByIndex(ulPdpIndex, (UCHAR**)&pstContext);
        if ((ulRet != VOS_OK) || (NULL == pstContext))
        {
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_314);
            continue;
        }

        /*没有申请到地址的上下文不做为老化对象*/
        if (VOS_OK != DHCPC_JudgePdpContextCheck(pstContext))
        {
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_313);
            continue;
        }

        DHCPC_CheckPdpProcForIpv4(pstContext);

        DHCPC_CheckPdpProcForIpv6(pstContext);

    }

    (VOID)DHCPC_SendSelfCtlBlockCheckMsg(0);
    return;
}

/*****************************************************************************
 函 数 名  : DHCPC_CheckCtrBlkforIpv6
 功能描述  : DHCPV6控制块老化处理函数
 输入参数  : ULONG ulHashValue
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年7月24日
    作    者   : tianyang 00144555
    修改内容   : 新生成函数

*****************************************************************************/
VOID DHCPC_CheckCtrBlkforIpv6(ULONG ulSelftSlotState, ULONG ulHashValue)
{
    ULONG ulRet = VOS_OK;
    DHCPC_CTRLBLK *pstDhcpcCtlBlk = NULL;
    DHCPC_CTRLBLK *pstDhcpcNextCtlBlk = NULL;

    pstDhcpcCtlBlk = g_pstDhcpcIpv6CtrlBlkRec[ulHashValue];

    while ( NULL != pstDhcpcCtlBlk )
    {
        pstDhcpcNextCtlBlk = pstDhcpcCtlBlk->pstNextNode;

        (pstDhcpcCtlBlk->ucAgingFlag)++;

        if ( pstDhcpcCtlBlk->ucAgingFlag <= DHCPC_AGING_TIMES )
        {
            pstDhcpcCtlBlk = pstDhcpcNextCtlBlk;
            continue;
        }

        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_CHECK_BLKDEL);
        ulRet = DHCPC_IsTimNodeExist(LAP_IPV6, pstDhcpcCtlBlk->ulTEIDC);
        if (VOS_OK == ulRet)
        {
            (VOID)DHCPC_StopTimer(LAP_IPV6, pstDhcpcCtlBlk->ulTEIDC, DHCPV6C_EV_TIMER_LEASE_EXPIRE);
            (VOID)DHCPC_StopTimer(LAP_IPV6, pstDhcpcCtlBlk->ulTEIDC, DHCPV6C_EV_TIMER_RENEW);
        }

        (VOID)DHCPC_FreeDhcpcContext(LAP_IPV6, pstDhcpcCtlBlk->ulTEIDC);

        pstDhcpcCtlBlk = pstDhcpcNextCtlBlk;
    }
}

/*****************************************************************************
 函 数 名  : DHCPC_CheckCtrBlkforIpv4
 功能描述  : DHCPV6控制块老化处理函数
 输入参数  : ULONG ulHashValue
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年7月24日
    作    者   : tianyang 00144555
    修改内容   : 新生成函数

*****************************************************************************/
VOID DHCPC_CheckCtrBlkforIpv4(ULONG ulSelftSlotState, ULONG ulHashValue)
{
    DHCPC_CTRLBLK *pstDhcpcCtlBlk = NULL;
    DHCPC_CTRLBLK *pstDhcpNewcCtlBlk = NULL;

    pstDhcpcCtlBlk = (DHCPC_CTRLBLK *)g_pstDhcpcCtrlBlkRec[ulHashValue];
    for (;;)
    {
        if (NULL == pstDhcpcCtlBlk)
        {
            break;
        }

        pstDhcpNewcCtlBlk = pstDhcpcCtlBlk->pstNextNode;
        (pstDhcpcCtlBlk->ucAgingFlag)++;

        if (DHCPC_AGING_TIMES >= pstDhcpcCtlBlk->ucAgingFlag)
        {
            pstDhcpcCtlBlk = pstDhcpNewcCtlBlk;
            continue;
        }

        /*dhcp控制块没有相应的上下文，此时应该释放dhcp控制块对应的资源*/
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_300);

        if ( E_CRM_ACTIVE == ulSelftSlotState )
        {
            (VOID)DHCPC_ReleaseDhcpCtrlBlock(pstDhcpcCtlBlk);
        }
        else
        {
            DHCPC_FreeDhcpCtrlBlk( pstDhcpcCtlBlk->ulDHCPCtxIdx,
                pstDhcpcCtlBlk->ulTEIDC, pstDhcpcCtlBlk->ucUser, pstDhcpcCtlBlk->ulPDPIndex);
        }

        /*获取下一个dhcp控制块*/
        pstDhcpcCtlBlk = pstDhcpNewcCtlBlk;
    }
}

/*****************************************************************************
 函 数 名  : DHCPC_CheckCtlBlock
 功能描述  : DHCPC核查DHCP控制块
 输入参数  : DHCPC_INNER_MSG_S *pstInnerMsg
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年5月17日
    作    者   : y00138047
    修改内容   : 新生成函数

*****************************************************************************/
VOID DHCPC_CheckCtlBlock(DHCPC_INNER_MSG_S *pstInnerMsg)
{
    ULONG ulHashValue = 0;
    ULONG ulScanNum = 0;
    ULONG ulSelftSlotState = 0;
    UCHAR ucLogicSlot = 0;

    if ( NULL == pstInnerMsg )
    {
        return;
    }

    ucLogicSlot = (UCHAR)CRM_GetSelfLogicSlotID();
    ulSelftSlotState = CRM_GetSlotPrimaryInfoOfSelfGroup(ucLogicSlot);
    if ((E_CRM_ACTIVE != ulSelftSlotState) && (E_CRM_STANDBY != ulSelftSlotState))
    {
        return;
    }


    pstInnerMsg = (DHCPC_INNER_MSG_S *)pstInnerMsg;
    ulHashValue = pstInnerMsg->ulCtlBlockHashValue;

    for(; ulHashValue < DHCPC_CTRLBLK_HASH_TABLE_SIZE; ulHashValue++)
    {
        ulScanNum++;
        if (0 == (ulScanNum % 3))
        {
            (VOID)DHCPC_SendSelfCtlBlockCheckMsg(ulHashValue);
            return;
        }

        DHCPC_CheckCtrBlkforIpv4(ulSelftSlotState, ulHashValue);

        DHCPC_CheckCtrBlkforIpv6(ulSelftSlotState, ulHashValue);
    }

    return;
}

/*****************************************************************************
 函 数 名  : DHCPC_SelfMsgProc
 功能描述  : dhcpc处理内部消息
 输入参数  : UCHAR *pucMsg
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年5月17日
    作    者   : y00138047
    修改内容   : 新生成函数

*****************************************************************************/
VOID DHCPC_SelfMsgProc(UCHAR *pucMsg)
{
    DHCPC_INNER_MSG_S *pstInnerMsg = NULL;

    if ( NULL == pucMsg )
    {
        return;
    }

    pstInnerMsg = (DHCPC_INNER_MSG_S *)pucMsg;

    switch ( pstInnerMsg->ulMsgCode )
    {
        case DHCPC_INNER_MSGCODE_CHECK_PDP :
            DHCPC_CheckPdpContext(pstInnerMsg);
            break;

        case DHCPC_INNER_MSGCODE_CHECK_CNTRL_BLCK :
            DHCPC_CheckCtlBlock(pstInnerMsg);
            break;

        case DHCPC_INNER_MSGCODE_TIM_RESTORE :
            DHCPV6C_TimerRestoreForSpud(pstInnerMsg);
            break;

        case DHCPC_INNER_MSGCODE_BOARD_STATE_CHANGE :
            DHCPV6C_ProcBoardStateChangeMsg();
            break;

        default:
            VOS_Assert(0);
            break;
    }

    return;
}
