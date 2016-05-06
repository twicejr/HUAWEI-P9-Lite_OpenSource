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
#define    THIS_FILE_ID          PS_FILE_ID_DHCPC_SERVER_C
/*lint +e767*/

/*****************************************************************************
 函 数 名  : DHCPC_UpdateServerGroupStatusNormal
 功能描述  : 将当前使用的服务器的状态设置为Normal
 输入参数  : DHCPC_CTRLBLK *pstDhcpcContext
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月3日
    作    者   : jixiaoming 00180244
    修改内容   : 新生成函数

*****************************************************************************/
VOID DHCPC_UpdateServerGroupStatusNormal(ULONG ulSvrGrpIndex, UCHAR ucCurrentSrv)
{
    if (DHCPC_PRIMARY_SERVER == ucCurrentSrv)
    {
        (VOID)DHCPM_SetPrimarySrvStatusByIndex(ulSvrGrpIndex, DHCP_SEVER_NORMAL);
    }
    else
    {
        (VOID)DHCPM_SetSecondarySrvStatusByIndex(ulSvrGrpIndex, DHCP_SEVER_NORMAL);
    }

    return;
}

/*****************************************************************************
 函 数 名  : DHCPC_TrySetCurSvrAbnormal
 功能描述  : 尝试将服务器的状态变为Abnormal.
             如果当前状态为Abnormal,什么都不做。
             如果不为Abnormal,将主服务器状态设置为Abnormal,同时设置状态变为
             TRY的时间间隔。
 输入参数  : ULONG ulSvrGrpIndex
             UCHAR ucCurrentSrv
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月25日
    作    者   : jixiaoming 00180244
    修改内容   : 新生成函数

*****************************************************************************/
VOID DHCPC_TrySetCurSvrAbnormal(ULONG ulSvrGrpIndex, UCHAR ucCurrentSrv)
{
    if (DHCPC_PRIMARY_SERVER == ucCurrentSrv)
    {
        (VOID)DHCPM_TrySetPrimStatusAbnormalByIndex(ulSvrGrpIndex);
    }
    else
    {
        (VOID)DHCPM_TrySetSecStatusAbnormalByIndex(ulSvrGrpIndex);
    }

    return;
}

/*****************************************************************************
 函 数 名  : DHCPC_ReachTotalLimit
 功能描述  : 向主备服务器发送消息达到最大重发次数处理
 输入参数  : DHCPC_CTRLBLK *pstDhcpcContext
 输出参数  : 无
 返 回 值  : ULONG
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月25日
    作    者   : jixiaoming 00180244
    修改内容   : 新生成函数

*****************************************************************************/
ULONG DHCPC_ReachTotalLimit(DHCPC_CTRLBLK *pstDhcpcContext)
{
    /* 设置当前使用的服务器状态 */
    DHCPC_TrySetCurSvrAbnormal(pstDhcpcContext->usServerGrpIndex, pstDhcpcContext->ucCurrentServer);

    pstDhcpcContext->ucCurSvrSendCount = 0;
    pstDhcpcContext->ucTotalSendCount = 0;

    /* 返回VOS_ERR,停止发送消息 */
    return VOS_ERR;
}

/*****************************************************************************
 函 数 名  : DHCPC_ReachSingleLimit
 功能描述  : 向一个服务器发送次数达到重发最大次数处理
 输入参数  : DHCPC_CTRLBLK *pstDhcpcContext
             LAP_DHCP_CFG_S *pstDhcpServer
             DHCP_SERVER_STATUS_S *pstDhcpServerStatus
 输出参数  : 无
 返 回 值  : ULONG
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月25日
    作    者   : jixiaoming 00180244
    修改内容   : 新生成函数

*****************************************************************************/
ULONG DHCPC_ReachSingleLimit(DHCPC_CTRLBLK *pstDhcpcContext, LAP_DHCP_CFG_S *pstDhcpServer,
                                DHCP_SERVER_STATUS_S *pstDhcpServerStatus)
{
    /* 首先设置当前使用的服务器状态 */
    DHCPC_TrySetCurSvrAbnormal(pstDhcpcContext->usServerGrpIndex, pstDhcpcContext->ucCurrentServer);

    /* 将向当前server发送消息次数清0 */
    pstDhcpcContext->ucCurSvrSendCount = 0;

    /* 如果是单服务器,发送达到最大次数,直接返回失败.不再进行发送 */
    if (DHCP_SEVER_INVALID_IP == pstDhcpServer->aulSecondaryServerIp[0])
    {
        return VOS_ERR;
    }

    /* 进行主备服务器切换 */
    if (DHCPC_PRIMARY_SERVER == pstDhcpcContext->ucCurrentServer)
    {
        /* 如果切换后服务器不是NORMAL,只尝试发送一次 */
        if (DHCP_SEVER_NORMAL != pstDhcpServerStatus->ucSecondarySrvStatus)
        {
            pstDhcpcContext->ucTotalSendCount += pstDhcpServer->ucRetransmitNum;
        }

        pstDhcpcContext->ucCurrentServer = DHCPC_SECONDARY_SERVER;
    }
    else
    {
        /* 如果切换后服务器不是NORMAL,只尝试发送一次 */
        if (DHCP_SEVER_NORMAL != pstDhcpServerStatus->ucPrimarySrvStatus)
        {
            pstDhcpcContext->ucTotalSendCount += pstDhcpServer->ucRetransmitNum;
        }

        pstDhcpcContext->ucCurrentServer = DHCPC_PRIMARY_SERVER;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : DHCPC_SingleFirstSend
 功能描述  : 单个服务器,第一次发送消息处理
 输入参数  : DHCPC_CTRLBLK *pstDhcpcContext
             LAP_DHCP_CFG_S *pstDhcpServer
             DHCP_SERVER_STATUS_S *pstDhcpServerStatus
 输出参数  : 无
 返 回 值  : ULONG
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月25日
    作    者   : jixiaoming 00180244
    修改内容   : 新生成函数

*****************************************************************************/
ULONG DHCPC_SingleFirstSend(DHCPC_CTRLBLK *pstDhcpcContext, LAP_DHCP_CFG_S *pstDhcpServer,
                                DHCP_SERVER_STATUS_S *pstDhcpServerStatus)
{
    if (DHCP_SEVER_NORMAL != pstDhcpServerStatus->ucPrimarySrvStatus)
    {
        /* 不是NORMAL态, 将发送次数设置为重发最大次数. */
        pstDhcpcContext->ucCurSvrSendCount = pstDhcpServer->ucRetransmitNum;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : DHCPC_DoubleFirstSend_MainNormal
 功能描述  : 主备服务器,第一次发送消息,主状态为Normal的处理
 输入参数  : DHCPC_CTRLBLK *pstDhcpcContext
             LAP_DHCP_CFG_S *pstDhcpServer
             DHCP_SERVER_STATUS_S *pstDhcpServerStatus
 输出参数  : 无
 返 回 值  : ULONG
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月25日
    作    者   : jixiaoming 00180244
    修改内容   : 新生成函数

*****************************************************************************/
ULONG DHCPC_DoubleFirstSend_MainNormal(DHCPC_CTRLBLK *pstDhcpcContext, LAP_DHCP_CFG_S *pstDhcpServer,
                                DHCP_SERVER_STATUS_S *pstDhcpServerStatus)
{
    if (DHCP_SEVER_TRY == pstDhcpServerStatus->ucSecondarySrvStatus)
    {
        /* 优先选Try,并且只发送一次 */
        pstDhcpcContext->ucCurSvrSendCount = pstDhcpServer->ucRetransmitNum;
        pstDhcpcContext->ucTotalSendCount = pstDhcpServer->ucRetransmitNum;
        pstDhcpcContext->ucCurrentServer = DHCPC_SECONDARY_SERVER;
    }
    else
    {
        pstDhcpcContext->ucCurrentServer = DHCPC_PRIMARY_SERVER;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : DHCPC_DoubleFirstSend_MainAbnormal
 功能描述  : 主备服务器,第一次发送消息,主服务器状态为Abnormal的处理
 输入参数  : DHCPC_CTRLBLK *pstDhcpcContext
             LAP_DHCP_CFG_S *pstDhcpServer
             DHCP_SERVER_STATUS_S *pstDhcpServerStatus
 输出参数  : 无
 返 回 值  : ULONG
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月25日
    作    者   : jixiaoming 00180244
    修改内容   : 新生成函数

*****************************************************************************/
ULONG DHCPC_DoubleFirstSend_MainAbnormal(DHCPC_CTRLBLK *pstDhcpcContext, LAP_DHCP_CFG_S *pstDhcpServer,
                                DHCP_SERVER_STATUS_S *pstDhcpServerStatus)
{
    switch(pstDhcpServerStatus->ucSecondarySrvStatus)
    {
        case DHCP_SEVER_NORMAL:
            pstDhcpcContext->ucCurrentServer = DHCPC_SECONDARY_SERVER;
            break;

        case DHCP_SEVER_ABNORMAL:
            /* 主备都为Abnormal,优先选主.向备只发送一次 */
            pstDhcpcContext->ucCurrentServer = DHCPC_PRIMARY_SERVER;
            pstDhcpcContext->ucCurSvrSendCount = pstDhcpServer->ucRetransmitNum;
            pstDhcpcContext->ucTotalSendCount = pstDhcpServer->ucRetransmitNum;
            break;

        case DHCP_SEVER_TRY:
            /* 主Abnormal备Try,优先选备.向备只发送一次 */
            pstDhcpcContext->ucCurrentServer = DHCPC_SECONDARY_SERVER;
            pstDhcpcContext->ucCurSvrSendCount = pstDhcpServer->ucRetransmitNum;
            pstDhcpcContext->ucTotalSendCount = pstDhcpServer->ucRetransmitNum;
            break;

        default:
            VOS_Assert(0);
            return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : DHCPC_DoubleFirstSend_MainTry
 功能描述  : 主备服务器,主服务器状态为Try的处理
 输入参数  : DHCPC_CTRLBLK *pstDhcpcContext
             LAP_DHCP_CFG_S *pstDhcpServer
             DHCP_SERVER_STATUS_S *pstDhcpServerStatus
 输出参数  : 无
 返 回 值  : ULONG
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月25日
    作    者   : jixiaoming 00180244
    修改内容   : 新生成函数

*****************************************************************************/
ULONG DHCPC_DoubleFirstSend_MainTry(DHCPC_CTRLBLK *pstDhcpcContext, LAP_DHCP_CFG_S *pstDhcpServer,
                                DHCP_SERVER_STATUS_S *pstDhcpServerStatus)
{
    /* 优先选Try,并且只发送一次 */
    pstDhcpcContext->ucCurSvrSendCount = pstDhcpServer->ucRetransmitNum;
    pstDhcpcContext->ucTotalSendCount = pstDhcpServer->ucRetransmitNum;
    pstDhcpcContext->ucCurrentServer = DHCPC_PRIMARY_SERVER;
    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : DHCPC_DoubleFirstSend
 功能描述  : 主备服务期,第一次发送消息服务器选择处理
 输入参数  : DHCPC_CTRLBLK *pstDhcpcContext
             LAP_DHCP_CFG_S *pstDhcpServer
             DHCP_SERVER_STATUS_S *pstDhcpServerStatus
 输出参数  : 无
 返 回 值  : ULONG
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月25日
    作    者   : jixiaoming 00180244
    修改内容   : 新生成函数

*****************************************************************************/
ULONG DHCPC_DoubleFirstSend(DHCPC_CTRLBLK *pstDhcpcContext, LAP_DHCP_CFG_S *pstDhcpServer,
                                DHCP_SERVER_STATUS_S *pstDhcpServerStatus)
{
    ULONG ulReturn = VOS_ERR;

    switch(pstDhcpServerStatus->ucPrimarySrvStatus)
    {
        case DHCP_SEVER_NORMAL:
            ulReturn = DHCPC_DoubleFirstSend_MainNormal(pstDhcpcContext, pstDhcpServer, pstDhcpServerStatus);
            break;

        case DHCP_SEVER_ABNORMAL:
            ulReturn = DHCPC_DoubleFirstSend_MainAbnormal(pstDhcpcContext, pstDhcpServer, pstDhcpServerStatus);
            break;

        case DHCP_SEVER_TRY:
            ulReturn = DHCPC_DoubleFirstSend_MainTry(pstDhcpcContext, pstDhcpServer, pstDhcpServerStatus);
            break;

        default:
            VOS_Assert(0);
            return VOS_ERR;
    }

    return ulReturn;
}

/*****************************************************************************
 函 数 名  : DHCPC_NotFirstSend
 功能描述  : 非第一次发送消息处理
 输入参数  : DHCPC_CTRLBLK *pstDhcpcContext
             LAP_DHCP_CFG_S *pstDhcpServer
             DHCP_SERVER_STATUS_S *pstDhcpServerStatus
 输出参数  : 无
 返 回 值  : ULONG
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月25日
    作    者   : jixiaoming 00180244
    修改内容   : 新生成函数

*****************************************************************************/
ULONG DHCPC_NotFirstSend(DHCPC_CTRLBLK *pstDhcpcContext, LAP_DHCP_CFG_S *pstDhcpServer,
                                DHCP_SERVER_STATUS_S *pstDhcpServerStatus)
{
    /* 考虑到重发过程中,Server status的状态可能被其他用户修改,
     * 此处进行判断,如果不是Normal,则再发送一次.
     */
    if (DHCPC_PRIMARY_SERVER == pstDhcpcContext->ucCurrentServer)
    {
        if (DHCP_SEVER_NORMAL != pstDhcpServerStatus->ucPrimarySrvStatus)
        {
            pstDhcpcContext->ucCurSvrSendCount = pstDhcpServer->ucRetransmitNum;
            pstDhcpcContext->ucTotalSendCount = pstDhcpServer->ucRetransmitNum;
        }
    }
    else
    {
        if (DHCP_SEVER_NORMAL != pstDhcpServerStatus->ucSecondarySrvStatus)
        {
            pstDhcpcContext->ucCurSvrSendCount = pstDhcpServer->ucRetransmitNum;
            pstDhcpcContext->ucTotalSendCount = pstDhcpServer->ucRetransmitNum;
        }
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : DHCPC_GetServerIp
 功能描述  : 从dhcp服务器的配置中获取Server地址
 输入参数  : LAP_DHCP_CFG_S *pstDhcpServer
             UCHAR ucCurrentSrv
             ULONG aulServerIp[LAP_IP_ULONG_NUM]
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月25日
    作    者   : jixiaoming 00180244
    修改内容   : 新生成函数

*****************************************************************************/
VOID DHCPC_GetServerIp(LAP_DHCP_CFG_S *pstDhcpServer, UCHAR ucCurrentSrv, ULONG aulServerIp[LAP_IP_ULONG_NUM])
{
    if (DHCPC_PRIMARY_SERVER == ucCurrentSrv)
    {
        VOS_MemCpy(aulServerIp, pstDhcpServer->aulPrimaryServerIp, (sizeof(ULONG) * LAP_IP_ULONG_NUM));
    }
    else
    {
        VOS_MemCpy(aulServerIp, pstDhcpServer->aulSecondaryServerIp, (sizeof(ULONG) * LAP_IP_ULONG_NUM));
    }

    return;
}

/*****************************************************************************
 函 数 名  : DHCPC_SelectAndGetServerCfg
 功能描述  : 选择要发送的dhcp服务器,并获取地址配置
 输入参数  : DHCPC_CTRLBLK *pstDhcpcContext
             ULONG aulServerIp[LAP_IP_ULONG_NUM]
 输出参数  : 无
 返 回 值  : ULONG
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月25日
    作    者   : jixiaoming 00180244
    修改内容   : 新生成函数

*****************************************************************************/
ULONG DHCPC_SelectAndGetServerCfg(DHCPC_CTRLBLK *pstDhcpcContext, ULONG aulServerIp[LAP_IP_ULONG_NUM])
{
    ULONG   ulRet = VOS_ERR;
    UCHAR   ucIsSingleServer = VOS_TRUE;
    ULONG   ulSrvrGrpIdx = 0;
    ULONG   ulSingleSendLimit = 0;
    ULONG   ulTotalSendLimit = 0;
    DHCP_SERVER_STATUS_S stDhcpServerStatus = {0};
    LAP_DHCP_CFG_S stDhcpServer = {0};

    if (NULL == pstDhcpcContext)
    {
        VOS_Assert(0);
        return VOS_ERR;
    }

    ulSrvrGrpIdx = pstDhcpcContext->usServerGrpIndex;
    if ( ulSrvrGrpIdx >= DHCPGRP_MAX_NUM )
    {
        DHCPC_DebugPrint(PTM_LOG_ERR, "\r\n ulSrvrGrpIdx Err DHCP ulSrvrGrpIdx is invalid!" );
        return VOS_ERR;
    }

    /*根据 dhcp server index 或取 server group 信息*/
    ulRet = DHCPM_GetDhcpSrvCfgStatusByIndex(ulSrvrGrpIdx, &stDhcpServer, &stDhcpServerStatus);
    if ( VOS_OK != ulRet )
    {
        DHCPC_DebugPrint(PTM_LOG_ERR, "\r\n stDhcpServerStatus Err DHCP stDhcpServerStatus!" );
        return VOS_ERR;
    }

    ulSingleSendLimit = stDhcpServer.ucRetransmitNum + 1;   /* 加上第一次发送消息(非重发) */
    ulTotalSendLimit = ulSingleSendLimit << 1;  /* 主备服务器时,最大发送次数应该是2倍 */

    /* 判断是否单服务器还是主备服务器. 当前的配置约束中单服务器只能配主,
     * 所以通过以下条件既可判断.
     */
    if (DHCP_SEVER_INVALID_IP != stDhcpServer.aulSecondaryServerIp[0])
    {
        ucIsSingleServer = VOS_FALSE;
    }

    if (pstDhcpcContext->ucTotalSendCount >= ulTotalSendLimit)
    {
        ulRet = DHCPC_ReachTotalLimit(pstDhcpcContext);
    }
    else if (pstDhcpcContext->ucCurSvrSendCount >= ulSingleSendLimit)
    {
        ulRet = DHCPC_ReachSingleLimit(pstDhcpcContext, &stDhcpServer, &stDhcpServerStatus);
    }
    /* 第一次发送 */
    else if (0 == pstDhcpcContext->ucTotalSendCount)
    {
        if (VOS_TRUE == ucIsSingleServer)
        {
            ulRet = DHCPC_SingleFirstSend(pstDhcpcContext, &stDhcpServer, &stDhcpServerStatus);
        }
        else
        {
            ulRet = DHCPC_DoubleFirstSend(pstDhcpcContext, &stDhcpServer, &stDhcpServerStatus);
        }
    }
    else
    {
        /* 重发总数没有达到最大次数，单服务器重发也没达到限定值. */
        ulRet = DHCPC_NotFirstSend(pstDhcpcContext, &stDhcpServer, &stDhcpServerStatus);
    }

    if (VOS_OK != ulRet)
    {
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_SERVER_NO_RSP);

        /* 设置原因码 */
        pstDhcpcContext->ucCause = DHCPV6C_CAUSE_SERVER_NOT_RSP;

        /* 清空记录的消息发送次数 */
        pstDhcpcContext->ucCurSvrSendCount = 0;
        pstDhcpcContext->ucTotalSendCount = 0;
    }
    else
    {
        DHCPC_GetServerIp(&stDhcpServer, pstDhcpcContext->ucCurrentServer, aulServerIp);
    }

    return ulRet;
}

