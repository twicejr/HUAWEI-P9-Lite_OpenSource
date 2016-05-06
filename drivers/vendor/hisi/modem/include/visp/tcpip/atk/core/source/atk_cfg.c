

#ifdef  __cplusplus
extern  "C"{
#endif

#include "tcpip/atk/include/atk_ext.h"



ULONG ATK_SetWarningSwitch(ULONG ulSwitch, ULONG ulMaxThreshold, ULONG ulMinThreshold)
{

    ULONG ulResult = VOS_OK;

    if (ulSwitch != g_stAttackCfg.ulAtkSwitch)
    {
        extern ULONG ulVRPTID_SOCK;
        extern ULONG ulSOCKTmrQueID;

        if (ATTACK_SWITCH_SET == ulSwitch)
        {
            /* Allocate memory for the hash array to store per interface attack stat. */
            if (NULL == g_pstAttackStatsList)
            {
                g_pstAttackStatsList = (ATTACKSTAT_BY_IF_S **)TCPIP_Malloc(
                                            MID_COMP_ATK | SID_COMP_ATK_HASH_TABLE_S,
                                            (sizeof(ATTACKSTAT_BY_IF_S *) * ATTACK_HASH_LEN));
                if (NULL == g_pstAttackStatsList)
                {
                    TCPIP_LOG_FIXLEN(RUN_LOG_VISP_344E, TCPIP_LOG_LEVEL_ERROR, LOG_TYPE_RUN, 
                        "TCPIP ATK LOG: ATK_SetWarningSwitch (%d, %u, %u), malloc fail \n",
                        ulSwitch, ulMaxThreshold, ulMinThreshold, 0);

                    return ATK_RET_MALLOC_FAIL;
                }

                /* Initialize hash table as all NULL. */
                (VOID)TCPIP_Mem_Set((CHAR *)g_pstAttackStatsList, 0,
                                    (sizeof(ATTACKSTAT_BY_IF_S *) * ATTACK_HASH_LEN)); 
            }

            /* Create 60 second timer to track malformed packet warning */
            if (0 == g_ulATK_Timer)
            {
                ulResult = VOS_Timer_Create(ulVRPTID_SOCK, ulSOCKTmrQueID,
                                            ATTACK_MALFORMED_PKT_TIME * 1000, 
                                            (VOID (*)(VOID *))ATK_Sock_TimeCallBack,
                                            NULL, &g_ulATK_Timer, VOS_TIMER_LOOP);
                if (VOS_OK != ulResult)
                {
                    (VOID)TCPIP_Free((VOID *)g_pstAttackStatsList);

                    g_pstAttackStatsList = NULL;

                    return ATK_RET_START_TIMER_FAIL;
                }
            }
        }
        else
        {
            /* Local variable that is passed to TCPIP_WarningOut. */
            ATTACK_WARNING_S stAttackWarning = {0};

            /* Delete the timer to track malformed packet warning */
            if (0 != g_ulATK_Timer)
            {
                /* Ignore error code returned by delete timer function. */
                (VOID)VOS_Timer_Delete(g_ulATK_Timer);

                g_ulATK_Timer = 0;
            }

            /* Clear the warning if it is already present */
            if (ATTACK_WARNING_BEGIN == g_stAttackWarningStatus.ulWarningType)
            {
                TCPIP_WarningOut(WARNING_ATTACK, (VOID *)&stAttackWarning);
            }

            /* Reset attack warning status. */
            (VOID)TCPIP_Mem_Set((CHAR *)&g_stAttackWarningStatus, 0, sizeof(ATTACK_WARNING_S));

            /* Reset global attack status. */
            (VOID)TCPIP_Mem_Set((CHAR *)&g_stGlobalAttackStats, 0, sizeof(TCPIP_ATTACKSTAT_S));
    
            /* Free all Statistics. */
            (VOID)ATK_DelAllStats();

            /* Free memory for hash array. */
            if (NULL != g_pstAttackStatsList)
            {
                (VOID)TCPIP_Free((VOID *)g_pstAttackStatsList);

                g_pstAttackStatsList = NULL;
            }
        }
    }

    /* Update the configuration */
    if (ATTACK_SWITCH_SET == ulSwitch)
    {
        /* The the threshold values are filled zero, take default values. */
        if ((0 == ulMaxThreshold) && (0 == ulMinThreshold))
        {
            g_stAttackCfg.ulAtkWarnMaxThreshold = ATTACK_WARNING_MAX_THRESHOLD;
            g_stAttackCfg.ulAtkWarnMinThreshold = ATTACK_WARNING_MIN_THRESHOLD;
        }
        else
        {
            g_stAttackCfg.ulAtkWarnMaxThreshold = ulMaxThreshold;
            g_stAttackCfg.ulAtkWarnMinThreshold = ulMinThreshold;
        }
    }

    g_stAttackCfg.ulAtkSwitch = ulSwitch;

    return VOS_OK;
}


ULONG ATK_SetLargeIcmpLen(ULONG ulMaxSize)
{

    g_stAttackCfg.ulLargeIcmpMaxSize = ulMaxSize;

    return VOS_OK;
}


ULONG ATK_GetCfgInfo(ATTACK_CFG_INFO_S *pstAtkCfgInfo)
{

    (VOID)TCPIP_Mem_Copy((VOID *)pstAtkCfgInfo, sizeof(ATTACK_CFG_INFO_S),
                         (VOID *)&g_stAttackCfg, sizeof(ATTACK_CFG_INFO_S));

    return VOS_OK;
}


ULONG ATK_GetStats(TCPIP_ATTACKSTAT_S *pstAtkStat)
{

    if (ATTACK_SWITCH_SET != g_stAttackCfg.ulAtkSwitch)
    {
        return ATK_RET_SWITCH_NOT_SET;
    }

    /* Copy the global malformed packet statistics to the output pointer. */
    (VOID)TCPIP_Mem_Copy((VOID *)pstAtkStat, sizeof(TCPIP_ATTACKSTAT_S),
                         (VOID *)&g_stGlobalAttackStats, sizeof(TCPIP_ATTACKSTAT_S));

    return VOS_OK;
}


ULONG ATK_GetStatsByIf(ULONG ulIfIndex, TCPIP_ATTACKSTAT_S *pstAtkStat)
{

    ULONG ulHashIndex = 0;
    ATTACKSTAT_BY_IF_S *pstAttackStatByIf = NULL;

    if (ATTACK_SWITCH_SET != g_stAttackCfg.ulAtkSwitch)
    {
        return ATK_RET_SWITCH_NOT_SET;
    }

    (VOID)TCPIP_Mem_Set((CHAR *)pstAtkStat, 0, sizeof(TCPIP_ATTACKSTAT_S));

    /* Get hash index using the interface index;*/
    ulHashIndex = HASH_FUN(ulIfIndex);

    /* Access the attack stat by interface structure from the hash table. */
    pstAttackStatByIf = g_pstAttackStatsList[ulHashIndex];

    /* Search in hash list for the entry with same IfIndex. */
    while (NULL != pstAttackStatByIf)
    {
        /* If IfIndex match, break the loop. */
        if (ulIfIndex == pstAttackStatByIf->ulIfIndex)
        {
            break;
        }

        pstAttackStatByIf = pstAttackStatByIf->pst_NextStat;
    }

    /* If entry is not present in list, return error. */
    if (NULL == pstAttackStatByIf)
    {
        return ATK_RET_NO_ATTACK_STAT;
    }

    /* Copy the attack statistics to the local structure. */
    (VOID)TCPIP_Mem_Copy((VOID *)pstAtkStat, sizeof(TCPIP_ATTACKSTAT_S),
                         (VOID *)&(pstAttackStatByIf->stAttackStats),
                         sizeof(TCPIP_ATTACKSTAT_S));

    return VOS_OK;
}


ULONG ATK_ClrStatsByIf(ULONG ulIfIndex, ULONG ulOper)
{

    ULONG ulHashIndex = 0;
    ATTACKSTAT_BY_IF_S *pstAttackStatByIf = NULL;
    ATTACKSTAT_BY_IF_S *pstPrevAttackStat = NULL;

    if (ATTACK_SWITCH_SET != g_stAttackCfg.ulAtkSwitch)
    {
        return ATK_RET_SWITCH_NOT_SET;
    }

    /* Get hash index using the interface index;*/
    ulHashIndex = HASH_FUN(ulIfIndex);

    /* Access the attack stat by interface structure from the hash table. */
    pstAttackStatByIf = g_pstAttackStatsList[ulHashIndex];

    /* Search in hash list for the entry with same IfIndex. */
    while (NULL != pstAttackStatByIf)
    {
        /* If IfIndex match, break the loop. */
        if (ulIfIndex == pstAttackStatByIf->ulIfIndex)
        {

            /* Reduce the counters in global statistics structure.*/
            g_stGlobalAttackStats.ulHeadErrorStat       -= pstAttackStatByIf->stAttackStats.ulHeadErrorStat;
            g_stGlobalAttackStats.ulIpOptErrStat        -= pstAttackStatByIf->stAttackStats.ulIpOptErrStat;
            g_stGlobalAttackStats.ulunkownProStat       -= pstAttackStatByIf->stAttackStats.ulunkownProStat;
            g_stGlobalAttackStats.ulIpSpoofStat         -= pstAttackStatByIf->stAttackStats.ulIpSpoofStat;
            g_stGlobalAttackStats.ulIpReassTimeOutStat  -= pstAttackStatByIf->stAttackStats.ulIpReassTimeOutStat;
            g_stGlobalAttackStats.ulIpReassErrStat      -= pstAttackStatByIf->stAttackStats.ulIpReassErrStat;
            g_stGlobalAttackStats.ulTcpErrorStat        -= pstAttackStatByIf->stAttackStats.ulTcpErrorStat;
            g_stGlobalAttackStats.ulLandAtkStat         -= pstAttackStatByIf->stAttackStats.ulLandAtkStat;
            g_stGlobalAttackStats.ulWinnukeStat         -= pstAttackStatByIf->stAttackStats.ulWinnukeStat;
            g_stGlobalAttackStats.ulIcmpLargeStat       -= pstAttackStatByIf->stAttackStats.ulIcmpLargeStat;

            if (ATTACK_STAT_FREE == ulOper)
            {
                /* Delete statistics from hash table and free memory. */
                if (NULL == pstPrevAttackStat)
                {
                    /* Remove from the start of list. */
                    g_pstAttackStatsList[ulHashIndex] = pstAttackStatByIf->pst_NextStat;
                }
                else
                {
                    pstPrevAttackStat->pst_NextStat = pstAttackStatByIf->pst_NextStat;
                }

                (VOID)TCPIP_Free((VOID *)pstAttackStatByIf);
            }
            else
            {
                /* Reset statistics. */
                (VOID)TCPIP_Mem_Set((CHAR *)&(pstAttackStatByIf->stAttackStats), 0,
                                            sizeof(TCPIP_ATTACKSTAT_S)); 
            }

            return VOS_OK;
        }

        pstPrevAttackStat = pstAttackStatByIf;
        pstAttackStatByIf = pstAttackStatByIf->pst_NextStat;
    }

    /* Return error if statistics not found. */
    return ATK_RET_NO_ATTACK_STAT;
}


ULONG ATK_ClrStats()
{

    ULONG ulResult = 0;
    ULONG ulHashIndex = 0;
    ATTACKSTAT_BY_IF_S *pstAttackStatByIf = NULL;

    if (ATTACK_SWITCH_SET != g_stAttackCfg.ulAtkSwitch)
    {
        return ATK_RET_SWITCH_NOT_SET;
    }

    if(0 != g_ulATK_Timer)
    {
        /* Restart the timer to track malformed packet warning */
        ulResult = VOS_Timer_Delete(g_ulATK_Timer);
        if (VOS_OK != ulResult)
        {
            return ATK_RET_STOP_TIMER_FAIL;
        }

        g_ulATK_Timer = 0;

        ulResult = VOS_Timer_Create(ulVRPTID_SOCK, ulSOCKTmrQueID,
                                ATTACK_MALFORMED_PKT_TIME * 1000, 
                                (VOID (*)(VOID *))ATK_Sock_TimeCallBack,
                                NULL, &g_ulATK_Timer, VOS_TIMER_LOOP);
        if (VOS_OK != ulResult)
        {
            return ATK_RET_START_TIMER_FAIL;
        }
    }

    /* Clean malformed packet warning status. */
    g_stAttackWarningStatus.ulAtkCounts     = 0;
    g_stAttackWarningStatus.ulWarnAtkType   = 0;
    g_stAttackWarningStatus.ulWarnIfIndex   = 0;

    (VOID)TCPIP_Mem_Set((CHAR *)&g_stAttackWarningStatus.stWarnIpHead, 0,
                            sizeof(IP_S));

    /* Clear all entries from hash table. */
    for (; ulHashIndex < ATTACK_HASH_LEN; ulHashIndex++)
    {
        pstAttackStatByIf = g_pstAttackStatsList[ulHashIndex];

        /* Traverse hash list and clear all entries. */
        while (NULL != pstAttackStatByIf)
        {
            /* Reset statistics. */
            (VOID)TCPIP_Mem_Set((CHAR *)&(pstAttackStatByIf->stAttackStats), 0,
                                        sizeof(TCPIP_ATTACKSTAT_S)); 

            pstAttackStatByIf = pstAttackStatByIf->pst_NextStat;
        }
    }

    (VOID)TCPIP_Mem_Set((CHAR *)&g_stGlobalAttackStats, 0, sizeof(TCPIP_ATTACKSTAT_S)); 

    return VOS_OK;
}


VOID ATK_ShowStats(const TCPIP_ATTACKSTAT_S *pstAtkStat)
{

    ULONG ulMsgLen = 0;
    CHAR szInfoBuffer[LEN_1024];

    if (NULL == pstAtkStat)
    {        
        return;
    }

    /* Display statistics as zero if there is not statistics to display. */
    ulMsgLen = TCPIP_SNPRINTF0(szInfoBuffer, LEN_1024, P0("\r\n  ATK Statistic:"));
    ulMsgLen += TCPIP_SNPRINTF(szInfoBuffer + ulMsgLen, LEN_1024 - ulMsgLen, 
        P1("\r\n     Head Error Stat            %5lu", pstAtkStat->ulHeadErrorStat));
    ulMsgLen += TCPIP_SNPRINTF(szInfoBuffer + ulMsgLen, LEN_1024 - ulMsgLen, 
        P1("\r\n     Ip Option Error Stat       %5lu", pstAtkStat->ulIpOptErrStat));
    ulMsgLen += TCPIP_SNPRINTF(szInfoBuffer + ulMsgLen, LEN_1024 - ulMsgLen, 
        P1("\r\n     Unkown Protocol Stat       %5lu", pstAtkStat->ulunkownProStat));
    ulMsgLen += TCPIP_SNPRINTF(szInfoBuffer + ulMsgLen, LEN_1024 - ulMsgLen, 
        P1("\r\n     Ip Spoof Stat              %5lu", pstAtkStat->ulIpSpoofStat));
    ulMsgLen += TCPIP_SNPRINTF(szInfoBuffer + ulMsgLen, LEN_1024 - ulMsgLen, 
        P1("\r\n     Ip Reassembly TimeOut Stat %5lu", pstAtkStat->ulIpReassTimeOutStat));
    ulMsgLen += TCPIP_SNPRINTF(szInfoBuffer + ulMsgLen, LEN_1024 - ulMsgLen, 
        P1("\r\n     Ip Reassembly Error Stat   %5lu", pstAtkStat->ulIpReassErrStat));
    ulMsgLen += TCPIP_SNPRINTF(szInfoBuffer + ulMsgLen, LEN_1024 - ulMsgLen, 
        P1("\r\n     Tcp Error Stat             %5lu", pstAtkStat->ulTcpErrorStat));
    ulMsgLen += TCPIP_SNPRINTF(szInfoBuffer + ulMsgLen, LEN_1024 - ulMsgLen, 
        P1("\r\n     Land Attack Stat           %5lu", pstAtkStat->ulLandAtkStat));
    ulMsgLen += TCPIP_SNPRINTF(szInfoBuffer + ulMsgLen, LEN_1024 - ulMsgLen, 
        P1("\r\n     Winnuke Stat               %5lu", pstAtkStat->ulWinnukeStat));
    ulMsgLen += TCPIP_SNPRINTF(szInfoBuffer + ulMsgLen, LEN_1024 - ulMsgLen, 
        P1("\r\n     Icmp Large Stat            %5lu", pstAtkStat->ulIcmpLargeStat));

    (VOID)TCPIP_InfoOutput(szInfoBuffer);

    return;
}

#ifdef  __cplusplus
}
#endif

