/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : dhcpv6_proc.c
  版 本 号   : 初稿
  作    者   : zhoujunping
  生成日期   : 2008年12月12日
  最近修改   :
  功能描述   : DHCPV6
  函数列表   :
  修改历史   :
  1.日    期   : 2008年12月12日
    作    者   : zhoujunping
    修改内容   : 生成

******************************************************************************/
#include "dhcp_inc.h"
#include "dhcpc_def.h"
#include "dhcpv6_proc.h"
#include "dhcpv6s_comp.h"
#include "dhcpv6s_dbg.h"

/*****************************************************************************
     协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID          PS_FILE_ID_DHCPV6S_COMP_C
/*lint +e767*/

PTM_COMPONENT_INFO_S g_stDhcpv6sComInfo = { 0 };

/*用于统计PGW接收的UE始发的DHCPV6 Inform Request消息包数*/
VOS_SIZE_T g_UEtoPGW_ulDHCPV6InformRequestNumAddr =  VOS_NULL_PTR ;

/*用于统计PGW发送给UE的DHCPV6 Ack消息包数*/
VOS_SIZE_T g_PGWtoUE_ulDHCPV6AckNumAddr =  VOS_NULL_PTR ;

/*用于统计SGW接收的UE始发的DHCPV6 Inform Request消息包数*/
VOS_SIZE_T g_UEtoSGW_ulDHCPV6InformRequestNumAddr =  VOS_NULL_PTR ;

/*用于统计SGW发送给UE的DHCPV6 Ack消息包数*/
VOS_SIZE_T g_SGWtoUE_ulDHCPV6AckNumAddr =  VOS_NULL_PTR ;

ULONG ulDhcpv6sPerfInitFinish = VOS_FALSE;

#define __DHCPV6S_COMP_INIT__

ULONG DHCPV6S_OmInitial()
{
    if ((g_UEtoPGW_ulDHCPV6InformRequestNumAddr = PerfGetFamPerfCounterAddress(
         PERF_TYPE_PGW_S5,
         PERF_TYPE_PGW_RCV_DHCPV6_INFO_REQ_FROM_UE_PKTS,
         VOS_NULL_PTR))
        == VOS_NULL_PTR)
    {
        /* 写日志 */
        DHCPV6S_DebugPrint(PTM_LOG_INFO, "IPV6_OmInitial GetAddress of  PERF_TYPE_PGW_RCV_DHCPV6_INFO_REQ_FROM_UE_PKTS fail!");
        return VOS_ERR;
    }

    if ((g_PGWtoUE_ulDHCPV6AckNumAddr = PerfGetFamPerfCounterAddress(
         PERF_TYPE_PGW_S5,
         PERF_TYPE_PGW_SEND_DHCPV6_ACK_TO_UE_PKTS,
         VOS_NULL_PTR))
        == VOS_NULL_PTR)
    {
        /* 写日志 */
        DHCPV6S_DebugPrint(PTM_LOG_INFO, "IPV6_OmInitial GetAddress of  PERF_TYPE_PGW_SEND_DHCPV6_ACK_TO_UE_PKTS fail!");
        return VOS_ERR;
    }

    /*性能统计 for sgw*/
    if ((g_UEtoSGW_ulDHCPV6InformRequestNumAddr = PerfGetFamPerfCounterAddress(
             PERF_TYPE_SGW_SM,
             PERF_TYPE_SGW_SM_RCV_DHCPV6_INFO_REQ_FROM_UE_PKTS,
             VOS_NULL_PTR))
        == VOS_NULL_PTR)
    {
        /* 写日志 */
        DHCPV6S_DebugPrint(PTM_LOG_INFO, "IPV6_OmInitial GetAddress of  PERF_TYPE_SGW_SM_RCV_DHCPV6_INFO_REQ_FROM_UE_PKTS fail!");
        return VOS_ERR;
    }

    if ((g_SGWtoUE_ulDHCPV6AckNumAddr = PerfGetFamPerfCounterAddress(
             PERF_TYPE_SGW_SM,
             PERF_TYPE_SGW_SM_SEND_DHCPV6_ACK_TO_UE_PKTS,
             VOS_NULL_PTR))
        == VOS_NULL_PTR)
    {
        /* 写日志 */
        DHCPV6S_DebugPrint(PTM_LOG_INFO, "IPV6_OmInitial GetAddress of  PERF_TYPE_SGW_SM_SEND_DHCPV6_ACK_TO_UE_PKTS fail!");
        return VOS_ERR;
    }

    ulDhcpv6sPerfInitFinish = VOS_TRUE;

    return VOS_OK;
}

/*****************************************************************************
 *  函数名称:       DHCPV6S_LocalMemInit
 *  初稿完成:       2012-08-02
 *  作    者:       y00170683
 *  函数功能:       DHCPV6S本地内存初始化
 *  输入参数:
 *  输出参数:       无
 *  返回类型:       ULONG
 *  其他说明:       无
 *  调用函数:
 *  主调函数:
*****************************************************************************/
ULONG DHCPV6S_LocalMemInit()
{
    /* 申请收消息缓存 */
    g_pucDhcpv6sRevBuff = (UCHAR*)DHCP_Malloc(DHCPV6S_HANDLE, sizeof(UCHAR) * DHCPV6S_REV_MSG_MAXLEN);
    if (NULL == g_pucDhcpv6sRevBuff)
    {
        return VOS_ERR;
    }
    DHCP_MemZero(g_pucDhcpv6sRevBuff, sizeof(UCHAR) * DHCPV6S_REV_MSG_MAXLEN);


    /* 申请发消息缓存 */
    g_pucDhcpv6sSendBuff = (UCHAR*)DHCP_Malloc(DHCPV6S_HANDLE, sizeof(UCHAR) * DHCPV6S_SEND_MSG_MAXLEN);
    if (NULL == g_pucDhcpv6sSendBuff)
    {
        return VOS_ERR;
    }
    DHCP_MemZero(g_pucDhcpv6sSendBuff, sizeof(UCHAR) * DHCPV6S_SEND_MSG_MAXLEN);

    return VOS_OK;
}

#ifdef __LINUX_PLATFORM__

/*****************************************************************************
 函 数 名  : DHCPV6S_GetSelfCompInfo
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
ULONG DHCPV6S_GetSelfCompInfo(DMS_COMMID_T myCSI )
{
    g_stDhcpv6sComInfo.ullSelfCsi = PSM_Inf_GetSelfCSI(E_COMP_TYPE_DSV6);
    g_stDhcpv6sComInfo.ullSelfSgId = PSM_Inf_GetSelfSGID();
    g_stDhcpv6sComInfo.ulHandle = PGP_CompGetDopraHandle();

    g_stDhcpv6sComInfo.ulSelfCmpIdx = PSM_Inf_GetCmpIndexInOSByCSI(g_stDhcpv6sComInfo.ullSelfCsi);
    g_stDhcpv6sComInfo.ulSelfCmpIdxInSG = PSM_Inf_GetCmpSameTIndexInSGByCSI(g_stDhcpv6sComInfo.ullSelfCsi);

    return VOS_OK;
}


VOID DHCPV6S_ScheduleInit( DMS_COMMID_T ullCpi )
{
    ULONG i = 0;
    ULONG ulReturn = VOS_OK;
    COMP_MSGSTM_ATTR_S astMsgQueAttr[DHCPV6S_MSG_TYPE_BULT] = {0};
    ULONG aulScheduleTlb[DHCPV6S_MSG_TYPE_BULT] = { 0 };
    ULONG ulNum = 0;

    /* 初始化每个队列的流控深度 */
    aulScheduleTlb[DHCPV6S_MSG_TYPE_PF]        = DHCPV6_FLOWCONTROL_MAX;

    for (i = M_PS_MSG_TYPE_BASE; i < DHCPV6S_MSG_TYPE_BULT; i++)
    {
        if ( 0 == aulScheduleTlb[i] )
        {
            continue;
        }

        astMsgQueAttr[ulNum].uiMsgNum = aulScheduleTlb[i];
        astMsgQueAttr[ulNum].uiStreamId = i;
        astMsgQueAttr[ulNum].uiFcmQue = 0;
        astMsgQueAttr[ulNum].uiMaxAppMsgNum = DHCPV6S_DEFAULT_MAX_APP_MSG_NUM;
        ulNum++;
    }

    ulReturn = (ULONG)PGP_ScmCompMsgStmAttribSet(ullCpi, ulNum, astMsgQueAttr);
    if (VOS_OK != ulReturn)
    {
        DHCPV6S_DebugPrint(PTM_LOG_ERR, "\r\n PGP_ScmCompMsgStmAttribSet fail, Ret = %u", ulReturn);
    }

    return;
}

#endif

/*****************************************************************************
 函 数 名  : DHCPV6S_CommInit1
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
ULONG DHCPV6S_CommInit1(  )
{
    ULONG ulRet = VOS_OK;

    DBG_LogRecordReg(M_PTM_SYSTEM_NAME, "DHCP", "DSV6", &g_ulDhcpv6sLogRecordRegId);

    DHCPV6S_InitCounter();

    DHCPV6S_DebugCmdInit(DHCPV6S_SELF_CSI);

    /* 创建私有内存 */
    ulRet = DHCPV6S_LocalMemInit();
    if (VOS_OK != ulRet)
    {
        DHCPV6S_DebugPrint(PTM_LOG_ERR, "DHCPS_LocalMemInit fail");
        return ulRet;
    }

    PTM_Dbg_RegMemoryPrint(DHCPV6S_SELF_CSI);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : DHCPV6S_CommInit2
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
ULONG DHCPV6S_CommInit2(  )
{
    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : DHCPV6S_CommInit3
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
ULONG DHCPV6S_CommInit3( )
{
    ULONG ulReturn = 0;

    ulReturn = DHCPV6S_OmInitial();
    if ( VOS_OK != ulReturn )
    {
        DHCPV6S_DebugPrint(PTM_LOG_ERR, "DHCPV6S_OmInitial fail, ulReturn = %x", ulReturn);
    }

    return VOS_OK;
}

#define __DHCPV6S_COMP_MSG_PROC___________


VOID DHCPV6S_ProcPfMsg(VOID* pMsg)
{
    PMBUF_S *pstMBuf = NULL;

    if ( NULL == pMsg )
    {
        VOS_Assert(0);
        return;
    }

    pstMBuf = (PMBUF_S *)pMsg;

    /* 收到消息计数*/
    DHCPV6S_DBGCNT_ADD(E_DHCPV6S_REV_MS_MSG);

    /* 消息处理 */
    if (VOS_OK != DHCPV6_MsgProc(pstMBuf))
    {
        DHCPV6S_DBGCNT_ADD(E_DHCPV6S_PROC_ERR);
    }

    return;
}

#ifdef __LINUX_PLATFORM__

/*****************************************************************************
 函 数 名  : DHCPV6S_CompMsgDistribute
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
ULONG DHCPV6S_CompMsgDistribute(ULONG ulMsgType, VOID* pMsg )
{
    if ( NULL == pMsg )
    {
        return VOS_ERR;
    }

    switch(ulMsgType)
    {
        case DHCPV6S_MSG_TYPE_PF:
        {
            DHCPV6S_ProcPfMsg(pMsg);

            /* MBUF需要组件自己释放 */
            (VOID)PMBUF_Destroy((PMBUF_S *)pMsg);
            break;
        }
        default:
        {
            break;
        }
    }

    return VOS_OK;
}

#define __DHCPV6S_COMP_FRAME____________
/*****************************************************************************
 函 数 名  : DHCPV6S_CompConstruct
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
ULONG DHCPV6S_CompConstruct( RTF_COMP_CONSTRUCT_STAGE_E eConstructStage,
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

            ulRet = DHCPV6S_GetSelfCompInfo(myCSI);
            if (VOS_OK != ulRet)
            {
                return ulRet;
            }

            ulRet = DHCPV6S_CommInit1();

            break;

        case RTF_COMP_CONSTRUCT_STAGE2:
            /* 第二阶段 PGPReady*/
            /* CDB配置、License、软参 */
            /* RDB 相关的业务初始化（包括内存，IFA 接口获取，逻辑部署） */
            ulRet = DHCPV6S_CommInit2();
            break;

        case RTF_COMP_CONSTRUCT_STAGE3:
            /* 第三阶段: 组件enable, 向平台回Confirm */
            /* Timer初始化 */
            ulRet = DHCPV6S_CommInit3();
            if (VOS_OK != ulRet)
            {
                return ulRet;
            }

            /* 注册流控初始化函数*/
            DHCPV6S_ScheduleInit(myCPI);
            break;

        default:
            /*错误处理*/
            ulRet = VOS_ERR;
            break;
    }

    vos_printf("DHCPV6S_CompConstruct stage %u, ret %u", eConstructStage, ulRet);

    return ulRet;
}

/*****************************************************************************
 函 数 名  : DHCPV6S_CompDestruct
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
ULONG DHCPV6S_CompDestruct( DMS_COMMID_T myPid, VOID* pThis )
{
    vos_printf("Destruct Component DHCPS\r\n");
    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : DHCPV6S_CompMsgProc
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
ULONG DHCPV6S_CompMsgProc(VOID* pMsg, VOID* pThis)
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
        (VOID)HAF_SendStartWorkRsp(((COMP_LOCAL_COMMON_S*)pThis)->selfDopraCpi, VOS_OK);

         return VOS_OK;
    }

    /* 定时器消息处理*/
    recvIId = DMS_MSG_RECV_IID_GET(pMsg);
    if( VOS_IID_TMR_TIMEOUT == recvIId )
    {
        /* 没有定时器回调 */
        VOS_Assert(0);
        return VOS_OK;
    }

    /* 获取DMSQ消息体 */
    pMsgBody = PGP_CompGetMsgBody(pMsg);

    ulMsgType = DMS_MSG_STREAMID_GET(pMsg);
    if ( ulMsgType < M_PS_MSG_TYPE_BASE ) /*队列是PGP队列*/
    {
        /* 平台消息处理*/
        (VOID)PGP_CompMsgProc(pMsgBody);
    }
    else
    {
        /* 其它队列消息分发处理 */
        ulRet = DHCPV6S_CompMsgDistribute(ulMsgType, pMsgBody);
    }

    /* 平台消息释放处理*/
    PGP_CompMsgRelease();

    return ulRet;
}

#endif


