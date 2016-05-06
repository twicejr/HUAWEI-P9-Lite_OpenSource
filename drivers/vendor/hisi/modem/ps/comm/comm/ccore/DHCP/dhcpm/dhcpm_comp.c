/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : dhcpm_comp.c
  版 本 号   : 初稿
  作    者   : y00138047
  生成日期   : 2012年6月21日
  最近修改   :
  功能描述   : dhcpm F板主文件
  函数列表   :
*
*       1.                DHCPM_ModDhcpServerGroupNode
*       2.                DHCPM_AlarmProcByDhcpServerIndex
*       3.                DHCPM_AlarmTimerProc
*       4.                DHCPM_CommInit1
*       5.                DHCPM_CommInit3
*       6.                DHCPM_CompConstruct
*       7.                DHCPM_CompDestruct
*       8.                DHCPM_CompMsgDistribute
*       9.                DHCPM_CompMsgProc
*       10.                DHCPM_CompTimerMsgProc
*       11.                DHCPM_DhcpServerStatusWriteLock
*       12.                DHCPM_DhcpServerStatusWriteUnlock
*       13.                DHCPM_GetDhcpSrvCfgByIndex
*       14.                DHCPM_GetDhcpSrvCfgStatusByIndex
*       15.                DHCPM_GetDhcpSrvStatusByIndex
*       16.                DHCPM_GetSelfCompInfo
*       17.                DHCPM_InitDhcpServerCfgManager
*       18.                DHCPM_InitDhcpServerStatusManager
*       19.                DHCPM_InitTimer
*       20.                DHCPM_RegDhcpServer
*       21.                DHCPM_RegDhcpServerCfgManager
*       22.                DHCPM_InitDhcpServerStatus
*       23.                DHCPM_RemoveDhcpServerByIndex
*       24.                DHCPM_RenewSoftPara
*       25.                DHCPM_ReportAlarm
*       26.                DHCPM_SetPrimarySrvStatusByIndex
*       27.                DHCPM_SetPrimarySrvTestByIndex
*       28.                DHCPM_SetPrimSrvTimerStatusByIndex
*       29.                DHCPM_SetPrimTimeoutNumByIndex
*       30.                DHCPM_SetSecondarySrvStatusByIndex
*       31.                DHCPM_SetSecondarySrvTestByIndex
*       32.                DHCPM_SetSecTimeoutNumByIndex
*       33.                DHCPM_StartWorkProc
*

  修改历史   :
  1.日    期   : 2012年6月21日
    作    者   : y00138047
    修改内容   : 创建文件

******************************************************************************/

#include "dhcp_inc.h"
#include "dhcpc_def.h"
#include "dhcpc.h"
#include "dhcpc_cdb.h"
#include "dhcpc_func.h"
#include "dhcpc_dbg.h"
#include "dhcpm_interface.h"
#include "dhcpm_comp.h"
#include "dhcpm_dbg.h"

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID          PS_FILE_ID_DHCPM_COMP_C
/*lint +e767*/


PTM_COMPONENT_INFO_S g_stDhcpMCompInfo = { 0 };

DHCP_SERVER_CFG_MANAGER_S g_stDhcpServerCfgManager = {0};

DHCP_SERVER_STATUS_S *g_pstDhcpServerStatus = NULL;

ULONG g_ulDHCPTimeOutNum = 0;

RELTMR_T g_ulDhcpmAlarmTimerID = 0;

UCHAR g_ucDhcpMSoftParaByte133 = 0;
UCHAR g_ucDhcpMSoftParaByte134 = 0;

ULONG g_ulDhcpMInitStep = 0;

LAP_DHCP_CFG_S g_stDhcpServer[DHCP_SERVER_GROUP_MAX_NUM] = {0};
DHCP_SERVER_STATUS_S g_pstDhcpServerStatusMem[DHCP_SERVER_GROUP_MAX_NUM] = {0};

ULONG DHCPM_DhcpServerCfgReadLock()
{
    ULONG ulReturn = 0;

    ulReturn = PGP_RWReadLockNoSchedule(&g_stDhcpServerCfgManager.RWLockId);
    if ( VOS_OK != ulReturn )
    {
        VOS_Assert(0);
        DHCPM_ADD_COUNTER(201);
        return ulReturn;
    }

    return VOS_OK;
}

ULONG DHCPM_DhcpServerCfgReadUnLock()
{
    ULONG ulReturn = 0;

    ulReturn = PGP_RWReadUnlockNoSchedule(&g_stDhcpServerCfgManager.RWLockId);
    if ( VOS_OK != ulReturn )
    {
        VOS_Assert(0);
        DHCPM_ADD_COUNTER(202);
        return ulReturn;
    }

    return VOS_OK;
}

ULONG DHCPM_DhcpServerCfgWriteLock()
{
    ULONG ulReturn = 0;

    ulReturn = PGP_RWWriteLockNoSchedule(&g_stDhcpServerCfgManager.RWLockId);
    if ( VOS_OK != ulReturn )
    {
        VOS_Assert(0);
        DHCPM_ADD_COUNTER(290);
        return ulReturn;
    }

    return VOS_OK;
}

ULONG DHCPM_DhcpServerCfgWriteUnLock()
{
    ULONG ulReturn = 0;

    ulReturn = PGP_RWWriteUnlockNoSchedule(&g_stDhcpServerCfgManager.RWLockId);
    if ( VOS_OK != ulReturn )
    {
        VOS_Assert(0);
        DHCPM_ADD_COUNTER(291);
        return ulReturn;
    }

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : DHCPM_GetDhcpSrvCfgByIndex
 功能描述  : dhcpm根据dhcp server index获取配置
 输入参数  : ULONG ulDhcpIndex
             LAP_DHCP_CFG_S *pstDhcpServer
 输出参数  : 无
 返 回 值  : ULONG
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月20日
    作    者   : y00138047
    修改内容   : 新生成函数

*****************************************************************************/
ULONG DHCPM_GetDhcpSrvCfgByIndex(ULONG ulDhcpIndex, LAP_DHCP_CFG_S *pstDhcpServer)
{
    ULONG ulFindFlag = VOS_FALSE;
    ULONG ulReturn = 0;

    if ( DHCPGRP_MAX_NUM <= ulDhcpIndex || NULL == pstDhcpServer )
    {
        VOS_Assert(0);
        DHCPM_ADD_COUNTER(203);
        return VOS_ERR;
    }

    ulReturn = DHCPM_DhcpServerCfgReadLock();
    if ( VOS_OK != ulReturn )
    {
        return ulReturn;
    }

    g_stDhcpServerCfgManager.pstDhcpServer[ulDhcpIndex].aulPrimaryServerIp[0] = 255;
    g_stDhcpServerCfgManager.pstDhcpServer[ulDhcpIndex].aulPrimaryServerIp[1] = 255;
    g_stDhcpServerCfgManager.pstDhcpServer[ulDhcpIndex].aulPrimaryServerIp[2] = 255;
    g_stDhcpServerCfgManager.pstDhcpServer[ulDhcpIndex].aulPrimaryServerIp[3] = 255;

    if ( LAP_DHCP_SERVER_INVALID_IP
        != g_stDhcpServerCfgManager.pstDhcpServer[ulDhcpIndex].aulPrimaryServerIp[0] )
    {
        ulFindFlag = VOS_TRUE;
        VOS_MemCpy(pstDhcpServer, &g_stDhcpServerCfgManager.pstDhcpServer[ulDhcpIndex], sizeof(LAP_DHCP_CFG_S));
    }

    ulReturn = DHCPM_DhcpServerCfgReadUnLock();
    if ( VOS_OK != ulReturn )
    {
        return ulReturn;
    }

    if ( VOS_TRUE == ulFindFlag )
    {
        return VOS_OK;
    }

    DHCPM_ADD_COUNTER(204);
    return VOS_ERR;
}

ULONG DHCPM_GetDhcpSrvStatusByIndex(ULONG ulDhcpIndex, DHCP_SERVER_STATUS_S *pstDhcpServerStatus)
{
    if ( DHCPGRP_MAX_NUM <= ulDhcpIndex || NULL == pstDhcpServerStatus )
    {
        DHCPM_ADD_COUNTER(205);
        return VOS_ERR;
    }

    if ( LAP_DHCP_SERVER_INVALID_IP
        == g_stDhcpServerCfgManager.pstDhcpServer[ulDhcpIndex].aulPrimaryServerIp[0] )
    {
        DHCPM_ADD_COUNTER(206);
        return VOS_ERR;
    }

    DHCPM_SPINLOCK(&g_pstDhcpServerStatus[ulDhcpIndex].stSpinLockId);

    VOS_MemCpy(pstDhcpServerStatus, &g_pstDhcpServerStatus[ulDhcpIndex], sizeof(DHCP_SERVER_STATUS_S));

    DHCPM_SPINUNLOCK(&g_pstDhcpServerStatus[ulDhcpIndex].stSpinLockId);

    return VOS_OK;
}

ULONG DHCPM_GetDhcpSrvCfgStatusByIndex(ULONG ulDhcpIndex, LAP_DHCP_CFG_S *pstDhcpServer,
                                       DHCP_SERVER_STATUS_S *pstDhcpServerStatus)
{
    ULONG ulReturn = 0;

    ulReturn = DHCPM_GetDhcpSrvCfgByIndex(ulDhcpIndex, pstDhcpServer);
    if ( VOS_OK != ulReturn )
    {
        DHCPM_ADD_COUNTER(209);
        return ulReturn;
    }

    ulReturn = DHCPM_GetDhcpSrvStatusByIndex(ulDhcpIndex, pstDhcpServerStatus);
    if ( VOS_OK != ulReturn )
    {
        DHCPM_ADD_COUNTER(210);
        return ulReturn;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : DHCPM_GetDhcpSrvVpnByIndex
 功能描述  : 获取与dhcp server绑定的vpn的索引
 输入参数  : ULONG ulDhcpIndex
             ULONG *pusVpnIndex
 输出参数  : 无
 返 回 值  : ULONG
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月25日
    作    者   : jixiaoming 00180244
    修改内容   : 新生成函数

*****************************************************************************/
ULONG DHCPM_GetDhcpSrvVpnByIndex(ULONG ulDhcpIndex, ULONG *pulVpnIndex)
{
    ULONG ulReturn = VOS_ERR;

    if ((ulDhcpIndex >= DHCPGRP_MAX_NUM) || (NULL == pulVpnIndex))
    {
        VOS_Assert(0);
        return VOS_ERR;
    }

    ulReturn = DHCPM_DhcpServerCfgReadLock();
    if ( VOS_OK != ulReturn )
    {
        return ulReturn;
    }

    *pulVpnIndex = g_stDhcpServerCfgManager.pstDhcpServer[ulDhcpIndex].ulVpnIndex;

    ulReturn = DHCPM_DhcpServerCfgReadUnLock();
    if ( VOS_OK != ulReturn )
    {
        return ulReturn;
    }

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : DHCPM_GetRetransmitCfgByIndex
 功能描述  : 获取重发超时时间
 输入参数  : ULONG ulDhcpIndex
             UCHAR *pucRetransmitNum
             UCHAR *pucRetransmitTimeOut
 输出参数  : 无
 返 回 值  : ULONG
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年7月17日
    作    者   : jixiaoming 00180244
    修改内容   : 新生成函数

*****************************************************************************/
inline ULONG DHCPM_GetRetransmitTimeOutByIndex(ULONG ulDhcpIndex, UCHAR *pucRetransmitTimeOut)
{
    ULONG ulReturn = VOS_ERR;

    if ((DHCPGRP_MAX_NUM <= ulDhcpIndex) || (NULL == pucRetransmitTimeOut))
    {
        VOS_Assert(0);
        return VOS_ERR;
    }

    ulReturn = DHCPM_DhcpServerCfgReadLock();
    if ( VOS_OK != ulReturn )
    {
        return ulReturn;
    }

    /* 协议中没有规定超时时间间隔，到时候需要和CDS对齐,暂设定1000来debug基本流程 */
    *pucRetransmitTimeOut = 10000;

    ulReturn = DHCPM_DhcpServerCfgReadUnLock();
    if ( VOS_OK != ulReturn )
    {
        return ulReturn;
    }

    return VOS_OK;
}

ULONG DHCPM_ReportAlarm(UCHAR *pucVpnName ,ULONG aulSrvIpAddr[4], UCHAR ucAlarmType, UCHAR ucIsDHCPv6)
{
    ULONG ulCpuID = 0;
    UCHAR ucSlotNo = 0;
    UCHAR ucParaNum = 4;
    UCHAR aucValueLen[4] = {0};
    VOID *pVarValue[4] = {0};
    UCHAR szVrfName[DHCP_VPN_INSTANCE_NAME_MAX_LENGTH] = {0};
    ULONG ulAlmRet = VOS_OK;
    UCHAR aucIPv6Addr[17] = {0};
    ULONG *pulIpAddr = (ULONG *)&(aucIPv6Addr[1]);

    DHCPM_ADD_COUNTER(1);
    DHCPM_DebugPrint(PTM_LOG_DEBUG, "entry");

    /*入参检查*/
    if (NULL ==  pucVpnName)
    {
        VOS_Assert(0);
        return VOS_ERR;
    }

    aucValueLen[0] = 1;
    aucValueLen[1] = 4;
    aucValueLen[2] = DHCP_VPN_INSTANCE_NAME_MAX_LENGTH;
    aucValueLen[3] = 17;

    /*填写告警恢复信息*/
    ucSlotNo = (UCHAR)DVM_SELF_SLOTID;
    /*lint -e666*/
    ulCpuID = VOS_HTONL(DVM_SELF_CPUID);
    /*lint +e666*/
    if( DHCP_SEVER_GROUP_IS_IPV4 == ucIsDHCPv6 )
    {
        aucIPv6Addr[0]  = DHCPM_ALARM_IPADDR_IPV4;
        pulIpAddr[0] = aulSrvIpAddr[0];
        pulIpAddr[1] = aulSrvIpAddr[1];
        pulIpAddr[2] = aulSrvIpAddr[2];
        pulIpAddr[3] = aulSrvIpAddr[3];

    }
    else
    {
        aucIPv6Addr[0]  = DHCPM_ALARM_IPADDR_IPV6;
        pulIpAddr[0] = aulSrvIpAddr[0];
        pulIpAddr[1] = aulSrvIpAddr[1];
        pulIpAddr[2] = aulSrvIpAddr[2];
        pulIpAddr[3] = aulSrvIpAddr[3];
    }

    pVarValue[0] = &ucSlotNo;
    pVarValue[1] = &ulCpuID;
    VOS_StrCpy(szVrfName, pucVpnName);
    pVarValue[2] = szVrfName;
    pVarValue[3] = aucIPv6Addr;

    /*  发送告警恢复信息 */
    ulAlmRet = AlarmToFamEx(ucSlotNo,
                         MID_DHCPM,
                         M_ALM_PATHDHCPSERVERDOWN,
                         ucAlarmType,
                         ucParaNum,
                         aucValueLen,
                         pVarValue );

    DHCPM_DebugPrint(PTM_LOG_DEBUG, "Begin to send primary server restore :"
                       "\r\nudwMid = %x, "
                       "\r\nULAlarmID = %u,"
                       "\r\nM_ALM_TYPE_RESTORE = %d ,"
                       "\r\nucParaNum = %d, "
                       "\r\nucSlotNo = %d,"
                       "\r\nIPAddr= %x,"
                       "\r\nulCpuID = %u,"
                       "\r\nszVrfName = %s",
                       MID_DHCPM,
                       M_ALM_PATHDHCPSERVERDOWN,
                       ucAlarmType,
                       ucParaNum,
                       ucSlotNo,
                       aucIPv6Addr[0],
                       ulCpuID,
                       szVrfName);

    if (VOS_OK != ulAlmRet)
    {
        DHCPM_ADD_COUNTER(211);
        DHCPM_DebugPrint(PTM_LOG_DEBUG, "AlarmToFamEx failed. The ip address is ulSrvIpAddr=%x", aucIPv6Addr[0]);
    }

    return VOS_OK;
}

VOID DHCPM_AlarmProcByDhcpServerIndex(ULONG ulDhcpIndex, ULONG ulAlarmDownFlg)
{
    LAP_DHCP_CFG_S stDhcpServer; /* 效率起见，该变量可以不初始化 */
    ULONG ulReturn = 0;
    DHCP_SERVER_STATUS_S stDhcpServerStatus;
    ULONG aulIPAddr[4] = {0};
    ULONG ulPrimaryRestoreFlg = VOS_FALSE;
    ULONG ulSecondaryRestoreFlg = VOS_FALSE;
    ULONG ulPrimaryAlarmFlg = VOS_FALSE;
    ULONG ulSecondaryAlarmFlg = VOS_FALSE;
    DHCP_SERVER_STATUS_S *pstDhcpServerStatus = NULL;

    DHCPM_ADD_COUNTER(2);

    ulReturn = DHCPM_GetDhcpSrvCfgStatusByIndex(ulDhcpIndex, &stDhcpServer, &stDhcpServerStatus);
    if ( VOS_OK != ulReturn )
    {
        DHCPM_ADD_COUNTER(212);
        return;
    }

    do
    {
        if ((DHCP_SEVER_NORMAL == stDhcpServerStatus.ucPrimarySrvStatus) && (DHCP_ALARMED == stDhcpServerStatus.ucPrimaryAlarmFlag))
        {
            ulPrimaryRestoreFlg = VOS_TRUE;
            aulIPAddr[0] = stDhcpServer.aulPrimaryServerIp[0];
            aulIPAddr[1] = stDhcpServer.aulPrimaryServerIp[1];
            aulIPAddr[2] = stDhcpServer.aulPrimaryServerIp[2];
            aulIPAddr[3] = stDhcpServer.aulPrimaryServerIp[3];
            ulReturn = DHCPM_ReportAlarm(stDhcpServer.aucVpnName, aulIPAddr, M_ALM_TYPE_RESTORE,stDhcpServer.ucIsDHCPv6);

            if ( VOS_OK != ulReturn  )
            {
                DHCPM_ADD_COUNTER(214);
            }
        }

        if ((DHCP_SEVER_NORMAL == stDhcpServerStatus.ucSecondarySrvStatus) && (DHCP_ALARMED == stDhcpServerStatus.ucSecondaryAlarmFlag))
        {
            ulSecondaryRestoreFlg = VOS_TRUE;
            aulIPAddr[0] = stDhcpServer.aulSecondaryServerIp[0];
            aulIPAddr[1] = stDhcpServer.aulSecondaryServerIp[1];
            aulIPAddr[2] = stDhcpServer.aulSecondaryServerIp[2];
            aulIPAddr[3] = stDhcpServer.aulSecondaryServerIp[3];
            ulReturn = DHCPM_ReportAlarm(stDhcpServer.aucVpnName, aulIPAddr, M_ALM_TYPE_RESTORE,stDhcpServer.ucIsDHCPv6);
            if ( VOS_OK != ulReturn  )
            {
                DHCPM_ADD_COUNTER(215);
            }
        }

        if ( VOS_TRUE != ulAlarmDownFlg)
        {
            break;
        }

        /* 判断主DHCP 服务器是否需要发送链路断告警 */
        if ((DHCP_SEVER_NORMAL != stDhcpServerStatus.ucPrimarySrvStatus)
            && (DHCP_NO_ALARM == stDhcpServerStatus.ucPrimaryAlarmFlag) /*初始化的时候应该定义为DHCP_NO_ALARM*/
            && (++stDhcpServerStatus.ucPrimTimeoutNum >= g_ucDhcpMSoftParaByte134))
        {
            ulPrimaryAlarmFlg = VOS_TRUE;
            aulIPAddr[0] = stDhcpServer.aulPrimaryServerIp[0];
            aulIPAddr[1] = stDhcpServer.aulPrimaryServerIp[1];
            aulIPAddr[2] = stDhcpServer.aulPrimaryServerIp[2];
            aulIPAddr[3] = stDhcpServer.aulPrimaryServerIp[3];
            ulReturn = DHCPM_ReportAlarm(stDhcpServer.aucVpnName, aulIPAddr, M_ALM_TYPE_FAULT,stDhcpServer.ucIsDHCPv6);
            if ( VOS_OK != ulReturn  )
            {
                DHCPM_ADD_COUNTER(216);
            }

        }

        /* 判断备DHCP 服务器是否需要发送链路断告警 */
        if ((DHCP_SEVER_NORMAL != stDhcpServerStatus.ucSecondarySrvStatus)
            && (DHCP_NO_ALARM == stDhcpServerStatus.ucSecondaryAlarmFlag)
            && (++stDhcpServerStatus.ucSecTimeoutNum >= g_ucDhcpMSoftParaByte134))
        {
            ulSecondaryAlarmFlg = VOS_TRUE;
            aulIPAddr[0] = stDhcpServer.aulSecondaryServerIp[0];
            aulIPAddr[1] = stDhcpServer.aulSecondaryServerIp[1];
            aulIPAddr[2] = stDhcpServer.aulSecondaryServerIp[2];
            aulIPAddr[3] = stDhcpServer.aulSecondaryServerIp[3];
            ulReturn = DHCPM_ReportAlarm(stDhcpServer.aucVpnName, aulIPAddr, M_ALM_TYPE_FAULT,stDhcpServer.ucIsDHCPv6);
            if ( VOS_OK != ulReturn  )
            {
                DHCPM_ADD_COUNTER(217);
            }
        }

    } while ( 0 );

    /* 尽量减少锁区操作 */
    DHCPM_SPINLOCK(&g_pstDhcpServerStatus[ulDhcpIndex].stSpinLockId);

    pstDhcpServerStatus = &(g_pstDhcpServerStatus[ulDhcpIndex]);
    if ( VOS_TRUE == ulPrimaryRestoreFlg )
    {
        pstDhcpServerStatus->ucPrimaryAlarmFlag = DHCP_NO_ALARM;
        pstDhcpServerStatus->ucPrimTimeoutNum = 0;
    }

    if ( VOS_TRUE == ulSecondaryRestoreFlg )
    {
        pstDhcpServerStatus->ucSecondaryAlarmFlag = DHCP_NO_ALARM;
        pstDhcpServerStatus->ucSecTimeoutNum= 0;
    }

    if ( VOS_TRUE == ulAlarmDownFlg )
    {
        if ( VOS_TRUE == ulPrimaryAlarmFlg )
        {
            pstDhcpServerStatus->ucPrimaryAlarmFlag  = DHCP_ALARMED;
            pstDhcpServerStatus->ucPrimTimeoutNum = 0;
        }
        else if (DHCP_SEVER_NORMAL != pstDhcpServerStatus->ucPrimarySrvStatus)
        {
            /* 只有服务器状态不正常时,才将计数器增加 */
            pstDhcpServerStatus->ucPrimTimeoutNum++;
        }

        if ( VOS_TRUE == ulSecondaryAlarmFlg )
        {
            pstDhcpServerStatus->ucSecondaryAlarmFlag= DHCP_ALARMED;
            pstDhcpServerStatus->ucSecTimeoutNum = 0;
        }
        else if (DHCP_SEVER_NORMAL != pstDhcpServerStatus->ucSecondarySrvStatus)
        {
            /* 只有服务器状态不正常时,才将计数器增加 */
            pstDhcpServerStatus->ucSecTimeoutNum++;
        }
    }

    DHCPM_SPINUNLOCK(&g_pstDhcpServerStatus[ulDhcpIndex].stSpinLockId);

    return;
}


/*****************************************************************************
 函 数 名  : DHCPM_RenewSoftPara
 功能描述  : dhcpm更新告警相关软参
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月20日
    作    者   : y00138047
    修改内容   : 新生成函数

*****************************************************************************/
VOID DHCPM_RenewSoftPara()
{
    UCHAR ucSoftParaByte133 = 0;
    UCHAR ucSoftParaByte134 = 0;
    ULONG ulReturn = 0;

    /*设置UGW探测Server状态的时间间隔，UGW以这个时长扫描DHCP 服务器的状态；默认为30秒*/
    ulReturn = SPM_GetByteValue(M_SPM_DHCP_ALARM_INTERVAL, &ucSoftParaByte133 );
    if (VOS_OK != ulReturn)
    {
        DHCPM_ADD_COUNTER(219);
        DHCPM_DebugPrint(PTM_LOG_ERR, "SPM_GetByteValue133 fail, ret = %u", ulReturn);
        ucSoftParaByte133 = DHCPC_PROBE_SERVER_INTERVAL;
    }

    /*取值范围为10~60秒*/
    if ((ucSoftParaByte133 > DHCPC_PROBE_SERVER_INTERVAL_MAX)
        || (ucSoftParaByte133 < DHCPC_PROBE_SERVER_INTERVAL_MIN))
    {
        DHCPM_ADD_COUNTER(220);
        ucSoftParaByte133 = DHCPC_PROBE_SERVER_INTERVAL;
    }

    g_ucDhcpMSoftParaByte133 = ucSoftParaByte133;

    /*设置UGW探测Server状态的次数，UGW以这个次数扫描DHCP 服务器的状态，默认为5次*/
    if (VOS_OK != SPM_GetByteValue(M_SPM_DHCP_ALARM_ACCUMULATE, &ucSoftParaByte134 ))
    {
        DHCPM_DebugPrint(PTM_LOG_ERR, "SPM_GetByteValue134 fail, ret = %u", ulReturn);
        ucSoftParaByte134 = DHCPC_PROBE_SERVER_TIMES;
    }

    /*取值范围为3~10次*/
    if ((ucSoftParaByte134 > DHCPC_PROBE_SERVER_TIMES_MAX)
        || (ucSoftParaByte134 < DHCPC_PROBE_SERVER_TIMES_MIN))
    {
        ucSoftParaByte134 = DHCPC_PROBE_SERVER_TIMES;
    }

    g_ucDhcpMSoftParaByte134 = ucSoftParaByte134;

    return;
}

VOID DHCPM_AlarmTimerProc( )
{
    ULONG i = 0;
    ULONG ulAlarmDownFlg = VOS_FALSE;
    UCHAR ucLogicSlot = 0;

    ucLogicSlot = (UCHAR)CRM_GetSelfLogicSlotID();
    if (E_CRM_ACTIVE != CRM_GetSlotPrimaryInfoOfSelfGroup(ucLogicSlot))
    {
        DHCPM_ADD_COUNTER(221);
        return;
    }

    g_ulDHCPTimeOutNum++;

    DHCPM_RenewSoftPara();

    /* 通过调用DHCPM_RenewSoftPara，g_ucDhcpMSoftParaByte133必然不为0 */
    if ( 0 == (g_ulDHCPTimeOutNum % g_ucDhcpMSoftParaByte133) )
    {
        g_ulDHCPTimeOutNum = 0;
        ulAlarmDownFlg = VOS_TRUE;
    }

    for ( i = 0 ; i < DHCPGRP_MAX_NUM ; i++ )
    {
        DHCPM_AlarmProcByDhcpServerIndex(i, ulAlarmDownFlg);
    }

    return;
}

/*****************************************************************************
 函 数 名  : DHCPM_PrimTryStatusTimeCountDown
 功能描述  : 主服务器Try时间倒计时处理.
 输入参数  : ULONG ulSvrGrpIndex
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月2日
    作    者   : jixiaoming 00180244
    修改内容   : 新生成函数

*****************************************************************************/
VOID DHCPM_PrimTryStatusTimeCountDown(ULONG ulSvrGrpIndex)
{
    LAP_DHCP_CFG_S *pstDhcpServer = g_stDhcpServerCfgManager.pstDhcpServer + ulSvrGrpIndex;
    DHCP_SERVER_STATUS_S * pstDhcpServerStatus = g_pstDhcpServerStatus + ulSvrGrpIndex;

    if (LAP_DHCP_SERVER_INVALID_IP == pstDhcpServer->aulPrimaryServerIp[0])
    {
        /* IP非法,说明未配置 */
        return;
    }

    DHCPM_SPINLOCK(&(pstDhcpServerStatus->stSpinLockId));

    do
    {
        /* 如果不是Abnormal状态,不需要倒计时 */
        if (DHCP_SEVER_ABNORMAL != pstDhcpServerStatus->ucPrimarySrvStatus)
        {
            pstDhcpServerStatus->usPrimTryTimeInterval = 0;
            break;
        }

        if (0 != pstDhcpServerStatus->usPrimTryTimeInterval)
        {
            --(pstDhcpServerStatus->usPrimTryTimeInterval);
            break;
        }

        /* Try的时间倒计时为0,将Server Group状态设置为Try */
        pstDhcpServerStatus->ucPrimarySrvStatus = DHCP_SEVER_TRY;
    }
    while(0);

    DHCPM_SPINUNLOCK(&(pstDhcpServerStatus->stSpinLockId));

    return;
}

/*****************************************************************************
 函 数 名  : DHCPM_SecTryStatusTimeCountDown
 功能描述  : 备服务器Try时间倒计时处理
 输入参数  : ULONG ulSvrGrpIndex
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月2日
    作    者   : jixiaoming 00180244
    修改内容   : 新生成函数

*****************************************************************************/
VOID DHCPM_SecTryStatusTimeCountDown(ULONG ulSvrGrpIndex)
{
    LAP_DHCP_CFG_S *pstDhcpServer = g_stDhcpServerCfgManager.pstDhcpServer + ulSvrGrpIndex;
    DHCP_SERVER_STATUS_S * pstDhcpServerStatus = g_pstDhcpServerStatus + ulSvrGrpIndex;

    if (LAP_DHCP_SERVER_INVALID_IP == pstDhcpServer->aulSecondaryServerIp[0])
    {
        /* IP非法,说明未配置 */
        return;
    }

    DHCPM_SPINLOCK(&(pstDhcpServerStatus->stSpinLockId));

    do
    {
        /* 如果不是Abnormal状态,不需要倒计时 */
        if (DHCP_SEVER_ABNORMAL != pstDhcpServerStatus->ucSecondarySrvStatus)
        {
            pstDhcpServerStatus->usSecTryTimeInterval = 0;
            break;
        }

        if (0 != pstDhcpServerStatus->usSecTryTimeInterval)
        {
            --(pstDhcpServerStatus->usSecTryTimeInterval);
            break;
        }

        /* Try的时间倒计时为0,将Server Group状态设置为Try */
        pstDhcpServerStatus->ucSecondarySrvStatus = DHCP_SEVER_TRY;
    }
    while(0);

    DHCPM_SPINUNLOCK(&(pstDhcpServerStatus->stSpinLockId));

    return;
}

/*****************************************************************************
 函 数 名  : DHCPM_TryStatusTimeCountDown
 功能描述  : 所有dhcp server group try状态转化倒计时处理
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月2日
    作    者   : jixiaoming 00180244
    修改内容   : 新生成函数

*****************************************************************************/
VOID DHCPM_TryStatusTimeCountDown()
{
    ULONG ulSvrGrpIndex = 0;
    LAP_DHCP_CFG_S *pstDhcpServer = g_stDhcpServerCfgManager.pstDhcpServer;

    for (ulSvrGrpIndex = 0; ulSvrGrpIndex < DHCPGRP_MAX_NUM; ulSvrGrpIndex++)
    {
        /* 目前仅DHCPV6 Server Group使用该方式 */
        if (DHCP_SEVER_GROUP_IS_IPV6 != pstDhcpServer[ulSvrGrpIndex].ucIsDHCPv6)
        {
            continue;
        }

        DHCPM_PrimTryStatusTimeCountDown(ulSvrGrpIndex);

        DHCPM_SecTryStatusTimeCountDown(ulSvrGrpIndex);
    }

    return;
}

/*****************************************************************************
 函 数 名  : DHCPCM_OneSecondTimerProc
 功能描述  : DHCPCM 1秒定时器处理
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月2日
    作    者   : jixiaoming 00180244
    修改内容   : 新生成函数

*****************************************************************************/
VOID DHCPCM_OneSecondTimerProc()
{
    UCHAR ucLogicSlot = 0;

    PTM_DebugBatchSRunCmdProc();

    ucLogicSlot = (UCHAR)CRM_GetSelfLogicSlotID();
    if (E_CRM_ACTIVE != CRM_GetSlotPrimaryInfoOfSelfGroup(ucLogicSlot))
    {
        DHCPM_ADD_COUNTER(221);
        return;
    }

    DHCPM_AlarmTimerProc();

    DHCPM_TryStatusTimeCountDown();

    return;
}

/*****************************************************************************
 函 数 名  : DHCPM_ModDhcpServerGroupNode
 功能描述  : 修改dhcp server group到全局数据结构中
 输入参数  : LAP_DHCP_CFG_S * pstDhcpServerGrpInfo
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007 年10月29日
    作    者   : heguangwei 65937
    修改内容   : 新生成函数

*****************************************************************************/
ULONG DHCPM_ModDhcpServerGroupNode(LAP_DHCP_CFG_S * pstDhcpServerGrpInfo)
{
    ULONG ulServerIndex = 0;
    ULONG ulReturn = 0;

    /*入参检查*/
    if(NULL == pstDhcpServerGrpInfo)
    {
        VOS_Assert(0);
        DHCPM_ADD_COUNTER(223);
        return VOS_ERR;
    }

    /*检查group 索引的有效性*/
    ulServerIndex = pstDhcpServerGrpInfo->usDhcpServerGrpIndex;
    if(DHCP_SERVER_GROUP_MAX_NUM <= ulServerIndex)
    {
        VOS_Assert(0);
        DHCPM_ADD_COUNTER(224);
        DHCPM_DebugPrint(PTM_LOG_ERR, "usDhcpServerGrpIndex %u err", ulServerIndex);
        return VOS_ERR;
    }

    ulReturn = DHCPM_DhcpServerCfgWriteLock();
    if ( VOS_OK != ulReturn )
    {
        return ulReturn;
    }

    VOS_MemCpy(&g_stDhcpServerCfgManager.pstDhcpServer[ulServerIndex], pstDhcpServerGrpInfo, sizeof(LAP_DHCP_CFG_S));

    ulReturn = DHCPM_DhcpServerCfgWriteUnLock();
    if ( VOS_OK != ulReturn )
    {
        return ulReturn;
    }

    return VOS_OK;
}


ULONG DHCPM_RemoveDhcpServerByIndex(ULONG ulDhcpIndex)
{
    LAP_DHCP_CFG_S stDhcpServerGrpInfo = {0};
    ULONG ulReturn = 0;

    if ( DHCPGRP_MAX_NUM <= ulDhcpIndex )
    {
        DHCPM_ADD_COUNTER(225);
        return VOS_ERR;
    }

    DHCPM_ADD_COUNTER(4);

    /* 将dhcp-server group的状态设置为DHCP_SEVER_NORMAL.以使告警能够恢复 */
    (VOID)DHCPM_SetPrimarySrvStatusByIndex(ulDhcpIndex, DHCP_SEVER_NORMAL);
    (VOID)DHCPM_SetSecondarySrvStatusByIndex(ulDhcpIndex, DHCP_SEVER_NORMAL);

    DHCPM_AlarmProcByDhcpServerIndex(ulDhcpIndex, VOS_FALSE);

    /* 删除DHCP Server配置 */
    stDhcpServerGrpInfo.usDhcpServerGrpIndex = (USHORT)ulDhcpIndex;
    ulReturn = DHCPM_ModDhcpServerGroupNode(&stDhcpServerGrpInfo);
    if ( VOS_OK != ulReturn )
    {
        DHCPM_ADD_COUNTER(226);
    }

    PGP_MemZero(&g_pstDhcpServerStatus[ulDhcpIndex], sizeof(DHCP_SERVER_STATUS_S));

    return VOS_OK;
}

ULONG DHCPM_GetTryStatusTimerIntreval()
{
    ULONG ulSoftParaDword71 = 0;
    ULONG ulReturn = 0;

    /*设置UGW探测Server状态的时间间隔，UGW以这个时长扫描DHCP 服务器的状态；默认为180秒*/
    ulReturn = SPM_GetDwordValue(M_SPM_PTM_DHCP_SERVER_INTERVAL, &ulSoftParaDword71);
    if (VOS_OK != ulReturn)
    {
        DHCPM_ADD_COUNTER(265);
        DHCPM_DebugPrint(PTM_LOG_ERR, "SPM_GetByteValue133 fail, ret = %u", ulReturn);
        ulSoftParaDword71 = DHCPC_SERVER_INTERVAL_AND_MIN;
    }

    /*取值范围为180~3600秒*/
    if ((ulSoftParaDword71 > DHCPC_SERVER_INTERVAL_MAX)
        || (ulSoftParaDword71 < DHCPC_SERVER_INTERVAL_AND_MIN))
    {
        DHCPM_ADD_COUNTER(266);
        ulSoftParaDword71 = DHCPC_SERVER_INTERVAL_AND_MIN;
    }

    return ulSoftParaDword71;
}

#define __DHCPM_INIT___________

/*****************************************************************************
 函 数 名  : DHCPM_RegDhcpServerCfgManager
 功能描述  : 注册dhcp server配置管理器
 输入参数  : 无
 输出参数  : 无
 返 回 值  : ULONG
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月20日
    作    者   : y00138047
    修改内容   : 新生成函数

*****************************************************************************/
ULONG DHCPM_RegDhcpServerCfgManager()
{
    ULONG ulMemSize = 0;
    ULONG ulReturn = 0;
    MC_RWLOCK_ID RWLockId = 0;

    ulMemSize = sizeof(LAP_DHCP_CFG_S) * DHCP_SERVER_GROUP_MAX_NUM;

    
    g_stDhcpServerCfgManager.pstDhcpServer = &g_stDhcpServer;
    if ( NULL == g_stDhcpServerCfgManager.pstDhcpServer )
    {
        VOS_Assert(0);
        DHCPM_ADD_COUNTER(227);
        return VOS_ERR;
    }

    ulReturn = PGP_ShrRWLockCreate("L_pstDhcpServerCfg", &RWLockId);
    if ( VOS_OK != ulReturn )
    {
        VOS_Assert(0);
        DHCPM_ADD_COUNTER(233);
        return ulReturn;
    }

    g_stDhcpServerCfgManager.RWLockId = RWLockId;

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : DHCPM_InitDhcpServerCfgManager
 功能描述  : 初始化dhcp server配置管理器
 输入参数  : 无
 输出参数  : 无
 返 回 值  : ULONG
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月20日
    作    者   : y00138047
    修改内容   : 新生成函数

*****************************************************************************/
ULONG DHCPM_InitDhcpServerCfgManager()
{
    ULONG ulRet = 0;
    ULONG ulQueryId = 0;
    LAP_DHCP_CFG_S stDhcpServerGrpInfo = {0};
    ULONG ulMemSize = 0;

    ulMemSize = sizeof(LAP_DHCP_CFG_S) * DHCP_SERVER_GROUP_MAX_NUM;

    VOS_MemSet(g_stDhcpServerCfgManager.pstDhcpServer, 0, ulMemSize );

    ulRet = DBApiQueryFirst(M_LAP_DHCP_TBL_ID,
                            0,
                            NULL,
                            (CHAR *)&stDhcpServerGrpInfo,
                            &ulQueryId);
    if ( M_CFG_DB_API_DBERROR == ulRet )
    {
        DHCPM_ADD_COUNTER(229);
        DHCPM_DebugPrint(PTM_LOG_ERR, "DBApiQueryFirst fail, return = %x", ulRet);
        return ulRet;
    }

    while (M_CFG_DB_API_SUCCESS == ulRet )
    {
        DHCPM_ADD_COUNTER(5);

        /*添加dhcp server group结点到全局数据结构*/
        ulRet = DHCPM_ModDhcpServerGroupNode(&stDhcpServerGrpInfo);
        if(VOS_OK != ulRet)
        {
            DHCPM_ADD_COUNTER(230);
        }

        /*查询下一个*/
        VOS_MemSet((VOID *)&stDhcpServerGrpInfo, 0, sizeof(stDhcpServerGrpInfo));
        ulRet = DBApiQueryNext(&ulQueryId, (CHAR *)&stDhcpServerGrpInfo);
        if ( M_CFG_DB_API_DBERROR == ulRet )
        {
            DHCPM_ADD_COUNTER(231);
            DHCPM_DebugPrint(PTM_LOG_ERR, "DBApiQueryNext fail, return = %x", ulRet);
            return ulRet;
        }
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : DHCPM_InitDhcpServerStatus
 功能描述  : 注册dhcp server状态管理器
 输入参数  : 无
 输出参数  : 无
 返 回 值  : ULONG
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月20日
    作    者   : y00138047
    修改内容   : 新生成函数

*****************************************************************************/
ULONG DHCPM_InitDhcpServerStatus()
{
    ULONG ulMemSize = 0;

    ulMemSize = sizeof(DHCP_SERVER_STATUS_S) * DHCP_SERVER_GROUP_MAX_NUM;

#if 0
    g_pstDhcpServerStatus = PGP_ShrMemAllocByName("pstDhcpServerStatus", SERVICE_MEM_TYPE_SHARE_GM_SC,
                                                MID_DHCPM, ulMemSize);
#endif

    g_pstDhcpServerStatus = g_pstDhcpServerStatusMem;
    if ( NULL == g_pstDhcpServerStatus )
    {
        VOS_Assert(0);
        DHCPM_ADD_COUNTER(232);
        return VOS_ERR;
    }

    if ( VOS_FALSE == PSM_Inf_IsOnlySGRestarted() )
    {
        PGP_MemZero(g_pstDhcpServerStatus, ulMemSize);
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : DHCPM_RegDhcpServer
 功能描述  : 注册dhcp server配置和状态管理器
 输入参数  : 无
 输出参数  : 无
 返 回 值  : ULONG
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月20日
    作    者   : y00138047
    修改内容   : 新生成函数

*****************************************************************************/
ULONG DHCPM_RegDhcpServer()
{
    ULONG ulReturn = VOS_OK;

    g_ulDhcpMInitStep = 200;

    /* DHCPC会调用该函数，需要注册DHCPM的调试打印和调试计数 */
    ulReturn = DHCPM_DbgInit();
    if ( VOS_OK != ulReturn )
    {
        DHCPM_ADD_COUNTER(237);
        return ulReturn;
    }

    g_ulDhcpMInitStep = 300;

    ulReturn = DHCPM_RegDhcpServerCfgManager();
    if ( VOS_OK != ulReturn )
    {
        DHCPM_ADD_COUNTER(238);
        return ulReturn;
    }

    g_ulDhcpMInitStep = 400;

    ulReturn = DHCPM_InitDhcpServerStatus();
    if ( VOS_OK != ulReturn )
    {
        DHCPM_ADD_COUNTER(239);
        return ulReturn;
    }

    g_ulDhcpMInitStep = 500;

    return VOS_OK;
}


ULONG DHCPM_InitTimer()
{
    ULONG ulReturn = 0;

    ulReturn = PGP_Timer_Create( DHCPM_SELF_CSI,
                                 DHCPM_MSG_TYPE_TIMER,
                                 DHCPM_ALARM_TIMER_LENGTH,/*1s*/
                                 ( VOID ( * )( VOID * ) )DHCPCM_OneSecondTimerProc,
                                 NULL,
                                 &g_ulDhcpmAlarmTimerID,
                                 VOS_TIMER_LOOP );
    if ( VOS_OK != ulReturn )
    {
        VOS_Assert( 0 );
        DHCPM_ADD_COUNTER(222);
        return ulReturn;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : DHCPM_CommInit1
 功能描述  : 第一阶段公共初始化
 输入参数  :
 输出参数  :
 返 回 值  : ULONG
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年5月10日
    作    者   : y00138047
    修改内容   : 新生成函数

*****************************************************************************/
ULONG DHCPM_CommInit1()
{
    ULONG ulReturn = VOS_OK;

    g_ulDhcpMInitStep = 1;

    ulReturn = DHCPM_DbgInit();
    if ( VOS_OK != ulReturn )
    {
        DHCPM_ADD_COUNTER(240);
        return ulReturn;
    }

    g_ulDhcpMInitStep = 100;

    ulReturn = DHCPM_RegDhcpServer();
    if ( VOS_OK != ulReturn )
    {
        DHCPM_ADD_COUNTER(241);
        return ulReturn;
    }

    g_ulDhcpMInitStep = 300;

    ulReturn = PGP_RTCreate ( DHCPM_SELF_CSI, IPC_NOTI_VIA_FUNC,
                              0, (IPC_RTNOTIFY_FUNC)PGP_RTDistributeCallback);
    if ( VOS_OK != ulReturn )
    {
        DHCPM_ADD_COUNTER(242);
        DHCPM_DebugPrint(PTM_LOG_ERR, "PGP_RTCreate fail, ulReturn = %x", ulReturn);
        return ulReturn;
    }

    g_ulDhcpMInitStep = 400;

    g_ulDhcpMInitStep = 1000;

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : DHCPM_CommInit3
 功能描述  : 第三阶段公共初始化
 输入参数  : 无
 输出参数  : 无
 返 回 值  : ULONG
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月20日
    作    者   : y00138047
    修改内容   : 新生成函数

*****************************************************************************/
ULONG DHCPM_CommInit3()
{
    ULONG ulReturn = VOS_OK;

    g_ulDhcpMInitStep = 2000;

    DHCPM_CDBRegCallBack();

    g_ulDhcpMInitStep = 2100;

    ulReturn = DHCPM_InitDhcpServerCfgManager();
    if ( VOS_OK != ulReturn )
    {
        DHCPM_ADD_COUNTER(242);
        return ulReturn;
    }

    g_ulDhcpMInitStep = 2400;

    return VOS_OK;
}



#define __DHCPM_COMP_MSG_PROC___________

/*****************************************************************************
 函 数 名  : DHCPM_StartWorkProc
 功能描述  : dhcpm开工消息处理
 输入参数  :
 输出参数  : 无
 返 回 值  : ULONG
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月20日
    作    者   : y00138047
    修改内容   : 新生成函数

*****************************************************************************/
ULONG DHCPM_StartWorkProc( )
{
    ULONG ulRet = VOS_OK;

    ulRet = DHCPM_InitTimer();
    if (VOS_OK != ulRet)
    {
        DHCPM_DebugPrint(PTM_LOG_ERR, "DHCPM_InitTimer fail, ulRet = %x", ulRet);
        return VOS_ERR;
    }

    return VOS_OK;
}

#ifdef __LINUX_PLATFORM__

/*****************************************************************************
 函 数 名  : DHCPM_GetSelfCompInfo
 功能描述  : 获取本组件相关信息
 输入参数  : DMS_COMMID_T myCSI
 输出参数  :
 返 回 值   :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年5月10日
    作    者   : y00138047
    修改内容   : 新生成函数

*****************************************************************************/
VOID DHCPM_GetSelfCompInfo(DMS_COMMID_T myCSI )
{
    g_stDhcpMCompInfo.ullSelfCsi = PSM_Inf_GetSelfCSI(E_COMP_TYPE_DHCPCGM);

    g_stDhcpMCompInfo.ulHandle = PGP_CompGetDopraHandle();

    g_stDhcpMCompInfo.ulSelfCmpIdx = PSM_Inf_GetCmpIndexInOSByCSI(g_stDhcpMCompInfo.ullSelfCsi);

    return;
}

/*****************************************************************************
 函 数 名  : DHCPM_CompMsgDistribute
 功能描述  : 组件消息分发函数
 输入参数  : VOID* pMsg
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年5月10日
    作    者   : y00138047
    修改内容   : 新生成函数

*****************************************************************************/
ULONG DHCPM_CompMsgDistribute(ULONG ulMsgType, VOID* pMsg )
{
    return VOS_OK;
}

#define __DHCPM_COMP_FRAME____________
/*****************************************************************************
 函 数 名  : DHCPM_CompConstruct
 功能描述  : DHCPM组件构造函数
 输入参数  : RTF_COMP_CONSTRUCT_STAGE_E eConstructStage
             DMS_COMMID_T myCSI
             DMS_COMMID_T myCPI
             VOID* pThis
 输出参数  :
 返 回 值  : ULONG
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年5月10日
    作    者   : y00138047
    修改内容   : 新生成函数

*****************************************************************************/
ULONG DHCPM_CompConstruct( RTF_COMP_CONSTRUCT_STAGE_E eConstructStage,
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

            /* 初始化组件参数 */
            DHCPM_GetSelfCompInfo(myCSI);

            ulRet = DHCPM_CommInit1();
            break;

        case RTF_COMP_CONSTRUCT_STAGE2:
            /* 第二阶段 PGPReady*/
            /* CDB配置、License、软参 */
            /* RDB 相关的业务初始化（包括内存，IFA 接口获取，逻辑部署） */
            ulRet = VOS_OK;
            break;

        case RTF_COMP_CONSTRUCT_STAGE3:
            /* 第三阶段: 组件enable, 向平台回Confirm */
            /* Timer初始化 */
            ulRet = DHCPM_CommInit3( );

            /* 该组件不需要注册流控函数，取组件默认的回调函数就行，
               因为该组件只有定时器消息 */

            break;

        default:
            /*错误处理*/
            ulRet = VOS_ERR;
            break;
    }

    vos_printf("DHCPM_CompConstruct stage %u, ret %u", eConstructStage, ulRet);

    return ulRet;
}

/*****************************************************************************
 函 数 名  : DHCPM_CompDestruct
 功能描述  : DHCPM组件析构函数
 输入参数  : DMS_COMMID_T myPid
             VOID* pThis
 输出参数  :
 返 回 值  : ULONG
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年5月10日
    作    者   : y00138047
    修改内容   : 新生成函数

*****************************************************************************/
ULONG DHCPM_CompDestruct( DMS_COMMID_T myPid, VOID* pThis )
{
    vos_printf("Destruct Component DHCPM\r\n");
    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : DHCPM_CompMsgProc
 功能描述  : DHCPM组件消息处理函数
 输入参数  : VOID* pMsg
                  VOID* pThis
 输出参数  :
 返 回 值  : ULONG
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年5月10日
    作    者   : y00138047
    修改内容   : 新生成函数

*****************************************************************************/
ULONG DHCPM_CompMsgProc(VOID* pMsg, VOID* pThis)
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
        DHCPM_ADD_COUNTER(7);
         ulRet = DHCPM_StartWorkProc();
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
        /* 其它队列消息分发处理 */
        ulRet = DHCPM_CompMsgDistribute(ulMsgType, pMsgBody);
    }

    /* 平台消息释放处理*/
    PGP_CompMsgRelease();

    g_ulDhcpMInitStep = 8888;
    return ulRet;
}

#endif

#define __INTERFACE__

ULONG inline DHCPM_SetPrimarySrvStatusByIndex(ULONG ulDhcpIndex, ULONG ulValue)
{
    DHCPM_ADD_COUNTER(8);

    if ( DHCP_SERVER_GROUP_MAX_NUM <= ulDhcpIndex )
    {
        DHCPM_ADD_COUNTER(244);
        return VOS_ERR;
    }

    DHCPM_SPINLOCK(&(g_pstDhcpServerStatus[ulDhcpIndex].stSpinLockId));

    g_pstDhcpServerStatus[ulDhcpIndex].ucPrimarySrvStatus = ulValue;

    if (DHCP_SEVER_NORMAL == ulValue)
    {
        /* 设置状态为Normal时,将扫描计数次数清0 */
        g_pstDhcpServerStatus[ulDhcpIndex].ucPrimTimeoutNum = 0;
        /* DHCPv4 REQUEST无响应次数清0 */
        g_pstDhcpServerStatus[ulDhcpIndex].ucPrimRequestTimeout = 0;
    }

    DHCPM_SPINUNLOCK(&(g_pstDhcpServerStatus[ulDhcpIndex].stSpinLockId));

    return VOS_OK;
}

ULONG inline DHCPM_SetPrimarySrvTestByIndex(ULONG ulDhcpIndex, ULONG ulValue)
{
    DHCPM_ADD_COUNTER(9);

    if ( DHCP_SERVER_GROUP_MAX_NUM <= ulDhcpIndex )
    {
        DHCPM_ADD_COUNTER(247);
        return VOS_ERR;
    }

    DHCPM_SPINLOCK(&(g_pstDhcpServerStatus[ulDhcpIndex].stSpinLockId));

    g_pstDhcpServerStatus[ulDhcpIndex].ucPrimarySrvTest = ulValue;

    DHCPM_SPINUNLOCK(&(g_pstDhcpServerStatus[ulDhcpIndex].stSpinLockId));

    return VOS_OK;
}

ULONG inline DHCPM_SetSecondarySrvStatusByIndex(ULONG ulDhcpIndex, ULONG ulValue)
{
    DHCPM_ADD_COUNTER(10);

    if ( DHCP_SERVER_GROUP_MAX_NUM <= ulDhcpIndex )
    {
        DHCPM_ADD_COUNTER(250);
        return VOS_ERR;
    }

    DHCPM_SPINLOCK(&(g_pstDhcpServerStatus[ulDhcpIndex].stSpinLockId));

    g_pstDhcpServerStatus[ulDhcpIndex].ucSecondarySrvStatus = ulValue;

    if (DHCP_SEVER_NORMAL == ulValue)
    {
        /* 设置状态为Normal时,将扫描计数次数清0 */
        g_pstDhcpServerStatus[ulDhcpIndex].ucSecTimeoutNum = 0;
        /* DHCPv4 REQUEST无响应次数清0 */
        g_pstDhcpServerStatus[ulDhcpIndex].ucSecRequestTimeout = 0;
    }

    DHCPM_SPINUNLOCK(&(g_pstDhcpServerStatus[ulDhcpIndex].stSpinLockId));

    return VOS_OK;
}

ULONG inline DHCPM_SetPrimSrvTimerStatusByIndex(ULONG ulDhcpIndex, UCHAR ucValue)
{
    DHCPM_ADD_COUNTER(17);

    if ( DHCP_SERVER_GROUP_MAX_NUM <= ulDhcpIndex )
    {
        DHCPM_ADD_COUNTER(256);
        return VOS_ERR;
    }

    DHCPM_SPINLOCK(&(g_pstDhcpServerStatus[ulDhcpIndex].stSpinLockId));

    g_pstDhcpServerStatus[ulDhcpIndex].ucPrimSrvTimerStatus = ucValue;

    DHCPM_SPINUNLOCK(&(g_pstDhcpServerStatus[ulDhcpIndex].stSpinLockId));

    return VOS_OK;
}


ULONG inline DHCPM_SetPrimTimeoutNumByIndex(ULONG ulDhcpIndex, UCHAR ucValue)
{
    DHCPM_ADD_COUNTER(13);

    if ( DHCP_SERVER_GROUP_MAX_NUM <= ulDhcpIndex )
    {
        DHCPM_ADD_COUNTER(259);
        return VOS_ERR;
    }

    DHCPM_SPINLOCK(&(g_pstDhcpServerStatus[ulDhcpIndex].stSpinLockId));

    g_pstDhcpServerStatus[ulDhcpIndex].ucPrimTimeoutNum = ucValue;

    DHCPM_SPINUNLOCK(&(g_pstDhcpServerStatus[ulDhcpIndex].stSpinLockId));

    return VOS_OK;
}

ULONG inline DHCPM_SetSecTimeoutNumByIndex(ULONG ulDhcpIndex, UCHAR ucValue)
{
    DHCPM_ADD_COUNTER(14);

    if ( DHCP_SERVER_GROUP_MAX_NUM <= ulDhcpIndex )
    {
        DHCPM_ADD_COUNTER(262);
        return VOS_ERR;
    }

    DHCPM_SPINLOCK(&(g_pstDhcpServerStatus[ulDhcpIndex].stSpinLockId));

    g_pstDhcpServerStatus[ulDhcpIndex].ucSecTimeoutNum = ucValue;

    DHCPM_SPINUNLOCK(&(g_pstDhcpServerStatus[ulDhcpIndex].stSpinLockId));

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : DHCPM_TrySetPrimStatusAbnormalByIndex
 功能描述  : 尝试将主服务器的状态变为Abnormal.
             如果当前状态为Abnormal,什么都不做。
             如果不为Abnormal,将主服务器状态设置为Abnormal,同时设置状态变为
             TRY的时间间隔。
 输入参数  : ULONG ulDhcpIndex
 输出参数  : 无
 返 回 值  : ULONG inline
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月3日
    作    者   : jixiaoming 00180244
    修改内容   : 新生成函数

*****************************************************************************/
ULONG inline DHCPM_TrySetPrimStatusAbnormalByIndex(ULONG ulDhcpIndex)
{
    ULONG   ulTryTimeInterval = 0;
    DHCP_SERVER_STATUS_S *pstDhcpServerStatus = NULL;
    if ( DHCP_SERVER_GROUP_MAX_NUM <= ulDhcpIndex )
    {
        VOS_Assert(0);
        return VOS_ERR;
    }

    ulTryTimeInterval = DHCPM_GetTryStatusTimerIntreval();

    pstDhcpServerStatus = g_pstDhcpServerStatus + ulDhcpIndex;

    DHCPM_SPINLOCK(&(pstDhcpServerStatus->stSpinLockId));
    if (DHCP_SEVER_ABNORMAL != pstDhcpServerStatus->ucPrimarySrvStatus)
    {
        pstDhcpServerStatus->ucPrimarySrvStatus = DHCP_SEVER_ABNORMAL;
        pstDhcpServerStatus->usPrimTryTimeInterval = (USHORT)ulTryTimeInterval;
    }
    DHCPM_SPINUNLOCK(&(pstDhcpServerStatus->stSpinLockId));

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : DHCPM_TrySetSecStatusAbnormalByIndex
 功能描述  : 尝试将备服务器的状态设置为Abnormal.
             如果当前状态为Abnormal,什么都不做。
             如果不为Abnormal,将备服务器状态设置为Abnormal,同时设置状态变为
             TRY的时间间隔。
 输入参数  : ULONG ulDhcpIndex
 输出参数  : 无
 返 回 值  : ULONG inline
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月3日
    作    者   : jixiaoming 00180244
    修改内容   : 新生成函数

*****************************************************************************/
ULONG inline DHCPM_TrySetSecStatusAbnormalByIndex(ULONG ulDhcpIndex)
{
    ULONG   ulTryTimeInterval = 0;
    DHCP_SERVER_STATUS_S *pstDhcpServerStatus = NULL;

    if ( DHCP_SERVER_GROUP_MAX_NUM <= ulDhcpIndex )
    {
        VOS_Assert(0);
        return VOS_ERR;
    }

    ulTryTimeInterval = DHCPM_GetTryStatusTimerIntreval();
    pstDhcpServerStatus = g_pstDhcpServerStatus + ulDhcpIndex;

    DHCPM_SPINLOCK(&(pstDhcpServerStatus->stSpinLockId));
    if (DHCP_SEVER_ABNORMAL != pstDhcpServerStatus->ucSecondarySrvStatus)
    {
        pstDhcpServerStatus->ucSecondarySrvStatus = DHCP_SEVER_ABNORMAL;
        pstDhcpServerStatus->usSecTryTimeInterval = (USHORT)ulTryTimeInterval;
    }
    DHCPM_SPINUNLOCK(&(pstDhcpServerStatus->stSpinLockId));

    return VOS_OK;
}

